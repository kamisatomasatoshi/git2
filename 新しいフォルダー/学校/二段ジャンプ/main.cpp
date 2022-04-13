#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "学籍番号 名前:タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 600;

// ウィンドウ縦幅
const int WIN_HEIGHT = 400;	

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


	// ゲームループで使う変数の宣言
	int player_posX;
	int player_posY;
	int player_posX2;
	int player_posY2;
	int deFever;
	int isJumping[2] = { 0 };
	int jumpTimer = 0;

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

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理

		//if (keys[KEY_INPUT_SPACE] == 1)//&& prev[KEY_INPUT_SPACE] == 0)//これ追加で長押し判定なし
		//{
		//	shot_flag_time -= 1;
		//	for (int i = 0; i < 5; i++)
		//	{
		//		if (shot_flag[i] == 0 && shot_flag_time == 0)
		//		{
		//			shot_flag[i] = 1;
		//			shot_bullte_posx[i] = player_posx;
		//			shot_bullte_posy[i] = player_posy;
		//			break;
		//		}
		//	}
		//}
		

		
		if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0)
		{
			for (int i = 0; i < 2; i++)
			{
				if (deFever == 0)
				{
					isJumping[i] = 1;
					jumpTimer = 18;
					break;
				}
				else if(deFever == 1)
				{
					isJumping[i] = 1;
					jumpTimer = 18;
					break;
				}
			}
		}
		
		

		// 描画処理

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
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}