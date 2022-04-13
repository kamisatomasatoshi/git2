#include "DxLib.h"
#include "stdlib.h"
#include "time.h"

CONST int HOLE = 14;

enum Scene
{
	Title,
	Init,
	Play,
	Clear,
	OverIn,
	Over,
};

struct Object
{
	int posX;
	int posY;
	int XR;
	int YR;
	int CR;
	float speed;
	bool alive;
};

struct ObjectHole
{
	int posX[HOLE];
	int posY[HOLE];
	int XR[HOLE];
	int YR[HOLE];
	int CR[HOLE];
	int speed[HOLE];
	bool alive[HOLE];
};

Object Player =
{
	600,
	600,
	32,
	32,
	16,
	6,
	true
};
Object Wall =
{
	600,
	400,
	100,
	400,
	64,
	0,
	true
};


int holePosX[HOLE];
int holePosY[HOLE];
int holePosXR[HOLE];
int holePosYR[HOLE];
int holePosCR[HOLE];
int holeSpeed[HOLE];
bool holeAlive[HOLE];


Object Flug =
{
	800,
	400,
	64,
	64,
	64,
	0,
	true
};

enum MapInfo
{
	NONE,
	BLOCK
};

//変数

int timerGame = 0;
int ScoreNow = 0;
int HiScoreNow = 5000;
bool HiScoreFlug = false;
bool HighScoreDrawFlug = false;

int PlR = 200;
int CountHop = 800;
int BoundHop = 100;
bool Jumphole = false;
bool FlugMove = false;
bool OldFlugMove = false;
bool upFlug = false;
bool downFlug = false;
bool leftFlug = false;
bool rightFlug = false;

bool StartSoundFlug = false;
bool PlayBGMFlug = false;
bool FallSoundFlug = false;
bool JumpSoundFlug = false;
bool HighSoundFlug = false;

int hopX = 0;
int hopY = 0;
int DrawHopX = Player.posX - Player.XR;
int DrawHopY = Player.posY - Player.YR;

int DrawEntryY = 850;

int DrawFloarY = 0;
int DrawTitleY = 0;

int ArrowUpX = 0;
int ArrowUpY = 0;

int ArrowDownX = 0;
int ArrowDownY = 0;

int ArrowLeftX = 0;
int ArrowLeftY = 0;

int ArrowRightX = 0;
int ArrowRightY = 0;

int KeyX = 0;
int KeyY = 0;

int playerLife = 3;

//入力判定
const bool Press = true;
const bool Release = false;

bool ENTER_Key = Release;
bool BACK_Key = Release;
bool UP_Key = Release;
bool DOWN_Key = Release;
bool LEFT_Key = Release;
bool RIGHT_Key = Release;
bool SPACE_Key = Release;

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LC1A_01_アカイケカケル:HOPPING CONVEYOR";

// ウィンドウ横幅
const int WIN_WIDTH = 1200;

// ウィンドウ縦幅
const int WIN_HEIGHT = 800;

// 最新のキーボード情報用
char keys[256] = { 0 };

// 1ループ(フレーム)前のキーボード情報
char oldkeys[256] = { 0 };

