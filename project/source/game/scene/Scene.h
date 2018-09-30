#pragma once
#include <DirectXMath.h>


class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}
private:
public:
	virtual void Initialize() {};
	virtual void Update() = 0;
	virtual void Render(float dt) = 0;


	
	
	static DirectX::XMMATRIX projection_mat;

};