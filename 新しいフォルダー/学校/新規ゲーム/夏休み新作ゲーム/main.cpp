#include "DxLib.h"
#include <math.h>

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LC1A_10_�J�~�T�g�}�T�g�V";

// �E�B���h�E����
const int WIN_WIDTH = 1200;

// �E�B���h�E�c��
const int WIN_HEIGHT = 800;	

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
	InitGraph();
	int stage1 = 0;
	stage1 = LoadGraph("stage_pixsel/stage1.png");
	int stage2 = 0;
	stage2 = LoadGraph("stage_pixsel/stage2.png");
	int stage3 = 0;
	stage3 = LoadGraph("stage_pixsel/stage3.png");
	int stage4 = 0;
	stage4 = LoadGraph("stage_pixsel/stage4.png");
	int stage5 = 0;
	stage5 = LoadGraph("stage_pixsel/stage5.png");
	int stage6 = 0;
	stage6 = LoadGraph("stage_pixsel/stage6.png");
	int stage7 = 0;
	stage7 = LoadGraph("stage_pixsel/stage7.png");
	int stage8 = 0;
	stage8 = LoadGraph("stage_pixsel/stage8.png");
	int stage9 = 0;
	stage9 = LoadGraph("stage_pixsel/stage9.png");


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	//�v���C���[���
	float player_posx = 200;
	float player_posy = 200;
	float moveSpeed = 5;
	float move = 0;
	double size = 32;
	int player_flag = 1;

	int shot_time = 0;
	int shot_number = 200;
	int shot_flag[256] = { 0 };
	double shot_bullte_posx[256] = { 0 };
	double shot_bullte_posy[256] = { 0 };
	double shot_size = 10;
	double shot_speed_x[256] = { 0 };
	double shot_speed_y[256] = { 0 };

	double ene_x = 600;
	double ene_y = 400;
	double ene_size = 32;
	int enemy_flag = 0;
	int radius = 0;
	int difference_posx = 0;
	int difference_posy = 0;
	int mato_x = 0;
	int mato_y = 0;

	int gv = 0;
	int junp = 10;

	int x = 100;
	int y = 300;
	int x2 = 300;
	int y2 = 310;


	int b_flag = 0;
	int b_time = 0;

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

		if (CheckHitKey(KEY_INPUT_A) && player_posx >= 0 + size)
		{
			player_posx -= moveSpeed * move;
		}


		if (CheckHitKey(KEY_INPUT_D) && player_posx <= 1200)
		{
			player_posx += moveSpeed * move;
		}


		if (CheckHitKey(KEY_INPUT_W) && player_posy >= 0 + size)
		{
			player_posy -= moveSpeed * move;
		}

		if (CheckHitKey(KEY_INPUT_S) && player_posy <= WIN_HEIGHT-size)
		{
			player_posy += moveSpeed * move;
		}
		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		

		if (player_posy <= y && player_posy <= y2 && b_flag != 1 && player_posx >= x || player_posx <= x2)
		{
			gv = 5;
			player_posy += gv;
			if (player_posy >= WIN_HEIGHT - size)
			{
				gv = 0;
			}
		}
		else if(keys[KEY_INPUT_B] == 1)
		{
			gv = 0;
			b_flag = 1;
		}

		if (b_flag == 1)
		{
			b_time++;
			player_posy -= junp;
		}

		if (b_time >= 30)
		{
			b_time = 0;
			b_flag = 0;
		}
		DrawFormatString(20, 30, GetColor(0, 0, 0),"%d", b_flag);
		DrawFormatString(20, 60, GetColor(0, 0, 0), "%d", gv);
		
		//�v���C���[���ʂ��o��
		if (keys[KEY_INPUT_SPACE] == 1 && player_flag == 1)//&& prev[KEY_INPUT_SPACE] == 0)//����ǉ��Œ���������Ȃ�
		{
			shot_time -= 1;

			for (int i = 0; i < shot_number; i++)
			{
				if (shot_flag[i] == 0 && shot_time == 0)
				{
					shot_flag[i] = 1;
					//PlaySoundMem(shot_music, DX_PLAYTYPE_BACK, true);
					shot_bullte_posx[i] = player_posx;
					shot_bullte_posy[i] = player_posy;
					{
						double sb, sbx, sby, bx, by, sx, sy;

						sx = player_posx + size / 2;
						sy = player_posy + size / 2;

						bx = ene_x + ene_size / 2;
						by = ene_y + ene_size / 2;

						sbx = bx - sx;
						sby = by - sy;

						// �����������߂�̂ɕW���֐��� sqrt ���g���A
						// ������g���ɂ� math.h ���C���N���[�h����K�v������
						sb = sqrt(sbx * sbx + sby * sby);

						// �P�t���[��������W�h�b�g�ړ�����悤�ɂ���
						shot_speed_x[i] = sbx / sb * 8;
						shot_speed_y[i] = sby / sb * 8;
					}
					
				}
			}
		}
		//�������ň��Ԋu�Ŕ��˂ł���悤�ɂ���ݒ�B
		if (shot_time <= 0 && player_flag == 1)
		{
			shot_time = 10;
		}
		if (keys[KEY_INPUT_SPACE] == 0)
		{
			shot_time = 1;
		}

		

		for (int i = 0; i < shot_number; i++)//�e�̑����̐ݒ�B
		{
			if (shot_flag[i] == 1)
			{
					// �e���ړ�������
					shot_bullte_posx[i] += shot_speed_x[i];
					shot_bullte_posy[i] += shot_speed_y[i];
			}
		}

		//�����蔻��
		for (int i = 0; i < shot_number; i++)
		{
			radius = (ene_size + shot_size) * (ene_size + shot_size);//���a
			difference_posx = (shot_bullte_posx[i] - ene_x) * (shot_bullte_posx[i] - ene_x);//X���W�̍�
			difference_posy = (shot_bullte_posy[i] - ene_y) * (shot_bullte_posy[i] - ene_y);//Y���W�̍�

			if (enemy_flag == 1)
			{
				if (shot_flag[i] == 1)
				{
					if (radius >= difference_posx + difference_posy)
					{
						shot_flag[i] = 0;
						enemy_flag = 0;
					}
				}
			}
			//�e����ʊO�ɏo����FLAG���O�ɂȂ�B
			/*if (shot_bullte_posy[i] < 0 || shot_bullte_posy[i]>400)
			{
				shot_flag[i] = 0;
			}*/
		}

		/*mato_x = ene_x - player_posx;
		mato_y = ene_y - player_posy;*/


		

















		// �`�揈��
		//DrawGraph(0, 0, stage2, true);
		DrawCircle(player_posx, player_posy, size, GetColor(150, 150, 0));
		DrawCircle(ene_x, ene_y, ene_size, GetColor(0, 150, 0));
		DrawBox(x, y, x2, y2,GetColor(0, 0, 0),TRUE);
		for (int i = 0; i < shot_number; i++)
		{
			if (shot_flag[i] == 1)
			{
				//DrawCircle(shot_bullte_posx[i], shot_bullte_posy[i], shot_size, GetColor(150, 250, 45), TRUE);//�e�̕\��
				//DrawGraph(shot_bullte_posx[i] - shot_size - 5, shot_bullte_posy[i] - shot_size, shot[s], true);
				DrawCircle(shot_bullte_posx[i], shot_bullte_posy[i], shot_size, GetColor(150, 100, 150));
			}
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
	//InitGraph();
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}