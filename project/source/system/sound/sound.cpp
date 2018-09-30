#include "source\system\sound\sound.h"
#include <mmsystem.h>
#include <Windows.h>
#pragma comment(lib,"winmm.lib")
#include "source\system\ResourceBrain.h"



//英語のコメントはMSDN公式より引用。
bool SoundBrain::ExtendWave(wchar_t* filename, WAVEFORMATEX &waveFormatEx, char** ppData, DWORD &dataSize)
{
	HMMIO hmmio = nullptr;
	MMIOINFO mmioinfo;
	memset(&mmioinfo, 0, sizeof(MMIOINFO));

	hmmio = mmioOpen(filename, &mmioinfo, MMIO_READ);
	if (hmmio == nullptr)
	{
		throw "Failed to open sound file.";
	}

	// search RIFF chunk 
	MMRESULT mmRes;
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmRes = mmioDescend(hmmio, &riffChunk, NULL, MMIO_FINDRIFF);
	if (mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hmmio, 0);
		throw "failed to search RIFF chunk.";
	}

	// search format chunk
	MMCKINFO format_chunk;

	format_chunk.ckid = mmioFOURCC('f', 'm', 't', ' ');

	mmRes = mmioDescend(hmmio, &format_chunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hmmio, 0);
		throw "failed to search format chunk.";
	}
	//WAVEFORMATEX waveFormatEx;

	DWORD fmsize = format_chunk.cksize;
	DWORD size = mmioRead(hmmio, (HPSTR)&waveFormatEx, fmsize);
	if (size != fmsize) 
	{
		mmioClose(hmmio, 0);
		throw "failed to mmioRead.";
	}

	mmioAscend(hmmio, &format_chunk, 0);


	mmioAscend(hmmio, &format_chunk, 0);

	// search data chunk
	MMCKINFO data_chunk;

	data_chunk.ckid = mmioFOURCC('d', 'a', 't', 'a');

	mmRes = mmioDescend(hmmio, &data_chunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR) 
	{
		mmioClose(hmmio, 0);
		throw "not find data_chunk";
	}

	*ppData = new char[data_chunk.cksize];

	size = mmioRead(hmmio, (HPSTR)*ppData, data_chunk.cksize);
	if (size != data_chunk.cksize) 
	{
		delete[] * ppData;
		throw "faild to write";
	}
	dataSize = size;

	// ハンドルクローズ
	mmioClose(hmmio, 0);
	return true;
}

//サウンドをロード、sound_mapに格納。キーの重複は許可しない。
void SoundBrain::LoadSound(wchar_t* filename, int key_number)
{
	if (searchSound(key_number))
	{
		throw "サウンドキーコードの重複";
	}
	WAVEFORMATEX wave_format_ex;
	char *wave_data = 0;
	DWORD wave_size = 0;
	if (!ExtendWave(filename, wave_format_ex, &wave_data, wave_size))
	{
		throw "wave失敗";
		return;
	}


	// Set up DSBUFFERDESC structure. 
	//HRESULT hr;
	DSBUFFERDESC dsbdesc;
	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
	dsbdesc.lpwfxFormat = &wave_format_ex;
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS;
	dsbdesc.dwBufferBytes = wave_size;
	dsbdesc.guid3DAlgorithm = GUID_NULL;
	// Create buffer. 
	IDirectSoundBuffer8 *pDSBuffer;
	HRESULT hr = sound_device->CreateSoundBuffer(&dsbdesc, &primary_buffer, NULL);
	if (SUCCEEDED(hr))
	{
		hr = primary_buffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pDSBuffer);
		primary_buffer->Release();
	}



	IDirectSoundBuffer *ptmpBuf = 0;

	hr=sound_device->CreateSoundBuffer(&dsbdesc, &ptmpBuf, NULL);
	if (FAILED(hr))
	{
		throw(0);
	}
	ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&pDSBuffer);
	ptmpBuf->Release();

	LPVOID lpvWrite = 0;
	DWORD dwLength = 0;
	if (DS_OK == pDSBuffer->Lock(0, 0, &lpvWrite, &dwLength, NULL, NULL, DSBLOCK_ENTIREBUFFER))
	{
		memcpy(lpvWrite, wave_data, dwLength);
		pDSBuffer->Unlock(lpvWrite, dwLength, NULL, 0);
	}

	sound_map.insert(std::make_pair(key_number, pDSBuffer));
	delete[] wave_data;

}





