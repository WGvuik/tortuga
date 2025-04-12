#pragma once

#include <stdexcept>
#include <format>
#include <minhook.h>
#include <sstream>
#include "mem/game.h"


#define HOOK_FUNCTION(pfnTarget, pfnDetour) \
	using fn ## pfnDetour ## _t = decltype(&pfnDetour); \
	inline fn ## pfnDetour ## _t m_pfn ## pfnDetour = \
		reinterpret_cast<fn ## pfnDetour ## _t>(HookFunction(pfnTarget, reinterpret_cast<void*>(pfnDetour)))

inline void* HookFunction(void* pfnTarget, void* pfnDetour)
{
	void* pfnOriginal = nullptr;
	if (const MH_STATUS status = MH_CreateHook(pfnTarget, pfnDetour, &pfnOriginal); status != MH_OK)
	{
		std::stringstream errorMessage;
		errorMessage << "Failed to hook: " << MH_StatusToString(status);
		throw std::runtime_error(errorMessage.str());
	}
	return pfnOriginal;
}

struct HookHandler_t
{
	HookHandler_t();
	~HookHandler_t();

	static void* __cdecl tcp_connect(const char* ip, int port);

	
	// Примеры хука
	//HOOK_FUNCTION(CTX::Memory->lib.pfn_uv_buf_init, uv_buf_init);
};
