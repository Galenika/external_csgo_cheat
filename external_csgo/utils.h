#pragma once
#include "singleton.h"

class c_utils : c_singleton<c_utils>
{
public:
	std::string random_string(size_t length);

	void alloc_console(const char * console_title);

};