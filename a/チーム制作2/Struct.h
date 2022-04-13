#pragma once
#include"Maptip.h"

typedef struct Transform
{
	//X座標
	float posX;
	//Y座標
	float posY;
	//１フレーム前の座標
	float oldX;
	float oldY;

	//横半径
	float radiusX;
	//縦半径
	float radiusY;
	//X軸のスピード
	float speedX;
	//Y軸のスピード
	float speedY;
}Transform;

typedef struct CollisionPoint 
{
	//マップチップ上での座標なのでint(整数値)で宣言
	int leftTopX;
	int leftTopY;
	int rightTopX;
	int rightTopY;
	int rightBottomX;
	int rightBottomY;
	int leftBottomX;
	int leftBottomY;

}CollisionPoint;