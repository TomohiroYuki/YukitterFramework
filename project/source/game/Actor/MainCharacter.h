//#pragma once
//#include "source\game\Actor\Actor.h"
//#include "source\system\input\Input.h"
//#include "source\game\YQCamera.h"
//#include "source\game\GameBrain.h"
//
//class  MainCharacter  :public   Actor
//{
//public:
//	MainCharacter(const char* filename,float camera_length) :
//		Actor(filename)
//	{
//		//camera = std::make_unique<Game2DCamera>(this, camera_length);
//		//GameBrain::GetInstance()->ActivateCamera(camera.get());
//		scale = 1.0f;
//		angle = 3.141592f;
//	}
//	virtual ~MainCharacter() {}
//private:
//
//public:
//	//ArmCamera
//	//std::unique_ptr<Game2DCamera> camera;
//
//	virtual void Update()
//	{
//		position.x -= InputBrain::getInstance()->GetXConLeftStick().x+InputBrain::getInstance()->GetKeyboardWASD().x;
//		position.y += InputBrain::getInstance()->GetXConLeftStick().y + InputBrain::getInstance()->GetKeyboardWASD().y;
//		//camera->Update();
//	}
//
//	void SetScale(float s)
//	{
//		scale = s;
//	}
//
//
//	virtual void Render()
//	{
//		Actor::Render();
//	}
//
//};