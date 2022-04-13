#include "DxLib.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "�w�Дԍ� ���O:LC1A_10_�J�~�T�g�}�T�g�V";

// �E�B���h�E����
const int WIN_WIDTH = 600;

// �E�B���h�E�c��
const int WIN_HEIGHT = 900;

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
	// 
	// ���y����ʉ�
	int shot_music;
	shot_music = LoadSoundMem("music/shot.mp3");
	int ok;
	ok = LoadSoundMem("music/ok.mp3");
	int ripea;
	ripea = LoadSoundMem("music/ripea.mp3");
	int bossdawn;
	bossdawn = LoadSoundMem("music/bossdawn.mp3");



	int titlebgm;
	titlebgm = LoadSoundMem("music/titlebgm.mp3");
	int main_bgm;
	main_bgm = LoadSoundMem("music/mainbgm.mp3");
	int gameover;
	gameover = LoadSoundMem("music/gameover.mp3");
	int clear;
	clear = LoadSoundMem("music/clear.mp3");




	//																�A�j���[�V�����ꖇ�̃T�C�Y
	//LoadDivGraph("player.png", ����������, ���̕�����, �c�̕�����, ���̃T�C�Y, �c�T�C�Y, �����ϐ�);
	// ��ʏ��
	int start[2];
	LoadDivGraph("picture/STARTfont-export.png", 2, 2, 1, 750, 500, start);
	int restsrt[2];
	LoadDivGraph("picture/restart.png", 2, 2, 1, 400, 128, restsrt);
	int backgame[2];
	LoadDivGraph("picture/backgame.png", 2, 2, 1, 400, 128, backgame);
	int game_over[16];
	LoadDivGraph("picture/game_over.png", 16, 16, 1, 400, 80, game_over);
	int game_claer[18];
	LoadDivGraph("picture/game_claer.png", 18, 18, 1, 400, 80, game_claer);
	int title[28];
	LoadDivGraph("picture/title.png", 28, 28, 1, 480, 96, title);
	int level_up[12];
	LoadDivGraph("picture/level_up.png", 12, 12, 1, 400, 40, level_up);
	int bullets[9];
	LoadDivGraph("picture/bullets.png", 9, 9, 1, 400, 40, bullets);
	int damage_up[9];
	LoadDivGraph("picture/damege.png", 9, 9, 1, 320, 40, damage_up);

	int huti;
	huti = LoadGraph("picture/huti.png");
	int move;
	move = LoadGraph("picture/move.png");
	int pouse;
	pouse = LoadGraph("picture/pause.png");
	int boss_main;
	boss_main = LoadGraph("picture/boss_main.png");
	int boss_sub1;
	boss_sub1 = LoadGraph("picture/boss_sub.png");
	int boss_sub2;
	boss_sub2 = LoadGraph("picture/boss_sub.png");

	//�v���C���[�̉摜
	int player[4];
	LoadDivGraph("picture/player.png", 4, 4, 1, 32, 32, player);//�~�܂��Ă���Ƃ�
	int playermove[8];
	LoadDivGraph("picture/playerRun1.png", 8, 8, 1, 32, 32, playermove);//�����Ă���Ƃ�
	int shot[3];
	LoadDivGraph("picture/shot.png", 3, 3, 1, 16, 16, shot);//�e

	//�G�̉摜
	int enemy[2];
	LoadDivGraph("picture/enemy1.png", 2, 2, 1, 32, 32, enemy);
	int enemy_ko[2];
	LoadDivGraph("picture/enemy2.png", 2, 2, 1, 32, 32, enemy_ko);
	int boss_dawn_gif[7];
	LoadDivGraph("picture/bossdawn.png", 7, 7, 1, 128, 128, boss_dawn_gif);
	int enemy_shot = LoadGraph("picture/enemy_shot.png", true);


	//�w�i
	int backscreen = LoadGraph("picture/backscreen.png", true);
	int backscreen1 = LoadGraph("picture/backscreen.png", true);

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
	int lu = 0;
	int lu_time = 0;
	int lu_flag = 0;
	int bl = 0;
	int bl_time = 0;
	int bl_flag = 0;
	int du = 0;
	int du_time = 0;

	//�v���C���[���
	double player_posx = 300;				//�����W
	double player_posy = 800;				//�����W
	double player_speed = 8;				//�v���C���[�̑���
	double player_size = 20;				//�v���C���[�̑傫��
	int player_flag = 1;				//�v���C���[�̃t���b�O
	int player_gif_time = 0;
	int p = 0;
	int p_time = 30;
	double player_move = 0;
	int mv = 0;

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
	int damage_flag = 0;
	int damage_flag2 = 0;

	//�G�̏��
	double enemy_posx[256] = { 0 };		//�~��X���W
	double enemy_posy[256] = { 0 };		//�~��Y���W
	double enemy_flag[256] = { 0 };		//�G�̃t���b�O���
	int enemy_respown[256] = { 0 };		//�����^�C�}�[
	int enemy_x_speed = 0;			//�~�̑����BX���W
	int enemy_y_speed = 1;			//�~�̑����BY���W
	double enemy_size = 15;			//�G�̒��a
	int enemy_number = 5;				//�G�̏���ݒ�
	int e = 0;
	int e_ko = 0;
	int enemy_gif_time = 0;
	int boom_time[256] = { 0 };
	int enemy_ko_posx[256] = { 0 };
	int enemy_ko_posy[256] = { 0 };

	//�G�̒e
	int enemy_shot_posx[256] = { 0 };
	int enemy_shot_posy[256] = { 0 };
	int enemy_shot_flag[256] = { 0 };
	int enemy_shot_speedx[256] = { 0 };
	int enemy_shot_speedy[256] = { 0 };
	int enemy_shot_counter = 0;



	//�{�X���
	int boss_main_posx = 350;				//�{�X���C���@X
	int boss_main_posy = 5;				//�{�X���C���@Y
	int boss_main_size = 64;				//�T�C�Y
	int boss_main_hp = 1;				//HP
	int boss_sub1_posx = 200;				//�{�X�T�u�PX
	int boss_sub1_posy = 10;				//�{�X�T�u�PY
	int boss_sub1_size = 32;				//�T�C�Y
	int boss_sub1_hp = 30;				//HP
	int boss_sub2_posx = 400;				//�{�X�T�u�QX
	int boss_sub2_posy = 10;				//�{�X�T�u�QY
	int boss_sub2_size = 32;				//�T�C�Y
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
	int bdg_time = 0;
	int bdg = 0;
	int stop_flag = 0;
	int start_boss_flag = 0;
	const int enemy_shot_redius = (shot_size + player_size) * (shot_size + player_size);

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
	SetFontSize(20);

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
		if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_RIGHT))
		{
			if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_DOWN))
			{
				player_move = 0.7f;//�ړ��W����0.71�ɐݒ�
			}
			else
			{
				player_move = 1.0f;//�΂߂���Ȃ����1.0�ɐݒ�
			}
		}

		else if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_DOWN))
		{
			player_move = 1.0f;
		}

		if (CheckHitKey(KEY_INPUT_LEFT) && player_posx >= 20 + player_size)
		{
			player_posx -= player_speed * player_move;
		}


		if (CheckHitKey(KEY_INPUT_RIGHT) && player_posx <= 570)
		{
			player_posx += player_speed * player_move;
		}


		if (CheckHitKey(KEY_INPUT_UP) && player_posy >= 30 + player_size)
		{
			player_posy -= player_speed * player_move;
		}

		if (CheckHitKey(KEY_INPUT_DOWN) && player_posy <= WIN_HEIGHT - 60)
		{
			player_posy += player_speed * player_move;
		}//�����܂ł�����ݒ�B

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
			case 0:

				if (CheckSoundMem(main_bgm) == 1 || CheckSoundMem(gameover) == 1 || CheckSoundMem(clear) == 1)
					{
						StopSoundMem(main_bgm);
						StopSoundMem(gameover);
						StopSoundMem(clear);
					}
					else
					{
						PlaySoundMem(titlebgm, DX_PLAYTYPE_LOOP, false);
					}
					break;
			case 1:
					if (CheckSoundMem(titlebgm) == 1)
					{
						StopSoundMem(titlebgm);
					}
					else
					{
						PlaySoundMem(main_bgm, DX_PLAYTYPE_LOOP, false);
					}
					break;
			case 2://p�|�[�Y���

					/*if (CheckSoundMem(secene_sc) == 1)
					{
						StopSoundMem(secene_sc);
					}
					else
					{
						PlaySoundMem(secene_sd, DX_PLAYTYPE_LOOP, false);
					}*/
					break;
			case 3://�s�k���
					if (CheckSoundMem(main_bgm) == 1)
					{
						StopSoundMem(main_bgm);
					}
					else
					{
						PlaySoundMem(gameover, DX_PLAYTYPE_LOOP, false);
					}
					break;
			case 4:
				if (CheckSoundMem(main_bgm) == 1)
				{
					StopSoundMem(main_bgm);
				}
				else
				{
					PlaySoundMem(clear, DX_PLAYTYPE_LOOP, false);
				}


				break;

		}


		switch (scene)
		{
			//�X�V����
			case 0:
				PlaySoundMem(titlebgm, DX_PLAYTYPE_LOOP, FALSE);
				//�V�[���؂�ւ��悤�B�X�^�[�g���j���[
				if (keys[KEY_INPUT_Z] == 1)
				{
					scene = 1;
				}
				//������
				score = 0;				//�X�R�A
				shot_upgrade = 10000;			//�e�̃A�b�v�O���[�h
				enemy_upgrade = 3000;				//�G�̃A�b�v�O���[�h
				time = 0;			//���Ԍo��

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
				for (int i = 0; i < 256; i++)
				{
					if (shot_flag[i] == 1)
					{
						shot_flag[i] = 0;
					}
				}

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
				enemy_number = 5;				//�G�̏���ݒ�

				for (int i = 0; i < 256; i++)
				{
					enemy_ko_posx[i] = { -100 };
					enemy_ko_posy[i] = { -100 };
				}


				//�{�X���
				boss_main_posx = 350;				//�{�X���C���@X
				boss_main_posy = -10;				//�{�X���C���@Y
				boss_main_hp = 120;				//HP
				boss_sub1_posx = 200;				//�{�X�T�u�PX
				boss_sub1_posy = -10;				//�{�X�T�u�PY
				boss_sub1_hp = 30;				//HP
				boss_sub2_posx = 400;				//�{�X�T�u�QX
				boss_sub2_posy = -10;				//�{�X�T�u�QY
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
				start_boss_flag = 0;
				stop_flag = 0;

				for (int i = 0; i < 256; i++)
				{
					enemy_shot_posx[i] = { 0 };
				}
				for (int i = 0; i < 256; i++)
				{
					enemy_shot_posy[i] = { 0 };

				}
				for (int i = 0; i < 256; i++)
				{
					enemy_shot_flag[i] = { 0 };
				}
				for (int i = 0; i < 256; i++)
				{

					enemy_shot_speedx[i] = { 0 };
				}
				for (int i = 0; i < 256; i++)
				{
					enemy_shot_speedy[i] = { 0 };
				}
				enemy_shot_counter = 0;

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
				if (scene == 0);
				{
					DrawGraph(100, 300, move, true);
					//DrawFormatString(0, 5, GetColor(150, 150, 0), "S�L�[�ŃX�^�[�g");
				}
				break;//secen 0

			case 1://�V�[���؂�ւ��悤�o�g����ʁB

				time++;//���Ԍo��

				if (keys[KEY_INPUT_P] == 1 && prev[KEY_INPUT_P] == 0)
				{
					scene = 2;
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
						mv++;
						player_gif_time = 0;
					}
					s++;
				}




				//�X�R�A�A�e�̃A�b�v�O���[�h�A�G�̃A�b�v�O���[�h�B
				if (score >= shot_upgrade)
				{
					shot_number += 1;
					shot_upgrade += 10000;
					lu_flag = 1;
				}
				if (score >= enemy_upgrade)
				{
					enemy_upgrade += 3000;
					enemy_number += 1;
				}

				//�{�X��˓�
				if (time > 3600 && boss_main_flag == 0 && boss_sub1_flag == 0 && boss_sub2_flag == 0)
				{
					boss_main_flag = 1;
					boss_sub1_flag = 1;
					boss_sub2_flag = 1;
				}
				if (lu_flag == 1)
				{
					lu_time++;
					if (lu_time >= 60)
					{
						lu++;
					}
				}
				if (bl_flag == 1)
				{
					bl_time++;
					if (bl_time >= 60)
					{
						bl++;
					}
				}


				//�e�̔���
				if (keys[KEY_INPUT_SPACE] == 1 && player_flag == 1)//&& prev[KEY_INPUT_SPACE] == 0)//����ǉ��Œ���������Ȃ�
				{
					//shot_music_flag = 1;
					shot_time -= 1;


					for (int i = 0; i < shot_number; i++)
					{
						if (shot_flag[i] == 0 && shot_time == 0)
						{
							shot_flag[i] = 1;
							PlaySoundMem(shot_music, DX_PLAYTYPE_BACK, true);
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
					if (enemy_flag[i] == 1 && enemy_posy[i] <= 300)
					{
						enemy_posy[i] += enemy_y_speed;
					}
				}

				enemy_shot_counter++;
				if (enemy_shot_counter == 100)
				{
					for (int i = 0; i < 256; i++)
					{
						// �������ɒe���w���ł��Ȃ��x��Ԃ������ꍇ�̂ݔ��ˏ������s��
						if (enemy_shot_flag[i] == 0)
						{
							// �e�̔��ˈʒu��ݒ肷��
							enemy_shot_posx[i] = enemy_posx[i];
							enemy_shot_posy[i] = enemy_posy[i];

							// �e�̈ړ����x��ݒ肷��
							{
								double sb, sbx, sby, bx, by, sx, sy;

								sx = enemy_posx[i] + enemy_size / 2;
								sy = enemy_posy[i] + enemy_size / 2;

								bx = player_posx + player_size / 2;
								by = player_posy + player_size / 2;

								sbx = bx - sx;
								sby = by - sy;

								// �����������߂�̂ɕW���֐��� sqrt ���g���A
								// ������g���ɂ� math.h ���C���N���[�h����K�v������
								sb = sqrt(sbx * sbx + sby * sby);

								// �P�t���[��������W�h�b�g�ړ�����悤�ɂ���
								enemy_shot_speedx[i] = sbx / sb * 8;
								enemy_shot_speedy[i] = sby / sb * 8;
							}
							if (enemy_posy[i] >= 10 && enemy_flag[i] == 1)
							{
								enemy_shot_flag[i] = 1;
							}
						}
						// �e��ł^�C�~���O���v�����邽�߂̕ϐ��ɂO����
						enemy_shot_counter = 0;
					}
				}
				//DrawFormatString(50, 440, GetColor(83, 160, 162), " flag[%d]", enemy_shot_flag[10]);//�X�R�A
				//DrawFormatString(50, 460, GetColor(83, 160, 162), "�G�l�~�[FLAG [%d]", enemy_flag[1]);//�X�R�A


				for (int i = 0; i < 256; i++)
				{
					if (enemy_shot_flag[i] == 1)
					{
						// �e���ړ�������
						enemy_shot_posx[i] += enemy_shot_speedx[i];
						enemy_shot_posy[i] += enemy_shot_speedy[i];

						// �����e����ʂ���͂ݏo�Ă��܂����ꍇ�͒e�̏�Ԃ��w���ł��Ȃ��x
						// ��\���O�ɂ���
						if (enemy_shot_posy[i] > 900 || enemy_shot_posy[i] < 0 || enemy_shot_posx[i] > 600 || enemy_shot_posx[i] < 0)
						{
							enemy_shot_flag[i] = 0;
						}
					}
				}

				for (int i = 0; i < 256; i++)
				{
					difference_posx[i] = (player_posx - enemy_shot_posx[i]) * (player_posx - enemy_shot_posx[i]);//X���W�̍�
					difference_posy[i] = (player_posy - enemy_shot_posy[i]) * (player_posy - enemy_shot_posy[i]);//Y���W�̍�
					if (player_flag == 1 && enemy_shot_flag[i] == 1)
					{
						if (enemy_shot_redius >= difference_posx[i] + difference_posy[i])
						{
							player_flag = 0;
							enemy_shot_flag[i] = 0;
						}
					}
				}


				//BOSS�̐ݒ�
				//�����蔻��
				if (boss_main_flag == 1)
				{
					//�_���[�W���₷�B�������
					if (boss_sub1_flag == 0 && boss_sub2_flag == 0 && damage_flag == 0)
					{
						shot_damage = 5;

					}


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
							PlaySoundMem(ok, DX_PLAYTYPE_BACK, true);
							shot_flag[i] = 0;
							boss_speed0_change += 1;
							if (boss_main_hp <= 0)
							{
								boss_main_flag = 0;
								stop_flag = 1;
								PlaySoundMem(bossdawn, DX_PLAYTYPE_BACK, true);
								score += 15000;

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
							PlaySoundMem(ok, DX_PLAYTYPE_BACK, true);
							shot_flag[i] = 0;
							boss_speed1_change += 1;
							if (boss_sub1_hp <= 0)
							{
								boss_sub1_flag = 0;
								damage_flag = 1;
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
							PlaySoundMem(ok, DX_PLAYTYPE_BACK, true);
							shot_flag[i] = 0;
							boss_speed2_change += 1;
							if (boss_sub2_hp <= 0)
							{
								damage_flag2 = 1;
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

				//���x�ω�������B

				if (boss_speed0_change >= 3)
				{
					boss_speed0_posx = GetRand(6 + 1);
					boss_speed0_posy = GetRand(7 + 1);
					boss_speed0_change = 0;
				}
				if (boss_speed1_change >= 3)
				{
					boss_speed1_posx = GetRand(7 + 1);
					boss_speed1_posy = GetRand(7 + 1);
					boss_speed1_change = 0;
				}
				if (boss_speed2_change >= 3)
				{
					boss_speed2_posx = GetRand(7 + 1);
					boss_speed2_posy = GetRand(7 + 1);
					boss_speed2_change = 0;
				}

				//�{�X�̈ړ�

				if (boss_main_flag && start_boss_flag == 0)
				{
					if (boss_main_posy != 200)
					{
						boss_main_posy++;
					}
					if (boss_sub1_posy != 250)
					{
						boss_sub1_posy++;
					}
					if (boss_sub2_posy != 250)
					{
						boss_sub2_posy++;
					}
					if (boss_main_posy == 200 && boss_sub1_posy == 250 && boss_sub2_posy == 250)
					{
						start_boss_flag = 1;
					}
				}
				if (start_boss_flag)
				{
					//X�̈ړ�����
					if (boss_main_posx >= 600 - boss_main_size + 18 || boss_main_posx <= 0 + boss_main_size - 18)
					{
						boss_speed0_posx = -boss_speed0_posx;
					}
					if (boss_sub1_posx >= 600 - boss_main_size + 18 || boss_sub1_posx <= 0 + boss_main_size - 18)
					{
						boss_speed1_posx = -boss_speed1_posx;
					}
					if (boss_sub2_posx >= 600 - boss_main_size + 18 || boss_sub2_posx <= 0 + boss_main_size - 18)
					{
						boss_speed2_posx = -boss_speed2_posx;
					}
					//Y�̈ړ�����
					if (boss_main_posy <= 0 - boss_main_size + 150 || boss_main_posy >= 900 + boss_main_size - 160)
					{
						boss_speed0_posy = -boss_speed0_posy;
					}
					if (boss_sub1_posy <= 0 - boss_sub1_size + 90 || boss_sub1_posy >= 900 + boss_sub1_size - 100)
					{
						boss_speed1_posy = -boss_speed1_posy;
					}
					if (boss_sub2_posy <= 0 - boss_sub2_size + 90 || boss_sub2_posy >= 900 + boss_sub2_size - 100)
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
								PlaySoundMem(ripea, DX_PLAYTYPE_BACK, true);
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
					if (enemy_flag[i] == 0 && stop_flag == 0)
					{
						boom_time[i] -= 1;
						enemy_respown[i] -= 1;
						if (enemy_respown[i] <= 0)
						{
							if (boss_main_flag != 1)
							{
								enemy_posx[i] = GetRand(400) + 50;
								enemy_posy[i] = -30;
								enemy_flag[i] = 1;
								enemy_respown[i] = 100;
								boom_time[i] = 10;
							}
							else
							{
								boom_time[i] = 0;
							}
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
				//DrawFormatString(0, 5, GetColor(150, 150, 0), "�e�̃t���b�O0[%d]", shot_flag[0]);//�e�̕\��
				//DrawFormatString(0, 20, GetColor(150, 150, 0), "�e�̃t���b�O1[%d]", shot_flag[1]);//�e�̕\��
				//DrawFormatString(0, 40, GetColor(150, 150, 0), "�e�̃t���b�O2[%d]", shot_flag[2]);//�e�̕\��
				//DrawFormatString(0, 60, GetColor(150, 150, 0), "�e�̃t���b�O3[%d]", shot_flag[3]);//�e�̕\��
				//DrawFormatString(0, 80, GetColor(150, 150, 0), "�e�̃t���b�O4[%d]", shot_flag[4]);//�e�̕\��
				//DrawFormatString(0, 100, GetColor(150, 150, 0), "�G�̃t���b�O [%d]", enemy_flag[0]);  //�G�̕\��
				////DrawFormatString(0, 120, GetColor(150, 150, 0), "�G�̃t���b�O [%d]", enemy_flag[1]);  //�G�̕\��
				////DrawFormatString(0, 140, GetColor(150, 150, 0), "�G�̃t���b�O [%d]", enemy_flag[2]);  //�G�̕\��
				//DrawFormatString(0, 160, GetColor(150, 150, 0), "�A�b�v�O���[�h���� [%d]", shot_upgrade);  //�e�����₷���߂̏���
				//DrawFormatString(0, 180, GetColor(150, 150, 0), "���݂̃X�R�A [%d]", score);//�X�R�A
				//DrawFormatString(0, 200, GetColor(150, 150, 0), "�GX[0] [%d]", enemy_posx[0]);//�X�R�A
				//DrawFormatString(0, 220, GetColor(150, 150, 0), "�GY[0] [%d]", enemy_posy[0]);//�X�R�A
				//DrawFormatString(0, 240, GetColor(150, 150, 0), "�GX[1] [%d]", enemy_posx[1]);//�X�R�A
				//DrawFormatString(0, 260, GetColor(150, 150, 0), "�GY[1] [%d]", enemy_posy[1]);//�X�R�A
				//DrawFormatString(0, 280, GetColor(150, 150, 0), "time[0] [%d]", enemy_respown[0]);//�X�R�A
				//DrawFormatString(0, 300, GetColor(150, 150, 0), "time[1] [%d]", enemy_respown[1]);//�X�R�A
				//DrawFormatString(0, 320, GetColor(150, 150, 0), "�G�̏o������ [%d]", enemy_number);
				//DrawFormatString(0, 340, GetColor(150, 150, 0), "�G�̏o������ [%d]", enemy_upgrade);
				//DrawFormatString(0, 360, GetColor(150, 150, 0), "ESC�L�[�Ń|�[�Y");
				//DrawFormatString(0, 400, GetColor(150, 150, 0), "%d", boss_main_flag);
				//DrawFormatString(0, 420, GetColor(150, 150, 0), "%d", boss_sub1_flag);
				//DrawFormatString(0, 440, GetColor(150, 150, 0), "%d", boss_sub2_flag);
				//DrawFormatString(0, 460, GetColor(150, 150, 0), "%d", boss_main_hp);
				//DrawFormatString(0, 500, GetColor(150, 150, 0), "%d", time);
				//DrawFormatString(0, 520, GetColor(150, 150, 0), "%d", boss_speed0_change);
				//DrawFormatString(0, 550, GetColor(150, 150, 0), "%d", boss_speed0_posx);
				//DrawFormatString(50, 570, GetColor(150, 150, 0), "%d", player_flag);
				//DrawFormatString(17, 120, GetColor(83, 160, 162), "sg [%d]", sg);//�X�R�A
				//DrawFormatString(17, 140, GetColor(83, 160, 162), "rs [%d]", rs);//�X�R�A
				//DrawFormatString(17, 160, GetColor(83, 160, 162), "  bg [%d]", bg);//�X�R�A
				//DrawFormatString(17, 180, GetColor(83, 160, 162), " go [%d]", go);//�X�R�A
				//DrawFormatString(17, 200, GetColor(83, 160, 162), "  gc [%d]", gc);//�X�R�A
				//DrawFormatString(17, 220, GetColor(83, 160, 162), " ti [%d]", ti);//�X�R�A
				//DrawFormatString(17, 240, GetColor(83, 160, 162), " lu [%d]", lu);//�X�R�A
				//DrawFormatString(17, 260, GetColor(83, 160, 162), "bl [%d]", bl);//�X�R�A
				//DrawFormatString(17, 280, GetColor(83, 160, 162), " du [%d]", du);//�X�R�A
				//DrawFormatString(17, 300, GetColor(83, 160, 162), " p [%d]", p);//�X�R�A
				//DrawFormatString(17, 320, GetColor(83, 160, 162), "mv [%d]", mv);//�X�R�A
				//DrawFormatString(17, 340, GetColor(83, 160, 162), "s [%d]", s);//�X�R�A
				//DrawFormatString(17, 360, GetColor(83, 160, 162), "e [%d]", e);//�X�R�A
				//DrawFormatString(17, 380, GetColor(83, 160, 162), " e_ko [%d]", e_ko);//�X�R�A
				//DrawFormatString(50, 400, GetColor(83, 160, 162), " arara[%d]", enemy_shot_counter);//�X�R�A
				DrawFormatString(20, 45, GetColor(83, 160, 162), "SCORE [%d]", score);//�X�R�A
				DrawFormatString(20, 65, GetColor(83, 160, 162), "BULLTE [%d]", shot_number);




				if (damage_flag == 1 && damage_flag2 == 1)
				{
					du_time++;
					if (du_time >= 10)
					{
						du++;
						du_time = 0;
					}
					DrawGraph(100, 500, damage_up[du], TRUE);
				}
				if (du >= 8)
				{
					damage_flag = 2;
					du = 0;
				}

				if (player_flag == 1)
				{
					if (keys[KEY_INPUT_RIGHT] == 1 || keys[KEY_INPUT_UP] == 1 || keys[KEY_INPUT_LEFT] == 1 || keys[KEY_INPUT_DOWN] == 1 || keys[KEY_INPUT_SPACE] == 1)
					{
						//DrawGraph(player_posx - player_size, player_posy - player_size, playermove[mv], true);
						DrawGraph(player_posx - player_size, player_posy - player_size, playermove[mv], true);

					}
					else
					{
						DrawGraph(player_posx - player_size, player_posy - player_size, player[p], true);
					}
					if (p >= 3)
					{
						p = 0;
					}
				}
				if (mv >= 7)
				{
					mv = 0;
				}

				//�e�̕\��
				for (int i = 0; i < shot_number; i++)
				{
					if (shot_flag[i] == 1)
					{
						//DrawCircle(shot_bullte_posx[i], shot_bullte_posy[i], shot_size, GetColor(150, 250, 45), TRUE);//�e�̕\��
						DrawGraph(shot_bullte_posx[i] - shot_size - 5, shot_bullte_posy[i] - shot_size, shot[s], true);
					}
					if (s >= 2)
					{
						s = 0;
					}
				}

				for (int i = 0; i < 256; i++)
				{
					if (enemy_shot_flag[i] == 1)
					{
						//DrawCircle(shot_bullte_posx[i], shot_bullte_posy[i], shot_size, GetColor(150, 250, 45), TRUE);//�e�̕\��
						DrawGraph(enemy_shot_posx[i] - shot_size - 5, enemy_shot_posy[i] - shot_size, enemy_shot, true);
					}
					if (s >= 2)
					{
						s = 0;
					}
				}


				//�G�̕\��
				for (int i = 0; i < enemy_number; i++)
				{
					if (enemy_flag[i] == 1)
					{
						//DrawCircle(enemy_posx[i], enemy_posy[i], enemy_size, GetColor(150, 250, 45), TRUE);//�G�̕\��	
						DrawGraph(enemy_posx[i] - enemy_size, enemy_posy[i] - enemy_size, enemy[e], TRUE);
					}
				}
				if (e >= 1)
				{
					e = 0;
				}
				for (int i = 0; i < enemy_number; i++)
				{
					if (enemy_flag[i] == 0 && boom_time[i] >= 1)
					{
						DrawGraph(enemy_ko_posx[i] - enemy_size, enemy_ko_posy[i] - enemy_size, enemy_ko[e_ko], TRUE);
					}
				}
				if (e_ko >= 1)
				{
					e_ko = 0;
				}

				//BOSS��̕`��
				if (boss_main_flag == 1 && boss_main_hp >= 0)
				{
					//DrawCircle(boss_main_posx, boss_main_posy, boss_main_size, GetColor(150, 250, 45), TRUE);
					DrawGraph(boss_main_posx - boss_main_size, boss_main_posy - boss_main_size, boss_main, TRUE);

					if (boss_sub1_flag == 1 && boss_sub1_hp >= 0)
					{
						//DrawCircle(boss_sub1_posx, boss_sub1_posy, boss_sub1_size, GetColor(150, 250, 45), TRUE);
						DrawGraph(boss_sub1_posx - boss_sub1_size, boss_sub1_posy - boss_sub1_size, boss_sub1, TRUE);
					}
					if (boss_sub2_flag == 1 && boss_sub2_hp >= 0)
					{
						//DrawCircle(boss_sub2_posx, boss_sub2_posy, boss_sub2_size, GetColor(150, 250, 45), TRUE);
						DrawGraph(boss_sub2_posx - boss_sub2_size, boss_sub2_posy - boss_sub2_size, boss_sub2, TRUE);
					}
				}
				if (boss_main_flag == 0 && time > 3600)
				{
					bdg_time++;
					if (bdg_time >= 20)
					{
						bdg++;
						bdg_time = 0;
					}
					DrawGraph(boss_main_posx - boss_main_size, boss_main_posy - boss_main_size, boss_dawn_gif[bdg], TRUE);
				}
				if (bdg >= 6)
				{
					bdg = 0;
					scene = 4;
				}


				DrawGraph(20, 28, pouse, true);
				if (lu_flag == 1)
				{
					DrawGraph(100, 600, level_up[lu], TRUE);
				}
				if (lu >= 11)
				{
					lu = 0;
					lu_flag = 0;
					bl_flag = 1;
				}
				if (bl_flag == 1)
				{
					DrawGraph(100, 600, bullets[bl], TRUE);
				}
				if (bl >= 8)
				{
					bl = 0;
					bl_flag = 0;
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
				if (scene == 2)
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
				//DrawFormatString(0, 360, GetColor(150, 150, 0), "GAME�@OVER");
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
					if (go >= 15)
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

		//DrawFormatString(0, 450, GetColor(150, 150, 0), "���secen[%d]", scene);
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

	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(start[i]);
		DeleteGraph(restsrt[i]);
		DeleteGraph(backgame[i]);
		DeleteGraph(enemy[i]);
		DeleteGraph(enemy_ko[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(shot[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(player[i]);
	}
	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(boss_dawn_gif[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(playermove[i]);
	}
	for (int i = 0; i < 9; i++)
	{
		DeleteGraph(bullets[i]);
		DeleteGraph(damage_up[i]);
	}
	for (int i = 0; i < 12; i++)
	{
		DeleteGraph(level_up[i]);
	}
	for (int i = 0; i < 16; i++)
	{
		DeleteGraph(game_over[i]);
	}
	for (int i = 0; i < 18; i++)
	{
		DeleteGraph(game_claer[i]);
	}
	for (int i = 0; i < 28; i++)
	{
		DeleteGraph(title[i]);
	}


	DeleteGraph(huti);
	DeleteGraph(move);
	DeleteGraph(pouse);
	DeleteGraph(boss_main);
	DeleteGraph(boss_sub1);
	DeleteGraph(boss_sub2);
	DeleteSoundMem(shot_music);
	DeleteSoundMem(ok);
	DeleteSoundMem(ripea);
	DeleteSoundMem(bossdawn);
	DeleteGraph(backscreen);
	DeleteGraph(backscreen1);
	DeleteSoundMem(titlebgm);
	DeleteSoundMem(main_bgm);
	DeleteSoundMem(gameover);
	DeleteSoundMem(clear);
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
