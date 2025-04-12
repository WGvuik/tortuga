#include "hooks.hpp"
#include <iostream>
#include <windows.h>


void UnlockConsole() {
	// Освобождаем консоль, если уже есть
	if (GetConsoleWindow() != NULL)
		FreeConsole();

	AllocConsole();

	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	freopen_s(&f, "CONOUT$", "w", stderr);
	freopen_s(&f, "CONIN$", "r", stdin);

	SetStdHandle(STD_OUTPUT_HANDLE, GetStdHandle(STD_OUTPUT_HANDLE));
	SetStdHandle(STD_ERROR_HANDLE, GetStdHandle(STD_ERROR_HANDLE));
	SetStdHandle(STD_INPUT_HANDLE, GetStdHandle(STD_INPUT_HANDLE));

	HWND consoleWindow = GetConsoleWindow();
	if (consoleWindow != NULL) {
		ShowWindow(consoleWindow, SW_SHOW);
		SetForegroundWindow(consoleWindow);
	}
}


void LockConsole() {
	// Закрываем консоль, если нужно
	if (GetConsoleWindow() != NULL) {
		FreeConsole();
	}
}




DWORD WINAPI main(LPVOID lpParam)
{
	try
	{
		UnlockConsole();
		Hooks::Attach();
		std::cout << "Hooks attached!\n";

		// ... тест хуков ...
		while (!(GetAsyncKeyState(VK_END) & 0x8000)) {
			Hooks::Detach();
			Sleep(100);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}
	std::cout << "Unloading...\n";
	LockConsole();

	HMODULE hModule = reinterpret_cast<HMODULE>(lpParam);
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, main, hModule, 0, nullptr);
	}
	return TRUE;
}
