#pragma once

#include "source\system\object\3d\FBX.h"
#include "source\math\yuki_math.h"
#include <memory>
#include <list>



class Effect
{
public:
	Effect(DirectX::XMFLOAT3 pos, float scale, std::shared_ptr<StaticMesh> effect0, std::shared_ptr<StaticMesh> effect1, std::shared_ptr<StaticMesh> effect2, std::shared_ptr<StaticMesh> effect3, std::shared_ptr<StaticMesh> effect4) :
		pos(pos),
		scale(scale)
	{
		effect[0] = effect0;
		effect[1] = effect1;
		effect[2] = effect2;
		effect[3] = effect3;
		effect[4] = effect4;
	}
	~Effect() {}
private:
	std::shared_ptr<StaticMesh> effect[5];

public:
	int current_effect_num = 0;
	const int speed = 5;
	int time{};
	DirectX::XMFLOAT3 pos;
	float scale;

	bool Update()
	{
		time++;
		if (time > speed)
		{
			time = 0;
			current_effect_num++;

		}
		if (current_effect_num > 4)
			return true;
		return false;
	}

	
	void Render()
	{
		if (current_effect_num < 5)
		{
			effect[current_effect_num]->Render(1.0/60.0f,pos, PI/2.0f, scale);
		}
	}
};


class EffectManager
{
public:
	EffectManager() {}
	~EffectManager() {}

private:
	static std::list<std::unique_ptr<Effect>> effect_list;
	static std::shared_ptr<StaticMesh> effect[5];
public:

	static void Initialize()
	{
		effect[0] = std::make_shared<StaticMesh>("DATA\\3D\\Effect\\e0.fbx");
		effect[1] = std::make_shared<StaticMesh>("DATA\\3D\\Effect\\e1.fbx");
		effect[2] = std::make_shared<StaticMesh>("DATA\\3D\\Effect\\e2.fbx");
		effect[3] = std::make_shared<StaticMesh>("DATA\\3D\\Effect\\e3.fbx");
		effect[4] = std::make_shared<StaticMesh>("DATA\\3D\\Effect\\e4.fbx");
	}

	static void Update()
	{
		for (auto& it = effect_list.begin(); it != effect_list.end();/**/)
		{
			if ((*it)->Update())
			{
				it = effect_list.erase(it);

			}
			else it++;
		}
	}

	static void AddEffect(DirectX::XMFLOAT3 pos, float scale)
	{
		effect_list.emplace_back(std::make_unique<Effect>(pos, scale,effect[0], effect[1], effect[2], effect[3], effect[4]));
	}

	static void Render()
	{
		for each(auto& eff in effect_list)
		{
			eff->Render();
		}
	}
};