void KeyBoard()
{
	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; i++)
	{
		oldkeys[i] = keys[i];
	}
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);

	//移動用キー設定
	if (oldkeys[KEY_INPUT_W] == Release
		&& keys[KEY_INPUT_W] == Press
		||
		oldkeys[KEY_INPUT_UP] == Release
		&& keys[KEY_INPUT_UP] == Press)
	{
		UP_Key = Press;
	}
	else if (oldkeys[KEY_INPUT_W] == Press
		&& keys[KEY_INPUT_W] == Release
		||
		oldkeys[KEY_INPUT_UP] == Press
		&& keys[KEY_INPUT_UP] == Release)
	{
		UP_Key = Release;
	}

	if (oldkeys[KEY_INPUT_S] == Release
		&& keys[KEY_INPUT_S] == Press
		||
		oldkeys[KEY_INPUT_DOWN] == Release
		&& keys[KEY_INPUT_DOWN] == Press)
	{
		DOWN_Key = Press;
	}
	else if (oldkeys[KEY_INPUT_S] == Press
		&& keys[KEY_INPUT_S] == Release
		||
		oldkeys[KEY_INPUT_DOWN] == Press
		&& keys[KEY_INPUT_DOWN] == Release)
	{
		DOWN_Key = Release;
	}

	if (oldkeys[KEY_INPUT_A] == Release
		&& keys[KEY_INPUT_A] == Press
		||
		oldkeys[KEY_INPUT_LEFT] == Release
		&& keys[KEY_INPUT_LEFT] == Press)
	{
		LEFT_Key = Press;
	}
	else if (oldkeys[KEY_INPUT_A] == Press
		&& keys[KEY_INPUT_A] == Release
		||
		oldkeys[KEY_INPUT_LEFT] == Press
		&& keys[KEY_INPUT_LEFT] == Release)
	{
		LEFT_Key = Release;
	}

	if (oldkeys[KEY_INPUT_D] == Release
		&& keys[KEY_INPUT_D] == Press
		||
		oldkeys[KEY_INPUT_RIGHT] == Release
		&& keys[KEY_INPUT_RIGHT] == Press)
	{
		RIGHT_Key = Press;
	}
	else if (oldkeys[KEY_INPUT_D] == Press
		&& keys[KEY_INPUT_D] == Release
		||
		oldkeys[KEY_INPUT_RIGHT] == Press
		&& keys[KEY_INPUT_RIGHT] == Release)
	{
		RIGHT_Key = Release;
	}

	//特殊キー
	if (oldkeys[KEY_INPUT_RETURN] == Release
		&& keys[KEY_INPUT_RETURN] == Press)
	{
		ENTER_Key = Press;
	}
	else if (oldkeys[KEY_INPUT_RETURN] == Press
		&& keys[KEY_INPUT_RETURN] == Release)
	{
		ENTER_Key = Release;
	}

	if (oldkeys[KEY_INPUT_BACK] == Release
		&& keys[KEY_INPUT_BACK] == Press)
	{
		BACK_Key = Press;
	}
	else if (oldkeys[KEY_INPUT_BACK] == Press
		&& keys[KEY_INPUT_BACK] == Release)
	{
		BACK_Key = Release;
	}

}

void INit();

void MovePlayer();
void ChackFlug();
void DrawMovePlayer();
void DrawHole();
void DrawFlug();
void DrawWall();
bool Bounding();

void OutHole();
void RespornHole();

void ResetHole()
{
	//Player.posX = 250 + (10 * (rand() % 70));
	for (int i = 0; i < HOLE; i++)
	{
		if (i % 2 == 0)
		{
			holePosX[i] = 100 * (rand() % (75 / 10)) + 250;
			holePosY[i] = 0 - (80 * (i + 1));
			holePosXR[i] = 16;
			holePosYR[i] = 16;
			holePosCR[i] = 32;
			holeSpeed[i] = 4;
			holeAlive[i] = true;
		}
		else
		{
			holePosX[i] = 100 * (rand() % (75 / 10)) + 250;
			holePosY[i] = 0 - (80 * (i));
			holePosXR[i] = 16;
			holePosYR[i] = 16;
			holePosCR[i] = 32;
			holeSpeed[i] = 4;
			holeAlive[i] = true;
		}
	}
}

void ResetPlayer()
{
	Player.posX = 250 + (10 * (rand() % 70));
	Player.posY = 600;

	Player.alive = true;
	hopY = 0;
	playerLife = 3;
}

void RespornPlayer()
{
	Player.alive = true;
	Player.posY = 600;
	hopY = 0;
}

void ResetFlug()
{
	upFlug = false;
	downFlug = false;
	leftFlug = false;
	rightFlug = false;
}

void ResetEntry()
{
	DrawEntryY = 850;
	DrawFloarY = 0;
	DrawTitleY = 0;
}

