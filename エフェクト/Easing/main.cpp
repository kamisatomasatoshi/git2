#include "DxLib.h"
#include "math.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "学籍番号 名前:タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 600;

// ウィンドウ縦幅
const int WIN_HEIGHT = 400;	

float Easing(float x);
float Easinf2(float x);
float conv(float x, float y, float z);


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
	float size = 25.0f;
	float posY = 50.0f;
	float posX = 50.0f;
	float posY2 = posY+size;
	float posX2 = posX+size;
	float speed = 5.0f;

	float posY3 = 100.0f;
	float posX3 = 50.0f;
	float posY4 = posY3 + size;
	float posX4 = posX3 + size;

	//out
	int flame = 0;
	int maxFlame = 300;
	int isStart = 0;
	//in
	int flame2 = 300;
	//int minFlame = 0;
	float x=0.0f;
	float x2 = 0.0f;

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

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		posY2 = posY + size;
		posX2 = posX + size;
		posY4 = posY3 + size;
		posX4 = posX3 + size;
		if (keys[KEY_INPUT_V] == 1)
		{
			isStart = 1;
		}

		if (isStart == 1)
		{
			flame++;
			flame2--;
			//posX += speed * Easing( conv(flame, maxFlame, x));//out
			posX3 += speed * Easing(conv(flame2, maxFlame, x2));//in

			if (flame2 == 0)
			{
				flame = 300;
			}
			if (flame == maxFlame)
			{
				flame = 0;
				isStart = 0;
			}


		}
		/*if (posX3 >= 400)
		{
			posX3 = 400;
		}*/


		// 描画処理
		DrawBox(posX, posY, posX2, posY2, GetColor(0, 0, 0), TRUE);
		DrawBox(posX3, posY3, posX4, posY4, GetColor(0, 0, 0), TRUE);
		DrawFormatString(0, 0, GetColor(0, 0, 0), "%d", isStart);
		DrawFormatString(0, 0, GetColor(0, 0, 0), "%d", flame);
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

float Easing(float x)
{
	return x*x*x*x*x;
}

//float Easinf2(float x)
//{
//	return 1 - pow(1 - x, 5);
//}

float conv(float x, float y,float z)
{
	return z = x / y;//x = (flame / maxFlame); 
}