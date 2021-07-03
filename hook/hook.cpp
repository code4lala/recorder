#include <stdio.h>
#include <windows.h>
#include "../common/common.h"

BOOL APIENTRY DllMain(HMODULE, DWORD, LPVOID)
{
    return TRUE;
}

extern "C" __declspec(dllexport) LRESULT CALLBACK hook(
	int code, WPARAM wParam, LPARAM lParam) {
	LOGD("Hello!");
	return 0;
}

extern "C" __declspec(dllexport) void* CDECL GetHookPointer(void) {
	LOGD("Hello!");
	return hook;
}