void Entry()
{
	DrawTitleY += 4;
	DrawFloarY += 4;

	ArrowUpX = 100 - 16;
	ArrowUpY = 700;
	ArrowDownX = 100 - 16;
	ArrowDownY = 708;
	ArrowLeftX = 100 - 80;
	ArrowLeftY = 708;
	ArrowRightX = 100 + 48;
	ArrowRightY = 708;
	KeyX = 100 - 32;
	KeyY = 700;
}

bool ObjectCollision(int Obj1_x, int Obj1_y, int Obj1_xr, int Obj1_yr, int Obj2_x, int Obj2_y, int Obj2_xr, int Obj2_yr);
bool ObjectCollision(int Obj1_x, int Obj1_y, int Obj1_r, int Obj2_x, int Obj2_y, int Obj2_r);

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
	int Graph = LoadGraph("Hopping.png");
	int MapGraph = LoadGraph("MapHopping.png");
	int TitleGraph = LoadGraph("HoppingTitle.png");
	int PressGraph = LoadGraph("HoppingPress.png");
	int RetryGraph = LoadGraph("HoppingRetry.png");
	int BackGraph = LoadGraph("HoppingBack.png");
	int OverGraph = LoadGraph("HoppingOver.png");
	int HighScoreGraph = LoadGraph("Crown.png");

	int PlayBGM = LoadSoundMem("PlayBGM.mp3");
	int FallSound = LoadSoundMem("Fall.mp3");
	int JumpSound = LoadSoundMem("Jump.mp3");
	int StartSound = LoadSoundMem("Start.mp3");
	int HighSound = LoadSoundMem("HighScore.mp3");


	// ゲームループで使う変数の宣言
	srand(time(NULL));

	CONST int a = 8;
	CONST int b = 25;
	CONST int c = 128;
	int DrawSize = 64;

	int DrawHoleX[HOLE];
	int DrawHoleY[HOLE];
	int DrawWallX[a];
	int DrawWallY[b];

	int DrawKeyX = 0;

	int DrawFloarX = 0;

	int DrawUpKeyY = DrawSize * 3;
	int DrawDownKeyY = DrawSize * 3;
	int DrawLeftKeyY = DrawSize * 3;
	int DrawRightKeyY = DrawSize * 3;

	int UpArrowX = DrawSize;
	int DownArrowX = DrawSize * 4;
	int LeftArrowX = DrawSize * 3;
	int RightArrowX = DrawSize * 2;
	int UpArrowY = DrawSize * 3;
	int DownArrowY = DrawSize * 3;
	int LeftArrowY = DrawSize * 3;
	int RightArrowY = DrawSize * 3;

	int DrawLifeX[3];
	int DrawLifeY[3];
	int LifeX[3];
	int LifeY[3];

	int BoundCircle = 0;
	int CR = 0;
	int CG = 0;
	int CB = 0;

	int ChangeCount = 2000;
	int FallCount = 3600;
	int HighSoundCount = 3500;
	

	ResetPlayer();

	for (int i = 0; i < 3; i++)
	{
		DrawLifeX[i] = 1000 + (i*64); 
		DrawLifeY[i] = 800 -DrawSize;
		LifeX[i] = DrawSize * 3;
		LifeY[i] = DrawSize * 1;
	}

	int GameScene = Title;
	bool ET = false;
	bool BK = false;

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };



	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		//OldFlugMove = FlugMove;
		KeyBoard();

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		PlayBGMFlug = false;
		StartSoundFlug = false;
		JumpSoundFlug = false;
		FallSoundFlug = false;
		HighSoundFlug = false;


		// 更新処理
		if (ENTER_Key == Press)
		{
			if (ET == false)
			{
				ET = true;
			}
		}
		if (BACK_Key == Press)
		{
			if (BK == false)
			{
				BK = true;
			}
		}
		if (ET == true)
		{
			if (ENTER_Key == Release)
			{
				switch (GameScene)
				{
				case Title:
					StartSoundFlug = true;
					GameScene = Init;
					break;
				//case Init:
				//	//StartSoundFlug = false;
				//	break;

				case Over:
					//StartSoundFlug = false;
					ScoreNow = 0;
					HighScoreDrawFlug = false;
					//HighSoundFlug = false;
					StartSoundFlug = true;
					GameScene = Play;
					break;
				}
				ET = false;
			}
		}
		if (BK == true)
		{
			if (BACK_Key == Release)
			{
				if (GameScene == Over)
				{
					HighScoreDrawFlug = false;
					//HighSoundFlug = false;
					ScoreNow = 0;
					GameScene = Title;
				}
				BK = false;
			}
		}

		if (GameScene == Title)
		{
			ResetEntry();
		}
		if (GameScene == Init)
		{

			Entry();

			if (DrawEntryY > Player.posY)
			{
				DrawEntryY -= Player.speed;
			}
			else
			{
				DrawEntryY = Player.posY;
			}
			if (DrawTitleY >= 800)
			{
				ResetHole();
				GameScene = Play;
			}
		}

		if (GameScene == Play)
		{
			//StartSoundFlug = false;
			PlayBGMFlug = true;
			if(Bounding() == false)
			{
				JumpSoundFlug = true;
			}
			else
			{
				JumpSoundFlug = false;
			}
			Player.speed = 6;

			INit();
			ChangeCount -= 50;
			for (int i = 0; i < a; i++)
			{
				for (int j = 0; j < b; j++)
				{
					if (i < 4)
					{
						DrawWallX[i] = 200 - ((i + 1) * DrawSize);
					}
					else
					{
						DrawWallX[i] = 1000 + ((i - 4) * DrawSize);
					}
					DrawWallY[j] = j * DrawSize;
				}
			}

			if (CountHop >= 400
				&& CountHop <= 500)
			{
				BoundCircle = 36;
			}
			else if (CountHop < BoundHop)
			{
				CR = 200;
				CG = 200;
				CB = 200;
				BoundCircle = Player.CR;
			}
			else if (CountHop > 500)
			{
				CR = 50;
				CG = 50;
				CB = 200;

				if (CountHop % 50 == 0)
				{
					BoundCircle += 6;
				}
			}
			else
			{
				CR = 200;
				CG = 50;
				CB = 50;

				if (CountHop % 50 == 0)
				{
					BoundCircle -= 6;
				}
			}

			if (ChangeCount % 1000 > 800)
			{
				if (Bounding() == true)
				{
					hopX = DrawSize * 3;
				}
				else
				{
					hopX = DrawSize * 1;
				}
			}
			else
			{
				if (Bounding() == true)
				{
					hopX = DrawSize * 2;
				}
				else
				{
					hopX = 0;
				}
			}

			if (ChangeCount <= 0)
			{
				ChangeCount = 2000;
			}

			for (int j = 0; j < HOLE; j++)
			{
				DrawHoleX[j] = holePosX[j] - (holePosXR[j] * 2);
				DrawHoleY[j] = holePosY[j] - (holePosYR[j] * 2);
			}

			DrawFloarY = DrawFloarY + holeSpeed[0];

			if (DrawFloarY > 800)
			{
				DrawFloarY = 0;
			}

			if (Player.alive == false)
			{
				ChangeCount = 2000;
				timerGame = 0;
				GameScene = OverIn;
			}

			if (upFlug == true)
			{
				DrawUpKeyY = DrawSize * 4;
				ArrowUpY = 708 - 48;
				UpArrowY = DrawSize * 4;
			}
			else
			{
				DrawUpKeyY = DrawSize * 3;
				ArrowUpY = 708 - 64;
				UpArrowY = DrawSize * 3;
			}

			if (downFlug == true)
			{
				DrawDownKeyY = DrawSize * 4;
				ArrowDownY = 724;
				DownArrowY = DrawSize * 4;
			}
			else
			{
				DrawDownKeyY = DrawSize * 3;
				ArrowDownY = 708;
				DownArrowY = DrawSize * 3;
			}

			if (leftFlug == true)
			{
				DrawLeftKeyY = DrawSize * 4;
				ArrowLeftY = 724;
				LeftArrowY = DrawSize * 4;
			}
			else
			{
				DrawLeftKeyY = DrawSize * 3;
				ArrowLeftY = 708;
				LeftArrowY = DrawSize * 3;
			}

			if (rightFlug == true)
			{
				DrawRightKeyY = DrawSize * 4;
				ArrowRightY = 724;
				RightArrowY = DrawSize * 4;
			}
			else
			{
				DrawRightKeyY = DrawSize * 3;
				ArrowRightY = 708;
				RightArrowY = DrawSize * 3;
			}

			if(playerLife <= 2 )
			{
				LifeX[2] = DrawSize * 4;
			}
			else
			{
				LifeX[2] = DrawSize * 3;
			}
			if(playerLife <= 1 )
			{
				LifeX[1] = DrawSize * 4;
			}
			else
			{
				LifeX[1] = DrawSize * 3;
			}
		}

		if (GameScene == OverIn)
		{
			FallSoundFlug = true;
			FallCount -= 50;
			if (FallCount <= 0)
			{
				playerLife--;
				FallCount = 3600;
				if (playerLife <= 0)
				{
					GameScene = Over;
				}
				else
				{
					ResetHole();
					RespornPlayer();
					GameScene = Play;
				}
			}
		}
		if (GameScene == Over)
		{
			if(HiScoreFlug == true)
			{
				HighSoundCount -= 50;
				HighSoundFlug = true;
				HighScoreDrawFlug = true;
			}
			if(HighSoundCount <= 0)
			{
				HighSoundCount = 3500;
				HiScoreFlug = false;
			}

			ResetFlug();
			ResetHole();
			ResetPlayer();
		}

		// 描画処理

		DrawHopX = Player.posX - Player.XR;
		DrawHopY = Player.posY - Player.YR;
		DrawFloarX = 0;
		switch (GameScene)
		{
		case Title:
			DrawRectGraph(0, 0, 0, 0, 1200, 800, TitleGraph, true, false);
			DrawRectGraph(300, 500, 0, 0, 1024, 64, PressGraph, true, false);
			break;

		case Init:
			DrawRectGraph(DrawFloarX, DrawFloarY - 800, 0, 0, 1200, 800, MapGraph, true, false);
			DrawRectGraph(0, DrawTitleY, 0, 0, 1200, 800, TitleGraph, true, false);
			DrawRectGraph(DrawHopX, DrawEntryY, hopX, hopY, DrawSize, DrawSize, Graph, true, false);

			break;

		case Play:
			//DrawMap();
			DrawRectGraph(DrawFloarX, DrawFloarY, 0, 0, 1200, 800, MapGraph, true, false);
			DrawRectGraph(DrawFloarX, DrawFloarY - 800, 0, 0, 1200, 800, MapGraph, true, false);

			//DrawHole();
			for (int i = 0; i < HOLE; i++)
			{
				DrawRectGraph(DrawHoleX[i], DrawHoleY[i], 0, 128, DrawSize, DrawSize, Graph, true, false);
			}

			//DrawMovePlayer();
			
			DrawRectGraph(KeyX, KeyY - DrawSize, DrawKeyX, DrawUpKeyY, DrawSize, DrawSize, Graph, true, false);
			DrawRectGraph(KeyX, KeyY, DrawKeyX, DrawDownKeyY, DrawSize, DrawSize, Graph, true, false);
			DrawRectGraph(KeyX - DrawSize, KeyY, DrawKeyX, DrawLeftKeyY, DrawSize, DrawSize, Graph, true, false);
			DrawRectGraph(KeyX + DrawSize, KeyY, DrawKeyX, DrawRightKeyY, DrawSize, DrawSize, Graph, true, false);

			DrawRectGraph(ArrowUpX, ArrowUpY, UpArrowX, UpArrowY, DrawSize / 2, DrawSize / 2, Graph, true, false);
			DrawRectGraph(ArrowDownX, ArrowDownY, DownArrowX, DownArrowY, DrawSize / 2, DrawSize / 2, Graph, true, false);
			DrawRectGraph(ArrowLeftX, ArrowLeftY, LeftArrowX, LeftArrowY, DrawSize / 2, DrawSize / 2, Graph, true, false);
			DrawRectGraph(ArrowRightX, ArrowRightY, RightArrowX, RightArrowY, DrawSize / 2, DrawSize / 2, Graph, true, false);

			for (int i = 0; i < 3; i++)
			{
				
				DrawRectGraph(DrawLifeX[i], DrawLifeY[i], LifeX[i], LifeY[i], DrawSize, DrawSize, Graph, true, false);
			}

			SetFontSize(24);
			DrawFormatString(1050, 200, GetColor(200, 200, 200),
				"%d\n\n"
				"%d",
				HiScoreNow,
				ScoreNow);
			SetFontSize(16);
			DrawFormatString(1050, 184, GetColor(200, 200, 200),
				"HIGH SCORE\n\n\n"
				"Score");

			DrawCircle(Player.posX - 1, Player.posY, BoundCircle, GetColor(CR, CG, CB), true);

			DrawRectGraph(DrawHopX, DrawHopY, hopX, hopY, DrawSize, DrawSize, Graph, true, false);
			break;
		case OverIn:
			if (FallCount > 2700)
			{
				hopX = 0;
				hopY = DrawSize;
			}
			else if (FallCount > 1800)
			{
				hopX = DrawSize;
				hopY = DrawSize;
			}
			else if (FallCount > 900)
			{
				hopX = DrawSize * 2;
				hopY = DrawSize;
			}

			DrawRectGraph(DrawFloarX, DrawFloarY, 0, 0, 1200, 800, MapGraph, true, false);
			DrawRectGraph(DrawFloarX, DrawFloarY - 800, 0, 0, 1200, 800, MapGraph, true, false);

			for (int i = 0; i < HOLE; i++)
			{
				DrawRectGraph(DrawHoleX[i], DrawHoleY[i], 0, 128, DrawSize, DrawSize, Graph, true, false);
			}

			if (FallCount > 900)
			{
				DrawRectGraph(DrawHopX, DrawHopY, hopX, hopY, DrawSize, DrawSize, Graph, true, false);
			}
			break;

		case Over:
				

			DrawRectGraph(0, 0, 0, 0, 1200, 800, MapGraph, true, false);
			SetFontSize(64);
			DrawFormatString(300, 400, GetColor(200, 200, 200),
				"%d\n\n"
				"%d",
				HiScoreNow,
				ScoreNow);
			SetFontSize(32);
			DrawFormatString(300, 368, GetColor(200, 200, 200),
				"HIGH SCORE\n\n\n\n"
				"Score");
			if (HighScoreDrawFlug == true)
			{
				DrawRectGraph(270, 310, 0, 0, 64, 64, HighScoreGraph, true, false);
			}

			DrawRectGraph(300, 600, 0, 0, 354, 57, RetryGraph, true, false);
			DrawRectGraph(300, 700, 0, 0, 316, 52, BackGraph, true, false);
			DrawRectGraph(198, 150, 0, 0, 808, 105, OverGraph, true, false);

			break;
		}
		
		if(StartSoundFlug == true)
		{
			if(CheckSoundMem(StartSound) == 0)
			{
				PlaySoundMem(StartSound,DX_PLAYTYPE_NORMAL,true);
			}
		}
		else
		{
			StopSoundMem(StartSound);
		}

		if(PlayBGMFlug == true)
		{
			if(CheckSoundMem(PlayBGM) == 0)
			{
				PlaySoundMem(PlayBGM,DX_PLAYTYPE_BACK,true);
			}
		}

		else
		{
			StopSoundMem(PlayBGM);
		}

		if(JumpSoundFlug == true)
		{
			if(CheckSoundMem(JumpSound) == 0)
			{
				PlaySoundMem(JumpSound,DX_PLAYTYPE_BACK,true);
			}
		}
		else
		{
			StopSoundMem(JumpSound);
		}

		if(FallSoundFlug == true)
		{
			if(CheckSoundMem(FallSound) == 0)
			{
				PlaySoundMem(FallSound,DX_PLAYTYPE_BACK,true);
			}
		}
		else
		{
			StopSoundMem(FallSound);
		}

		if(HighSoundFlug == true)
		{
			if(CheckSoundMem(HighSound) == 0)
			{
				PlaySoundMem(HighSound,DX_PLAYTYPE_BACK,true);
			}
		}
		else
		{
			StopSoundMem(HighSound);
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

	DeleteGraph(Graph);
	DeleteGraph(MapGraph);
	DeleteGraph(TitleGraph);
	DeleteGraph(PressGraph);
	DeleteGraph(RetryGraph);
	DeleteGraph(BackGraph);
	DeleteGraph(OverGraph);
	DeleteGraph(HighScoreGraph);

	DeleteSoundMem(PlayBGM);
	DeleteSoundMem(FallSound);
	DeleteSoundMem(JumpSound);
	DeleteSoundMem(StartSound);
	DeleteSoundMem(HighSound);

	// Dxライブラリ終了処理
	DxLib_End();


	// 正常終了
	return 0;
}
void UpPlayer()
{
	//KeyBoard();
	if (upFlug == true)
	{
		if (leftFlug == true
			|| rightFlug == true)
		{
			Player.speed = 4;
		}
		if (Player.posY > 0 + Player.XR)
		{
			Player.posY -= Player.speed;
		}

	}
}
void DownPlayer()
{
	//KeyBoard();
	if (downFlug == true)
	{
		if (leftFlug == true
			|| rightFlug == true)
		{
			Player.speed = 4;
		}

		if (Player.posY < WIN_HEIGHT - Player.XR)
		{
			Player.posY += Player.speed;
		}

	}
}
void LeftPlayer()
{
	//KeyBoard();
	if (leftFlug == true)
	{
		if (upFlug == true
			|| downFlug == true)
		{
			Player.speed = 4;
		}

		if (Player.posX > 200 + Player.XR)
		{
			Player.posX -= Player.speed;
		}
	}
}
void RightPlayer()
{
	//KeyBoard();
	if (rightFlug == true)
	{
		if (upFlug == true
			|| downFlug == true)
		{
			Player.speed = 4;
		}

		if (Player.posX < WIN_WIDTH - (Wall.YR / 2) - Player.XR)
		{
			Player.posX += Player.speed;
		}
	}
}

