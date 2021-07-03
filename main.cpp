#include <windows.h>
#include <stdio.h>
#include "common/common.h"

typedef LRESULT (*HookType)(
	int code, WPARAM wParam, LPARAM lParam);
typedef void* (*GetHookType)(void);

DWORD WINAPI fBackgroundThread(LPVOID) {
	LOGD("Hello world!");
	HINSTANCE hinstDLL = LoadLibrary(TEXT("hook.dll"));
	if(hinstDLL == NULL)
	{
		LOGE("load dll failed");
		return 0;
	}
	LOGI("load dll succeed");
	GetHookType getHook = (GetHookType)GetProcAddress(hinstDLL, "GetHookPointer");
	if (getHook == NULL)
	{
		LOGE("load getHook failed");
		return 0;
	}
	LOGI("load getHook succeed");
	HookType hook = (HookType)getHook();
	LOGI("call hook now");
	hook(0, 0, 0);
	LOGI("call hook succeed");
	HHOOK handleHook = SetWindowsHookEx(WH_SHELL, hook, hinstDLL, 0);
	if (handleHook == NULL)
	{
		DWORD e = GetLastError();
		LOGE("handleHook is NULL, error = %d, 0x%x", e, e);
	}else
	{
		LOGI("handleHook created");
	}
	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int) {
	HANDLE hBackgroundThread = CreateThread(nullptr, 0, fBackgroundThread,
		nullptr, 0, nullptr);
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CloseHandle(hBackgroundThread);
	return (int)msg.wParam;
}
