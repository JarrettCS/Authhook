#include "Global.h"

extern "C" 
{

}

VOID WINAPI HeaderProc(DWORD dwPID)
{

}

void InitializeConsole()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
}

DWORD WINAPI MainProc(PVOID)
{

	DWORD dwCurProcId = GetCurrentProcessId();
	HeaderProc(dwCurProcId);

	bool bInit = true;

	bInit &= HookSockApi();
	bInit &= HookWinApi();
	bInit &= HookNMCO();

	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
	
		DisableThreadLibraryCalls(hinstDLL);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&MainProc, NULL, NULL, NULL);
	}

	return TRUE;
}
