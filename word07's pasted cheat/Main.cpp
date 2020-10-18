#include "main.h"

DWORD WINAPI aim_thread(LPVOID)
{
	while (TRUE)
	{
		math::aim::AimbotLoop();

		Sleep(5);
	}

	return true;
}
HWND hwnd = NULL;
bool initialize()
{
	m_driver_control = kernel_control_function();

	if (!m_driver_control)
		return false;

	PID = GetProcessID(XorString("RustClient.exe"));

	if (!PID)
		return false;

	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	baseAddress = call_driver_control(
		m_driver_control, ID_GET_PROCESS_BASE, PID);

	if (baseAddress == NULL) {
		return false;
	}

	unityModule = call_driver_control(m_driver_control, ID_GET_PROCESS_MODULE, PID, XorString(L"UnityPlayer.dll"));
	assemblyModule = call_driver_control(m_driver_control, ID_GET_PROCESS_MODULE, PID, XorString(L"GameAssembly.dll"));

	printf(XorString("PID -> %llx\n"), PID);
	printf(XorString("baseAddress -> %llx\n"), baseAddress);
	printf(XorString("unityModule -> %llx || assemblyModule -> %llx\n"), unityModule, assemblyModule);

	static const auto game_obj_mgr_addr = process::find_signature(unityModule, "\x48\x89\x05\x00\x00\x00\x00\x48\x83\xc4\x38\xc3\x48\xc7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x48\x83\xc4\x38\xc3\xcc\xcc\xcc\xcc\xcc\x48", "xxx????xxxxxxxx????????xxxxxxxxxxx");
	static const auto base_network_addr = process::find_signature(assemblyModule, "\x48\x8b\x05\x00\x00\x00\x00\x48\x8b\x88\x00\x00\x00\x00\x48\x8b\x09\x48\x85\xc9\x74\x00\x45\x33\xc0\x8b", "xxx????xxx????xxxxxxx?xxxx");

	std::cout << XorString("Offset_ObjectManager 0x") << std::hex << game_obj_mgr_addr << std::endl;
	std::cout << XorString("Offset_NetworkManager 0x") << std::hex << base_network_addr << std::endl;

	game_object_manager = read<uintptr_t>(unityModule + game_obj_mgr_addr);
	base_networkable = read<uintptr_t>(assemblyModule + base_network_addr);

	printf(XorString("GameObjM -> 0x%p\n"), game_object_manager);
	printf(XorString("Network -> 0x%p\n"), base_networkable);

	HANDLE top = CreateThread(NULL, 0, entity_thread, NULL, NULL, NULL);
	CloseHandle(top);

	HANDLE top2 = CreateThread(NULL, 0, aim_thread, NULL, NULL, NULL);
	CloseHandle(top2);

	return true;
}

HRESULT DirectXInit(HWND hWnd)
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(3);

	ZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = hWnd;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = Width;
	p_Params.BackBufferHeight = Height;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device)))
	{
		p_Object->Release();
		exit(4);
	}

	ImGui_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImFontConfig font_config;
	font_config.OversampleH = 1;
	font_config.OversampleV = 1;
	font_config.PixelSnapH = true;

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF,
		0x0400, 0x044F,
		0,
	};

	io.Fonts->AddFontFromFileTTF(XorString("C:\\Windows\\Fonts\\Verdana.ttf"), 13.f);

	settings::menu::SkeetFont = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(icon_compressed_data, icon_compressed_size, 15.f, &font_config, ranges);

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(p_Device);

	ImGui::StyleColorsClassic();
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 0.0f;
	style->FramePadding = ImVec2(2, 2);
	style->FrameRounding = 0.0f;
	style->ItemSpacing = ImVec2(8, 8);// ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 0.0f;
	style->GrabMinSize = 10.0f;
	style->GrabRounding = 0.0f;
	style->TabRounding = 0.f;
	style->ChildRounding = 0.f;

	style->Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
	style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImColor(40, 40, 40, 255);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImColor(150, 0, 0, 255);
	style->Colors[ImGuiCol_SliderGrab] = ImColor(40, 40, 40, 255);
	style->Colors[ImGuiCol_SliderGrabActive] = ImColor(60, 60, 60, 255);
	style->Colors[ImGuiCol_Button] = ImColor(40, 40, 40, 255);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);

	style->WindowTitleAlign.x = 0.50f;
	style->FrameRounding = 2.0f;

	p_Object->Release();
	return S_OK;
}

void create_console()
{
	if (!AllocConsole())
	{
		char buffer[1024] = { 0 };
		sprintf_s(buffer, XorString("Failed to AllocConsole( ), GetLastError( ) = %d"), GetLastError());
		MessageBox(HWND_DESKTOP, LPCSTR(buffer), XorString("Error"), MB_OK);

		return;
	}

	auto lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	auto hConHandle = _open_osfhandle(PtrToUlong(lStdHandle), _O_TEXT);
	auto fp = _fdopen(hConHandle, XorString("w"));

	freopen_s(&fp, XorString("CONOUT$"), XorString("w"), stdout);

	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);
}

