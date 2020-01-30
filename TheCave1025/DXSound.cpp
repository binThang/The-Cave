
#include "DXSound.h"
#pragma comment( lib, "dsound" )



/////////////////////////////////////////
//
// 다이렉트 사운드 클래스
//
/////////////////////////////////////////



CDirectSound::CDirectSound(HWND hWindow)
{
	m_lpDSBuf = 0;
	m_iBufCount= 0;
	m_hWnd = hWindow;
	DirectSoundInitt();
}

CDirectSound::~CDirectSound()
{
	if (m_lpDS) DSObjectRelease();
}

void CDirectSound::DirectSoundInitt(void)
{
	// 다이렉트 사운드 객체생성
	HRESULT dsrval = ::DirectSoundCreate(NULL, &m_lpDS, NULL);
	if (dsrval != DS_OK) DirectSoundError("객체 생성 실패");
	// 다이렉트 사운드 사용 환경을 지정한다.
	dsrval = m_lpDS->SetCooperativeLevel(m_hWnd, DSSCL_NORMAL);
	if (dsrval != DS_OK) DirectSoundError("모드 설정 실패");
}

void CDirectSound::DirectSoundError(LPSTR Message)
{
	if (m_lpDS) DSObjectRelease();
	MessageBox(m_hWnd, Message, "다이렉트 사운드", MB_OK);
}

void CDirectSound::DSObjectRelease()
{
	StopAll();
	if(m_lpDSBuf)
		delete m_lpDSBuf;
	m_lpDS->Release();
}

// 읽을 소리 화일이 몇개인지를 지정한다.
void CDirectSound::SetWavSize(int num)
{
	if(num<0)
	{
		m_iBufCount = 0;
		return;
	}

	m_iBufCount = num;
	m_lpDSBuf = new LPDIRECTSOUNDBUFFER[m_iBufCount];
}

