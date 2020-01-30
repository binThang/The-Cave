#include "Field1State.h"
#include "DXSound.h"
#include "Main.h"

Field::Field()
{
	ifinit = false;

	m_f_Stage1 = new Sprite;

	m_f_Mop1[0] = new Sprite;
	m_f_Mop1[1] = new Sprite;
	m_f_Mop1[2] = new Sprite;
	m_f_Mop1[3] = new Sprite;
	m_f_Mop1[4] = new Sprite;
	m_f_Mop1[5] = new Sprite;

}

//지나감0 벽1 열쇠3 없어지는벽4 출구5

char FieldMap1[14][21] =
{
	"11111111111111111151",
	"10000001000010004001",
	"10110100010010101001",
	"10000101010000101001",
	"10000001000100001001",
	"10001111000001001001",
	"10001000011001001001",
	"10011000000000011001",
	"11011001001011000001",
	"13001001001000000001",
	"11111000001000010001",
	"11100000101000011101",
	"00000000001000016001",
	"11111111111111111111"
};

char FieldMap2[14][21] =
{
	"11111111111111111111",
	"10000000001000001105",
	"10011111101011010001",
	"10100000101001000101",
	"10100000101001010101",
	"10101111101010010101",
	"10100000001010110101",
	"10101011011010100101",
	"10101000001010101101",
	"10111111101011001001",
	"10100000000001000001",
	"10111111111111111111",
	"10000000000000000001",
	"11111111111111111101"
};

char FieldMap3[14][21] =
{
	"11111111111111111111",
	"00013000000000100001",
	"10011100001110111001",
	"10000011000000000001",
	"11100001011110111001",
	"10100010110011100001",
	"10110000000000000001",
	"10010000011100001101",
	"10011000130110011001",
	"10001001100100110111",
	"10111001001101100001",
	"10100011001001001001",
	"10001000004004001001",
	"11111111111111111151"
};

char FieldMap4[14][21] =
{
	"11111111111111111101",
	"13011000000001100001",
	"10001011000111000011",
	"10000014111100001111",
	"10000010000000010001",
	"10141110110100110101",
	"10100000100100000001",
	"10111100110010011001",
	"10010110010100010001",
	"10110010000100110031",
	"10000000000000114111",
	"10011100101000010001",
	"10100001100100010001",
	"11111111111115111111"
};

char FieldMap5[8][7] =
{
	"101101",
	"100001",
	"101101",
	"101101",
	"101001",
	"100001",
	"110011",
	"111111"
};

void Field::Render(int &CurrentStage)
{
	if (CurrentStage == 1)
	{
		m_f_Stage1->Draw();
		
		for (int i=0; i<6; i++)
		{
			if (be_monster1[i])
				m_f_Mop1[i]->Draw();
		}
		if (be_key1)
			m_f_key1->Draw();
		if (be_cage1)
			m_f_cage1->Draw();
		if (be_potion1)
			m_f_potion1->Draw();
	}
	if (CurrentStage == 2)
	{
		m_f_Stage2->Draw();

		for (int i=0; i<6; i++)
		{
			if (be_monster2[i])
				m_f_Mop2[i]->Draw();
		}
	}
	if (CurrentStage == 3)
	{
		m_f_Stage3->Draw();

		for (int i=0; i<7; i++)
		{
			if (be_monster3[i])
				m_f_Mop3[i]->Draw();
		}

		for (int i=0; i<2; i++)
		{
			if(be_key3)
				m_f_key3[i]->Draw();
			if(be_cage3)
				m_f_cage3[i]->Draw();
		}
	}
	if (CurrentStage == 4)
	{
		m_f_Stage4->Draw();

		for (int i=0; i<7; i++)
		{
			if (be_monster4[i])
				m_f_Mop4[i]->Draw();
		}

		for (int i=0; i<2; i++){
			if(be_key4)
				m_f_key4[i]->Draw();
		}
		for (int i=0; i<3; i++){
			if(be_cage4)
				m_f_cage4[i]->Draw();
		}
	}
	if (CurrentStage == 5)
	{
		m_f_Stage5->Draw();
		m_f_Mop5->Draw();
	}

	m_f_Char.Draw();
	m_f_Fog.Draw();
	m_f_UI.Draw();
	for (int i=0; i<10; i++)
		m_f_HP[i]->Draw();
	for (int i=0; i<6; i++)
		m_f_Font[i]->Draw();
}

void Field::Update(int &CurrentState, int &CurrentStage)
{		
	if (GetAsyncKeyState(VK_ESCAPE))
		CurrentState = 3;


	//stage1일 경우
	if(CurrentStage == 1){
		if (!ifinit){
			Stage1init();
			ifinit = true;
		}
		if (!CSound->IsLooping(SOUND_CAVE1))
		{
			CSound->Loop(SOUND_CAVE1);
		}
		Stage1process(CurrentState, CurrentStage);
	}
	//stage2
	if (CurrentStage == 2){
		if (CSound->IsLooping(SOUND_CAVE1))
		{
			CSound->Stop(SOUND_CAVE1);
		}
		if (!CSound->IsLooping(SOUND_CAVE2))
		{
			CSound->Loop(SOUND_CAVE2);
		}
		Stage2process(CurrentState, CurrentStage);
	}
	//stage3
	if (CurrentStage == 3)
	{
		if (CSound->IsLooping(SOUND_CAVE2))
		{
			CSound->Stop(SOUND_CAVE2);
		}
		if (!CSound->IsLooping(SOUND_CAVE1))
		{
			CSound->Loop(SOUND_CAVE1);
		}
		Stage3process(CurrentState, CurrentStage);
	}
	//stage4
	if (CurrentStage == 4)
	{
		if (CSound->IsLooping(SOUND_CAVE1))
		{
			CSound->Stop(SOUND_CAVE1);
		}
		if (!CSound->IsLooping(SOUND_CAVE2))
		{
			CSound->Loop(SOUND_CAVE2);
		}
		Stage4process(CurrentState, CurrentStage);
	}
	//stage5
	if (CurrentStage == 5)
	{
		if (CSound->IsLooping(SOUND_CAVE2))
		{
			CSound->Stop(SOUND_CAVE2);
		}
		Stage5process(CurrentState, CurrentStage);
	}

	//UI업뎃
	UIUpdate();
	//별,레벨업 업뎃
	StarUpdate(CurrentState);

	if (!(CurrentState==1))
	{
		if(CSound->IsLooping(SOUND_CAVE1))
			CSound->Stop(SOUND_CAVE1);
		if(CSound->IsLooping(SOUND_CAVE2))
			CSound->Stop(SOUND_CAVE2);
	}

}

