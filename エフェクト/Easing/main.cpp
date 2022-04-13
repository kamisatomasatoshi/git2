#include "DxLib.h"
#include "math.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "�w�Дԍ� ���O:�^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH = 600;

// �E�B���h�E�c��
const int WIN_HEIGHT = 400;	

float Easing(float x);
float Easinf2(float x);
float conv(float x, float y, float z);


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0xFF);			

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	float size = 25.0f;
	float posY = 50.0f;
	float posX = 50.0f;
	float posY2 = posY+size;
	float posX2 = posX+size;
	float speed = 5.0f;

	float posY3 = 100.0f;
	float posX3 = 50.0f;
	float posY4 = posY3 + size;
	float posX4 = posX3 + size;

	//out
	int flame = 0;
	int maxFlame = 300;
	int isStart = 0;
	//in
	int flame2 = 300;
	//int minFlame = 0;
	float x=0.0f;
	float x2 = 0.0f;

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		posY2 = posY + size;
		posX2 = posX + size;
		posY4 = posY3 + size;
		posX4 = posX3 + size;
		if (keys[KEY_INPUT_V] == 1)
		{
			isStart = 1;
		}

		if (isStart == 1)
		{
			flame++;
			flame2--;
			//posX += speed * Easing( conv(flame, maxFlame, x));//out
			posX3 += speed * Easing(conv(flame2, maxFlame, x2));//in

			if (flame2 == 0)
			{
				flame = 300;
			}
			if (flame == maxFlame)
			{
				flame = 0;
				isStart = 0;
			}


		}
		/*if (posX3 >= 400)
		{
			posX3 = 400;
		}*/


		// �`�揈��
		DrawBox(posX, posY, posX2, posY2, GetColor(0, 0, 0), TRUE);
		DrawBox(posX3, posY3, posX4, posY4, GetColor(0, 0, 0), TRUE);
		DrawFormatString(0, 0, GetColor(0, 0, 0), "%d", isStart);
		DrawFormatString(0, 0, GetColor(0, 0, 0), "%d", flame);
		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();	

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}

float Easing(float x)
{
	return x*x*x*x*x;
}

//float Easinf2(float x)
//{
//	return 1 - pow(1 - x, 5);
//}

float conv(float x, float y,float z)
{
	return z = x / y;//x = (flame / maxFlame); 
}