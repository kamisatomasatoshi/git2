#include "DxLib.h"
#include"map.h"
#include"player.h"



// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LC1A_08_オキヤマクニアキ";

// ウィンドウ横幅
const int WIN_WIDTH = 800;

// ウィンドウ縦幅
const int WIN_HEIGHT = 800;

VECTOR MoveInput(char keys[256], bool jump);

bool obj_hit(int left_ax, int up_ay, int right_ax, int down_ay, int left_bx, int up_by, int right_bx, int down_by);




int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x54);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int block3 = LoadGraph("resource\\block1.png");
	int player_gra = LoadGraph("resource\\player_main.png");
	int player_eye_gra[2];
	LoadDivGraph("resource\\player.png", 2, 2, 1, 32, 32, player_eye_gra);
	int trap_gra = LoadGraph("resource\\trap.png");

	int title_name = LoadGraph("resource\\title.png");

	int key_gra = LoadGraph("resource\\key.png");

	int start_button = LoadGraph("resource\\start.png");
	int start2_button = LoadGraph("resource\\start2.png");

	int select_door = LoadGraph("resource\\select_door.png");
	int exit = LoadGraph("resource\\exit.png");
	int lock_exit = LoadGraph("resource\\lock_exit.png");

	int title_menu = LoadGraph("resource\\title_menu.png");
	int title_menu2 = LoadGraph("resource\\title_menu2.png");

	int stage_text = LoadGraph("resource\\stage_text.png");

	int select_num[8];
	LoadDivGraph("resource\\stage_num.png", 8, 8, 1, 32, 32, select_num);

	int select2_num[8];
	LoadDivGraph("resource\\stage_num2.png", 8, 8, 1, 32, 32, select2_num);

	int clear_text[5];
	LoadDivGraph("resource\\clear_text.png", 5, 5, 1, 48, 64, clear_text);

	int timer_text[10];
	LoadDivGraph("resource\\timer_text.png", 10, 5, 2, 48, 64, timer_text);
	int timer_text_small[10];
	LoadDivGraph("resource\\timer_text_small.png", 10, 5, 2, 32, 32, timer_text_small);

	int second = LoadGraph("resource\\second.png");

	int time_text = LoadGraph("resource\\time_text.png");

	int haikei = LoadGraph("resource\\haikei.png");

	int retire = LoadGraph("resource\\retire.png");

	//音
	int mainBgm = LoadSoundMem("resource\\魔王魂 ループ  8bit27.mp3");
	ChangeVolumeSoundMem(50, mainBgm);

	int jump_sound = LoadSoundMem("resource\\se_jump3.mp3");

	int dead = LoadSoundMem("resource\\キャンセル3.mp3");

	int kettei = LoadSoundMem("resource\\決定、ボタン押下3.mp3");

	int key_sound = LoadSoundMem("resource\\決定、ボタン押下9.mp3");
	bool key_sound_flag = false;

	int result_sound = LoadSoundMem("resource\\決定、ボタン押下4.mp3");

	// ゲームループで使う変数の宣言
	int* mapchip = (int*)title;

	player ball;
	ball.PlayerInit(64, 700, 16);

	float time_move = 0.0f;

	int spead = 10;

	int old_ball_posx;
	int old_ball_posy;

	bool isjump = false;
	int jump_spead = 5;

	int jump_chrge = 0;

	int vec_spead_x = 0;

	int vec_spead_y = 0;

	bool motion_chenge = false;

	int chenge_timer = 50;
	int motion_timer = 5;

	int eye_move = 0;

	bool stay_motion2 = false;

	bool stay_motion = false;

	float text_move = 0.0f;
	bool text_re = false;

	int timer = 0;

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//
		// 更新処理

		VECTOR MoveV = VGet(0, 0, 0);

		old_ball_posx = ball.x;
		old_ball_posy = ball.y;

		if (!text_re)
		{
			text_move += 0.3f;
			if (text_move > 9.9f)
			{
				text_re = true;
			}
		}
		if (text_re)
		{
			text_move -= 0.3f;
			if (text_move <= 0.0f)
			{
				text_re = false;
			}
		}

		if (!motion_chenge)
		{
			motion_timer = 5;
			chenge_timer--;
			if (chenge_timer < 0)
			{
				motion_chenge = true;
			}
		}
		if (motion_chenge)
		{
			chenge_timer = 50;
			motion_timer--;
			if (motion_timer < 0)
			{
				motion_chenge = false;
			}
		}

		if (!stay_motion && !isjump)
		{
			stay_motion = true;
		}
		if (stay_motion)
		{
			if (!stay_motion2)
			{
				time_move += 0.1f;
				if (time_move > 5.0f)
				{
					stay_motion2 = true;
				}
			}
			if (stay_motion2)
			{
				time_move -= 0.1f;
				if (time_move <= 0.0f)
				{
					stay_motion2 = false;
				}
			}
		}
		//トラップ当たり判定
		if (ball.Trap(vec_spead_x, vec_spead_y, old_ball_posx, old_ball_posy, block_size, mapCountx, mapCountY, mapchip)
			|| ball.Trap_top(vec_spead_x, vec_spead_y, old_ball_posx, old_ball_posy, block_size, mapCountx, mapCountY, mapchip))
		{
			trap_flag = true;
			key_sound_flag = false;
		}
		else
		{
			trap_flag = false;
		}

		//鍵
		if (ball.Exit_key(vec_spead_x, vec_spead_y, old_ball_posx, old_ball_posy, block_size, mapCountx, mapCountY, mapchip))
		{
			key_flag = true;
			key_sound_flag = true;
		}

		//タイトル画面のスタート処理
		if (title_flag && keys[KEY_INPUT_RETURN] && obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (9 - 1) * block_size, (16 - 1) * block_size, (18 - 1) * block_size, (19 - 1) * block_size))
		{
			stage_select_flag = true;
			title_flag = false;
			mapchip = (int*)stage_select;
		}
		//ステージselectでの各画面への処理
		if (stage_select_flag)
		{
			timer = 0;
			key_flag = false;
			if (keys[KEY_INPUT_RETURN])
			{
				//タイトル画面へ
				if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (11 - 1) * block_size, (23 - 1) * block_size, (16 - 1) * block_size, (25 - 1) * block_size))
				{
					stage_select_flag = false;
					title_flag = true;
					mapchip = (int*)title;
				}
				//1
				if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (2 - 1) * block_size, (22 - 1) * block_size, (5 - 1) * block_size, (25 - 1) * block_size))
				{
					stage_select_flag = false;
					stage1_flag = true;
					mapchip = (int*)stage1;
				}
				//2
				if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (2 - 1) * block_size, (17 - 1) * block_size, (5 - 1) * block_size, (20 - 1) * block_size))
				{
					stage_select_flag = false;
					stage2_flag = true;
					mapchip = (int*)stage2;
				}
				//3
				if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (22 - 1) * block_size, (22 - 1) * block_size, (25 - 1) * block_size, (25 - 1) * block_size))
				{
					stage_select_flag = false;
					stage3_flag = true;
					mapchip = (int*)stage3;
				}
				//4
				if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (22 - 1) * block_size, (17 - 1) * block_size, (25 - 1) * block_size, (20 - 1) * block_size))
				{
					stage_select_flag = false;
					stage4_flag = true;
					mapchip = (int*)stage4;
				}
				//5
				if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (2 - 1) * block_size, (9 - 1) * block_size, (5 - 1) * block_size, (12 - 1) * block_size))
				{
					stage_select_flag = false;
					stage5_flag = true;
					mapchip = (int*)stage5;
				}
				//6
				if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (22 - 1) * block_size, (9 - 1) * block_size, (25 - 1) * block_size, (12 - 1) * block_size))
				{
					stage_select_flag = false;
					stage6_flag = true;
					mapchip = (int*)stage6;
				}
				//7
				if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (2 - 1) * block_size, (2 - 1) * block_size, (5 - 1) * block_size, (5 - 1) * block_size))
				{
					stage_select_flag = false;
					stage7_flag = true;
					mapchip = (int*)stage7;
				}
				//8
				if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (22 - 1) * block_size, (2 - 1) * block_size, (25 - 1) * block_size, (5 - 1) * block_size))
				{
					stage_select_flag = false;
					stage8_flag = true;
					mapchip = (int*)stage8;
				}


			}
		}
		if (stage1_flag)
		{
			timer++;
			if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (2 - 1) * block_size, (2 - 1) * block_size, (5 - 1) * block_size, (5 - 1) * block_size))
			{
				result_flag = true;
				stage1_clear_flag = true;
				stage1_flag = false;
				mapchip = (int*)result;
				ball.x = 400;
				ball.y = 500;
				PlaySoundMem(result_sound, DX_PLAYTYPE_BACK, true);
			}
			if (keys[KEY_INPUT_B] == 1)
			{
				stage1_flag = false;
				stage_select_flag = true;
				mapchip = (int*)stage_select;
				ball.x = 400;
				ball.y = 500;
			}
		}
		if (stage2_flag)
		{
			timer++;
			if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (2 - 1) * block_size, (2 - 1) * block_size, (5 - 1) * block_size, (5 - 1) * block_size))
			{
				result_flag = true;
				stage2_clear_flag = true;
				stage2_flag = false;
				mapchip = (int*)result;
				ball.x = 400;
				ball.y = 500;
				PlaySoundMem(result_sound, DX_PLAYTYPE_BACK, true);
			}
			if (trap_flag)
			{
				ball.x = 64;
				ball.y = 500;
			}
			if (keys[KEY_INPUT_B] == 1)
			{
				stage2_flag = false;
				stage_select_flag = true;
				mapchip = (int*)stage_select;
				ball.x = 400;
				ball.y = 500;
			}
		}
		if (stage3_flag)
		{
			timer++;
			if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (2 - 1) * block_size, (22 - 1) * block_size, (5 - 1) * block_size, (25 - 1) * block_size))
			{
				result_flag = true;
				stage3_clear_flag = true;
				stage3_flag = false;
				mapchip = (int*)result;
				ball.x = 400;
				ball.y = 500;
				PlaySoundMem(result_sound, DX_PLAYTYPE_BACK, true);
			}
			if (trap_flag)
			{
				ball.x = 700;
				ball.y = 700;
			}
			if (keys[KEY_INPUT_B] == 1)
			{
				stage3_flag = false;
				stage_select_flag = true;
				mapchip = (int*)stage_select;
				ball.x = 400;
				ball.y = 500;
			}
		}
		if (stage4_flag)
		{
			timer++;
			if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (7 - 1) * block_size, (3 - 1) * block_size, (10 - 1) * block_size, (6 - 1) * block_size))
			{
				result_flag = true;
				stage4_clear_flag = true;
				stage4_flag = false;
				mapchip = (int*)result;
				ball.x = 400;
				ball.y = 500;
				PlaySoundMem(result_sound, DX_PLAYTYPE_BACK, true);
			}
			if (trap_flag)
			{
				ball.x = 700;
				ball.y = 520;
			}
			if (keys[KEY_INPUT_B] == 1)
			{
				stage4_flag = false;
				stage_select_flag = true;
				mapchip = (int*)stage_select;
				ball.x = 400;
				ball.y = 500;
			}
		}
		if (stage5_flag)
		{
			timer++;
			if (key_flag)
			{
				if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (2 - 1) * block_size, (22 - 1) * block_size, (5 - 1) * block_size, (25 - 1) * block_size))
				{
					result_flag = true;
					stage5_clear_flag = true;
					stage5_flag = false;
					mapchip = (int*)result;
					ball.x = 400;
					ball.y = 500;
					PlaySoundMem(result_sound, DX_PLAYTYPE_BACK, true);
				}
			}
			if (trap_flag)
			{
				key_flag = false;
				ball.x = 64;
				ball.y = 320;
			}
			if (keys[KEY_INPUT_B] == 1)
			{
				stage5_flag = false;
				stage_select_flag = true;
				mapchip = (int*)stage_select;
				ball.x = 400;
				ball.y = 500;
			}
		}
		if (stage6_flag)
		{
			timer++;
			if (key_flag)
			{
				if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (22 - 1) * block_size, (9 - 1) * block_size, (25 - 1) * block_size, (12 - 1) * block_size))
				{
					result_flag = true;
					stage6_clear_flag = true;
					stage6_flag = false;
					mapchip = (int*)result;
					ball.x = 400;
					ball.y = 500;
					PlaySoundMem(result_sound, DX_PLAYTYPE_BACK, true);
				}
			}
			if (trap_flag)
			{
				key_flag = false;
				ball.x = 700;
				ball.y = 320;
			}
			if (keys[KEY_INPUT_B] == 1)
			{
				stage6_flag = false;
				stage_select_flag = true;
				mapchip = (int*)stage_select;
				ball.x = 400;
				ball.y = 500;
			}
		}
		if (stage7_flag)
		{
			timer++;
			if (key_flag)
			{
				if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (5 - 1) * block_size, (10 - 1) * block_size, (8 - 1) * block_size, (13 - 1) * block_size))
				{
					result_flag = true;
					stage7_clear_flag = true;
					stage7_flag = false;
					mapchip = (int*)result;
					ball.x = 400;
					ball.y = 500;
					PlaySoundMem(result_sound, DX_PLAYTYPE_BACK, true);
				}
			}
			if (trap_flag)
			{
				key_flag = false;
				ball.x = 100;
				ball.y = 40;
			}
			if (keys[KEY_INPUT_B] == 1)
			{
				stage7_flag = false;
				stage_select_flag = true;
				mapchip = (int*)stage_select;
				ball.x = 400;
				ball.y = 500;
			}
		}
		if (stage8_flag)
		{
			timer++;
			if (key_flag)
			{
				if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (21 - 1) * block_size, (15 - 1) * block_size, (24 - 1) * block_size, (18 - 1) * block_size))
				{
					result_flag = true;
					stage8_clear_flag = true;
					stage8_flag = false;
					mapchip = (int*)result;
					ball.x = 400;
					ball.y = 500;
					PlaySoundMem(result_sound, DX_PLAYTYPE_BACK, true);
				}
			}
			if (trap_flag)
			{
				key_flag = false;
				ball.x = 700;
				ball.y = 40;
			}
			if (keys[KEY_INPUT_B] == 1)
			{
				stage8_flag = false;
				stage_select_flag = true;
				mapchip = (int*)stage_select;
				ball.x = 400;
				ball.y = 500;
			}
		}
		if (keys[KEY_INPUT_RIGHT])
		{
			eye_move = 5;
		}
		else if (keys[KEY_INPUT_LEFT])
		{
			eye_move = -5;
		}
		else
		{
			eye_move = 0;
		}

		if (result_flag)
		{
			timer = timer;
			if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (22 - 1) * block_size, (22 - 1) * block_size, (25 - 1) * block_size, (25 - 1) * block_size))
			{
				result_flag = false;
				stage_select_flag = true;
				mapchip = (int*)stage_select;
				ball.x = 400;
				ball.y = 500;
			}
		}



		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 1 && isjump == false)
		{
			motion_chenge = true;
			time_move = 10.0f;
			if (jump_chrge < 30)
			{
				jump_chrge += 1;
			}
		}

		if (keys[KEY_INPUT_SPACE] == 0 && oldkeys[KEY_INPUT_SPACE] == 1 && isjump == false)
		{

			motion_chenge = false;
			time_move = 0;
			isjump = true;
			jump_spead = jump_chrge;
			jump_chrge = 0;
		}


		MoveV = MoveInput(keys, isjump);


		//jump関係
		if (jump_spead > -25 && isjump)
		{
			jump_spead -= 1;
		}
		vec_spead_x = MoveV.x * spead;
		vec_spead_y = MoveV.y * jump_spead;

		ball.Move(vec_spead_x, vec_spead_y);

		ball.Col(vec_spead_x, vec_spead_y, old_ball_posx, old_ball_posy, block_size, mapCountx, mapCountY, mapchip);


		int jump_bottom = (ball.y + ball.r) / block_size;
		int jump_top = (ball.y - ball.r - 1) / block_size;
		int ball_left = (ball.x - ball.r) / block_size;
		int ball_right = (ball.x + ball.r - 1) / block_size;

		//各ステージのジャンプ
		if (title_flag)
		{
			//地面に当たった時ジャンプフラグfalse
			if (title[jump_bottom][ball_right] == 2 || title[jump_bottom][ball_left] == 2)
			{
				isjump = false;
				jump_spead = 5;

			}

			//頭落とし
			if (title[jump_top][ball_right] == 2 || title[jump_top][ball_left] == 2)
			{
				jump_spead = -jump_spead;
			}

			//自然落下&二段ジャンプ阻止
			if (title[jump_bottom][ball_right] == 0 && title[jump_bottom][ball_left] == 0 && !isjump)
			{
				isjump = true;
				jump_spead = -1;
			}
		}
		if (result_flag)
		{
			if (result[jump_bottom][ball_right] == 2 || result[jump_bottom][ball_left] == 2)
			{
				isjump = false;
				jump_spead = 5;

			}

			//頭落とし
			if (result[jump_top][ball_right] == 2 || result[jump_top][ball_left] == 2)
			{
				jump_spead = -jump_spead;
			}

			//自然落下&二段ジャンプ阻止
			if (result[jump_bottom][ball_right] == 0 && result[jump_bottom][ball_left] == 0 && !isjump)
			{
				isjump = true;
				jump_spead = -1;
			}
		}
		if (stage_select_flag)
		{
			//地面に当たった時ジャンプフラグfalse
			if (stage_select[jump_bottom][ball_right] == 2 || stage_select[jump_bottom][ball_left] == 2)
			{
				isjump = false;
				jump_spead = 5;

			}

			//頭落とし
			if (stage_select[jump_top][ball_right] == 2 || stage_select[jump_top][ball_left] == 2)
			{
				jump_spead = -jump_spead;
			}

			//自然落下&二段ジャンプ阻止
			if (stage_select[jump_bottom][ball_right] == 0 && stage_select[jump_bottom][ball_left] == 0 && !isjump)
			{
				isjump = true;
				jump_spead = -1;
			}
		}
		if (stage1_flag)
		{
			//地面に当たった時ジャンプフラグfalse
			if (stage1[jump_bottom][ball_right] == 2 || stage1[jump_bottom][ball_left] == 2)
			{
				isjump = false;
				jump_spead = 5;

			}

			//頭落とし
			if (stage1[jump_top][ball_right] == 2 || stage1[jump_top][ball_left] == 2)
			{
				jump_spead = -jump_spead;
			}

			//自然落下&二段ジャンプ阻止
			if (stage1[jump_bottom][ball_right] == 0 && stage1[jump_bottom][ball_left] == 0 && !isjump)
			{
				isjump = true;
				jump_spead = -1;
			}
		}
		if (stage2_flag)
		{
			//地面に当たった時ジャンプフラグfalse
			if (stage2[jump_bottom][ball_right] == 2 || stage2[jump_bottom][ball_left] == 2)
			{
				isjump = false;
				jump_spead = 5;

			}

			//頭落とし
			if (stage2[jump_top][ball_right] == 2 || stage2[jump_top][ball_left] == 2)
			{
				jump_spead = -jump_spead;
			}

			//自然落下&二段ジャンプ阻止
			if (stage2[jump_bottom][ball_right] == 0 && stage2[jump_bottom][ball_left] == 0 && !isjump)
			{
				isjump = true;
				jump_spead = -1;
			}
		}
		if (stage3_flag)
		{
			//地面に当たった時ジャンプフラグfalse
			if (stage3[jump_bottom][ball_right] == 2 || stage3[jump_bottom][ball_left] == 2)
			{
				isjump = false;
				jump_spead = 5;

			}

			//頭落とし
			if (stage3[jump_top][ball_right] == 2 || stage3[jump_top][ball_left] == 2)
			{
				jump_spead = -jump_spead;
			}

			//自然落下&二段ジャンプ阻止
			if (stage3[jump_bottom][ball_right] == 0 && stage3[jump_bottom][ball_left] == 0 && !isjump)
			{
				isjump = true;
				jump_spead = -1;
			}
		}
		if (stage4_flag)
		{
			//地面に当たった時ジャンプフラグfalse
			if (stage4[jump_bottom][ball_right] == 2 || stage4[jump_bottom][ball_left] == 2)
			{
				isjump = false;
				jump_spead = 5;

			}

			//頭落とし
			if (stage4[jump_top][ball_right] == 2 || stage4[jump_top][ball_left] == 2)
			{
				jump_spead = -jump_spead;
			}

			//自然落下&二段ジャンプ阻止
			if (stage4[jump_bottom][ball_right] == 0 && stage4[jump_bottom][ball_left] == 0 && !isjump)
			{
				isjump = true;
				jump_spead = -1;
			}
		}
		if (stage5_flag)
		{
			//地面に当たった時ジャンプフラグfalse
			if (stage5[jump_bottom][ball_right] == 2 || stage5[jump_bottom][ball_left] == 2)
			{
				isjump = false;
				jump_spead = 5;

			}

			//頭落とし
			if (stage5[jump_top][ball_right] == 2 || stage5[jump_top][ball_left] == 2)
			{
				jump_spead = -jump_spead;
			}

			//自然落下&二段ジャンプ阻止
			if (stage5[jump_bottom][ball_right] == 0 && stage5[jump_bottom][ball_left] == 0 && !isjump)
			{
				isjump = true;
				jump_spead = -1;
			}
		}
		if (stage6_flag)
		{
			//地面に当たった時ジャンプフラグfalse
			if (stage6[jump_bottom][ball_right] == 2 || stage6[jump_bottom][ball_left] == 2)
			{
				isjump = false;
				jump_spead = 5;

			}

			//頭落とし
			if (stage6[jump_top][ball_right] == 2 || stage6[jump_top][ball_left] == 2)
			{
				jump_spead = -jump_spead;
			}

			//自然落下&二段ジャンプ阻止
			if (stage6[jump_bottom][ball_right] == 0 && stage6[jump_bottom][ball_left] == 0 && !isjump)
			{
				isjump = true;
				jump_spead = -1;
			}
		}
		if (stage7_flag)
		{
			//地面に当たった時ジャンプフラグfalse
			if (stage7[jump_bottom][ball_right] == 2 || stage7[jump_bottom][ball_left] == 2)
			{
				isjump = false;
				jump_spead = 5;

			}

			//頭落とし
			if (stage7[jump_top][ball_right] == 2 || stage7[jump_top][ball_left] == 2)
			{
				jump_spead = -jump_spead;
			}

			//自然落下&二段ジャンプ阻止
			if (stage7[jump_bottom][ball_right] == 0 && stage7[jump_bottom][ball_left] == 0 && !isjump)
			{
				isjump = true;
				jump_spead = -1;
			}
		}
		if (stage8_flag)
		{
			//地面に当たった時ジャンプフラグfalse
			if (stage8[jump_bottom][ball_right] == 2 || stage8[jump_bottom][ball_left] == 2)
			{
				isjump = false;
				jump_spead = 5;

			}

			//頭落とし
			if (stage8[jump_top][ball_right] == 2 || stage8[jump_top][ball_left] == 2)
			{
				jump_spead = -jump_spead;
			}

			//自然落下&二段ジャンプ阻止
			if (stage8[jump_bottom][ball_right] == 0 && stage8[jump_bottom][ball_left] == 0 && !isjump)
			{
				isjump = true;
				jump_spead = -1;
			}
		}
		// 描画処理

		PlaySoundMem(mainBgm, DX_PLAYTYPE_LOOP, false);
		if (keys[KEY_INPUT_SPACE] == 0 && oldkeys[KEY_INPUT_SPACE] == 1)
		{
			if (CheckSoundMem(jump_sound) == 0)
			{
				PlaySoundMem(jump_sound, DX_PLAYTYPE_BACK, true);
			}
		}
		if (!key_sound_flag)
		{
			PlaySoundMem(key_sound, DX_PLAYTYPE_BACK, true);
		}

		if (trap_flag)
		{
			PlaySoundMem(dead, DX_PLAYTYPE_BACK, true);
		}

		if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
		{
			if (title_flag || stage_select_flag)
			{
				PlaySoundMem(kettei, DX_PLAYTYPE_BACK, true);
			}
		}


		// 各ステージの描画

		//タイトル
		if (title_flag)
		{
			DrawGraph(0, 0, haikei, true);
			DrawGraph((2 - 1) * block_size, (3 - 1) * block_size + text_move, title_name, true);
			DrawGraph((9 - 1) * block_size, (16 - 1) * block_size, start_button, true);
			if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (9 - 1) * block_size, (16 - 1) * block_size, (18 - 1) * block_size, (19 - 1) * block_size))
			{
				DrawGraph((9 - 1) * block_size, (16 - 1) * block_size, start2_button, true);
			}
			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{

					if (title[y][x] == obj)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, block3, true);
					}
				}
			}
		}

		if (result_flag)
		{

			DrawGraph(7 * block_size, 6 * block_size + text_move, stage_text, true);
			DrawGraph((22 - 1) * block_size, (22 - 1) * block_size, exit, true);
			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{

					if (result[y][x] == obj)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, block3, true);
					}
				}
			}
			for (int z = 0; z < 5; z++)
			{
				DrawGraph((8 + z + z) * block_size, 8 * block_size + text_move, clear_text[z], true);

			}
			DrawGraph(8 * block_size, 11 * block_size, time_text, true);
			DrawGraph(8 * block_size, 12 * block_size, timer_text[timer / 5500], true);
			DrawGraph(10 * block_size, 12 * block_size, timer_text[timer % 5500 / 550], true);
			DrawGraph(12 * block_size, 12 * block_size, timer_text[timer % 550 / 55], true);
			DrawCircle(14 * block_size, 14 * block_size, 3, GetColor(255, 255, 0), true);
			DrawGraph(14 * block_size, 13 * block_size, timer_text_small[timer % 55 / 5], true);
			DrawGraph(15 * block_size, 12 * block_size, second, true);


		}
		//ステージselect
		if (stage_select_flag)
		{
			DrawGraph((11 - 1) * block_size, (23 - 1) * block_size, title_menu, true);
			if (obj_hit(ball.x - ball.r, ball.y - ball.r, ball.x + ball.r, ball.y + ball.r, (11 - 1) * block_size, (23 - 1) * block_size, (16 - 1) * block_size, (25 - 1) * block_size))
			{
				DrawGraph((11 - 1) * block_size, (23 - 1) * block_size, title_menu2, true);
			}
			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{
					if (stage_select[y][x] == obj)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, block3, true);
					}
				}
			}
			DrawGraph((2 - 1) * block_size, (22 - 1) * block_size, select_door, true);
			DrawGraph(1 * block_size, 22 * block_size, select_num[0], true);
			if (stage1_clear_flag)
			{
				DrawGraph(1 * block_size, 22 * block_size, select2_num[0], true);
			}

			DrawGraph((2 - 1) * block_size, (17 - 1) * block_size, select_door, true);
			DrawGraph(1 * block_size, 17 * block_size, select_num[1], true);
			if (stage2_clear_flag)
			{
				DrawGraph(1 * block_size, 17 * block_size, select2_num[1], true);
			}

			DrawGraph((22 - 1) * block_size, (22 - 1) * block_size, select_door, true);
			DrawGraph(21 * block_size, 22 * block_size, select_num[2], true);
			if (stage3_clear_flag)
			{
				DrawGraph(21 * block_size, 22 * block_size, select2_num[2], true);
			}

			DrawGraph((22 - 1) * block_size, (17 - 1) * block_size, select_door, true);
			DrawGraph(21 * block_size, 17 * block_size, select_num[3], true);
			if (stage4_clear_flag)
			{
				DrawGraph(21 * block_size, 17 * block_size, select2_num[3], true);
			}

			DrawGraph((2 - 1) * block_size, (9 - 1) * block_size, select_door, true);
			DrawGraph(1 * block_size, 9 * block_size, select_num[4], true);
			if (stage5_clear_flag)
			{
				DrawGraph(1 * block_size, 9 * block_size, select2_num[4], true);
			}

			DrawGraph((22 - 1) * block_size, (9 - 1) * block_size, select_door, true);
			DrawGraph(21 * block_size, 9 * block_size, select_num[5], true);
			if (stage6_clear_flag)
			{
				DrawGraph(21 * block_size, 9 * block_size, select2_num[5], true);
			}

			DrawGraph((2 - 1) * block_size, (2 - 1) * block_size, select_door, true);
			DrawGraph(1 * block_size, 2 * block_size, select_num[6], true);
			if (stage7_clear_flag)
			{
				DrawGraph(1 * block_size, 2 * block_size, select2_num[6], true);
			}

			DrawGraph((22 - 1) * block_size, (2 - 1) * block_size, select_door, true);
			DrawGraph(21 * block_size, 2 * block_size, select_num[7], true);
			if (stage8_clear_flag)
			{
				DrawGraph(21 * block_size, 2 * block_size, select2_num[7], true);
			}
		}
		if (stage1_flag)
		{
			DrawGraph((2 - 1) * block_size, (2 - 1) * block_size, exit, true);
			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{
					if (stage1[y][x] == obj)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, block3, true);
					}
				}
			}
		}
		if (stage2_flag)
		{
			DrawGraph((2 - 1) * block_size, (2 - 1) * block_size, exit, true);
			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{
					if (stage2[y][x] == trap_top)
					{
						DrawExtendGraph(x * block_size, y * block_size + block_size, x * block_size + block_size, y * block_size, trap_gra, true);
					}
					if (stage2[y][x] == obj)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, block3, true);
					}
					if (stage2[y][x] == trap)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, trap_gra, true);
					}
				}
			}
		}
		if (stage3_flag)
		{
			DrawGraph((2 - 1) * block_size, (22 - 1) * block_size, exit, true);
			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{
					if (stage3[y][x] == trap_top)
					{
						DrawExtendGraph(x * block_size, y * block_size + block_size, x * block_size + block_size, y * block_size, trap_gra, true);
					}
					if (stage3[y][x] == obj)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, block3, true);
					}
					if (stage3[y][x] == trap)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, trap_gra, true);
					}
				}
			}
		}
		if (stage4_flag)
		{
			DrawGraph((7 - 1) * block_size, (3 - 1) * block_size, exit, true);
			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{
					if (stage4[y][x] == trap_top)
					{
						DrawExtendGraph(x * block_size, y * block_size + block_size, x * block_size + block_size, y * block_size, trap_gra, true);
					}
					if (stage4[y][x] == obj)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, block3, true);
					}
					if (stage4[y][x] == trap)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, trap_gra, true);
					}
				}
			}
		}
		if (stage5_flag)
		{
			if (key_flag)
			{
				DrawGraph((2 - 1) * block_size, (22 - 1) * block_size, exit, true);
			}
			else
			{
				DrawGraph((2 - 1) * block_size, (22 - 1) * block_size, lock_exit, true);
			}
			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{
					if (stage5[y][x] == exitkey && !key_flag)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, key_gra, true);
					}
					if (stage5[y][x] == trap_top)
					{
						DrawExtendGraph(x * block_size, y * block_size + block_size, x * block_size + block_size, y * block_size, trap_gra, true);
					}
					if (stage5[y][x] == obj)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, block3, true);
					}
					if (stage5[y][x] == trap)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, trap_gra, true);
					}
				}
			}
		}
		if (stage6_flag)
		{
			if (key_flag)
			{
				DrawGraph((22 - 1) * block_size, (9 - 1) * block_size, exit, true);
			}
			else
			{
				DrawGraph((22 - 1) * block_size, (9 - 1) * block_size, lock_exit, true);
			}
			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{
					if (stage6[y][x] == exitkey && !key_flag)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, key_gra, true);
					}
					if (stage6[y][x] == trap_top)
					{
						DrawExtendGraph(x * block_size, y * block_size + block_size, x * block_size + block_size, y * block_size, trap_gra, true);
					}
					if (stage6[y][x] == obj)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, block3, true);
					}
					if (stage6[y][x] == trap)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, trap_gra, true);
					}
				}
			}
		}
		if (stage7_flag)
		{
			if (key_flag)
			{
				DrawGraph((5 - 1) * block_size, (10 - 1) * block_size, exit, true);
			}
			else
			{
				DrawGraph((5 - 1) * block_size, (10 - 1) * block_size, lock_exit, true);
			}
			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{
					if (stage7[y][x] == exitkey && !key_flag)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, key_gra, true);
					}
					if (stage7[y][x] == trap_top)
					{
						DrawExtendGraph(x * block_size, y * block_size + block_size, x * block_size + block_size, y * block_size, trap_gra, true);
					}
					if (stage7[y][x] == obj)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, block3, true);
					}
					if (stage7[y][x] == trap)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, trap_gra, true);
					}
				}
			}
		}
		if (stage8_flag)
		{
			if (key_flag)
			{
				DrawGraph((21 - 1) * block_size, (15 - 1) * block_size, exit, true);
			}
			else
			{
				DrawGraph((21 - 1) * block_size, (15 - 1) * block_size, lock_exit, true);
			}
			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{
					if (stage8[y][x] == exitkey && !key_flag)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, key_gra, true);
					}
					if (stage8[y][x] == trap_top)
					{
						DrawExtendGraph(x * block_size, y * block_size + block_size, x * block_size + block_size, y * block_size, trap_gra, true);
					}
					if (stage8[y][x] == obj)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, block3, true);
					}
					if (stage8[y][x] == trap)
					{
						DrawExtendGraph(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, trap_gra, true);
					}
				}
			}
		}
		DrawExtendGraph(ball.x - ball.r, ball.y - ball.r + time_move, ball.x + ball.r, ball.y + ball.r, player_gra, true);
		if (!motion_chenge)
		{
			DrawExtendGraph(ball.x - ball.r + eye_move, ball.y - ball.r + time_move, ball.x + ball.r + eye_move, ball.y + ball.r, player_eye_gra[0], true);
		}
		if (motion_chenge)
		{
			DrawExtendGraph(ball.x - ball.r + eye_move, ball.y - ball.r + time_move, ball.x + ball.r + eye_move, ball.y + ball.r, player_eye_gra[1], true);
		}

		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 1 && isjump == false)
		{
			DrawBox(ball.x - ball.r, ball.y - ball.r - 24, ball.x - ball.r + jump_chrge, ball.y - ball.r - 12, GetColor(0, 255, 0), true);
		}
		if (!title_flag && !stage_select_flag && !result_flag)
		{
			DrawGraph(10 * block_size, 24 * block_size, retire, true);
		}

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	DeleteGraph(block3);
	DeleteGraph(player_gra);
	for (int i = 0; i < 10; i++)
	{

		if (i < 2)
		{
			DeleteGraph(player_eye_gra[i]);
		}
		if (i < 5)
		{
			DeleteGraph(clear_text[i]);
		}
		if (i < 8)
		{
			DeleteGraph(select_num[i]);
			DeleteGraph(select2_num[i]);
		}
		DeleteGraph(timer_text[i]);
		DeleteGraph(timer_text_small[i]);
	}
	DeleteGraph(trap_gra);
	DeleteGraph(exit);
	DeleteGraph(lock_exit);
	DeleteGraph(title_name);
	DeleteGraph(key_gra);
	DeleteGraph(start_button);
	DeleteGraph(start2_button);
	DeleteGraph(title_menu);
	DeleteGraph(title_menu2);
	DeleteGraph(stage_text);
	DeleteGraph(time_text);
	DeleteGraph(second);
	DeleteGraph(haikei);
	DeleteGraph(retire);

	InitSoundMem();

	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
VECTOR MoveInput(char keys[256], bool jump)
{
	VECTOR vec = VGet(0, 0, 0);


	if (jump)
	{
		if (keys[KEY_INPUT_RIGHT])
		{
			vec.x += 1;
		}
		if (keys[KEY_INPUT_LEFT])
		{
			vec.x += -1;
		}
		vec.y += -1;
	}
	if (!jump)
	{
		vec.y += 1;
	}
	if (vec.x != 0 && vec.y != 0)
	{
		vec = VNorm(vec);
	}
	return vec;
}

bool obj_hit(int left_ax, int up_ay, int right_ax, int down_ay, int left_bx, int up_by, int right_bx, int down_by)
{
	if (left_ax < right_bx && left_bx < right_ax && up_ay < down_by && up_by < down_ay)
	{

		return 1;

	}
	else
	{
		return 0;
	}
}