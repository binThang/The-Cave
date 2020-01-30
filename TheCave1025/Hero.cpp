#include "Hero.h"


#define ZERO 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define SPACE 5

#define IDLE 1
#define MOVE 2
#define ATTACK 3
#define RAGE 4
#define HITTED 6
#define DEAD 7

void Hero::Key()
{



		///////////아래쪽 키 ↓↓↓↓↓↓↓
		if(GetKeyState(VK_DOWN) & 0x8000)
		{
			if(down == false)
			{
				down	=	true;

				down_A	=	timeGetTime();
				down_B	=	timeGetTime();

				combo_A	=	timeGetTime();
				combo_B	=	timeGetTime();

				/////////// 한 개씩 밀어 넣기 ////////
				for(int i=19;i>0;i--)
				{
					combo[i]=combo[i-1];
				}
				combo[0]	=	DOWN;
			}

			if(down_B - down_A > 100 && combo[1] == 0)
			{
				combo[0]	=	0;
			}

		}
		else
		{
			down		=	false;
				
			down_A		=	0;
			down_B		=	0;

		}


	/////////////////// 왼쪽 키	←←←←←←←←←←←←←←
		if(GetKeyState(VK_LEFT) & 0x8000)
		{
			if(left == false)
			{
				left	=	true;
				left_A	=	timeGetTime();
				left_B	=	timeGetTime();

				combo_A	=	timeGetTime();
				combo_B	=	timeGetTime();

				/////////// 한 개씩 밀어 넣기 ////////
				for(int i=19;i>0;i--)
				{
					combo[i]=combo[i-1];
				}
				combo[0]	=	LEFT;
			}

			left_B	=	timeGetTime();

			if(left_B - left_A > 100)
			{
				for(int i=1;i<20;i++)
				{
					combo[i]	=	0;	//콤보시간이 지나면 콤보리스트 비움. 단 첫번째 키는 유지.
				}
				combo[0]	=	LEFT;
			}
		}
		else
		{
			left		=	false;

			left_A		=	0;
			left_B		=	0;

		}


		///////////////////// 오른쪽 키 →→→→→→→

		if(GetKeyState(VK_RIGHT) & 0x8000)
		{
			if(right == false)				// 처음 눌리면
			{
				right		=	true;
				right_A	=	timeGetTime();
				right_B	=	timeGetTime();

				combo_A	=	timeGetTime();
				combo_B	=	timeGetTime();

				//////////// 한 개씩 밀어넣기 ////////
				for(int i=19;i>0;i--)
				{
					combo[i]=combo[i-1];
				}
				combo[0]	=	RIGHT;
			}

			right_B	=	timeGetTime();

			if(right_B - right_A > 100)		//토글 시간이 지나면
			{
				for(int i=1;i<20;i++)
				{
					combo[i]	=	0;	//콤보시간이 지나면 콤보리스트 비움. 단 첫번째 키는 유지.
				}
				combo[0]	=	RIGHT;
			}
		}
		else
		{
			right		=	false;

			right_A		=	0;
			right_B		=	0;

		}

		
		///////////스페이스바  ↓↓↓↓↓↓↓
		if(GetKeyState(VK_SPACE) & 0x8000)
		{
			if(space == false)
			{
				space	=	true;

				space_A	=	timeGetTime();
				space_B	=	timeGetTime();

				combo_A	=	timeGetTime();
				combo_B	=	timeGetTime();

				/////////// 한 개씩 밀어 넣기 ////////
				for(int i=19;i>0;i--)
				{
					combo[i]=combo[i-1];
				}
				combo[0]	=	SPACE;
			}

			if(space_B - space_A > 100 && (combo[1] == 0 || combo[1]==SPACE))
			{
				combo[0]	=	0;
			}

		}
		else
		{
			space		=	false;

			space_A	=	0;
			space_B	=	0;

		}

		///////////위쪽 키 ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
		if(GetKeyState(VK_UP) & 0x8000)
		{
			if(up == false)
			{
				up	=	true;

				up_A	=	timeGetTime();
				up_B	=	timeGetTime();

				combo_A	=	timeGetTime();
				combo_B	=	timeGetTime();

				/////////// 한 개씩 밀어 넣기 ////////
				for(int i=19;i>0;i--)
				{
					combo[i]=combo[i-1];
				}
				combo[0]	=	UP;
			}
			if(up_B - up_A > 100 && combo[1] == 0)
			{
				combo[0]	=	0;
			}

		}
		else
		{
			up		=	false;

			up_A	=	0;
			up_B	=	0;
		}

		


		/////////// 키 입력 끝나고 콤보끝인지 계산하는 것
		combo_B	=	timeGetTime();

		if(combo_B - combo_A > 150)
		{
			if(up || down || left || right)	//콤보시간 후에 뭐라도 눌려져있으면 그 키 빼고 지움
			{
				for(int i=1;i<20;i++)
				{
					combo[i]	=	0;	//콤보시간이 지나면 콤보리스트 비움. 단 첫번째 키는 유지.
				}
			}
			else
			{
				for(int i=0;i<20;i++)
				{
					combo[i]	=	0;
				}
			}

			combo_A	= combo_B;
		}


		//////////// 키 입력 끝


}


void Hero::SetState()
{
	state	=	combo[5]*100000	+	combo[4]*10000	+	combo[3]*1000	+	combo[2]*100	+	combo[1]*10	+	combo[0];
}