#pragma once
#include"Struct.h"

class Player
{
public:

	Transform transform;
	CollisionPoint collisionPoint;

	void PlayerMove();
	void PlayerDraw();

	Player(Transform transform,CollisionPoint collisionPoint);
	~Player();
};


