#include "Global.h"
#include <stdio.h>

bool Hook_CreateWindowExA(bool bEnable)
{
	static auto _CreateWindowExA = decltype(&CreateWindowExA)(GetFuncAddress("USER32", "CreateWindowExA"));

	decltype(&CreateWindowExA) Hook = [](DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) -> HWND
	{
		auto lpLocalWndName = lpWindowName;

		if (!strcmp(lpClassName, "MapleStoryClass"))
		{
			FuckMaple();
			lpLocalWndName = OPT_APPNAME;
		}

		return _CreateWindowExA(dwExStyle, lpClassName, lpLocalWndName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	};

	return SetHook(bEnable, reinterpret_cast<void**>(&_CreateWindowExA), Hook);
}

bool Hook_CreateMutexA(bool bEnable)
{
	static auto _CreateMutexA = decltype(&CreateMutexA)(GetFuncAddress("KERNEL32", "CreateMutexA"));

	decltype(&CreateMutexA) Hook = [](LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName) -> HANDLE
	{
		if (lpName && strstr(lpName, "WvsClientMtx"))
		{
			char szMutex[128];
			int nPID = GetCurrentProcessId();

			sprintf_s(szMutex, "%s-%d", lpName, nPID);
			Log("MultiClient: Faking %s", szMutex);
			lpName = szMutex;

		}

		return _CreateMutexA(lpMutexAttributes, bInitialOwner, lpName);
	};

	return SetHook(bEnable, reinterpret_cast<void**>(&_CreateMutexA), Hook);
}


bool Hook_WriteStageLogA(bool bEnable)
{
	typedef int(__cdecl* pWriteStageLogA)(int nIdx, ZXString<char>* szMessage);
	static auto _WriteStageLogA = (pWriteStageLogA)(GetFuncAddress("nxgsm", "WriteStageLogA"));

	pWriteStageLogA Hook = [](int nIdx, ZXString<char>* szMessage) -> int
	{
		Log("WriteStageLogA: %s", szMessage->m_pStr);
		return 0;
	};

	return SetHook(bEnable, reinterpret_cast<void**>(&_WriteStageLogA), Hook);
}

bool Hook_WriteErrorLogA(bool bEnable)
{
	typedef int(__cdecl* pWriteErrorLogA)(int nIdx, ZXString<char>* szMessage);
	static auto _WriteErrorLogA = (pWriteErrorLogA)(GetFuncAddress("nxgsm", "WriteErrorLogA"));

	pWriteErrorLogA Hook = [](int nIdx, ZXString<char>* szMessage) -> int
	{
		Log("WriteErrorLogA: %s", szMessage->m_pStr);
		return 0;
	};

	return SetHook(bEnable, reinterpret_cast<void**>(&_WriteErrorLogA), Hook);
}

bool HookWinApi()
{
	bool bResult = true;

	bResult &= Hook_CreateWindowExA(true);

	return bResult;
}