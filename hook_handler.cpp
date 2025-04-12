#include "hook_handler.hpp"
#include "hooks.hpp"
#include <iostream>

HookHandler_t::HookHandler_t() = default;
HookHandler_t::~HookHandler_t() = default;

void* __cdecl HookHandler_t::tcp_connect(const char* ip, int port)
{
	std::cout << "[HOOK] tcp_connect to " << ip << ":" << port << '\n';
	return Hooks::Get().tcp_connect(ip, port);
}
