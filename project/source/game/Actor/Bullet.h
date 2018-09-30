#pragma once
#include "source\game\Actor\Actor.h"
class Bullet :public Actor
{
public:
	Bullet(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 move, std::shared_ptr<StaticMesh> mesh) :
		Actor(mesh),
		time(0),
		is_end(false),
		move(move)
	{
		position = pos;
		angle = 3.141592f;
		
		
	}
	virtual ~Bullet() {}
private:
	int time;

	DirectX::XMFLOAT3 move;
public:

	bool is_end;
	virtual void Update()
	{
		time++;
		if (time >= 60 * 5)
		{
			is_end = true;
		}


		//XMFLOAT3に+=オペレータがないなんて聞いてない
		position.x += move.x;
		position.y += move.y;
		position.z += move.z;
	}



};