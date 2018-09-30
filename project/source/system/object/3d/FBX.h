#pragma once
#include <fbxsdk.h>
#include "source\system\object\primitive\Primitive.h"

#include <vector>
//class FBXLoader
//{
//public:
//	FBXLoader() = delete;
//	~FBXLoader() = delete;
//private:
//public:
//
//	static bool LoadFBX(const char* file_name);
//	static void GetMesh(FbxNode* node);
//	static void LoadMesh(FbxMesh* mesh);
//};


struct bone_influence
{
	int index; // index of bone  
	float weight; // weight of bone 
};
typedef std::vector<bone_influence> bone_influences_per_control_point;





class YQCamera;

class StaticMesh : public YQ3DBase
{
public:
	StaticMesh(const char* file_name);
	~StaticMesh(){};
private:
public:

	struct bone
	{
		DirectX::XMFLOAT4X4 transform;
	};
	typedef std::vector<bone> skeletal;
	struct skeletal_animation : public std::vector<skeletal>
	{
	public:
		float sampling_time = 1 / 24.0f;
		float animation_tick = 0.0f;
	};

	struct Mesh
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> index_buffer;
		std::vector<Subset> subsets;
		DirectX::XMFLOAT4X4 global_transform = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		//std::vector<StaticMesh::bone> skeletal;
		skeletal_animation skeletal_animation;
		float animation_tick__ = 0.0f;
	};



	std::vector<Mesh> meshes;
	
	void Render(float dt,DirectX::XMFLOAT3 pos,float angle,float scale);
};


//class HOGE : public YQ3DBase
//{
//public:
//	HOGE(const char* file_name);
//	~HOGE(){};
//private:
//public:
//	DirectX::XMFLOAT4X4 coordinate_conversion = { 1, 0, 0, 0,    0, 0, 1, 0,    0, 1, 0, 0,    0, 0, 0, 1 };
//	//std::vector<Mesh> meshes;
//	bool CreateBuffer(SkeltalMeshVertexData* v, int v_num, unsigned int* indicies, int ind_num, ID3D11Buffer** v_buffer, ID3D11Buffer** i_buffer);
//	void Render();
//};
//
