//#pragma once
//#include "source\system\object\3d\FBX.h"
//#include "source\game\Actor\Actor.h"
//#include <memory>
//#include "source\math\yuki_math.h"
//#include "source\system\input\Input.h"
//#include "source\game\Actor\Enemy.h"
//class Stage
//{
//public:
//private:
//public:
//};
//
//class StageManager
//{
//public:
//	StageManager()
//	{
//	}
//
//	~StageManager()
//	{
//	}
//
//private:
//	static std::shared_ptr<StaticMesh> mesh;
//	static Player*  player_ref;
//public:
//	static void Initialize(Player*  p_ref)
//	{
//		mesh = std::make_shared<StaticMesh>("DATA\\3D\\stage_panel.fbx");
//		player_ref = p_ref;
//	}
//	
//
//
//	static void Render()
//	{
//		
//		
//	
//		VECTORIII p_pos = player_ref->GetActorLocation();
//
//		//p_pos.x
//		int plx = static_cast<int>(p_pos.x / (7.99f*3.0f));
//		int ply = static_cast<int>(p_pos.y / (7.99f*3.0f));
//		for (int row = -10; row < 10; row++)
//		{
//			for (int clm = -10; clm < 10; clm++)
//			{
//				mesh->Render({ (row+plx)*7.99f*3.0f,(clm+ ply)*7.99f*3.0f,-5.0f }, 0, 3.0f);
//			}
//		}
//
//
//	}
//
//};
