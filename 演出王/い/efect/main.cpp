#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LC1B_10_カミサト_マサトシ";

// ウィンドウ横幅
const int WIN_WIDTH = 600;

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
	SetBackgroundColor(0x00, 0x00, 0xFF);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言

	int centerPointPosx = WIN_WIDTH / 2;
	int centerPointPosy = WIN_HEIGHT / 2;
	int size = 10;

	double playerPosX = 450;
	double playerPosY = 100;
	double playerSize = 64;
	double move = 0.0f;//斜め処理の計算
	double moveSpeed = 3.0f;

	double efectPosX[5] = { 0 };
	double efectPosY[5] = { 0 };
	int efectSpace = 32;//もう片方に出すときの間感
	float efectSize[5] = { 0 };
	float efectSpeed = 0.5f;
	int efectHp[5] = { 0 };//ある意味フラグ。
	int landingTime = 20;
	int left = 0;
	int right = 0;


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

		}

		if (CheckHitKey(KEY_INPUT_D) && playerPosX <= 600)
		{
			playerPosX += moveSpeed * move;

		}

		if (CheckHitKey(KEY_INPUT_W) && playerPosY >= 0 + size)
		{
			playerPosY -= moveSpeed * move;

		}

		if (CheckHitKey(KEY_INPUT_S) && playerPosY <= WIN_HEIGHT)
		{
			playerPosY += moveSpeed * move;

		}

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理

		//足元のエフェクト更新処理。BOXS
		for (int i = 0; i < 5; i++)
		{
			if (efectHp[i] <= 0 && keys[KEY_INPUT_SPACE])
			{
				efectHp[i] = GetRand(60);
				efectPosX[i] = playerPosX + GetRand(20) - 10;
				efectSize[i] = GetRand(8);
				efectPosY[i] = playerPosY + playerSize;

				break;
			}
			else if (efectSize[i] <= 0)
			{
				efectHp[i] = 0;
			}
			else
			{
				efectPosY[i] -= efectSpeed;
				efectHp[i]--;
				efectSize[i] -= 0.1;
			}
			if (keys[KEY_INPUT_A])
			{
				left = 1;
			}
			if (keys[KEY_INPUT_D])
			{
				right = 1;
			}
		}
		for (int i = 0; i < 5; i++)
		{
			if (right)
			{
				efectPosX[i] += GetRand(5);
				right = 0;
			}

			if (left)
			{
				efectPosX[i] -= GetRand(5);
				left = 0;
			}
		}
		//for (int i = 0; i < 5; i++)
		//{
		//	if (efectSize[i] >= 1 && efectHp[i] >= 1)
		//	{
		//		//efectSize[i] -= 0.1;
		//	}
		//}
		//for (int i = 0; i < 5; i++)
		//{
		//	if (efectHp[i] >= 1)
		//	{
		//		
		//		
		//	}

		//}


		//if (keys[KEY_INPUT_SPACE])// && efectHp <= 0)
		//{
		//	efectHp1 = GetRand(60);
		//	efectPosX1= playerPosX + GetRand(20) - 10;
		//	efectSize1 = GetRand(12);
		//	efectPosY1 = playerPosY+playerSize;
		//}
		//else
		//{
		//	efectHp1--;
		//}

		//if (efectHp1 >= 1)
		//{
		//	efectPosY1 += efectSpeed1;
		//}


		// 描画処理
		DrawFormatString(0, 0, GetColor(0, 0, 0), "%d", efectSpeed);
		DrawBox(playerPosX, playerPosY, playerPosX + playerSize, playerPosY + playerSize, GetColor(255, 0, 0), TRUE);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "エフェクト:SPACE");
		DrawFormatString(0, 30, GetColor(255, 255, 255), "移動方法:W A S D");
		//足元のエフェクト BOXS
		/*for (int i = 0; i < 30; i++)
		{
			if (efectHp[i] >= 1)
			{
				SetDrawBlendMode(DX_BLENDMODE_ADD, 123);
				DrawBox(efectPosX[i], efectPosY[i] + playerSize, efectPosX[i] + efectSize[i], efectPosY[i] + efectSize[i] + playerSize, GetColor(6, 200, 255), TRUE);
				DrawBox(efectPosX[i] + playerSize - 10, efectPosY[i] + playerSize, efectPosX[i] + efectSize[i] + playerSize - 10, efectPosY[i] + efectSize[i] + playerSize, GetColor(60, 200, 255), TRUE);
			}
		}*/
		//着地の煙
		for (int i = 0; i < 5; i++)
		{
			if (efectHp[i] >= 1)
			{
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawCircle(efectPosX[i], efectPosY[i], efectSize[i], GetColor(163, 163, 163), TRUE);
				DrawCircle(efectPosX[i] + playerSize, efectPosY[i], efectSize[i], GetColor(163, 163, 163), TRUE);
			}
		}
		//DrawCircle(centerPointPosx, centerPointPosy, size, GetColor(255, 255, 255),TRUE);
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