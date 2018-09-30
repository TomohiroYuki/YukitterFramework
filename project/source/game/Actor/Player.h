//#pragma once
//#include "source\game\Actor\MainCharacter.h"
//#include "source\game\Actor\Bullet.h"
//#include "source\system\UI\Widget.h"
////#include "source\game\Actor\Enemy.h"
//#include <list> 
//
//class Player final :public MainCharacter
//{
//public:
//	Player(const char* filename, float camera_length):
//		MainCharacter(filename,camera_length)
//	{
//		shot_method = std::make_unique<SingleShot>(this);
//		bullet_mesh = std::make_unique<StaticMesh>("DATA\\3D\\tama.fbx");
//		inochi		= std::make_unique<Sprite>(L"DATA\\2D\\inochi.png");
//	}
//private:
//	std::list<std::unique_ptr<Bullet>>	bullet_list;
//	std::shared_ptr<StaticMesh>			bullet_mesh;
//	std::shared_ptr<Sprite>				inochi;
//public:
//	int life=3;
//
//	class ShotMethod
//	{
//	public:
//		ShotMethod(){}
//		~ShotMethod() {}
//	private:
//	public:
//		virtual void Shot() = 0;
//	};
//
//	class SingleShot final :public ShotMethod
//	{
//	public:
//		SingleShot(Player* const p_ref):
//			player_reference(p_ref)
//		{}
//		~SingleShot() {}
//	private:
//		Player* const player_reference;
//
//	public:
//		void Shot()
//		{
//			if (InputBrain::getInstance()->XConGet(XINPUT_GAMEPAD_B) == 3|| InputBrain::getInstance()->KeyGet(DIK_SPACE)==3)
//			{
//				player_reference->bullet_list.emplace_back(std::make_unique<Bullet>(player_reference->position,DirectX::XMFLOAT3(-1,0,0) , player_reference->bullet_mesh));
//			}
//		}
//	};
//
//	
//
//	std::unique_ptr<ShotMethod> shot_method;
//	std::unique_ptr<GaugeWidget> gauge_widget;
//
//	void Update();
//
//	void Render()
//	{
//		if(life>0)
//		MainCharacter::Render();
//
//		for each(auto& bullet in bullet_list)
//		{
//			bullet->Render();
//		}
//
//		for (int i = 0; i < life; i++)
//		{
//			inochi->Render({static_cast<float>(0+(64)*i),650}, {64,64}, {0,0}, {64,64}, {}, 0);
//		}
//	}
//
//};