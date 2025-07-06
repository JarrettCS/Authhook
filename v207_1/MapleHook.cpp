#include "Global.h"
#include "CWvsContext.h"
#include <intrin.h>
#include <map>
#include <string>

std::map<int, std::string>	g_mStringPool;

//----------------------------------------------------------------------------------------------------

//typedef void(__cdecl* set_stage_t)(void* pThis, void* pParam);
//auto set_stage = reinterpret_cast<set_stage_t>(0x01AA4610);

//typedef int(__cdecl* ZtlSecureFuse_int_t)(int* at, unsigned int uCS);
//auto ZtlSecureFuse_int = reinterpret_cast<ZtlSecureFuse_int_t>(0x00872530);

typedef INT16(__cdecl* ZtlSecureFuse_short_t)(INT16* at, unsigned int uCS);
auto ZtlSecureFuse_short = reinterpret_cast<ZtlSecureFuse_short_t>(0x00873820);

typedef ZXString<char>* (__fastcall* StringPool__GetString_t)(void* ecx, void* edx, ZXString<char>* result, unsigned int nIdx, char formal);
auto StringPool__GetString = reinterpret_cast<StringPool__GetString_t>(0x00C659A0); // 55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 83 EC 14 53 56 57 A1 ? ? ? ? 33 C5 50 8D 45 F4 64 A3 ? ? ? ? 8B F9 89 7D F0 8B 5D 0C 53 C7 45 ? ? ? ? ? E8 ? ? ? ? 83 C4 04 85 C0 74 27 8B 75 08 8B CE  ///////////    55 8B EC 6A FF 68 58 C2 1F 03 64 A1 00 00 00 00 50 83 EC 14 53 56 57 A1 88 FA E7 03 33 C5 50 8D 45 F4 64 A3 00 00 00 00 8B F9 89 7D F0 8B 5D 0C
typedef void(__fastcall* ZXString_char__Assign_t)(void* pThis, void* edx, const char* s, int n);
auto ZXString_char__Assign = reinterpret_cast<ZXString_char__Assign_t>(0x00826AD0); // 55 8B EC 57 8B F9 8B 4D 08 85 C9 75 1D 8B 07 85 C0 74 4C 83 C0 F4 50 E8 ? ? ? ? 83 C4 04 C7 07 ? ? ? ? 5F 5D C2 08 00       ///////////     55 8B EC 57 8B F9 8B 4D 08 85 C9 75 1D 8B 07 85 C0 74 4C 83 C0 F4 50 E8 24 12 CD FF 83 C4 04 C7 07 00 00 00 00 5F 5D C2 08 00 56 8B 75 0C 83 FE

typedef int* (__cdecl* SetPotentialAndAdditionalDescTitle_t)(void* pThis, int nGrade, void* a3, void* a4);
auto SetPotentialAndAdditionalDescTitle = reinterpret_cast<SetPotentialAndAdditionalDescTitle_t>(0x024EE930);

typedef void(__fastcall* CUIToolTip__SetNewToolTip_Equip_t)(void* pThis, void* edx, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, unsigned int a10, int a11, int a12, int a13, int a14, int a15, int a16, char a17, int a18, int a19, int a20, int a21, int a22, int a23, char a24, int a25, int a26, int* a27, int a28, int a29, char a30, int a31, int a32, int a33);
auto CUIToolTip__SetNewToolTip_Equip = reinterpret_cast<CUIToolTip__SetNewToolTip_Equip_t>(0x0247D660);

typedef double(__cdecl* CalcDamage__CalcDamageByWT_t)(int nWT, int* bs, int nPAD, int nMAD, int nSkillID, int nSetBaseDamage);
auto CalcDamage__CalcDamageByWT = reinterpret_cast<CalcDamage__CalcDamageByWT_t>(0x0088ECB0);

ZXString<char>* __fastcall StringPool__GetString_Hook(void* pThis, void* edx, ZXString<char>* result, unsigned int nIdx, char formal)
{
	if (g_mStringPool.count(nIdx) > 0)
	{
		auto szEntry = g_mStringPool[nIdx];

		result->m_pStr = 0;
		ZXString_char__Assign(result, edx, szEntry.c_str(), -1);

		return result;
	}

	return StringPool__GetString(pThis, edx, result, nIdx, formal);
}

