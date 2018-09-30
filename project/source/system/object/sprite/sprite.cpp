#include "source\math\yuki_math.h"
#include "Sprite.h"
#include <d3dcompiler.h>
#include "source\system\DXTex\DirectXTex.h"
#include "source\system\DXTex\WICTextureLoader.h"
//#include "source\Game\GameBrain.h"
#include "source\system\Framework.h"
#include "source\system\ResourceBrain.h"

#pragma comment(lib,"d3dcompiler.lib")
#if _DEBUG
#pragma comment(lib,"lib\\debug\\DirectXTexD.lib")
#else
#pragma comment(lib,"lib\\release\\DirectXTexR.lib")
#endif

vertex vertexies[] = {
	{ DirectX::XMFLOAT4(-0.5f,+0.5f,0,1.0f),DirectX::XMFLOAT4(1,1,1,1),DirectX::XMFLOAT2(0.0f,0.0f) },
	{ DirectX::XMFLOAT4(+0.5f,+0.5f,0,1.0f),DirectX::XMFLOAT4(1,0,0,1),DirectX::XMFLOAT2(1.0f,0.0f) },
	{ DirectX::XMFLOAT4(-0.5f,-0.5f,0,1.0f),DirectX::XMFLOAT4(1,1,0,1),DirectX::XMFLOAT2(1.0f,1.0f) },
	{ DirectX::XMFLOAT4(+0.5f,-0.5f,0,1.0f),DirectX::XMFLOAT4(1,0,1,1),DirectX::XMFLOAT2(0.0f,1.0f) }
};


