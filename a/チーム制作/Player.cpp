#include"DxLib.h"
#include"Player.h"

//�R���X�g���N�^
//���W�̏�����
Player::Player(Transform transform, CollisionPoint collisionPoint)
{
	this->transform = transform;
	this->collisionPoint = collisionPoint;
}

//�f�X�g���N�^
Player::~Player()
{
}

void Player::PlayerMove()
{

	transform.oldX = transform.posX;
	transform.oldY = transform.posY;

	//�E��
	collisionPoint.rightTopX = (transform.posX + transform.radiusX - 1) / BLOCK_SIZE;
	collisionPoint.rightTopY = (transform.posY + transform.radiusY) / BLOCK_SIZE;
	//�E��
	collisionPoint.rightTopX = (transform.posX + transform.radiusX - 1) / BLOCK_SIZE;
	collisionPoint.rightTopY = (transform.posY + transform.radiusY - 1) / BLOCK_SIZE;
	//����
	collisionPoint.rightTopX = (transform.posX + transform.radiusX) / BLOCK_SIZE;
	collisionPoint.rightTopY = (transform.posY + transform.radiusY) / BLOCK_SIZE;
	//����
	collisionPoint.rightTopX = (transform.posX + transform.radiusX) / BLOCK_SIZE;
	collisionPoint.rightTopY = (transform.posY + transform.radiusY - 1) / BLOCK_SIZE;

	/*if (keys[KEY_INPUT_D] == 1)
	{
		collisionPoint.rightTopX = ((transform.posX + transform.radiusX - 1) + transform.speedX) / BLOCK_SIZE;
		collisionPoint.rightBottomX = ((transform.posX + transform.radiusX - 1) + transform.radiusX - 1) / BLOCK_SIZE;
		if (map[collisionPoint.rightTopY][collisionPoint.rightTopX] == 0 && map[collisionPoint.rightBottomY][collisionPoint.rightBottomX] == 0)
		{
			transform.posX += transform.speedX;
		}
	}*/
	/*if (keys[KEY_INPUT_A] == 1)
	{
		collisionPoint.leftTopX = (transform.posX - transform.radiusX - transform.speedX) / BLOCK_SIZE;
		collisionPoint.leftBottomX = (transform.posX - transform.radiusX - transform.speedX) / BLOCK_SIZE;
		if (map[collisionPoint.leftTopY][collisionPoint.leftTopX] == 0 && map[collisionPoint.leftBottomY][collisionPoint.leftBottomX] == 0)
		{
			transform.posX -= transform.speedX;
		}
	}*/

	/*if (keys[KEY_INPUT_W] == 1)
	{
		transform.posY -= transform.speedY;
	}*/
	/*if (keys[KEY_INPUT_S] == 1)
	{
		transform.posY += transform.speedY;
	}*/

	if (keys[KEY_INPUT_A] == 1)
	{
		if (transform.posX > BLOCK_SIZE) //��ʓ��œ����悤�ɔ͈͂�ݒ�
		{
			collisionPoint.rightTopX = ((transform.posX - transform.speedX) + transform.radiusX - 1) / BLOCK_SIZE;
			collisionPoint.rightBottomX = ((transform.posX - transform.speedX) + transform.radiusX - 1) / BLOCK_SIZE;
			collisionPoint.leftTopX = ((transform.posX - transform.speedX) - transform.radiusX) / BLOCK_SIZE;
			collisionPoint.leftBottomX = ((transform.posX - transform.speedX) - transform.radiusX) / BLOCK_SIZE;
			collisionPoint.leftTopY = (transform.posY - transform.radiusX) / BLOCK_SIZE;
			collisionPoint.leftBottomY = (transform.posY + transform.radiusX - 1) / BLOCK_SIZE;

			if (map[collisionPoint.leftTopY][collisionPoint.leftTopX] == BLOCK)
			{
				transform.speedX /= 2;

				//�c�ׂ�ɂ����ׂ�̗����ɐi�߂�
				if (map[collisionPoint.leftTopY][collisionPoint.leftTopX + 1] != BLOCK && map[collisionPoint.leftTopY + 1][collisionPoint.leftTopX] != BLOCK)
				{

				}
				//�c�ׂ�ɂ͐i�߂Ȃ������ׂ�ɂ͐i�߂�ꍇ
				else if (map[collisionPoint.leftTopY][collisionPoint.leftTopX + 1] == BLOCK && map[collisionPoint.leftTopY + 1][collisionPoint.leftTopX] != BLOCK)
				{
					transform.posY = transform.oldY;
					/*scrollY = transform.oldY;*/
				}
				//�c�ׂ�ɂ͐i�߂邪���ׂ�ɂ͐i�߂Ȃ��ꍇ
				else if (map[collisionPoint.leftTopY][collisionPoint.leftTopX + 1] != BLOCK && map[collisionPoint.leftTopY + 1][collisionPoint.leftTopX] == BLOCK)
				{
					transform.posX = transform.oldX;
				}
				//�c�ׂ�ɂ����ׂ�ɂ��i�߂Ȃ��ꍇ
				else if (map[collisionPoint.leftTopY][collisionPoint.leftTopX + 1] == BLOCK && map[collisionPoint.leftTopY + 1][collisionPoint.leftTopX] == BLOCK)
				{
					transform.posY = transform.oldY;
					transform.posX = transform.oldX;
				}
			}
			else if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX] == BLOCK)
			{
				transform.speedX /= 2;

				//�c�ׂ�ɂ����ׂ�̗����ɐi�߂�
				if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] != BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] != BLOCK)
				{

				}
				//�c�ׂ�ɂ͐i�߂Ȃ������ׂ�ɂ͐i�߂�ꍇ
				else if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] == BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] != BLOCK)
				{
					transform.posY = transform.oldY;
				}
				//�c�ׂ�ɂ͐i�߂邪���ׂ�ɂ͐i�߂Ȃ��ꍇ
				else if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] != BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] == BLOCK)
				{
					transform.posX = transform.oldX;
				}
				//�c�ׂ�ɂ����ׂ�ɂ��i�߂Ȃ��ꍇ
				else if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] == BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] == BLOCK)
				{
					transform.posY = transform.oldY;
					transform.posX = transform.oldX;
				}
			}
			else
			{
				transform.posX -= transform.speedX;
			}
		}
	}

	if (keys[KEY_INPUT_D] == 1)
	{
		if (transform.posX < MAP_SIZE_X * BLOCK_SIZE) //��ʓ��œ����悤�ɔ͈͂�ݒ�
		{
			collisionPoint.rightTopX = ((transform.posX + transform.speedX) + transform.radiusX - 1) / BLOCK_SIZE;
			collisionPoint.rightBottomX = ((transform.posX + transform.speedX) + transform.radiusX - 1) / BLOCK_SIZE;
			collisionPoint.leftTopX = ((transform.posX + transform.speedX) - transform.radiusX) / BLOCK_SIZE;
			collisionPoint.leftBottomX = ((transform.posX + transform.speedX) - transform.radiusX) / BLOCK_SIZE;
			collisionPoint.rightTopY = (transform.posY - transform.radiusY) / BLOCK_SIZE;
			collisionPoint.rightBottomY = (transform.posY + transform.radiusY - 1) / BLOCK_SIZE;

			//�u���b�N�ɓ��������ۂ̉����߂��̏���
			if (map[collisionPoint.rightTopY][collisionPoint.rightTopX] == BLOCK)
			{
				//�c�ׂ�ɂ����ׂ�̗����ɐi�߂�
				if (map[collisionPoint.rightTopY][collisionPoint.rightTopX - 1] != BLOCK && map[collisionPoint.rightTopY + 1][collisionPoint.rightTopX] != BLOCK)
				{

				}
				//�c�ׂ�ɂ͐i�߂Ȃ������ׂ�ɂ͐i�߂�ꍇ
				else if (map[collisionPoint.rightTopY][collisionPoint.rightTopX - 1] == BLOCK && map[collisionPoint.rightTopY + 1][collisionPoint.rightTopX] != BLOCK)
				{
					transform.posY = transform.oldY;
				}
				//�c�ׂ�ɂ͐i�߂邪���ׂ�ɂ͐i�߂Ȃ��ꍇ
				else if (map[collisionPoint.rightTopY][collisionPoint.rightTopX - 1] != BLOCK && map[collisionPoint.rightTopY + 1][collisionPoint.rightTopX] == BLOCK)
				{
					transform.posX = transform.oldX;
				}
				//�c�ׂ�ɂ����ׂ�ɂ��i�߂Ȃ��ꍇ
				else if (map[collisionPoint.rightTopY][collisionPoint.rightTopX - 1] == BLOCK && map[collisionPoint.rightTopY + 1][collisionPoint.rightTopX] == BLOCK)
				{
					transform.posY = transform.oldY;
					transform.posX = transform.oldX;
				}
			}
			else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX] == BLOCK)
			{
				//�c�ׂ�ɂ����ׂ�̗����ɐi�߂�
				if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] != BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] != BLOCK)
				{

				}
				//�c�ׂ�ɂ͐i�߂Ȃ������ׂ�ɂ͐i�߂�ꍇ
				else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] == BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] != BLOCK)
				{
					transform.posY = transform.oldY;
				}
				//�c�ׂ�ɂ͐i�߂邪���ׂ�ɂ͐i�߂Ȃ��ꍇ
				else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] != BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] == BLOCK)
				{
					transform.posX = transform.oldX;
				}
				//�c�ׂ�ɂ����ׂ�ɂ��i�߂Ȃ��ꍇ
				else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] == BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] == BLOCK)
				{
					transform.posY = transform.oldY;
					transform.posX = transform.oldX;
				}
			}
			else
			{
				transform.posX += transform.speedX;
			}
		}
	}

	if (keys[KEY_INPUT_S] == 1)
	{
		if (transform.posY < MAP_SIZE_Y * BLOCK_SIZE) //��ʓ��œ����悤�ɔ͈͂�ݒ�
		{
			collisionPoint.leftBottomX = (transform.posX - transform.radiusX) / BLOCK_SIZE;
			collisionPoint.rightBottomX = (transform.posX + transform.radiusX - 1) / BLOCK_SIZE;
			collisionPoint.leftTopY = ((transform.posY - transform.radiusY) + transform.speedY) / BLOCK_SIZE;
			collisionPoint.rightTopY = ((transform.posY - transform.radiusY) + transform.speedY) / BLOCK_SIZE;
			collisionPoint.leftBottomY = ((transform.posY + transform.radiusY - 1) + transform.speedY) / BLOCK_SIZE;
			collisionPoint.rightBottomY = ((transform.posY + transform.radiusY - 1) + transform.speedY) / BLOCK_SIZE;

			//�u���b�N�ɓ��������ۂ̉����߂��̏���
			if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX] == BLOCK)
			{
				//�c�ׂ�ɂ����ׂ�̗����ɐi�߂�
				if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] != BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] != BLOCK)
				{

				}
				//�c�ׂ�ɂ͐i�߂Ȃ������ׂ�ɂ͐i�߂�ꍇ
				else if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] == BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] != BLOCK)
				{
					transform.posY = transform.oldY;
				}
				//�c�ׂ�ɂ͐i�߂邪���ׂ�ɂ͐i�߂Ȃ��ꍇ
				else if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] != BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] == BLOCK)
				{
					transform.posX = transform.oldX;
				}
				//�c�ׂ�ɂ����ׂ�ɂ��i�߂Ȃ��ꍇ
				else if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] == BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] == BLOCK)
				{
					transform.posY = transform.oldY;
					transform.posX = transform.oldX;
				}
			}
			else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX] == BLOCK)
			{
				//�c�ׂ�ɂ����ׂ�̗����ɐi�߂�
				if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] != BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] != BLOCK)
				{

				}
				//�c�ׂ�ɂ͐i�߂Ȃ������ׂ�ɂ͐i�߂�ꍇ
				else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] == BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] != BLOCK)
				{
					transform.posY = transform.oldY;
				}
				//�c�ׂ�ɂ͐i�߂邪���ׂ�ɂ͐i�߂Ȃ��ꍇ
				else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] != BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] == BLOCK)
				{
					transform.posX = transform.oldX;
				}
				//�c�ׂ�ɂ����ׂ�ɂ��i�߂Ȃ��ꍇ
				else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] == BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] == BLOCK)
				{
					transform.posY = transform.oldY;
					transform.posX = transform.oldX;
				}
			}
			else
			{
				transform.posY += transform.speedY;
			}
		}
	}

}

void Player::PlayerDraw()
{
	//���@�𒆐S�Ƃ���3�~3�̐����`�̕`��
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			DrawBox((transform.posX - transform.radiusX) + (x * BLOCK_SIZE), (transform.posY - transform.radiusY) + (y * BLOCK_SIZE),
				(transform.posX + transform.radiusX) + (x * BLOCK_SIZE), (transform.posY + transform.radiusY) + (y * BLOCK_SIZE), GetColor(17, 167, 177), FALSE);
		}
	}
}
