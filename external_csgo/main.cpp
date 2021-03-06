#pragma once
#include <Windows.h>
HANDLE handle = nullptr;
DWORD proc_id = NULL;
DWORD client_dll = NULL;
DWORD engine_dll = NULL;
DWORD local_player = NULL;

#include "mem.h"
#include "main.h"
#include "vector.h"
#include "math.h"
#include "entity.h"
#include "ChromaSDKImpl.h"


bool enemy_in_fov(DWORD player)
{
	float max_fov = 5.f;

	const float fov = c_math().get_fov(c_entity().get_angles(), c_entity().get_eye_position(local_player), c_entity().get_bone_pos(player, 8));

	if (fov < max_fov && c_entity().get_class_id(player) == 35)
	{
		max_fov = fov;
		return true;
	}
	return false;
}


int main()
{
	c_utils().alloc_console(c_utils().random_string(30).c_str());
	c_mem::instance()->init("csgo.exe");
	g_chroma_sdk.Initialize();

	handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proc_id);
	client_dll = c_mem::instance()->get_module_base("client_panorama.dll");
	engine_dll = c_mem::instance()->get_module_base("engine.dll");

	offsets::local_base = 0xC5F80C;
	offsets::ent_list = 0x4C3C3EC;
	offsets::client_state = 0x586A74;
	offsets::team_num = 0xF0;
	offsets::dormant = 0xE9;
	offsets::health = 0xFC;
	offsets::crosshair_id = 0xB2B8;
	offsets::bone_matrix = 0x2698;
	offsets::view_angles = 0x4D10;
	offsets::origin = 0x134;
	offsets::view_offset = 0x104;

	while (true)
	{
		local_player = c_mem::instance()->read_mem<uintptr_t>(client_dll + offsets::local_base);

		int flicker_distance = 5;

		for (int i = 0; i <= 64; i++) {
			DWORD player = c_entity().get_player(i);
			int local_team = c_entity().get_team(local_player);
			int enemy_team = c_entity().get_team(player);


			if (player == local_player ||
				local_team == enemy_team ||
				c_entity().is_dormant(player) ||
				!c_entity().is_alive(player))
				continue;

			if (enemy_in_fov(player)) {
				vector_3 a = c_entity().get_origin(player);
				vector_3 b = c_entity().get_origin(local_player);
				flicker_distance = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2)) * METERS_PER_INCH;

				RZEFFECTID EffectId = GUID_NULL;
				if (IsEqualGUID(EffectId, GUID_NULL))
				{
					g_chroma_sdk.CreateEffectGroup(&EffectId);

					RZEFFECTID Frame1, Frame2;
					ChromaSDK::Mouse::BLINKING_EFFECT_TYPE effect = {};
					effect.LEDId = ChromaSDK::Mouse::RZLED_ALL;

					int health = c_entity().get_health(player);
					int r = 255 - (health * 2.55);
					int g = health * 2.55;

					effect.Color = RGB(r, g, 0);

					g_chroma_sdk.CreateMouseEffectImpl(ChromaSDK::Mouse::CHROMA_STATIC, &effect, &Frame1);
					g_chroma_sdk.CreateMouseEffectImpl(ChromaSDK::Mouse::CHROMA_NONE, NULL, &Frame2);

					g_chroma_sdk.AddToGroup(EffectId, Frame2, 200);  // Clear the LEDs
					g_chroma_sdk.AddToGroup(EffectId, Frame1, 200);
				}
				g_chroma_sdk.SetEffectImpl(EffectId);
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(int(flicker_distance * 10)));
	}
	return 0;
}
