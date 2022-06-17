#include "Overlay.hpp"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui_internal.h"
#include "FontData.hpp"

#include <d3d9.h>
#include <dinput.h>
#include <tchar.h>
#include <dwmapi.h>
#include "Menu/menu.hh"

#include "../fonts/FontAwesome.h"
#include "../fonts/RudaBolt.h"
#include "../globals.h"

#define DIRECTINPUT_VERSION 0x0800

static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool toggle = false;

void Overlay::Style(ImGuiStyle& style)
{
	style.WindowPadding = ImVec2(0, 0);
	style.FramePadding = ImVec2(4, 3);
	style.ItemSpacing = ImVec2(8, 4);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.IndentSpacing = 21;
	style.ScrollbarSize = 1;
	style.GrabMinSize = 1;
	style.WindowBorderSize = 0;
	style.ChildBorderSize = 1;
	style.PopupBorderSize = 0;
	style.FrameBorderSize = 1;
	style.WindowRounding = 0;
	style.ChildRounding = 0;
	style.FrameRounding = 0;
	style.PopupRounding = 0;
	style.ScrollbarRounding = 0;
	style.GrabRounding = 0;
	style.SelectableTextAlign = ImVec2(0.5f, 0.5f);

	style.Colors[ImGuiCol_Text] = ImVec4(0.900000f, 0.900000f, 0.900000f, 1.000000f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.600000f, 0.600000f, 0.600000f, 1.000000f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.078431f, 0.078431f, 0.090196f, 1.000000f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.000000f, 0.000000f, 0.000000f, 0.000000f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.110000f, 0.110000f, 0.140000f, 0.920000f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.500000f, 0.500000f, 0.500000f, 0.500000f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.000000f, 0.000000f, 0.000000f, 0.000000f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.430000f, 0.430000f, 0.430000f, 0.390000f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.470000f, 0.470000f, 0.690000f, 0.400000f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.420000f, 0.410000f, 0.640000f, 0.690000f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.270000f, 0.270000f, 0.540000f, 0.830000f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.320000f, 0.320000f, 0.630000f, 0.870000f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.400000f, 0.400000f, 0.800000f, 0.200000f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.400000f, 0.400000f, 0.550000f, 0.800000f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.200000f, 0.250000f, 0.300000f, 0.600000f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.400000f, 0.400000f, 0.800000f, 0.300000f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.400000f, 0.400000f, 0.800000f, 0.400000f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.410000f, 0.390000f, 0.800000f, 0.600000f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.900000f, 0.900000f, 0.900000f, 0.500000f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.000000f, 1.000000f, 1.000000f, 0.300000f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.410000f, 0.390000f, 0.800000f, 0.600000f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.350000f, 0.400000f, 0.610000f, 0.620000f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.400000f, 0.480000f, 0.710000f, 0.790000f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.460000f, 0.540000f, 0.800000f, 1.000000f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.400000f, 0.400000f, 0.900000f, 0.450000f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.450000f, 0.450000f, 0.900000f, 0.800000f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.530000f, 0.530000f, 0.870000f, 0.800000f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.500000f, 0.500000f, 0.500000f, 0.600000f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.600000f, 0.600000f, 0.700000f, 1.000000f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.700000f, 0.700000f, 0.900000f, 1.000000f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.000000f, 1.000000f, 1.000000f, 0.160000f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.780000f, 0.820000f, 1.000000f, 0.600000f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.780000f, 0.820000f, 1.000000f, 0.900000f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.000000f, 0.000000f, 1.000000f, 0.350000f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.000000f, 1.000000f, 0.000000f, 0.900000f);

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	g_pd3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);

	g_pd3dDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN |
		D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
}


