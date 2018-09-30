#include "source\shaders\Shader.h"
#include "source\system\DXTex\DirectXTex.h"
#include "source\system\Framework.h"
void  ToonShaderStructure::Initialize()
{
	DirectX::TexMetadata metadata;
	DirectX::ScratchImage image;
	
	DirectX::LoadFromWICFile(L"DATA\\2D\\toon.png", 0, &metadata, image);
	HRESULT hr = DirectX::CreateShaderResourceView(Framework::device.Get(), image.GetImages(), image.GetImageCount(), metadata, srv.GetAddressOf());

	
	vs_path = L"shader\\primitive_vs.hlsl";
	ps_path = L"shader\\primitive_ps.hlsl";
	vs_model = "vs_5_0";
	ps_model = "ps_5_0";
	vs_entry = "ToonShader_VS";
	ps_entry = "ToonShader_PS";
}