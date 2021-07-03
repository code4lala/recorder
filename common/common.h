#pragma once

extern "C" __declspec(dllexport) void CDECL log(const char* szFormat, ...);

#define LOGI(format, ...) log("[I][%s][%d]" format, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGD(format, ...) log("[D][%s][%d]" format, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGE(format, ...) log("[E][%s][%d]" format, __FUNCTION__, __LINE__, ##__VA_ARGS__)
