
#include "DXSound.h"
#pragma comment( lib, "dsound" )



/////////////////////////////////////////
//
// ���̷�Ʈ ���� Ŭ����
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
	// ���̷�Ʈ ���� ��ü����
	HRESULT dsrval = ::DirectSoundCreate(NULL, &m_lpDS, NULL);
	if (dsrval != DS_OK) DirectSoundError("��ü ���� ����");
	// ���̷�Ʈ ���� ��� ȯ���� �����Ѵ�.
	dsrval = m_lpDS->SetCooperativeLevel(m_hWnd, DSSCL_NORMAL);
	if (dsrval != DS_OK) DirectSoundError("��� ���� ����");
}

void CDirectSound::DirectSoundError(LPSTR Message)
{
	if (m_lpDS) DSObjectRelease();
	MessageBox(m_hWnd, Message, "���̷�Ʈ ����", MB_OK);
}

void CDirectSound::DSObjectRelease()
{
	StopAll();
	if(m_lpDSBuf)
		delete m_lpDSBuf;
	m_lpDS->Release();
}

// ���� �Ҹ� ȭ���� ������� �����Ѵ�.
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

// wavȭ���� �о directsound buffer�� ���� �ִ´�.
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

	// ȭ���� ����
	hmmioIn=mmioOpen((LPSTR)wav, NULL, MMIO_ALLOCBUF | MMIO_READ);
	if (!hmmioIn) DirectSoundError("WAV ȭ���� ������ ����");

	// ����ȭ���� RIFF WAVEȭ������ Ȯ���Ѵ�
	ckInfoRIFF.fccType = mmioFOURCC('W','A','V','E');
	if (mmioDescend(hmmioIn, &ckInfoRIFF, NULL, MMIO_FINDRIFF) != 0)
	{
		DirectSoundError("RIFF WAVE ȭ���� �ƴմϴ�");
	}

	// 'fmt' Chunk���� Ȯ���Ѵ�
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (mmioDescend(hmmioIn, &ckInfo,&ckInfoRIFF, MMIO_FINDCHUNK) != 0)
	{
		DirectSoundError("ȭ���� fmt Chunk�� �ƴմϴ�");
	}

	// ����ȭ���� �д´�
	ret = mmioRead(hmmioIn, (HPSTR) &pcmWaveFormat, (long) sizeof(pcmWaveFormat));
	if (ret != (long) sizeof(pcmWaveFormat))
	{
		DirectSoundError("ȭ�� �б� ����");
	}

	// ���� ȭ���� PCM�������� Ȯ���Ѵ�
	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
		wExtraAlloc = 0;
	else
	{
		ret = mmioRead(hmmioIn, (LPSTR) &wExtraAlloc,(long) sizeof(wExtraAlloc));
		if (ret != (long) sizeof(wExtraAlloc))
		{
			DirectSoundError("ȭ�� �б� ����");
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
			DirectSoundError("ȭ�� �б� ����");
		}
	}

	if (mmioAscend(hmmioIn, &ckInfo, 0) != MMSYSERR_NOERROR)
	{
		DirectSoundError("����");
	}


	if (mmioSeek(hmmioIn, ckInfoRIFF.dwDataOffset+sizeof(FOURCC),SEEK_SET) == -1)
	{
		DirectSoundError("����");
	}

	// 'data' Chunk�� ã�´�
	MMCKINFO pckIn;
	pckIn.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(hmmioIn,&pckIn,&ckInfoRIFF, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		DirectSoundError("Data Chunk�� �ƴմϴ�");
	}

	dwDataSize = pckIn.cksize;
	lpData = NULL;

	// ����ƽ 2�� ���۸� ����� ���� ����ü�� �����Ѵ�.
	// ���� ������ ����� ����, �¿� �뷱��, ���ļ� ������ �����ϵ��� �Ѵ�
	memset(&dsbd, 0, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC;
	dsbd.dwBufferBytes = dwDataSize;
	dwWavSize = lpWaveFormat->cbSize + sizeof(WAVEFORMATEX);

	dsbd.lpwfxFormat = (LPWAVEFORMATEX) malloc(dwWavSize);
	memcpy( dsbd.lpwfxFormat, lpWaveFormat, dwWavSize );
	free(lpWaveFormat);

	// 2�� ���� ���۸� �����Ѵ�.
	if (m_lpDS->CreateSoundBuffer(&dsbd, &m_lpDSBuf[index],NULL) != DS_OK)
	{
		DirectSoundError("������� ��������");
	}
	free(dsbd.lpwfxFormat);

	// ������ ���ۿ� �����Ѵ�
	ret = m_lpDSBuf[index]->Lock(0, dwDataSize, (LPVOID *)&lpData,&dwBSize,
		&lpWrapPtr, &dwWrapBSize, 0L);
	if (ret != DS_OK)
	{
		DirectSoundError("����");
	}
	dwDataSize = dwBSize;

	// ����ȭ���� ����(�����Ȳ)�� �˾ƿ´�
	if (mmioGetInfo(hmmioIn, &mmioinfoIn, 0) != MMSYSERR_NOERROR)
	{
		DirectSoundError("����");
	}

	DataIn = dwDataSize;
	if (DataIn > pckIn.cksize) DataIn = pckIn.cksize;
	pckIn.cksize -= DataIn;

	for (i = 0; i < DataIn; i++)
	{
		if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
		{
			ret = mmioAdvance(hmmioIn, &mmioinfoIn, MMIO_READ);
			if (ret != MMSYSERR_NOERROR) DirectSoundError("����");
		}
		*((BYTE*)lpData + i) = *((BYTE*)mmioinfoIn.pchNext++);
	}
	if (mmioSetInfo(hmmioIn, &mmioinfoIn, 0) != MMSYSERR_NOERROR)
	{
		DirectSoundError("����");
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
		m_lpDSBuf[index]->SetCurrentPosition(0); // ���ϰ� ó�� ����
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



