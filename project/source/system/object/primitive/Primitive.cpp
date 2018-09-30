#include "source\system\object\primitive\Primitive.h"
#include <d3dcompiler.h>
//#include "source\system\DXTex\DirectXTex.h"
#include "source\system\Framework.h"
#include "source\system\object\3d\FBX.h"
using namespace DirectX;




// 定数バッファのデータ


VertexData CUBE_VERTEX[] =
{
	{ XMFLOAT3(-0.5f, +0.5f, +0.5f),XMFLOAT3(+0.0f, +1.0f, +0.0f),{} },
	{ XMFLOAT3(+0.5f, +0.5f, +0.5f),XMFLOAT3(+0.0f, +1.0f, +0.0f),{}},
	{ XMFLOAT3(-0.5f, +0.5f, -0.5f),XMFLOAT3(+0.0f, +1.0f, +0.0f),{}},
	{ XMFLOAT3(+0.5f, +0.5f, -0.5f),XMFLOAT3(+0.0f, +1.0f, +0.0f),{}},
	{ XMFLOAT3(-0.5f, -0.5f, +0.5f),XMFLOAT3(+0.0f, -1.0f, +0.0f),{} },
	{ XMFLOAT3(+0.5f, -0.5f, +0.5f),XMFLOAT3(+0.0f, -1.0f, +0.0f),{} },
	{ XMFLOAT3(-0.5f, -0.5f, -0.5f),XMFLOAT3(+0.0f, -1.0f, +0.0f),{} },
	{ XMFLOAT3(+0.5f, -0.5f, -0.5f),XMFLOAT3(+0.0f, -1.0f, +0.0f),{} },
	{ XMFLOAT3(-0.5f, +0.5f, -0.5f),XMFLOAT3(+0.0f, +0.0f, -1.0f),{} },
	{ XMFLOAT3(+0.5f, +0.5f, -0.5f),XMFLOAT3(+0.0f, +0.0f, -1.0f),{}},
	{ XMFLOAT3(-0.5f, -0.5f, -0.5f),XMFLOAT3(+0.0f, +0.0f, -1.0f),{}},
	{ XMFLOAT3(+0.5f, -0.5f, -0.5f),XMFLOAT3(+0.0f, +0.0f, -1.0f),{}},
	{ XMFLOAT3(-0.5f, +0.5f, +0.5f),XMFLOAT3(+0.0f, +0.0f, +1.0f),{} },
	{ XMFLOAT3(+0.5f, +0.5f, +0.5f),XMFLOAT3(+0.0f, +0.0f, +1.0f),{} },
	{ XMFLOAT3(-0.5f, -0.5f, +0.5f),XMFLOAT3(+0.0f, +0.0f, +1.0f),{} },
	{ XMFLOAT3(+0.5f, -0.5f, +0.5f),XMFLOAT3(+0.0f, +0.0f, +1.0f),{} },
	{ XMFLOAT3(+0.5f, +0.5f, -0.5f),XMFLOAT3(+1.0f, +0.0f, +0.0f),{} },
	{ XMFLOAT3(+0.5f, +0.5f, +0.5f),XMFLOAT3(+1.0f, +0.0f, +0.0f),{} },
	{ XMFLOAT3(+0.5f, -0.5f, -0.5f),XMFLOAT3(+1.0f, +0.0f, +0.0f),{} },
	{ XMFLOAT3(+0.5f, -0.5f, +0.5f),XMFLOAT3(+1.0f, +0.0f, +0.0f),{} },
	{ XMFLOAT3(-0.5f, +0.5f, -0.5f),XMFLOAT3(-1.0f, +0.0f, +0.0f),{} },
	{ XMFLOAT3(-0.5f, +0.5f, +0.5f),XMFLOAT3(-1.0f, +0.0f, +0.0f),{} },
	{ XMFLOAT3(-0.5f, -0.5f, -0.5f),XMFLOAT3(-1.0f, +0.0f, +0.0f),{} },
	{ XMFLOAT3(-0.5f, -0.5f, +0.5f),XMFLOAT3(-1.0f, +0.0f, +0.0f),{} }
};


unsigned  int CUBE_INDICES[] =
{
	0,1,2,1,3,2,
	4 ,6 ,5 ,5 ,6 ,7 ,
	8 ,9 ,10,9 ,11,10,
	12,14,13,13,14,15,
	16,17,18,17,19,18,
	20,22,21,21,22,23
};


