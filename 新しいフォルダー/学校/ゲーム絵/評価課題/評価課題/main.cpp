#include "DxLib.h"
#include <time.h>
#include <stdlib.h>

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "�w�Дԍ� ���O:LC1A_10_�J�~�T�g�}�T�g�V";

// �E�B���h�E����
int WIN_WIDTH = 600;

// �E�B���h�E�c��
int WIN_HEIGHT = 900;

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
	//																�A�j���[�V�����ꖇ�̃T�C�Y
	//LoadDivGraph("player.png", ����������, ���̕�����, �c�̕�����, ���̃T�C�Y, �c�T�C�Y, �����ϐ�);
	// ��ʏ��
	int start[2];
	LoadDivGraph("STARTfont-export.png", 2, 2, 1, 750, 500, start);
	int restsrt[2];
	LoadDivGraph("restart.png", 2, 2, 1, 400, 128, restsrt);
	int backgame[2];
	LoadDivGraph("backgame.png", 2, 2, 1, 400, 128, backgame);
	int game_over[16];
	LoadDivGraph("game_over.png", 16, 16, 1, 400, 80, game_over);
	int game_claer[18];
	LoadDivGraph("game_claer.png", 18, 18, 1, 400, 80, game_claer);
	int title[28];
	LoadDivGraph("title.png", 28, 28, 1, 480, 96, title);

	int huti;
	huti = LoadGraph("huti.png");
	int move;
	move = LoadGraph("move.png");

	//�v���C���[�̉摜
	int player[4];
	LoadDivGraph("player.png", 4, 4, 1, 32, 32, player);//�~�܂��Ă���Ƃ�
	int playermove[8];
	LoadDivGraph("playerRun1.png", 8, 8, 1, 256, 32, playermove);//�����Ă���Ƃ�
	int shot[3];
	LoadDivGraph("shot.png", 3, 3, 1, 16, 16, shot);//�e

	//�G�̉摜
	int enemy[2];
	LoadDivGraph("enemy1.png", 2, 2, 1, 32, 32, enemy);
	int enemy_ko[2];
	LoadDivGraph("enemy2.png", 2, 2, 1, 32, 32, enemy_ko);



	//�w�i
	int backscreen = LoadGraph("backscreen.png", true);
	int backscreen1 = LoadGraph("backscreen.png", true);

	int screen_posy = 0;
	int screen_posy1 = 0;

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	//��ʏ��
	int score = 0;				//�X�R�A
	int shot_upgrade = 10000;			//�e�̃A�b�v�O���[�h
	int enemy_upgrade = 3000;				//�G�̃A�b�v�O���[�h
	int scene = 0;				//��ʐ؂�ւ��B
	int time = 0;
	int start_gif_time = 0;
	int go_time = 0;
	int sg = 0;
	int rs = 0;
	int bg = 0;
	int go = 0;
	int gc = 0;
	int ti = 0;
	int ti_time = 0;

	//�v���C���[���
	float player_posx = 300;				//�����W
	float player_posy = 800;				//�����W
	float player_speed = 8;				//�v���C���[�̑���
	int player_size = 20;				//�v���C���[�̑傫��
	int player_flag = 1;				//�v���C���[�̃t���b�O
	int player_gif_time = 0;
	int p = 0;
	int p_time = 30;
	float player_move = 0;

	//�e�̏��
	int shot_bullte_posx[256] = { 0 };	//�e��X���W
	int shot_bullte_posy[256] = { 0 };	//�e��Y���W
	int shot_flag[256] = { 0 };	//�e�̔F���ϐ��B
	int shot_speed = 6;		//�e�̑��x
	int shot_size = 3;		//�e�̒��a
	int shot_time = 1;		//�e�̊Ԋu
	int shot_number = 1;		//�e�̍ő吔
	int shot_damage = 1;		//�_���[�W
	int s = 0;

	//�G�̏��
	int enemy_posx[256] = { 0 };		//�~��X���W
	int enemy_posy[256] = { 0 };		//�~��Y���W
	int enemy_flag[256] = { 0 };		//�G�̃t���b�O���
	int enemy_respown[256] = { 0 };		//�����^�C�}�[
	int enemy_x_speed = 0;			//�~�̑����BX���W
	int enemy_y_speed = 1;			//�~�̑����BY���W
	int enemy_size = 15;			//�G�̒��a
	int enemy_number = 1;				//�G�̏���ݒ�
	int e = 0;
	int e_ko = 0;
	int enemy_gif_time = 0;
	int boom_time[256] = { 0 };
	int enemy_ko_posx[256];
	int enemy_ko_posy[256];


	//�{�X���
	int boss_main_posx = 350;				//�{�X���C���@X
	int boss_main_posy = 5;				//�{�X���C���@Y
	int boss_main_size = 50;				//�T�C�Y
	int boss_main_hp = 1;				//HP
	int boss_sub1_posx = 200;				//�{�X�T�u�PX
	int boss_sub1_posy = 10;				//�{�X�T�u�PY
	int boss_sub1_size = 20;				//�T�C�Y
	int boss_sub1_hp = 30;				//HP
	int boss_sub2_posx = 400;				//�{�X�T�u�QX
	int boss_sub2_posy = 10;				//�{�X�T�u�QY
	int boss_sub2_size = 20;				//�T�C�Y
	int boss_sub2_hp = 30;				//HP
	int boss_main_flag = 0;				//�{�X���C���t���O
	int boss_sub1_flag = 0;				//�{�X�T�u�P�t���O
	int boss_sub2_flag = 0;				//�{�X�T�u�Q�t���O]
	int boss_speed0_posx = 0;				//�{�X����
	int boss_speed1_posx = 0;				//	//
	int boss_speed2_posx = 0;				//	//
	int boss_speed0_posy = 0;				//	//
	int boss_speed1_posy = 0;				//	//
	int boss_speed2_posy = 0;				//	//
	int boss_speed0_change = 0;				//�����̕ύX�B
	int boss_speed1_change = 3;				//�����̕ω��T�u�P
	int boss_speed2_change = 3;				//�����̕ω��T�u�Q

		//�����蔻����
	const int radius = (enemy_size + shot_size) * (enemy_size + shot_size);//���a
	const int redius_main = (enemy_size + player_size) * (enemy_size + player_size);
	const int boss_main_redius = (boss_main_size + shot_size) * (boss_main_size + shot_size);
	const int boss_sub1_redius = (boss_sub1_size + shot_size) * (boss_sub1_size + shot_size);
	const int boss_sub2_redius = (boss_sub2_size + shot_size) * (boss_sub2_size + shot_size);
	const int boss_boss_player = (boss_main_size + player_size) * (boss_main_size + player_size);
	const int boss_sub1_player = (boss_sub1_size + player_size) * (boss_sub1_size + player_size);
	const int boss_sub2_player = (boss_sub2_size + player_size) * (boss_sub2_size + player_size);
	int difference_posx[256] = { 0 };			//x�̍�
	int difference_posy[256] = { 0 };			//y�̍�
	int difference_posx_main[256] = { 0 };		//x�̖{�̍�
	int difference_posy_main[256] = { 0 };		//y�̖{�̍�

	//������


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
				player_move = 0.7f;//�ړ��W����0.71�ɐݒ�
			}
			else
			{
				player_move = 1.0f;//�΂߂���Ȃ����1.0�ɐݒ�
			}
		}

		else if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_S))
		{
			move = 1.0f;
		}

		if (CheckHitKey(KEY_INPUT_A) && player_posx >= 0 + player_size)
		{
			player_posx -= player_speed * player_move;
		}


		if (CheckHitKey(KEY_INPUT_D) && player_posx <= 600)
		{
			player_posx += player_speed * player_move;
		}


		if (CheckHitKey(KEY_INPUT_W) && player_posy >= 0 + player_size)
		{
			player_posy -= player_speed * player_move;
		}

		if (CheckHitKey(KEY_INPUT_S) && player_posy <= WIN_HEIGHT)
		{
			player_posy += player_speed * player_move;
		}
		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		screen_posy++;
		screen_posy1++;

		if (screen_posy >= 890)
		{
			screen_posy = 0;
		}

		if (screen_posy1 >= 0)
		{
			screen_posy1 = -890;
		}

		DrawGraph(0, screen_posy, backscreen, true);
		DrawGraph(0, screen_posy1, backscreen1, true);


		switch (scene)
		{
			//�X�V����
			case 0:
				//�V�[���؂�ւ��悤�B�X�^�[�g���j���[
				if (keys[KEY_INPUT_Z] == 1)
				{
					scene = 1;
				}
				//������
				score = 0;				//�X�R�A
				shot_upgrade = 10000;			//�e�̃A�b�v�O���[�h
				enemy_upgrade = 3000;				//�G�̃A�b�v�O���[�h
				time = 0;				//���Ԍo��

				//�v���C���[���
				player_posx = 300;				//�����W
				player_posy = 800;				//�����W
				player_speed = 8;				//�v���C���[�̑���
				player_size = 20;				//�v���C���[�̑傫��
				player_flag = 1;				//�v���C���[�̃t���b�O
				player_gif_time = 0;

				//�e�̏��


				shot_time = 1;					//�e�̊Ԋu
				shot_number = 1;					//�ő吔�̐ݒ�
				shot_damage = 1;					//�_���[�W

				//�G�̏��

				for (int i = 0; i < 256; i++)
				{
					enemy_flag[i] = { 0 };
				}
				for (int i = 0; i < 256; i++)
				{
					enemy_respown[i] = { 100 };
				}
				for (int i = 0; i < 256; i++)
				{
					boom_time[i] = { 5 };
				}
				enemy_x_speed = 0;				//�~�̑����BX���W
				enemy_y_speed = 2;				//�~�̑����BY���W
				enemy_number = 1;				//�G�̏���ݒ�

				for (int i = 0; i < 256; i++)
				{
					enemy_ko_posx[i] = { -100 };
					enemy_ko_posy[i] = { -100 };
				}


				//�{�X���
				boss_main_posx = 350;				//�{�X���C���@X
				boss_main_posy = 5;				//�{�X���C���@Y
				boss_main_size = 50;				//�T�C�Y
				boss_main_hp = 1;				//HP
				boss_sub1_posx = 200;				//�{�X�T�u�PX
				boss_sub1_posy = 10;				//�{�X�T�u�PY
				boss_sub1_size = 20;				//�T�C�Y
				boss_sub1_hp = 30;				//HP
				boss_sub2_posx = 400;				//�{�X�T�u�QX
				boss_sub2_posy = 10;				//�{�X�T�u�QY
				boss_sub2_hp = 30;				//HP
				boss_main_flag = 0;				//�{�X���C���t���O
				boss_sub1_flag = 0;				//�{�X�T�u�P�t���O
				boss_sub2_flag = 0;				//�{�X�T�u�Q�t���O]
				boss_speed0_posx = 0;				//�{�X����
				boss_speed1_posx = 0;				//	//
				boss_speed2_posx = 0;				//	//
				boss_speed0_posy = 0;				//	//
				boss_speed1_posy = 0;				//	//
				boss_speed2_posy = 0;				//	//
				boss_speed0_change = 0;				//�����̕ύX�B
				boss_speed1_change = 3;
				boss_speed2_change = 3;

				if (scene == 0)
				{
					start_gif_time++;
					if (start_gif_time >= 30)
					{
						sg += 1;
						start_gif_time = 0;
					}
				}
				if (scene == 0)
				{
					ti_time++;
					if (ti_time >= 30)
					{
						ti++;
					}
				}





				DrawGraph(30, 50, title[ti], true);
				if (ti >= 27)
				{
					ti = 0;
				}

				//�`�揈��
				if (scene == 0)
				{
					DrawGraph(-100, 400, start[sg], true);
				}
				if (sg >= 1)
				{
					sg = 0;
				}

				DrawGraph(100, 300, move, true);
				//DrawFormatString(0, 5, GetColor(150, 150, 0), "S�L�[�ŃX�^�[�g");
				break;//secen 0

			case 1://�V�[���؂�ւ��悤�o�g����ʁB

				time++;//���Ԍo��

				if (keys[KEY_INPUT_B] == 1 && prev[KEY_INPUT_B] == 0)
				{
					scene = 4;
				}
				if (player_flag == 1)
				{
					enemy_gif_time++;
					player_gif_time++;

					if (enemy_gif_time >= 30)
					{
						e_ko++;
						e++;
						enemy_gif_time = 0;
					}
					if (player_gif_time >= 10)
					{
						p++;
						player_gif_time = 0;
					}
					s++;
				}




				//�X�R�A�A�e�̃A�b�v�O���[�h�A�G�̃A�b�v�O���[�h�B
				if (score >= shot_upgrade)
				{
					shot_number += 1;
					shot_upgrade += 10000;
				}
				if (score >= enemy_upgrade)
				{
					enemy_upgrade += 3000;
					enemy_number += 1;
				}

				//�{�X��˓�
				if (time > 5400 && boss_main_flag == 0)
				{
					boss_main_flag = 1;
					boss_sub1_flag = 1;
					boss_sub2_flag = 1;
				}

				//�e�̔���
				if (keys[KEY_INPUT_SPACE] == 1 && player_flag == 1)//&& prev[KEY_INPUT_SPACE] == 0)//����ǉ��Œ���������Ȃ�
				{
					shot_time -= 1;
					for (int i = 0; i < shot_number; i++)
					{
						if (shot_flag[i] == 0 && shot_time == 0)
						{
							shot_flag[i] = 1;
							shot_bullte_posx[i] = player_posx;
							shot_bullte_posy[i] = player_posy;
							break;
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

				//�e�̑����̐ݒ�
				for (int i = 0; i < shot_number; i++)//�e�̑����̐ݒ�B
				{
					if (shot_flag[i] == 1)
					{
						shot_bullte_posy[i] = shot_bullte_posy[i] - 5;
					}
				}

				//�G�̑���
				for (int i = 0; i < enemy_number; i++)
				{
					if (enemy_flag[i] == 1)
					{
						enemy_posy[i] += enemy_y_speed;
					}
				}

				//BOSS�̐ݒ�
				//�����蔻��
				if (boss_main_flag == 1)
				{
					//�_���[�W���₷�B�������
					if (boss_sub1_flag == 0 && boss_sub2_flag == 0)
					{
						shot_damage = 3;
					}
					for (int i = 0; i < shot_number; i++)
					{
						difference_posx[i] = (boss_main_posx - shot_bullte_posx[i]) * (boss_main_posx - shot_bullte_posx[i]);//X���W�̍�
						difference_posy[i] = (boss_main_posy - shot_bullte_posy[i]) * (boss_main_posy - shot_bullte_posy[i]);//Y���W�̍�
						if (boss_main_flag == 1 && shot_flag[i] == 1)
						{
							if (boss_main_redius >= difference_posx[i] + difference_posy[i])
							{
								boss_main_hp -= shot_damage;
								shot_flag[i] = 0;
								boss_speed0_change += 1;
								if (boss_main_hp <= 0)
								{
									boss_main_flag = 0;
									score += 15000;
									scene = 4;
									break;
								}
							}
						}
					}
					for (int i = 0; i < shot_number; i++)
					{
						difference_posx[i] = (boss_sub1_posx - shot_bullte_posx[i]) * (boss_sub1_posx - shot_bullte_posx[i]);//X���W�̍�
						difference_posy[i] = (boss_sub1_posy - shot_bullte_posy[i]) * (boss_sub1_posy - shot_bullte_posy[i]);//Y���W�̍�
						if (boss_sub1_flag == 1 && shot_flag[i] == 1)
						{
							if (boss_sub1_redius >= difference_posx[i] + difference_posy[i])
							{
								boss_sub1_hp -= shot_damage;
								shot_flag[i] = 0;
								boss_speed1_change += 1;
								if (boss_sub1_hp <= 0)
								{
									boss_sub1_flag = 0;
									score += 5000;
									break;
								}
							}
						}
					}
					for (int i = 0; i < shot_number; i++)
					{
						difference_posx[i] = (boss_sub2_posx - shot_bullte_posx[i]) * (boss_sub2_posx - shot_bullte_posx[i]);//X���W�̍�
						difference_posy[i] = (boss_sub2_posy - shot_bullte_posy[i]) * (boss_sub2_posy - shot_bullte_posy[i]);//Y���W�̍�
						if (boss_sub2_flag == 1 && shot_flag[i] == 1)
						{
							if (boss_sub2_redius >= difference_posx[i] + difference_posy[i])
							{
								boss_sub2_hp -= shot_damage;
								shot_flag[i] = 0;
								boss_speed2_change += 1;
								if (boss_sub2_hp <= 0)
								{
									boss_sub2_flag = 0;
									score += 5000;
									break;
								}
							}
						}
					}
					for (int i = 0; i < enemy_number; i++)
					{
						if (boss_main_flag == 1)
						{
							difference_posx[i] = (boss_main_posx - player_posx) * (boss_main_posx - player_posx);//X���W�̍�
							difference_posy[i] = (boss_main_posy - player_posy) * (boss_main_posy - player_posy);//Y���W�̍�
							if (boss_boss_player >= difference_posx[i] + difference_posy[i])
							{
								player_flag = 0;
							}
						}
					}
					for (int i = 0; i < enemy_number; i++)
					{
						if (boss_sub1_flag == 1)
						{
							difference_posx[i] = (boss_sub1_posx - player_posx) * (boss_sub1_posx - player_posx);//X���W�̍�
							difference_posy[i] = (boss_sub1_posy - player_posy) * (boss_sub1_posy - player_posy);//Y���W�̍�
							if (boss_sub1_player >= difference_posx[i] + difference_posy[i])
							{
								player_flag = 0;
							}
						}
					}
					for (int i = 0; i < enemy_number; i++)
					{
						if (boss_sub2_flag == 1)
						{
							difference_posx[i] = (boss_sub2_posx - player_posx) * (boss_sub2_posx - player_posx);//X���W�̍�
							difference_posy[i] = (boss_sub2_posy - player_posy) * (boss_sub2_posy - player_posy);//Y���W�̍�
							if (boss_sub2_player >= difference_posx[i] + difference_posy[i])
							{
								player_flag = 0;
							}
						}
					}
				}
				//���x�ω�������B

				if (boss_speed0_change >= 3)
				{
					boss_speed0_posx = GetRand(30 + 1);
					boss_speed0_posy = GetRand(20 + 1);
					boss_speed0_change = 0;
				}
				if (boss_speed1_change >= 3)
				{
					boss_speed1_posx = GetRand(15 + 1);
					boss_speed1_posy = GetRand(15 + 1);
					boss_speed1_change = 0;
				}
				if (boss_speed2_change >= 3)
				{
					boss_speed2_posx = GetRand(15 + 1);
					boss_speed2_posy = GetRand(15 + 1);
					boss_speed2_change = 0;
				}

				//�{�X�̈ړ�
				//X�̈ړ�����
				if (boss_main_posx >= 600 - 64 || boss_main_posx <= 0 + 64)
				{
					boss_speed0_posx = -boss_speed0_posx;
				}
				if (boss_sub1_posx >= 600 - 64 || boss_sub1_posx <= 0 + 64)
				{
					boss_speed1_posx = -boss_speed1_posx;
				}
				if (boss_sub2_posx >= 600 - 64 || boss_sub2_posx <= 0 + 64)
				{
					boss_speed2_posx = -boss_speed2_posx;
				}
				//Y�̈ړ�����
				if (boss_main_posy <= 0 - 64 || boss_main_posy >= 900 + 64)
				{
					boss_speed0_posy = -boss_speed0_posy;
				}
				if (boss_sub1_posy <= 0 - 64 || boss_sub1_posy >= 900 + 64)
				{
					boss_speed1_posy = -boss_speed1_posy;
				}
				if (boss_sub2_posy <= 0 - 64 || boss_sub2_posy >= 900 + 64)
				{
					boss_speed2_posy = -boss_speed2_posy;
				}
				//���������B
				if (boss_main_flag == 1)
				{
					boss_main_posx = boss_main_posx + boss_speed0_posx;
					boss_main_posy = boss_main_posy + boss_speed0_posy;
				}
				if (boss_sub1_flag == 1)
				{
					boss_sub1_posx = boss_sub1_posx + boss_speed1_posx;
					boss_sub1_posy = boss_sub1_posy + boss_speed1_posy;
				}
				if (boss_sub2_flag == 1)
				{
					boss_sub2_posx = boss_sub2_posx + boss_speed2_posx;
					boss_sub2_posy = boss_sub2_posy + boss_speed2_posy;
				}
				for (int i = 0; i < enemy_number; i++)
				{
					if (enemy_flag[i])
					{
						enemy_ko_posx[i] = enemy_posx[i];
						enemy_ko_posy[i] = enemy_posy[i];
					}
				}
				//�����蔻��
				//�e�ƎG���G
				for (int i = 0; i < shot_number; i++)
				{
					for (int j = 0; j < enemy_number; j++)
					{
						difference_posx[j] = (shot_bullte_posx[i] - enemy_posx[j]) * (shot_bullte_posx[i] - enemy_posx[j]);//X���W�̍�
						difference_posy[j] = (shot_bullte_posy[i] - enemy_posy[j]) * (shot_bullte_posy[i] - enemy_posy[j]);//Y���W�̍�
						if (enemy_flag[j] == 1 && shot_flag[i] == 1)
						{
							if (radius >= difference_posx[j] + difference_posy[j])
							{
								/*x[j]			= enemy_posx[j];
								y[j]			= enemy_posy[j];*/
								shot_flag[i] = 0;
								enemy_flag[j] = 0;
								enemy_posy[j] = 0;
								score += 1000;
								break;
							}
						}
					}
				}
				//�G���G�Ɩ{�̂̓����蔻��
				for (int i = 0; i < enemy_number; i++)
				{
					difference_posx[i] = (enemy_posx[i] - player_posx) * (enemy_posx[i] - player_posx);//X���W�̍�
					difference_posy[i] = (enemy_posy[i] - player_posy) * (enemy_posy[i] - player_posy);//Y���W�̍�
					if (enemy_flag[i] == 1)
					{
						if (redius_main >= difference_posx[i] + difference_posy[i])
						{
							player_flag = 0;
						}
					}
				}


				//�e����ʊO�ɏo����FLAG���O�ɂȂ�B
				for (int i = 0; i < shot_number; i++)
				{
					if (shot_bullte_posy[i] <= 0 || shot_bullte_posy[i] >= 900)
					{
						shot_flag[i] = 0;
					}
				}
				for (int i = 0; i < enemy_number; i++)
				{
					if (enemy_posy[i] >= 900)
					{
						enemy_flag[i] = 0;
					}
				}
				//�����^�C�}�[
				for (int i = 0; i < enemy_number; i++)
				{
					if (enemy_flag[i] == 0 && boss_main_flag == 0)
					{
						boom_time[i] -= 1;
						enemy_respown[i] -= 1;
						if (enemy_respown[i] <= 0)
						{
							enemy_posx[i] = GetRand(400) + 50;
							enemy_posy[i] = -30;
							enemy_flag[i] = 1;
							enemy_respown[i] = 100;
							boom_time[i] = 10;
						}
					}
				}

				//���񂾂Ƃ��̏���
				if (player_flag == 0)
				{
					scene = 3;
				}

				//�`�揈��
				//�����̕\�L
				DrawFormatString(0, 5, GetColor(150, 150, 0), "�e�̃t���b�O0[%d]", shot_flag[0]);//�e�̕\��
				DrawFormatString(0, 20, GetColor(150, 150, 0), "�e�̃t���b�O1[%d]", shot_flag[1]);//�e�̕\��
				DrawFormatString(0, 40, GetColor(150, 150, 0), "�e�̃t���b�O2[%d]", shot_flag[2]);//�e�̕\��
				DrawFormatString(0, 60, GetColor(150, 150, 0), "�e�̃t���b�O3[%d]", shot_flag[3]);//�e�̕\��
				DrawFormatString(0, 80, GetColor(150, 150, 0), "�e�̃t���b�O4[%d]", shot_flag[4]);//�e�̕\��
				DrawFormatString(0, 100, GetColor(150, 150, 0), "�G�̃t���b�O [%d]", enemy_flag[0]);  //�G�̕\��
				//DrawFormatString(0, 120, GetColor(150, 150, 0), "�G�̃t���b�O [%d]", enemy_flag[1]);  //�G�̕\��
				//DrawFormatString(0, 140, GetColor(150, 150, 0), "�G�̃t���b�O [%d]", enemy_flag[2]);  //�G�̕\��
				DrawFormatString(0, 160, GetColor(150, 150, 0), "�A�b�v�O���[�h���� [%d]", shot_upgrade);  //�e�����₷���߂̏���
				DrawFormatString(0, 180, GetColor(150, 150, 0), "���݂̃X�R�A [%d]", score);//�X�R�A
				DrawFormatString(0, 200, GetColor(150, 150, 0), "�GX[0] [%d]", enemy_posx[0]);//�X�R�A
				DrawFormatString(0, 220, GetColor(150, 150, 0), "�GY[0] [%d]", enemy_posy[0]);//�X�R�A
				DrawFormatString(0, 240, GetColor(150, 150, 0), "�GX[1] [%d]", enemy_posx[1]);//�X�R�A
				DrawFormatString(0, 260, GetColor(150, 150, 0), "�GY[1] [%d]", enemy_posy[1]);//�X�R�A
				DrawFormatString(0, 280, GetColor(150, 150, 0), "time[0] [%d]", enemy_respown[0]);//�X�R�A
				DrawFormatString(0, 300, GetColor(150, 150, 0), "time[1] [%d]", enemy_respown[1]);//�X�R�A
				DrawFormatString(0, 320, GetColor(150, 150, 0), "�G�̏o������ [%d]", enemy_number);
				DrawFormatString(0, 340, GetColor(150, 150, 0), "�G�̏o������ [%d]", enemy_upgrade);
				DrawFormatString(0, 360, GetColor(150, 150, 0), "ESC�L�[�Ń|�[�Y");
				DrawFormatString(0, 400, GetColor(150, 150, 0), "%d", boss_main_flag);
				DrawFormatString(0, 420, GetColor(150, 150, 0), "%d", boss_sub1_flag);
				DrawFormatString(0, 440, GetColor(150, 150, 0), "%d", boss_sub2_flag);
				DrawFormatString(0, 460, GetColor(150, 150, 0), "%d", boss_main_hp);
				DrawFormatString(0, 500, GetColor(150, 150, 0), "%d", time);
				DrawFormatString(0, 520, GetColor(150, 150, 0), "%d", boss_speed0_change);
				DrawFormatString(0, 550, GetColor(150, 150, 0), "%d", boss_speed0_posx);
				DrawFormatString(50, 570, GetColor(150, 150, 0), "%d", player_flag);

				if (player_flag == 1)
				{
					//DrawCircle(player_posx, player_posy, player_size, GetColor(255, 255, 255), TRUE);//�v���C���[�\��
					DrawGraph(player_posx - player_size, player_posy - player_size, player[p], true);
					if (p >= 3)
					{
						p = 0;
					}
				}

				//�e�̕\��
				for (int i = 0; i < shot_number; i++)
				{
					if (shot_flag[i] == 1)
					{
						//DrawCircle(shot_bullte_posx[i], shot_bullte_posy[i], shot_size, GetColor(150, 250, 45), TRUE);//�e�̕\��
						DrawGraph(shot_bullte_posx[i] - shot_size - 5, shot_bullte_posy[i] - shot_size, shot[s], true);
						if (s >= 2)
						{
							s = 0;
						}
					}

				}

				//�G�̕\��
				for (int i = 0; i < enemy_number; i++)
				{
					if (enemy_flag[i] == 1)
					{
						//DrawCircle(enemy_posx[i], enemy_posy[i], enemy_size, GetColor(150, 250, 45), TRUE);//�G�̕\��	
						DrawGraph(enemy_posx[i] - enemy_size, enemy_posy[i] - enemy_size, enemy[e], TRUE);
						if (e >= 1)
						{
							e = 0;
						}
					}
				}
				for (int i = 0; i < enemy_number; i++)
				{
					if (enemy_flag[i] == 0 && boom_time[i] >= 1)
					{
						DrawGraph(enemy_ko_posx[i] - enemy_size, enemy_ko_posy[i] - enemy_size, enemy_ko[e_ko], TRUE);
						if (e_ko >= 1)
						{
							e_ko = 0;
						}
					}
				}

				//BOSS��̕`��
				if (boss_main_flag == 1 && boss_main_hp >= 0)
				{
					DrawCircle(boss_main_posx, boss_main_posy, boss_main_size, GetColor(150, 250, 45), TRUE);
				}
				if (boss_sub1_flag == 1 && boss_sub1_hp >= 0)
				{
					DrawCircle(boss_sub1_posx, boss_sub1_posy, boss_sub1_size, GetColor(150, 250, 45), TRUE);
				}
				if (boss_sub2_flag == 1 && boss_sub2_hp >= 0)
				{
					DrawCircle(boss_sub2_posx, boss_sub2_posy, boss_sub2_size, GetColor(150, 250, 45), TRUE);
				}


				break;

			case 2://�|�[�Y��ʁB�V�[���؂�ւ��悤�B
				if (keys[KEY_INPUT_B] == 1)
				{
					scene = 1;
				}
				if (keys[KEY_INPUT_R] == 1)
				{
					scene = 0;
				}

				if (scene == 2)
				{
					start_gif_time++;
					if (start_gif_time >= 30)
					{
						rs += 1;
						bg += 1;
						start_gif_time = 0;
					}
				}

				//�`�揈��
				if (scene == 2 && player_flag == 0)
				{
					DrawGraph(100, 100, restsrt[rs], true);
					if (rs >= 1)
					{
						rs = 0;
					}
					DrawGraph(100, 400, backgame[bg], true);
					if (bg >= 1)
					{
						bg = 0;
					}
				}

				break;

			case 3://�s�k���
				DrawFormatString(0, 360, GetColor(150, 150, 0), "GAME�@OVER");
				if (keys[KEY_INPUT_R] == 1)
				{
					scene = 0;
				}

				if (scene == 3)
				{
					start_gif_time++;
					if (start_gif_time >= 30)
					{
						rs += 1;
						start_gif_time = 0;
					}
				}

				if (scene == 3)
				{
					go_time++;
					if (go_time >= 10)
					{
						go += 1;
						go_time = 0;
					}
				}

				//�`�揈��
				if (scene == 3 && player_flag == 0)
				{
					DrawGraph(100, 400, game_over[go], true);
					if (go >= 16)
					{
						go = 0;
					}
					DrawGraph(100, 100, restsrt[rs], true);
					if (rs >= 1)
					{
						rs = 0;
					}
				}

				break;

			case 4://clear���
				//DrawFormatString(0, 360, GetColor(150, 150, 0), "GAME�@clear");
				if (keys[KEY_INPUT_R] == 1)
				{
					scene = 0;
				}

				if (scene == 4)
				{
					start_gif_time++;
					if (start_gif_time >= 30)
					{
						rs += 1;
						start_gif_time = 0;
					}
				}
				if (scene == 4)
				{
					go_time++;
					if (go_time >= 10)
					{
						gc += 1;
						go_time = 0;
					}
				}

				//�`�揈��
				if (scene == 4)
				{
					DrawGraph(100, 400, game_claer[gc], true);
					if (gc >= 17)
					{
						gc = 0;
					}
					DrawGraph(100, 100, restsrt[rs], true);
					if (rs >= 1)
					{
						rs = 0;
					}
				}
				break;




		}
		DrawGraph(0, 0, huti, true);

		DrawFormatString(0, 450, GetColor(150, 150, 0), "���secen[%d]", scene);
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
		if (CheckHitKey(KEY_INPUT_F5) == 1)
		{
			break;
		}
	}
	DeleteGraph(huti);
	DeleteGraph(backscreen);
	DeleteGraph(backscreen1);
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(enemy_ko[i]);
		DeleteGraph(enemy[i]);
		DeleteGraph(backgame[i]);
		DeleteGraph(restsrt[i]);
		DeleteGraph(start[i]);
	}
	for (int i = 0; i < 18; i++)
	{
		DeleteGraph(game_claer[i]);
	}
	for (int i = 0; i < 16; i++)
	{
		DeleteGraph(game_over[i]);
	}

	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}