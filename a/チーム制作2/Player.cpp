#include"DxLib.h"
#include"Player.h"

//�R���X�g���N�^
//���W�̏�����
Player::Player()
{
	defaultSpped = 4.0f;
	jumpCount = 1;
	jumpHeight = 20;
}

//�f�X�g���N�^
Player::~Player()
{
	delete object;
}

void Player::PlayerMoveCollision()
{
	//�E��
	object->collisionPoint.rightTopX = (object->transform.posX + object->transform.radiusX - 1) / BLOCK_SIZE;
	object->collisionPoint.rightBottomX = (object->transform.posX + object->transform.radiusX - 1) / BLOCK_SIZE;
	//�E��
	object->collisionPoint.rightTopY = (object->transform.posY - object->transform.radiusY) / BLOCK_SIZE;
	object->collisionPoint.rightBottomY = (object->transform.posY + object->transform.radiusY - 1) / BLOCK_SIZE;
	//����
	object->collisionPoint.leftTopX = (object->transform.posX - object->transform.radiusX) / BLOCK_SIZE;
	object->collisionPoint.leftBottomX = (object->transform.posX - object->transform.radiusX) / BLOCK_SIZE;
	//����
	object->collisionPoint.leftTopY = (object->transform.posY - object->transform.radiusY) / BLOCK_SIZE;
	object->collisionPoint.leftBottomY = (object->transform.posY + object->transform.radiusY - 1) / BLOCK_SIZE;
}

