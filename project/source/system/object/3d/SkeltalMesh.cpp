#include "source\system\object\3d\SkeltalMesh.h"
#include "source\system\Framework.h"
#include <d3dcompiler.h>
#include <functional>
#include "source\system\DXTex\DirectXTex.h"
#include <DirectXMath.h>
using namespace DirectX;


void fetch_bone_influences(const FbxMesh *fbx_mesh, std::vector<bone_influences_per_control_point> &influences)
{
	const int number_of_control_points = fbx_mesh->GetControlPointsCount();
	influences.resize(number_of_control_points);

	const int number_of_deformers = fbx_mesh->GetDeformerCount(FbxDeformer::eSkin);
	for (int index_of_deformer = 0; index_of_deformer < number_of_deformers; ++index_of_deformer)
	{
		FbxSkin *skin = static_cast<FbxSkin *>(fbx_mesh->GetDeformer(index_of_deformer, FbxDeformer::eSkin));

		const int number_of_clusters = skin->GetClusterCount();
		for (int index_of_cluster = 0; index_of_cluster < number_of_clusters; ++index_of_cluster)
		{
			FbxCluster* cluster = skin->GetCluster(index_of_cluster);

			const int number_of_control_point_indices = cluster->GetControlPointIndicesCount();
			const int *array_of_control_point_indices = cluster->GetControlPointIndices();
			const double *array_of_control_point_weights = cluster->GetControlPointWeights();

			for (int i = 0; i < number_of_control_point_indices; ++i)
			{
				bone_influences_per_control_point &influences_per_control_point = influences.at(array_of_control_point_indices[i]);
				bone_influence influence;
				influence.index = index_of_cluster;
				influence.weight = static_cast<float>(array_of_control_point_weights[i]);
				influences_per_control_point.push_back(influence);
			}
		}
	}
}

void fetch_bone_matrices(FbxMesh *fbx_mesh, std::vector<SkeltalMesh::bone> &skeletal, FbxTime time)
{
	const int number_of_deformers = fbx_mesh->GetDeformerCount(FbxDeformer::eSkin);
	for (int index_of_deformer = 0; index_of_deformer < number_of_deformers; ++index_of_deformer)
	{
		FbxSkin *skin = static_cast<FbxSkin *>(fbx_mesh->GetDeformer(index_of_deformer, FbxDeformer::eSkin));
		const int number_of_clusters = skin->GetClusterCount();
		skeletal.resize(number_of_clusters);
		for (int index_of_cluster = 0; index_of_cluster < number_of_clusters; ++index_of_cluster)
		{
			SkeltalMesh::bone &bone = skeletal.at(index_of_cluster);
			FbxCluster *cluster = skin->GetCluster(index_of_cluster);
			// this matrix trnasforms coordinates of the initial pose from mesh space to global space
			FbxAMatrix reference_global_init_position;
			cluster->GetTransformMatrix(reference_global_init_position);
			// this matrix trnasforms coordinates of the initial pose from bone space to global space
			FbxAMatrix cluster_global_init_position;
			cluster->GetTransformLinkMatrix(cluster_global_init_position);
			// this matrix trnasforms coordinates of the current pose from bone space to global space
			FbxAMatrix cluster_global_current_position;
			cluster_global_current_position = cluster->GetLink()->EvaluateGlobalTransform(time);
			// this matrix trnasforms coordinates of the current pose from mesh space to global space
			FbxAMatrix reference_global_current_position;
			reference_global_current_position = fbx_mesh->GetNode()->EvaluateGlobalTransform(time);
			// Matrices are defined using the Column Major scheme. When a FbxAMatrix represents a transformation
			// (translation, rotation and scale), the last row of the matrix represents the translation part of the
			// transformation.
			FbxAMatrix transform = reference_global_current_position.Inverse() * cluster_global_current_position
				* cluster_global_init_position.Inverse() * reference_global_init_position;
			// convert FbxAMatrix(transform) to XMDLOAT4X4(bone.transform)
		}
	}
}


