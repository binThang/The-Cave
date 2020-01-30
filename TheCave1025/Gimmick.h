#pragma once

typedef struct Gimmick
{
	int x;
	int y;
	int screen_x;
	int screen_y;
	int sprite_x;
	int sprite_y;
	int moving_x;
	int moving_y;
	int ground;

	float size;
	float degree;
	int phase;
	int time;
	bool valid;


	void Initialize()
	{
		ground = 715;
		x=0;
		y=0;
		sprite_x=0;
		sprite_y=0;
		moving_x=0;
		moving_y=0;
		size=1;
		degree=0;
		phase=0;
		time=0;
		valid=false;
	}

} Gimmick;