struct Colors
{
	Color Red = D3DCOLOR_RGBA(255, 0, 0, 255);
	Color Orange = D3DCOLOR_RGBA(255, 100, 0, 255);
	Color Yellow = D3DCOLOR_RGBA(255, 255, 0, 255);
	Color Green = D3DCOLOR_RGBA(0, 255, 0, 255);
	Color Turquoise = D3DCOLOR_RGBA(0, 255, 255, 255);
	Color Blue = D3DCOLOR_RGBA(0, 130, 255, 255);
	Color Purple = D3DCOLOR_RGBA(130, 0, 255, 255);
	Color Pink = D3DCOLOR_RGBA(255, 0, 255, 255);
	Color Black = D3DCOLOR_RGBA(0, 0, 0, 255);
	Color Gray = D3DCOLOR_RGBA(69, 69, 69, 255);
	Color White = D3DCOLOR_RGBA(255, 255, 255, 255);
};
Colors ColorClass;


std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

void __fastcall Render::DrawString(int x, int y, const char* str, Color* color)
{
	ImFont a;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), utf_8_2.c_str());
}


void __fastcall Overlay::Loop()
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("OverWolf"), NULL };
	::RegisterClassEx(&wc);
	HWND hwnd = ::CreateWindow(wc.lpszClassName, _T(""), WS_EX_TOPMOST | WS_POPUP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, wc.hInstance, NULL);
	//SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT); // clickable WS_EX_TRANSPARENT
	SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);

	MARGINS margins = { -1 };
	DwmExtendFrameIntoClientArea(hwnd, &margins);

	if (!CreateDeviceD3D(hwnd))
	{
		CleanupDeviceD3D();
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
		return;
	}

	::ShowWindow(hwnd, SW_SHOWDEFAULT);
	::UpdateWindow(hwnd);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	Style(ImGui::GetStyle());

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX9_Init(g_pd3dDevice);

	ImVec4 clear_color = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			continue;
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		{
			//ImGui::Begin(safe_str("main"), (bool*)true, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
			{
				if (globals.auth) {
					start(hwnd);
				}
				else {
					login();
				}
			}
			//ImGui::End();
		}
		PostProcessing::setDevice(g_pd3dDevice);
		PostProcessing::newFrame();
		ImGui::EndFrame();
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

		D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * 255.0f), (int)(clear_color.y * 255.0f), (int)(clear_color.z * 255.0f), (int)(clear_color.w * 255.0f));
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
		if (g_pd3dDevice->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			g_pd3dDevice->EndScene();
		}

		HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

		if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
			ResetDevice();
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanupDeviceD3D();
	::DestroyWindow(hwnd);
	::UnregisterClass(wc.lpszClassName, wc.hInstance);
}

void __fastcall Overlay::start(HWND hwnd) {

	HWND gameWnd = FindWindowA(("UnityWndClass"), ("Rust")); //UnityWndClass
	HWND activeWnd = nullptr;

	activeWnd = GetForegroundWindow();
	if (activeWnd != gameWnd && activeWnd != hwnd) {
		::SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	else {
		::SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}

	RECT screen_rect{};
	GetWindowRect(GetDesktopWindow(), &screen_rect);
	glui::screen_res = ImVec2(float(screen_rect.right), float(screen_rect.bottom));

	//ImGui::StyleColorsvosLight();
	//ImGui::StyleColorsDark();
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(glui::screen_res.x, glui::screen_res.y), ImGuiCond_Always);
	ImGui::Begin(" ", (bool*)true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);

	ESP::Run();

	//Render::DrawString(20, 25, "", &ColorClass.White);
	//Render::DrawString(58, 25, ".", &ColorClass.Pink);
	ImGui::End();

	if (GetKeyState(VK_INSERT) & 0x8000) {  //Menu Key
		Sleep(200);
		toggle = !toggle;
	}

	if (toggle) {
		SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_LAYERED);
		//ImGui::StyleColorsvosLight();
		//ImGui::StyleColorsDark();
		colors[ImGuiCol_WindowBg] = ImVec4(40 / 255.f, 40 / 255.f, 40 / 255.f, 255 / 255.f); //ImVec4(20 / 255.f, 20 / 255.f, 20 / 255.f, 255 / 255.f);
		colors[ImGuiCol_Border] = ImColor(25, 20, 36, 255);
		if (toggle)
			PostProcessing::performFullscreenBlur(ImGui::GetBackgroundDrawList(), 155);
		menu();
	}
	else {
		SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT);
	}

}

bool CreateDeviceD3D(HWND hWnd)
{
	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return false;

	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	g_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
		return false;

	return true;
}

