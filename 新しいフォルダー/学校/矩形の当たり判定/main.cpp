#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "K021G1271 名前:上里まさとし";

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
	int circleBorrowed = 0;
	circleBorrowed = LoadGraph("機体/Circle.png");
	int circleShowBox = 0;
	circleShowBox = LoadGraph("機体/CircleW.png");

	int hitCircleBorrowed = 0;
	hitCircleBorrowed = LoadGraph("機体/CircleHit.png");
	int hitCircleShowBoxBorrowed = 0;
	hitCircleShowBoxBorrowed = LoadGraph("機体/CircleWHit.png");

	int screen1 = 0;
	screen1 = LoadGraph("背景画像/haikei1.png");
	int screen2 = 0;
	screen2 = LoadGraph("背景画像/haikei2.png");
	int screen3 = 0;
	screen3 = LoadGraph("背景画像/haikei3.png");


	// ゲームループで使う変数の宣言

	float scroll_x = 0;
	int boxX2 = 900;
	int boxY2 = 300;
	int boxX = 300;
	int boxY = 200;
	int size = 32;
	float playerPosX = 200;
	float playerPosY = 200;
	float playerPosX2 = playerPosX + 32;
	float playerPosY2 = playerPosY + 32;
	float moveSpeed = 5;
	float move = 0;
	int isHit = 0;

	int isShowBox = 0;
	int circleResult = circleBorrowed;
	int hitCircleResult = hitCircleBorrowed;


	int screen1_posx = 0;
	int screen2_posx = 600;
	int screen_speed = 5;

	float world_x = 200;
	float local_x = 0;
	int scroll_line_x = 300;
	int scroll_line_y = 400;

	int screen = 0;

	int getMousuX = 0;
	int getMousuY = 0;
	int MouseInput = 0;
	
	int isGetMouse = 0;


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

		if (CheckHitKey(KEY_INPUT_A) && playerPosX >= 0 + size)
		{
			playerPosX -= moveSpeed * move;
			playerPosX2 -= moveSpeed * move;
			world_x -= moveSpeed;
		}

		if (CheckHitKey(KEY_INPUT_D) && playerPosX <= 600)
		{
			playerPosX += moveSpeed * move;
			playerPosX2 += moveSpeed * move;
			world_x += moveSpeed;
		}

		if (CheckHitKey(KEY_INPUT_W) && playerPosY >= 0 + size)
		{
			playerPosY -= moveSpeed * move;
			playerPosY2 -= moveSpeed * move;
		}

		if (CheckHitKey(KEY_INPUT_S) && playerPosY <= WIN_HEIGHT)
		{
			playerPosY += moveSpeed * move;
			playerPosY2 += moveSpeed * move;
		}


		//拡大縮小、横バージョン
		if (CheckHitKey(KEY_INPUT_E))
		{
			playerPosX -= 1;
			playerPosX2 += 1;
		}
		if (CheckHitKey(KEY_INPUT_Q))
		{
			playerPosX += 1;
			playerPosX2 -= 1;
		}

		//拡大縮小、縦バージョン。
		if (CheckHitKey(KEY_INPUT_C))
		{
			playerPosY -= 1;
			playerPosY2 += 1;
		}
		if (CheckHitKey(KEY_INPUT_Z))
		{
			playerPosY += 1;
			playerPosY2 -= 1;
		}


		//マウス部分
		GetMousePoint(&getMousuX, &getMousuY);
		MouseInput = GetMouseInput();
		if ((GetMouseInput() & MOUSE_INPUT_LEFT))
		{
			playerPosX = getMousuX;
			playerPosY = getMousuY;
			playerPosX2 = playerPosX + 32;
			playerPosY2 = playerPosY + 32;
		}
		
		

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理


		//当たり判定
		if (playerPosX <= boxX + size && boxX <= playerPosX2)
		{
			if (playerPosY <= boxY + size && boxY <= playerPosY2)
			{
				isHit = 1;
			}
			else
			{
				isHit = 0;
			}
		}
		else
		{
			isHit = 0;
		}
		
		
			//当たり判定の描画の画像設定。
		if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0)
		{
			if (isShowBox == 0)
			{
				isShowBox = 1;
				circleResult = circleShowBox;
				hitCircleResult = hitCircleShowBoxBorrowed;
			}
			else
			{
				isShowBox = 0;
				circleResult = circleBorrowed;
				hitCircleResult = hitCircleBorrowed;
			}
		}


		// 描画処理
		//背景
		DrawGraph(screen - scroll_x, 0, screen1, true);
		DrawGraph(screen + 600 - scroll_x, 0, screen2, true);
		DrawGraph(screen + 1200 - scroll_x, 0, screen3, true);

		if (isHit == 0)
		{
			DrawGraph(boxX2 - size, boxY2 - size, circleResult, true);
			DrawGraph(boxX - size, boxY - size, circleResult, true);
			DrawExtendGraph(playerPosX - size, playerPosY - size, playerPosX2 - size, playerPosY2 - size, circleResult, TRUE);
		}
		else
		{
			DrawGraph(boxX2 - size, boxY2 - size, hitCircleResult, true);
			DrawGraph(boxX - size, boxY - size, hitCircleResult, true);
			DrawExtendGraph(playerPosX - size, playerPosY - size, playerPosX2 - size, playerPosY2 - size, hitCircleResult, TRUE);
		}

		DrawFormatString(0, 40, GetColor(150, 150, 0), "当たり判定[%d]", isHit);
		DrawFormatString(0, 60, GetColor(150, 150, 0), "速さ[%lf]", moveSpeed);
		DrawFormatString(0, 80, GetColor(150, 150, 0), "固定X[%d]", boxX);
		DrawFormatString(0, 100, GetColor(150, 150, 0), "player_x[%lf]", playerPosX);
		DrawFormatString(0, 120, GetColor(150, 150, 0), "スクリーン１x[%d]", screen1_posx);
		DrawFormatString(0, 140, GetColor(150, 150, 0), "スクリーン２x[%d]", screen2_posx);
		DrawFormatString(400, 10, GetColor(0, 0, 0), "world_x : [%lf]", world_x);
		DrawFormatString(400, 30, GetColor(0, 0, 0), "scroll_x : [%lf]", scroll_x);
		DrawFormatString(400, 50, GetColor(0, 0, 0), "BOX出すか : [%d]", isShowBox);

		//DrawLine(scroll_line_x, 0, scroll_line_x, scroll_line_y, GetColor(0, 0, 0));

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
	DeleteGraph(circleBorrowed);
	DeleteGraph(circleShowBox);
	DeleteGraph(hitCircleBorrowed);
	DeleteGraph(hitCircleShowBoxBorrowed);
	DeleteGraph(screen1);
	DeleteGraph(screen2);
	DeleteGraph(screen3);
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}