#pragma once
#include"Struct.h"
#include"Object.h"

class Player
{
public:

	Transform playerTransform
	{
		100.0f,
		150.0f,
		0.0f,
		0.0f,
		16.0f,
		16.0f,
		2.0f,
		2.0f 
	};

	CollisionPoint collisionPoint
	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	};

	Object *object = new Object(playerTransform,collisionPoint);

	float defaultSpped;
	
	// ジャンプできる回数(1か0の時はジャンプ中)
	int jumpCount;
	//ジャンプカウントの管理用タイマー
	int jumpHeight;

	void PlayerMove();
	void PlayerDraw();
	void PlayerMoveCollision();

	Player();
	~Player();
};


