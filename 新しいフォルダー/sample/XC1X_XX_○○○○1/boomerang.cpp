#include "DxLib.h"
#include "boomerang.h"

//�~����
const double pi = 3.141592;

//�u�[�������̏�Ԃ�enum
enum boomerangState {
	hold,			//0,�v���C���[�������Ă��鎞
	fly2target,		//1,�^�[�Q�b�g�Ɍ������Ĕ��ł��鎞
	return2player,	//2,�v���C���[�̂��ƂɋA���Ă��Ă��鎞
};

void PlayerBoomerang(Object& player, Boomerang& boomerang, Mouse& mouseStructure, Transform& target, int isAirjump) {

	if (boomerang.isThrown == false) {
		//�^�[�Q�b�g�̈ʒu���}�E�X�̈ʒu�ɍ��킹��
		//target.x = mouseStructure.x;
		//target.y = mouseStructure.y;

		if (mouseStructure.x - 20 <= 0) {
			target.x = 0 + 20;
		}
		else if (mouseStructure.x + 20 >= 1280) {
			target.x = 1280 - 20;
		}
		else {
			target.x = mouseStructure.x;
		}

		if (mouseStructure.y - 20 <= 0) {
			target.y = 0 + 20;
		}
		else if (mouseStructure.y + 20 >= 768 - 192) {
			target.y = 768 - 192 - 20;
		}
		else {
			target.y = mouseStructure.y - target.r;
		}

		//�u�[�������̈ʒu���v���C���[�̈ʒu�ɍ��킹��
		boomerang.object.transform.x = player.transform.x;
		boomerang.object.transform.y = player.transform.y;

		int mouse = GetMouseInput();
		if (mouse & MOUSE_INPUT_LEFT) {
			if (isAirjump != 1) {
				if (mouseStructure.isLeftPush == false) {	//�����n�߂Ȃ�
					mouseStructure.isLeftPush = true;		//������Ă�t���O��true
					boomerang.isThrown = true;

					//�^�[�Q�b�g�ƃu�[�������̋������珉���x���v�Z
					boomerang.object.velocityX = (target.x - boomerang.object.transform.x) / 25;
					boomerang.object.velocityY = (target.y - boomerang.object.transform.y) / 25;

					//�u�[�������̏����x�����49�t���[���Ń^�[�Q�b�g�ɓ��B����悤�ȉ����x���v�Z
					boomerang.accerarationX = boomerang.object.velocityX / 49;
					boomerang.accerarationY = boomerang.object.velocityY / 49;
				}
			}
		}
		else {
			if (mouseStructure.isLeftPush == true) {	//������Ă�t���O��true�̎�
				mouseStructure.isLeftPush = false;		//������Ă�t���Ofalse�ɂ���
			}
		}
	}
	else if (boomerang.isThrown == true) {
		if (boomerang.state == hold) {		//�v���C���[�������Ă鎞
			boomerang.state = fly2target;	//�u�[�������̏�Ԃ��^�[�Q�b�g�Ɍ������Ĕ��ōs���Ă鎞�ɂ���
		}

		else if (boomerang.state == fly2target) {//�^�[�Q�b�g�Ɍ������Ĕ��ōs���Ă鎞

			//�u�[�������̑������v�Z
			boomerang.object.speedX = boomerang.object.velocityX - boomerang.accerarationX * boomerang.flyingTimer;
			boomerang.object.speedY = boomerang.object.velocityY - boomerang.accerarationY * boomerang.flyingTimer;
			boomerang.flyingTimer++;

			//�u�[���������^�[�Q�b�g�܂ŗ����Ƃ�
			if (boomerang.object.transform.x <= target.x + target.r && boomerang.object.transform.x >= target.x - target.r) {
				if (boomerang.object.transform.y <= target.y + target.r && boomerang.object.transform.y >= target.y - target.r) {

					//�u�[�������̏�Ԃ��v���C���[�̂��ƂɋA���Ă��Ă��鎞
					boomerang.state = return2player;
					//�u�[�������̓����Ɋւ���ϐ������ׂ�0�ɂ���
					boomerang.object.speedX = 0;
					boomerang.object.speedY = 0;
					boomerang.object.velocityX = 0;
					boomerang.object.velocityY = 0;
					boomerang.accerarationX = 0;
					boomerang.accerarationY = 0;
					boomerang.flyingTimer = 0;
				}
			}
		}

		else if (boomerang.state == return2player) {//�v���C���[�̂��ƂɋA���Ă��Ă��鎞

			//���x�x�N�g���ƌ������ׂ������̃x�N�g���̊O�ς��Ƃ�
			//�������v�Z
			if (boomerang.object.transform.y + boomerang.object.transform.r >= 768 - 192) {
				boomerang.crros.angle = -boomerang.crros.angle;
			}

			boomerang.object.speedX = boomerang.returnSpeed * boomerang.flyingTimer * cos(boomerang.crros.angle);
			boomerang.object.speedY = boomerang.returnSpeed * boomerang.flyingTimer * sin(boomerang.crros.angle);
			//�u�[�������ƃv���C���[�Ƃ̋������v�Z
			float b2pX = boomerang.object.transform.x - player.transform.x;
			float b2pY = boomerang.object.transform.y - player.transform.y;

			//�O�ς��v�Z
			boomerang.crros.first = boomerang.object.speedX * b2pY - boomerang.object.speedY * b2pX;
			if (boomerang.crros.first <= 0) {		//�e���猩�ēG�����Ȃ�
				boomerang.crros.angle += pi / 36;	//���ɋȂ���
			}
			else if (boomerang.crros.first >= 0) {	//�e���猩�ēG���E�Ȃ�
				boomerang.crros.angle += -pi / 36;	//�E�ɋȂ���
			}

			if (boomerang.flyingTimer <= 100) {
				boomerang.flyingTimer++;	//���ł鎞�Ԃ��C���N�������g
			}

			//�u�[�������̑��x���v�Z
			boomerang.object.speedX = boomerang.returnSpeed * boomerang.flyingTimer * cos(boomerang.crros.angle);
			boomerang.object.speedY = boomerang.returnSpeed * boomerang.flyingTimer * sin(boomerang.crros.angle);
			//�v���C���[�̔��a�͈̔͂ɓ��B������
			if (boomerang.object.transform.x <= player.transform.x + player.transform.r &&
				boomerang.object.transform.x >= player.transform.x - player.transform.r) {
				if (boomerang.object.transform.y <= player.transform.y + player.transform.r &&
					boomerang.object.transform.y >= player.transform.y - player.transform.r) {

					//�u�[�������̏�Ԃ��v���C���[�������Ă����Ԃɂ���
					boomerang.state = hold;

					//�u�[�������̓����Ɋւ���ϐ������ׂ�0�ɂ���
					boomerang.object.speedX = 0;
					boomerang.object.speedY = 0;
					boomerang.object.velocityX = 0;
					boomerang.object.velocityY = 0;
					boomerang.accerarationX = 0;
					boomerang.accerarationY = 0;
					boomerang.flyingTimer = 0;
					boomerang.isThrown = false;

				}
			}
		}

		//�u�[�������̍��W�Ƀu�[�������̑����𑫂�
		boomerang.object.transform.x += boomerang.object.speedX;
		boomerang.object.transform.y += boomerang.object.speedY;

	}

}