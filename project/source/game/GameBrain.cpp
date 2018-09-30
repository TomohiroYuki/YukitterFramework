#include "source\game\GameBrain.h"
#include "source\game\scene\SceneZero.h"
#include "source\game\scene\SceneTitle.h"



Yukitter::YQCamera* GameBrain::active_camera_reference;
DirectX::XMMATRIX  GameBrain::view_mat;


void GameBrain::Update()
{
	
}

void GameBrain::Initialize()
{
	if (is_initialized)return;
	default_camera = std::make_unique<Yukitter::YQCamera>();
	active_camera_reference = default_camera.get();
	scene = std::make_unique<SceneZero>();
	scene->Initialize();
	load = std::make_unique<Sprite>(L"DATA\\2D\\yomi.png");
	win = std::make_unique<Sprite>(L"DATA\\2D\\win.png");
	lose = std::make_unique<Sprite>(L"DATA\\2D\\lose.png");
	is_initialized = true;
}