double __cdecl CalcDamage__CalcDamageByWT__Hook(int nWT, int* bs, int nPAD, int nMAD, int nSkillID, int nSetBaseDamage)
{
	return CalcDamage__CalcDamageByWT(nWT, bs, nPAD, nMAD, nSkillID, nSetBaseDamage);
}

int* __cdecl SetPotentialAndAdditionalDescTitle__Hook(void* pThis, int nGrade, void* a3, void* a4)
{
	PatchNull(0x033503C0, 18);

	switch (nGrade)
	{
	case 4:
		WriteProcessMemory(GetCurrentProcess(), (void*)0x033503C0, L"legendary", 20, NULL);
		PatchByte(0x24EEC8D, 0x29);
		break;
	case 5:
		WriteProcessMemory(GetCurrentProcess(), (void*)0x033503C0, L"supreme", 16, NULL);
		PatchByte(0x24EEC8D, 0x28);
		nGrade = 4;
		break;
	case 6:
		WriteProcessMemory(GetCurrentProcess(), (void*)0x033503C0, L"mystic", 14, NULL);
		PatchByte(0x24EEC8D, 0x25);
		nGrade = 4;
		break;
	default:
		break;
	}
	return SetPotentialAndAdditionalDescTitle(pThis, nGrade, a3, a4);
}

void __fastcall CUIToolTip__SetNewToolTip_Equip_Hook(void* pThis, void* edx, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, unsigned int a10, int a11, int a12, int a13, int a14, int a15, int a16, char a17, int a18, int a19, int a20, int a21, int a22, int a23, char a24, int a25, int a26, int* a27, int a28, int a29, char a30, int a31, int a32, int a33)
{
	auto v1047 = (int*)a4;
	auto v215 = (int)v1047;

	if ((ZtlSecureFuse_short((INT16*)(v215 + 282), *(DWORD*)(v215 + 286)) & 2) != 0) 
	{
		g_mStringPool[8418] = std::string("#cThis item has been augmented.");

		if ((ZtlSecureFuse_short((INT16*)(v215 + 282), *(DWORD*)(v215 + 286)) & 0x1000) != 0) 
		{
			g_mStringPool[8418].append("\nShard of Recollection applied.");
		}

		g_mStringPool[8418].append("#");
	}

	return CUIToolTip__SetNewToolTip_Equip(pThis, edx, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32, a33);
}

//----------------------------------------------------------------------------------------------------

void InitStringPool()
{
	g_mStringPool[4727] = std::string("ElodinMS 207 - Version 1.0");
	
	g_mStringPool[3737] = std::string("#1");
	g_mStringPool[3738] = std::string("#2");
	g_mStringPool[3739] = std::string("#3");
	g_mStringPool[3740] = std::string("#4");
	g_mStringPool[3741] = std::string("#5");
	g_mStringPool[3742] = std::string("#6");
	g_mStringPool[3743] = std::string("#7");
	g_mStringPool[3744] = std::string("#8");

}

void FuckMaple()
{
	InitStringPool();

	PatchRetZero(0x2AC0720); // NGS Bypass v207.1
	PatchRetZero(0x2ACF1A0); // CRC Bypass v207.1


	PatchChat(0x011C8B05); // Bypass Chat Spam   
	PatchChat(0x011C8A35); // Bypass Chat Spam    
	PatchNoFade(0x01B2565F); // No Fade 
	PatchNoFade(0x01B25CBF); // No Fade 
	PatchNop(0x012E30BB, 6); // Drop Cash Items
	PatchNop(0x012E30C7, 6); // Drop Cash Items 
	PatchUI(0x027DCE81); // No UI Transparency

	PatchByte(0x01B145CE, 0); // 1 above this is bPlainText
	PatchByte(0x01B14088, 0); // Pic Typer

	SetHook(TRUE, reinterpret_cast<void**>(&StringPool__GetString), StringPool__GetString_Hook);
	SetHook(TRUE, reinterpret_cast<void**>(&SetPotentialAndAdditionalDescTitle), SetPotentialAndAdditionalDescTitle__Hook);
	SetHook(TRUE, reinterpret_cast<void**>(&CUIToolTip__SetNewToolTip_Equip), CUIToolTip__SetNewToolTip_Equip_Hook);

}
