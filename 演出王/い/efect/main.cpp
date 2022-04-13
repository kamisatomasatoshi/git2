#include "DxLib.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LC1B_10_�J�~�T�g_�}�T�g�V";

// �E�B���h�E����
const int WIN_WIDTH = 600;

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
	SetBackgroundColor(0x00, 0x00, 0xFF);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	int centerPointPosx = WIN_WIDTH / 2;
	int centerPointPosy = WIN_HEIGHT / 2;
	int size = 10;

	double playerPosX = 450;
	double playerPosY = 100;
	double playerSize = 64;
	double move = 0.0f;//�΂ߏ����̌v�Z
	double moveSpeed = 3.0f;

	double efectPosX[5] = { 0 };
	double efectPosY[5] = { 0 };
	int efectSpace = 32;//�����Е��ɏo���Ƃ��̊Ԋ�
	float efectSize[5] = { 0 };
	float efectSpeed = 0.5f;
	int efectHp[5] = { 0 };//����Ӗ��t���O�B
	int landingTime = 20;
	int left = 0;
	int right = 0;


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
		if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_D))
		{
			if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_S))
			{
				move = 0.7f;//�ړ��W����0.71�ɐݒ�
			}
			else
			{
				move = 1.0f;//�΂߂���Ȃ����1.0�ɐݒ�
			}
		}

		else if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_S))
		{
			move = 1.0f;
		}

		if (CheckHitKey(KEY_INPUT_A) && playerPosX >= 0 + size)
		{
			playerPosX -= moveSpeed * move;

		}

		if (CheckHitKey(KEY_INPUT_D) && playerPosX <= 600)
		{
			playerPosX += moveSpeed * move;

		}

		if (CheckHitKey(KEY_INPUT_W) && playerPosY >= 0 + size)
		{
			playerPosY -= moveSpeed * move;

		}

		if (CheckHitKey(KEY_INPUT_S) && playerPosY <= WIN_HEIGHT)
		{
			playerPosY += moveSpeed * move;

		}

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����

		//�����̃G�t�F�N�g�X�V�����BBOXS
		for (int i = 0; i < 5; i++)
		{
			if (efectHp[i] <= 0 && keys[KEY_INPUT_SPACE])
			{
				efectHp[i] = GetRand(60);
				efectPosX[i] = playerPosX + GetRand(20) - 10;
				efectSize[i] = GetRand(8);
				efectPosY[i] = playerPosY + playerSize;

				break;
			}
			else if (efectSize[i] <= 0)
			{
				efectHp[i] = 0;
			}
			else
			{
				efectPosY[i] -= efectSpeed;
				efectHp[i]--;
				efectSize[i] -= 0.1;
			}
			if (keys[KEY_INPUT_A])
			{
				left = 1;
			}
			if (keys[KEY_INPUT_D])
			{
				right = 1;
			}
		}
		for (int i = 0; i < 5; i++)
		{
			if (right)
			{
				efectPosX[i] += GetRand(5);
				right = 0;
			}

			if (left)
			{
				efectPosX[i] -= GetRand(5);
				left = 0;
			}
		}
		//for (int i = 0; i < 5; i++)
		//{
		//	if (efectSize[i] >= 1 && efectHp[i] >= 1)
		//	{
		//		//efectSize[i] -= 0.1;
		//	}
		//}
		//for (int i = 0; i < 5; i++)
		//{
		//	if (efectHp[i] >= 1)
		//	{
		//		
		//		
		//	}

		//}


		//if (keys[KEY_INPUT_SPACE])// && efectHp <= 0)
		//{
		//	efectHp1 = GetRand(60);
		//	efectPosX1= playerPosX + GetRand(20) - 10;
		//	efectSize1 = GetRand(12);
		//	efectPosY1 = playerPosY+playerSize;
		//}
		//else
		//{
		//	efectHp1--;
		//}

		//if (efectHp1 >= 1)
		//{
		//	efectPosY1 += efectSpeed1;
		//}


		// �`�揈��
		DrawFormatString(0, 0, GetColor(0, 0, 0), "%d", efectSpeed);
		DrawBox(playerPosX, playerPosY, playerPosX + playerSize, playerPosY + playerSize, GetColor(255, 0, 0), TRUE);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "�G�t�F�N�g:SPACE");
		DrawFormatString(0, 30, GetColor(255, 255, 255), "�ړ����@:W A S D");
		//�����̃G�t�F�N�g BOXS
		/*for (int i = 0; i < 30; i++)
		{
			if (efectHp[i] >= 1)
			{
				SetDrawBlendMode(DX_BLENDMODE_ADD, 123);
				DrawBox(efectPosX[i], efectPosY[i] + playerSize, efectPosX[i] + efectSize[i], efectPosY[i] + efectSize[i] + playerSize, GetColor(6, 200, 255), TRUE);
				DrawBox(efectPosX[i] + playerSize - 10, efectPosY[i] + playerSize, efectPosX[i] + efectSize[i] + playerSize - 10, efectPosY[i] + efectSize[i] + playerSize, GetColor(60, 200, 255), TRUE);
			}
		}*/
		//���n�̉�
		for (int i = 0; i < 5; i++)
		{
			if (efectHp[i] >= 1)
			{
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawCircle(efectPosX[i], efectPosY[i], efectSize[i], GetColor(163, 163, 163), TRUE);
				DrawCircle(efectPosX[i] + playerSize, efectPosY[i], efectSize[i], GetColor(163, 163, 163), TRUE);
			}
		}
		//DrawCircle(centerPointPosx, centerPointPosy, size, GetColor(255, 255, 255),TRUE);
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