void ChackFlug()
{
	if (UP_Key == Press)
	{
		upFlug = true;
		downFlug = false;
		if (LEFT_Key == Press)
		{
			leftFlug = true;
			rightFlug = false;
			//LeftPlayer();
		}
		else
		{
			leftFlug = false;
		}

		if (RIGHT_Key == Press)
		{
			leftFlug = false;
			rightFlug = true;
			//RightPlayer();
		}
		else
		{
			rightFlug = false;
		}
		//UpPlayer();
	}
	if (DOWN_Key == Press)
	{
		downFlug = true;
		upFlug = false;
		if (LEFT_Key == Press)
		{
			leftFlug = true;
			rightFlug = false;
			//LeftPlayer();
		}
		else
		{
			leftFlug = false;
		}

		if (RIGHT_Key == Press)
		{
			leftFlug = false;
			rightFlug = true;
			//RightPlayer();
		}
		else
		{
			rightFlug = false;
		}
		//DownPlayer();
	}
	if (LEFT_Key == Press)
	{
		leftFlug = true;
		rightFlug = false;
		if (UP_Key == Press)
		{
			upFlug = true;
			downFlug = false;
			//LeftPlayer();
		}
		else
		{
			upFlug = false;
		}

		if (DOWN_Key == Press)
		{
			upFlug = false;
			downFlug = true;
			//RightPlayer();
		}
		else
		{
			downFlug = false;
		}
		//LeftPlayer();
	}
	if (RIGHT_Key == Press)
	{
		leftFlug = false;
		rightFlug = true;
		if (UP_Key == Press)
		{
			upFlug = true;
			downFlug = false;
			//LeftPlayer();
		}
		else
		{
			upFlug = false;
		}

		if (DOWN_Key == Press)
		{
			upFlug = false;
			downFlug = true;
			//RightPlayer();
		}
		else
		{
			downFlug = false;
		}
		//RightPlayer();
	}
}