void Field::Stage1init()//HWND g_hWnd, int &CurrentStage)
{

	CSound = Main::GetInstance().Get_DSound();

	//Stage1
	m_f_Stage1->m_bVisible = true;

	m_f_Stage1->m_rSource.left = 0;
	m_f_Stage1->m_rSource.top = 0;
	m_f_Stage1->m_rSource.right = 1000;
	m_f_Stage1->m_rSource.bottom = 700;

	m_f_Stage1->m_vPosition.x = 0;
	m_f_Stage1->m_vPosition.y = 0;
	m_f_Stage1->m_vPosition.z = 0;

	m_f_Stage1->CreateTextureFromFile( "stage1.png", &(m_f_Stage1->m_Texture) );
	
	//Char
	m_f_Char.m_bVisible = true;

	m_f_Char.m_rSource.left = 0;
	m_f_Char.m_rSource.top = 0;
	m_f_Char.m_rSource.right = 50;
	m_f_Char.m_rSource.bottom = 50;

	m_f_Char.m_vPosition.x = 0;
	m_f_Char.m_vPosition.y = 600;
	m_f_Char.m_vPosition.z = 0;

	m_f_Char.CreateTextureFromFile( "herofmm1.png", &(m_f_Char.m_Texture) );

	//Fog
	m_f_Fog.m_bVisible = true;

	m_f_Fog.m_rSource.left = 0;
	m_f_Fog.m_rSource.top = 0;
	m_f_Fog.m_rSource.right = 2000;
	m_f_Fog.m_rSource.bottom = 1400;

	m_f_Fog.m_vPosition.x = m_f_Char.m_vPosition.x - 975;
	m_f_Fog.m_vPosition.y = m_f_Char.m_vPosition.y - 675;
	m_f_Fog.m_vPosition.z = 0;

	m_f_Fog.CreateTextureFromFile( "FOG2.png", &(m_f_Fog.m_Texture) );

	//UI
	m_f_UI.m_bVisible = true;

	m_f_UI.m_rSource.left = 0;
	m_f_UI.m_rSource.top = 0;
	m_f_UI.m_rSource.right = 1000;
	m_f_UI.m_rSource.bottom = 68;

	m_f_UI.m_vPosition.x = 0;
	m_f_UI.m_vPosition.y = 700;
	m_f_UI.m_vPosition.z = 0;

	m_f_UI.CreateTextureFromFile( "fieldUI.png", &(m_f_UI.m_Texture) );

	//monster
	for (int i=0; i<6; i++)
	{
		m_f_Mop1[i]->m_bVisible = true;

		m_f_Mop1[i]->m_rSource.left = 0;
		m_f_Mop1[i]->m_rSource.top = 0;
		m_f_Mop1[i]->m_rSource.right = 50;
		m_f_Mop1[i]->m_rSource.bottom = 50;
		
		m_f_Mop1[i]->CreateTextureFromFile( "fieldmop.png", &(m_f_Mop1[i]->m_Texture) );
	}
	m_f_Mop1[0]->m_vPosition.x = 100;
	m_f_Mop1[0]->m_vPosition.y = 200;
	m_f_Mop1[0]->m_vPosition.z = 0;

	m_f_Mop1[1]->m_vPosition.x = 250;
	m_f_Mop1[1]->m_vPosition.y = 600;
	m_f_Mop1[1]->m_vPosition.z = 0;

	m_f_Mop1[2]->m_vPosition.x = 400;
	m_f_Mop1[2]->m_vPosition.y = 350;
	m_f_Mop1[2]->m_vPosition.z = 0;

	m_f_Mop1[3]->m_vPosition.x = 850;
	m_f_Mop1[3]->m_vPosition.y = 200;
	m_f_Mop1[3]->m_vPosition.z = 0;

	m_f_Mop1[4]->m_vPosition.x = 750;
	m_f_Mop1[4]->m_vPosition.y = 450;
	m_f_Mop1[4]->m_vPosition.z = 0;

	m_f_Mop1[5]->m_vPosition.x = 550;
	m_f_Mop1[5]->m_vPosition.y = 400;
	m_f_Mop1[5]->m_vPosition.z = 0;

	for (int i=0; i<6; i++)
	{
		monster1[i] = new FieldMonster;
		be_monster1[i] = true;
	}
	monster1[0]-> init(2, 4, 0);
	monster1[1]-> init(5, 12, 12);
	monster1[2]-> init(8, 7, 30);
	monster1[3]-> init(17, 4, 25);
	monster1[4]-> init(15, 9, 41);
	monster1[5]-> init(11, 8, 19);
	
	//key1
	m_f_key1 = new Sprite;
	be_key1 = true;

	m_f_key1->m_bVisible = true;

	m_f_key1->m_rSource.left = 0;
	m_f_key1->m_rSource.top = 0;
	m_f_key1->m_rSource.right = 50;
	m_f_key1->m_rSource.bottom = 50;

	m_f_key1->m_vPosition.x = 50;
	m_f_key1->m_vPosition.y = 450;
	m_f_key1->m_vPosition.z = 0;

	m_f_key1->CreateTextureFromFile( "key.png", &(m_f_key1->m_Texture) );

	//cage1
	m_f_cage1 = new Sprite;
	be_cage1 = true;

	m_f_cage1->m_bVisible = true;

	m_f_cage1->m_rSource.left = 0;
	m_f_cage1->m_rSource.top = 0;
	m_f_cage1->m_rSource.right = 50;
	m_f_cage1->m_rSource.bottom = 50;

	m_f_cage1->m_vPosition.x = 800;
	m_f_cage1->m_vPosition.y = 50;
	m_f_cage1->m_vPosition.z = 0;
	m_f_cage1->CreateTextureFromFile( "cage.png", &(m_f_cage1->m_Texture) );

	//potion
	m_f_potion1 = new Sprite;
	be_potion1 = true;

	m_f_potion1->m_bVisible = true;

	m_f_potion1->m_rSource.left = 0;
	m_f_potion1->m_rSource.top = 0;
	m_f_potion1->m_rSource.right = 50;
	m_f_potion1->m_rSource.bottom = 50;

	m_f_potion1->m_vPosition.x = 800;
	m_f_potion1->m_vPosition.y = 600;
	m_f_potion1->m_vPosition.z = 0;
	m_f_potion1->CreateTextureFromFile( "potion.png", &(m_f_potion1->m_Texture) );

	//HP
	for (int i=0; i<10; i++){
		m_f_HP[i] = new Sprite;

		m_f_HP[i]->m_bVisible = true;

		m_f_HP[i]->m_rSource.left = 0;
		m_f_HP[i]->m_rSource.top = 0;
		m_f_HP[i]->m_rSource.right = 30;
		m_f_HP[i]->m_rSource.bottom = 29;
		
		m_f_HP[i]->m_vPosition.y = 719;
		m_f_HP[i]->m_vPosition.z = 0;

		m_f_HP[i]->CreateTextureFromFile( "heart.png", &(m_f_HP[i]->m_Texture) );
	}

	m_f_HP[0]->m_vPosition.x = 81;
	m_f_HP[1]->m_vPosition.x = 98;
	m_f_HP[2]->m_vPosition.x = 115;
	m_f_HP[3]->m_vPosition.x = 132;
	m_f_HP[4]->m_vPosition.x = 149;
	m_f_HP[5]->m_vPosition.x = 166;
	m_f_HP[6]->m_vPosition.x = 183;
	m_f_HP[7]->m_vPosition.x = 200;
	m_f_HP[8]->m_vPosition.x = 217;
	m_f_HP[9]->m_vPosition.x = 234;

	//Font
	for (int i=0; i<6; i++)
	{
		m_f_Font[i] = new Sprite;

		m_f_Font[i]->m_bVisible = true;

		m_f_Font[i]->m_rSource.left = 0;
		m_f_Font[i]->m_rSource.top = 0;
		m_f_Font[i]->m_rSource.right = 25;
		m_f_Font[i]->m_rSource.bottom = 35;

		m_f_Font[i]->m_vPosition.y = 718;
		m_f_Font[i]->m_vPosition.z = 0;

		m_f_Font[i]->CreateTextureFromFile( "font.png", &(m_f_Font[i]->m_Texture) );
	}

	m_f_Font[0]->m_vPosition.x = 466;
	m_f_Font[1]->m_vPosition.x = 491;
	m_f_Font[2]->m_vPosition.x = 769;
	m_f_Font[3]->m_vPosition.x = 794;
	m_f_Font[4]->m_vPosition.x = 516;
	m_f_Font[5]->m_vPosition.x = 541;

}

