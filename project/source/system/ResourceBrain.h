#pragma once
#include <map>
#include <d3d11.h>
#include <string>
#include "source\math\yuki_math.h"


struct VSandInputLayout {
	VSandInputLayout(Microsoft::WRL::ComPtr<ID3D11VertexShader> vs, Microsoft::WRL::ComPtr<ID3D11InputLayout> ir) :
		vs(vs),
		input_layout(ir)
	{}
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vs;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout;
};

struct SRVandTexture {
	SRVandTexture(VECTORII& texsize, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv) :
		texsize(texsize),
		srv(srv)
	{}
	VECTORII texsize;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
};


class ResourceBrain {
	ResourceBrain() = default;
	~ResourceBrain() = default;
public:
	// Singleton
	ResourceBrain(const ResourceBrain&) = delete;				//コピーコンストラクタを delete 指定
	ResourceBrain& operator=(const ResourceBrain&) = delete;	//コピー代入演算子も delete 指定
	ResourceBrain(ResourceBrain&&) = delete;					//ムーブコンストラクタを delete 指定
	ResourceBrain& operator=(ResourceBrain&&) = delete;			//ムーブ代入演算子も delete 指定


	std::map<std::string, ID3D11Texture2D* > texture_map;
	std::map<std::string, SRVandTexture > srv_and_tex_map;
	std::map<std::string, VSandInputLayout > vertex_shader_map;
	std::map<std::string, Microsoft::WRL::ComPtr<ID3D11PixelShader>> pixel_shader_map;

	//std::map<const wchar_t*, ID3D11GeometryShader* > geometry_shader_map;

	//mapにすでにあるかの確認**************************************************
	bool searchTecture(const wchar_t* string)
	{
		char path[256];
		size_t size = {};
		wcstombs_s(&size, path, string, 256);
		if (texture_map.count(path) != 0)return true;
		return false;
	}
	bool searchShaderResourceView(const wchar_t* string)
	{
		char path[256];
		size_t size = {};
		wcstombs_s(&size, path, string, 256);
		if (srv_and_tex_map.count(path) != 0)return true;
		return false;
	}
	bool searchVS(const wchar_t* string)
	{
		char path[256];
		size_t size = {};
		wcstombs_s(&size, path, string, 256);
		if (vertex_shader_map.count(path) != 0)return true;
		return false;
	}
	bool searchPS(const wchar_t* string)
	{
		char path[256];
		size_t size = {};
		wcstombs_s(&size, path, string, 256);
		if (pixel_shader_map.count(path) != 0)return true;
		return false;
	}

	//**********************************************************************

	//mapからデータを取得*****************************************************
	ID3D11Texture2D* GetTextureFromR_MGR(const wchar_t* string)
	{
		char path[256];
		size_t size = {};
		wcstombs_s(&size, path, string, 256);
		return texture_map.find(path)->second;
	}
	SRVandTexture& GetSRVanTexFromR_MGR(const wchar_t* string)
	{
		char path[256];
		size_t size = {};
		wcstombs_s(&size, path, string, 256);
		return srv_and_tex_map.find(path)->second;
	}
	VSandInputLayout& GetVSFromR_MGR(const wchar_t* string)
	{
		char path[256];
		size_t size = {};
		wcstombs_s(&size, path, string, 256);
		return vertex_shader_map.find(path)->second;
	}
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetPSFromR_MGR(const wchar_t* string)
	{
		char path[256];
		size_t size = {};
		wcstombs_s(&size, path, string, 256);
		return pixel_shader_map.find(path)->second;
	}

	//*************************************************************************

	static ResourceBrain* getInstance()
	{
		static ResourceBrain inst;			// privateなコンストラクタを呼び出す
		return &inst;
	}


};

#define RESOURCE_BRAIN  (ResourceBrain::getInstance())