void CleanupDeviceD3D()
{
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
	if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
	PostProcessing::onDeviceReset();
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			ResetDevice();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

/*std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}*/

void __fastcall Render::Line(ImVec2 pos, ImVec2 size, ImU32 color, float thickness)
{
	ImGui::GetWindowDrawList()->AddLine(pos, size, color, thickness);
}

/*void __fastcall Render::DrawString(int x, int y, const char* str, Color* color)
{
	ImFont a;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), utf_8_2.c_str());
}*/

void __fastcall Render::DrawBox(ImVec2 pos, ImVec2 size, ImColor color)
{
	const ImRect rect_bb(pos, pos + size);

	ImGui::GetWindowDrawList()->AddRect(rect_bb.Min - ImVec2(1, 1), rect_bb.Max + ImVec2(1, 1), ImColor(0, 0, 0), 0.0f, 15, 2);
	ImGui::GetWindowDrawList()->AddRect(rect_bb.Min + ImVec2(1, 1), rect_bb.Max - ImVec2(1, 1), ImColor(0, 0, 0), 0.0f, 15, 2);
	ImGui::GetWindowDrawList()->AddRect(rect_bb.Min, rect_bb.Max, color, 0.0f, 15, 2);
}


void __fastcall Render::DrawLootBox(const ImVec2& Start, const ImVec2& End, const ImColor color, float Thickk = 1.5f)
{
	ImGui::GetWindowDrawList()->AddRect(Start, End, color, Thickk);
}

void __fastcall Render::DrawHealthBar(ImVec2 pos, ImVec2 size, ImColor color)
{
	const ImRect rect_bb(pos, pos + size);

	ImGui::GetWindowDrawList()->AddRect(rect_bb.Min - ImVec2(1, 1), rect_bb.Max + ImVec2(1, 1), ImColor(0, 0, 0), 0.0f, 15, 2);
}

void __fastcall Render::DrawFilledBox(ImVec2 pos, ImVec2 size, ImColor color)
{
	const ImRect rect_bb(pos, pos + size);

	ImGui::GetWindowDrawList()->AddRectFilled(rect_bb.Min - ImVec2(1, 1), rect_bb.Max + ImVec2(1, 1), ImColor(0, 0, 0), 0.0f, 15);
	ImGui::GetWindowDrawList()->AddRectFilled(rect_bb.Min + ImVec2(1, 1), rect_bb.Max - ImVec2(1, 1), ImColor(0, 0, 0), 0.0f, 15);
	ImGui::GetWindowDrawList()->AddRectFilled(rect_bb.Min, rect_bb.Max, color, 0.5f, 15);
}


void __fastcall Render::DrawFilledRect(float x, float y, float w, float h, ImVec4 color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), NULL, NULL);
}


void __fastcall Render::DrawHealthbarVertical(float x, float y, float w, float h, float value, float max)
{
	Render::DrawFilledRect(x, y, w, h, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
	if (value <= 225.0f) Render::DrawFilledRect(x, y, w, value / max * h, ImVec4(0.0f, 0.502f, 1.0f, 1.0f)); // player with shield
	if (value <= 100.0f) Render::DrawFilledRect(x, y, w, value / max * h, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)); // health only
}

