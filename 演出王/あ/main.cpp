#include "DxLib.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "�w�Дԍ� ���O:�^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH = 600;

// �E�B���h�E�c��
const int WIN_HEIGHT = 400;	
double conv(double x, double y, double z);
double EaseingTitle(double x);

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
	const int MAXFLAME = 300;
	int flame = 0;
	int x = 0;
	int isEaseing = 0;
	int posX = WIN_WIDTH / 2;
	int posY = WIN_HEIGHT / 2;
	int speed = 42;
	int isBoxDown = 0;
	int boxPosY = 0;

	int fontSize = 50;

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
		if (keys[KEY_INPUT_SPACE])
		{
			isEaseing = 1;
		}

		if (isEaseing == 1)
		{
			flame++;
			posY+=speed* EaseingTitle(conv(flame, MAXFLAME, x));
			boxPosY+=speed* EaseingTitle(conv(flame, MAXFLAME, x));
			if (posY <= -32)
			{
				fontSize = 100;
				isBoxDown = 1;
			}
			if (flame == MAXFLAME)
			{
				flame = 0;
				isEaseing = 0;
			}
		}

		if (keys[KEY_INPUT_R])
		{
			flame = 0;
			x = 0;
			isEaseing = 0;
			posX = WIN_WIDTH / 2;
			posY = WIN_HEIGHT / 2;
			speed = 42;
			fontSize = 50;
			boxPosY = 0;
		}

		// �`�揈��
		DrawBox(0, 0, WIN_WIDTH, boxPosY, GetColor(0, 0, 0), TRUE);
		SetFontSize(fontSize);
		DrawFormatString(posX-50, posY-50, GetColor(0, 0, 0), "TITLE");
		SetFontSize(20);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "�X�^�[�g:SPACE");
		DrawFormatString(0, 30, GetColor(255, 255, 255), "���Z�b�g:R");
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

double conv(double x, double y, double z)
{
	return z = x / y;//x = (flame / maxFlame); 
}

double EaseingTitle(double x)
{
	const double c1 = 1.70158;
	const double c3 = c1 +1;

	return c3 * x * x * x - c1 * x * x;
}