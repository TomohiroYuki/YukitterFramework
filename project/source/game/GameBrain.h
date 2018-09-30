#pragma once
#include "source\game\YQCamera.h"
#include "source\system\object\sprite\sprite.h"
#include "source\game\scene\Scene.h"

#include <memory>

using namespace Yukitter;

class GameBrain final
{
	// Singleton
	GameBrain() = default;
	~GameBrain() = default;
public:
	// Singleton
	GameBrain(const GameBrain&) = delete;
	GameBrain& operator=(const GameBrain&) = delete;
	GameBrain(GameBrain&&) = delete;
	GameBrain& operator=(GameBrain&&) = delete;
public:
	
private:
	static Yukitter::YQCamera* active_camera_reference;
	std::unique_ptr<Yukitter::YQCamera> default_camera;
	std::unique_ptr<Sprite> load;
	std::unique_ptr<Sprite> win;
	std::unique_ptr<Sprite> lose;
public:
	std::unique_ptr<Scene> scene;
	int timer = 0;
	void Initialize();


	enum GAME_STATE
	{
		PLAYING,
		WIN,
		LOSE
	}game_state= PLAYING;
	
	bool is_initialized = 0;
	static GameBrain* GetInstance()
	{
		static GameBrain inst;
		return &inst;
	}
	void ChangeScene(Scene* new_scene)
	{
		scene.reset(new_scene);
		scene->Initialize();
	}

	void Update();

	static void ActivateCamera(Yukitter::YQCamera* other_camera)
	{
		active_camera_reference = nullptr;
		active_camera_reference = other_camera;
	}

	static Vector GetActiveCameraLocation()
	{
		return active_camera_reference->transform.translation;
	}
	static Vector GetActiveCameraFocus()
	{
		//TODO!!!: FIX
		return Vector(0,50,0);
	}


	static DirectX::XMMATRIX view_mat;


	void LoadingRender()
	{
		load->Render({}, {1280,720}, {}, {1280,720}, {},0);
	}


	void ResultRender()
	{
		switch (game_state)
		{
		case PLAYING:
			break;
		case WIN:
			win->Render({}, {1280,720}, {}, {1280,720}, {},0);
			break;
		case LOSE:
			lose->Render({}, { 1280,720 }, {}, { 1280,720 }, {}, 0);
			break;
		default:
			break;
		}
	}
	

	void Reset()
	{
		timer = 0;
		game_state = PLAYING;

	}

	static Yukitter::YQCamera* GetActiveCameraReference()
	{
		return active_camera_reference;
	}

};