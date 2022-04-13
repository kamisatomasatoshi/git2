#include "DxLib.h"
#include <stdio.h>



// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "学籍番号 名前:タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 720;	

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
	SetBackgroundColor(0x0, 0x0, 0x0);			

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int moveKeys  = LoadGraph("resource/keys.png");
	
	int moveKeysA = LoadGraph("resource/A_keys.png");
	
	int moveKeysD = LoadGraph("resource/D_keys.png");

	int mousenone = LoadGraph("resource/mouse.png");
	int mouseRight = LoadGraph("resource/mouse_right.png");
	int mouseLeft = LoadGraph("resource/mouse_left.png");
	int notUse= LoadGraph("resource/not.png");
	int boomerang = LoadGraph("resource/boomerang.png");
	int shield= LoadGraph("resource/shield.png");
	int spece = LoadGraph("resource/space.png");
	int speceUse = LoadGraph("resource/space_use.png");
	int title = LoadGraph("resource/title.png");
	int gameClear = LoadGraph("resource/gameclear.png");
	int gameOver = LoadGraph("resource/gameover.png");
	int explanation = LoadGraph("resource/explanation.png");

	int mouse = GetMouseInput();
	// ゲームループで使う変数の宣言


	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);
		//マウスの取得
		mouse = GetMouseInput();

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理


		// 描画処理
		if (0)//シーンがタイトルだったら
		{
			DrawGraph(0, 0, title, TRUE);
		}
		
		if (0)//もし説明の画面なら
		{
			DrawGraph(0, 0, explanation, TRUE);
		}
		

		if (0)//シーンが戦闘の時
		{
			//移動キーの描画
			DrawGraph(200, 660, moveKeys, TRUE);
			if (keys[KEY_INPUT_A])
			{
				DrawGraph(200, 660, moveKeysA, TRUE);
			}

			if (keys[KEY_INPUT_D])
			{
				DrawGraph(200, 660, moveKeysD, TRUE);
			}
			DrawGraph(300, 660, spece, TRUE);
			if (keys[KEY_INPUT_SPACE])
			{
				DrawGraph(300, 660, speceUse, TRUE);
			}

			//マウスの描画
			DrawGraph(1080, 650, mousenone, TRUE);
			if (mouse & MOUSE_INPUT_LEFT)
			{
				//ブーメラン攻撃
				DrawGraph(1080, 650, mouseLeft, TRUE);
			}
			if (mouse & MOUSE_INPUT_RIGHT)
			{
				//ガード
				DrawGraph(1080, 650, mouseRight, TRUE);
			}

			//ブーメラン表示
			DrawGraph(1000, 650, boomerang, TRUE);

			//シールドの表示
			DrawGraph(1140, 650, shield, TRUE);

			if (1)//もし、ブーメランを投げてしまっていたら。
			{
				DrawGraph(1000, 650, notUse, TRUE);
				DrawGraph(1140, 650, notUse, TRUE);
			}
		}

		if (0)//シーンがクリアなら
		{
			DrawGraph(0, 0, gameClear, TRUE);
		}
		if (0)//シーンがオーバーなら
		{
			DrawGraph(0, 0, gameOver, TRUE);
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
	// Dxライブラリ終了処理
	InitGraph();
	DxLib_End();

	// 正常終了
	return 0;
}