#include "DxLib.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "学籍番号 名前:LC1A_10_カミサトマサトシ";

// ウィンドウ横幅
const int WIN_WIDTH = 600;

// ウィンドウ縦幅
const int WIN_HEIGHT = 900;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
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
	SetBackgroundColor(0x00, 0x00, 0xFF);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	// 
	// 音楽や効果音
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




	//																アニメーション一枚のサイズ
	//LoadDivGraph("player.png", 総合分割数, 横の分割数, 縦の分割数, 横のサイズ, 縦サイズ, 入れる変数);
	// 画面情報
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

	//プレイヤーの画像
	int player[4];
	LoadDivGraph("picture/player.png", 4, 4, 1, 32, 32, player);//止まっているとき
	int playermove[8];
	LoadDivGraph("picture/playerRun1.png", 8, 8, 1, 32, 32, playermove);//動いているとき
	int shot[3];
	LoadDivGraph("picture/shot.png", 3, 3, 1, 16, 16, shot);//弾

	//敵の画像
	int enemy[2];
	LoadDivGraph("picture/enemy1.png", 2, 2, 1, 32, 32, enemy);
	int enemy_ko[2];
	LoadDivGraph("picture/enemy2.png", 2, 2, 1, 32, 32, enemy_ko);
	int boss_dawn_gif[7];
	LoadDivGraph("picture/bossdawn.png", 7, 7, 1, 128, 128, boss_dawn_gif);
	int enemy_shot = LoadGraph("picture/enemy_shot.png", true);


	//背景
	int backscreen = LoadGraph("picture/backscreen.png", true);
	int backscreen1 = LoadGraph("picture/backscreen.png", true);

	int screen_posy = 0;
	int screen_posy1 = 0;

	// ゲームループで使う変数の宣言
	//画面情報
	int score = 0;				//スコア
	int shot_upgrade = 10000;			//弾のアップグレード
	int enemy_upgrade = 3000;				//敵のアップグレード
	int scene = 0;				//画面切り替え。
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

	//プレイヤー情報
	double player_posx = 300;				//ｘ座標
	double player_posy = 800;				//ｙ座標
	double player_speed = 8;				//プレイヤーの速さ
	double player_size = 20;				//プレイヤーの大きさ
	int player_flag = 1;				//プレイヤーのフラッグ
	int player_gif_time = 0;
	int p = 0;
	int p_time = 30;
	double player_move = 0;
	int mv = 0;

	//弾の情報
	int shot_bullte_posx[256] = { 0 };	//弾のX座標
	int shot_bullte_posy[256] = { 0 };	//弾のY座標
	int shot_flag[256] = { 0 };	//弾の認識変数。
	int shot_speed = 6;		//弾の速度
	int shot_size = 3;		//弾の直径
	int shot_time = 1;		//弾の間隔
	int shot_number = 1;		//弾の最大数
	int shot_damage = 1;		//ダメージ
	int s = 0;
	int damage_flag = 0;
	int damage_flag2 = 0;

	//敵の情報
	double enemy_posx[256] = { 0 };		//円のX座標
	double enemy_posy[256] = { 0 };		//円のY座標
	double enemy_flag[256] = { 0 };		//敵のフラッグ情報
	int enemy_respown[256] = { 0 };		//復活タイマー
	int enemy_x_speed = 0;			//円の速さ。X座標
	int enemy_y_speed = 1;			//円の速さ。Y座標
	double enemy_size = 15;			//敵の直径
	int enemy_number = 5;				//敵の上限設定
	int e = 0;
	int e_ko = 0;
	int enemy_gif_time = 0;
	int boom_time[256] = { 0 };
	int enemy_ko_posx[256] = { 0 };
	int enemy_ko_posy[256] = { 0 };

	//敵の弾
	int enemy_shot_posx[256] = { 0 };
	int enemy_shot_posy[256] = { 0 };
	int enemy_shot_flag[256] = { 0 };
	int enemy_shot_speedx[256] = { 0 };
	int enemy_shot_speedy[256] = { 0 };
	int enemy_shot_counter = 0;



	//ボス情報
	int boss_main_posx = 350;				//ボスメイン機X
	int boss_main_posy = 5;				//ボスメイン機Y
	int boss_main_size = 64;				//サイズ
	int boss_main_hp = 1;				//HP
	int boss_sub1_posx = 200;				//ボスサブ１X
	int boss_sub1_posy = 10;				//ボスサブ１Y
	int boss_sub1_size = 32;				//サイズ
	int boss_sub1_hp = 30;				//HP
	int boss_sub2_posx = 400;				//ボスサブ２X
	int boss_sub2_posy = 10;				//ボスサブ２Y
	int boss_sub2_size = 32;				//サイズ
	int boss_sub2_hp = 30;				//HP
	int boss_main_flag = 0;				//ボスメインフラグ
	int boss_sub1_flag = 0;				//ボスサブ１フラグ
	int boss_sub2_flag = 0;				//ボスサブ２フラグ]
	int boss_speed0_posx = 0;				//ボス速さ
	int boss_speed1_posx = 0;				//	//
	int boss_speed2_posx = 0;				//	//
	int boss_speed0_posy = 0;				//	//
	int boss_speed1_posy = 0;				//	//
	int boss_speed2_posy = 0;				//	//
	int boss_speed0_change = 0;				//速さの変更。
	int boss_speed1_change = 3;				//速さの変化サブ１
	int boss_speed2_change = 3;				//速さの変化サブ２
	int bdg_time = 0;
	int bdg = 0;
	int stop_flag = 0;
	int start_boss_flag = 0;
	const int enemy_shot_redius = (shot_size + player_size) * (shot_size + player_size);

	//当たり判定情報
	const int radius = (enemy_size + shot_size) * (enemy_size + shot_size);//半径
	const int redius_main = (enemy_size + player_size) * (enemy_size + player_size);
	const int boss_main_redius = (boss_main_size + shot_size) * (boss_main_size + shot_size);
	const int boss_sub1_redius = (boss_sub1_size + shot_size) * (boss_sub1_size + shot_size);
	const int boss_sub2_redius = (boss_sub2_size + shot_size) * (boss_sub2_size + shot_size);
	const int boss_boss_player = (boss_main_size + player_size) * (boss_main_size + player_size);
	const int boss_sub1_player = (boss_sub1_size + player_size) * (boss_sub1_size + player_size);
	const int boss_sub2_player = (boss_sub2_size + player_size) * (boss_sub2_size + player_size);
	int difference_posx[256] = { 0 };			//xの差
	int difference_posy[256] = { 0 };			//yの差
	int difference_posx_main[256] = { 0 };		//xの本体差
	int difference_posy_main[256] = { 0 };		//yの本体差

	//初期化
	SetFontSize(20);

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char prev[256] = { 0 };


	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++)//キーの情報保存
		{
			prev[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);
		if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_RIGHT))
		{
			if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_DOWN))
			{
				player_move = 0.7f;//移動係数を0.71に設定
			}
			else
			{
				player_move = 1.0f;//斜めじゃなければ1.0に設定
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
		}//ここまでが操作設定。

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
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
			case 2://pポーズ画面

					/*if (CheckSoundMem(secene_sc) == 1)
					{
						StopSoundMem(secene_sc);
					}
					else
					{
						PlaySoundMem(secene_sd, DX_PLAYTYPE_LOOP, false);
					}*/
					break;
			case 3://敗北画面
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
			//更新処理
			case 0:
				PlaySoundMem(titlebgm, DX_PLAYTYPE_LOOP, FALSE);
				//シーン切り替えよう。スタートメニュー
				if (keys[KEY_INPUT_Z] == 1)
				{
					scene = 1;
				}
				//初期化
				score = 0;				//スコア
				shot_upgrade = 10000;			//弾のアップグレード
				enemy_upgrade = 3000;				//敵のアップグレード
				time = 0;			//時間経過

				//プレイヤー情報
				player_posx = 300;				//ｘ座標
				player_posy = 800;				//ｙ座標
				player_speed = 8;				//プレイヤーの速さ
				player_size = 20;				//プレイヤーの大きさ
				player_flag = 1;				//プレイヤーのフラッグ
				player_gif_time = 0;

				//弾の情報


				shot_time = 1;					//弾の間隔
				shot_number = 1;					//最大数の設定
				shot_damage = 1;					//ダメージ
				for (int i = 0; i < 256; i++)
				{
					if (shot_flag[i] == 1)
					{
						shot_flag[i] = 0;
					}
				}

				//敵の情報

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
				enemy_x_speed = 0;				//円の速さ。X座標
				enemy_y_speed = 2;				//円の速さ。Y座標
				enemy_number = 5;				//敵の上限設定

				for (int i = 0; i < 256; i++)
				{
					enemy_ko_posx[i] = { -100 };
					enemy_ko_posy[i] = { -100 };
				}


				//ボス情報
				boss_main_posx = 350;				//ボスメイン機X
				boss_main_posy = -10;				//ボスメイン機Y
				boss_main_hp = 120;				//HP
				boss_sub1_posx = 200;				//ボスサブ１X
				boss_sub1_posy = -10;				//ボスサブ１Y
				boss_sub1_hp = 30;				//HP
				boss_sub2_posx = 400;				//ボスサブ２X
				boss_sub2_posy = -10;				//ボスサブ２Y
				boss_sub2_hp = 30;				//HP
				boss_main_flag = 0;				//ボスメインフラグ
				boss_sub1_flag = 0;				//ボスサブ１フラグ
				boss_sub2_flag = 0;				//ボスサブ２フラグ]
				boss_speed0_posx = 0;				//ボス速さ
				boss_speed1_posx = 0;				//	//
				boss_speed2_posx = 0;				//	//
				boss_speed0_posy = 0;				//	//
				boss_speed1_posy = 0;				//	//
				boss_speed2_posy = 0;				//	//
				boss_speed0_change = 0;				//速さの変更。
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

				//描画処理
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
					//DrawFormatString(0, 5, GetColor(150, 150, 0), "Sキーでスタート");
				}
				break;//secen 0

			case 1://シーン切り替えようバトル画面。

				time++;//時間経過

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




				//スコア、弾のアップグレード、敵のアップグレード。
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

				//ボス戦突入
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


				//弾の発射
				if (keys[KEY_INPUT_SPACE] == 1 && player_flag == 1)//&& prev[KEY_INPUT_SPACE] == 0)//これ追加で長押し判定なし
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
				//長押しで一定間隔で発射できるようにする設定。
				if (shot_time <= 0 && player_flag == 1)
				{
					shot_time = 10;
				}
				if (keys[KEY_INPUT_SPACE] == 0)
				{
					shot_time = 1;
				}

				//弾の速さの設定
				for (int i = 0; i < shot_number; i++)//弾の速さの設定。
				{
					if (shot_flag[i] == 1)
					{
						shot_bullte_posy[i] = shot_bullte_posy[i] - 5;
					}
				}

				//敵の速さ
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
						// もし既に弾が『飛んでいない』状態だった場合のみ発射処理を行う
						if (enemy_shot_flag[i] == 0)
						{
							// 弾の発射位置を設定する
							enemy_shot_posx[i] = enemy_posx[i];
							enemy_shot_posy[i] = enemy_posy[i];

							// 弾の移動速度を設定する
							{
								double sb, sbx, sby, bx, by, sx, sy;

								sx = enemy_posx[i] + enemy_size / 2;
								sy = enemy_posy[i] + enemy_size / 2;

								bx = player_posx + player_size / 2;
								by = player_posy + player_size / 2;

								sbx = bx - sx;
								sby = by - sy;

								// 平方根を求めるのに標準関数の sqrt を使う、
								// これを使うには math.h をインクルードする必要がある
								sb = sqrt(sbx * sbx + sby * sby);

								// １フレーム当たり８ドット移動するようにする
								enemy_shot_speedx[i] = sbx / sb * 8;
								enemy_shot_speedy[i] = sby / sb * 8;
							}
							if (enemy_posy[i] >= 10 && enemy_flag[i] == 1)
							{
								enemy_shot_flag[i] = 1;
							}
						}
						// 弾を打つタイミングを計測するための変数に０を代入
						enemy_shot_counter = 0;
					}
				}
				//DrawFormatString(50, 440, GetColor(83, 160, 162), " flag[%d]", enemy_shot_flag[10]);//スコア
				//DrawFormatString(50, 460, GetColor(83, 160, 162), "エネミーFLAG [%d]", enemy_flag[1]);//スコア


				for (int i = 0; i < 256; i++)
				{
					if (enemy_shot_flag[i] == 1)
					{
						// 弾を移動させる
						enemy_shot_posx[i] += enemy_shot_speedx[i];
						enemy_shot_posy[i] += enemy_shot_speedy[i];

						// もし弾が画面からはみ出てしまった場合は弾の状態を『飛んでいない』
						// を表す０にする
						if (enemy_shot_posy[i] > 900 || enemy_shot_posy[i] < 0 || enemy_shot_posx[i] > 600 || enemy_shot_posx[i] < 0)
						{
							enemy_shot_flag[i] = 0;
						}
					}
				}

				for (int i = 0; i < 256; i++)
				{
					difference_posx[i] = (player_posx - enemy_shot_posx[i]) * (player_posx - enemy_shot_posx[i]);//X座標の差
					difference_posy[i] = (player_posy - enemy_shot_posy[i]) * (player_posy - enemy_shot_posy[i]);//Y座標の差
					if (player_flag == 1 && enemy_shot_flag[i] == 1)
					{
						if (enemy_shot_redius >= difference_posx[i] + difference_posy[i])
						{
							player_flag = 0;
							enemy_shot_flag[i] = 0;
						}
					}
				}


				//BOSSの設定
				//当たり判定
				if (boss_main_flag == 1)
				{
					//ダメージ増やす。特殊条件
					if (boss_sub1_flag == 0 && boss_sub2_flag == 0 && damage_flag == 0)
					{
						shot_damage = 5;

					}


				}
				for (int i = 0; i < shot_number; i++)
				{
					difference_posx[i] = (boss_main_posx - shot_bullte_posx[i]) * (boss_main_posx - shot_bullte_posx[i]);//X座標の差
					difference_posy[i] = (boss_main_posy - shot_bullte_posy[i]) * (boss_main_posy - shot_bullte_posy[i]);//Y座標の差
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
					difference_posx[i] = (boss_sub1_posx - shot_bullte_posx[i]) * (boss_sub1_posx - shot_bullte_posx[i]);//X座標の差
					difference_posy[i] = (boss_sub1_posy - shot_bullte_posy[i]) * (boss_sub1_posy - shot_bullte_posy[i]);//Y座標の差
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
					difference_posx[i] = (boss_sub2_posx - shot_bullte_posx[i]) * (boss_sub2_posx - shot_bullte_posx[i]);//X座標の差
					difference_posy[i] = (boss_sub2_posy - shot_bullte_posy[i]) * (boss_sub2_posy - shot_bullte_posy[i]);//Y座標の差
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
						difference_posx[i] = (boss_main_posx - player_posx) * (boss_main_posx - player_posx);//X座標の差
						difference_posy[i] = (boss_main_posy - player_posy) * (boss_main_posy - player_posy);//Y座標の差
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
						difference_posx[i] = (boss_sub1_posx - player_posx) * (boss_sub1_posx - player_posx);//X座標の差
						difference_posy[i] = (boss_sub1_posy - player_posy) * (boss_sub1_posy - player_posy);//Y座標の差
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
						difference_posx[i] = (boss_sub2_posx - player_posx) * (boss_sub2_posx - player_posx);//X座標の差
						difference_posy[i] = (boss_sub2_posy - player_posy) * (boss_sub2_posy - player_posy);//Y座標の差
						if (boss_sub2_player >= difference_posx[i] + difference_posy[i])
						{
							player_flag = 0;
						}
					}
				}

				//速度変化させる。

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

				//ボスの移動

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
					//Xの移動制限
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
					//Yの移動制限
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

					//速さ足す。
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
				//当たり判定
				//弾と雑魚敵
				for (int i = 0; i < shot_number; i++)
				{
					for (int j = 0; j < enemy_number; j++)
					{
						difference_posx[j] = (shot_bullte_posx[i] - enemy_posx[j]) * (shot_bullte_posx[i] - enemy_posx[j]);//X座標の差
						difference_posy[j] = (shot_bullte_posy[i] - enemy_posy[j]) * (shot_bullte_posy[i] - enemy_posy[j]);//Y座標の差
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
				//雑魚敵と本体の当たり判定
				for (int i = 0; i < enemy_number; i++)
				{
					difference_posx[i] = (enemy_posx[i] - player_posx) * (enemy_posx[i] - player_posx);//X座標の差
					difference_posy[i] = (enemy_posy[i] - player_posy) * (enemy_posy[i] - player_posy);//Y座標の差
					if (enemy_flag[i] == 1)
					{
						if (redius_main >= difference_posx[i] + difference_posy[i])
						{
							player_flag = 0;
						}
					}
				}


				//弾が画面外に出たらFLAGが０になる。
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
				//復活タイマー
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

				//死んだときの処理
				if (player_flag == 0)
				{
					scene = 3;
				}

				//描画処理
				//数字の表記
				//DrawFormatString(0, 5, GetColor(150, 150, 0), "弾のフラッグ0[%d]", shot_flag[0]);//弾の表示
				//DrawFormatString(0, 20, GetColor(150, 150, 0), "弾のフラッグ1[%d]", shot_flag[1]);//弾の表示
				//DrawFormatString(0, 40, GetColor(150, 150, 0), "弾のフラッグ2[%d]", shot_flag[2]);//弾の表示
				//DrawFormatString(0, 60, GetColor(150, 150, 0), "弾のフラッグ3[%d]", shot_flag[3]);//弾の表示
				//DrawFormatString(0, 80, GetColor(150, 150, 0), "弾のフラッグ4[%d]", shot_flag[4]);//弾の表示
				//DrawFormatString(0, 100, GetColor(150, 150, 0), "敵のフラッグ [%d]", enemy_flag[0]);  //敵の表示
				////DrawFormatString(0, 120, GetColor(150, 150, 0), "敵のフラッグ [%d]", enemy_flag[1]);  //敵の表示
				////DrawFormatString(0, 140, GetColor(150, 150, 0), "敵のフラッグ [%d]", enemy_flag[2]);  //敵の表示
				//DrawFormatString(0, 160, GetColor(150, 150, 0), "アップグレード条件 [%d]", shot_upgrade);  //弾数増やすための条件
				//DrawFormatString(0, 180, GetColor(150, 150, 0), "現在のスコア [%d]", score);//スコア
				//DrawFormatString(0, 200, GetColor(150, 150, 0), "敵X[0] [%d]", enemy_posx[0]);//スコア
				//DrawFormatString(0, 220, GetColor(150, 150, 0), "敵Y[0] [%d]", enemy_posy[0]);//スコア
				//DrawFormatString(0, 240, GetColor(150, 150, 0), "敵X[1] [%d]", enemy_posx[1]);//スコア
				//DrawFormatString(0, 260, GetColor(150, 150, 0), "敵Y[1] [%d]", enemy_posy[1]);//スコア
				//DrawFormatString(0, 280, GetColor(150, 150, 0), "time[0] [%d]", enemy_respown[0]);//スコア
				//DrawFormatString(0, 300, GetColor(150, 150, 0), "time[1] [%d]", enemy_respown[1]);//スコア
				//DrawFormatString(0, 320, GetColor(150, 150, 0), "敵の出現条件 [%d]", enemy_number);
				//DrawFormatString(0, 340, GetColor(150, 150, 0), "敵の出現条件 [%d]", enemy_upgrade);
				//DrawFormatString(0, 360, GetColor(150, 150, 0), "ESCキーでポーズ");
				//DrawFormatString(0, 400, GetColor(150, 150, 0), "%d", boss_main_flag);
				//DrawFormatString(0, 420, GetColor(150, 150, 0), "%d", boss_sub1_flag);
				//DrawFormatString(0, 440, GetColor(150, 150, 0), "%d", boss_sub2_flag);
				//DrawFormatString(0, 460, GetColor(150, 150, 0), "%d", boss_main_hp);
				//DrawFormatString(0, 500, GetColor(150, 150, 0), "%d", time);
				//DrawFormatString(0, 520, GetColor(150, 150, 0), "%d", boss_speed0_change);
				//DrawFormatString(0, 550, GetColor(150, 150, 0), "%d", boss_speed0_posx);
				//DrawFormatString(50, 570, GetColor(150, 150, 0), "%d", player_flag);
				//DrawFormatString(17, 120, GetColor(83, 160, 162), "sg [%d]", sg);//スコア
				//DrawFormatString(17, 140, GetColor(83, 160, 162), "rs [%d]", rs);//スコア
				//DrawFormatString(17, 160, GetColor(83, 160, 162), "  bg [%d]", bg);//スコア
				//DrawFormatString(17, 180, GetColor(83, 160, 162), " go [%d]", go);//スコア
				//DrawFormatString(17, 200, GetColor(83, 160, 162), "  gc [%d]", gc);//スコア
				//DrawFormatString(17, 220, GetColor(83, 160, 162), " ti [%d]", ti);//スコア
				//DrawFormatString(17, 240, GetColor(83, 160, 162), " lu [%d]", lu);//スコア
				//DrawFormatString(17, 260, GetColor(83, 160, 162), "bl [%d]", bl);//スコア
				//DrawFormatString(17, 280, GetColor(83, 160, 162), " du [%d]", du);//スコア
				//DrawFormatString(17, 300, GetColor(83, 160, 162), " p [%d]", p);//スコア
				//DrawFormatString(17, 320, GetColor(83, 160, 162), "mv [%d]", mv);//スコア
				//DrawFormatString(17, 340, GetColor(83, 160, 162), "s [%d]", s);//スコア
				//DrawFormatString(17, 360, GetColor(83, 160, 162), "e [%d]", e);//スコア
				//DrawFormatString(17, 380, GetColor(83, 160, 162), " e_ko [%d]", e_ko);//スコア
				//DrawFormatString(50, 400, GetColor(83, 160, 162), " arara[%d]", enemy_shot_counter);//スコア
				DrawFormatString(20, 45, GetColor(83, 160, 162), "SCORE [%d]", score);//スコア
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

				//弾の表示
				for (int i = 0; i < shot_number; i++)
				{
					if (shot_flag[i] == 1)
					{
						//DrawCircle(shot_bullte_posx[i], shot_bullte_posy[i], shot_size, GetColor(150, 250, 45), TRUE);//弾の表示
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
						//DrawCircle(shot_bullte_posx[i], shot_bullte_posy[i], shot_size, GetColor(150, 250, 45), TRUE);//弾の表示
						DrawGraph(enemy_shot_posx[i] - shot_size - 5, enemy_shot_posy[i] - shot_size, enemy_shot, true);
					}
					if (s >= 2)
					{
						s = 0;
					}
				}


				//敵の表示
				for (int i = 0; i < enemy_number; i++)
				{
					if (enemy_flag[i] == 1)
					{
						//DrawCircle(enemy_posx[i], enemy_posy[i], enemy_size, GetColor(150, 250, 45), TRUE);//敵の表示	
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

				//BOSS戦の描画
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

			case 2://ポーズ画面。シーン切り替えよう。
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

				//描画処理
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

			case 3://敗北画面
				//DrawFormatString(0, 360, GetColor(150, 150, 0), "GAME　OVER");
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

				//描画処理
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

			case 4://clear画面
				//DrawFormatString(0, 360, GetColor(150, 150, 0), "GAME　clear");
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

				//描画処理
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

		//DrawFormatString(0, 450, GetColor(150, 150, 0), "画面secen[%d]", scene);
	//---------  ここまでにプログラムを記述  ---------//
	// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
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
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