void Field::Stage2init()
{
	m_f_Stage2 = new Sprite;

	//Stage2
	m_f_Stage2->m_bVisible = true;

	m_f_Stage2->m_rSource.left = 0;
	m_f_Stage2->m_rSource.top = 0;
	m_f_Stage2->m_rSource.right = 1000;
	m_f_Stage2->m_rSource.bottom = 700;

	m_f_Stage2->m_vPosition.x = 0;
	m_f_Stage2->m_vPosition.y = 0;
	m_f_Stage2->m_vPosition.z = 0;

	m_f_Stage2->CreateTextureFromFile( "stage2.png", &(m_f_Stage2->m_Texture) );

	//monster
	for (int i=0; i<6; i++)
	{
		m_f_Mop2[i] = new Sprite;

		m_f_Mop2[i]->m_bVisible = true;

		m_f_Mop2[i]->m_rSource.left = 0;
		m_f_Mop2[i]->m_rSource.top = 0;
		m_f_Mop2[i]->m_rSource.right = 50;
		m_f_Mop2[i]->m_rSource.bottom = 50;

		m_f_Mop2[i]->CreateTextureFromFile( "fieldmop.png", &(m_f_Mop2[i]->m_Texture) );
	}
	m_f_Mop2[0]->m_vPosition.x = 650;
	m_f_Mop2[0]->m_vPosition.y = 600;
	m_f_Mop2[0]->m_vPosition.z = 0;

	m_f_Mop2[1]->m_vPosition.x = 100;
	m_f_Mop2[1]->m_vPosition.y = 50;
	m_f_Mop2[1]->m_vPosition.z = 0;

	m_f_Mop2[2]->m_vPosition.x = 200;
	m_f_Mop2[2]->m_vPosition.y = 200;
	m_f_Mop2[2]->m_vPosition.z = 0;

	m_f_Mop2[3]->m_vPosition.x = 550;
	m_f_Mop2[3]->m_vPosition.y = 200;
	m_f_Mop2[3]->m_vPosition.z = 0;

	m_f_Mop2[4]->m_vPosition.x = 650;
	m_f_Mop2[4]->m_vPosition.y = 150;
	m_f_Mop2[4]->m_vPosition.z = 0;

	m_f_Mop2[5]->m_vPosition.x = 850;
	m_f_Mop2[5]->m_vPosition.y = 450;
	m_f_Mop2[5]->m_vPosition.z = 0;

	for (int i=0; i<6; i++)
	{
		monster2[i] = new FieldMonster;
		be_monster2[i] = true;
	}
	monster2[0]-> init(13, 12, 0);
	monster2[1]-> init(2, 1, 12);
	monster2[2]-> init(4, 4, 30);
	monster2[3]-> init(11, 4, 25);
	monster2[4]-> init(13, 3, 41);
	monster2[5]-> init(17, 9, 19);
}

