#pragma once
#include "source\system\object\3d\FBX.h"
//#include "source\game\YQCamera.h"

#include "source\math\Transform.h"
#include <DirectXMath.h>
#include <memory>

//using Matrix4x4 = DirectX::XMFLOAT4X4;
struct Matrix4x4
{

};

//void A()
//{
//	Matrix4x4 m;
//}

using namespace Yukitter;
class Actor
{
public:
	Actor(const char* filename)
	{
		mesh = std::make_unique<StaticMesh>(filename);
	}


	Actor(std::shared_ptr<StaticMesh> copy_mesh)
	{
		
		mesh = copy_mesh;

	}
	virtual ~Actor() 
	{
		
	}
protected:

	Transform transform;


	//std::unique_ptr<StaticMesh> mesh;
	std::shared_ptr<StaticMesh> mesh;
public:
	
	F_INLINE Vector GetActorLocation()
	{
		return transform.translation;
	}


	virtual void Render()
	{
		mesh->Render(1,DirectX::XMFLOAT3(0,0,0),0,1);
	}

};
