#include "DxLib.h"
#include "Object.h"
#include "Player.h"
#include "maptip.h"
#include "Struct.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
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
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み

	int blockHandle = 0;
	blockHandle = LoadGraph("resource/block.png");

	int playerHandle = 0;
	playerHandle = LoadGraph("resource/test_player.png");

	// ゲームループで使う変数の宣言
	
	int scene = 0;

	//インスタンスの生成
	//Object *object = new Object(objectTransform);
	Player* player = new Player();

	// ゲームループ
	while (true)
	{
		//キー入力
		KeyUpdate();

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		//更新処理
		if (scene == 0 || scene == 1 )
		{
		player->PlayerMove();

		}

		//描画処理
		
		switch (scene)
		{
		case 0://スタート
			if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0)
			{
				scene = 1;
			}
			DrawGraph(player->object->transform.posX - player->object->transform.radiusX, player->object->transform.posY - player->object->transform.radiusY, playerHandle, TRUE);
			break;

		case 1://ゲーム
			if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0)
			{
				scene = 2;
			}
			DrawFormatString(400, 600, GetColor(255, 255, 255), "scene:%d", scene);
			break;

		case 2://ポーズ
			if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0)
			{
				scene = 3;
			}
			DrawFormatString(0, 0, GetColor(255, 255, 255), "POUSE");
			break;

		case 3://クリア
			if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0)
			{
				scene = 4;
			}
			DrawFormatString(0, 0, GetColor(255, 255, 255), "ゲームクリア！");
			break;

		case 4://オーバー
			if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0)
			{
				scene = 0;
			}
			DrawFormatString(0, 0, GetColor(255, 255, 255), "オーバー…");
			break;

		};
		if (scene == 0 || scene == 1 || scene == 2)
		{
			for (int x = 0; x < MAP_WIDTH; x++)
			{
				for (int y = 0; y < MAP_HEIGHT; y++)
				{
					if (map[y][x] == BLOCK)
					{
						DrawGraph(x * BLOCK_SIZE, y * BLOCK_SIZE, blockHandle, TRUE);
					}
				}
			}


			player->PlayerDraw();
		}

		DrawFormatString(400, 600, GetColor(255, 255, 255), "scene:%d", scene);
		//DrawFormatString(400, 620, GetColor(255, 255, 255), "speedY %f", player->transform.speedY);

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}

	DeleteGraph(blockHandle);
	DeleteGraph(playerHandle);


	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}












