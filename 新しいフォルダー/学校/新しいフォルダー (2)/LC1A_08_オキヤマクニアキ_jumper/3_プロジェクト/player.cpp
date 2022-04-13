#include "player.h"
#include"DxLib.h"

//�ύX�_�Ȃ�
void player::Move(int vx, int vy)
{
	x += vx;
	y += vy;
}
void player::PlayerInit(int xarg, int yarg, int rarg)
{
	x = xarg;
	y = yarg;
	r = rarg;
}

void player::Col(int vx, int vy, int old_x, int old_y, int size, int mapCx, int mapCy, int* map)
{
	int old_ball_left = (old_x - r) / size;

	int old_ball_top = (old_y - r) / size;

	int old_ball_bottom = (old_y + r - 1) / size;

	int old_ball_right = (old_x + r - 1) / size;

	int ball_left = (x - r) / size;

	int ball_top = (y - r) / size;

	int ball_bottom = (y + r - 1) / size;

	int ball_right = (x + r - 1) / size;

	//�E
	if (vx > 0)
	{
		if (*(map + (old_ball_top * mapCx) + ball_right) == 2 || *(map + (old_ball_bottom * mapCx) + ball_right) == 2)
		{
			x = size * (ball_right - 1) + r;
		}
	}
	//��
	if (vx < 0)
	{
		if (*(map + (old_ball_top * mapCx) + ball_left) == 2 || *(map + (old_ball_bottom * mapCx) + ball_left) == 2)
		{
			x = size * (ball_left + 1) + r;
		}
	}
	//��
	if (vy < 0)
	{
		if (*(map + (ball_top * mapCx) + old_ball_left) == 2 || *(map + (ball_top * mapCx) + old_ball_right) == 2)
		{
			y = size * (ball_top + 1) + r;
		}
	}
	//��
	if (vy > 0)
	{
		if (*(map + (ball_bottom * mapCx) + old_ball_left) == 2 || *(map + (ball_bottom * mapCx) + old_ball_right) == 2)
		{
			y = size * (ball_bottom - 1) + r;
		}

	}
}

bool player::Trap(int vx, int vy, int old_x, int old_y, int size, int mapCx, int mapCy, int* map)
{
	int old_ball_left = (old_x - r) / size;

	int old_ball_top = (old_y - r) / size;

	int old_ball_bottom = (old_y + r - 1) / size;

	int old_ball_right = (old_x + r - 1) / size;

	int ball_left = (x - r) / size;

	int ball_top = (y - r) / size;

	int ball_bottom = (y + r - 1) / size;

	int ball_right = (x + r - 1) / size;

	//�E
	if (*(map + (old_ball_top * mapCx) + ball_right) == 3 || *(map + (old_ball_bottom * mapCx) + ball_right) == 3)
	{
		return true;
	}

	//��
	if (*(map + (old_ball_top * mapCx) + ball_left) == 3 || *(map + (old_ball_bottom * mapCx) + ball_left) == 3)
	{
		return true;
	}

	//��
	if (*(map + (ball_top * mapCx) + old_ball_left) == 3 || *(map + (ball_top * mapCx) + old_ball_right) == 3)
	{
		return true;
	}

	//��
	if (*(map + (ball_bottom * mapCx) + old_ball_left) == 3 || *(map + (ball_bottom * mapCx) + old_ball_right) == 3)
	{
		return true;
	}

	else
	{
		return false;
	}
}
bool player::Trap_top(int vx, int vy, int old_x, int old_y, int size, int mapCx, int mapCy, int* map)
{
	int old_ball_left = (old_x - r) / size;

	int old_ball_top = (old_y - r) / size;

	int old_ball_bottom = (old_y + r - 1) / size;

	int old_ball_right = (old_x + r - 1) / size;

	int ball_left = (x - r) / size;

	int ball_top = (y - r) / size;

	int ball_bottom = (y + r - 1) / size;

	int ball_right = (x + r - 1) / size;

	//�E
	if (*(map + (old_ball_top * mapCx) + ball_right) == 4 || *(map + (old_ball_bottom * mapCx) + ball_right) == 4)
	{
		return true;
	}

	//��
	if (*(map + (old_ball_top * mapCx) + ball_left) == 4 || *(map + (old_ball_bottom * mapCx) + ball_left) == 4)
	{
		return true;
	}

	//��
	if (*(map + (ball_top * mapCx) + old_ball_left) == 4 || *(map + (ball_top * mapCx) + old_ball_right) == 4)
	{
		return true;
	}

	//��
	if (*(map + (ball_bottom * mapCx) + old_ball_left) == 4 || *(map + (ball_bottom * mapCx) + old_ball_right) == 4)
	{
		return true;
	}

	else
	{
		return false;
	}
}
bool player::Exit_key(int vx, int vy, int old_x, int old_y, int size, int mapCx, int mapCy, int* map)
{
	int old_ball_left = (old_x - r) / size;

	int old_ball_top = (old_y - r) / size;

	int old_ball_bottom = (old_y + r - 1) / size;

	int old_ball_right = (old_x + r - 1) / size;

	int ball_left = (x - r) / size;

	int ball_top = (y - r) / size;

	int ball_bottom = (y + r - 1) / size;

	int ball_right = (x + r - 1) / size;

	//�E
	if (*(map + (old_ball_top * mapCx) + ball_right) == 5 || *(map + (old_ball_bottom * mapCx) + ball_right) == 5)
	{
		return true;
	}

	//��
	if (*(map + (old_ball_top * mapCx) + ball_left) == 5 || *(map + (old_ball_bottom * mapCx) + ball_left) == 5)
	{
		return true;
	}

	//��
	if (*(map + (ball_top * mapCx) + old_ball_left) == 5 || *(map + (ball_top * mapCx) + old_ball_right) == 5)
	{
		return true;
	}

	//��
	if (*(map + (ball_bottom * mapCx) + old_ball_left) == 5 || *(map + (ball_bottom * mapCx) + old_ball_right) == 5)
	{
		return true;
	}

	else
	{
		return false;
	}
}