void MovePlayer()
{
	KeyBoard();

	UpPlayer();
	DownPlayer();
	LeftPlayer();
	RightPlayer();
}

void MoveHole()
{
	for (int i = 0; i < HOLE; i++)
	{
		holePosY[i] += holeSpeed[i];
	}
}
void OutHole()
{
	for (int i = 0; i < HOLE; i++)
	{
		if (holePosY[i] >= 80 * (HOLE)-16)
		{
			holeAlive[i] = false;
		}
	}
}
void RespornHole()
{
	for (int i = 0; i < HOLE; i++)
	{
		if (holeAlive[i] == false)
		{
			holePosY[i] = -16;
			holePosX[i] = 100 * (rand() % (75 / 10)) + 250;
			holeAlive[i] = true;
		}
	}
}

bool ObjectCollision(int Obj1_x, int Obj1_y, int Obj1_xr, int Obj1_yr, int Obj2_x, int Obj2_y, int Obj2_xr, int Obj2_yr)
{
	if (Obj1_x - Obj1_xr < Obj2_x + Obj2_xr
		&& Obj2_x - Obj2_xr < Obj1_x + Obj1_xr
		&&
		Obj1_y - Obj1_yr < Obj2_y + Obj2_yr
		&& Obj2_y - Obj2_yr < Obj1_y + Obj1_yr)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool ObjectCollision(int Obj1_x, int Obj1_y, int Obj1_r, int Obj2_x, int Obj2_y, int Obj2_r)
{
	if (Obj1_x - Obj1_r < Obj2_x + Obj2_r
		&& Obj2_x - Obj2_r < Obj1_x + Obj1_r
		&&
		Obj1_y - Obj1_r < Obj2_y + Obj2_r
		&& Obj2_y - Obj2_r < Obj1_y + Obj1_r)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Bounding()
{
	if (CountHop >= 0
		&& CountHop < BoundHop)
	{
		return true;
	}
	return false;
}
bool MoveFlug()
{
	if (Bounding() == true)
	{
		return false;
	}
	return true;
}
void INit()
{

	int startCountHop = 800;

	timerGame += 1;
	if(Player.alive == true)
	{
		CountHop -= 20;
	}

	for (int i = 0; i < HOLE; i++)
	{
		//MoveHole();
		holePosY[i] += holeSpeed[i];
		OutHole();
		RespornHole();
	}

	if (Bounding() == true)
	{
		ResetFlug();
		PlR = 150;

		if (Player.posY <= WIN_HEIGHT - Player.XR)
		{
			Player.posY += holeSpeed[0];
		}

		ChackFlug();
	}
	else
	{
		PlR = 200;
		MovePlayer();
	}

	if (Bounding() == true)
	{
		for (int i = 0; i < HOLE; i++)
		{
			if (ObjectCollision(Player.posX, Player.posY, Player.CR, holePosX[i], holePosY[i], holePosCR[i]) == true)
			{
				CountHop = 50;
				Player.posX = holePosX[i];
				Player.posY = holePosY[i];
				Player.alive = false;
				//FallSoundFlug = true;
			}
			else if (Jumphole == true)
			{
				ScoreNow += 500;
			}

			Jumphole = false;
		}
	}
	else
	{
		for (int i = 0; i < HOLE; i++)
		{
			if (ObjectCollision(Player.posX, Player.posY, Player.CR, holePosX[i], holePosY[i], holePosCR[i]) == true)
			{
				Jumphole = true;
			}
		}
	}

	if (CountHop <= 0)
	{
		CountHop = startCountHop;
	}
	if (timerGame % 10 == 0)
	{
		ScoreNow += +timerGame / 10;
	}
	if (ScoreNow > HiScoreNow)
	{
		HiScoreNow = ScoreNow;
		HiScoreFlug = true;
	}
}