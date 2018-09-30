#include <Windows.h>
#include <crtdbg.h>
#include "source\system\Framework.h"
#include "source\game\scene\Scene.h"

//#pragma warning( disable : 4099)

DirectX::XMMATRIX Scene::projection_mat;

//_____________________________________________________________________________
Microsoft::WRL::ComPtr<ID3D11Device>			Framework::device;
Microsoft::WRL::ComPtr<ID3D11DeviceContext>		Framework::device_context;
Microsoft::WRL::ComPtr<IDXGISwapChain>			Framework::swapchain;
Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	Framework::render_target_view;
//______________________________________________________________________________


LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		if (wparam == VK_ESCAPE)
		{
			PostMessage(hwnd, WM_CLOSE, 0, 0);
		}
	 return 0;
	 break;
	default:
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}


INT WINAPI wWinMain(HINSTANCE instance, HINSTANCE prev_instance, LPWSTR cmd_line, INT cmd_show)
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(924);
#endif
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = instance;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"I am not Yukitter";
	wcex.hIconSm = 0;
	RegisterClassEx(&wcex);

	RECT rc = { 0, 0, Framework::SCREEN_WIDTH, Framework::SCREEN_HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	HWND hwnd = CreateWindow(L"I am not Yukitter", L"I am not Yukitter", WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, instance, NULL);
	ShowWindow(hwnd, cmd_show);

	Framework f(hwnd);
	//SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&f));
	
	f.MainLoop();
	return 0;
}