void Field::Stage3init()
{
	m_f_Stage3 = new Sprite;

	m_f_Stage3->m_bVisible = true;

	m_f_Stage3->m_rSource.left = 0;
	m_f_Stage3->m_rSource.top = 0;
	m_f_Stage3->m_rSource.right = 1000;
	m_f_Stage3->m_rSource.bottom = 700;

	m_f_Stage3->m_vPosition.x = 0;
	m_f_Stage3->m_vPosition.y = 0;
	m_f_Stage3->m_vPosition.z = 0;

	m_f_Stage3->CreateTextureFromFile( "stage3.png", &(m_f_Stage3->m_Texture) );

	for (int i=0; i<7; i++)
	{
		m_f_Mop3[i] = new Sprite;

		m_f_Mop3[i]->m_bVisible = true;

		m_f_Mop3[i]->m_rSource.left = 0;
		m_f_Mop3[i]->m_rSource.top = 0;
		m_f_Mop3[i]->m_rSource.right = 50;
		m_f_Mop3[i]->m_rSource.bottom = 50;

		m_f_Mop3[i]->CreateTextureFromFile( "fieldmop.png", &(m_f_Mop3[i]->m_Texture) );
	}
	m_f_Mop3[0]->m_vPosition.x = 100;
	m_f_Mop3[0]->m_vPosition.y = 100;
	m_f_Mop3[0]->m_vPosition.z = 0;

	m_f_Mop3[1]->m_vPosition.x = 200;
	m_f_Mop3[1]->m_vPosition.y = 200;
	m_f_Mop3[1]->m_vPosition.z = 0;

	m_f_Mop3[2]->m_vPosition.x = 300;
	m_f_Mop3[2]->m_vPosition.y = 350;
	m_f_Mop3[2]->m_vPosition.z = 0;

	m_f_Mop3[3]->m_vPosition.x = 50;
	m_f_Mop3[3]->m_vPosition.y = 350;
	m_f_Mop3[3]->m_vPosition.z = 0;

	m_f_Mop3[4]->m_vPosition.x = 450;
	m_f_Mop3[4]->m_vPosition.y = 550;
	m_f_Mop3[4]->m_vPosition.z = 0;

	m_f_Mop3[5]->m_vPosition.x = 650;
	m_f_Mop3[5]->m_vPosition.y = 300;
	m_f_Mop3[5]->m_vPosition.z = 0;

	m_f_Mop3[6]->m_vPosition.x = 850;
	m_f_Mop3[6]->m_vPosition.y = 550;
	m_f_Mop3[6]->m_vPosition.z = 0;

	for (int i=0; i<7; i++)
	{
		monster3[i] = new FieldMonster;
		be_monster3[i] = true;
	}
	monster3[0]-> init(2, 2, 0);
	monster3[1]-> init(4, 4, 12);
	monster3[2]-> init(6, 7, 30);
	monster3[3]-> init(1, 7, 25);
	monster3[4]-> init(9,11, 41);
	monster3[5]-> init(13, 6, 19);
	monster3[6]-> init(17, 11, 35);

	//key
	for (int i=0; i<2; i++)
	{
		m_f_key3[i] = new Sprite;
		be_key3[i] = true;
	
		m_f_key3[i]->m_bVisible = true;
	
		m_f_key3[i]->m_rSource.left = 0;
		m_f_key3[i]->m_rSource.top = 0;
		m_f_key3[i]->m_rSource.right = 50;
		m_f_key3[i]->m_rSource.bottom = 50;
	
		m_f_key3[i]->m_vPosition.z = 0;
	
		m_f_key3[i]->CreateTextureFromFile( "key.png", &(m_f_key3[i]->m_Texture) );
	}

	m_f_key3[0]->m_vPosition.x = 200;
	m_f_key3[0]->m_vPosition.y = 50;
	m_f_key3[1]->m_vPosition.x = 450; 
	m_f_key3[1]->m_vPosition.y = 400;

	for (int i=0; i<2; i++)
	{
		m_f_cage3[i] = new Sprite;
		be_cage3[i] = true;

		m_f_cage3[i]->m_bVisible = true;

		m_f_cage3[i]->m_rSource.left = 0;
		m_f_cage3[i]->m_rSource.top = 0;
		m_f_cage3[i]->m_rSource.right = 50;
		m_f_cage3[i]->m_rSource.bottom = 50;

		m_f_cage3[i]->m_vPosition.z = 0;

		m_f_cage3[i]->CreateTextureFromFile( "cage.png", &(m_f_cage3[i]->m_Texture) );
	}

	m_f_cage3[0]->m_vPosition.x = 500;
	m_f_cage3[0]->m_vPosition.y = 600;
	m_f_cage3[1]->m_vPosition.x = 650;
	m_f_cage3[1]->m_vPosition.y = 600;
}

void Field::Stage4init()
{
	m_f_Stage4 = new Sprite;

	//Stage4
	m_f_Stage4->m_bVisible = true;

	m_f_Stage4->m_rSource.left = 0;
	m_f_Stage4->m_rSource.top = 0;
	m_f_Stage4->m_rSource.right = 1000;
	m_f_Stage4->m_rSource.bottom = 700;

	m_f_Stage4->m_vPosition.x = 0;
	m_f_Stage4->m_vPosition.y = 0;
	m_f_Stage4->m_vPosition.z = 0;

	m_f_Stage4->CreateTextureFromFile( "stage4.png", &(m_f_Stage4->m_Texture) );

	//monstersprite
	for (int i=0; i<7; i++)
	{
		m_f_Mop4[i] = new Sprite;

		m_f_Mop4[i]->m_bVisible = true;

		m_f_Mop4[i]->m_rSource.left = 0;
		m_f_Mop4[i]->m_rSource.top = 0;
		m_f_Mop4[i]->m_rSource.right = 50;
		m_f_Mop4[i]->m_rSource.bottom = 50;

		m_f_Mop4[i]->CreateTextureFromFile( "fieldmop.png", &(m_f_Mop4[i]->m_Texture) );
	}
	m_f_Mop4[0]->m_vPosition.x = 800;
	m_f_Mop4[0]->m_vPosition.y = 100;
	m_f_Mop4[0]->m_vPosition.z = 0;

	m_f_Mop4[1]->m_vPosition.x = 600;
	m_f_Mop4[1]->m_vPosition.y = 550;
	m_f_Mop4[1]->m_vPosition.z = 0;

	m_f_Mop4[2]->m_vPosition.x = 400;
	m_f_Mop4[2]->m_vPosition.y = 450;
	m_f_Mop4[2]->m_vPosition.z = 0;

	m_f_Mop4[3]->m_vPosition.x = 150;
	m_f_Mop4[3]->m_vPosition.y = 150;
	m_f_Mop4[3]->m_vPosition.z = 0;

	m_f_Mop4[4]->m_vPosition.x = 400;
	m_f_Mop4[4]->m_vPosition.y = 50;
	m_f_Mop4[4]->m_vPosition.z = 0;

	m_f_Mop4[5]->m_vPosition.x = 200;
	m_f_Mop4[5]->m_vPosition.y = 500;
	m_f_Mop4[5]->m_vPosition.z = 0;

	m_f_Mop4[6]->m_vPosition.x = 850;
	m_f_Mop4[6]->m_vPosition.y = 550;
	m_f_Mop4[6]->m_vPosition.z = 0;

	//monster
	for (int i=0; i<7; i++)
	{
		monster4[i] = new FieldMonster;
		be_monster4[i] = true;
	}
	monster4[0]-> init(16, 2, 0);
	monster4[1]-> init(12, 11, 12);
	monster4[2]-> init(8, 9, 30);
	monster4[3]-> init(3, 3, 25);
	monster4[4]-> init(8, 1, 41);
	monster4[5]-> init(4, 10, 19);
	monster4[6]-> init(17, 11, 35);

	//key
	for (int i=0; i<2; i++)
	{
		m_f_key4[i] = new Sprite;
		be_key4[i] = true;

		m_f_key4[i]->m_bVisible = true;

		m_f_key4[i]->m_rSource.left = 0;
		m_f_key4[i]->m_rSource.top = 0;
		m_f_key4[i]->m_rSource.right = 50;
		m_f_key4[i]->m_rSource.bottom = 50;

		m_f_key4[i]->m_vPosition.z = 0;

		m_f_key4[i]->CreateTextureFromFile( "key.png", &(m_f_key4[i]->m_Texture) );
	}

	m_f_key4[0]->m_vPosition.x = 50;
	m_f_key4[0]->m_vPosition.y = 50;
	m_f_key4[1]->m_vPosition.x = 900; 
	m_f_key4[1]->m_vPosition.y = 450;

	//cage
	for (int i=0; i<3; i++)
	{
		m_f_cage4[i] = new Sprite;
		be_cage4[i] = true;

		m_f_cage4[i]->m_bVisible = true;

		m_f_cage4[i]->m_rSource.left = 0;
		m_f_cage4[i]->m_rSource.top = 0;
		m_f_cage4[i]->m_rSource.right = 50;
		m_f_cage4[i]->m_rSource.bottom = 50;

		m_f_cage4[i]->m_vPosition.z = 0;

		m_f_cage4[i]->CreateTextureFromFile( "cage.png", &(m_f_cage4[i]->m_Texture) );
	}

	m_f_cage4[0]->m_vPosition.x = 350;
	m_f_cage4[0]->m_vPosition.y = 150;
	m_f_cage4[1]->m_vPosition.x = 800;
	m_f_cage4[1]->m_vPosition.y = 500;
	m_f_cage4[2]->m_vPosition.x = 150;
	m_f_cage4[2]->m_vPosition.y = 250;
}

