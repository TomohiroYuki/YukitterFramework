#pragma once
#include "source\system\object\primitive\Primitive.h"

#define MAX_BONE_INFLUENCES 4 
struct SkeltalMeshVertexData
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 texcoord;
	FLOAT bone_weights[MAX_BONE_INFLUENCES] = { 1, 0, 0, 0 };
	INT bone_indices[MAX_BONE_INFLUENCES] = {};
};



class SkeltalMesh :public YQ3DBase
{
public:
	SkeltalMesh(const char* file_name);
	~SkeltalMesh() {};
private:
public:
	struct bone
	{
		DirectX::XMFLOAT4X4 transform;
	};
	typedef std::vector<bone> skeletal;
	struct skeletal_animation : public std::vector<skeletal>
	{
		float sampling_time = 1 / 24.0f;
		float animation_tick = 0.0f;
	};


	struct Mesh
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> index_buffer;
		std::vector<Subset> subsets;
		DirectX::XMFLOAT4X4 global_transform = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		// UNIT.22
		std::vector<SkeltalMesh::bone> skeletal;
	};
public:


	DirectX::XMFLOAT4X4 coordinate_conversion = { 1, 0, 0, 0,    0, 0, 1, 0,    0, 1, 0, 0,    0, 0, 0, 1 };
	std::vector<Mesh> meshes;
	bool CreateBuffer(SkeltalMeshVertexData* v, int v_num, unsigned int* indicies, int ind_num, ID3D11Buffer** v_buffer, ID3D11Buffer** i_buffer);
	void Render(DirectX::XMFLOAT3 pos, float angle, float scale);
};