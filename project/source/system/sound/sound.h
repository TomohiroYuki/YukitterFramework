#pragma once
#include <wrl.h>
#pragma comment(lib,"dsound.lib")
#include <map>
#include <d3d11.h>
#include "source\system\sound\dsound.h"


class SoundBrain
{

	SoundBrain() = default;
	~SoundBrain() = default;
public:
	// Singleton
	SoundBrain(const SoundBrain&) = delete;					
	SoundBrain& operator=(const SoundBrain&) = delete;		
	SoundBrain(SoundBrain&&) = delete;						
	SoundBrain& operator=(SoundBrain&&) = delete;			

	void Initialize(HWND hwnd) 
	{
		HRESULT hr = DirectSoundCreate8(nullptr, sound_device.GetAddressOf(), nullptr);
		sound_device->SetCooperativeLevel(hwnd, DSSCL_NORMAL);
	}
	Microsoft::WRL::ComPtr<IDirectSound8>	sound_device;
	LPDIRECTSOUNDBUFFER primary_buffer;
	std::map<int, IDirectSoundBuffer8* > sound_map;

	void SoundPlay(int key, bool is_se)
	{
		DWORD statues;
		if (!searchSound(key))return;
		sound_map[key]->GetStatus(&statues);
		if (statues&DSBSTATUS_PLAYING)
		{
			LPDIRECTSOUNDBUFFER copy_buffer;

			HRESULT hr = sound_device->DuplicateSoundBuffer(sound_map[key], &copy_buffer);
			if (FAILED(hr))
			{
				throw "failed to copy";
			}
			(copy_buffer)->Play(0, 0, is_se);
		}
		else sound_map[key]->Play(0, 0, is_se);

	}

public:

	

	bool ExtendWave(wchar_t* filename, WAVEFORMATEX &waveFormatEx, char** ppData, DWORD &dataSize);
	void LoadSound(wchar_t* filename,int key_number);
	

	IDirectSoundBuffer8* GetSoundBuffer(int sound_id)
	{
		return sound_map.find(sound_id)->second;
	}

	bool searchSound(int sound_id)
	{
		if (sound_map.count(sound_id) != 0)return true;
		return false;
	}

	void SE_Play(int key)
	{
		SoundPlay(key, false);
	}

	void BGM_Play(int key)
	{
		SoundPlay(key, true);
	}


	static SoundBrain* getInstance()
	{
		static SoundBrain inst;			// privateなコンストラクタを呼び出す
		return &inst;
	}
};
#define SOUND_BRAIN (SoundBrain::getInstance())