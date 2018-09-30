#pragma once
#include <DirectXMath.h>
#include <wrl.h> 
#include <d3d11.h>
#include <vector>

#include <memory>
#include "source\shaders\Shader.h"
struct VertexData
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 texcoord;
#define MAX_BONE_INFLUENCES_ 4
	FLOAT bone_weights[MAX_BONE_INFLUENCES_] = { 1, 0, 0, 0 };
	INT bone_indices[MAX_BONE_INFLUENCES_] = {};
};





#define BONE_MAX 64

class YQ3DBase
{


public:
	YQ3DBase() 
	{
		shader_structure = std::make_unique<ShaderStructure>();
	}
	virtual ~YQ3DBase()
	{

	}
protected:
	Microsoft::WRL::ComPtr<ID3D11VertexShader>		vertex_shader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>		pixel_shader;
	Microsoft::WRL::ComPtr<ID3D11GeometryShader>	geometry_shader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>		input_layout;
	Microsoft::WRL::ComPtr<ID3D11Buffer>			constant_buffer;
	//Microsoft::WRL::ComPtr<ID3D11Buffer>			index_buffer;
	//Microsoft::WRL::ComPtr<ID3D11Buffer>			vertex_buffer;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>	rasterizer_state;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>srv;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>		sampler_state;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state;
	Microsoft::WRL::ComPtr<ID3D11BlendState>		blend_state;

	std::unique_ptr<ShaderStructure> shader_structure;

	struct material
	{
		DirectX::XMFLOAT4 color = { 0.8f, 0.8f, 0.8f, 1.0f };

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
	};
	struct Subset
	{
		u_int index_start = 0; // start number of index buffer  
		u_int index_count = 0; // number of vertices (indices)  
		material diffuse;
	};


public:


	struct ConstantBuffer
	{
		DirectX::XMFLOAT4X4 world_view_projection;
		DirectX::XMFLOAT4X4 world_inverse_transpose;
		DirectX::XMFLOAT4   material_color;
		DirectX::XMFLOAT4   light_direction;
		DirectX::XMFLOAT4X4 bone_transforms[BONE_MAX] = {};
		DirectX::XMFLOAT4   camera_location;
		DirectX::XMFLOAT4   ambient_color;
	};




	virtual void Render();

	int vertex_count{};

	bool CreateBuffer(VertexData* v, int v_num, unsigned int* indicies, int ind_num);
	virtual bool CreateBuffer(VertexData* v, int v_num, unsigned int* indicies, int ind_num, ID3D11Buffer** v_buffer, ID3D11Buffer** i_buffer);


	void CreateDummyTexture(ID3D11ShaderResourceView** srv);

};

class Primitive_Cube :public YQ3DBase
{
public:
	Primitive_Cube();
	~Primitive_Cube() {}
private:
public:


};


class YQMesh :public YQ3DBase
{
public:
	YQMesh(const char*);
	~YQMesh() {}
private:
public:

};