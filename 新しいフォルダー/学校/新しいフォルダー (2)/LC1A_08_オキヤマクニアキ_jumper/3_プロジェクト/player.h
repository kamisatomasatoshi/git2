#pragma once
//•ÏX“_‚È‚µ
class player
{
public:
	int x;
	int y;
	int r;

	int spead;

	int prev_x;
	int prev_y;

	bool jumpflag;
	int jump_spead;


	void Move(int vx, int vy);
	void PlayerInit(int xarg, int yarg, int rarg);
	void Col(int vx, int vy, int old_x, int old_y, int size, int mapCx, int mapCy, int* map);
	bool Trap(int vx, int vy, int old_x, int old_y, int size, int mapCx, int mapCy, int* map);
	bool Trap_top(int vx, int vy, int old_x, int old_y, int size, int mapCx, int mapCy, int* map);
	bool Exit_key(int vx, int vy, int old_x, int old_y, int size, int mapCx, int mapCy, int* map);
};