void Field::Stage5init()
{
	//Stage5
	m_f_Stage5 = new Sprite;

	m_f_Stage5->m_bVisible = true;

	m_f_Stage5->m_rSource.left = 0;
	m_f_Stage5->m_rSource.top = 0;
	m_f_Stage5->m_rSource.right = 300;
	m_f_Stage5->m_rSource.bottom = 400;

	m_f_Stage5->m_vPosition.x = 350;
	m_f_Stage5->m_vPosition.y = 150;
	m_f_Stage5->m_vPosition.z = 0;

	m_f_Stage5->CreateTextureFromFile( "stage5.png", &(m_f_Stage5->m_Texture) );

	//보스몹
	m_f_Mop5 = new Sprite;

	m_f_Mop5->m_bVisible = true;

	m_f_Mop5->m_rSource.left = 0;
	m_f_Mop5->m_rSource.top = 0;
	m_f_Mop5->m_rSource.right = 50;
	m_f_Mop5->m_rSource.bottom = 50;

	m_f_Mop5->m_vPosition.x = 550;
	m_f_Mop5->m_vPosition.y = 150;
	m_f_Mop5->m_vPosition.z = 0;

	m_f_Mop5->CreateTextureFromFile( "fieldmop.png", &(m_f_Mop5->m_Texture) );

	monster5 = new FieldMonster;

	monster5->init(4,0,0);

	be_monster5 = true;
}

void Field::Stage1release()
{
	m_f_Stage1->m_Texture->Release();
	delete m_f_Stage1;

	for (int i=0; i<6; i++)
	{	
		if(be_monster1[i])
			delete m_f_Mop1[i];
	}
	if (be_key1)
		delete m_f_key1;
	if (be_cage1)
		delete m_f_cage1;
	if(be_potion1)
		delete m_f_potion1;
}

void Field::Stage2release()
{
	delete m_f_Stage2;

	for (int i=0; i<6; i++)
	{	
		if(be_monster2[i])
			delete m_f_Mop2[i];
	}
}

void Field::Stage3release()
{
	delete m_f_Stage3;

	for (int i=0; i<7; i++)
	{	
		if(be_monster3[i])
			delete m_f_Mop3[i];
	}
}

void Field::Stage4release()
{
	delete m_f_Stage4;

	for (int i=0; i<7; i++)
	{	
		if(be_monster4[i])
			delete m_f_Mop4[i];
	}
}

void Field::Stage5release()
{

}


void Field::UIUpdate()
{
	int i=0;

	for (i=0; i<10; i++)
		m_f_HP[i]->m_bVisible = false;
	for(i=0; i<HeroStat::hp; i++)
		m_f_HP[i]->m_bVisible = true;

	//별 1000의자리 숫자
	m_f_Font[0]->m_rSource.left = (HeroStat::star / 1000)*25;
	m_f_Font[0]->m_rSource.right = m_f_Font[0]->m_rSource.left + 25;
	//별 100의자리 숫자
	m_f_Font[1]->m_rSource.left = ((HeroStat::star % 1000) / 100)*25;
	m_f_Font[1]->m_rSource.right =	m_f_Font[1]->m_rSource.left + 25;
	//별 10의자리 숫자
	m_f_Font[4]->m_rSource.left = ((HeroStat::star % 100) / 10)*25;
	m_f_Font[4]->m_rSource.right =	m_f_Font[4]->m_rSource.left + 25;
	//별 1의자리 숫자
	m_f_Font[5]->m_rSource.left = (HeroStat::star % 10)*25;
	m_f_Font[5]->m_rSource.right =	m_f_Font[5]->m_rSource.left + 25;
	//열쇠 10의자리 숫자
	m_f_Font[2]->m_rSource.left = (hero.key / 10) * 25;
	m_f_Font[2]->m_rSource.right = m_f_Font[2]->m_rSource.left + 25;
	//열쇠 1의자리 숫자
	m_f_Font[3]->m_rSource.left = (hero.key % 10) * 25;
	m_f_Font[3]->m_rSource.right = m_f_Font[3]->m_rSource.left + 25;
}