bool YQ3DBase::CreateBuffer(VertexData* v, int v_num, unsigned int* indices, int ind_num)
{
	//HRESULT hr;

	//D3D11_BUFFER_DESC buffer_desc = {};
	//D3D11_SUBRESOURCE_DATA subresource_data = {};


	////vertex buffer作成

	//buffer_desc.ByteWidth = sizeof(VertexData)*v_num;
	////buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	//buffer_desc.Usage = D3D11_USAGE_IMMUTABLE;
	//buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//buffer_desc.CPUAccessFlags = 0;
	//buffer_desc.MiscFlags = 0;
	//buffer_desc.StructureByteStride = 0;
	//subresource_data.pSysMem = v;
	//subresource_data.SysMemPitch = 0;
	//subresource_data.SysMemSlicePitch = 0;

	//hr = Framework::device->CreateBuffer(&buffer_desc, &subresource_data, vertex_buffer.ReleaseAndGetAddressOf());




	////index buffer作成

	//buffer_desc.ByteWidth = sizeof(u_int)*ind_num;
	////buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	//buffer_desc.Usage = D3D11_USAGE_IMMUTABLE;
	//buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//buffer_desc.CPUAccessFlags = 0;
	//buffer_desc.MiscFlags = 0;
	//buffer_desc.StructureByteStride = 0;
	//subresource_data.pSysMem = indices;
	//subresource_data.SysMemPitch = 0;
	//subresource_data.SysMemSlicePitch = 0;
	//hr = Framework::device->CreateBuffer(&buffer_desc, &subresource_data, index_buffer.ReleaseAndGetAddressOf());

	return true;

}
bool YQ3DBase::CreateBuffer(VertexData* v, int v_num, unsigned int* indices, int ind_num, ID3D11Buffer** v_buffer, ID3D11Buffer** i_buffer)
{
	HRESULT hr;

	D3D11_BUFFER_DESC buffer_desc = {};
	D3D11_SUBRESOURCE_DATA subresource_data = {};


	//vertex buffer作成

	buffer_desc.ByteWidth = sizeof(VertexData)*v_num;
	//buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.Usage = D3D11_USAGE_IMMUTABLE;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;
	subresource_data.pSysMem = v;
	subresource_data.SysMemPitch = 0;
	subresource_data.SysMemSlicePitch = 0;

	hr = Framework::device->CreateBuffer(&buffer_desc, &subresource_data, v_buffer);




	//index buffer作成

	buffer_desc.ByteWidth = sizeof(u_int)*ind_num;
	//buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.Usage = D3D11_USAGE_IMMUTABLE;
	buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;
	subresource_data.pSysMem = indices;
	subresource_data.SysMemPitch = 0;
	subresource_data.SysMemSlicePitch = 0;
	hr = Framework::device->CreateBuffer(&buffer_desc, &subresource_data, i_buffer);

	return true;

}

void YQ3DBase::CreateDummyTexture(ID3D11ShaderResourceView** dpsrv)
{


	D3D11_TEXTURE2D_DESC texture2d_desc = {};
	texture2d_desc.Width = 1;
	texture2d_desc.Height = 1;
	texture2d_desc.MipLevels = 1;
	texture2d_desc.ArraySize = 1;
	texture2d_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texture2d_desc.SampleDesc.Count = 1;
	texture2d_desc.SampleDesc.Quality = 0;
	texture2d_desc.Usage = D3D11_USAGE_DEFAULT;
	texture2d_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texture2d_desc.CPUAccessFlags = 0;
	texture2d_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA subresource_data = {};
	u_int color = 0xFFFFFFFF;
	subresource_data.pSysMem = &color;
	subresource_data.SysMemPitch = 4;
	subresource_data.SysMemSlicePitch = 4;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2d;

	HRESULT hr = Framework::device->CreateTexture2D(&texture2d_desc, &subresource_data, texture2d.GetAddressOf());


	D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_desc = {};
	shader_resource_view_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	shader_resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shader_resource_view_desc.Texture2D.MipLevels = 1;

	hr = Framework::device->CreateShaderResourceView(texture2d.Get(), &shader_resource_view_desc, dpsrv);

	//srv.Reset();
}

