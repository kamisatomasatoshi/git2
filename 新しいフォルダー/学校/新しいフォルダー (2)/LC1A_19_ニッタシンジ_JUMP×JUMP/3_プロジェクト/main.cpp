#include "DxLib.h"
#include "stdlib.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LC1A_19_�j�b�^�V���W: JUMP�~JUMP";

// �E�B���h�E����
const int WIN_WIDTH = 800;

// �E�B���h�E�c��
const int WIN_HEIGHT = 800;

enum switch_flag
{
	OFF,
	ON
};

float diagonal_num_sum ()
{
	if (CheckHitKey(KEY_INPUT_LEFT) == 1 || CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		if (CheckHitKey(KEY_INPUT_DOWN) == 1 || CheckHitKey(KEY_INPUT_UP) == 1)
		{
			return  0.7; //�΂߂̌W��
		}
		else
		{
			 return  1.0; //�΂߂���Ȃ���΂��̂܂�
		}
	}
	else if (CheckHitKey(KEY_INPUT_UP)== 1 || CheckHitKey(KEY_INPUT_DOWN)== 1)
	{
		return  1.0; //�΂߂���Ȃ���΂��̂܂�
	}
}

void draw_player(float player_pos_x,float player_pos_y,int player_handle[1])
{
	DrawGraph(player_pos_x, player_pos_y, player_handle[1], true);

	if(CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		DrawGraph(player_pos_x, player_pos_y, player_handle[0], true);
	}
	if(CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		DrawGraph(player_pos_x, player_pos_y, player_handle[0], true);
	}
	if(CheckHitKey(KEY_INPUT_UP) == 1)
	{
		DrawGraph(player_pos_x, player_pos_y, player_handle[0], true);
	}
	if(CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		DrawGraph(player_pos_x, player_pos_y, player_handle[0], true);
	}

}

//���̕`��
void Draw_line(int scroll_line_x, int scroll_line_y, int scroll_line_w,int scroll_line_h, unsigned int word_color);

//�w�i�̕`��
void Draw_background(int number_handle[], float scroll_y, float monitor_x);

//monitor���W�̌v�Z
float monitor_x_calculation(float world_x, float scroll_x);

float monitor_y_calculation(float world_y, float scroll_y);

//�X�N���[�����J�n����Ă��邩�ǂ����𔻒f����t���O
bool IsScrollflag(float monitor_y, float scroll_line_y);

//float player_move(float player_pos_x, float player_r, float player_speed, float diagonal_num)
//{
//	if (CheckHitKey(KEY_INPUT_LEFT) == 1 && player_pos_x >= 0)
//	{
//		return   player_speed ;
//	}
//
//	if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && player_pos_x + player_r <= WIN_WIDTH)
//	{
//		return   player_speed ;
//	}
//}

typedef struct circle
{
	float pos_x;
	float pos_y;
	float r;
	int FillFlag;
	float speed;
};

