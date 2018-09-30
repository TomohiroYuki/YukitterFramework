#pragma once
#include <string>
#include <wrl.h>
#include <d3d11.h>
class ShaderStructure
{
public:
	ShaderStructure()
	{
		Initialize();
	}

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
	std::wstring vs_path;
	std::wstring ps_path;
	std::string vs_model;
	std::string ps_model;
	std::string vs_entry;
	std::string ps_entry;

	virtual void Initialize()
	{
		vs_path = L"shader\\primitive_vs.hlsl";
		ps_path = L"shader\\primitive_ps.hlsl";
		vs_model = "vs_5_0";
		ps_model = "ps_5_0";
		vs_entry = "VS";
		ps_entry = "PS";
	}



};

class PhongShaderStructure :public ShaderStructure
{
public:
	PhongShaderStructure() :
		ShaderStructure() {}

	void  Initialize() override
	{
		vs_path = L"shader\\SkeltalMeshVertexShader.hlsl";
		ps_path = L"shader\\primitive_ps.hlsl";
		vs_model = "vs_5_0";
		ps_model = "ps_5_0";
		vs_entry = "VS";
		ps_entry = "PS";
	}
};


class GouraudshaderStructure :public ShaderStructure
{
public:
	GouraudshaderStructure() :
		ShaderStructure() {}

	void  Initialize() override
	{
		vs_path = L"shader\\primitive_vs.hlsl";
		ps_path = L"shader\\primitive_ps.hlsl";
		vs_model = "vs_5_0";
		ps_model = "ps_5_0";
		vs_entry = "GouraudShader_VS";
		ps_entry = "GouraudShader_PS";
	}
};

class ToonShaderStructure :public ShaderStructure
{
public:
	ToonShaderStructure() :
		ShaderStructure() {}


	void  Initialize() override;
};


class HemisphereshaderStructure :public ShaderStructure
{
public:
	HemisphereshaderStructure() :
		ShaderStructure() {}

	void  Initialize() override
	{
		vs_path = L"shader\\primitive_vs.hlsl";
		ps_path = L"shader\\primitive_ps.hlsl";
		vs_model = "vs_5_0";
		ps_model = "ps_5_0";
		vs_entry = "HemisphereShader";
		ps_entry = "GouraudShader_PS";
	}
};