SkeltalMesh::SkeltalMesh(const char* file_name)
{
	HRESULT hr = S_OK;

	D3D11_INPUT_ELEMENT_DESC input_element_desc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"	, 0, DXGI_FORMAT_R32G32B32_FLOAT	, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT		, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "WEIGHT"	, 0, DXGI_FORMAT_R32G32B32A32_FLOAT	, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONES"	, 0, DXGI_FORMAT_R32G32B32A32_SINT	, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	//create_vs_from_cso(device, "geometric_primitive_vs.cso", vertex_shader.GetAddressOf(), input_layout.GetAddressOf(), input_element_desc, ARRAYSIZE(input_element_desc));
	//create_ps_from_cso(device, "geometric_primitive_ps.cso", pixel_shader.GetAddressOf());

	ID3DBlob* pBlobVS;

	hr = D3DCompileFromFile(L"shader\\SkeltalMeshVertexShader.hlsl", NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS",
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

#ifdef GS


	ID3DBlob* pBlobGS;

	hr = D3DCompileFromFile(L"shader\\GeometryShader.hlsl", NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
		"gs_5_0", 0, 0, &pBlobGS, NULL);

	if (FAILED(hr))return;


	hr = Framework::device->CreateGeometryShader(pBlobGS->GetBufferPointer(),
		pBlobGS->GetBufferSize(), NULL, geometry_shader.GetAddressOf());

	if (FAILED(hr))
		return;

	pBlobGS->Release();
#endif

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

	D3D11_SAMPLER_DESC samDesc;
	ZeroMemory(&samDesc, sizeof(samDesc));
	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samDesc.AddressU = samDesc.AddressV = samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.MaxAnisotropy = 1;
	samDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samDesc.MaxLOD = D3D11_FLOAT32_MAX;

	Framework::device->CreateSamplerState(&samDesc, sampler_state.GetAddressOf());




	// Create the FBX SDK manager
	FbxManager* manager = FbxManager::Create();
	// Create an IOSettings object. IOSROOT is defined in Fbxiosettingspath.h.
	manager->SetIOSettings(FbxIOSettings::Create(manager, IOSROOT));
	// Create an importer.
	FbxImporter* importer = FbxImporter::Create(manager, "");
	// Initialize the importer.
	bool import_status = false;
	import_status = importer->Initialize(file_name, -1, manager->GetIOSettings());
	//_ASSERT_EXPR_A(import_status, importer->GetStatus().GetErrorString());
	// Create a new scene so it can be populated by the imported file.
	FbxScene* scene = FbxScene::Create(manager, "");
	// Import the contents of the file into the scene.
	import_status = importer->Import(scene);
	//_ASSERT_EXPR_A(import_status, importer->GetStatus().GetErrorString());

	// Convert mesh, NURBS and patch into triangle mesh
	fbxsdk::FbxGeometryConverter geometry_converter(manager);
	geometry_converter.Triangulate(scene, /*replace*/true);
	// Fetch node attributes and materials under this node recursively. Currently only mesh.
	std::vector<FbxNode*> fetched_meshes;
	std::function<void(FbxNode*)> traverse = [&](FbxNode* node)
	{
		if (node)
		{
			FbxNodeAttribute *fbx_node_attribute = node->GetNodeAttribute();

			if (fbx_node_attribute)
			{
				switch (fbx_node_attribute->GetAttributeType())
				{
				case FbxNodeAttribute::eMesh:
					fetched_meshes.push_back(node);
					break;
				}
			}
			for (int i = 0; i < node->GetChildCount(); i++)
				traverse(node->GetChild(i));
		}
	};
	traverse(scene->GetRootNode());



	//FbxMesh *fbx_mesh = fetched_meshes.at(0)->GetMesh();  // Currently only one mesh.  
	meshes.resize(fetched_meshes.size());
	for (size_t i = 0; i < fetched_meshes.size(); i++)
	{
		FbxMesh *fbx_mesh = fetched_meshes.at(i)->GetMesh();
		Mesh &mesh = meshes.at(i);

		std::vector<bone_influences_per_control_point> bone_influences;
		fetch_bone_influences(fbx_mesh, bone_influences);

		// Fetch mesh data
		std::vector<SkeltalMeshVertexData> vertices; // Vertex buffer
		std::vector<u_int> indices; // Index buffer
		u_int v_count = 0;

		const int number_of_materials = fbx_mesh->GetNode()->GetMaterialCount();

		FbxAMatrix global_transform = fbx_mesh->GetNode()->EvaluateGlobalTransform(0);
		for (int row = 0; row < 4; row++)
		{
			for (int column = 0; column < 4; column++)
			{
				mesh.global_transform.m[row][column] = static_cast<float>(global_transform[row][column]);
			}
		}
		//Material0

		for (int index_of_material = 0; index_of_material < number_of_materials; ++index_of_material)
		{
			const FbxSurfaceMaterial *surface_material = fbx_mesh->GetNode()->GetMaterial(index_of_material);
			const FbxProperty property = surface_material->FindProperty(FbxSurfaceMaterial::sDiffuse);
			const FbxProperty factor = surface_material->FindProperty(FbxSurfaceMaterial::sDiffuseFactor);
			Subset s;
			if (property.IsValid() && factor.IsValid())
			{

				FbxDouble3 color = property.Get<FbxDouble3>();
				double f = factor.Get<FbxDouble>();
				s.diffuse.color.x = static_cast<float>(color[0] * f);
				s.diffuse.color.y = static_cast<float>(color[1] * f);
				s.diffuse.color.z = static_cast<float>(color[2] * f);
			}
			if (property.IsValid())
			{
				const int number_of_textures = property.GetSrcObjectCount<FbxFileTexture>();
				if (number_of_textures)
				{
					const FbxFileTexture* file_texture = property.GetSrcObject<FbxFileTexture>();
					if (file_texture)
					{
						const char *texture_name = file_texture->GetRelativeFileName();
						// Create "diffuse.shader_resource_view" from "texture_name".

						DirectX::TexMetadata metadata;
						DirectX::ScratchImage image;


						//変換前文字列

						//変換文字列格納バッファ
						wchar_t	w_texture_name[128];

						size_t wLen = 0;
						errno_t err = 0;

						//ロケール指定
						setlocale(LC_ALL, "japanese");
						//変換
						err = mbstowcs_s(&wLen, w_texture_name, 128, texture_name, _TRUNCATE);

						wchar_t* extention = YQUtility::YQUtility::FindExtention(wLen, w_texture_name);

						int ext_len = wcsnlen_s(extention, sizeof(ext_len));

						for (int i = 0; i < ext_len; i++)
						{
							extention[i] = towupper(extention[i]);
						}

						wchar_t f[128];
						wcscpy(f, YQUtility::YQUtility::ChangeToWcharFromChar(file_name));


						std::wstring  filename = YQUtility::YQUtility::ConnectFilePathAndTextureName(f, w_texture_name);
						if (wcscmp(extention, L"TGA") == 0)
						{
							hr = DirectX::LoadFromTGAFile(filename.c_str(), &metadata, image);
						}

						else if (wcscmp(extention, L"PNG") == 0 || wcscmp(extention, L"JPG") == 0)
						{
							hr = DirectX::LoadFromWICFile(filename.c_str(), 0, &metadata, image);

						}

						if (FAILED(hr))
						{
							//return;
						}
						hr = DirectX::CreateShaderResourceView(Framework::device.Get(), image.GetImages(), image.GetImageCount(), metadata, s.diffuse.srv.GetAddressOf());
						if (FAILED(hr))
						{
							//return;
						}

					}

				}
				else
				{
					CreateDummyTexture(s.diffuse.srv.GetAddressOf());
				}
			}
			mesh.subsets.push_back(s);


		}


		if (number_of_materials > 0)
		{
			const int number_of_polygons = fbx_mesh->GetPolygonCount();
			for (int index_of_polygon = 0; index_of_polygon < number_of_polygons; index_of_polygon++)
			{
				const u_int material_index = fbx_mesh->GetElementMaterial()->GetIndexArray().GetAt(index_of_polygon);
				mesh.subsets.at(material_index).index_count += 3;
			}
			int offset = 0;
			for (Subset& s : mesh.subsets)
			{
				s.index_start = offset;
				offset += s.index_count;
				s.index_count = 0;
			}
		}
		const FbxVector4 *array_of_control_points = fbx_mesh->GetControlPoints();
		const int number_of_polygons = fbx_mesh->GetPolygonCount();
		indices.resize(number_of_polygons * 3);

		for (int index_of_polygon = 0; index_of_polygon < number_of_polygons; index_of_polygon++)
		{
			int index_of_material = 0;
			if (number_of_materials > 0)
			{
				index_of_material = fbx_mesh->GetElementMaterial()->GetIndexArray().GetAt(index_of_polygon);
			}
			Subset &s = mesh.subsets.at(index_of_material);
			const int index_offset = s.index_start + s.index_count;


			for (int index_of_vertex = 0; index_of_vertex < 3; index_of_vertex++)
			{
				SkeltalMeshVertexData vertex;
				const int index_of_control_point = fbx_mesh->GetPolygonVertex(index_of_polygon, index_of_vertex);
				vertex.pos.x = static_cast<float>(array_of_control_points[index_of_control_point][0]);
				vertex.pos.y = static_cast<float>(array_of_control_points[index_of_control_point][1]);
				vertex.pos.z = static_cast<float>(array_of_control_points[index_of_control_point][2]);
				FbxVector4 normal;
				fbx_mesh->GetPolygonVertexNormal(index_of_polygon, index_of_vertex, normal);
				vertex.normal.x = static_cast<float>(normal[0]);
				vertex.normal.y = static_cast<float>(normal[1]);
				vertex.normal.z = static_cast<float>(normal[2]);


				//bone_influences_per_control_point influences_per_control_point = bone_influences.at(index_of_control_point);
				//for (size_t index_of_influence = 0; index_of_influence < influences_per_control_point.size(); index_of_influence++)
				//{
				//	if (index_of_influence < MAX_BONE_INFLUENCES)
				//	{
				//		vertex.bone_weights[index_of_influence] = influences_per_control_point.at(index_of_influence).weight;
				//		vertex.bone_indices[index_of_influence] = influences_per_control_point.at(index_of_influence).index;
				//	}
				//	else
				//	{
				//		for (int i = 0; i < MAX_BONE_INFLUENCES; i++)
				//		{
				//			if (vertex.bone_weights[i] < influences_per_control_point.at(index_of_influence).weight)
				//			{
				//				//vertex.bone_weights[i] = influences_per_control_point.at(index_of_influence).weight;
				//				vertex.bone_weights[i] += influences_per_control_point.at(index_of_influence).weight;
				//				vertex.bone_indices[i] = influences_per_control_point.at(index_of_influence).index;
				//				break;
				//			}
				//		}
				//	}
				//}

				FbxStringList uv_names;
				fbx_mesh->GetUVSetNames(uv_names);

				FbxVector2 uv;
				bool unmapped_uv;
				fbx_mesh->GetPolygonVertexUV(index_of_polygon, index_of_vertex, uv_names[0], uv, unmapped_uv);
				vertex.texcoord.x = static_cast<float>(uv[0]);
				vertex.texcoord.y = 1.0f - static_cast<float>(uv[1]);

				vertices.push_back(vertex);
				//indices.push_back(v_count);
				indices.at(index_offset + index_of_vertex) += static_cast<u_int>(v_count);
				v_count += 1;

			}
			s.index_count += 3;
		}





		CreateBuffer(vertices.data(), v_count, indices.data(), v_count, mesh.vertex_buffer.GetAddressOf(), mesh.index_buffer.GetAddressOf());

		////
		//FbxTime::EMode time_mode = fbx_mesh->GetScene()->GetGlobalSettings().GetTimeMode();
		//FbxTime frame_time;
		//frame_time.SetTime(0, 0, 0, 1, 0, time_mode);
		//fetch_bone_matrices(fbx_mesh, mesh.skeletal, frame_time * 20); // pose at frame 20
		////
	}







	scene->Destroy();
	importer->Destroy();
	manager->Destroy();
}


bool SkeltalMesh::CreateBuffer(SkeltalMeshVertexData* v, int v_num, unsigned int* indicies, int ind_num, ID3D11Buffer** v_buffer, ID3D11Buffer** i_buffer)
{
	HRESULT hr;

	D3D11_BUFFER_DESC buffer_desc = {};
	D3D11_SUBRESOURCE_DATA subresource_data = {};

	//vertex buffer作成

	buffer_desc.ByteWidth = sizeof(SkeltalMeshVertexData)*v_num;
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
	subresource_data.pSysMem = indicies;
	subresource_data.SysMemPitch = 0;
	subresource_data.SysMemSlicePitch = 0;
	hr = Framework::device->CreateBuffer(&buffer_desc, &subresource_data, i_buffer);

	return true;
}


void SkeltalMesh::Render(DirectX::XMFLOAT3 pos, float angle, float scale = 1.0f)
{

	//return;

	Vector camera_pos = GameBrain::GetInstance()->GetActiveCameraLocation();
	Vector camera_focus = GameBrain::GetInstance()->GetActiveCameraFocus();
	XMVECTOR eye = XMVectorSet(camera_pos.x, camera_pos.y, camera_pos.z, 1.0f);
	XMVECTOR At = XMVectorSet(camera_focus.x + 0.01f, camera_focus.y, camera_focus.z, 1.0f);


	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	GameBrain::view_mat = XMMatrixLookAtLH(eye, At, Up);
	Scene::projection_mat = XMMatrixPerspectiveFovLH(3.14f / 8.0f, static_cast<float>(Framework::SCREEN_WIDTH) / Framework::SCREEN_HEIGHT, 1.0f, 5000.0f);


	//FLOAT rotate = (FLOAT)(XM_PI * (timeGetTime() % 3000)) / 1500.0f;
	//matY = XMMatrixRotationY(rotate);
	//rotate = (FLOAT)(XM_PI * (timeGetTime() % 1500)) / 750.0f;
	//matX = XMMatrixRotationX(rotate);
	//Scene::world_mat = XMMatrixTranspose(matY * matX);

	//XMMatrixRotationRollPitchYaw


	XMMATRIX world, S, R, T;

	S = XMMatrixScaling(scale, scale, scale);
	R = XMMatrixRotationRollPitchYaw(0, angle, 0);
	T = XMMatrixTranslation(pos.x, pos.y, pos.z);
	world = S * R*T;

	XMFLOAT4X4 wvp;
	XMFLOAT4X4 inverse;
	//XMStoreFloat4x4(&wvp, Scene::world_mat * Scene::view_mat * Scene::projection_mat);
	XMStoreFloat4x4(&wvp, world*GameBrain::view_mat   * Scene::projection_mat);
	XMStoreFloat4x4(&inverse, DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(0, world)));

	for each(auto& mesh in meshes)
	{

		UINT strides = { sizeof(VertexData) };
		UINT offsets[2] = { 0, 0 };
		Framework::device_context->IASetVertexBuffers(0, 1, mesh.vertex_buffer.GetAddressOf(), &strides, offsets);
		Framework::device_context->IASetIndexBuffer(mesh.index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		Framework::device_context->IASetInputLayout(input_layout.Get());
		Framework::device_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Framework::device_context->VSSetShader(vertex_shader.Get(), NULL, 0);
#ifdef GS
		Framework::device_context->GSSetShader(geometry_shader.Get(), NULL, 0);
#endif
		Framework::device_context->PSSetShader(pixel_shader.Get(), NULL, 0);
		Framework::device_context->OMSetDepthStencilState(depth_stencil_state.Get(), 0);
		Framework::device_context->RSSetState(rasterizer_state.Get());
		FLOAT BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };



		for (auto& s : mesh.subsets)
		{
			ConstantBuffer cb;

			cb.world_view_projection = wvp;
			cb.world_inverse_transpose = inverse;

			//DirectX::XMStoreFloat4x4(&cb.world_view_projection, DirectX::XMLoadFloat4x4(&wvp));


			/*cb.world_view_projection = wvp;*/
			//DirectX::XMStoreFloat4x4(&cb.world_inverse_transpose, DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(0, world)));

			//cb.world_inverse_transpose = inverse;
			//DirectX::XMStoreFloat4x4(&cb.world_inverse_transpose, world * DirectX::XMLoadFloat4x4(&inverse));
			cb.material_color = s.diffuse.color;
			//cb.material_color.w = 1.0f;
			//cb.material_color = { 1.0f,1.0f,1.0f ,1.0f };
			cb.light_direction = { 0, 0, -1.0f,1.0f };
			cb.ambient_color = DirectX::XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
			cb.camera_location = DirectX::XMFLOAT4(camera_pos.x, camera_pos.y, camera_pos.z, 1);
			Framework::device_context->UpdateSubresource(constant_buffer.Get(), 0, NULL, &cb, 0, 0);
			Framework::device_context->VSSetConstantBuffers(0, 1, constant_buffer.GetAddressOf());
			Framework::device_context->PSSetConstantBuffers(0, 1, constant_buffer.GetAddressOf());
			Framework::device_context->PSSetShaderResources(0, 1, s.diffuse.srv.GetAddressOf());
			Framework::device_context->PSSetShaderResources(1, 1, shader_structure->srv.GetAddressOf());

			Framework::device_context->PSSetSamplers(0, 1, sampler_state.GetAddressOf());

			Framework::device_context->DrawIndexed(s.index_count, s.index_start, 0);
		}
	}
}