void __fastcall Render::DrawCornerBox(ImVec2 pos, ImVec2 size, ImColor color)
{
	float line_w = (size.x / 5);
	float line_h = (size.y / 6);
	float line_t = 1;

	{
		// bottom right
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ pos.x - line_t, pos.y - line_t }, ImVec2{ pos.x + line_w, pos.y - line_t }, color, 1.5f);
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ pos.x - line_t, pos.y - line_t }, ImVec2{ pos.x - line_t, pos.y + line_h }, color, 1.5f);

		// bottom left
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ pos.x + size.x - line_w, pos.y - line_t }, ImVec2{ pos.x + size.x + line_t, pos.y - line_t }, color, 1.5f);
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ pos.x + size.x + line_t, pos.y - line_t }, ImVec2{ pos.x + size.x + line_t, pos.y + line_h }, color, 1.5f);

		// top right
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ pos.x - line_t, pos.y + size.y - line_h }, ImVec2{ pos.x - line_t, pos.y + size.y + line_t }, color, 1.5f);
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ pos.x - line_t, pos.y + size.y + line_t }, ImVec2{ pos.x + line_w, pos.y + size.y + line_t }, color, 1.5f);

		// top left
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ pos.x + size.x + line_t, pos.y + size.y - line_h }, ImVec2{ pos.x + size.x + line_t, pos.y + size.y + line_t }, color, 1.5f);
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ pos.x + size.x - line_w, pos.y + size.y + line_t }, ImVec2{ pos.x + size.x + line_t, pos.y + size.y + line_t }, color, 1.5f);
	}

	{
		// bottom right
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ (pos.x + size.x - line_w),  (pos.y + size.y) }, ImVec2{ (pos.x + size.x), (pos.y + size.y) }, ImColor(0, 0, 0), 1.f);
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ (pos.x + size.x),  (pos.y + size.y - line_h) }, ImVec2{ (pos.x + size.x), (pos.y + size.y) }, ImColor(0, 0, 0), 1.f);

		// bottom left
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ (pos.x), (pos.y + size.y - line_h) }, ImVec2{ (pos.x),  (pos.y + size.y) }, ImColor(0, 0, 0), 1.f);
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ (pos.x), (pos.y + size.y) }, ImVec2{ (pos.x + line_w), (pos.y + size.y) }, ImColor(0, 0, 0), 1.f);

		// top right
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ (pos.x + size.x - line_w), (pos.y) }, ImVec2{ (pos.x + size.x), (pos.y) }, ImColor(0, 0, 0), 1.f);
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ (pos.x + size.x), (pos.y) }, ImVec2{ (pos.x + size.x), (pos.y + line_h) }, ImColor(0, 0, 0), 1.f);

		// top left
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ (pos.x), (pos.y) }, ImVec2{ (pos.x), (pos.y + line_h) }, ImColor(0, 0, 0), 1.f);
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ (pos.x), (pos.y) }, ImVec2{ (pos.x + line_w), (pos.y) }, ImColor(0, 0, 0), 1.f);
	}
}
void __fastcall Render::Line2(const ImVec2& Start, const ImVec2& End, const ImColor color, float Thickk = 1.5f)
{
	ImGui::GetWindowDrawList()->AddLine(Start, End, color, Thickk);
}
void __fastcall Render::Text(ImVec2 pos, std::string strText, ImColor color, bool outline, ImFont* font, float fontSize)
{
	ImGuiContext& g = *GImGui;

	const char* text_end = strText.c_str() + strlen(strText.c_str());
	const char* text_display_end = ImGui::FindRenderedTextEnd(strText.c_str(), text_end);

	if (fontSize == 0.f) fontSize = g.Font->FontSize;

	if (outline) {
		ImGui::GetWindowDrawList()->AddText(font, fontSize, pos - ImVec2(1, 0), ImColor(0, 0, 0), strText.c_str(), NULL, 0.0f, NULL);
		ImGui::GetWindowDrawList()->AddText(font, fontSize, pos - ImVec2(0, 1), ImColor(0, 0, 0), strText.c_str(), NULL, 0.0f, NULL);
		ImGui::GetWindowDrawList()->AddText(font, fontSize, pos + ImVec2(1, 0), ImColor(0, 0, 0), strText.c_str(), NULL, 0.0f, NULL);
		ImGui::GetWindowDrawList()->AddText(font, fontSize, pos + ImVec2(0, 1), ImColor(0, 0, 0), strText.c_str(), NULL, 0.0f, NULL);
	}

	ImGui::GetWindowDrawList()->AddText(font, fontSize, pos, color, strText.c_str(), NULL, 0.0f, NULL);
}

void __fastcall Render::Circle(ImVec2 point, float radius, ImColor color)
{
	ImGui::GetWindowDrawList()->AddCircle(point, radius, color, 50, 0.5);
}

ImU32 __fastcall Render::FtIM(float* color) {
	return ImGui::ColorConvertFloat4ToU32(ImVec4(color[0], color[1], color[2], color[3]));
}