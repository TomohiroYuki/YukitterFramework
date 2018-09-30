#pragma once

#include "source\game\scene\Scene.h"
#include "source\game\scene\SceneTitle.h"
#include "source\game\GameBrain.h"
#include "source\system\object\3d\SkeltalMesh.h"
class SceneZero :public Scene
{
public:
	SceneZero()
	{

		
	}
	~SceneZero() {}
private:
	//std::unique_ptr<SkeltalMesh> yuppi;
	std::unique_ptr<StaticMesh>		yuppi;
	std::unique_ptr<ViewerCamera>	camera;
public:


	void Initialize();
	void Update()
	{
		camera->Update();
	}

	void Render(float dt);
};