void Field::Stage1process( int &CurrentState, int &CurrentStage )
{
	//hero업뎃
	hero.Update(FieldMap1, m_f_Char.m_rSource, m_f_Char.m_vPosition.x, m_f_Char.m_vPosition.y, m_f_Fog.m_vPosition.x, m_f_Fog.m_vPosition.y);

	//몬스터1_1존재시 몬스터1_1업뎃
	for (int i=0; i<6; i++)
	{
		if (be_monster1[i])
			monster1[i]->Update(FieldMap1, m_f_Mop1[i]->m_rSource, m_f_Mop1[i]->m_vPosition.x, m_f_Mop1[i]->m_vPosition.y);
	}

	//hero가 몬스터를 만나면
	for (int i=0; i<6; i++)
	{		
		if ( hero.minipos_x == monster1[i]->minipos_x && hero.minipos_y == monster1[i]->minipos_y && (be_monster1[i]==true)){	
			CurrentState = 2;									//전투화면으로 전환
			delete monster1[i];									//몬스터 객체삭제
			delete m_f_Mop1[i];								//몬스터 스프라이트 객체삭제
			be_monster1[i] = false;								//몬스터 존재삭제
			FieldMap1[hero.minipos_y][hero.minipos_x] = '0';	//몬스터 맵에서 삭제
		}
	}

	//열쇠를 먹으면
	if(FieldMap1[hero.minipos_y][hero.minipos_x] == '3'){
		(hero.key)++;
		FieldMap1[hero.minipos_y][hero.minipos_x] = '0';
		delete m_f_key1;
		be_key1 = false;
	}

	//포션을 먹으면
	if (FieldMap1[hero.minipos_y][hero.minipos_x] == '6')
	{
		HeroStat::hp++;
		FieldMap1[hero.minipos_y][hero.minipos_x] = '0';
		delete m_f_potion1;
		be_potion1 = false;
	}

	//철창을만나면
	if ((FieldMap1[hero.minipos_y][hero.minipos_x+1] == '4') && (hero.m_direct == 3) && (hero.key))
	{
		(hero.key)--;
		FieldMap1[hero.minipos_y][hero.minipos_x+1] = '0';
		delete m_f_cage1;
		be_cage1 = false;
	}
	if ((FieldMap1[hero.minipos_y][hero.minipos_x-1] == '4') && (hero.m_direct == 2) && (hero.key))
	{
		(hero.key)--;
		FieldMap1[hero.minipos_y][hero.minipos_x-1] = '0';
		delete m_f_cage1;
		be_cage1 = false;
	}
	if ((FieldMap1[hero.minipos_y-1][hero.minipos_x] == '4') && (hero.m_direct == 0) && (hero.key))
	{
		(hero.key)--;
		FieldMap1[hero.minipos_y-1][hero.minipos_x] = '0';
		delete m_f_cage1;
		be_cage1 = false;
	}
	if ((FieldMap1[hero.minipos_y+1][hero.minipos_x] == '4') && (hero.m_direct == 1) && (hero.key))
	{
		(hero.key)--;
		FieldMap1[hero.minipos_y+1][hero.minipos_x] = '0';
		delete m_f_cage1;
		be_cage1 = false;
	}

	//hero가 출구를 만나면
	if ( FieldMap1[hero.minipos_y][hero.minipos_x] == '5')
// 	{
// 		CurrentStage = 5;				//stage2로 전환
// 		m_f_Char.m_vPosition.x = 400;	//stage2의 시작지점 좌표
// 		m_f_Char.m_vPosition.y = 200;
// 		hero.minipos_x = 1;			//stage2의 시작지점 맵좌표
// 		hero.minipos_y = 1;
// 
// 		Stage1release();				//stage1 릴리즈
// 		Stage5init();					//stage2 이니셜라이즈
// 	}
	{
		CurrentStage = 2;				//stage2로 전환
		m_f_Char.m_vPosition.x = 900;	//stage2의 시작지점 좌표
		m_f_Char.m_vPosition.y = 650;
		hero.minipos_x = 18;			//stage2의 시작지점 맵좌표
		hero.minipos_y = 12;

		Stage1release();				//stage1 릴리즈
		Stage2init();					//stage2 이니셜라이즈
	}
}

void Field::Stage2process(int &CurrentState, int &CurrentStage)
{
	//hero 업뎃
	hero.Update(FieldMap2,m_f_Char.m_rSource, m_f_Char.m_vPosition.x, m_f_Char.m_vPosition.y, m_f_Fog.m_vPosition.x, m_f_Fog.m_vPosition.y);

	//몬스터2_i존재시 몬스터1_1업뎃
	for (int i=0; i<6; i++)
	{
		if (be_monster2[i])
			monster2[i]->Update(FieldMap2, m_f_Mop2[i]->m_rSource, m_f_Mop2[i]->m_vPosition.x, m_f_Mop2[i]->m_vPosition.y);
	}

	//hero가 몬스터를 만나면
	for (int i=0; i<6; i++)
	{		
		if ( hero.minipos_x == monster2[i]->minipos_x && hero.minipos_y == monster2[i]->minipos_y && (be_monster2[i]==true)){	
			CurrentState = 2;									//전투화면으로 전환
			delete monster2[i];									//몬스터 객체삭제
			delete m_f_Mop2[i];								//몬스터 스프라이트 객체삭제
			be_monster2[i] = false;								//몬스터 존재삭제
			FieldMap2[hero.minipos_y][hero.minipos_x] = '0';	//몬스터 맵에서 삭제
		}
	}
// 
// 	//열쇠를 먹으면
// 	if(FieldMap2[hero.minipos_y][hero.minipos_x] == '3'){
// 		(hero.key)++;
// 		FieldMap2[hero.minipos_y][hero.minipos_x] = '0';
// 		delete m_f_key1;
// 		be_key1 = false;
// 	}
// 
// 	//포션을 먹으면
// 	if (FieldMap2[hero.minipos_y][hero.minipos_x] == '6')
// 	{
// 		HeroStat::hp++;
// 		FieldMap2[hero.minipos_y][hero.minipos_x] = '0';
// 		delete m_f_potion1;
// 		be_potion1 = false;
// 
// 	}
// 
// 	//철창을만나면
// 	if ((FieldMap2[hero.minipos_y][hero.minipos_x+1] == '4') && (hero.m_direct == 3) && (hero.key))
// 	{
// 		(hero.key)--;
// 		FieldMap2[hero.minipos_y][hero.minipos_x+1] = '0';
// 		delete m_f_cage1;
// 		be_cage1 = false;
// 	}
// 	if ((FieldMap2[hero.minipos_y][hero.minipos_x-1] == '4') && (hero.m_direct == 2) && (hero.key))
// 	{
// 		(hero.key)--;
// 		FieldMap2[hero.minipos_y][hero.minipos_x-1] = '0';
// 		delete m_f_cage1;
// 		be_cage1 = false;
// 	}
// 	if ((FieldMap2[hero.minipos_y-1][hero.minipos_x] == '4') && (hero.m_direct == 0) && (hero.key))
// 	{
// 		(hero.key)--;
// 		FieldMap2[hero.minipos_y-1][hero.minipos_x] = '0';
// 		delete m_f_cage1;
// 		be_cage1 = false;
// 	}
// 	if ((FieldMap2[hero.minipos_y+1][hero.minipos_x] == '4') && (hero.m_direct == 1) && (hero.key))
// 	{
// 		(hero.key)--;
// 		FieldMap2[hero.minipos_y+1][hero.minipos_x] = '0';
// 		delete m_f_cage1;
// 		be_cage1 = false;
// 	}

	//hero가 출구를 만나면
	if ( FieldMap2[hero.minipos_y][hero.minipos_x] == '5')
	{
		CurrentStage = 3;				//stage2로 전환
		m_f_Char.m_vPosition.x = 0;	//stage2의 시작지점 좌표
		m_f_Char.m_vPosition.y = 50;
		hero.minipos_x = 1;			//stage2의 시작지점 맵좌표
		hero.minipos_y = 1;

		Stage2release();				//stage1 릴리즈
		Stage3init();					//stage2 이니셜라이즈
	}
}

