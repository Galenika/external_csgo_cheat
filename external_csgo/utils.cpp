#include "main.h"
#include "utils.h"

std::string c_utils::random_string(size_t length)
{
	static std::string alpha_numeric_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	std::random_device rd;
	std::mt19937 gen(rd());
	const std::uniform_int_distribution< size_t > dis(0U, alpha_numeric_chars.size() - 1U);

	std::string random_string("", length);
	for (size_t i = 0; i < length; ++i) {
		random_string.at(i) = alpha_numeric_chars.at(dis(gen));
	}
	return random_string;
}

void c_utils::alloc_console(const char* console_title)
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	SetConsoleTitleA(console_title);
}