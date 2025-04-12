#include "hooks.hpp"
#include "hook_handler.hpp"

#include <optional>

namespace Hooks
{
	std::optional<HookHandler_t> hookHandler;

	void Attach()
	{
		if (MH_Initialize() != MH_OK)
			throw std::runtime_error("Failed to initialize MinHook");

		hookHandler.emplace();

		if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
			throw std::runtime_error("Failed to enable hooks");
	}

	void Detach()
	{
		MH_DisableHook(MH_ALL_HOOKS);
		MH_Uninitialize();

		hookHandler.reset();
	}

	HookHandler_t& Get()
	{
		return hookHandler.value();
	}
}
