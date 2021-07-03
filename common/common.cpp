#include <windows.h>
#include "common.h"
#include <stdio.h>

BOOL APIENTRY DllMain(HMODULE, DWORD, LPVOID)
{
    return TRUE;
}

extern "C" __declspec(dllexport) void CDECL log(const char* szFormat, ...)
{
	static char szBuffer[1024];
	static char szB2[1024];
	static SYSTEMTIME st;
	va_list pArgList;
	va_start(pArgList, szFormat);
	vsnprintf_s(szBuffer, sizeof(szBuffer) / sizeof(char), szFormat, pArgList);
	va_end(pArgList);
	GetLocalTime(&st);
	wsprintfA(szB2, "%02d:%02d:%02d.%03d [%d] %s\n",
		// current time
		st.wHour, st.wMinute, st.wSecond, st.wMilliseconds,
		// process id
		GetCurrentProcessId(),
		// debug log
		szBuffer);
	OutputDebugStringA(szB2);
}