void SetupWindow()
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);

	WNDCLASSEX wClass =
	{
		sizeof(WNDCLASSEX),
		0,
		WinProc,
		0,
		0,
		nullptr,
		LoadIcon(nullptr, IDI_APPLICATION),
		LoadCursor(nullptr, IDC_ARROW),
		nullptr,
		nullptr,
		opatudobem.c_str(),
		LoadIcon(nullptr, IDI_APPLICATION)
	};

	if (!RegisterClassEx(&wClass))
		exit(1);

	GameWnd = FindWindowW(XorString(L"UnityWndClass"), 0);

	if (GameWnd)
	{
		GetClientRect(GameWnd, &GameRect);
		POINT xy;
		ClientToScreen(GameWnd, &xy);
		GameRect.left = xy.x;
		GameRect.top = xy.y;

		Width = GameRect.right;
		Height = GameRect.bottom;
	}

	MyWnd = CreateWindowExA(WS_EX_TRANSPARENT | WS_EX_NOACTIVATE, opatudobem.c_str(), vsf.c_str(), WS_POPUP | WS_VISIBLE, GameRect.left, GameRect.top, Width, Height, NULL, NULL, 0, NULL);
	DwmExtendFrameIntoClientArea(MyWnd, &Margin);
	SetWindowLong(MyWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	//SetWindowDisplayAffinity(MyWnd, WDA_MONITOR);
	ShowWindow(MyWnd, SW_SHOW);
	UpdateWindow(MyWnd);
}

void background()
{
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Once);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.09f, 0.09f, 0.09f, 0.40f / 1.f * 2.f));
	static const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove;
	ImGui::Begin(XorString("##background"), nullptr, flags);
	ImGui::End();
	ImGui::PopStyleColor();
}

void render() {

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	draw_things();

	if (settings::menu::menu_key) {
		background();
		draw_abigsquare();
		ImGui::GetIO().MouseDrawCursor = 1;
	}
	else
	{
		ImGui::GetIO().MouseDrawCursor = 0;
	}

	ImGui::EndFrame();
	p_Device->SetRenderState(D3DRS_ZENABLE, false);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	p_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	if (p_Device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		p_Device->EndScene();
	}
	HRESULT result = p_Device->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		p_Device->Reset(&p_Params);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}


std::string random_string()
{
	std::string str(XorString("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"));

	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(str.begin(), str.end(), generator);

	return str.substr(0, 27);    // assumes 32 < number of characters in str         
}

std::string RandomString(int len)
{
	srand(time(0));
	std::string str = (XorString("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"));
	std::string newstr;
	int pos;
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}

std::string Random_String(int len)
{
	srand(time(0));
	std::string str = (XorString("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"));
	std::string newstr;
	int pos;
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	create_console();
	HWND ConsWind = GetConsoleWindow();
	comcalma = random_string();
	opatudobem = RandomString(17);
	vsf = Random_String(21);
	SetConsoleTitle(comcalma.c_str());

	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int col = 12;
	SetConsoleTextAttribute(hConsole, 9);

	settings::Load_Settings(XorString("C:\\Rust-Default.ini"));
	while (TRUE)
	{
		if (!initialize())
		{
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << XorString("[+] Waiting for the game open") << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(4));
			continue;
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << XorString("[+] Game Found!") << std::endl;
			SetupWindow();
			DirectXInit(MyWnd);
			MainLoop();
		}
	}

	return 0;
}

WPARAM MainLoop()
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, MyWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();
		if (GetAsyncKeyState(0x23) & 1)
			exit(8);

		if (hwnd_active == GameWnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(MyWnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(GameWnd, &rc);
		ClientToScreen(GameWnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = GameWnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{

			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			p_Params.BackBufferWidth = Width;
			p_Params.BackBufferHeight = Height;
			SetWindowPos(MyWnd, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}
		render();

	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanuoD3D();
	DestroyWindow(MyWnd);

	return Message.wParam;
}
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message)
	{
	case WM_DESTROY:
		CleanuoD3D();
		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (p_Device != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			p_Params.BackBufferWidth = LOWORD(lParam);
			p_Params.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = p_Device->Reset(&p_Params);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}
void CleanuoD3D()
{
	if (p_Device != NULL)
	{
		p_Device->EndScene();
		p_Device->Release();
	}
	if (p_Object != NULL)
	{
		p_Object->Release();
	}
}
int isTopwin()
{
	HWND hWnd = GetForegroundWindow();
	if (hWnd == GameWnd)
		return TopWindowGame;
	if (hWnd == MyWnd)
		return TopWindowMvoe;

	return 0;
}
void SetWindowToTarget()
{
	while (true)
	{
		GameWnd = FindWindowW(XorString(L"UnityWndClass"), 0);

		if (!GameWnd)
			continue;
		else
		{
			ZeroMemory(&GameRect, sizeof(GameRect));
			GetWindowRect(GameWnd, &GameRect);
			Width = GameRect.right - GameRect.left;
			Height = GameRect.bottom - GameRect.top;
			DWORD dwStyle = GetWindowLong(GameWnd, GWL_STYLE);
			if (dwStyle & WS_BORDER)
			{
				GameRect.top += 32;
				Height -= 39;
			}
			ScreenCenterX = Width / 2;
			ScreenCenterY = Height / 2;
			MoveWindow(MyWnd, GameRect.left, GameRect.top, Width, Height, true);
		}
	}
}
