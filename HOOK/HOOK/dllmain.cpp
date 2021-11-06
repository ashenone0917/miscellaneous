// dllmain.cpp : 定义 DLL 应用程序的入口点。
//Detours测试
#include "pch.h"
#include "detours.h"
#define __DLL_EXPORT extern "C" __declspec(dllexport)

__DLL_EXPORT void Startup();

typedef LSTATUS (APIENTRY * fnRegCreateKeyW)(HKEY hKey,LPCWSTR lpSubKey,PHKEY phkResult);
typedef LSTATUS (APIENTRY *ProcRegCreateKeyExW)(HKEY hKey,LPCWSTR lpSubKey,
	DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,PHKEY phkResult,LPDWORD lpdwDisposition);
typedef LSTATUS (APIENTRY *fnRegQueryValueW)(HKEY hKey, LPCWSTR lpSubKey,LPWSTR lpData,PLONG lpcbData);
typedef LSTATUS (APIENTRY *fnRegQueryValueExW)(HKEY hKey,LPCWSTR lpValueName,LPDWORD lpReserved, LPDWORD lpType,LPBYTE lpData,LPDWORD lpcbData);
fnRegCreateKeyW OldRegCreateKeyW;
ProcRegCreateKeyExW OldRegCreateKeyExW;
fnRegQueryValueW OldRegQueryValueW;
fnRegQueryValueExW OldRegQueryValueExW;
LSTATUS APIENTRY NewRegCreateKeyW(HKEY hKey, LPCWSTR lpSubKey, PHKEY phkResult)
{
	WCHAR temp[255] = { 0 };
	wsprintf(temp, L"yanchao [%ws]%ws", __FUNCTIONW__, lpSubKey);
	OutputDebugStringW(temp);
	return OldRegCreateKeyW(hKey, lpSubKey, phkResult);
}

LSTATUS APIENTRY NewRegCreateKeyExW(HKEY hKey, LPCWSTR lpSubKey,
	DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition)
{
	WCHAR temp[255] = { 0 };
	wsprintf(temp, L"yanchao [%ws]%ws", __FUNCTIONW__, lpSubKey);
	OutputDebugStringW(temp);
	return OldRegCreateKeyExW(hKey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);
}

LSTATUS APIENTRY NewRegQueryValueW(HKEY hKey, LPCWSTR lpSubKey, LPWSTR lpData, PLONG lpcbData)
{
	WCHAR temp[255] = { 0 };
	wsprintf(temp, L"yanchao [%ws]%ws", __FUNCTIONW__, lpSubKey);
	OutputDebugStringW(temp);
	return OldRegQueryValueW(hKey, lpSubKey, lpData, lpcbData);
}

LSTATUS APIENTRY NewRegQueryValueExW(HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
	WCHAR temp[255] = { 0 };
	wsprintf(temp, L"yanchao [%ws]%ws", __FUNCTIONW__, lpValueName);
	OutputDebugStringW(temp);
	return OldRegQueryValueExW(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
}
void Hook()
{
	
	OutputDebugStringW(L"yanchao Detours test Hook");
	OldRegCreateKeyW = (fnRegCreateKeyW)RegCreateKeyW;
	OldRegCreateKeyExW = (ProcRegCreateKeyExW)RegCreateKeyExW;
	OldRegQueryValueW = (fnRegQueryValueW)RegQueryValueW;
	OldRegQueryValueExW = (fnRegQueryValueExW)RegQueryValueExW;
	 ;
	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)OldRegCreateKeyW, NewRegCreateKeyW);
	DetourAttach(&(PVOID&)OldRegCreateKeyExW, NewRegCreateKeyExW);
	DetourAttach(&(PVOID&)OldRegQueryValueW, NewRegQueryValueW);
	DetourAttach(&(PVOID&)OldRegQueryValueExW, NewRegQueryValueExW);
	DetourTransactionCommit();

}
void UnHook()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)OldRegCreateKeyW, NewRegCreateKeyW);
	DetourDetach(&(PVOID&)OldRegCreateKeyExW, NewRegCreateKeyExW);
	DetourDetach(&(PVOID&)OldRegQueryValueW, NewRegQueryValueW);
	DetourDetach(&(PVOID&)OldRegQueryValueExW, NewRegQueryValueExW);
	DetourTransactionCommit();
}
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Startup();
		break;
	case DLL_PROCESS_DETACH:
		UnHook();
		break;
	}
	return TRUE;
}
__DLL_EXPORT void
Startup()
{
	Hook();
}