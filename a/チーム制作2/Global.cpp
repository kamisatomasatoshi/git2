#include"DxLib.h"
#include"Global.h"

// �ŐV�̃L�[�{�[�h���p
char keys[256] = { 0 };

// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
char prev[256] = { 0 };

//�L�[�{�[�h���X�V�֐�
void KeyUpdate()
{
	// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	for (int i = 0; i < 256; ++i) {
		prev[i] = keys[i];
	}

	//�L�[�{�[�h�������
	GetHitKeyStateAll(keys);
}
