#include "DxLib.h"
#include "Object.h"
#include "Player.h"
#include "maptip.h"

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

	Transform playerTransform =
	{
		100.0f,
		100.0f,
		0.0f,
		0.0f,
		16.0f,
		16.0f,
		2.0f,
		2.0f
	};
	Transform objectTransform =
	{
		100.0f,
		100.0f,
		0.0f,
		0.0f,
		16.0f,
		16.0f,
		2.0f,
		2.0f
	};

	CollisionPoint collsionPoint =
	{
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	};

	// ゲームループで使う変数の宣言
	
	int scene = 0;

	//インスタンスの生成
	Object* object = new Object(objectTransform);
	Player* player = new Player(playerTransform, collsionPoint);

	// ゲームループ
	while (true)
	{
		//キー入力
		KeyUpdate();

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		player->PlayerMove();

		//switch (scene)//処理
		//{
		//case0://スタート

		//	break;

		//case1://ゲーム

		//	break;

		//case2://クリア

		//	break;

		//case3://オーバー

		//	break;

		//	
		//}
		// 描画処理
		switch (scene)
		{
		case0://スタート
			DrawGraph(player->transform.posX - player->transform.radiusX, player->transform.posY - player->transform.radiusY, playerHandle, TRUE);
			break;

		case1://ゲーム

			break;

		case2://クリア

			break;

		case3://オーバー

			break;

			
		}

		

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