Sprite::Sprite(const wchar_t* file_string)
{

	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	//		vertex buffer
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	buffer_desc.ByteWidth = sizeof(vertex) * 4;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = sizeof(DirectX::XMFLOAT4);



	//頂点バッファ①のサブリソースの定義
	D3D11_SUBRESOURCE_DATA xyzSubData;
	xyzSubData.pSysMem = vertexies;
	xyzSubData.SysMemPitch = 0;
	xyzSubData.SysMemSlicePitch = 0;

	//頂点バッファ①の作成
	HRESULT hr = Framework::device->CreateBuffer(&buffer_desc, &xyzSubData, buffer.GetAddressOf());
	if (FAILED(hr))
		return;


	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "COLOR"	,0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	ID3DBlob* pBlobVS;

	if (RESOURCE_BRAIN->searchVS(file_string))
	{
		VSandInputLayout vs_input_l = RESOURCE_BRAIN->GetVSFromR_MGR(file_string);
		if (!vs_input_l.input_layout)MessageBox(nullptr, L"error", L"error", MB_OK | MB_ICONERROR);
		vertex_shader = vs_input_l.vs;
		input_layout = vs_input_l.input_layout;

	}
	else {

		hr = D3DCompileFromFile(L"shader\\sprite_vs.hlsl", NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
			"vs_5_0", 0, 0, &pBlobVS, NULL);

		if (FAILED(hr))return;


		hr = Framework::device->CreateVertexShader(pBlobVS->GetBufferPointer(),
			pBlobVS->GetBufferSize(), NULL, vertex_shader.GetAddressOf());

		if (FAILED(hr))
			return;

		hr = Framework::device->CreateInputLayout(layout, _countof(layout), pBlobVS->GetBufferPointer(),
			pBlobVS->GetBufferSize(), input_layout.GetAddressOf());
		if (FAILED(hr))return;

		char path[256];
		size_t size = {};
		wcstombs_s(&size, path, file_string, 256);
		RESOURCE_BRAIN->vertex_shader_map.insert(std::make_pair(path, VSandInputLayout(vertex_shader, input_layout)));

		pBlobVS->Release();


	}








	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	//		pixel shader
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

	ID3DBlob* pBlobPS;
	if (RESOURCE_BRAIN->searchPS(file_string))
	{
		pixel_shader = RESOURCE_BRAIN->GetPSFromR_MGR(file_string);
	}
	else {
		hr = D3DCompileFromFile(L"shader\\sprite_ps.hlsl", NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
			"ps_5_0", 0, 0, &pBlobPS, NULL);
		if (FAILED(hr))return;


		hr = Framework::device->CreatePixelShader(pBlobPS->GetBufferPointer(),
			pBlobPS->GetBufferSize(), NULL, pixel_shader.GetAddressOf());
		if (FAILED(hr))return;

		char path[256];
		size_t size = {};
		wcstombs_s(&size, path, file_string, 256);
		RESOURCE_BRAIN->pixel_shader_map.insert(std::make_pair(path, pixel_shader));



		pBlobPS->Release();
	}


	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

	D3D11_RASTERIZER_DESC RSDesc;
	RSDesc.FillMode = D3D11_FILL_SOLID;
	RSDesc.CullMode = D3D11_CULL_NONE;
	RSDesc.FrontCounterClockwise = FALSE;
	RSDesc.DepthBias = 0;
	RSDesc.DepthBiasClamp = 0;
	RSDesc.SlopeScaledDepthBias = 0;
	RSDesc.DepthClipEnable = FALSE;
	RSDesc.ScissorEnable = FALSE;
	RSDesc.MultisampleEnable = FALSE;
	RSDesc.AntialiasedLineEnable = FALSE;

	hr = Framework::device->CreateRasterizerState(&RSDesc, rasterizer_state.GetAddressOf());
	if (FAILED(hr))return;



	DirectX::TexMetadata metadata;
	DirectX::ScratchImage image;

	if (RESOURCE_BRAIN->searchShaderResourceView(file_string))
	{
		//shader_resourceview = RESOURCE_BRAIN->GetSRVanTexFromR_MGR(file_string);
		SRVandTexture& srv_and_tex = RESOURCE_BRAIN->GetSRVanTexFromR_MGR(file_string);
		//metadata= *srv_and_tex.metadata;
		//image= srv_and_tex.image;

		shader_resourceview = srv_and_tex.srv;
		tex_size = srv_and_tex.texsize;
	}
	else {
		hr = DirectX::LoadFromWICFile(file_string, 0, &metadata, image);
		tex_size.x = static_cast<float>(metadata.width);
		tex_size.y = static_cast<float>(metadata.height);
		if (FAILED(hr))
		{
			return;
		}
		hr = DirectX::CreateShaderResourceView(Framework::device.Get(), image.GetImages(), image.GetImageCount(), metadata, &shader_resourceview);
		if (FAILED(hr))
		{
			return;
		}
		char path[256];
		size_t size = {};
		wcstombs_s(&size, path, file_string, 256);
		RESOURCE_BRAIN->srv_and_tex_map.insert(std::make_pair(path, SRVandTexture(tex_size/*&metadata,*/, shader_resourceview.Get())));
	}


	//ID3D11Texture2D* pResolveTexture = nullptr;
	//if (RESOURCE_BRAIN->searchTecture(file_string))
	//{
	//	pResolveTexture = RESOURCE_BRAIN->GetTextureFromR_MGR(file_string);
	//}
	//else {

	//	ZeroMemory(&texture_desc, sizeof(texture_desc));
	//	texture_desc.ArraySize = 1;
	//	texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	//	texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//	texture_desc.SampleDesc.Count = 1;
	//	texture_desc.SampleDesc.Quality = 0;
	//	texture_desc.Width = 256;
	//	texture_desc.Height = 256;
	//	texture_desc.Usage = D3D11_USAGE_DEFAULT;
	//	texture_desc.MipLevels = 1;


	//	Framework::device->CreateTexture2D(&texture_desc, NULL, &pResolveTexture);

	//	RESOURCE_BRAIN->texture_map.insert(std::make_pair(file_string, pResolveTexture));



	//	

	//	Framework::device->CreateDepthStencilState(nullptr, nullptr);

	//	pResolveTexture->Release();
	//}


	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	hr = Framework::device->CreateSamplerState(&samplerDesc, sampler_state.GetAddressOf());
	if (FAILED(hr))
	{
		return;
	}



	//深度/ステンシル・ステートオブジェクトの作成
	D3D11_DEPTH_STENCIL_DESC DepthStencil;
	DepthStencil.DepthEnable = FALSE;
	DepthStencil.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthStencil.DepthFunc = D3D11_COMPARISON_LESS;
	DepthStencil.StencilEnable = NULL;
	DepthStencil.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	DepthStencil.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	//面が表を向いてるときのステンシルテストの設定
	DepthStencil.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStencil.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStencil.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthStencil.FrontFace.StencilFunc = D3D11_COMPARISON_NEVER;

	//面が裏を向いてるときのステンシルテストの設定

	DepthStencil.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStencil.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStencil.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthStencil.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	hr = Framework::device->CreateDepthStencilState(&DepthStencil, depth_stencil_state.GetAddressOf());
	if (FAILED(hr))return;



	//D3D11_BLEND_DESC BlendState;
	//
	////ブレンドステートオブジェクトの作成
	//ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
	//
	//BlendState.AlphaToCoverageEnable = TRUE;
	//BlendState.IndependentBlendEnable = FALSE;
	//BlendState.RenderTarget[0].BlendEnable = FALSE;
	//BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	//hr = Framework::device->CreateBlendState(&BlendState, &blend_state);
	//if (FAILED(hr))return;








	D3D11_BLEND_DESC desc = {};
	desc.AlphaToCoverageEnable = false;  //αカバレッジ
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	//desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	//desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	hr = Framework::device->CreateBlendState(&desc, &blend_state);
	if (FAILED(hr))return;
}