void Player::PlayerMove()
{
	object->transform.oldX = object->transform.posX;
	object->transform.oldY = object->transform.posY;

	PlayerMoveCollision();

	if (keys[KEY_INPUT_A] == 1)
	{
		if (object->transform.posX > BLOCK_SIZE) //��ʓ��œ����悤�ɔ͈͂�ݒ�
		{
			object->collisionPoint.rightTopX = ((object->transform.posX - object->transform.speedX) + object->transform.radiusX - 1) / BLOCK_SIZE;
			object->collisionPoint.rightBottomX = ((object->transform.posX - object->transform.speedX) + object->transform.radiusX - 1) / BLOCK_SIZE;
			object->collisionPoint.leftTopX = ((object->transform.posX - object->transform.speedX) - object->transform.radiusX) / BLOCK_SIZE;
			object->collisionPoint.leftBottomX = ((object->transform.posX - object->transform.speedX) - object->transform.radiusX) / BLOCK_SIZE;
			object->collisionPoint.leftTopY = (object->transform.posY - object->transform.radiusX) / BLOCK_SIZE;
			object->collisionPoint.leftBottomY = (object->transform.posY + object->transform.radiusX - 1) / BLOCK_SIZE;

			if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX] == BLOCK)
			{
				object->transform.speedX /= 2;

				//�c�ׂ�ɂ����ׂ�̗����ɐi�߂�
				if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX + 1] != BLOCK && map[object->collisionPoint.leftTopY + 1][object->collisionPoint.leftTopX] != BLOCK)
				{

				}
				//�c�ׂ�ɂ͐i�߂Ȃ������ׂ�ɂ͐i�߂�ꍇ
				else if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX + 1] == BLOCK && map[object->collisionPoint.leftTopY + 1][object->collisionPoint.leftTopX] != BLOCK)
				{
					object->transform.posY = object->transform.oldY;
				}
				//�c�ׂ�ɂ͐i�߂邪���ׂ�ɂ͐i�߂Ȃ��ꍇ
				else if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX + 1] != BLOCK && map[object->collisionPoint.leftTopY + 1][object->collisionPoint.leftTopX] == BLOCK)
				{
					object->transform.posX = object->transform.oldX;
				}
				//�c�ׂ�ɂ����ׂ�ɂ��i�߂Ȃ��ꍇ
				else if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX + 1] == BLOCK && map[object->collisionPoint.leftTopY + 1][object->collisionPoint.leftTopX] == BLOCK)
				{
					object->transform.posY = object->transform.oldY;
					object->transform.posX = object->transform.oldX;
				}
			}
			else if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX] == BLOCK)
			{
				object->transform.speedX /= 2;

				//�c�ׂ�ɂ����ׂ�̗����ɐi�߂�
				if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] != BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] != BLOCK)
				{

				}
				//�c�ׂ�ɂ͐i�߂Ȃ������ׂ�ɂ͐i�߂�ꍇ
				else if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] == BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] != BLOCK)
				{
					object->transform.posY = object->transform.oldY;
				}
				//�c�ׂ�ɂ͐i�߂邪���ׂ�ɂ͐i�߂Ȃ��ꍇ
				else if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] != BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] == BLOCK)
				{
					object->transform.posX = object->transform.oldX;
				}
				//�c�ׂ�ɂ����ׂ�ɂ��i�߂Ȃ��ꍇ
				else if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] == BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] == BLOCK)
				{
					object->transform.posY = object->transform.oldY;
					object->transform.posX = object->transform.oldX;
				}
			}
			else
			{
				object->transform.posX -= object->transform.speedX;
			}
		}
	}

	if (keys[KEY_INPUT_D] == 1)
	{
		if (object->transform.posX < MAP_SIZE_X * BLOCK_SIZE) //��ʓ��œ����悤�ɔ͈͂�ݒ�
		{
			object->collisionPoint.rightTopX = ((object->transform.posX + object->transform.speedX) + object->transform.radiusX - 1) / BLOCK_SIZE;
			object->collisionPoint.rightBottomX = ((object->transform.posX + object->transform.speedX) + object->transform.radiusX - 1) / BLOCK_SIZE;
			object->collisionPoint.leftTopX = ((object->transform.posX + object->transform.speedX) - object->transform.radiusX) / BLOCK_SIZE;
			object->collisionPoint.leftBottomX = ((object->transform.posX + object->transform.speedX) - object->transform.radiusX) / BLOCK_SIZE;
			object->collisionPoint.rightTopY = (object->transform.posY - object->transform.radiusY) / BLOCK_SIZE;
			object->collisionPoint.rightBottomY = (object->transform.posY + object->transform.radiusY - 1) / BLOCK_SIZE;

			//�u���b�N�ɓ��������ۂ̉����߂��̏���
			if (map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX] == BLOCK)
			{
				//�c�ׂ�ɂ����ׂ�̗����ɐi�߂�
				if (map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX - 1] != BLOCK && map[object->collisionPoint.rightTopY + 1][object->collisionPoint.rightTopX] != BLOCK)
				{

				}
				//�c�ׂ�ɂ͐i�߂Ȃ������ׂ�ɂ͐i�߂�ꍇ
				else if (map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX - 1] == BLOCK && map[object->collisionPoint.rightTopY + 1][object->collisionPoint.rightTopX] != BLOCK)
				{
					object->transform.posY = object->transform.oldY;
				}
				//�c�ׂ�ɂ͐i�߂邪���ׂ�ɂ͐i�߂Ȃ��ꍇ
				else if (map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX - 1] != BLOCK && map[object->collisionPoint.rightTopY + 1][object->collisionPoint.rightTopX] == BLOCK)
				{
					object->transform.posX = object->transform.oldX;
				}
				//�c�ׂ�ɂ����ׂ�ɂ��i�߂Ȃ��ꍇ
				else if (map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX - 1] == BLOCK && map[object->collisionPoint.rightTopY + 1][object->collisionPoint.rightTopX] == BLOCK)
				{
					object->transform.posY = object->transform.oldY;
					object->transform.posX = object->transform.oldX;
				}
			}
			else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX] == BLOCK)
			{
				//�c�ׂ�ɂ����ׂ�̗����ɐi�߂�
				if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] != BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] != BLOCK)
				{

				}
				//�c�ׂ�ɂ͐i�߂Ȃ������ׂ�ɂ͐i�߂�ꍇ
				else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] == BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] != BLOCK)
				{
					object->transform.posY = object->transform.oldY;
				}
				//�c�ׂ�ɂ͐i�߂邪���ׂ�ɂ͐i�߂Ȃ��ꍇ
				else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] != BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] == BLOCK)
				{
					object->transform.posX = object->transform.oldX;
				}
				//�c�ׂ�ɂ����ׂ�ɂ��i�߂Ȃ��ꍇ
				else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] == BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] == BLOCK)
				{
					object->transform.posY = object->transform.oldY;
					object->transform.posX = object->transform.oldX;
				}
			}
			else
			{
				object->transform.posX += object->transform.speedX;
			}
		}
	}

	if (keys[KEY_INPUT_S] == 1)
	{
		if (object->transform.posY < MAP_SIZE_Y * BLOCK_SIZE) //��ʓ��œ����悤�ɔ͈͂�ݒ�
		{
			object->collisionPoint.leftBottomX = (object->transform.posX - object->transform.radiusX) / BLOCK_SIZE;
			object->collisionPoint.rightBottomX = (object->transform.posX + object->transform.radiusX - 1) / BLOCK_SIZE;
			object->collisionPoint.leftTopY = ((object->transform.posY - object->transform.radiusY) + object->transform.speedY) / BLOCK_SIZE;
			object->collisionPoint.rightTopY = ((object->transform.posY - object->transform.radiusY) + object->transform.speedY) / BLOCK_SIZE;
			object->collisionPoint.leftBottomY = ((object->transform.posY + object->transform.radiusY - 1) + object->transform.speedY) / BLOCK_SIZE;
			object->collisionPoint.rightBottomY = ((object->transform.posY + object->transform.radiusY - 1) + object->transform.speedY) / BLOCK_SIZE;

			//�u���b�N�ɓ��������ۂ̉����߂��̏���
			if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX] == BLOCK)
			{
				//�c�ׂ�ɂ����ׂ�̗����ɐi�߂�
				if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] != BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] != BLOCK)
				{

				}
				//�c�ׂ�ɂ͐i�߂Ȃ������ׂ�ɂ͐i�߂�ꍇ
				else if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] == BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] != BLOCK)
				{
					object->transform.posY = object->transform.oldY;
				}
				//�c�ׂ�ɂ͐i�߂邪���ׂ�ɂ͐i�߂Ȃ��ꍇ
				else if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] != BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] == BLOCK)
				{
					object->transform.posX = object->transform.oldX;
				}
				//�c�ׂ�ɂ����ׂ�ɂ��i�߂Ȃ��ꍇ
				else if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] == BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] == BLOCK)
				{
					object->transform.posY = object->transform.oldY;
					object->transform.posX = object->transform.oldX;
				}
			}
			else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX] == BLOCK)
			{
				//�c�ׂ�ɂ����ׂ�̗����ɐi�߂�
				if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] != BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] != BLOCK)
				{

				}
				//�c�ׂ�ɂ͐i�߂Ȃ������ׂ�ɂ͐i�߂�ꍇ
				else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] == BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] != BLOCK)
				{
					object->transform.posY = object->transform.oldY;
				}
				//�c�ׂ�ɂ͐i�߂邪���ׂ�ɂ͐i�߂Ȃ��ꍇ
				else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] != BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] == BLOCK)
				{
					object->transform.posX = object->transform.oldX;
				}
				//�c�ׂ�ɂ����ׂ�ɂ��i�߂Ȃ��ꍇ
				else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] == BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] == BLOCK)
				{
					object->transform.posY = object->transform.oldY;
					object->transform.posX = object->transform.oldX;
				}
			}
			else
			{
				object->transform.posY += object->transform.speedY;
			}
		}
	}	

	//�X�s�[�h���K��l�ɖ߂�
	object->transform.speedX = defaultSpped;
	object->transform.speedY = defaultSpped;

	//�ǂ����̃}�b�v�����������瑬�x�𔼕��ɂ���B
	if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX] == BLOCK || map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX] == BLOCK || map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX] == BLOCK || map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX] == BLOCK)
	{
		object->transform.speedX /= 2;
		object->transform.speedY /= 2;
	}
	//�����Ȃ��΂߈ړ��̍ۂɁA�X�s�[�h�𔼕��ɂ���B
	else if (keys[KEY_INPUT_W] == 1 && keys[KEY_INPUT_D] == 1)
	{
		object->transform.speedX /= 2;
		object->transform.speedY /= 2;
	}
	else if (keys[KEY_INPUT_W] == 1 && keys[KEY_INPUT_A] == 1)
	{
		object->transform.speedX /= 2;
		object->transform.speedY /= 2;
	}
	else if (keys[KEY_INPUT_S] == 1 && keys[KEY_INPUT_D] == 1)
	{
		object->transform.speedX /= 2;
		object->transform.speedY /= 2;
	}
	else if (keys[KEY_INPUT_S] == 1 && keys[KEY_INPUT_A] == 1)
	{
		object->transform.speedX /= 2;
		object->transform.speedY /= 2;
	}

	object->gravity();

	//�v���C���[�̃W�����v
	if (jumpCount > 0) {
		if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX] != BLOCK || map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX] != BLOCK) {
			if (keys[KEY_INPUT_W] == 1 && prev[KEY_INPUT_W] == 0) {
				object->isFlying = 1;
				object->gravitySpeed = 0;
				jumpCount -= 1;
				jumpHeight = MAX_JUMP;

				////���ʉ�
				//StopSoundMem(jumpSound);
				//if (CheckSoundMem(jumpSound) == 0) {
				//	PlaySoundMem(jumpSound, DX_PLAYTYPE_BACK, true);
				//}
			}
		}
	}
	//�W�����v�̎d�g��
	if (jumpCount < 1)
	{
		if (object->isFlying == 1)
		{
			jumpHeight--;
			if (jumpHeight < -10) {
				jumpHeight = -10;
			}

			object->transform.posY -= jumpHeight;
		}
	}

	//�n�ʂɒ��n������ēx�W�����v�ł���悤�ɂ���
	if (jumpCount == 0) {
		if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX] == BLOCK || map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX] == BLOCK)
		{
			jumpCount = 1;
		}
	}

	object->fallProcess();

	////���ł���Ƃ�
	//if (jumpCount < 1) {
	//	//������Ńu���b�N�ɂԂ��������̏���
	//	if (object->transform.posY <= (object->BottomYHeightPlus - object->transform.radiusY))
	//	{
	//		if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX] == BLOCK || map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX] == BLOCK) {
	//			jumpHeight = 0;
	//		}
	//	}
	//}

	//�������Ƀu���b�N�ɂԂ��������̏���
	if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX] == BLOCK || map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX] == BLOCK)
	{
		jumpCount = 1;
		jumpHeight = 20;
	}

	//�n�ʂƐڂ��Ă���Ƃ�
	if (object->transform.posY >= (MAP_HEIGHT - 1) * BLOCK_SIZE - object->transform.radiusY) 
	{
		jumpCount = 1;
		jumpHeight = 20;
	}


}

void Player::PlayerDraw()
{
	//���@�𒆐S�Ƃ���3�~3�̐����`�̕`��
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			DrawBox((object->transform.posX - object->transform.radiusX) + (x * BLOCK_SIZE), (object->transform.posY - object->transform.radiusY) + (y * BLOCK_SIZE),
				(object->transform.posX + object->transform.radiusX) + (x * BLOCK_SIZE), (object->transform.posY + object->transform.radiusY) + (y * BLOCK_SIZE), GetColor(17, 167, 177), FALSE);
		}
	}

	DrawFormatString(200, 200, GetColor(255, 255, 255), "playerTransform.posX %f", playerTransform.posX);
	DrawFormatString(200, 300, GetColor(255, 255, 255), "object->transform.posX %f", object->transform.posX);
	DrawFormatString(200, 320, GetColor(255, 255, 255), "object->isFlying %d", object->isFlying);
	DrawFormatString(200, 340, GetColor(255, 255, 255), "jumpCount %d", jumpCount);

	//DrawFormatString(200, 300, GetColor(255, 255, 255), "object->isFlying %f", object->isFlying);

}
