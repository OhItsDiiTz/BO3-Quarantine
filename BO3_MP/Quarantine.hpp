#pragma once
#include <cellstatus.h>
#include <sys/prx.h>
#include <sys/ppu_thread.h>
#include <sys/timer.h>
#include <sysutil/sysutil_msgdialog.h>
#include <fastmath.h>
#include <sys/process.h>
#include <cell/fs/cell_fs_file_api.h>

#pragma comment (lib, "sysutil_stub")
#pragma comment (lib, "libfs_stub.a")
#pragma comment (lib, "libc.a")

#include "GameStructs.hpp"
#include "Addresses.hpp"
#include "HookManager.hpp"
#include "GameFunctions.hpp"
#include "Variables.hpp"
#include "Menu.hpp"
#include "MenuFuncs.hpp"
#include "BulletTracers.hpp"
//#include "BreadCrumbs.hpp"

#define DUMP_PATH "/dev_hdd0/tmp/Quarantine/rawfiles/"

#define CDECL extern "C"
CDECL void* _sys_malloc(size_t size);
#define malloc _sys_malloc
CDECL void _sys_free(void* ptr);
#define free _sys_free
CDECL void* _sys_memcpy(void* dest, const void* src, size_t n);
#define memcpy _sys_memcpy
CDECL int _sys_printf(const char* fmt, ...);
#define printf _sys_printf
CDECL char* _sys_strcpy(char* dest, const char* src);
#define strcpy _sys_strcpy
CDECL size_t _sys_strlen(const char* str);
#define strlen _sys_strlen
CDECL int _sys_strcmp(const char* s1, const char* s2);
#define strcmp _sys_strcmp
CDECL void* _sys_memset(void* m, int c, size_t n);
#define memset _sys_memset

struct RawFileAsset;

void R_EndFrame_Detour();
void R_SetDepthOfField_Detour(uint32_t viewInfo, uint32_t sceneParams);
void CL_WritePacket_Detour(uint32_t r3);
void CL_GamepadButtonEventForPort_Detour(int portIndex, int key, int buttonEvent, uint32_t time, int button);
void CG_PredictPlayerState_Detour(int localClientNum);
bool CL_GetSnapshot_Detour(int localClientNum, int r4, int snapshot);

void PrintRawfile(RawFileAsset * pRawfile);

extern sys_ppu_thread_t start_thread;

void * operator new(size_t r3);
void * operator new[](size_t r3);
void operator delete(void * r3);
void operator delete[](void * r3);

void write_memory(uint64_t address, void* data, size_t size);
int32_t sys_dbg_read_process_memory(uint64_t address, void* data, size_t size);
int32_t sys_dbg_write_process_memory(uint64_t address, const void* data, size_t size);
int32_t sys_dbg_write_process_memory_ps3mapi(uint64_t ea, const void* data, size_t size);
int32_t sys_dbg_read_process_memory_ps3mapi(uint64_t ea, void* data, size_t size);
void HookFunctionStart(uint32_t functionStartAddress, uint32_t newFunction, uint32_t functionStub);
void UnHookFunctionStart(uint32_t functionStartAddress, uint32_t functionStub);

uint32_t ReverseInt(uint32_t address);


