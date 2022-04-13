#include "DxLib.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "K021G1271 ���O:�㗢�܂��Ƃ�";

// �E�B���h�E����
const int WIN_WIDTH = 600;

// �E�B���h�E�c��
const int WIN_HEIGHT = 400;

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
	int circleBorrowed = 0;
	circleBorrowed = LoadGraph("�@��/Circle.png");
	int circleShowBox = 0;
	circleShowBox = LoadGraph("�@��/CircleW.png");

	int hitCircleBorrowed = 0;
	hitCircleBorrowed = LoadGraph("�@��/CircleHit.png");
	int hitCircleShowBoxBorrowed = 0;
	hitCircleShowBoxBorrowed = LoadGraph("�@��/CircleWHit.png");

	int screen1 = 0;
	screen1 = LoadGraph("�w�i�摜/haikei1.png");
	int screen2 = 0;
	screen2 = LoadGraph("�w�i�摜/haikei2.png");
	int screen3 = 0;
	screen3 = LoadGraph("�w�i�摜/haikei3.png");


	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	float scroll_x = 0;
	int boxX2 = 900;
	int boxY2 = 300;
	int boxX = 300;
	int boxY = 200;
	int size = 32;
	float playerPosX = 200;
	float playerPosY = 200;
	float playerPosX2 = playerPosX + 32;
	float playerPosY2 = playerPosY + 32;
	float moveSpeed = 5;
	float move = 0;
	int isHit = 0;

	int isShowBox = 0;
	int circleResult = circleBorrowed;
	int hitCircleResult = hitCircleBorrowed;


	int screen1_posx = 0;
	int screen2_posx = 600;
	int screen_speed = 5;

	float world_x = 200;
	float local_x = 0;
	int scroll_line_x = 300;
	int scroll_line_y = 400;

	int screen = 0;

	int getMousuX = 0;
	int getMousuY = 0;
	int MouseInput = 0;
	
	int isGetMouse = 0;


	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char prev[256] = { 0 };

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++)//�L�[�̏��ۑ�
		{
			prev[i] = keys[i];
		}
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
			playerPosX2 -= moveSpeed * move;
			world_x -= moveSpeed;
		}

		if (CheckHitKey(KEY_INPUT_D) && playerPosX <= 600)
		{
			playerPosX += moveSpeed * move;
			playerPosX2 += moveSpeed * move;
			world_x += moveSpeed;
		}

		if (CheckHitKey(KEY_INPUT_W) && playerPosY >= 0 + size)
		{
			playerPosY -= moveSpeed * move;
			playerPosY2 -= moveSpeed * move;
		}

		if (CheckHitKey(KEY_INPUT_S) && playerPosY <= WIN_HEIGHT)
		{
			playerPosY += moveSpeed * move;
			playerPosY2 += moveSpeed * move;
		}


		//�g��k���A���o�[�W����
		if (CheckHitKey(KEY_INPUT_E))
		{
			playerPosX -= 1;
			playerPosX2 += 1;
		}
		if (CheckHitKey(KEY_INPUT_Q))
		{
			playerPosX += 1;
			playerPosX2 -= 1;
		}

		//�g��k���A�c�o�[�W�����B
		if (CheckHitKey(KEY_INPUT_C))
		{
			playerPosY -= 1;
			playerPosY2 += 1;
		}
		if (CheckHitKey(KEY_INPUT_Z))
		{
			playerPosY += 1;
			playerPosY2 -= 1;
		}


		//�}�E�X����
		GetMousePoint(&getMousuX, &getMousuY);
		MouseInput = GetMouseInput();
		if ((GetMouseInput() & MOUSE_INPUT_LEFT))
		{
			playerPosX = getMousuX;
			playerPosY = getMousuY;
			playerPosX2 = playerPosX + 32;
			playerPosY2 = playerPosY + 32;
		}
		
		

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����


		//�����蔻��
		if (playerPosX <= boxX + size && boxX <= playerPosX2)
		{
			if (playerPosY <= boxY + size && boxY <= playerPosY2)
			{
				isHit = 1;
			}
			else
			{
				isHit = 0;
			}
		}
		else
		{
			isHit = 0;
		}
		
		
			//�����蔻��̕`��̉摜�ݒ�B
		if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0)
		{
			if (isShowBox == 0)
			{
				isShowBox = 1;
				circleResult = circleShowBox;
				hitCircleResult = hitCircleShowBoxBorrowed;
			}
			else
			{
				isShowBox = 0;
				circleResult = circleBorrowed;
				hitCircleResult = hitCircleBorrowed;
			}
		}


		// �`�揈��
		//�w�i
		DrawGraph(screen - scroll_x, 0, screen1, true);
		DrawGraph(screen + 600 - scroll_x, 0, screen2, true);
		DrawGraph(screen + 1200 - scroll_x, 0, screen3, true);

		if (isHit == 0)
		{
			DrawGraph(boxX2 - size, boxY2 - size, circleResult, true);
			DrawGraph(boxX - size, boxY - size, circleResult, true);
			DrawExtendGraph(playerPosX - size, playerPosY - size, playerPosX2 - size, playerPosY2 - size, circleResult, TRUE);
		}
		else
		{
			DrawGraph(boxX2 - size, boxY2 - size, hitCircleResult, true);
			DrawGraph(boxX - size, boxY - size, hitCircleResult, true);
			DrawExtendGraph(playerPosX - size, playerPosY - size, playerPosX2 - size, playerPosY2 - size, hitCircleResult, TRUE);
		}

		DrawFormatString(0, 40, GetColor(150, 150, 0), "�����蔻��[%d]", isHit);
		DrawFormatString(0, 60, GetColor(150, 150, 0), "����[%lf]", moveSpeed);
		DrawFormatString(0, 80, GetColor(150, 150, 0), "�Œ�X[%d]", boxX);
		DrawFormatString(0, 100, GetColor(150, 150, 0), "player_x[%lf]", playerPosX);
		DrawFormatString(0, 120, GetColor(150, 150, 0), "�X�N���[���Px[%d]", screen1_posx);
		DrawFormatString(0, 140, GetColor(150, 150, 0), "�X�N���[���Qx[%d]", screen2_posx);
		DrawFormatString(400, 10, GetColor(0, 0, 0), "world_x : [%lf]", world_x);
		DrawFormatString(400, 30, GetColor(0, 0, 0), "scroll_x : [%lf]", scroll_x);
		DrawFormatString(400, 50, GetColor(0, 0, 0), "BOX�o���� : [%d]", isShowBox);

		//DrawLine(scroll_line_x, 0, scroll_line_x, scroll_line_y, GetColor(0, 0, 0));

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
	DeleteGraph(circleBorrowed);
	DeleteGraph(circleShowBox);
	DeleteGraph(hitCircleBorrowed);
	DeleteGraph(hitCircleShowBoxBorrowed);
	DeleteGraph(screen1);
	DeleteGraph(screen2);
	DeleteGraph(screen3);
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}