void Field::Stage3process( int &CurrentState, int &CurrentStage )
{
	//hero 업뎃
	hero.Update(FieldMap3,m_f_Char.m_rSource, m_f_Char.m_vPosition.x, m_f_Char.m_vPosition.y, m_f_Fog.m_vPosition.x, m_f_Fog.m_vPosition.y);

	//몬스터1_1존재시 몬스터1_1업뎃
	for (int i=0; i<7; i++)
	{
		if (be_monster3[i])
			monster3[i]->Update(FieldMap3, m_f_Mop3[i]->m_rSource, m_f_Mop3[i]->m_vPosition.x, m_f_Mop3[i]->m_vPosition.y);
	}
	 
	//hero가 몬스터를 만나면
	for (int i=0; i<7; i++)
	{		
		if ( hero.minipos_x == monster3[i]->minipos_x && hero.minipos_y == monster3[i]->minipos_y && (be_monster3[i]==true)){	
			CurrentState = 2;									//전투화면으로 전환
			delete monster3[i];									//몬스터 객체삭제
			delete m_f_Mop3[i];								//몬스터 스프라이트 객체삭제
			be_monster3[i] = false;								//몬스터 존재삭제
			FieldMap3[hero.minipos_y][hero.minipos_x] = '0';	//몬스터 맵에서 삭제
		}
	}
	//열쇠를 먹으면
	if(FieldMap3[hero.minipos_y][hero.minipos_x] == '3'){
		for (int i=0; i<2; i++)
		{
			if ((hero.minipos_x == (m_f_key3[i]->m_vPosition.x) / 50) && (hero.minipos_y == (m_f_key3[i]->m_vPosition.y) / 50))
			{
				(hero.key)++;
				FieldMap3[hero.minipos_y][hero.minipos_x] = '0';
				delete m_f_key3[i];
				be_key3[i] = false;
			}
		}
	}
	 
	// 	//포션을 먹으면
	// 	if (FieldMap2[hero.minipos_y][hero.minipos_x] == '6')
	// 	{
	// 		HeroStat::hp++;
	// 		FieldMap2[hero.minipos_y][hero.minipos_x] = '0';
	// 		delete m_f_potion1;
	// 		be_potion1 = false;
	// 
	// 	}
	// 
 	//철창을만나면
	for (int i=0; i<2; i++)
	{
		if ((hero.minipos_x +1 == (m_f_cage3[i]->m_vPosition.x) / 50 ) && (hero.minipos_y == (m_f_cage3[i]->m_vPosition.y) / 50) && (hero.m_direct == 3) && (hero.key))
		{
			(hero.key)--;
			FieldMap3[hero.minipos_y][hero.minipos_x+1] = '0';
			delete m_f_cage3[i];
			be_cage3[i] = false;
		}
		if (((hero.minipos_x -1 == (m_f_cage3[i]->m_vPosition.x) / 50 ) && (hero.minipos_y == (m_f_cage3[i]->m_vPosition.y) / 50)) && (hero.m_direct == 2) && (hero.key))
		{
			(hero.key)--;
			FieldMap3[hero.minipos_y][hero.minipos_x-1] = '0';
			delete m_f_cage3[i];
			be_cage3[i] = false;
		}
		if ((hero.minipos_x == (m_f_cage3[i]->m_vPosition.x) / 50) && (hero.minipos_y -1 == (m_f_cage3[i]->m_vPosition.y) / 50 ) && (hero.m_direct == 0) && (hero.key))
		{
			(hero.key)--;
			FieldMap3[hero.minipos_y-1][hero.minipos_x] = '0';
			delete m_f_cage3[i];
			be_cage3[i] = false;
		}
		if (((hero.minipos_x == (m_f_cage3[i]->m_vPosition.x) / 50) && (hero.minipos_y +1 == (m_f_cage3[i]->m_vPosition.y) / 50 )) && (hero.m_direct == 1) && (hero.key))
		{
			(hero.key)--;
			FieldMap3[hero.minipos_y+1][hero.minipos_x] = '0';
			delete m_f_cage3[i];
			be_cage3[i] = false;
		}
	}

	//hero가 출구를 만나면
	if ( FieldMap3[hero.minipos_y][hero.minipos_x] == '5')
	{
		CurrentStage = 4;				//stage4로 전환
		m_f_Char.m_vPosition.x = 900;	//stage4의 시작지점 좌표
		m_f_Char.m_vPosition.y = 0;
		hero.minipos_x = 18;			//stage4의 시작지점 맵좌표
		hero.minipos_y = 1;

		Stage3release();				//stage1 릴리즈
		Stage4init();					//stage2 이니셜라이즈
	}
}