void Sprite::Render(VECTORII pos, VECTORII size, VECTORII tpos, VECTORII tsize)
{
	//UINT stride = sizeof(vertex);
	//UINT offset = 0;
	//
	//D3D11_VIEWPORT viewport;
	//UINT num_viewports = 1;
	//Framework::device_context->RSGetViewports(&num_viewports, &viewport);
	//
	//Framework::device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//Framework::device_context->IASetInputLayout(input_layout.Get());
	//Framework::device_context->RSSetState(rasterizer_state.Get());
	//Framework::device_context->VSSetShader(vertex_shader.Get(), nullptr, 0);
	//Framework::device_context->PSSetShader(pixel_shader.Get(), nullptr, 0);
	//Framework::device_context->PSSetShaderResources(0, 1, shader_resourceview.GetAddressOf());
	//Framework::device_context->PSSetSamplers(0, 1, sampler_state.GetAddressOf());
	//
	//D3D11_MAP map = D3D11_MAP_WRITE_DISCARD;
	//D3D11_MAPPED_SUBRESOURCE mapped_buffer;
	//HRESULT hr = Framework::device_context->Map(buffer.Get(), 0, map, 0, &mapped_buffer);
	////_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
	//auto vertices = static_cast<vertex *>(mapped_buffer.pData);
	//
	//FLOAT w = 2.0f / viewport.Width;
	//FLOAT h = -2.0f / viewport.Height;
	//vertices[0].position.x = w - 1.0f;
	//vertices[0].position.y = h + 1.0f;
	//vertices[0].texcoord.x = static_cast<FLOAT>(tpos.x) / tex_size.x;
	//vertices[0].texcoord.y = static_cast<FLOAT>(tpos.y) / tex_size.y;
	//vertices[1].position.x = w*size.x*c + w*(-rpos.x*c + -rpos.y*-s + rpos.x + pos.x) - 1.0f;
	//vertices[1].position.y = w*size.y*-s + h*(-rpos.x*s + -rpos.y*c + rpos.y + pos.y) + 1.0f;
	//vertices[1].texcoord.x = static_cast<FLOAT>(tpos.x + tsize.x) / tex_size.x;
	//vertices[1].texcoord.y = static_cast<FLOAT>(tpos.y) / tex_size.y;
	//vertices[2].position.x = h*size.x*s + w*(-rpos.x*c + -rpos.y*-s + rpos.x + pos.x) - 1.0f;
	//vertices[2].position.y = h*size.y*c + h*(-rpos.x*s + -rpos.y*c + rpos.y + pos.y) + 1.0f;
	//vertices[2].texcoord.x = static_cast<FLOAT>(tpos.x) / tex_size.x;
	//vertices[2].texcoord.y = static_cast<FLOAT>(tpos.y + tsize.y) / tex_size.y;
	//vertices[3].position.x = w*size.x*c + h*size.x*s + w*(-rpos.x*c + -rpos.y*-s + rpos.x + pos.x) - 1.0f;
	//vertices[3].position.y = w*size.y*-s + h*size.y*c + h*(-rpos.x*s + -rpos.y*c + rpos.y + pos.y) + 1.0f;
	//vertices[3].texcoord.x = static_cast<FLOAT>(tpos.x + tsize.x) / tex_size.x;
	//vertices[3].texcoord.y = static_cast<FLOAT>(tpos.y + tsize.y) / tex_size.y;
	//for (int i = 0; i < 4; i++)
	//{
	//	vertices[i].position.z = .0f;
	//	vertices[i].position.w = 1.0f;
	//}
	//Framework::device_context->Unmap(buffer.Get(), 0);
	//Framework::device_context->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &stride, &offset);
	//
	//
	//Framework::device_context->RSSetState(rasterizer_state.Get());
	//FLOAT blend_factor[4] = { 1.0f,0.0f,0.0f,0.0f };
	//Framework::device_context->OMSetBlendState(blend_state.Get(), blend_factor, 0xFFFFFFFF);
	////g_pImmediateContext->OMSetBlendState(g_pBlendState, BlendFactor, 0xFFFFFF);
	//
	//Framework::device_context->OMSetDepthStencilState(depth_stencil_state.Get(), 0);
	//
	//Framework::device_context->Draw(4, 0);
	////// Resolve
	////pImmediateContext->ResolveSubresource(
	////	pResolveTexture, 0, pRenderTexture, 0,
	////	DXGI_FORMAT_R8G8B8A8_UNORM);
	//


}



