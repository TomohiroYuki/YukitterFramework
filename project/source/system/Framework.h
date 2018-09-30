#pragma once
#include <wrl.h>
#include <memory>
#include <d3d11.h>
#include "source\game\scene\SceneMain.h"
#include "source\game\scene\SceneTitle.h"
#include "source\game\scene\SceneZero.h"
#include "source\game\GameBrain.h"
#include "source\system\sound\sound.h"
#pragma comment(lib,"d3d11.lib")

class Framework
{
public:
	Framework(HWND hwnd):hwnd(hwnd){}
	~Framework() {}
private:
	const HWND hwnd;
	std::unique_ptr<Scene> scene;
public:

	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;

	static Microsoft::WRL::ComPtr<ID3D11Device>				device;
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>		device_context;
	static Microsoft::WRL::ComPtr<IDXGISwapChain>			swapchain;
	static Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	render_target_view;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>			depth_stencil_view;

	int MainLoop()
	{

		MSG msg = {};

		if (!Initialize()) return false;
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
			
				Update();
				Render();
			}
		}
		swapchain->SetFullscreenState(false, NULL);

		return static_cast<int>(msg.wParam);
	}


	bool Initialize()
	{
		// デバイスとスワップチェーンの作成
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;        
		sd.BufferDesc.Width = SCREEN_WIDTH; 
		sd.BufferDesc.Height = SCREEN_HEIGHT;   
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
		sd.BufferDesc.RefreshRate.Numerator = 60;   
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hwnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		D3D_FEATURE_LEVEL  feature_level = D3D_FEATURE_LEVEL_11_0;

		UINT create_device_flags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
		create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, create_device_flags,
			&feature_level, 1, D3D11_SDK_VERSION, &sd, swapchain.GetAddressOf(), device.GetAddressOf(), NULL, device_context.GetAddressOf())))
		{
			return 0;
		}

		Microsoft::WRL::ComPtr<ID3D11Texture2D>		back_buffer;
		HRESULT hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)back_buffer.GetAddressOf());

		if (FAILED(hr))
			return 0;

		hr = device->CreateRenderTargetView(back_buffer.Get(), NULL, render_target_view.GetAddressOf());

		if (FAILED(hr))
			return 0;

		Microsoft::WRL::ComPtr<ID3D11Texture2D>		depth_stencil;

		//深度/ステンシルテクスチャの作成
		D3D11_TEXTURE2D_DESC dep_desc;
		dep_desc.Width = Framework::SCREEN_WIDTH;
		dep_desc.Height = Framework::SCREEN_HEIGHT;
		dep_desc.MipLevels = 1;
		dep_desc.ArraySize = 1;
		dep_desc.Format = DXGI_FORMAT_D32_FLOAT;
		dep_desc.SampleDesc.Count = 1;
		dep_desc.SampleDesc.Quality = 0;
		dep_desc.Usage = D3D11_USAGE_DEFAULT;
		dep_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		dep_desc.CPUAccessFlags = 0;
		dep_desc.MiscFlags = 0;

		hr = device->CreateTexture2D(&dep_desc, NULL, depth_stencil.GetAddressOf());
		if (FAILED(hr))return false;

		//深度/ステンシルビューの作成
		D3D11_DEPTH_STENCIL_VIEW_DESC dep_ste_desc;
		dep_ste_desc.Format = dep_desc.Format;
		dep_ste_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dep_ste_desc.Flags = 0;
		dep_ste_desc.Texture2D.MipSlice = 0;
		hr = device->CreateDepthStencilView(depth_stencil.Get(), &dep_ste_desc, depth_stencil_view.GetAddressOf());


		InputBrain::getInstance()->Initialize(hwnd);

		SoundBrain::getInstance()->Initialize(hwnd);
		GameBrain::GetInstance()->Initialize();

		SoundBrain::getInstance()->LoadSound(L"DATA\\Sound\\bgm_maoudamashii_cyber41.wav", 0);
		SoundBrain::getInstance()->LoadSound(L"DATA\\Sound\\bubble_boss_break.wav", 1);
		SoundBrain::getInstance()->LoadSound(L"DATA\\Sound\\sen_ge_harisen01.wav", 2);
		


		SoundBrain::getInstance()->BGM_Play(0);
		return true;
	}

	bool Update()
	{
		InputBrain::getInstance()->UpData();
		GameBrain::GetInstance()->scene->Update();
		return true;
	}

	void Render()
	{
		D3D11_VIEWPORT vp;
		vp.Width = SCREEN_WIDTH;
		vp.Height = SCREEN_HEIGHT;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		device_context->RSSetViewports(1, &vp);
		float ClearColor[4] = { 0.2f,0.2f,0.2f,1.0f }; //消去色
		device_context->ClearRenderTargetView(render_target_view.Get(), ClearColor);
		device_context->ClearDepthStencilView(depth_stencil_view.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		device_context->OMSetRenderTargets(1, render_target_view.GetAddressOf(), depth_stencil_view.Get());

		GameBrain::GetInstance()->scene->Render(1.0f/60.0f);

		swapchain->Present(1, 0);
	}
};