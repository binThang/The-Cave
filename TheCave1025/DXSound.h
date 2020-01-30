#pragma once

#define WIN32_LEAN_AND_MEAN



#include "DXSoundProto.h"
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>


#ifndef __DIRTSND_H
#define __DIRTSND_H



class CDirectSound
{
public:
	CDirectSound(HWND);
	~CDirectSound(void);
	void Play(int index);
	void Loop(int index);
	void Stop(int index);
	void StopAll();
	BOOL IsPlaying(int index);
	BOOL IsLooping(int index);
	void SetPan(int index,long pan);
	void GetPan(int index,long& pan);
	void SetVol(int index,long vol);
	void GetVol(int index,long& vol);
	void SetFreq(int index,DWORD freq);
	void GetFreq(int index,DWORD& freq);
	void SetWavSize(int num);
	void LoadWav(LPSTR wav,int index);

	//static CDirectSound getSingleton();
	static CDirectSound* CDirectSound::getSingleton()
	{
		static CDirectSound* instance;
		return instance;
	}

private:
	BOOL IsBufIndex(int index);
	void DirectSoundInitt(void);
	void DirectSoundError(LPSTR Message);
	void DSObjectRelease(void);

private:
	HWND m_hWnd;
	LPDIRECTSOUND m_lpDS;
	LPDIRECTSOUNDBUFFER* m_lpDSBuf;
	int m_iBufCount; // 버퍼의 갯수 (WAV)
	int m_iRefCount;
};

#endif

/*
Volume -10000 ~ 0 (작다 ~ 크다, -2000 ~ 0)
Pan -10000 ~ 10000 ( 좌 ~ 우 )
Frequency 100 ~ 100000 (느림 ~ 빠름, 보통 속도는 약 11000)
*초기값은 0
*/