void Sprite::Render(VECTORII pos, VECTORII size, VECTORII tpos, VECTORII tsize, VECTORII rpos, float angle)
{
	UINT stride = sizeof(vertex);
	UINT offset = 0;

	D3D11_VIEWPORT viewport;
	UINT num_viewports = 1;
	Framework::device_context->RSGetViewports(&num_viewports, &viewport);

	Framework::device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	Framework::device_context->IASetInputLayout(input_layout.Get());
	//Framework::device_context->OMSetDepthStencilState(depth_stencil_state.Get(), 1);
	//Framework::device_context->OMSetBlendState(blend_state.Get(), nullptr, 0xFFFFFFFF);
	Framework::device_context->RSSetState(rasterizer_state.Get());
	Framework::device_context->VSSetShader(vertex_shader.Get(), nullptr, 0);
	Framework::device_context->PSSetShader(pixel_shader.Get(), nullptr, 0);
	Framework::device_context->PSSetShaderResources(0, 1, shader_resourceview.GetAddressOf());
	Framework::device_context->PSSetSamplers(0, 1, sampler_state.GetAddressOf());

	D3D11_MAP map = D3D11_MAP_WRITE_DISCARD;
	D3D11_MAPPED_SUBRESOURCE mapped_buffer;
	HRESULT hr = Framework::device_context->Map(buffer.Get(), 0, map, 0, &mapped_buffer);
	//_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
	auto vertices = static_cast<vertex *>(mapped_buffer.pData);
	FLOAT c = cosf(angle*0.01745f);
	FLOAT s = sinf(angle*0.01745f);
	FLOAT w = 2.0f / viewport.Width;
	FLOAT h = -2.0f / viewport.Height;

	vertices[0].texcoord.x = static_cast<FLOAT>(tpos.x) / tex_size.x;
	vertices[0].texcoord.y = static_cast<FLOAT>(tpos.y) / tex_size.y;
	vertices[1].texcoord.x = static_cast<FLOAT>(tpos.x + tsize.x) / tex_size.x;
	vertices[1].texcoord.y = static_cast<FLOAT>(tpos.y) / tex_size.y;
	vertices[2].texcoord.x = static_cast<FLOAT>(tpos.x) / tex_size.x;
	vertices[2].texcoord.y = static_cast<FLOAT>(tpos.y + tsize.y) / tex_size.y;
	vertices[3].texcoord.x = static_cast<FLOAT>(tpos.x + tsize.x) / tex_size.x;
	vertices[3].texcoord.y = static_cast<FLOAT>(tpos.y + tsize.y) / tex_size.y;

	//頂点設定
	float x[4] = { 0 }, y[4] = { 0 };
	x[0] = pos.x, y[0] = pos.y;								//左上の頂点設定
	x[1] = pos.x + size.x, y[1] = pos.y;					//右上の頂点設定
	x[2] = pos.x, y[2] = pos.y + size.y;					//左下の頂点設定
	x[3] = pos.x + size.x, y[3] = pos.y + size.y;			//右下の頂点設定

											//スプライトの中心点設定
	float mx = pos.x + rpos.x, my = pos.y + rpos.y;
	for (int num = 0; num < 4; num++)
	{
		x[num] -= mx;
		y[num] -= my;
	}

	//回転描画の設定
	for (int num = 0; num < 4; num++)
	{
		float rx = x[num], ry = y[num];
		x[num] = rx*cosf(angle) + ry * (-sinf(angle));
		y[num] = rx* sinf(angle) + ry*cosf(angle);
	}

	for (int num = 0; num < 4; num++)
	{
		x[num] += mx;
		y[num] += my;
	}

	//NDC座標軸に変換
	for (int num = 0; num < 4; num++)
	{
		x[num] = 2.0f*x[num] / Framework::SCREEN_WIDTH - 1.0f;
		y[num] = 1.0f - 2.0f*y[num] / Framework::SCREEN_HEIGHT;
	}



	for (int i = 0; i < 4; i++)
	{

		vertices[i].position = DirectX::XMFLOAT4(x[i], y[i], 0, 1.0f);
		vertices[i].color.x = 1.0f;//color.x;
		vertices[i].color.y = 1.0f;//color.y;
		vertices[i].color.z = 1.0f;//color.z;
		vertices[i].color.w = 1.0f;// color.w;
	}
	Framework::device_context->Unmap(buffer.Get(), 0);
	Framework::device_context->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &stride, &offset);


	Framework::device_context->RSSetState(rasterizer_state.Get());
	FLOAT blend_factor[4] = { 1.0f,0.0f,0.0f,0.0f };
	Framework::device_context->OMSetBlendState(blend_state.Get(), blend_factor, 0xFFFFFFFF);
	Framework::device_context->OMSetDepthStencilState(depth_stencil_state.Get(), 0);

	Framework::device_context->Draw(4, 0);
	
}

