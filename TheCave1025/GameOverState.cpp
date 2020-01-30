#include "GameOverState.h"


void GameOver::Update(int &m_iCurrentState, int &m_iCurrentStage)
{
	if (!ifinit)
	{
		init();
		ifinit = true;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000 && !(select==0) && timet==0){
		select--;
		timet = TERM;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && !(select==1) && timet==0){
		select++;
		timet = TERM;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000){
		if(select==0){
			m_iCurrentState = 0;
			Sleep(300);
		}
		if(select==1){
			AllManager::GameON = false;
		}	
	}

	for (int i=0; i<2; i++)
	{
		if (select == i)
		{
			GameOverBG.m_rSource.top = 768*i;
			GameOverBG.m_rSource.bottom = GameOverBG.m_rSource.top + 768;
		}
	}

	UPKEYPRESS = false;
	DOWNKEYPRESS = false;

	timet--;
	if (timet <= 0)
		timet = 0;


}

void GameOver::Render()
{
	GameOverBG.Draw();
}

void GameOver::init()
{
	GameOverBG.m_bVisible = true;

	GameOverBG.m_rSource.left = 0;
	GameOverBG.m_rSource.top = 0;
	GameOverBG.m_rSource.right = 1024;
	GameOverBG.m_rSource.bottom = 768;

	GameOverBG.m_vPosition.x = 0;
	GameOverBG.m_vPosition.y = 0;
	GameOverBG.m_vPosition.z = 0;

	GameOverBG.CreateTextureFromFile( "Gameover.png", &(GameOverBG.m_Texture) );
}

GameOver::GameOver()
{
	timet = TERM;
	select = 0;
	ifinit = false;
}