Primitive_Cube::Primitive_Cube()
{
	HRESULT hr = S_OK;

	D3D11_INPUT_ELEMENT_DESC input_element_desc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	//create_vs_from_cso(device, "geometric_primitive_vs.cso", vertex_shader.GetAddressOf(), input_layout.GetAddressOf(), input_element_desc, ARRAYSIZE(input_element_desc));
	//create_ps_from_cso(device, "geometric_primitive_ps.cso", pixel_shader.GetAddressOf());

	ID3DBlob* pBlobVS;

	hr = D3DCompileFromFile(L"shader\\primitive_vs.hlsl", NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS",
		"vs_5_0", 0, 0, &pBlobVS, NULL);

	if (FAILED(hr))return;


	hr = Framework::device->CreateVertexShader(pBlobVS->GetBufferPointer(),
		pBlobVS->GetBufferSize(), NULL, vertex_shader.GetAddressOf());

	if (FAILED(hr))
		return;

	hr = Framework::device->CreateInputLayout(input_element_desc, _countof(input_element_desc), pBlobVS->GetBufferPointer(),
		pBlobVS->GetBufferSize(), input_layout.GetAddressOf());
	if (FAILED(hr))return;


	pBlobVS->Release();


	D3D11_RASTERIZER_DESC rasterizer_desc = {};
	rasterizer_desc.FillMode = D3D11_FILL_SOLID; //D3D11_FILL_WIREFRAME, D3D11_FILL_SOLID
	rasterizer_desc.CullMode = D3D11_CULL_BACK; //, D3D11_CULL_NONED3D11_CULL_FRONT, D3D11_CULL_BACK   
	rasterizer_desc.FrontCounterClockwise = FALSE;
	rasterizer_desc.DepthBias = 0;
	rasterizer_desc.DepthBiasClamp = 0;
	rasterizer_desc.SlopeScaledDepthBias = 0;
	rasterizer_desc.DepthClipEnable = TRUE;
	rasterizer_desc.ScissorEnable = FALSE;
	rasterizer_desc.MultisampleEnable = FALSE;
	rasterizer_desc.AntialiasedLineEnable = FALSE;
	hr = Framework::device->CreateRasterizerState(&rasterizer_desc, rasterizer_state.GetAddressOf());
	if (FAILED(hr))
	{
		return;
	}




	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
	depth_stencil_desc.DepthEnable = TRUE;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
	depth_stencil_desc.StencilEnable = FALSE;
	depth_stencil_desc.StencilReadMask = 0xFF;
	depth_stencil_desc.StencilWriteMask = 0xFF;
	depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	hr = Framework::device->CreateDepthStencilState(&depth_stencil_desc, depth_stencil_state.GetAddressOf());
	if (FAILED(hr))
	{
		return;
	}
	ID3DBlob* pBlobPS;
	hr = D3DCompileFromFile(L"shader\\primitive_ps.hlsl", NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS",
		"ps_5_0", 0, 0, &pBlobPS, NULL);
	if (FAILED(hr))return;

	hr = Framework::device->CreatePixelShader(pBlobPS->GetBufferPointer(),
		pBlobPS->GetBufferSize(), NULL, pixel_shader.GetAddressOf());
	if (FAILED(hr))return;

	//char path[256];
	//size_t size = {};
	//wcstombs_s(&size, path, file_string, 256);
	//RESOURCE_BRAIN->pixel_shader_map.insert(std::make_pair(path, pixel_shader));



	pBlobPS->Release();


	D3D11_BUFFER_DESC buffer_desc = {};
	buffer_desc.ByteWidth = sizeof(ConstantBuffer);
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;
	hr = Framework::device->CreateBuffer(&buffer_desc, nullptr, constant_buffer.GetAddressOf());
	if (FAILED(hr))
	{
		return;
	}

	vertex_count = 36;
	CreateBuffer(CUBE_VERTEX, 24, CUBE_INDICES, vertex_count);

}



void YQ3DBase::Render()
{

	////return;
	//XMVECTOR eye = XMVectorSet(0.0f, .0f, -10.0f, 1.0f);
	//XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	//XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//Scene::view_mat = XMMatrixLookAtLH(eye, At, Up);
	//Scene::projection_mat = XMMatrixPerspectiveFovLH(3.14f / 8.0f, static_cast<float>(Framework::SCREEN_WIDTH) / Framework::SCREEN_HEIGHT, 0.01f, 100.0f);

	//XMMATRIX matY, matX;
	//FLOAT rotate = (FLOAT)(XM_PI * (timeGetTime() % 3000)) / 1500.0f;
	//matY = XMMatrixRotationY(rotate);
	//rotate = (FLOAT)(XM_PI * (timeGetTime() % 1500)) / 750.0f;
	//matX = XMMatrixRotationX(rotate);
	//Scene::world_mat = XMMatrixTranspose(matY * matX);

	//XMFLOAT4X4 wvp;
	//XMFLOAT4X4 inverse;
	//XMStoreFloat4x4(&wvp, Scene::world_mat * Scene::view_mat * Scene::projection_mat);
	//VECTORIII a = {};



	//ConstantBuffer cb;

	//cb.world_view_projection = wvp;
	//DirectX::XMStoreFloat4x4(&inverse, DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(0, Scene::world_mat)));
	//cb.world_inverse_transpose = inverse;
	//cb.material_color = { 1.0f,1.0f,1.0f,1.0f };
	//cb.light_direction = { 5.0f,.0f,.0f,1.0f };



	//for each(auto& mesh in meshes)
	//{




	//	Framework::device_context->UpdateSubresource(constant_buffer.Get(), 0, NULL, &cb, 0, 0);
	//	UINT strides = { sizeof(VertexData) };
	//	UINT offsets[2] = { 0, 0 };
	//	Framework::device_context->IASetVertexBuffers(0, 1, vertex_buffer.GetAddressOf(), &strides, offsets);
	//	Framework::device_context->IASetIndexBuffer(index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	//	Framework::device_context->IASetInputLayout(input_layout.Get());
	//	Framework::device_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//	Framework::device_context->VSSetShader(vertex_shader.Get(), NULL, 0);
	//	Framework::device_context->VSSetConstantBuffers(0, 1, constant_buffer.GetAddressOf());
	//	Framework::device_context->PSSetShader(pixel_shader.Get(), NULL, 0);
	//	Framework::device_context->PSSetConstantBuffers(0, 1, constant_buffer.GetAddressOf());
	//	Framework::device_context->OMSetDepthStencilState(depth_stencil_state.Get(), 0);
	//	Framework::device_context->RSSetState(rasterizer_state.Get());
	//	FLOAT BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	//	Framework::device_context->DrawIndexed(vertex_count, 0, 0);
	//}
}


