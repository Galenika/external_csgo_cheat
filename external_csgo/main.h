#pragma once

#include <Windows.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <TlHelp32.h>
#include <iterator>
#include <stdio.h>
#include <thread>
#include <string>
#include <random>

#include "utils.h"

namespace offsets
{
	static DWORD_PTR ent_list = 0;
	static DWORD_PTR team_num = 0;
	static DWORD_PTR dormant = 0;
	static DWORD_PTR local_base = 0;
	static DWORD_PTR crosshair_id = 0;
	static DWORD_PTR bone_matrix = 0;
	static DWORD_PTR client_state = 0;
	static DWORD_PTR view_angles = 0;
	static DWORD_PTR health = 0;
	static DWORD_PTR origin = 0;
	static DWORD_PTR view_offset = 0;
}