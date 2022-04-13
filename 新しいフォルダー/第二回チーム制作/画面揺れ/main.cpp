#include "DxLib.h"
#include <stdio.h>



// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "�w�Дԍ� ���O:�^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH = 1280;

// �E�B���h�E�c��
const int WIN_HEIGHT = 720;	

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
	SetBackgroundColor(0x0, 0x0, 0x0);			

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int moveKeys  = LoadGraph("resource/keys.png");
	
	int moveKeysA = LoadGraph("resource/A_keys.png");
	
	int moveKeysD = LoadGraph("resource/D_keys.png");

	int mousenone = LoadGraph("resource/mouse.png");
	int mouseRight = LoadGraph("resource/mouse_right.png");
	int mouseLeft = LoadGraph("resource/mouse_left.png");
	int notUse= LoadGraph("resource/not.png");
	int boomerang = LoadGraph("resource/boomerang.png");
	int shield= LoadGraph("resource/shield.png");
	int spece = LoadGraph("resource/space.png");
	int speceUse = LoadGraph("resource/space_use.png");
	int title = LoadGraph("resource/title.png");
	int gameClear = LoadGraph("resource/gameclear.png");
	int gameOver = LoadGraph("resource/gameover.png");
	int explanation = LoadGraph("resource/explanation.png");

	int mouse = GetMouseInput();
	// �Q�[�����[�v�Ŏg���ϐ��̐錾


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
		//�}�E�X�̎擾
		mouse = GetMouseInput();

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����


		// �`�揈��
		if (0)//�V�[�����^�C�g����������
		{
			DrawGraph(0, 0, title, TRUE);
		}
		
		if (0)//���������̉�ʂȂ�
		{
			DrawGraph(0, 0, explanation, TRUE);
		}
		

		if (0)//�V�[�����퓬�̎�
		{
			//�ړ��L�[�̕`��
			DrawGraph(200, 660, moveKeys, TRUE);
			if (keys[KEY_INPUT_A])
			{
				DrawGraph(200, 660, moveKeysA, TRUE);
			}

			if (keys[KEY_INPUT_D])
			{
				DrawGraph(200, 660, moveKeysD, TRUE);
			}
			DrawGraph(300, 660, spece, TRUE);
			if (keys[KEY_INPUT_SPACE])
			{
				DrawGraph(300, 660, speceUse, TRUE);
			}

			//�}�E�X�̕`��
			DrawGraph(1080, 650, mousenone, TRUE);
			if (mouse & MOUSE_INPUT_LEFT)
			{
				//�u�[�������U��
				DrawGraph(1080, 650, mouseLeft, TRUE);
			}
			if (mouse & MOUSE_INPUT_RIGHT)
			{
				//�K�[�h
				DrawGraph(1080, 650, mouseRight, TRUE);
			}

			//�u�[�������\��
			DrawGraph(1000, 650, boomerang, TRUE);

			//�V�[���h�̕\��
			DrawGraph(1140, 650, shield, TRUE);

			if (1)//�����A�u�[�������𓊂��Ă��܂��Ă�����B
			{
				DrawGraph(1000, 650, notUse, TRUE);
				DrawGraph(1140, 650, notUse, TRUE);
			}
		}

		if (0)//�V�[�����N���A�Ȃ�
		{
			DrawGraph(0, 0, gameClear, TRUE);
		}
		if (0)//�V�[�����I�[�o�[�Ȃ�
		{
			DrawGraph(0, 0, gameOver, TRUE);
		}

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
	InitGraph();
	DxLib_End();

	// ����I��
	return 0;
}