YQMesh::YQMesh(const char* filename)
{
	HRESULT hr = S_OK;

	D3D11_INPUT_ELEMENT_DESC input_element_desc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	//create_vs_from_cso(device, "geometric_primitive_vs.cso", vertex_shader.GetAddressOf(), input_layout.GetAddressOf(), input_element_desc, ARRAYSIZE(input_element_desc));
	//create_ps_from_cso(device, "geometric_primitive_ps.cso", pixel_shader.GetAddressOf());

	ID3DBlob* pBlobVS;

	hr = D3DCompileFromFile(L"shader\\primitive_vs.hlsl", NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS",
		"vs_5_0", 0, 0, &pBlobVS, NULL);

	if (FAILED(hr))return;


	hr = Framework::device->CreateVertexShader(pBlobVS->GetBufferPointer(),
		pBlobVS->GetBufferSize(), NULL, vertex_shader.GetAddressOf());

	if (FAILED(hr))
		return;

	hr = Framework::device->CreateInputLayout(input_element_desc, _countof(input_element_desc), pBlobVS->GetBufferPointer(),
		pBlobVS->GetBufferSize(), input_layout.GetAddressOf());
	if (FAILED(hr))return;


	pBlobVS->Release();


	D3D11_RASTERIZER_DESC rasterizer_desc = {};
	rasterizer_desc.FillMode = D3D11_FILL_SOLID; //D3D11_FILL_WIREFRAME, D3D11_FILL_SOLID
	rasterizer_desc.CullMode = D3D11_CULL_BACK; //, D3D11_CULL_NONED3D11_CULL_FRONT, D3D11_CULL_BACK   
	rasterizer_desc.FrontCounterClockwise = FALSE;
	rasterizer_desc.DepthBias = 0;
	rasterizer_desc.DepthBiasClamp = 0;
	rasterizer_desc.SlopeScaledDepthBias = 0;
	rasterizer_desc.DepthClipEnable = TRUE;
	rasterizer_desc.ScissorEnable = FALSE;
	rasterizer_desc.MultisampleEnable = FALSE;
	rasterizer_desc.AntialiasedLineEnable = FALSE;
	hr = Framework::device->CreateRasterizerState(&rasterizer_desc, rasterizer_state.GetAddressOf());
	if (FAILED(hr))
	{
		return;
	}
	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
	depth_stencil_desc.DepthEnable = TRUE;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
	depth_stencil_desc.StencilEnable = FALSE;
	depth_stencil_desc.StencilReadMask = 0xFF;
	depth_stencil_desc.StencilWriteMask = 0xFF;
	depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	hr = Framework::device->CreateDepthStencilState(&depth_stencil_desc, depth_stencil_state.GetAddressOf());
	if (FAILED(hr))
	{
		return;
	}
	ID3DBlob* pBlobPS;
	hr = D3DCompileFromFile(L"shader\\primitive_ps.hlsl", NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS",
		"ps_5_0", 0, 0, &pBlobPS, NULL);
	if (FAILED(hr))return;

	hr = Framework::device->CreatePixelShader(pBlobPS->GetBufferPointer(),
		pBlobPS->GetBufferSize(), NULL, pixel_shader.GetAddressOf());
	if (FAILED(hr))return;

	pBlobPS->Release();


	D3D11_BUFFER_DESC buffer_desc = {};
	buffer_desc.ByteWidth = sizeof(ConstantBuffer);
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;
	hr = Framework::device->CreateBuffer(&buffer_desc, nullptr, constant_buffer.GetAddressOf());
	if (FAILED(hr))
	{
		return;
	}

	//FBXLoader::LoadFBX(filename);

	CreateBuffer(CUBE_VERTEX, 24, CUBE_INDICES, 36);
}