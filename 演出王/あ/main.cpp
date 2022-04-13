#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "学籍番号 名前:タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 600;

// ウィンドウ縦幅
const int WIN_HEIGHT = 400;	
double conv(double x, double y, double z);
double EaseingTitle(double x);

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
	const int MAXFLAME = 300;
	int flame = 0;
	int x = 0;
	int isEaseing = 0;
	int posX = WIN_WIDTH / 2;
	int posY = WIN_HEIGHT / 2;
	int speed = 42;
	int isBoxDown = 0;
	int boxPosY = 0;

	int fontSize = 50;

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
		if (keys[KEY_INPUT_SPACE])
		{
			isEaseing = 1;
		}

		if (isEaseing == 1)
		{
			flame++;
			posY+=speed* EaseingTitle(conv(flame, MAXFLAME, x));
			boxPosY+=speed* EaseingTitle(conv(flame, MAXFLAME, x));
			if (posY <= -32)
			{
				fontSize = 100;
				isBoxDown = 1;
			}
			if (flame == MAXFLAME)
			{
				flame = 0;
				isEaseing = 0;
			}
		}

		if (keys[KEY_INPUT_R])
		{
			flame = 0;
			x = 0;
			isEaseing = 0;
			posX = WIN_WIDTH / 2;
			posY = WIN_HEIGHT / 2;
			speed = 42;
			fontSize = 50;
			boxPosY = 0;
		}

		// 描画処理
		DrawBox(0, 0, WIN_WIDTH, boxPosY, GetColor(0, 0, 0), TRUE);
		SetFontSize(fontSize);
		DrawFormatString(posX-50, posY-50, GetColor(0, 0, 0), "TITLE");
		SetFontSize(20);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "スタート:SPACE");
		DrawFormatString(0, 30, GetColor(255, 255, 255), "リセット:R");
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

double conv(double x, double y, double z)
{
	return z = x / y;//x = (flame / maxFlame); 
}

double EaseingTitle(double x)
{
	const double c1 = 1.70158;
	const double c3 = c1 +1;

	return c3 * x * x * x - c1 * x * x;
}