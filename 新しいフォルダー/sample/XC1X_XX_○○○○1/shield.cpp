#include "DxLib.h"
#include "shield.h"
#include <math.h>

//�~����
const double pi = 3.141592;

////�V�[���h�̏�Ԃ�enum
//enum shieldState {
//	nomal,		//0,�ʏ펞
//	scraped,	//1,��ꂽ��
//	recharge,	//2,���`���[�W��
//	crack,		//3,���ꂽ��
//};

void PlayerShield(
	Object& player,
	Shield& playerShield,
	Mouse& mouseStructure,
	Boomerang& boomerang
) {

	//angle�̒l���擾
	playerShield.crros[0].angle = atan2((double)mouseStructure.y - player.transform.y, (double)mouseStructure.x - player.transform.x);

	//�O�p�`�̒��_�̈ʒu���擾
	playerShield.point1.x = player.transform.x + cos(playerShield.crros[0].angle + pi / 6 * playerShield.level / playerShield.max) * playerShield.radius;
	playerShield.point1.y = player.transform.y + sin(playerShield.crros[0].angle + pi / 6 * playerShield.level / playerShield.max) * playerShield.radius;
	playerShield.point2.x = player.transform.x + cos(playerShield.crros[0].angle - pi / 6 * playerShield.level / playerShield.max) * playerShield.radius;
	playerShield.point2.y = player.transform.y + sin(playerShield.crros[0].angle - pi / 6 * playerShield.level / playerShield.max) * playerShield.radius;

	int mouse = GetMouseInput();

	if (boomerang.isThrown == false) {
		// �}�E�X�̉E�{�^����������Ă�Ƃ�
		if (mouse & MOUSE_INPUT_RIGHT) {
			if (0 < playerShield.level) {
				if (mouseStructure.isRightPush == false) {//�����n�߂Ȃ�
					//������Ă�t���O��true
					mouseStructure.isRightPush = true;
					playerShield.level -= 10;				//�V�[���h�W�J���̏���
					playerShield.parryTimer = 5;			//�p���B�̃^�C�}�[��5����

					playerShield.isShieldOn = true;			//�V�[���h�W�J�̃t���O��true�ɂ���
					if (playerShield.level <= 0) {			//�����V�[���h�c�ʂ�0�ȉ���������
						playerShield.level = 0;				//�V�[���h�c�ʂ�0�ɂ���
						playerShield.state = crack;			//�V�[���h�̏�Ԃ����ꂽ���ɂ���
						playerShield.rechargeTimer = 500;	//�V�[���h���`���[�W�̃^�C�}�[��500(10�b)����
					}
				}
				//�@�O�t���[������E�{�^����
				//�@�����ꑱ���Ă��鎞��else�ɗ���
				else {
					playerShield.level--;					//���t���[���V�[���h�c�ʂ��f�N�������g
					playerShield.state = scraped;			//�V�[���h�̏�Ԃ���ꂽ���ɂ���
					playerShield.rechargeTimer = 250;		//�V�[���h���`���[�W�̃^�C�}�[��250(5�b)����
					if (0 < playerShield.parryTimer) {		//�p���B�^�C�}�[��0���傫�����
						playerShield.parryTimer--;			//�p���B�^�C�}�[���f�N�������g
					}
					if (playerShield.level <= 0) {			//�V�[���h�c�ʂ�0�ȉ��ɂȂ�����
						playerShield.level = 0;				//�V�[���h�c�ʂ�0�ɂ���
						playerShield.state = crack;			//�V�[���h�̏�Ԃ����ꂽ���ɂ���
						playerShield.rechargeTimer = 500;	//�V�[���h���`���[�W�̃^�C�}�[��500(10�b)����
					}
				}
			}
		}
		//�E�{�^��������ĂȂ��ꍇ
		else {
			if (mouseStructure.isRightPush == true) {	//������Ă�t���O��true�̎�
				mouseStructure.isRightPush = false;		//������Ă�t���Ofalse�ɂ���
				playerShield.isShieldOn = false;		//�V�[���h�W�J�̃t���O��false�ɂ���
			}
		}
	}

	if (playerShield.state == scraped) {			//�V�[���h�̏�Ԃ���ꂽ���Ȃ�
		playerShield.rechargeTimer--;				//�V�[���h���`���[�W�^�C�}�[���f�N�������g
		if (playerShield.rechargeTimer <= 0) {		//�V�[���h���`���[�W�^�C�}�[��0�ȉ��Ȃ�
			playerShield.state = recharge;			//�V�[���h�̏�Ԃ����`���[�W���ɂ���
		}
	}
	else if (playerShield.state == recharge) {			//�V�[���h�̏�Ԃ����`���[�W���Ȃ�
		playerShield.level++;							//�V�[���h�c�ʂ��C���N�������g
		if (playerShield.max <= playerShield.level) {	//�V�[���h�c�ʂ��ő�l�ȏ�ɂȂ�����
			playerShield.level = playerShield.max;		//�V�[���h�c�ʂ��ő�l�ɍ��킹��
			playerShield.state = nomal;					//�V�[���h�̏�Ԃ�ʏ펞�ɂ���
		}
	}
	else if (playerShield.state == crack) {			//�V�[���h�̏�Ԃ����ꂽ���Ȃ�
		playerShield.rechargeTimer--;				//�V�[���h���`���[�W�^�C�}�[���f�N�������g
		if (playerShield.rechargeTimer <= 0) {		//�V�[���h���`���[�W�^�C�}�[��0�ȉ��Ȃ�
			playerShield.state = recharge;			//�V�[���h�̏�Ԃ����`���[�W���ɂ���
		}
		playerShield.isShieldOn = false;			//�V�[���h�W�J�̃t���O��false�ɂ���
	}
}