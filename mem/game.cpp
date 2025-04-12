#include "game.h"

namespace CTX
{
	Memory_t::Memory_t()
	{
		// инициализация модуля
		util::mem::module_t tortuga_mod("Tortuga Game Club.exe");

		// поиск сигнатур
		tortuga.tpc_connect_game = tortuga_mod.find_pattern(
			"48 83 EC ? 83 7A ? ? 75 ? 41 0F B7 00"
		);
	}
}
