#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <fcntl.h>
#include <io.h>
#include <cstdint>
#include <cstdlib>
#include <atomic>
#include <memory>
#include <vector>
#include <string>
#include <tlhelp32.h>
#include <random>
#include <string_view>
#include <tchar.h>
#include "glm/glm.hpp"

#include "xorstr.hpp"

#include <dwmapi.h>
#include <comdef.h> 
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "ImGui/ImGui.h"
#include "ImGui/ImGui_impl_dx9.h"
#include "ImGui/ImGui_impl_win32.h"

#include "render.h"
#include "Vectors.h"
#include "kernel.h"
#include "pattern.h"
#include "xor.h"
#include "globals.h"
#include "decs.h"
#include "engine.h"
#include "math.h"
#include "menu.h"
#include "draw.h"
#include "SkeetFont.h"
#pragma comment(lib, "dwmapi.lib")

const MARGINS Margin = { -1 };

HRESULT DirectXInit(HWND hWnd);
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
void SetupWindow();
WPARAM MainLoop();
void CleanuoD3D();

int isTopwin();
void SetWindowToTarget();
void create_console();

#define TopWindowGame 11
#define TopWindowMvoe 22

DWORD ScreenCenterX;
DWORD ScreenCenterY;

IDirect3D9Ex* p_Object = NULL;
IDirect3DDevice9Ex* p_Device = NULL;
D3DPRESENT_PARAMETERS p_Params = { NULL };
std::string comcalma;
std::string opatudobem;
std::string vsf;
#define M_Name (opatudobem.c_str())
HWND MyWnd = NULL;
HWND GameWnd = NULL;
HWND GameWindow = NULL;
RECT GameRect = { NULL };
MSG Message = { NULL };

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
