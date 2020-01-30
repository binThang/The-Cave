#include "PauseState.h"

Pause::Pause()
{
	ifinit = 0;
	select = 0;
}

void Pause::Update( int &m_iCurrentState, int &m_iCurrentStage, int &m_beforeState )
{
	if(!ifinit){
		init();
		ifinit = 1;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000 && !(select==0) && timet==0){
		select--;
		timet = TERM;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && !(select==3) && timet==0){
		select++;
		timet = TERM;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000){
		if(select==0)
			m_iCurrentState = m_beforeState;
		if(select==2){
			m_iCurrentState = 0;
			Sleep(300);
		}
		if(select==3)
			AllManager::GameON = false;
	}

	for (int i=0; i<4; i++)
	{
		if (select == i)
		{
			m_pauseBG.m_rSource.top = 768*i;
			m_pauseBG.m_rSource.bottom = m_pauseBG.m_rSource.top + 768;
		}
	}

	timet--;
	if (timet <= 0)
		timet = 0;

}

void Pause::Render()
{

	m_pauseBG.Draw();
}

void Pause::init()
{
	m_pauseBG.m_bVisible = true;

	m_pauseBG.m_rSource.left = 0;
	m_pauseBG.m_rSource.top = 0;
	m_pauseBG.m_rSource.right = 1024;
	m_pauseBG.m_rSource.bottom = 768;

	m_pauseBG.m_vPosition.x = 0;
	m_pauseBG.m_vPosition.y = 0;
	m_pauseBG.m_vPosition.z = 0;

	m_pauseBG.CreateTextureFromFile( "pause.png", &(m_pauseBG.m_Texture) );
}
