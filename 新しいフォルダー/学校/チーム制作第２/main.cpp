#include "DxLib.h"
#include "main.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "学籍番号 名前:タイトル";

int map1[MAP_HEIGHT][MAP_WIDTH] =
{
	//		 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40
	/* 1*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/* 2*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/* 3*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/* 4*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/* 5*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/* 6*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/* 7*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/* 8*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/* 9*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*10*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*11*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*12*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*13*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*14*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*15*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*16*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*17*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*18*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*19*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*22*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*21*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*20*/ { 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1 ,1, 1, 1, 0, 0, 1, 1, 1, 1, 1},
	/*23*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*24*/ { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
	/*25*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*26*/ { 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1},
	/*27*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*28*/ { 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
	/*29*/ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	/*30*/ { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int Absolute(int a);

float Absolute(float a);

bool BoxCld(float objx, float objy, float objr, float objx2, float objy2, float objr2);

void Jump();

void SetBlock();

void MapScroll();

//void DrawMapGraph();

void graphNumberDisplayScore(float X, float Y, int number, int rank, int numberImage, int imageWidth, int imageHeight);

int exponentiation10(int a);


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

	int number;
	number = LoadGraph("resource\\number1.png");
	int fever;
	fever = LoadGraph("resource\\fever.png");
	int block;
	block = LoadGraph("resource\\block.png");
	int pengin;
	pengin = LoadGraph("resource\\pengin.png");
	// ゲームループで使う変数の宣言
	int fi = 0;

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (1)
	{
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

		//制限時間の減少
		timer--;
		if (timer < 0 && countTimer > 0)
		{
			countTimer--;
			timer = 60;
		}

		if (Fever.x + Fever.w <= 498)
		{
			deFever = 0;
			addFever = 1;
		}
		else if (Fever.x + Fever.w > 579 && addFever == 1)
		{
			addFever = 0;
			deFever = 1;
		}
		/*if (Fever.x + Fever.w < 579)
		{
			deFever = 0;
			addFever = 1;
		}
		else if (Fever.x + Fever.w >= 579)
		{
			addFever = 0;
			deFever = 1;
		}*/
		//加算
		if (addFever == 1)
		{
			Fever.w += 0.5f;
		}
		//減算
		else if (deFever == 1)
		{
			Fever.w -= 0.2f;
		}
		if (keys[KEY_INPUT_D] == 1)
		{
			player.x = player.x + playerSpeed;//右移動
		}

		if (keys[KEY_INPUT_A] == 1)
		{
			player.x = player.x - playerSpeed;//左移動
		}

		if (player.x + playerR >= blockSize * 12 || player.x - player.r <= blockSize)
		{
			playerSpeed *= -1;
			count += (WIN_HEIGHT - (player.y + player.r)) - 66;
		}

		if (count > 0)
		{
			count -= 3;
			score += 3;
		}



		//jump saidai
		if (deFever == 0)
		{
			fi = 1;
		}
		else if(deFever == 1)
		{
			fi = 2;
		}

		for (int i = 0; i < fi; i++)
		{
			if (isJumping[i] <= 0)
			{
				//ジャンプ
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
				{
					isJumping[i] = 1;
					jumpTimer = 18;
					break;
				}
			}
		}
		

		//player.x = player.x + playerSpeed;

		
		/*if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
		{
			if (deFever == 0)
			{
				isJumping[0] = 1;
				jumpTimer = 18;
			}
			for (int i = 0; i < 2; i++)
			{
				if (deFever == 1)
				{
					isJumping[i] = 1;
					jumpTimer = 18;
				}
			}
		}*/
		

		
		Jump();

		SetBlock();

		MapScroll();

		/*DrawMapGraph();*/

		// 描画処理
		DrawGraph(player.x - player.r, player.y - player.r, pengin, TRUE);
		DrawLine(0, 64 * 6 - 1, 1200, 64 * 6 - 1, GetColor(255, 255, 255), TRUE);

		graphNumberDisplayScore(scoreX, scoreY, score, 3, number, 32, 64);
		graphNumberDisplayScore(numberX2, scoreY, countTimer, 1, number, 32, 64);

		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			for (int x = 0; x < MAP_WIDTH; x++)
			{
				br = blockSize / 2;
				yoko = x * blockSize + br + backX;
				tate = y * blockSize + br + backY;

				if (map1[y][x] == 1 || map1[y][x] == 2)
				{
					DrawBox(yoko - br, tate - br, yoko + br, tate + br, GetColor(0, 255, 0), TRUE);
					/*	DrawGraph(yoko1 - br, tate - br, block, TRUE);*/
				}
			}
		}
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%d\n %d + %d", backX, Fever.x, Fever.w);
		DrawFormatString(0, 60, GetColor(255, 255, 255), "%d\n%d\n%d", backY, addFever, deFever);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "%d\n%d\n%d", isJumping[0], isJumping[1], deFever);

		//フィーバー
		DrawGraph(feverX, feverY, fever, TRUE);
		DrawBox(Fever.x, Fever.y,
			Fever.x + Fever.w, Fever.y + Fever.h, GetColor(255, 0, 0), TRUE);
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
	DeleteGraph(number);
	DeleteGraph(fever);
	DeleteGraph(block);
	DeleteGraph(pengin);
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}

//当たり判定
bool BoxCld(float objx, float objy, float objr, float objx2, float objy2, float objr2)
{
	return  objx + objr > objx2 - objr2 &&
		objy + objr > objy2 - objr2 &&
		objx - objr < objx2 + objr2 &&
		objy - objr < objy2 + objr2;
}
//ジャンプ
void Jump()
{
	oldPosX = playerX;
	oldPosY = playerY;
	for (int i = 0; i < 2; i++)
	{
		if (isJumping[i] == 1) //ジャンプ中
		{
			player.y -= jumpTimer;
			jumpTimer--;
			break;
		}
		else
		{
			jumpTimer--;
			player.y = player.y - jumpTimer;
			break;
		}
		//終端速度
		if (jumpTimer < -18)
		{
			jumpTimer = -18;
			break;
		}
		break;
	}
}

void SetBlock()
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			br = blockSize / 2;
			yoko = x * blockSize + br + backX;
			tate = y * blockSize + br + backY;

			if (map1[y][x] == 1)
			{
				if (BoxCld(player.x, player.y, player.r, yoko, tate, br))
				{
					for (int i = 0; i < 2; i++)
					{
						if (player.y + player.r < tate && jumpTimer <= 0)
						{
							player.y = tate - br - player.r;
							jumpTimer = 0;
							isJumping[i] = 0;
						}

						else if (player.x - player.r + 18 > yoko + br)
						{
							player.x = yoko + br + player.r;
						}

						else if (player.x + player.r - 18 < yoko - br)
						{
							player.x = yoko - br - player.r;
						}

						else if (player.y - player.r > tate && jumpTimer > 0)
						{
							player.y = tate + br + player.r;
							jumpTimer = 0;
						}
					}
				}
			}
		}
	}
}

