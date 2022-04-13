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
	
	// �W�����v�ł����(1��0�̎��̓W�����v��)
	int jumpCount;
	//�W�����v�J�E���g�̊Ǘ��p�^�C�}�[
	int jumpHeight;

	void PlayerMove();
	void PlayerDraw();
	void PlayerMoveCollision();

	Player();
	~Player();
};


