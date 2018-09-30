#include "source\system\object\3d\YQ3D.h"
#include <DirectXMath.h>
#include "source\system\Framework.h"
#include "source\game\scene\Scene.h"
#include "source\system\object\3d\FBX.h"

using namespace DirectX;

YQ3D::YQ3D(const wchar_t* filename)
{

}

bool YQ3D::LoadFBX(const char* filename)
{

	//this=StaticMesh::LoadFromFBXFile(filename);
	
	return true;
}

void YQ3D::Render()
{
	//return;
	XMVECTOR eye = XMVectorSet(0.0f, .0f, -10.0f, 1.0f);
	XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//Scene::view_mat = XMMatrixLookAtLH(eye, At, Up);
	Scene::projection_mat = XMMatrixPerspectiveFovLH(3.14f / 8.0f, static_cast<float>(Framework::SCREEN_WIDTH) / Framework::SCREEN_HEIGHT, 0.01f, 100.0f);

	XMMATRIX matY, matX;
	FLOAT rotate = (FLOAT)(XM_PI * (timeGetTime() % 3000)) / 1500.0f;
	matY = XMMatrixRotationY(rotate);
	rotate = (FLOAT)(XM_PI * (timeGetTime() % 1500)) / 750.0f;
	matX = XMMatrixRotationX(rotate);
	//Scene::world_mat = XMMatrixTranspose(matY * matX);

	XMFLOAT4X4 wvp;
	XMFLOAT4X4 inverse;
	//XMStoreFloat4x4(&wvp, Scene::world_mat * Scene::view_mat * Scene::projection_mat);
	VECTORIII a = {};



	ConstantBuffer cb;

	cb.world_view_projection = wvp;
	//DirectX::XMStoreFloat4x4(&inverse, DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(0, Scene::world_mat)));
	cb.world_inverse_transpose = inverse;
	cb.material_color = { 1.0f,1.0f,1.0f,1.0f };
	cb.light_direction = { 5.0f,.0f,.0f,1.0f };

	Framework::device_context->UpdateSubresource(constant_buffer.Get(), 0, NULL, &cb, 0, 0);
	UINT strides = { sizeof(VertexData) };
	UINT offsets[2] = { 0, 0 };
	Framework::device_context->IASetVertexBuffers(0, 1, vertex_buffer.GetAddressOf(), &strides, offsets);
	Framework::device_context->IASetIndexBuffer(index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	Framework::device_context->IASetInputLayout(input_layout.Get());
	Framework::device_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Framework::device_context->VSSetShader(vertex_shader.Get(), NULL, 0);
	Framework::device_context->VSSetConstantBuffers(0, 1, constant_buffer.GetAddressOf());
	Framework::device_context->PSSetShader(pixel_shader.Get(), NULL, 0);
	Framework::device_context->PSSetConstantBuffers(0, 1, constant_buffer.GetAddressOf());
	Framework::device_context->OMSetDepthStencilState(depth_stencil_state.Get(), 0);
	Framework::device_context->RSSetState(rasterizer_state.Get());
	FLOAT BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	Framework::device_context->DrawIndexed(36, 0, 0);
}