void Sprite::Render(VECTORII pos, VECTORII size, VECTORII tpos, VECTORII tsize, VECTORII rpos, float angle, VECTORIV color)
{
	UINT stride = sizeof(vertex);
	UINT offset = 0;

	D3D11_VIEWPORT viewport;
	UINT num_viewports = 1;
	Framework::device_context->RSGetViewports(&num_viewports, &viewport);

	Framework::device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	Framework::device_context->IASetInputLayout(input_layout.Get());
	//Framework::device_context->OMSetDepthStencilState(depth_stencil_state.Get(), 1);
	//Framework::device_context->OMSetBlendState(blend_state.Get(), nullptr, 0xFFFFFFFF);
	Framework::device_context->RSSetState(rasterizer_state.Get());
	Framework::device_context->VSSetShader(vertex_shader.Get(), nullptr, 0);
	Framework::device_context->PSSetShader(pixel_shader.Get(), nullptr, 0);
	Framework::device_context->PSSetShaderResources(0, 1, shader_resourceview.GetAddressOf());
	Framework::device_context->PSSetSamplers(0, 1, sampler_state.GetAddressOf());

	D3D11_MAP map = D3D11_MAP_WRITE_DISCARD;
	D3D11_MAPPED_SUBRESOURCE mapped_buffer;
	HRESULT hr = Framework::device_context->Map(buffer.Get(), 0, map, 0, &mapped_buffer);
	//_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
	auto vertices = static_cast<vertex *>(mapped_buffer.pData);
	FLOAT c = cosf(angle/**0.01745f*/);
	FLOAT s = sinf(angle/**0.01745f*/);
	FLOAT w = 2.0f / viewport.Width;
	FLOAT h = -2.0f / viewport.Height;

	static float a = 1;
	static float aaa = .0f;
	a += sinf(aaa += 0.2f);
	vertices[0].position.x = w*(-rpos.x*c + -rpos.y*-s + rpos.x + pos.x) - 1.0f;
	vertices[0].position.y = h*(-rpos.x*s + -rpos.y*c + rpos.y + pos.y) + 1.0f;
	vertices[0].texcoord.x = static_cast<FLOAT>(tpos.x) / tex_size.x;
	vertices[0].texcoord.y = static_cast<FLOAT>(tpos.y) / tex_size.y;
	/*vertices[1].position.x = w*size.x*c + w*(-rpos.x*c + -rpos.y*-s + rpos.x + pos.x) - 1.0f;
	vertices[1].position.y = w*size.y*-s + h*(-rpos.x*s + -rpos.y*c + rpos.y + pos.y) + 1.0f;*/
	//eleven
	vertices[1].position.x = w*size.x*c + w*(-rpos.x*c + -rpos.y*-s + rpos.x + pos.x) - 1.0f;
	vertices[1].position.y = w*size.y*-s + h*(-rpos.x*s + -rpos.y*c + rpos.y + pos.y) + 1.0f;
	//

	vertices[1].texcoord.x = static_cast<FLOAT>(tpos.x + tsize.x) / tex_size.x;
	vertices[1].texcoord.y = static_cast<FLOAT>(tpos.y) / tex_size.y;
	vertices[2].position.x = h*size.x*s + w*(-rpos.x*c + -rpos.y*-s + rpos.x + pos.x) - 1.0f;
	vertices[2].position.y = h*size.y*c + h*(-rpos.x*s + -rpos.y*c + rpos.y + pos.y) + 1.0f;
	vertices[2].texcoord.x = static_cast<FLOAT>(tpos.x) / tex_size.x;
	vertices[2].texcoord.y = static_cast<FLOAT>(tpos.y + tsize.y) / tex_size.y;
	vertices[3].position.x = w*size.x*c + h*size.x*s + w*(-rpos.x*c + -rpos.y*-s + rpos.x + pos.x) - 1.0f;
	vertices[3].position.y = w*size.y*-s + h*size.y*c + h*(-rpos.x*s + -rpos.y*c + rpos.y + pos.y) + 1.0f;
	vertices[3].texcoord.x = static_cast<FLOAT>(tpos.x + tsize.x) / tex_size.x;
	vertices[3].texcoord.y = static_cast<FLOAT>(tpos.y + tsize.y) / tex_size.y;
	for (int i = 0; i < 4; i++)
	{
		vertices[i].position.z = .0f;
		vertices[i].position.w = 1.0f;
		//vertices[i].color.w = color;
		vertices[i].color.x = 1.0f;//color.x;
		vertices[i].color.y = 1.0f;//color.y;
		vertices[i].color.z = 1.0f;//color.z;
		vertices[i].color.w = color.w;// color.w;
	}

	Framework::device_context->Unmap(buffer.Get(), 0);
	Framework::device_context->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &stride, &offset);


	Framework::device_context->RSSetState(rasterizer_state.Get());
	FLOAT blend_factor[4] = { 1.0f,0.0f,0.0f,0.0f };
	Framework::device_context->OMSetBlendState(blend_state.Get(), blend_factor, 0xFFFFFFFF);
	//g_pImmediateContext->OMSetBlendState(g_pBlendState, BlendFactor, 0xFFFFFF);

	Framework::device_context->OMSetDepthStencilState(depth_stencil_state.Get(), 0);

	Framework::device_context->Draw(4, 0);
	
}
