#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
class YQ3D
{
public:
	YQ3D(const wchar_t* filename);
	~YQ3D() {}
protected:
	Microsoft::WRL::ComPtr<ID3D11VertexShader>		vertex_shader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>		pixel_shader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>		input_layout;
	Microsoft::WRL::ComPtr<ID3D11Buffer>			constant_buffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>			vertex_buffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>			index_buffer;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>	rasterizer_state;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>srv;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>		sampler_state;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state;
	Microsoft::WRL::ComPtr<ID3D11BlendState>		blend_state;

	struct VertexData
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
	};

	struct ConstantBuffer
	{
		DirectX::XMFLOAT4X4 world_view_projection;
		DirectX::XMFLOAT4X4 world_inverse_transpose;
		DirectX::XMFLOAT4 material_color;
		DirectX::XMFLOAT4 light_direction;
	};
public:
	void Render();

	bool LoadFBX(const char* filename);

};

