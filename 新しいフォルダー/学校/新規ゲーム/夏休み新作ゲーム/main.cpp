#include "DxLib.h"
#include <math.h>

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LC1A_10_カミサトマサトシ";

// ウィンドウ横幅
const int WIN_WIDTH = 1200;

// ウィンドウ縦幅
const int WIN_HEIGHT = 800;	

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


	// ゲームループで使う変数の宣言
	//プレイヤー情報
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
		if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_D))
		{
			if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_S))
			{
				move = 0.7f;//移動係数を0.71に設定
			}
			else
			{
				move = 1.0f;//斜めじゃなければ1.0に設定
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
		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		

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
		
		//プレイヤーが玉を出す
		if (keys[KEY_INPUT_SPACE] == 1 && player_flag == 1)//&& prev[KEY_INPUT_SPACE] == 0)//これ追加で長押し判定なし
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

						// 平方根を求めるのに標準関数の sqrt を使う、
						// これを使うには math.h をインクルードする必要がある
						sb = sqrt(sbx * sbx + sby * sby);

						// １フレーム当たり８ドット移動するようにする
						shot_speed_x[i] = sbx / sb * 8;
						shot_speed_y[i] = sby / sb * 8;
					}
					
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

		

		for (int i = 0; i < shot_number; i++)//弾の速さの設定。
		{
			if (shot_flag[i] == 1)
			{
					// 弾を移動させる
					shot_bullte_posx[i] += shot_speed_x[i];
					shot_bullte_posy[i] += shot_speed_y[i];
			}
		}

		//当たり判定
		for (int i = 0; i < shot_number; i++)
		{
			radius = (ene_size + shot_size) * (ene_size + shot_size);//半径
			difference_posx = (shot_bullte_posx[i] - ene_x) * (shot_bullte_posx[i] - ene_x);//X座標の差
			difference_posy = (shot_bullte_posy[i] - ene_y) * (shot_bullte_posy[i] - ene_y);//Y座標の差

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
			//弾が画面外に出たらFLAGが０になる。
			/*if (shot_bullte_posy[i] < 0 || shot_bullte_posy[i]>400)
			{
				shot_flag[i] = 0;
			}*/
		}

		/*mato_x = ene_x - player_posx;
		mato_y = ene_y - player_posy;*/


		

















		// 描画処理
		//DrawGraph(0, 0, stage2, true);
		DrawCircle(player_posx, player_posy, size, GetColor(150, 150, 0));
		DrawCircle(ene_x, ene_y, ene_size, GetColor(0, 150, 0));
		DrawBox(x, y, x2, y2,GetColor(0, 0, 0),TRUE);
		for (int i = 0; i < shot_number; i++)
		{
			if (shot_flag[i] == 1)
			{
				//DrawCircle(shot_bullte_posx[i], shot_bullte_posy[i], shot_size, GetColor(150, 250, 45), TRUE);//弾の表示
				//DrawGraph(shot_bullte_posx[i] - shot_size - 5, shot_bullte_posy[i] - shot_size, shot[s], true);
				DrawCircle(shot_bullte_posx[i], shot_bullte_posy[i], shot_size, GetColor(150, 100, 150));
			}
		}





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
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	//InitGraph();
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}