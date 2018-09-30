#include "source\game\scene\SceneZero.h"

void SceneZero::Initialize()
{

	//yuppi  = std::make_unique<SkeltalMesh>("DATA\\3D\\yuppi_wait.fbx");
	yuppi = std::make_unique<StaticMesh>("DATA\\3D\\gune1.fbx");

	camera = std::make_unique<ViewerCamera>();
	GameBrain::ActivateCamera(camera.get());

	

}


void SceneZero::Render(float dt)
{
	yuppi->Render(dt ,DirectX::XMFLOAT3(0, 30, 0), 0, 10);
}