// wav화일을 읽어서 directsound buffer에 집어 넣는다.
void CDirectSound::LoadWav(LPSTR wav,int index)
{
	int ret;
	WORD wExtraAlloc;
	UINT i, DataIn;

	HMMIO hmmioIn;
	MMIOINFO mmioinfoIn;
	MMCKINFO ckInfo, ckInfoRIFF;
	LPWAVEFORMATEX lpWaveFormat=0;
	PCMWAVEFORMAT pcmWaveFormat;

	LPBYTE lpData;
	LPVOID lpWrapPtr;
	DWORD dwBSize, dwWavSize, dwDataSize, dwWrapBSize;

	DSBUFFERDESC dsbd;

	// 화일을 연다
	hmmioIn=mmioOpen((LPSTR)wav, NULL, MMIO_ALLOCBUF | MMIO_READ);
	if (!hmmioIn) DirectSoundError("WAV 화일을 읽을수 없음");

	// 열린화일이 RIFF WAVE화일인지 확인한다
	ckInfoRIFF.fccType = mmioFOURCC('W','A','V','E');
	if (mmioDescend(hmmioIn, &ckInfoRIFF, NULL, MMIO_FINDRIFF) != 0)
	{
		DirectSoundError("RIFF WAVE 화일이 아닙니다");
	}

	// 'fmt' Chunk인지 확인한다
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (mmioDescend(hmmioIn, &ckInfo,&ckInfoRIFF, MMIO_FINDCHUNK) != 0)
	{
		DirectSoundError("화일이 fmt Chunk가 아닙니다");
	}

	// 열린화일을 읽는다
	ret = mmioRead(hmmioIn, (HPSTR) &pcmWaveFormat, (long) sizeof(pcmWaveFormat));
	if (ret != (long) sizeof(pcmWaveFormat))
	{
		DirectSoundError("화일 읽기 실패");
	}

	// 읽은 화일이 PCM형식인지 확인한다
	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
		wExtraAlloc = 0;
	else
	{
		ret = mmioRead(hmmioIn, (LPSTR) &wExtraAlloc,(long) sizeof(wExtraAlloc));
		if (ret != (long) sizeof(wExtraAlloc))
		{
			DirectSoundError("화일 읽기 실패");
		}
	}

	lpWaveFormat = (LPWAVEFORMATEX) malloc(sizeof(WAVEFORMATEX)+wExtraAlloc);
	memcpy(lpWaveFormat, &pcmWaveFormat, sizeof(pcmWaveFormat));
	lpWaveFormat->cbSize = wExtraAlloc;

	if (wExtraAlloc != 0)
	{
		ret = mmioRead(hmmioIn,
			(LPSTR)(((BYTE*)&(lpWaveFormat->cbSize))+sizeof(wExtraAlloc)),
			(long)(wExtraAlloc));
		if (ret != (long) sizeof(wExtraAlloc))
		{
			DirectSoundError("화일 읽기 실패");
		}
	}

	if (mmioAscend(hmmioIn, &ckInfo, 0) != MMSYSERR_NOERROR)
	{
		DirectSoundError("오류");
	}


	if (mmioSeek(hmmioIn, ckInfoRIFF.dwDataOffset+sizeof(FOURCC),SEEK_SET) == -1)
	{
		DirectSoundError("오류");
	}

	// 'data' Chunk를 찾는다
	MMCKINFO pckIn;
	pckIn.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(hmmioIn,&pckIn,&ckInfoRIFF, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		DirectSoundError("Data Chunk가 아닙니다");
	}

	dwDataSize = pckIn.cksize;
	lpData = NULL;

	// 스태틱 2차 버퍼를 만들기 위해 구조체를 생성한다.
	// 사운드 버퍼의 제어는 볼륨, 좌우 밸런스, 주파수 조절이 가능하도록 한다
	memset(&dsbd, 0, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC;
	dsbd.dwBufferBytes = dwDataSize;
	dwWavSize = lpWaveFormat->cbSize + sizeof(WAVEFORMATEX);

	dsbd.lpwfxFormat = (LPWAVEFORMATEX) malloc(dwWavSize);
	memcpy( dsbd.lpwfxFormat, lpWaveFormat, dwWavSize );
	free(lpWaveFormat);

	// 2차 사운드 버퍼를 생성한다.
	if (m_lpDS->CreateSoundBuffer(&dsbd, &m_lpDSBuf[index],NULL) != DS_OK)
	{
		DirectSoundError("사운드버퍼 생성실패");
	}
	free(dsbd.lpwfxFormat);

	// 생성된 버퍼에 기입한다
	ret = m_lpDSBuf[index]->Lock(0, dwDataSize, (LPVOID *)&lpData,&dwBSize,
		&lpWrapPtr, &dwWrapBSize, 0L);
	if (ret != DS_OK)
	{
		DirectSoundError("오류");
	}
	dwDataSize = dwBSize;

	// 열린화일의 상태(진행상황)을 알아온다
	if (mmioGetInfo(hmmioIn, &mmioinfoIn, 0) != MMSYSERR_NOERROR)
	{
		DirectSoundError("오류");
	}

	DataIn = dwDataSize;
	if (DataIn > pckIn.cksize) DataIn = pckIn.cksize;
	pckIn.cksize -= DataIn;

	for (i = 0; i < DataIn; i++)
	{
		if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
		{
			ret = mmioAdvance(hmmioIn, &mmioinfoIn, MMIO_READ);
			if (ret != MMSYSERR_NOERROR) DirectSoundError("오류");
		}
		*((BYTE*)lpData + i) = *((BYTE*)mmioinfoIn.pchNext++);
	}
	if (mmioSetInfo(hmmioIn, &mmioinfoIn, 0) != MMSYSERR_NOERROR)
	{
		DirectSoundError("오류");
	}
}

////////

BOOL CDirectSound::IsBufIndex(int index)
{
	if (index > 0 && index <= m_iBufCount)
		return TRUE;
	else
		return FALSE;
}

void CDirectSound::Play(int index)
{
	if (IsBufIndex(index))
	{
		m_lpDSBuf[index]->SetCurrentPosition(0); // 리턴값 처리 않함
		m_lpDSBuf[index]->Play(0, 0, 0); //
	}
}

void CDirectSound::Loop(int index)
{
	if (IsBufIndex(index))
	{
		m_lpDSBuf[index]->SetCurrentPosition(0);
		m_lpDSBuf[index]->Play(0, 0, DSBPLAY_LOOPING);
	}
}

void CDirectSound::Stop(int index)
{
	if (IsBufIndex(index)) m_lpDSBuf[index]->Stop();
}

void CDirectSound::StopAll()
{
	for (int i=0; i < m_iBufCount; i++) m_lpDSBuf[i]->Stop();
}

BOOL CDirectSound::IsPlaying(int index)
{
	if (IsBufIndex(index))
	{
		DWORD Status;
		m_lpDSBuf[index]->GetStatus(&Status);
		return Status & DSBSTATUS_PLAYING;
	}
	return FALSE;
}

BOOL CDirectSound::IsLooping(int index)
{
	if (IsBufIndex(index))
	{
		DWORD Status;
		m_lpDSBuf[index]->GetStatus(&Status);
		return Status & DSBSTATUS_LOOPING;
	}
	return FALSE;
}

void CDirectSound::SetPan(int index,long pan)
{
	if (IsBufIndex(index)) m_lpDSBuf[index]->SetPan(pan);
}

void CDirectSound::GetPan(int index,long& pan)
{
	if (IsBufIndex(index)) m_lpDSBuf[index]->GetPan(&pan);
}

void CDirectSound::SetVol(int index,long vol)
{
	if (IsBufIndex(index)) m_lpDSBuf[index]->SetVolume(vol);
}

void CDirectSound::GetVol(int index,long& vol)
{
	if (IsBufIndex(index)) m_lpDSBuf[index]->GetVolume(&vol);
}

void CDirectSound::SetFreq(int index,DWORD freq)
{
	if (IsBufIndex(index)) m_lpDSBuf[index]->SetFrequency(freq);
}

void CDirectSound::GetFreq(int index,DWORD& freq)
{
	if (IsBufIndex(index)) m_lpDSBuf[index]->GetFrequency(&freq);
}



