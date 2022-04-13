#include "DxLib.h"
#include "stdlib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LC1A_19_ニッタシンジ: JUMP×JUMP";

// ウィンドウ横幅
const int WIN_WIDTH = 800;

// ウィンドウ縦幅
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
			return  0.7; //斜めの係数
		}
		else
		{
			 return  1.0; //斜めじゃなければそのまま
		}
	}
	else if (CheckHitKey(KEY_INPUT_UP)== 1 || CheckHitKey(KEY_INPUT_DOWN)== 1)
	{
		return  1.0; //斜めじゃなければそのまま
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

//線の描画
void Draw_line(int scroll_line_x, int scroll_line_y, int scroll_line_w,int scroll_line_h, unsigned int word_color);

//背景の描画
void Draw_background(int number_handle[], float scroll_y, float monitor_x);

//monitor座標の計算
float monitor_x_calculation(float world_x, float scroll_x);

float monitor_y_calculation(float world_y, float scroll_y);

//スクロールが開始されているかどうかを判断するフラグ
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

//線の構造体
typedef struct line {
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	unsigned int color;
};

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
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み

	//背景画像の読み込み
	int back_ground_number_handle[] = { 0,1,2,3 };

	back_ground_number_handle[0] = LoadGraph("summer_game_background1.png");

	back_ground_number_handle[1] = LoadGraph("summer_game_background2.png");

	back_ground_number_handle[2] = LoadGraph("summer_game_background3.png");

	back_ground_number_handle[3] = LoadGraph("summer_game_background4.png");

	//タイトル画像の読み込み
	int title_handle = 0;
	title_handle = LoadGraph("summer_game_title1.png");

	//数字の画像の読み込み
	int number_handle = 0;
	number_handle = LoadGraph("game_summer_number.png");

	//円の下部分は端から42マス
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

	//音楽の変数

	int op_bgm_handle = LoadSoundMem("op_bgm.mp3");
	ChangeVolumeSoundMem(100, op_bgm_handle);

	int play_bgm_handle = LoadSoundMem("play_bgm.mp3");
	ChangeVolumeSoundMem(80, play_bgm_handle);

	int button_handle = LoadSoundMem("button.mp3");
	ChangeVolumeSoundMem(128, button_handle);

	int two_jump_handle = LoadSoundMem("jump_2.mp3");
	ChangeVolumeSoundMem(128,two_jump_handle);

	// ゲームループで使う変数の宣言

	//自機の基礎設定
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

	//playerの追加情報
	float player_left_side = 0; //(左前脚)
	float player_right_side = 0;
	float player_top_side = 0;
	float player_down_side = 0;
	
	 float diagonal_num = 1.0f; //自機移動の斜め係数

	//各シーン用の変数
	int scene = 0;

	//シーン用の待ちタイマー
	int scene_timer = 10;

	//タイトル画面用の変数

	int space_anime_time = 0;
	int space_anime_time_flag = 0;

	//ジャンプ用の変数
	bool jump_flag = 0;
	bool jump_flag_twice = 0;
	float jump_speed_timer = 11.0f;
	float gravity_speed = 9.8f;
	int jump_count = 0; //ジャンプ数を数えて、回数を制限する用の変数
	int jump_count_timer = 0;
	bool jump_count_flag = 0;

	//待機時のアニメーション用変数

	float wait_anime_timer = 7.0f;
	bool loop_up_flag = 0;
	bool loop_down_flag = 0;

	//ステージ選択用の変数

	bool first_stage_flag = 1;
	bool second_stage_flag = 0;
	//移動時の待ちタイマー
	int stage_wait_timer = 15;
	//移動させる時の保存用変数
	float save_stage_info_pos_x = 0.0f;
	float save_stage_info_pos_y = 0.0f;

	//スクロール用の変数

	//ワールド座標
	float world_x = player.pos_x;
	float world_y = player.pos_y;
	//モニター座標
	float monitor_x = 0.0f;
	float monitor_y = 0.0f;
	//スクロール値
	float scroll_x = 0.0f;
	float scroll_y = 0.0f;

	//スクロール開始位置の線の座標
	line scroll_line = {
		0,
		350,
		800,
		350,
		GetColor(255,0,0)
	};

	//スクロールがされているかどうかのフラグ
	bool is_scrollflag = 0;

	//ステージの土台用の変数
	float base_x[10] = { 85,340,272,400,150,456,289,543,653,440};
	float base_y[10] = { 300,530,100,0,400,-300,-450,-670,-900,-1200};
	float base_r = 32;

	//プレイヤーと土台が触れた時のフラグ

	bool base_confrict_flag[10] = { 0,1,0,0,0,0,0,0,0,0};

	//ゲームプレイ後の選択ボタン

	int select_button_x = 150;
	int select_button_y = 285;

	//ゲームオーバー画面の変数

	int continue_anime_timer = 30;
	int continue_anime_flag = 0;

	//ゲームクリア画面の変数

	int game_clear_anime_timer = 10;

	//ローディング画面用の変数

	int Lording_timer = 270;


	// 最新のキーボード情報用
	char keys[256] = {0};

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = {0};

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

		//各シーンの設定
		if (scene == 0)//タイトル画面
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

		//ステージ選択画面
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

			//ステージ選択画面で自機を固定させたまま跳ねさせる処理
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
			//ステージを選択させるときに、各ステージの位置を交換させる処理
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

		//プレイヤーの動き
		if (scene == 3 || scene == 4)//プレイ画面でのプレイヤーの動き
		{
			if (scene == 4)
			{
				//scene4 で4個目が二段目で超えようとすると受けつけなくなる

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

			//モニター座標の計算
			monitor_y = monitor_y_calculation(world_y, scroll_y);

			if (world_y < 400 && world_y > -1600 && scroll_line.y >= player.pos_y)
			{
				is_scrollflag = ON;
			}

			//スクロールが開始された場合の処理
			if (is_scrollflag == ON)
			{
				if (world_y < 400 && world_y > -1600  && jump_flag == 1)
				{
					scroll_y += player.speed * jump_speed_timer + 5;
					//ワールド座標のY軸をプレイヤーの移動に合わせる
				}

				//画面外に行かないよう範囲をつける
				if (scroll_y >= 1600)//スクロール値が1600になったら固定
				{
					scroll_y = 1600;
					//is_scrollflag = OFF;
				}
				if (player.pos_y > scroll_line.y)//スクロールしない場面(一番下のステージに戻った場合にスクロール値をリセット)
				{
					is_scrollflag = OFF;
					//scroll_y = 0;
				}
			}

			//斜め移動係数
			diagonal_num = diagonal_num_sum();

			//ジャンプの動きにゲームプレイ画面での土台の上に乗る判定を加える
			player_left_side = player.pos_x + 25;
			player_right_side = player.pos_x + 40;
			player_top_side = player.pos_y ;
			player_down_side = player.pos_y + 34;


			//左右の移動処理
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

			//ジャンプの仕組み
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

				if (base_x[i] - 10 <= player_left_side && base_x[i] + 74 >= player_right_side) //各両辺に5pixcel分余裕を持たせる
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

					//何もしていない時に土台から落ちない処理
					if (base_confrict_flag[i] == 1)
					{
						world_y = base_y[i] + scroll_y -78;
						player.pos_y = base_y[i] + scroll_y -78;
					}
				}
				//何ものっかっていない時にプレイヤーが落下する仕組み

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

				//土台からずれた時に当たっているフラグを0にする。
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
			//選択ボタンのアニメーション
			if (continue_anime_flag == 1)
			{
				continue_anime_timer--;

				if (continue_anime_timer <= 0)
				{
					continue_anime_timer = 30;
				}
			}

			//選択ボタンの変数設定
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
			//ステージ選択画面で自機を固定させたまま跳ねさせる処理
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

		//各変数のリセット
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

		// 描画処理
		switch (scene)
		{
			//タイトル
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

	//画像の後処理
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

	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}

//モニター座標の計算
float monitor_x_calculation(float world_x, float scroll_x)
{
	return world_x - scroll_x;
}
float monitor_y_calculation(float world_y, float scroll_y)
{
	return world_y - scroll_y;
}
//スクロールが開始されるための条件
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
//各線の描画
void Draw_line(int scroll_line_x, int  scroll_line_y, int scroll_line_w,int scroll_line_h, unsigned word_color) 
{
	//scroll開始位置の線
	DrawLine(scroll_line_x, scroll_line_y, scroll_line_w, scroll_line_h, word_color);
}
//背景の描画
void Draw_background(int number_handle[], float scroll_y, float monitor_x)
{
	DrawGraph(monitor_x, 0 - scroll_y, number_handle[0], true);
	DrawGraph(monitor_x, 800 - scroll_y, number_handle[1], true);
	DrawGraph(monitor_x, 1600 - scroll_y, number_handle[2], true);

}