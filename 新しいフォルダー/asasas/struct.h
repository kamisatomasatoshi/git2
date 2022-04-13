#pragma once
typedef struct square
{
    float pos_x;
    float pos_y;
	float bottom_y_info;
	float top_y_info;
	float right_x_info;
	float left_x_info;
	float bottom_y_height_plus;
	float top_y_height;
	float bottom_y_height;
	float right_x_wide;
	float left_x_wide;
	int right_x_maptip;
	int left_x_maptip;
	int bottom_y_maptip;
	int top_y_maptip;
	int bottom_y_maptip_plus;
    float radius;
    float speed_x;
    float speed_y;
	float jump_speed;
};

//プレイヤーの情報

//自機の四角
square right_player =
{
	224.0f,//(96-16)
	848.0f,//(832-16)
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0,
	0,
	0,
	0,
	0,
	16.0f,
	0.0f,
	0.0f,
	2.0f,
};

square left_player =
{
	1264.0f,//(96-16)
	848.0f,//(832-16)
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0,
	0,
	0,
	0,
	0,
	16.0f,
	0.0f,
	0.0f,
	2.0f,
};