//���̍\����
typedef struct line {
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	unsigned int color;
};

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
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
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���

	//�w�i�摜�̓ǂݍ���
	int back_ground_number_handle[] = { 0,1,2,3 };

	back_ground_number_handle[0] = LoadGraph("summer_game_background1.png");

	back_ground_number_handle[1] = LoadGraph("summer_game_background2.png");

	back_ground_number_handle[2] = LoadGraph("summer_game_background3.png");

	back_ground_number_handle[3] = LoadGraph("summer_game_background4.png");

	//�^�C�g���摜�̓ǂݍ���
	int title_handle = 0;
	title_handle = LoadGraph("summer_game_title1.png");

	//�����̉摜�̓ǂݍ���
	int number_handle = 0;
	number_handle = LoadGraph("game_summer_number.png");

	//�~�̉������͒[����42�}�X
	int player_handle[3] = { 0 };
	LoadDivGraph(
		"player_summer_game.png",
		3,
		3, 1,
		64,68,
		player_handle
	);

	int select_stage_handle = 0;
	select_stage_handle = LoadGraph("select_stage.png");

	int stage_base_handle = 0;
	stage_base_handle = LoadGraph("dodai_test2.png");

	int space_key_handle = 0;
	space_key_handle = LoadGraph("game_summer_space.png");

	int arrow_sign_handle = 0;
	arrow_sign_handle = LoadGraph("arrow_sign.png");

	int title_return_handle = 0;
	title_return_handle = LoadGraph("summer_game_title_return.png");

	int continue_handle = 0;
	continue_handle = LoadGraph("summer_game_continue.png");

	int game_over_handle = 0;
	game_over_handle = LoadGraph("summer_game_game_over.png");

	int game_clear_handle = 0;
	game_clear_handle = LoadGraph("summer_game_game_clear.png");

	int goal_handle = 0;
	goal_handle = LoadGraph("select_hole_1.png");

	int now_loding_handle = 0;
	now_loding_handle = LoadGraph("summer_game_now_loding.png");

	int arrow_handle = 0; 
	arrow_handle = LoadGraph("summer_game_arrows.png");

	int jump_handle = 0;
	jump_handle = LoadGraph("jump_summer_game.png");

	//���y�̕ϐ�

	int op_bgm_handle = LoadSoundMem("op_bgm.mp3");
	ChangeVolumeSoundMem(100, op_bgm_handle);

	int play_bgm_handle = LoadSoundMem("play_bgm.mp3");
	ChangeVolumeSoundMem(80, play_bgm_handle);

	int button_handle = LoadSoundMem("button.mp3");
	ChangeVolumeSoundMem(128, button_handle);

	int two_jump_handle = LoadSoundMem("jump_2.mp3");
	ChangeVolumeSoundMem(128,two_jump_handle);

	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	//���@�̊�b�ݒ�
	circle player =
	{
		340.0f,
		400.0f,
		128.0f,
		true,
		3.0f
	};

	circle first_stage =
	{
		290.0f,
		380.0f,
		96.0f,
		true,
		2.0f
	};
	
	circle second_stage =
	{
		290.0f,
		180.0f,
		96.0f,
		true,
		2.0f
	};

	//player�̒ǉ����
	float player_left_side = 0; //(���O�r)
	float player_right_side = 0;
	float player_top_side = 0;
	float player_down_side = 0;
	
	 float diagonal_num = 1.0f; //���@�ړ��̎΂ߌW��

	//�e�V�[���p�̕ϐ�
	int scene = 0;

	//�V�[���p�̑҂��^�C�}�[
	int scene_timer = 10;

	//�^�C�g����ʗp�̕ϐ�

	int space_anime_time = 0;
	int space_anime_time_flag = 0;

	//�W�����v�p�̕ϐ�
	bool jump_flag = 0;
	bool jump_flag_twice = 0;
	float jump_speed_timer = 11.0f;
	float gravity_speed = 9.8f;
	int jump_count = 0; //�W�����v���𐔂��āA�񐔂𐧌�����p�̕ϐ�
	int jump_count_timer = 0;
	bool jump_count_flag = 0;

	//�ҋ@���̃A�j���[�V�����p�ϐ�

	float wait_anime_timer = 7.0f;
	bool loop_up_flag = 0;
	bool loop_down_flag = 0;

	//�X�e�[�W�I��p�̕ϐ�

	bool first_stage_flag = 1;
	bool second_stage_flag = 0;
	//�ړ����̑҂��^�C�}�[
	int stage_wait_timer = 15;
	//�ړ������鎞�̕ۑ��p�ϐ�
	float save_stage_info_pos_x = 0.0f;
	float save_stage_info_pos_y = 0.0f;

	//�X�N���[���p�̕ϐ�

	//���[���h���W
	float world_x = player.pos_x;
	float world_y = player.pos_y;
	//���j�^�[���W
	float monitor_x = 0.0f;
	float monitor_y = 0.0f;
	//�X�N���[���l
	float scroll_x = 0.0f;
	float scroll_y = 0.0f;

	//�X�N���[���J�n�ʒu�̐��̍��W
	line scroll_line = {
		0,
		350,
		800,
		350,
		GetColor(255,0,0)
	};

	//�X�N���[��������Ă��邩�ǂ����̃t���O
	bool is_scrollflag = 0;

	//�X�e�[�W�̓y��p�̕ϐ�
	float base_x[10] = { 85,340,272,400,150,456,289,543,653,440};
	float base_y[10] = { 300,530,100,0,400,-300,-450,-670,-900,-1200};
	float base_r = 32;

	//�v���C���[�Ɠy�䂪�G�ꂽ���̃t���O

	bool base_confrict_flag[10] = { 0,1,0,0,0,0,0,0,0,0};

	//�Q�[���v���C��̑I���{�^��

	int select_button_x = 150;
	int select_button_y = 285;

	//�Q�[���I�[�o�[��ʂ̕ϐ�

	int continue_anime_timer = 30;
	int continue_anime_flag = 0;

	//�Q�[���N���A��ʂ̕ϐ�

	int game_clear_anime_timer = 10;

	//���[�f�B���O��ʗp�̕ϐ�

	int Lording_timer = 270;


	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = {0};

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = {0};

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����

		//�e�V�[���̐ݒ�
		if (scene == 0)//�^�C�g�����
		{
			scene_timer--;
			space_anime_time--;
			if (space_anime_time <= 40)
			{
				space_anime_time_flag = 0;
			}
			if (space_anime_time <= 0)
			{
				space_anime_time_flag = 1;
				space_anime_time = 90;
			}

			if (keys[KEY_INPUT_SPACE] == 1 && scene_timer <= 0)
			{
				PlaySoundMem(button_handle, DX_PLAYTYPE_NORMAL, true);
				if (CheckSoundMem(op_bgm_handle) == 0)
				{
					PlaySoundMem(op_bgm_handle, DX_PLAYTYPE_BACK, true);
				}
				scene = 2;
				loop_up_flag = 1;
				player.pos_x = 650.0f;
				player.pos_y = 400.0f;
				world_x = 340.0f;
				world_y = 400.0f;
				scene_timer = 10;
			}
		}

		if (scene == 2)
		{
			Lording_timer--;
			if (Lording_timer <= 0)
			{
				player.pos_x = 340.0f;
				player.pos_y = 400.0f;
				space_anime_time = 0;
				scene = 1;
			}

			if (loop_up_flag == 1)
			{
				wait_anime_timer -= 0.7;
				player.pos_y -= player.speed + wait_anime_timer;
			}

			if (player.pos_y <= 300)
			{
				wait_anime_timer = 5.0f;
				loop_up_flag = 0;
				loop_down_flag = 1;
			}

			if (loop_down_flag == 1)
			{
				wait_anime_timer -= 0.7;
				player.pos_y += player.speed + wait_anime_timer;
			}

			if (player.pos_y >= 400)
			{
				wait_anime_timer = 5.0f;
				loop_up_flag = 1;
				loop_down_flag = 0;
			}
		}

		//�X�e�[�W�I�����
		if (scene == 1)
		{
			scene_timer--;

			scene_timer--;
			space_anime_time--;
			if (space_anime_time <= 40)
			{
				space_anime_time_flag = 0;
			}
			if (space_anime_time <= 0)
			{
				space_anime_time_flag = 1;
				space_anime_time = 90;
			}

			//�X�e�[�W�I����ʂŎ��@���Œ肳�����܂ܒ��˂����鏈��
			if (loop_up_flag == 1)
			{
				wait_anime_timer -= 0.7;
				player.pos_y -= player.speed + wait_anime_timer;
			}

			if (player.pos_y <= 300)
			{
				wait_anime_timer = 5.0f;
				loop_up_flag = 0;
				loop_down_flag = 1;
			}

			if (loop_down_flag == 1)
			{
				wait_anime_timer -= 0.7;
				player.pos_y += player.speed + wait_anime_timer;
			}

			if (player.pos_y >= 400)
			{
				wait_anime_timer = 5.0f;
				loop_up_flag = 1;
				loop_down_flag = 0;
			}
			//�X�e�[�W��I��������Ƃ��ɁA�e�X�e�[�W�̈ʒu�����������鏈��
			if (first_stage_flag == 1)
			{

				stage_wait_timer -= 1;

				if (stage_wait_timer <= 0 && keys[KEY_INPUT_UP] == 1 && oldkeys[KEY_INPUT_UP] == 0)
				{
						second_stage_flag = 1;
						first_stage_flag = 0;

						save_stage_info_pos_y = first_stage.pos_y;
						first_stage.pos_y = second_stage.pos_y;
						second_stage.pos_y = save_stage_info_pos_y;

						stage_wait_timer = 15;
				}


				if (stage_wait_timer <= 0 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 1 && scene_timer <= 0)
				{
					StopSoundMem(op_bgm_handle);
					PlaySoundMem(play_bgm_handle,DX_PLAYTYPE_BACK,true);
					scene = 3;
					scene_timer = 10;
					player.pos_x = 325.0f;
					player.pos_y = 456.0f;
					world_x = 325.0f;
					world_y = 456.0f;
				}
			}

			if (second_stage_flag == 1)
			{

				stage_wait_timer -= 1;

				if (stage_wait_timer <= 0 && keys[KEY_INPUT_DOWN] == 1 && oldkeys[KEY_INPUT_DOWN] == 0)
				{
						first_stage_flag = 1;
						second_stage_flag = 0;

						save_stage_info_pos_y = first_stage.pos_y;
						first_stage.pos_y = second_stage.pos_y;
						second_stage.pos_y = save_stage_info_pos_y;

						stage_wait_timer = 15;
				}

				if (stage_wait_timer <= 0 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 1 && scene_timer <= 0)
				{
					StopSoundMem(op_bgm_handle);
					PlaySoundMem(play_bgm_handle, DX_PLAYTYPE_BACK, true);
					scene = 4;
					scene_timer = 10;
					player.pos_x = 325.0f;
					player.pos_y = 456.0f;
					world_x = 325.0f;
					world_y = 456.0f;
				}
			}
		}

		//�v���C���[�̓���
		if (scene == 3 || scene == 4)//�v���C��ʂł̃v���C���[�̓���
		{
			if (scene == 4)
			{
				//scene4 ��4�ڂ���i�ڂŒ����悤�Ƃ���Ǝ󂯂��Ȃ��Ȃ�

				base_x[0] = 105;
				base_x[1] = 340;
				base_x[2] = 340;
				base_x[3] = 100;
				base_x[4] = 360;
				base_x[5] = 130;
				base_x[6] = 350;
				base_x[7] = 105;
				base_x[8] = 305;
				base_x[9] = 575;
				
				base_y[0] = 260;
				base_y[1] = 500;
				base_y[2] = 0;
				base_y[3] = -251;
				base_y[4] = -400;
				base_y[5] = -790;
				base_y[6] = -900;
				base_y[7] = -1140;
				base_y[8] = -1290;
				base_y[9] = -1400;
			}

			if (scene == 3)
			{
				base_x[0] = 85;
				base_x[1] = 340;
				base_x[2] = 272;
				base_x[3] = 400;
				base_x[4] = 150;
				base_x[5] = 456;
				base_x[6] = 289;
				base_x[7] = 543;
				base_x[8] = 653;
				base_x[9] = 440;

				base_y[0] = 300;
				base_y[1] = 530;
				base_y[2] = 100;
				base_y[3] = 0;
				base_y[4] = 400;
				base_y[5] = -300;
				base_y[6] = -450;
				base_y[7] = -670;
				base_y[8] = -900;
				base_y[9] = -1200;
			}

			diagonal_num = diagonal_num_sum();

			if (keys[KEY_INPUT_LEFT] == 1 && player.pos_x >= 0)
			{
				player.pos_x -= player.speed * diagonal_num;
			}
			if (keys[KEY_INPUT_RIGHT] == 1 && player.pos_x + player.r <= WIN_WIDTH)
			{
				player.pos_x += player.speed * diagonal_num;
			}

			//���j�^�[���W�̌v�Z
			monitor_y = monitor_y_calculation(world_y, scroll_y);

			if (world_y < 400 && world_y > -1600 && scroll_line.y >= player.pos_y)
			{
				is_scrollflag = ON;
			}

			//�X�N���[�����J�n���ꂽ�ꍇ�̏���
			if (is_scrollflag == ON)
			{
				if (world_y < 400 && world_y > -1600  && jump_flag == 1)
				{
					scroll_y += player.speed * jump_speed_timer + 5;
					//���[���h���W��Y�����v���C���[�̈ړ��ɍ��킹��
				}

				//��ʊO�ɍs���Ȃ��悤�͈͂�����
				if (scroll_y >= 1600)//�X�N���[���l��1600�ɂȂ�����Œ�
				{
					scroll_y = 1600;
					//is_scrollflag = OFF;
				}
				if (player.pos_y > scroll_line.y)//�X�N���[�����Ȃ����(��ԉ��̃X�e�[�W�ɖ߂����ꍇ�ɃX�N���[���l�����Z�b�g)
				{
					is_scrollflag = OFF;
					//scroll_y = 0;
				}
			}

			//�΂߈ړ��W��
			diagonal_num = diagonal_num_sum();

			//�W�����v�̓����ɃQ�[���v���C��ʂł̓y��̏�ɏ�锻���������
			player_left_side = player.pos_x + 25;
			player_right_side = player.pos_x + 40;
			player_top_side = player.pos_y ;
			player_down_side = player.pos_y + 34;


			//���E�̈ړ�����
			if (keys[KEY_INPUT_LEFT] == 1 && player.pos_x >= 0)
			{
				player.pos_x -= player.speed * diagonal_num;
				world_x -= player.speed * diagonal_num;
			}
			if (keys[KEY_INPUT_RIGHT] == 1 && player.pos_x + player.r <= WIN_WIDTH)
			{
				player.pos_x += player.speed * diagonal_num;
				world_x += player.speed * diagonal_num;
			}

			//�W�����v�̎d�g��
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{
				jump_flag = 1;
				jump_count += 1;
				for (int i = 0; i < 10; i++)
				{
					base_confrict_flag[i] = 0;
				}
			}

			if (jump_flag == 1)
			{
				jump_count_timer++;

				jump_speed_timer--;
				if (jump_speed_timer < 30)
				{
					player.pos_y -= player.speed * jump_speed_timer;
					world_y -= player.speed * jump_speed_timer;
				}

				jump_flag_twice = 1;

			}

			if (jump_flag_twice == 1)
			{
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
				{
					PlaySoundMem(two_jump_handle, DX_PLAYTYPE_BACK, true);
					if (jump_count == 2)
					{
						jump_speed_timer = 11.0f;
						jump_speed_timer--;
						if (jump_speed_timer < 11)
						{
							player.pos_y -= player.speed * jump_speed_timer;
							world_y -= player.speed * jump_speed_timer;
							if (jump_speed_timer < -11)
							{
								jump_speed_timer = -11;
							}
						}
					}
				}
			}

			for (int i = 0; i < 10; i++)
			{

				if (base_x[i] - 10 <= player_left_side && base_x[i] + 74 >= player_right_side) //�e���ӂ�5pixcel���]�T����������
				{
					if (jump_speed_timer <= 0 && player_down_side <= base_y[i] + scroll_y)
					{
						if(player_top_side >= base_y[i] + scroll_y -100)
						{
							world_y = base_y[i] + scroll_y - 78;
							player.pos_y = base_y[i] + scroll_y - 78;
							jump_flag = 0;
							jump_speed_timer = 11.0f;
							jump_count = 0;
							base_confrict_flag[i] = 1;
						}
					}

					//�������Ă��Ȃ����ɓy�䂩�痎���Ȃ�����
					if (base_confrict_flag[i] == 1)
					{
						world_y = base_y[i] + scroll_y -78;
						player.pos_y = base_y[i] + scroll_y -78;
					}
				}
				//�����̂������Ă��Ȃ����Ƀv���C���[����������d�g��

				if (base_x[i] -10 >= player_right_side || base_x[i] + 74 <= player_left_side )
				{
					if (player_down_side >= base_y[i] + scroll_y)
					{
						if (jump_flag == 0)
						{
							if (keys[KEY_INPUT_SPACE] == 0 && oldkeys[KEY_INPUT_SPACE] == 0)
							{
								player.pos_y += 3;
								if (player.pos_y >= 800)
								{
									player.pos_y = 800;
								}
							}
						}
					}
					if (player_down_side <= base_y[9] + scroll_y)
					{
						if (jump_flag == 0)
						{
							if (keys[KEY_INPUT_SPACE] == 0 && oldkeys[KEY_INPUT_SPACE] == 0)
							{
								player.pos_y += 2;
								if (player.pos_y >= 800)
								{
									player.pos_y = 800;
								}
							}
						}
					}
				}
				
				if (player.pos_y >= 800)
				{
					StopSoundMem(play_bgm_handle);
					player.pos_y = 800;
					world_y = 800;
					scene = 5;
					continue_anime_flag = 1;
					base_confrict_flag[1] = 1;
				}

				//�y�䂩�炸�ꂽ���ɓ������Ă���t���O��0�ɂ���B
				if (base_x[i] -10 >= player_left_side || base_x[i] + 74  <= player_right_side)
				{
					base_confrict_flag[i] = 0;
				}

				if (base_x[9] -10 <= player_left_side && base_x[9] + 74 >= player_right_side && scroll_y >= 1400)
				{
					if (base_y[9] + scroll_y -77 >= player_down_side && base_y[9] + scroll_y - 145 <= player_down_side)
					{
						StopSoundMem(play_bgm_handle);
						player.pos_y = 800;
						world_y = 800;
						scene = 6;
						continue_anime_flag = 1;
						base_confrict_flag[1] = 1;
					}
				}
			}
		}

		if (scene == 5)
		{
			//�I���{�^���̃A�j���[�V����
			if (continue_anime_flag == 1)
			{
				continue_anime_timer--;

				if (continue_anime_timer <= 0)
				{
					continue_anime_timer = 30;
				}
			}

			//�I���{�^���̕ϐ��ݒ�
			if(keys[KEY_INPUT_UP] == 1)
			{
				select_button_y = 285;
			}
			if(keys[KEY_INPUT_DOWN] == 1)
			{
				select_button_y = 585;
			}

			if (select_button_y == 285 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE]== 0)
			{
				scene = 1;
				player.pos_x = 340.0f;
				player.pos_y = 400.0f;
			}
			
			if (select_button_y == 585 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{
				scene = 0;
				player.pos_x = 340.0f;
				player.pos_y = 400.0f;
			}
		}

		if (scene == 6)
		{
			//�X�e�[�W�I����ʂŎ��@���Œ肳�����܂ܒ��˂����鏈��
			if (loop_up_flag == 1)
			{
				wait_anime_timer -= 0.7;
				player.pos_y -= player.speed + wait_anime_timer;
			}

			if (player.pos_y <= 300)
			{
				wait_anime_timer = 5.0f;
				loop_up_flag = 0;
				loop_down_flag = 1;
			}

			if (loop_down_flag == 1)
			{
				wait_anime_timer -= 0.7;
				player.pos_y += player.speed + wait_anime_timer;
			}

			if (player.pos_y >= 400)
			{
				wait_anime_timer = 5.0f;
				loop_up_flag = 1;
				loop_down_flag = 0;
			}

			if (select_button_y == 285 && keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{
				scene = 0;
				player.pos_x = 340.0f;
				player.pos_y = 400.0f;
			}
		}

		//�e�ϐ��̃��Z�b�g
		if (scene == 5 || scene == 6)
		{
			world_x = 340.0f;
			world_y = 400.0f;
			scroll_y = 0;
			Lording_timer = 100;

			jump_flag = 0;
			jump_speed_timer = 11.0f;
			jump_count = 0;
			jump_count_timer = 0;
		}

		// �`�揈��
		switch (scene)
		{
			//�^�C�g��
			case 0:
				SetBackgroundColor(0x20, 0x00, 0x20);

				DrawGraph(144, 0, title_handle, true);

				if (space_anime_time_flag == 1)
				{
					DrawGraph(280, 550, space_key_handle, true);
				}
				break;

			case 1:
				SetBackgroundColor(0x55, 0x00, 0x55);

				DrawGraph(first_stage.pos_x,first_stage.pos_y, select_stage_handle, true);

				DrawGraph(first_stage.pos_x,second_stage.pos_y, select_stage_handle, true);

				DrawGraph(player.pos_x +13, player.pos_y, player_handle[1], true);

				if (keys[KEY_INPUT_RIGHT] == 1)
				{
					DrawGraph(player.pos_x + 13, player.pos_y, player_handle[0], true);
				}
				if (keys[KEY_INPUT_LEFT] == 1)
				{
					DrawGraph(player.pos_x + 13, player.pos_y, player_handle[0], true);
				}
				if (keys[KEY_INPUT_UP] == 1)
				{
					DrawGraph(player.pos_x + 13, player.pos_y, player_handle[0], true);
				}
				if (keys[KEY_INPUT_DOWN] == 1)
				{
					DrawGraph(player.pos_x + 13, player.pos_y, player_handle[2], true);
				}

				DrawRectGraph(first_stage.pos_x + 96, first_stage.pos_y + 106, 1, 1, 6, 16, number_handle, TRUE, FALSE);

				DrawRectGraph(second_stage.pos_x + 94, second_stage.pos_y + 106, 9, 1, 10, 16, number_handle, TRUE, FALSE);

				DrawRectGraph(500, 300, 2, 2, 89, 97, arrow_sign_handle, TRUE, FALSE);

				DrawRectGraph(200, 300, 94, 3, 89, 97, arrow_sign_handle, TRUE, FALSE);

				if (space_anime_time_flag == 1)
				{
					DrawGraph(260, 550, space_key_handle, true);
				}

				break;

			case 2 :
				SetBackgroundColor(0x00, 0x00, 0x00);
				DrawGraph(125, 380, now_loding_handle, true);
				DrawGraph(player.pos_x + 5, player.pos_y + -20, player_handle[0], true);
				DrawGraph(500, 650, space_key_handle, true);
				DrawGraph(80, 600, arrow_handle, true);
				DrawGraph(500, 580, jump_handle, true);
				DrawRectGraph(684, 580, 61, 75, 43, 51, arrow_handle, TRUE, FALSE);

				break;

			case 3 :
				SetBackgroundColor(0x55, 0x00, 0x55);

				DrawGraph(monitor_x, 0 + scroll_y, back_ground_number_handle[0], true);
				DrawGraph(monitor_x, -800 + scroll_y, back_ground_number_handle[1], true);
				DrawGraph(monitor_x, -1600 + scroll_y, back_ground_number_handle[2], true);
				DrawGraph(monitor_x, -2400 + scroll_y, back_ground_number_handle[3], true);

				DrawGraph(player.pos_x, player.pos_y, player_handle[1], true);

				if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
				{
					DrawGraph(player.pos_x, player.pos_y, player_handle[0], true);
				}
				if (CheckHitKey(KEY_INPUT_LEFT) == 1)
				{
					DrawGraph(player.pos_x, player.pos_y, player_handle[0], true);
				}
				if (CheckHitKey(KEY_INPUT_UP) == 1)
				{
					DrawGraph(player.pos_x, player.pos_y, player_handle[0], true);
				}
				if (CheckHitKey(KEY_INPUT_DOWN) == 1)
				{
					DrawGraph(player.pos_x, player.pos_y, player_handle[0], true);
				}

				for (int i = 0; i < 10; i++)
				{
					DrawGraph(base_x[i], base_y[i] + scroll_y, stage_base_handle, true);
				}

				DrawGraph(base_x[9] - 5, base_y[9] + scroll_y -77, goal_handle, true);

				break;


			case 4:

				SetBackgroundColor(0x55, 0x00, 0x55);

				DrawGraph(monitor_x, 0 + scroll_y, back_ground_number_handle[0], true);
				DrawGraph(monitor_x, -800 + scroll_y, back_ground_number_handle[1], true);
				DrawGraph(monitor_x, -1600 + scroll_y, back_ground_number_handle[2], true);
				DrawGraph(monitor_x, -2400 + scroll_y, back_ground_number_handle[3], true);

				DrawGraph(player.pos_x, player.pos_y, player_handle[1], true);

				if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
				{
					DrawGraph(player.pos_x, player.pos_y, player_handle[0], true);
				}
				if (CheckHitKey(KEY_INPUT_LEFT) == 1)
				{
					DrawGraph(player.pos_x, player.pos_y, player_handle[0], true);
				}
				if (CheckHitKey(KEY_INPUT_UP) == 1)
				{
					DrawGraph(player.pos_x, player.pos_y, player_handle[0], true);
				}
				if (CheckHitKey(KEY_INPUT_DOWN) == 1)
				{
					DrawGraph(player.pos_x, player.pos_y, player_handle[0], true);
				}

				for (int i = 0; i < 10; i++)
				{
					DrawGraph(base_x[i], base_y[i] + scroll_y, stage_base_handle, true);
				}

				DrawGraph(base_x[9], base_y[9] + scroll_y - 77, goal_handle, true);

				break;


			case 5 :

				DrawGraph(250, 300, continue_handle, true);

				DrawGraph(300, 600, title_return_handle, true);

				DrawRectGraph(500, 450, 2, 2, 89, 97, arrow_sign_handle, TRUE, FALSE);

				DrawRectGraph(200, 450, 94, 3, 89, 97, arrow_sign_handle, TRUE, FALSE);

				DrawGraph(25, 100, game_over_handle, true);

				if (continue_anime_timer <= 15)
				{
					DrawGraph(select_button_x, select_button_y, player_handle[2], true);
				}
				if (continue_anime_timer > 15)
				{
					DrawGraph(select_button_x, select_button_y, player_handle[1], true);
				}
				break;

			case 6:

				DrawGraph(-10, 200, game_clear_handle, true);
				DrawGraph(player.pos_x, player.pos_y, player_handle[0], true);
				DrawGraph(300, 600, title_return_handle, true);
				DrawCircle(270, 635, 10, GetColor(255, 255, 255), true);
				break;
		}

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}

	//�摜�̌㏈��
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(player_handle[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(back_ground_number_handle[i]);
	}

	DeleteGraph(select_stage_handle);
	DeleteGraph(stage_base_handle);
	DeleteGraph(title_handle);
	DeleteGraph(number_handle);
	DeleteGraph(arrow_sign_handle);
	DeleteGraph(title_return_handle);
	DeleteGraph(continue_handle);
	DeleteGraph(game_over_handle);
	DeleteGraph(game_clear_handle);
	DeleteGraph(goal_handle);
	DeleteGraph(now_loding_handle);
	DeleteGraph(arrow_handle);
	DeleteGraph(jump_handle);

	DeleteSoundMem(op_bgm_handle);
	DeleteSoundMem(play_bgm_handle);
	DeleteSoundMem(button_handle);
	DeleteSoundMem(two_jump_handle);

	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}

//���j�^�[���W�̌v�Z
float monitor_x_calculation(float world_x, float scroll_x)
{
	return world_x - scroll_x;
}
float monitor_y_calculation(float world_y, float scroll_y)
{
	return world_y - scroll_y;
}
//�X�N���[�����J�n����邽�߂̏���
bool IsScrollflag(float monitor_y,float scroll_line_y)
{
	//if (monitor_y == scroll_line_y)
	if (monitor_y == scroll_line_y)
	{
		return ON;
	}
	else
	{
		return OFF;
	}
}
//�e���̕`��
void Draw_line(int scroll_line_x, int  scroll_line_y, int scroll_line_w,int scroll_line_h, unsigned word_color) 
{
	//scroll�J�n�ʒu�̐�
	DrawLine(scroll_line_x, scroll_line_y, scroll_line_w, scroll_line_h, word_color);
}
//�w�i�̕`��
void Draw_background(int number_handle[], float scroll_y, float monitor_x)
{
	DrawGraph(monitor_x, 0 - scroll_y, number_handle[0], true);
	DrawGraph(monitor_x, 800 - scroll_y, number_handle[1], true);
	DrawGraph(monitor_x, 1600 - scroll_y, number_handle[2], true);

}