void Field::Stage4process( int &CurrentState, int &CurrentStage )
{
	//hero 업뎃
	hero.Update(FieldMap4,m_f_Char.m_rSource, m_f_Char.m_vPosition.x, m_f_Char.m_vPosition.y, m_f_Fog.m_vPosition.x, m_f_Fog.m_vPosition.y);

	//몬스터1_1존재시 몬스터1_1업뎃
	for (int i=0; i<7; i++)
	{
		if (be_monster4[i])
			monster4[i]->Update(FieldMap4, m_f_Mop4[i]->m_rSource, m_f_Mop4[i]->m_vPosition.x, m_f_Mop4[i]->m_vPosition.y);
	}

	//hero가 몬스터를 만나면
	for (int i=0; i<6; i++)
	{		
		if ( hero.minipos_x == monster4[i]->minipos_x && hero.minipos_y == monster4[i]->minipos_y && (be_monster4[i]==true)){	
			CurrentState = 2;									//전투화면으로 전환
			delete monster4[i];									//몬스터 객체삭제
			delete m_f_Mop4[i];								//몬스터 스프라이트 객체삭제
			be_monster4[i] = false;								//몬스터 존재삭제
			FieldMap4[hero.minipos_y][hero.minipos_x] = '0';	//몬스터 맵에서 삭제
		}
	}
	// 
	//열쇠를 먹으면
	if(FieldMap4[hero.minipos_y][hero.minipos_x] == '3'){
		for (int i=0; i<2; i++)
		{
			if ((hero.minipos_x == (m_f_key4[i]->m_vPosition.x) / 50) && (hero.minipos_y == (m_f_key4[i]->m_vPosition.y) / 50))
			{
				(hero.key)++;
				FieldMap4[hero.minipos_y][hero.minipos_x] = '0';
				delete m_f_key4[i];
				be_key4[i] = false;
			}
		}
	}
	// 
	// 	//포션을 먹으면
	// 	if (FieldMap2[hero.minipos_y][hero.minipos_x] == '6')
	// 	{
	// 		HeroStat::hp++;
	// 		FieldMap2[hero.minipos_y][hero.minipos_x] = '0';
	// 		delete m_f_potion1;
	// 		be_potion1 = false;
	// 
	// 	}

	//열쇠를 먹으면 
	if(FieldMap4[hero.minipos_y][hero.minipos_x] == '3'){
		for (int i=0; i<2; i++)
		{
			if ((hero.minipos_x == (m_f_key4[i]->m_vPosition.x) / 50) && (hero.minipos_y == (m_f_key4[i]->m_vPosition.y) / 50))
			{
				(hero.key)++;
				FieldMap4[hero.minipos_y][hero.minipos_x] = '0';
				delete m_f_key4[i];
				be_key4[i] = false;
			}
		}
	}

	//철창을만나면
	for (int i=0; i<3; i++)
	{
		if ((hero.minipos_x +1 == (m_f_cage4[i]->m_vPosition.x) / 50 ) && (hero.minipos_y == (m_f_cage4[i]->m_vPosition.y) / 50) && (hero.m_direct == 3) && (hero.key))
		{
			(hero.key)--;
			FieldMap4[hero.minipos_y][hero.minipos_x+1] = '0';
			delete m_f_cage4[i];
			be_cage4[i] = false;
		}
		if (((hero.minipos_x -1 == (m_f_cage4[i]->m_vPosition.x) / 50 ) && (hero.minipos_y == (m_f_cage4[i]->m_vPosition.y) / 50)) && (hero.m_direct == 2) && (hero.key))
		{
			(hero.key)--;
			FieldMap4[hero.minipos_y][hero.minipos_x-1] = '0';
			delete m_f_cage4[i];
			be_cage4[i] = false;
		}
		if ((hero.minipos_x == (m_f_cage4[i]->m_vPosition.x) / 50) && (hero.minipos_y -1 == (m_f_cage4[i]->m_vPosition.y) / 50 ) && (hero.m_direct == 0) && (hero.key))
		{
			(hero.key)--;
			FieldMap4[hero.minipos_y-1][hero.minipos_x] = '0';
			delete m_f_cage4[i];
			be_cage4[i] = false;
		}
		if (((hero.minipos_x == (m_f_cage4[i]->m_vPosition.x) / 50) && (hero.minipos_y +1 == (m_f_cage4[i]->m_vPosition.y) / 50 )) && (hero.m_direct == 1) && (hero.key))
		{
			(hero.key)--;
			FieldMap4[hero.minipos_y+1][hero.minipos_x] = '0';
			delete m_f_cage4[i];
			be_cage4[i] = false;
		}
	}

	//hero가 출구를 만나면
	if ( FieldMap4[hero.minipos_y][hero.minipos_x] == '5')
	{
		CurrentStage = 5;				//stage2로 전환
		m_f_Char.m_vPosition.x = 400;	//stage2의 시작지점 좌표
		m_f_Char.m_vPosition.y = 150;
		hero.minipos_x = 1;			//stage2의 시작지점 맵좌표
		hero.minipos_y = 1;

		Stage4release();				//stage1 릴리즈
		Stage5init();					//stage2 이니셜라이즈
	}
}

void Field::Stage5process( int &CurrentState, int &CurrentStage )
{
	hero.Update(FieldMap5,m_f_Char.m_rSource, m_f_Char.m_vPosition.x, m_f_Char.m_vPosition.y, m_f_Fog.m_vPosition.x, m_f_Fog.m_vPosition.y);

	if (be_monster5 == false)
	{
		CurrentState = 6;
	}

	if ( hero.minipos_x == monster5->minipos_x && hero.minipos_y == monster5->minipos_y && (be_monster5==true)){	
		CurrentState = 2;									//전투화면으로 전환
		delete monster5;									//몬스터 객체삭제
		delete m_f_Mop5;								//몬스터 스프라이트 객체삭제
		be_monster5 = false;								//몬스터 존재삭제
		FieldMap5[hero.minipos_y][hero.minipos_x] = '0';	//몬스터 맵에서 삭제
	}
}

void Field::StarUpdate(int &CurrentState)
{
	if (HeroStat::star >= 100 )
	{
		HeroStat::star -= 100;
		HeroStat::level++;
		CurrentState = 5;
	}
}

Field::~Field()
{
// 	m_f_Stage1->m_Texture->Release();
// 
// 	m_f_Mop1[0]->m_Texture->Release();
// 	m_f_Mop1[1]->m_Texture->Release();
// 	m_f_Mop1[2]->m_Texture->Release();
// 	m_f_Mop1[3]->m_Texture->Release();
// 	m_f_Mop1[4]->m_Texture->Release();
// 	m_f_Mop1[5]->m_Texture->Release();
}
