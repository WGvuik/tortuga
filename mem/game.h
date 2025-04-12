#pragma once

#include <optional>
#include "modules.h" // где лежит util::mem::module_t и mem::addr_t

namespace CTX
{
	struct Memory_t
	{
		struct
		{
			util::mem::addr_t tpc_connect_game;
		} tortuga;

		Memory_t(); // конструктор, который инициализирует адреса
	};

	inline std::optional<Memory_t> Memory = std::nullopt; // отложенная инициализация
}
