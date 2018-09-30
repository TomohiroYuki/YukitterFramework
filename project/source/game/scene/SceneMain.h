#pragma once
#include <memory>
#include "source\game\GameBrain.h"
#include "source\game\scene\Scene.h"
#include "source\system\object\Sprite\Sprite.h"
#include "source\system\object\primitive\Primitive.h"
#include "source\system\object\3d\FBX.h"
#include "source\game\YQCamera.h"
//#include "source\game\Actor\MainCharacter.h"
//#include "source\game\Actor\Player.h"
//#include "source\game\Actor\Enemy.h"
//#include "source\system\Effect\Effect.h
#include "source\game\Stage.h"


class SceneMain final :public Scene
{
public:
	SceneMain()
	{
		sprite = std::make_unique<Sprite>(L"DATA\\2D\\way.png");
		//cube = std::make_unique<Primitive_Cube>();
		//cube2 = std::make_unique<StaticMesh>("DATA\\3D\\003_cube.fbx");
		//cube4 = std::make_unique<HOGE>("DATA\\3D\\005_cube.fbx");
		cube3  = std::make_unique<StaticMesh>("DATA\\3D\\Effect\\e0.fbx");
		//cube2 = std::make_unique<StaticMesh>("DATA\\3D\\yuppi_wait.fbx");
		camera = std::make_unique<Yukitter::YQCamera>();


		//character = std::make_unique<Player>("DATA\\3D\\watakusi.fbx",7.0f);
		tips = std::make_unique<Sprite>(L"DATA\\2D\\tips.png");
		//時間がなかったのでスーパー雑static実装____
		//EnemyManager::Initialize(character.get());
		//EffectManager::Initialize();
		//StageManager::Initialize(character.get());
		//____________________________________
		//EnemyManager::SpawnEnemy(std::make_unique<E2_YuppiY>(DirectX::XMFLOAT3(0,0,0), character.get()));
		//EnemyManager::enemies_list.emplace_back(std::make_unique<Enemy_ECC>(DirectX::XMFLOAT3(-500, 0, 0), character.get()));
	
		GameBrain::GetInstance()->Reset();
	}
	~SceneMain() {}
private:
	std::unique_ptr<Sprite>				sprite;
	std::unique_ptr<Yukitter::YQCamera>			camera;
	//std::unique_ptr<Player>				character;
	std::unique_ptr<StaticMesh>			cube3;

	std::unique_ptr<Sprite>				tips;
	
public:

	void Update()
	{
		camera->Update();
		//character->Update();
		//EnemyManager::Update();
		///EffectManager::Update();
		GameBrain::GetInstance()->Update();;

	}

	void Render(float dt)
	{
		//cube2->Render(*camera);
		//cube2->Render(*camera.get(),);
		//cube3->Render({0,0,0},0,80.0f);
		//cube4->Render(*camera.get());
		//StageManager::Render();
		//EnemyManager::Render();
		//character->Render();
		//EffectManager::Render();
		GameBrain::GetInstance()->ResultRender();
		tips->Render({600,600}, {1024,128}, {}, { 1024,128 }, {}, 0);
		//sprite->Render({}, {1280/4,640/4}, {}, {2048,1024}, {}, 0);
	}
};