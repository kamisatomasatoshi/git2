#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LC1B_10_カミサト_マサトシ";

// ウィンドウ横幅
const int WIN_WIDTH = 1400;

// ウィンドウ縦幅
const int WIN_HEIGHT = 720;

double conv(double x, double y, double z);
double EaseingTitle(double x);
float Easing(float x);
int hit(int aX, int aY, int bX, int bY, int aSize, int bSize);

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

	int centerPointPosx = WIN_WIDTH / 2;
	int centerPointPosy = WIN_HEIGHT / 2;
	int size = 10;

	double playerPosX = 100;
	double playerPosY = 600;
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

	int scene = 0;

	int flame = 0;
	int x = 0;
	int isEaseing = 0;
	int posX = WIN_WIDTH / 2;
	int posY = WIN_HEIGHT / 2;
	int speed = 42;
	int isBoxDown = 0;
	int boxPosY = 0;
	int sceneSpeed = 100;

	int fontSize = 50;

	int isChange = 0;

	int randX = 0;
	int randY = 0;
	int randNum = 50;
	int time = 10;

	int isShake = 0;

	int ciclePosX=700;
	int ciclePosY=300;
	int cicelsSize = 40;
	int cicleSize = 60;

	int isMove = 0;
	int isLight = 1;

	int lightRand = 0;
	int isHit = 0;

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char prev[256] = { 0 };

	int randTime = 0;
	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 最新のキーボード情報を取得
		for (int i = 0; i < 256; i++)//キーの情報保存
		{
			prev[i] = keys[i];
		}
		GetHitKeyStateAll(keys);
		if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_D))
		{
			if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_S))
			{
				move = 0.7f;//移動係数を0.71に設定
				isMove = 1;
			}
			else
			{
				move = 1.0f;//斜めじゃなければ1.0に設定
				isMove = 1;
			}
		}

		else if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_S))
		{
			move = 1.0f;
			isMove = 1;
		}
		else
		{
			isMove = 0;
		}

		if (CheckHitKey(KEY_INPUT_A) && playerPosX >= 0 )
		{
			playerPosX -= moveSpeed * move;

		}
		else if (playerPosX <= 0)
		{
			isShake = 1;
			playerPosX += 5;
		}
		

		if (CheckHitKey(KEY_INPUT_D) && playerPosX+playerSize <= WIN_WIDTH)
		{
			playerPosX += moveSpeed * move;

		}
		else if (playerPosX+playerSize >= WIN_WIDTH)
		{
			isShake = 1;
			playerPosX -= 5;
		}
		

		if (CheckHitKey(KEY_INPUT_W) && playerPosY >= 0)
		{
			playerPosY -= moveSpeed * move;

		}

		if (CheckHitKey(KEY_INPUT_S) && playerPosY+playerSize <= WIN_HEIGHT)
		{
			playerPosY += moveSpeed * move;

		}

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		randTime++;
		//足元のエフェクト更新処理。BOXS

		if (scene == 0)
		{
			//タイトル
			if (keys[KEY_INPUT_SPACE])
			{
				isEaseing = 1;
			}

			if (isEaseing == 1)
			{
				flame++;
				posY += speed * EaseingTitle(conv(flame, MAXFLAME, x));
				boxPosY += speed * EaseingTitle(conv(flame, MAXFLAME, x));
				if (posY <= -32)
				{
					fontSize = 100;
					isBoxDown = 1;
				}
				if (flame == MAXFLAME)
				{
					flame = 0;
					isEaseing = 0;
					isBoxDown = 0;
					isChange = 1;
					scene = 1;
				}
			}
		}

		if (isChange == 1)
		{
			flame++;
			boxPosY -=sceneSpeed* Easing(conv(flame, MAXFLAME, x));
			if (flame == MAXFLAME)
			{
				flame = 0;
				isChange = 0;
				
				boxPosY = 0;
			}
		}


		if (scene == 0 || scene == 1);
		{
			for (int i = 0; i < 5; i++)
			{
				if (efectHp[i] <= 0 && isMove==1)
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


		if (keys[KEY_INPUT_R])
		{
			playerPosX = WIN_WIDTH / 2;
			playerPosY = 600;
			playerSize = 64;
			move = 0.0f;//斜め処理の計算
			moveSpeed = 3.0f;
			for (int i = 0; i < 5; i++)
			{
				efectPosX[i] =  0 ;
				efectPosY[i] =  0 ;
				efectSize[i] =  0 ;
				efectHp[i] =  0 ;
			}
			
			efectSpeed = 0.5f;
			//ある意味フラグ。
			landingTime = 20;
			left = 0;
			right = 0;

			scene = 0;

			flame = 0;
			x = 0;
			isEaseing = 0;
			posX = WIN_WIDTH / 2;
			posY = WIN_HEIGHT / 2;
			speed = 42;
			isBoxDown = 0;
			boxPosY = 0;
			sceneSpeed = 100;

			fontSize = 50;

			isChange = 0;

			SetBackgroundColor(0x00, 0x00, 0xFF);

		}


		if (isShake == 1)
		{
			randX = GetRand(randNum) - randNum / 2;
			randY = GetRand(randNum) - randNum / 2;

			randNum -= 2;

			if (randNum <= 0)
			{
				randNum = 50;
				isShake = 0;
			}
		}

		if (keys[KEY_INPUT_L] == 1 && prev[KEY_INPUT_L] == 0)
		{
			if (isLight == 0)
			{
				isLight = 1;
			}
			else
			{
				isLight = 0;
			}
		}
		//光の大きくなったり小さくなったり
		if (randTime % 4 == 0)
		{
			lightRand = GetRand(6) ;
		}

		//------------------------------------------//
		//当たり判定

		if (hit(playerPosX + (playerSize / 2) + randX, playerPosY + (playerSize / 2) + randY, ciclePosX, ciclePosY, cicleSize + lightRand, cicelsSize))
		{
			if (isLight)
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
			isHit=0;
		}

		// 描画処理

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, WIN_WIDTH, WIN_HEIGHT, GetColor(0, 0, 0), TRUE);//画面を暗くする
		
		//足元のエフェクト BOXS
		switch (scene)
		{
			case 0:
				if (keys[KEY_INPUT_B])
				{
					scene = 1;
				}
				SetFontSize(fontSize);
				DrawFormatString(posX - 50, posY - 50, GetColor(0, 0, 0), "演出王");
				SetFontSize(16);
				
				DrawFormatString(posX - 50, (WIN_HEIGHT / 2)+50 , GetColor(255, 255, 255), "start to 'SPACE'\n演出スキップ'B'");
				break;


			case 1:
				
				//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
				//DrawBox(0, 0, WIN_WIDTH, WIN_HEIGHT, GetColor(0, 0, 0), TRUE);//画面を暗くする

				//SetBackgroundColor(25, 25, 26);
				//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

				//SetDrawBlendMode(DX_BLENDMODE_SUB, 50);
				/*if (hit(playerPosX + (playerSize / 2) + randX, playerPosY + (playerSize / 2) + randY, ciclePosX, ciclePosY, cicleSize + lightRand, cicelsSize))
				{
					if (isLight)
					{

					DrawCircle(ciclePosX, ciclePosY, cicelsSize, GetColor(155, 155, 155), TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					}
				}*/

				if (isHit==1)
				{
					DrawCircle(ciclePosX, ciclePosY, cicelsSize, GetColor(155, 155, 155), TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
				}
				
				DrawCircle(ciclePosX, ciclePosY, cicelsSize, GetColor(255, 255, 255), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

				//DrawFormatString(0, 60, GetColor(255, 255, 255), "%d", scene); 
				
				break;

			case 2:
				break;
			default:
				printf("エラー:再起動してください。");
				break;
		}



		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		if (scene == 0 || scene == 1);
		{
			if (isLight == 1)
			{
				
				SetDrawBlendMode(DX_BLENDMODE_ADD, 30);
				DrawCircle(playerPosX + (playerSize / 2) + randX, playerPosY + (playerSize / 2) + randY, cicleSize+lightRand, GetColor(255, 255, 255), TRUE);
				
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			DrawBox(playerPosX + randX, playerPosY + randY, playerPosX + playerSize + randX, playerPosY + playerSize + randY, GetColor(110, 110, 114), TRUE);

			for (int i = 0; i < 5; i++)
			{
				if (efectHp[i] >= 1)
				{
					SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
					DrawCircle(efectPosX[i], efectPosY[i], efectSize[i], GetColor(255, 255, 255), TRUE);
					DrawCircle(efectPosX[i] + playerSize, efectPosY[i], efectSize[i], GetColor(255, 255, 255), TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
				}
			}
		}
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
	
		//シーンチェンジ用
		
		DrawBox(0, 0, WIN_WIDTH, boxPosY, GetColor(0, 0, 0), TRUE);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "移動方法:W A S D       リセット:R       ライト:L");
		DrawFormatString(0, 30, GetColor(255, 255, 255), "両端で自機がシェイク");
		/*DrawFormatString(0, 60, GetColor(255, 255, 255), "%d", scene);
		DrawFormatString(0, 90, GetColor(255, 255, 255), "%d", isChange);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "%d", boxPosY);*/

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

double conv(double x, double y, double z)
{
	return z = x / y;//x = (flame / maxFlame); 
}

double EaseingTitle(double x)
{
	const double c1 = 1.70158;
	const double c3 = c1 + 1;

	return c3 * x * x * x - c1 * x * x;
}
float Easing(float x)
{
	return x * x * x * x * x;
}

int hit(int aX, int aY, int bX, int bY, int aSize, int bSize)
{
	float dx = aX - bX;
	float dy = aY- bY;
	float dr = dx * dx + dy * dy;

	float ar = aSize + bSize;
	float dl = ar * ar;
	if (dr < dl)
	{
		return true;
	}

	return false;
}