#pragma once

struct HookHandler_t;

namespace Hooks
{
	void Attach();
	void Detach();

	HookHandler_t& Get();
}
