#pragma once
#include"Maptip.h"

typedef struct Transform
{
	//X���W
	float posX;
	//Y���W
	float posY;
	//�P�t���[���O�̍��W
	float oldX;
	float oldY;

	//�����a
	float radiusX;
	//�c���a
	float radiusY;
	//X���̃X�s�[�h
	float speedX;
	//Y���̃X�s�[�h
	float speedY;
}Transform;

typedef struct CollisionPoint 
{
	//�}�b�v�`�b�v��ł̍��W�Ȃ̂�int(�����l)�Ő錾
	int leftTopX;
	int leftTopY;
	int rightTopX;
	int rightTopY;
	int rightBottomX;
	int rightBottomY;
	int leftBottomX;
	int leftBottomY;

}CollisionPoint;