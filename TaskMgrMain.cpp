#include <iostream>
#include <Windows.h>

uintptr_t baseAddress = (uintptr_t)GetModuleHandleA("taskmgr.exe");

struct PTH
{
	int procs;
	int threads;
	int handles;
};

DWORD MainThread(HMODULE hModule)
{
	AllocConsole();
	FILE* f = new FILE;
	freopen_s(&f, "CONOUT$", "w", stdout);

	std::cout << "<Reversing windows task manager project [CONSOLE]>" << std::endl;

	PTH* procThreadsHandles = (PTH*)(baseAddress + 0x11C38C);
	std::cout << "Processes running: " << procThreadsHandles->procs << std::endl;
	std::cout << "Threads running: " << procThreadsHandles->threads << std::endl;
	std::cout << "Handles opened: " << procThreadsHandles->handles << std::endl;

	while (!GetAsyncKeyState(VK_DELETE) & 1)
	{
		
	}

	FreeConsole();
	fclose(f);
	FreeLibraryAndExitThread(hModule, NULL);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulReasonForCall, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hModule);

	if (ulReasonForCall == DLL_PROCESS_ATTACH)
		CloseHandle(CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, nullptr));
	if (ulReasonForCall != DLL_PROCESS_ATTACH)
		return TRUE;

	return TRUE;
}
