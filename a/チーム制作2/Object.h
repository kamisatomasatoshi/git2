#pragma once
#include"Struct.h"

class Object
{
public:

	//�N���X�ɍ\���̂��������
	//���W
	Transform transform;
	//�����蔻��p�̊p
	CollisionPoint collisionPoint;

	//�d��
	int hasGravity;
	//�󒆂ɂ��邩�ǂ���
	int isFlying;
	float gravitySpeed;

	float BottomYInfo;
	float BottomYMaptip;
	float BottomYHeight;
	float BottomYHeightPlus;
	float BottomYMaptipPlus;
	float TopYInfo;
	float TopYMaptip;
	float TopYHeight;
	float MoveCollision;

	//�d��
	void gravity();

	//��������
	void fallProcess();

	//���݈ʒu�𑪒肷��p�̊֐�
	void posInfo();

	void ObjectMoveCollision();

	//�R���X�g���N�^
	Object(Transform transform, CollisionPoint collisionPoint);
	//�f�X�g���N�^
	~Object();

private:

};

