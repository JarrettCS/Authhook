#include <Windows.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include "MapleType.h"
#include "ThemidaSDK.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "detours.lib")
#pragma comment(lib, "Version.lib")

#define DISCORD_REQUIRE(x) assert(x == DiscordResult_Ok)

//---------------------------------------------------------------------------------------------


#define OPT_APPVERSION		"1.0.0.1"

#define OPT_APPNAME			"Destiny"
#define OPT_ADDR_HOSTNAME   "192.168.1.117"

#define OPT_ADDR_SEARCH		"8.31.99."
#define OPT_ADDR_NEXON		"8.31.99.141"
#define OPT_PORT_LOW		8484
#define OPT_PORT_HIGH		8989

#define CLIENT_ID	1321232945700147250


//---------------------------------------------------------------------------------------------

void FuckMaple();

bool HookNMCO();
bool HookWinApi();
bool HookSockApi();
//bool HookCRC();

//---------------------------------------------------------------------------------------------

void Log(const char* format, ...);

void PatchByte(DWORD dwAddress, BYTE byReplacement);
void PatchJmp(DWORD dwAddress, DWORD dwDest);
void PatchRetZero(DWORD dwAddress);
void PatchNop(DWORD dwAddress, DWORD dwCount);
void PatchFJ(DWORD dwAddress);
void PatchChat(DWORD dwAddress);
void PatchNoBreath(DWORD dwAddress);
void PatchNoFade(DWORD dwAddress);
void PatchUI(DWORD dwAddress);
void PatchDrop(DWORD dwAddress);
void PatchUnlimitedAttack(DWORD dwAddress);
void PatchNull(DWORD dwAddress, DWORD dwCount);

void CatchMessage(char* result, size_t maxlen, const char* message, ...);
TCHAR* GenerateWindowTitle(HINSTANCE hInstance);

DWORD GetFuncAddress(LPCSTR lpModule, LPCSTR lpFunc);

BOOL SetHook(BOOL bInstall, PVOID* ppvTarget, PVOID pvDetour);