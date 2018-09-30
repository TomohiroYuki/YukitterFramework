#pragma once

#include "source\game\scene\SceneMain.h"

#include "source\game\Actor\MainCharacter.h"
#include "source\game\YQCamera.h"
#include "source\game\GameBrain.h"
class SceneTitle final :public Scene
{
public:
	SceneTitle()
	{
		//logo = std::make_unique<MainCharacter>("DATA\\3D\\hyoudai.fbx",3.0f);
		t= std::make_unique<Sprite>(L"DATA\\2D\\text.png");
		
	}
	~SceneTitle() {}
private:
	//std::unique_ptr<MainCharacter> logo;
	std::unique_ptr<Sprite> t;
public:

	void Update()
	{
		//logo->Update();

		if (InputBrain::getInstance()->KeyGet(DIK_SPACE) || InputBrain::getInstance()->XConGet(XINPUT_GAMEPAD_B))
		{
			GameBrain::GetInstance()->ChangeScene(new SceneMain);
		}
	}

	void Render()
	{
		//logo->SetScale(2.8f);
		//logo->Render();
		t->Render({650,650}, {512,128}, {}, {  512,128 }, {}, 0);
	}
};