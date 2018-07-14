typedef float matrix3x4[3][4];

class c_entity : c_singleton<c_entity>
{
public:

	DWORD get_player(int i) {
		return c_mem::instance()->read_mem<DWORD>(client_dll + offsets::ent_list + (i * 0x10));
	}

	vector_3 get_angles() {
		DWORD engine_ptr = c_mem::instance()->read_mem<DWORD>(engine_dll + offsets::client_state);
		return c_mem::instance()->read_mem<vector_3>(engine_ptr + offsets::view_angles);
	}

	vector_3 get_bone_pos(DWORD entity, int bone) { // credits to a8pure
		uintptr_t bone_matrix_ptr = c_mem::instance()->read_mem<DWORD>(entity + offsets::bone_matrix);
		matrix3x4 bone_matrix[128];

		ReadProcessMemory(handle, (PBYTE*)(bone_matrix_ptr), &bone_matrix, sizeof(bone_matrix), 0);

		return vector_3(
			bone_matrix[bone][0][3],
			bone_matrix[bone][1][3],
			bone_matrix[bone][2][3]
		);
	}

	vector_3 get_origin(DWORD ent) {
		return c_mem::instance()->read_mem<vector_3>(ent + offsets::origin);
	}

	vector_3 get_eye_position(DWORD ent) {
		vector_3 View = c_mem::instance()->read_mem<vector_3>(ent + offsets::view_offset);
		return(get_origin(ent) + View);
	}

	int get_team(DWORD ent) {
		return c_mem::instance()->read_mem<int>(ent + offsets::team_num);
	}

	bool is_dormant(DWORD ent) {
		return c_mem::instance()->read_mem<bool>(ent + offsets::dormant);
	}

	int get_health(DWORD ent) {
		return c_mem::instance()->read_mem<int>(ent + offsets::health);
	}

	bool is_alive(DWORD ent) {
		return (get_health(ent) >= 1) ? true : false;
	}

	int get_class_id(DWORD ent) {
		int vt = c_mem::instance()->read_mem<DWORD>(ent + 0x8);
		int fn = c_mem::instance()->read_mem<DWORD>(vt + 2 * 0x4);
		int cls = c_mem::instance()->read_mem<DWORD>(fn + 0x1);
		return c_mem::instance()->read_mem<int>(cls + 20);
	}

};