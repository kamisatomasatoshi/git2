#include"Object.h"

//�R���X�g���N�^
Object::Object(Transform transform, CollisionPoint collisionPoint)
{
	this->transform = transform;
	this->collisionPoint = collisionPoint;
	hasGravity = 1;
	isFlying = 0;
	gravitySpeed = 2.0f;

	BottomYInfo = 0;
	BottomYMaptip = 0;
	BottomYHeight = 0;
	BottomYHeightPlus = 0;
	BottomYMaptipPlus = 0;
	TopYInfo = 0;
	TopYMaptip = 0;
	TopYHeight = 0;
}

//�f�X�g���N�^
Object::~Object()
{
}

//���݈ʒu�̏��֐��i�d�͏����Ŏg���j
void Object::posInfo()
{
	////���݈ʒu�̒�ӂ̏��
	//BottomYInfo = transform.posY + transform.radiusY - 1;
	////�����݈ʒu�̒�ӂ̃}�b�v�`�b�v���(��ӂ̏�񂩂�}�b�v�`�b�v��ł̂ǂ̐����ɂ��邩���v�Z����)
	//BottomYMaptip = (transform.posY + transform.radiusY - 1) / BLOCK_SIZE;
	////����ӂ��߂荞�񂾎��ɖ߂��p�̃}�b�v��y���W
	//BottomYHeight = (BottomYMaptip)*BLOCK_SIZE;

	//���ݒn���P����y���W�B���@�̒�ӂ̍��W�͈���̍����y���W�ɂȂ邽�߁B(���2�s����}�b�v��̎��@�̐�������ꂽ�̂ŁA�Œ肷��ʒu���w�肵�ău���b�N�T�C�Y�������Ă�����)
	BottomYHeightPlus = (BottomYMaptip + 1) * BLOCK_SIZE;
	//���ݒn���P���̃}�b�v�`�b�v�̏��
	BottomYMaptipPlus = (BottomYHeightPlus / BLOCK_SIZE);

	//���݈ʒu�̒��_�̏�� 
	TopYInfo = transform.posY - transform.radiusY;
	 
	 
	//���݈ʒu�̒��_�̃}�b�v�`�b�v���
	TopYMaptip = (transform.oldY - transform.radiusY) / BLOCK_SIZE;
	//���_�����l�ɌŒ肷�邽�߂�y���W���o�����߂�y���W�����߂�B
	TopYHeight = (TopYMaptip + 1) * BLOCK_SIZE;
}

//�e�p�̌��ݒn�̍��W�v�Z
void Object::ObjectMoveCollision()
{
	//�E��
	collisionPoint.rightTopX = (transform.posX + transform.radiusX - 1) / BLOCK_SIZE;
	collisionPoint.rightBottomX = (transform.posX + transform.radiusX - 1) / BLOCK_SIZE;
	//�E��
	collisionPoint.rightTopY = (transform.posY - transform.radiusY) / BLOCK_SIZE;
	collisionPoint.rightBottomY = (transform.posY + transform.radiusY - 1) / BLOCK_SIZE;
	//����
	collisionPoint.leftTopX = (transform.posX - transform.radiusX) / BLOCK_SIZE;
	collisionPoint.leftBottomX = (transform.posX - transform.radiusX) / BLOCK_SIZE;
	//����
	collisionPoint.leftTopY = (transform.posY - transform.radiusY) / BLOCK_SIZE;
	collisionPoint.leftBottomY = (transform.posY + transform.radiusY - 1) / BLOCK_SIZE;

}

//�d��
void Object::gravity()
{
	//���Ƀu���b�N���Ȃ���Η������鏈��
	if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX] != BLOCK && map[collisionPoint.rightBottomY][collisionPoint.rightBottomX] != BLOCK && hasGravity == 1) {
		if (transform.posY + transform.radiusY <= MAP_SIZE_Y * BLOCK_SIZE)
		{
			if (isFlying == 0) {
				gravitySpeed--;

				transform.posY -= gravitySpeed;

				if (gravitySpeed < -10) {
					gravitySpeed = -10;
				}
			}
		}
	}
}

void Object::fallProcess()
{
	posInfo();

	ObjectMoveCollision();

	//�󒆂Ȃǂ̑���ɂ��鎞��Y���W���Œ�
	if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX] == BLOCK || map[collisionPoint.rightBottomY][collisionPoint.rightBottomX] == BLOCK) {
		transform.posY = TopYHeight - transform.radiusY;

		gravitySpeed = 0;
		isFlying = 0;
		
	}

	//�n�ʂɂ߂荞�݂Ȃ��悤�ɑ΍�
	if (transform.posY >= (MAP_HEIGHT - 1) * BLOCK_SIZE - transform.radiusY) {
		transform.posY = (MAP_HEIGHT - 1) * BLOCK_SIZE - transform.radiusY;

		isFlying = 0;
	};
}
