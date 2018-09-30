#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
#include "source\math\yuki_math.h"
class Sprite {

	Microsoft::WRL::ComPtr<ID3D11VertexShader>		vertex_shader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>		pixel_shader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>		input_layout;
	Microsoft::WRL::ComPtr<ID3D11Buffer>			buffer;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>	rasterizer_state;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>shader_resourceview;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>		sampler_state;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state; 
	Microsoft::WRL::ComPtr<ID3D11BlendState>		blend_state;

	D3D11_TEXTURE2D_DESC		texture_desc;
	
			
	// add 
	/*int _width = 0;
	int _height = 0;*/
	VECTORII tex_size;

public:
	void Render(VECTORII pos, VECTORII size, VECTORII tpos, VECTORII tsize);
	void Render(VECTORII pos, VECTORII size, VECTORII tpos, VECTORII tsize, VECTORII rpos, float angle);
	void Render(VECTORII pos, VECTORII size, VECTORII tpos, VECTORII tsize, VECTORII rpos, float angle,VECTORIV color);

	Sprite(const wchar_t*);
	~Sprite() {}
};

struct vertex
{
	DirectX::XMFLOAT4 position;
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT2 texcoord;
};