//void DrawMapGraph()
//{
//	for (int y = 0; y < MAP_HEIGHT; y++)
//	{
//		for (int x = 0; x < MAP_WIDTH; x++)
//		{
//			br = blockSize / 2;
//			yoko1 = x * blockSize + br + backX;
//			tate = y * blockSize + br + backY;
//
//			if (map1[y][x] == 1 || map1[y][x] == 2)
//			{
//				/*DrawBox(yoko1 - br, tate - br, yoko1 + br, tate + br, GetColor(0, 255, 0), TRUE);*/
//				
//			}
//		}
//	}
//}

//マップスクロール
void MapScroll()
{
	//右へのスクロール
	if (player.x > WIN_WIDTH / 2 + 10 && backX > MAX_SCROLL_X)
	{
		backX = backX - scrollSpeed;
		player.x = WIN_WIDTH / 2 + 10;
	}
	//左へのスクロール
	if (player.x < WIN_WIDTH / 2 - 10 && backX < 0)
	{
		backX = backX + scrollSpeed;
		player.x = WIN_WIDTH / 2 - 10;
	}
	//上下へのスクロール
	if (player.y < WIN_HEIGHT / 2 - 20 && backY < 0)
	{
		player.y = (WIN_HEIGHT / 2 - 20);
		backY = backY + jumpTimer;
	}
	if (player.y > WIN_HEIGHT / 2 + 20 && backY > MAX_SCROLL_Y)
	{
		player.y = (WIN_HEIGHT / 2 + 20) + 5;
		backY = backY + jumpTimer;
	}

	if (backX > 0)
	{
		backX = 0;
	}

	if (backY > 0)
	{
		backY = 0;
	}

	if (backX < MAX_SCROLL_X)
	{
		backX = MAX_SCROLL_X;
	}

	if (backY < MAX_SCROLL_Y)
	{
		backY = MAX_SCROLL_Y;
	}

}
//桁を決め全てに数字を画像で表示する関数(数字がない場合は０を出力)
void graphNumberDisplayScore(float X, float Y, int number, int rank, int numberGraph, int GraphWidth, int GraphHeight)
{
	int outputNumber = 0;
	for (int i = rank; i >= 0; i--)
	{
		outputNumber = number / exponentiation10(i);
		if (outputNumber > 9)
		{
			outputNumber = outputNumber % 10;
		}
		DrawRectGraph(X + GraphWidth * (rank - i), Y, GraphWidth * outputNumber, 0, GraphWidth, GraphHeight, numberGraph, true, false);
	}
}

//累乗の関数
int exponentiation10(int a)
{
	int ans = 0;
	if (a == 0)
	{
		return 1;
	}

	for (int i = 0; i < a; i++)
	{
		if (ans == 0)
		{
			ans = 10;
		}
		else
		{
			ans = ans * 10;
		}
	}

	return ans;
}

//絶対値
int Absolute(int a)
{
	if (a < 0)
	{
		return a = -a;
	}
	return a;
}

float Absolute(float a)
{
	if (a < 0)
	{
		return a = -a;
	}
	return a;
}
