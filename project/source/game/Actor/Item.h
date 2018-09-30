#pragma once
#include "source\game\Actor\Player.h"
class ItemBase :public Actor
{
public:
	ItemBase(const char* filename,Player* ref):
		Actor(filename),
		player_ref(ref)
	{}
	virtual ~ItemBase() {}
protected:
	Player* const player_ref;
public:

	virtual bool Update()
	{
		VECTORIII p = player_ref->GetActorLocation();
		VECTORIII i = GetActorLocation();

		position.x -= 0.3f;
		if ((p - i).Length() < 5.0f)
		{
			Activate();
		}
	}

	virtual void Activate()=0;
};


class ItemManager
{

};


class OneUpItem final :public ItemBase
{
public:
	OneUpItem(Player* ref):
		ItemBase("DATA\\3D\\inochi.fbx", ref)
	{}
	~OneUpItem() {}
private:
	
public:
	
	void Activate()
	{
		
	}


};
