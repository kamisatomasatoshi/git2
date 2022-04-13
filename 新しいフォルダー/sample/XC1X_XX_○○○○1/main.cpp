#include "DxLib.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "variable.h"
#include "mapchip.h"
#include "shield.h"
#include "boomerang.h"
#include "boss.h"
#include "hit.h"



#define pi 3.14159
#define G           9.81                // 重力加速度

//enum shieldState {
//	nomal,		//0,通常時
//	scraped,	//1,削れた時
//	recharge,	//2,リチャージ時
//	crack,		//3,割れた時
//};

enum boomerangState {
	hold,			//0,プレイヤーが持っている時
	fly2target,		//1,ターゲットに向かって飛んでいる時
	stop,			//2,空中停止している時
	return2player,	//3,プレイヤーのもとに帰ってきている時
};


// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LC1B_23_ホソイタイセイ:タカミヲメザセ";


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

	backgroundBack = LoadGraph("resource/runnerbgFore.png");
	backgroundFore = LoadGraph("resource/runnerbgBack.png");
	backgroundSky = LoadGraph("resource/runnerbgSky.png");
	jumpPng = LoadGraph("resource/jumpMotion_64x96.png");
	jumpPngNB = LoadGraph("resource/jumpMotionNoneB.png");
	airJumpPng = LoadGraph("resource/airJump.png");
	airJumpPngNB = LoadGraph("resource/airJumpNoneB.png");
	charaIdlePng = LoadGraph("resource/charaIdle.png");
	charaIdleNBPng = LoadGraph("resource/charaIdleNoneB.png");
	stagePng = LoadGraph("resource/stage1.png");

	moveKeys = LoadGraph("resource/keys.png");
	moveKeysA = LoadGraph("resource/A_keys.png");
	moveKeysD = LoadGraph("resource/D_keys.png");
	spece = LoadGraph("resource/space.png");
	speceUse = LoadGraph("resource/space_use.png");

	mousenone = LoadGraph("resource/mouse.png");
	mouseRight = LoadGraph("resource/mouse_right.png");
	mouseLeft = LoadGraph("resource/mouse_left.png");
	notUse = LoadGraph("resource/not.png");
	boomerangIcon = LoadGraph("resource/boomerang.png");
	shieldIcon = LoadGraph("resource/shield.png");

	handPng = LoadGraph("resource/enemyHand.png");
	boomerangPng = LoadGraph("resource/boomerang2.png");

	int bossGraph = LoadGraph("resource/boss.png");

	int parryAtkAnmPng[9] = {};
	LoadDivGraph(
		"resource/parryAtkAnm.png",
		9, 9, 1, 100, 64,
		parryAtkAnmPng
	);

	LoadDivGraph(
		"resource/runAnmNoneB.png",
		4, 4, 1, 64, 64,
		runAnmNB
	);

	LoadDivGraph(
		"resource/runAnm.png",
		4, 4, 1, 64, 64,
		runAnm
	);

	LoadDivGraph(
		"resource/gameclearAnmS.png",
		7, 7, 1, 768, 512,
		gameClearAnm
	);

	//背景



	LoadDivGraph(
		"resource/maptipTile.png",
		20, 4, 5, 64, 64,
		mapchip
	);

	LoadDivGraph(
		"resource/roboRunAll.png",
		6, 6, 1, 32, 32,
		charaAnm
	);

	LoadDivGraph(
		"resource/roboRun.png",
		3, 3, 1, 32, 32,
		roboRunAnm
	);

	LoadDivGraph(
		"resource/roboIdle.png",
		2, 2, 1, 32, 32,
		roboIdleAnm
	);
	srand(time(nullptr));	//乱数の宣言





	enum mapInfo {
		NONE,	//0
		ground1	//1

	};

	//マップ
	const int MAP_COUNT_X = sizeof(map[0]) / sizeof(map[0][0]);
	const int MAP_COUNT_Y = sizeof(map) / sizeof(map[0]);

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i) {
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);
		GetMousePoint(&mouse_x, &mouse_y);
		int Mouse = GetMouseInput();


		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		//前のフレームの情報
		posOldX = (int)player.transform.x;
		posOldY = (int)player.transform.y;

		// 更新処理--------------------------------------------------------------------------//

		if (playerShield.parrynow <= 0) {
			//ブーメランのダメージを設定
			boomerang.damage = 5 * downCount;

#pragma region//ボスの更新処理

			MOVE_ROULETTE(bossAttackCoolTime, bossLeftHand, bossRightHand, bossAttackPattern, bossAttackCount);

			//敵の腕の動き
			ATK_MOVE(bossRightHand, player, bossAttackCoolTime, bossTimer, isShake);
			ATK_MOVE(bossLeftHand, player, bossAttackCoolTime, bossTimer, isShake);

			//ボスの弾
			BOSS_BULLET(player, bossFace, enemyBullet);

			ugoku += ugokuSpeed;
			if (10 <= ugoku) {
				ugokuSpeed *= -1;
			}
			else if (ugoku <= -10) {
				ugokuSpeed *= -1;
			}

			bossFace.posY = bossFace.initPosY + ugoku;

#pragma endregion//ボスの更新処理

#pragma region//プレイヤーの更新処理
#pragma region//移動処理
			if (keys[KEY_INPUT_D] == 1) {
				orientation = 1;
				isRun = 1;
				isIdle = 0;
				if (player.transform.x + playerRadius >= WIN_WIDTH) {
					isRightWallSlip = 1;
					isLeftWallSlip = 0;
				}
				else {
					isRightWallSlip = 0;
					isLeftWallSlip = 0;
				}
				if (player.speedX <= 10) {
					player.speedX += 1;
				}
				else if (player.speedX > 10) {
					player.speedX -= 1;
				}

			}
			else if (keys[KEY_INPUT_A] == 1) {
				orientation = 0;
				isRun = 1;
				isIdle = 0;
				if (player.transform.x - playerRadius <= 0) {
					player.transform.x = playerRadius;
					isLeftWallSlip = 1;
					isRightWallSlip = 0;
				}
				else {
					isLeftWallSlip = 0;
					isRightWallSlip = 0;
				}
				if (player.speedX >= -10) {
					player.speedX -= 1;
				}

			}
			else {
				isRun = 0;
				isIdle = 1;
				if (player.speedX != 0) {
					if (player.speedX > 0) {
						player.speedX -= 1;
					}
					else if (player.speedX < 0) {
						player.speedX += 1;
					}
				}
			}

			if (player.speedX > 10) {	//オーバースピード時減速
				player.speedX -= 1;
			}
			else if (player.speedX < -10) {
				player.speedX += 1;
			}

			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && isAirjump == 0 ||
				keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && isRightWallSlip == 1 ||
				keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && isLeftWallSlip == 1) {
				isJump = 1;

				if (map[leftBottomY][leftBottomX] == 0 && map[oldleftBottomY][oldleftBottomX] == 0 &&
					map[rightBottomY][rightBottomX] == 0 && map[oldrightBottomY][oldrightBottomX] == 0) {
					isAirjump = 1;
				}
				else {
					isAirjump = 0;
				}

				if (isRightWallSlip == 1) {
					player.transform.x -= 1;
					player.speedX -= 20;
				}
				else if (isLeftWallSlip == 1) {
					player.transform.x += 1;
					player.speedX += 20;
				}
				else {

				}
			}

			if (isJump == 1) {
				jumpCount += 1;
				if (jumpCount > 0) {
					player.transform.y -= (jumpHeight - 3 * jumpCount);
				}
			}

			if (jumpCount == 10) {
				jumpCount = 0;
				isJump = 0;
			}

			if (map[oldleftBottomY][leftBottomX] == 0 && map[leftBottomY][oldleftBottomX] == 0 &&
				map[oldrightBottomY][rightBottomX] == 0 && map[rightBottomY][oldrightBottomX] == 0) {
				isAir = 1;
			}
			else {
				isAir = 0;
			}


			if (map[rightBottomY][rightBottomX] == 0 && map[oldrightBottomY][oldrightBottomX] == 0 &&
				map[leftBottomY][leftBottomX] == 0 && map[oldleftBottomY][oldleftBottomX] == 0 && isJump == 0) {

				if (player.speedY <= 15) {
					player.speedY += 0.8;

				}
			}
			else {

				player.speedY = 2;

			}

			player.transform.y += (int)player.speedY;	//毎フレームの移動処理
			player.transform.x += (int)player.speedX;

#pragma endregion//移動処理
#pragma region//マップチップ
			leftTopX = ((int)player.transform.x - (int)player.transform.r) / BLOCK_SIZE;	//4点を求める
			leftTopY = ((int)player.transform.y - (int)player.transform.r) / BLOCK_SIZE;
			leftBottomX = ((int)player.transform.x - (int)player.transform.r) / BLOCK_SIZE;
			leftBottomY = ((int)player.transform.y + (int)player.transform.r - 1) / BLOCK_SIZE;
			rightTopX = ((int)player.transform.x + (int)player.transform.r - 1) / BLOCK_SIZE;
			rightTopY = ((int)player.transform.y - (int)player.transform.r) / BLOCK_SIZE;
			rightBottomX = ((int)player.transform.x + (int)player.transform.r - 1) / BLOCK_SIZE;
			rightBottomY = ((int)player.transform.y + (int)player.transform.r - 1) / BLOCK_SIZE;
			//---------------地上移動----------------//
			oldleftTopX = ((int)posOldX - (int)player.transform.r) / BLOCK_SIZE;
			oldleftTopY = ((int)posOldY - (int)player.transform.r) / BLOCK_SIZE;
			oldleftBottomX = ((int)posOldX - (int)player.transform.r) / BLOCK_SIZE;
			oldleftBottomY = ((int)posOldY + (int)player.transform.r - 1) / BLOCK_SIZE;
			oldrightTopX = ((int)posOldX + (int)player.transform.r - 1) / BLOCK_SIZE;
			oldrightTopY = ((int)posOldY - (int)player.transform.r) / BLOCK_SIZE;
			oldrightBottomX = ((int)posOldX + (int)player.transform.r - 1) / BLOCK_SIZE;
			oldrightBottomY = ((int)posOldY + (int)player.transform.r - 1) / BLOCK_SIZE;


			//マップチップ当たり判定
			if (map[leftTopY][leftTopX] >= 1 && map[leftTopY][leftTopX] <= 14) {
				if (map[leftTopY][leftTopX] >= 9 && map[leftTopY][leftTopX] <= 13 && isInvincible == 0) {
					playerLife -= 1;
					isInvincible = 1;
				}
				if (map[oldleftTopY][leftTopX] == 0 && map[leftTopY][oldleftTopX] == 0) {

				}
				else if (map[oldleftTopY][leftTopX] == 0 && map[leftTopY][oldleftTopX] >= 1) {
					player.transform.y = (int)posOldY;

				}
				else if (map[oldleftTopY][leftTopX] >= 1 && map[leftTopY][oldleftTopX] == 0) {
					player.transform.x = (int)posOldX;
					player.speedX = 0;
				}
				else if (map[oldleftTopY][leftTopX] >= 1 && map[leftTopY][oldleftTopX] >= 1) {
					player.transform.y = (int)posOldY;
					player.transform.x = (int)posOldX;

				}
			}

			if (map[leftBottomY][leftBottomX] == 0 && map[leftBottomY][leftBottomX] >= 15//橋
				) {
				if (oldleftBottomY < leftBottomY) {
					player.transform.y = ((int)player.transform.y / BLOCK_SIZE + 1) * BLOCK_SIZE - (int)player.transform.r - 1;
				}
			}
			if (map[rightBottomY][rightBottomX] == 0 && map[rightBottomY][rightBottomX] >= 15//橋
				) {
				if (oldrightBottomY < rightBottomY) {
					player.transform.y = ((int)player.transform.y / BLOCK_SIZE + 1) * BLOCK_SIZE - (int)player.transform.r - 1;
				}
			}


			if (map[leftBottomY][leftBottomX] >= 1 && map[leftBottomY][leftBottomX] <= 14) {
				if (map[leftBottomY][leftBottomX] >= 9 && map[leftBottomY][leftBottomX] <= 13 && isInvincible == 0) {
					playerLife -= 1;
					isInvincible = 1;
				}
				if (map[oldleftBottomY][leftBottomX] == 0 && map[leftBottomY][oldleftBottomX] == 0) {

				}
				else if (map[oldleftBottomY][leftBottomX] == 0 && map[leftBottomY][oldleftBottomX] >= 1) {
					player.transform.y = ((int)player.transform.y / BLOCK_SIZE + 1) * BLOCK_SIZE - (int)player.transform.r - 1;
					isAirjump = 0;
					isAir = 0;
				}
				else if (map[oldleftBottomY][leftBottomX] >= 1 && map[leftBottomY][oldleftBottomX] == 0) {
					player.transform.x = (int)posOldX;
					player.speedX = 0;
				}
				else if (map[oldleftBottomY][leftBottomX] >= 1 && map[leftBottomY][oldleftBottomX] >= 1) {
					player.transform.y = (int)posOldY;
					player.transform.x = (int)posOldX;
				}
			}


			if (map[rightBottomY][rightBottomX] >= 1 && map[rightBottomY][rightBottomX] <= 14) {
				if (map[rightBottomY][rightBottomX] >= 9 && map[rightBottomY][rightBottomX] <= 13 && isInvincible == 0) {
					playerLife -= 1;
					isInvincible = 1;
				}
				if (map[oldrightBottomY][rightBottomX] == 0 && map[rightBottomY][oldrightBottomX] == 0) {

				}
				else if (map[oldrightBottomY][rightBottomX] == 0 && map[rightBottomY][oldrightBottomX] >= 1) {
					player.transform.y = ((int)player.transform.y / BLOCK_SIZE + 1) * BLOCK_SIZE - (int)player.transform.r - 1;
					isAirjump = 0;
					isAir = 0;
				}
				else if (map[oldrightBottomY][rightBottomX] >= 1 && map[rightBottomY][oldrightBottomX] == 0) {
					player.transform.x = (int)posOldX;
					player.speedX = 0;
				}
				else if (map[oldrightBottomY][rightBottomX] >= 1 && map[rightBottomY][oldrightBottomX] >= 1) {
					player.transform.y = (int)posOldY;
					player.transform.x = (int)posOldX;
				}
			}


			if (map[rightTopY][rightTopX] >= 1 && map[rightTopY][rightTopX] <= 14) {
				if (map[rightTopY][rightTopX] >= 9 && map[rightTopY][rightTopX] <= 13 && isInvincible == 0) {
					playerLife -= 1;
					isInvincible = 1;
				}
				if (map[oldrightTopY][rightTopX] == 0 && map[rightTopY][oldrightTopX] == 0) {

				}
				else if (map[oldrightTopY][rightTopX] == 0 && map[rightTopY][oldrightTopX] >= 1) {
					player.transform.y = (int)posOldY;
				}
				else if (map[oldrightTopY][rightTopX] >= 1 && map[rightTopY][oldrightTopX] == 0) {
					player.transform.x = (int)posOldX;
					player.speedX = 0;
				}
				else if (map[oldrightTopY][rightTopX] >= 1 && map[rightTopY][oldrightTopX] >= 1) {
					player.transform.y = (int)posOldY;
					player.transform.x = (int)posOldX;
				}
			}
#pragma endregion//マップチップ

			GetMousePoint(&mouseStructure.x, &mouseStructure.y);

			PlayerShield(	//シールド関数
				player,
				playerShield,
				mouseStructure,
				boomerang
			);

			PlayerBoomerang(player, boomerang, mouseStructure, target, isAirjump);	//ブーメラン関数

			if (player.transform.x + player.transform.r >= WIN_WIDTH) {	//横の画面外に進まない処理
				player.transform.x = WIN_WIDTH - player.transform.r;
			}
			if (player.transform.x - player.transform.r <= 0) {
				player.transform.x = player.transform.r;
			}
#pragma endregion//プレイヤーの更新処理

			//当たり判定
			HitDecision(player, boomerang, playerShield, bossLeftHand, bossRightHand, bossFace, enemyBullet, downCount);
		}

		//パリィの時
		if (playerShield.isParry == 1) {		//パリィ状態のフラグをtrueの時
			playerShield.parrynow--;			//パリィ成功時のタイマーをデクリメント
			playerShield.isShieldOn = false;
			isShake = 1;

			if (playerShield.parrynow <= 0) {	//パリィ成功時のタイマーが0以下になったら
				playerShield.isParry = 0;		//パリィ状態のフラグをfalseにする
				playerShield.parrynow = 0;		//パリィ成功時のタイマーを0にする
				player.transform.x += cos(playerShield.crros[0].angle) * 200;	//カーソル方向にワープ
				player.transform.y += sin(playerShield.crros[0].angle) * 200;
			}
		}

#pragma region//コメントアウトで保留されてるやつ
		//無敵判定
		/*if (isInvincible == 1) {
			invinsibleTimer++;
			if (invinsibleTimer >= 70) {
				invinsibleTimer = 0;
				isInvincible = 0;
			}
		}

		//ゲームーバー処理
		if (playerLife <= 0 && gameOverAnmTimer < 21) {
			gameOverAnmTimer++;
			if (gameOverAnmTimer == 20) {
				gameOverAnmTimer = 0;
				scene = 2;
			}
		}*/



		//	break;

		//case 2:
		//	if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0) {
		//		playerLife = 5;	//ヒットポイント
		//		player.transform.x = 470;	//X座標の位置
		//		player.transform.y = 3072;	//Y座標の位置
		//		posOldX = 0;
		//		posOldY = 0;
		//		player.speedX = 0;	//X座標のスピード
		//		player.speedY = 0;	//Y座標のスピード
		//		leftTopX = 0;
		//		leftTopY = 0;
		//		leftBottomX = 0;
		//		leftBottomY = 0;
		//		rightTopX = 0;
		//		rightTopY = 0;
		//		rightBottomX = 0;
		//		rightBottomY = 0;
		//		player.transform.r = 16;
		//		oldleftTopX = 0;
		//		oldleftTopY = 0;
		//		oldleftBottomX = 0;
		//		oldleftBottomY = 0;
		//		oldrightTopX = 0;
		//		oldrightTopY = 0;
		//		oldrightBottomX = 0;
		//		oldrightBottomY = 0;
		//		rightScrStartX = 470;	//スクロール開始の位置
		//		leftScrStartX = 350;
		//		upScrStartY = 150;	//スクロール開始の位置
		//		downScrStartY = 460;
		//		scrollX = 0;	//スクロール値
		//		scrollY = 2800;
		//		Screenplayer.transform.x = 0;	//画面上での自機の位置
		//		jumpCount = 0;
		//		jumpHeight = 39;
		//		isJump = 0;
		//		isAirjump = 0;
		//		isIdle = 0;
		//		isRun = 0;
		//		isLeftRun = 0;
		//		isAir = 0;
		//		isRightWallSlip = 0;
		//		isLeftWallSlip = 0;
		//		isInvincible = 0;
		//		cAnimCount = 0;
		//		orientation = 0;
		//		scene = 0;
		//	}
		//	break;


		//case 3:
		//	if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0) {
		//		playerLife = 5;	//ヒットポイント
		//		player.transform.x = 470;	//X座標の位置
		//		player.transform.y = 3072;	//Y座標の位置
		//		posOldX = 0;
		//		posOldY = 0;
		//		player.speedX = 0;	//X座標のスピード
		//		player.speedY = 0;	//Y座標のスピード
		//		leftTopX = 0;
		//		leftTopY = 0;
		//		leftBottomX = 0;
		//		leftBottomY = 0;
		//		rightTopX = 0;
		//		rightTopY = 0;
		//		rightBottomX = 0;
		//		rightBottomY = 0;
		//		player.transform.r = 16;
		//		oldleftTopX = 0;
		//		oldleftTopY = 0;
		//		oldleftBottomX = 0;
		//		oldleftBottomY = 0;
		//		oldrightTopX = 0;
		//		oldrightTopY = 0;
		//		oldrightBottomX = 0;
		//		oldrightBottomY = 0;
		//		rightScrStartX = 470;	//スクロール開始の位置
		//		leftScrStartX = 350;
		//		upScrStartY = 150;	//スクロール開始の位置
		//		downScrStartY = 460;
		//		scrollX = 0;	//スクロール値
		//		scrollY = 2800;
		//		Screenplayer.transform.x = 0;	//画面上での自機の位置
		//		jumpCount = 0;
		//		jumpHeight = 39;
		//		isJump = 0;
		//		isAirjump = 0;
		//		isIdle = 0;
		//		isRun = 0;
		//		isLeftRun = 0;
		//		isAir = 0;
		//		isRightWallSlip = 0;
		//		isLeftWallSlip = 0;
		//		isInvincible = 0;
		//		cAnimCount = 0;
		//		orientation = 0;
		//		scene = 0;
		//	}

		//	break;
		//}
#pragma endregion//コメントアウトで保留されてるやつ

		// 描画処理-----------------------------------------//

		if (isShake == 1) {
			randomX = GetRand(shakeTimer);	//シェイクの処理
			randomY = GetRand(shakeTimer);
			shakeTimer -= 2;
			if (shakeTimer <= 0) {
				randomX = 0;
				randomY = 0;
				shakeTimer = 10;
				isShake = 0;
			}
		}

		/*switch (scene) {
		case 0:
			DrawGraph(0, 0, startScreen[startSceneTimer / 5 % 2], true);
			break;

		case 1:*/
		//背景
		/*DrawGraph(-(scrollX / 15), 0, backgroundSky, true);
		DrawGraph(-(scrollX / 15 - 768), 0, backgroundSky, true);
		DrawGraph(-(scrollX / 10), 0, backgroundFore, true);
		DrawGraph(-(scrollX / 10 - 768), 0, backgroundFore, true);
		DrawGraph(-scrollX / 5, 0, backgroundBack, true);
		DrawGraph(-(scrollX / 5 - 768), 0, backgroundBack, true);*/


		DrawGraph(0 + randomX, 556 + randomY, stagePng, true);

#pragma region//敵の描画
		if (bossFace.hitPoint > 0) {	//顔の描画
			//DrawBox(bossFace.posX - bossFace.radius,
			//	bossFace.posY - bossFace.radius,
			//	bossFace.posX + bossFace.radius,
			//	bossFace.posY + bossFace.radius,
			//	GetColor(100, 255, 100), false);

			DrawGraph(bossFace.posX - bossFace.radius, bossFace.posY - bossFace.radius, bossGraph, true);

			DrawBox(0,
				0,
				WIN_WIDTH,
				30,
				GetColor(100, 100, 100), true);
			DrawBox(5,
				5,
				WIN_WIDTH - 5,
				25,
				GetColor(255, 50, 50), true);

			DrawBox(5,
				5,
				((float)WIN_WIDTH - 5) / 2000 * bossFace.hitPoint,
				25,
				GetColor(50, 255, 50), true);
		}

		if (bossLeftHand.hitPoint > 0) {	//左手の描画
			/*DrawBox(bossLeftHand.posX - bossLeftHand.radius,
				bossLeftHand.posY - bossLeftHand.radius,
				bossLeftHand.posX + bossLeftHand.radius,
				bossLeftHand.posY + bossLeftHand.radius,
				GetColor(100, 100, 255), false);*/
			DrawRotaGraph(bossLeftHand.posX + randomX, bossLeftHand.posY + randomY, 1.0, 0, handPng, true, 1.0);

			DrawBox(bossLeftHand.posX + randomX - 50,
				bossLeftHand.posY + randomY - bossLeftHand.radius - 20,
				bossLeftHand.posX + randomX + 50,
				bossLeftHand.posY + randomY - bossLeftHand.radius - 15,
				GetColor(255, 50, 50), true);

			DrawBox(bossLeftHand.posX + randomX - 50,
				bossLeftHand.posY + randomY - bossLeftHand.radius - 20,
				bossLeftHand.posX + randomX - 50 + bossLeftHand.hitPoint,
				bossLeftHand.posY + randomY - bossLeftHand.radius - 15,
				GetColor(50, 255, 50), true);
		}

		if (bossRightHand.hitPoint > 0) {	//右手の描画
			/*DrawBox(bossRightHand.posX - bossRightHand.radius,
				bossRightHand.posY - bossRightHand.radius,
				bossRightHand.posX + bossRightHand.radius,
				bossRightHand.posY + bossRightHand.radius,
				GetColor(255, 100, 100), false);*/
			DrawRotaGraph(bossRightHand.posX + randomX, bossRightHand.posY + randomY, 1.0, 0, handPng, true, 0);
			DrawBox(bossRightHand.posX + randomX - 50,
				bossRightHand.posY + randomY - bossRightHand.radius - 20,
				bossRightHand.posX + randomX + 50,
				bossRightHand.posY + randomY - bossRightHand.radius - 15,
				GetColor(255, 50, 50), true);
			DrawBox(bossRightHand.posX + randomX - 50,
				bossRightHand.posY + randomY - bossRightHand.radius - 20,
				bossRightHand.posX + randomX - 50 + bossRightHand.hitPoint,
				bossRightHand.posY + randomY - bossRightHand.radius - 15,
				GetColor(50, 255, 50), true);
		}

		for (int i = 0; i < MAP_COUNT_X; i++) {
			for (int j = 0; j < MAP_COUNT_Y; j++) {
				for (int k = 1; k < 17; k++) {
					if (map[j][i] == k) {
						DrawGraph(i * blockSize, j * blockSize, mapchip[k], true);
					}
				}

			}
		}

		if (enemyBullet.isShot == 1) {
			DrawCircle(
				enemyBullet.object.transform.x,
				enemyBullet.object.transform.y,
				enemyBullet.object.transform.r,
				GetColor(255, 100, 100), true
			);
		}

		if (bossRightHand.attackType == 5 &&
			bossLeftHand.attackType == 6) {
			if (bossLeftHand.atk.moveFaze == 2) {
				if (0 < bossTimer && bossTimer <= 30) {
					DrawLine(
						bossLeftHand.posX + randomX - bossLeftHand.radius, 0,
						bossLeftHand.posX + randomX - bossLeftHand.radius, 768 - 192,
						GetColor(255, 50, 50), true);
					DrawLine(
						bossRightHand.posX + randomX + bossRightHand.radius, 0,
						bossRightHand.posX + randomX + bossRightHand.radius, 768 - 192,
						GetColor(255, 50, 50), true);

					DrawBox(
						bossLeftHand.posX + randomX + bossLeftHand.radius, 200,
						bossRightHand.posX + randomX - bossRightHand.radius, 350,
						GetColor(255, 50, 50), true);

					DrawBox(
						bossLeftHand.posX + randomX + bossLeftHand.radius, 400,
						bossRightHand.posX + randomX - bossRightHand.radius, 450,
						GetColor(255, 50, 50), true);
				}
			}
		}
#pragma endregion//敵の描画

#pragma region//シールド
		if (boomerang.isThrown == false) {
			//if (playerShield.isShieldOn == 0) {
			//	DrawLine(player.transform.x + randomX, player.transform.y + randomY, playerShield.point1.x + randomX, playerShield.point1.y + randomY, GetColor(255, 255, 255));
			//	DrawLine(playerShield.point1.x + randomX, playerShield.point1.y + randomY, playerShield.point2.x + randomX, playerShield.point2.y + randomY, GetColor(255, 255, 255));
			//	DrawLine(playerShield.point2.x + randomX, playerShield.point2.y + randomY, player.transform.x + randomX, player.transform.y + randomY, GetColor(255, 255, 255));
			//}
			if (playerShield.isShieldOn == 1) {
				DrawLine(player.transform.x + randomX, player.transform.y + randomY, playerShield.point1.x + randomX, playerShield.point1.y + randomY, GetColor(255, 255, 255));
				DrawLine(playerShield.point2.x + randomX, playerShield.point2.y + randomY, player.transform.x + randomX, player.transform.y + randomY, GetColor(255, 255, 255));
				DrawLine(playerShield.point1.x + randomX, playerShield.point1.y + randomY, playerShield.point2.x + randomX, playerShield.point2.y + randomY, GetColor(255, 255, 255));
				for (int i = 0; i < 16; i++) {
					if (playerShield.crros[i].first < 0) {
						DrawLine(player.transform.x + randomX, player.transform.y + randomY, playerShield.point1.x + randomX, playerShield.point1.y + randomY, GetColor(255, 255, 255));
					}
					if (playerShield.crros[i].seccond < 0) {
						DrawLine(playerShield.point1.x + randomX, playerShield.point1.y + randomY, playerShield.point2.x + randomX, playerShield.point2.y + randomY, GetColor(255, 255, 255));
					}
					if (playerShield.crros[i].third < 0) {
						DrawLine(playerShield.point2.x + randomX, playerShield.point2.y + randomY, player.transform.x + randomX, player.transform.y + randomY, GetColor(255, 255, 255));
					}
				}
			}
		}
#pragma endregion//シールド

#pragma region//ブーメラン
		/*if (boomerang.isThrown == true) {
			DrawTriangle(
				boomerang.object.transform.x + boomerang.object.transform.r * cos(pi / 3 * 2),
				boomerang.object.transform.y + boomerang.object.transform.r * sin(pi / 3 * 2),
				boomerang.object.transform.x + boomerang.object.transform.r * cos(pi / 3 * 4),
				boomerang.object.transform.y + boomerang.object.transform.r * sin(pi / 3 * 4),
				boomerang.object.transform.x + boomerang.object.transform.r * cos(pi / 3 * 6),
				boomerang.object.transform.y + boomerang.object.transform.r * sin(pi / 3 * 6),
				GetColor(255, 255, 0), true
			);
		}*/

		if (boomerang.isThrown == true) {
			boomerangAngle += 0.5;

			DrawRotaGraph(boomerang.object.transform.x + randomX, boomerang.object.transform.y + randomY, 0.8, boomerangAngle, boomerangPng, true, 0);
		}
		else {
			boomerangAngle = 0.0;
		}

#pragma endregion//ブーメラン

#pragma region//ターゲット
		if (boomerang.isThrown == false) {
			DrawCircle(target.x + randomX, target.y + randomY, 5, GetColor(255, 255, 255), false);
			DrawCircle(target.x + randomX, target.y + randomY, 10, GetColor(255, 255, 255), false);
			DrawLine(target.x + randomX, target.y + randomY, target.x + randomX + 20, target.y + randomY, GetColor(255, 255, 255), true);
			DrawLine(target.x + randomX, target.y + randomY, target.x + randomX - 20, target.y + randomY, GetColor(255, 255, 255), true);
			DrawLine(target.x + randomX, target.y + randomY, target.x + randomX, target.y + 20 + randomY, GetColor(255, 255, 255), true);
			DrawLine(target.x + randomX, target.y + randomY, target.x + randomX, target.y - 20 + randomY, GetColor(255, 255, 255), true);
		}
		else if (boomerang.isThrown == true) {
			DrawCircle(target.x + randomX, target.y, 5, GetColor(255, 255, 0), false);
			DrawCircle(target.x + randomX, target.y, 10, GetColor(255, 255, 0), false);
			DrawLine(target.x + randomX, target.y, target.x + randomX + 20, target.y + randomY, GetColor(255, 255, 0), true);
			DrawLine(target.x + randomX, target.y, target.x + randomX - 20, target.y + randomY, GetColor(255, 255, 0), true);
			DrawLine(target.x + randomX, target.y, target.x + randomX, target.y + 20 + randomY, GetColor(255, 255, 0), true);
			DrawLine(target.x + randomX, target.y, target.x + randomX, target.y - 20 + randomY, GetColor(255, 255, 0), true);
		}
#pragma endregion//ターゲット

#pragma region//プレイヤー
		//　ライン描画
		/*DrawBox(player.transform.x - player.transform.r,
			player.transform.y - player.transform.r,
			player.transform.x + player.transform.r,
			player.transform.y + player.transform.r,
			GetColor(255, 255, 255), true);*/
		if (isAir == 0) {
			if (isIdle == 1) {	//アイドル時
				cAnimCount = 0;


				if (boomerang.state == hold) {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY - 12/*中心にyを揃えるため*/, 1.0, 0, charaIdlePng, TRUE, orientation);
				}
				else {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY - 12, 1.0, 0, charaIdleNBPng, TRUE, orientation);
				}

			}
			else if (isRun == 1) {	//走っているとき
				cAnimCount++;
				if (cAnimCount >= 16) {
					cAnimCount = 0;
				}
				if (boomerang.state == hold) {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY - 12, 1.0, 0, runAnm[cAnimCount / 4], TRUE, orientation);
				}
				else {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY - 12, 1.0, 0, runAnmNB[cAnimCount / 4], TRUE, orientation);
				}
			}
		}
		else {
			if (isAirjump == 0) {	//空中
				if (boomerang.state == hold) {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY, 1.0, 0, jumpPng, TRUE, orientation);
				}
				else {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY, 1.0, 0, jumpPngNB, TRUE, orientation);
				}
			}
			else if (isAirjump == 1) {	//2段ジャンプ時

				if (orientation == 1) {	//方向
					airJumpCharaAngle += 0.7;
				}
				else {
					airJumpCharaAngle -= 0.7;
				}

				if (boomerang.state == hold) {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY + 12, 1.0, airJumpCharaAngle, airJumpPng, TRUE, orientation);

				}
				else {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY, 1.0, airJumpCharaAngle, airJumpPngNB, TRUE, orientation);

				}
			}
			else {
				airJumpCharaAngle = 0.0;
			}

		}
#pragma endregion//プレイヤー

#pragma region//UI
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
		if (mouseStructure.isLeftPush == true)
		{
			//ブーメラン攻撃
			DrawGraph(1080, 650, mouseLeft, TRUE);
		}
		if (mouseStructure.isRightPush == true)
		{
			//ガード
			DrawGraph(1080, 650, mouseRight, TRUE);
		}

		//ブーメラン表示
		DrawGraph(1000, 650, boomerangIcon, TRUE);

		//シールドの表示
		DrawGraph(1140, 650, shieldIcon, TRUE);

		if (boomerang.isThrown == true)//もし、ブーメランを投げてしまっていたら。
		{
			DrawGraph(1000, 650, notUse, TRUE);
			DrawGraph(1140, 650, notUse, TRUE);
		}

		if (isAirjump == true) {
			DrawGraph(1000, 650, notUse, TRUE);
		}

		if (playerShield.state == crack) {
			DrawGraph(1140, 650, notUse, TRUE);
		}

		if (playerShield.parrynow > 0) {
			parryAtkAnmTimer++;
			if (parryAtkAnmTimer >= 27) {
				parryAtkAnmTimer = 0;
			}
			DrawRotaGraph(player.transform.x + cos(playerShield.crros[0].angle) * 100,
				player.transform.y + sin(playerShield.crros[0].angle) * 100,
				1.5, playerShield.crros[0].angle, parryAtkAnmPng[parryAtkAnmTimer / 3], TRUE, 1.0);

		}
		else {
			parryAtkAnmTimer = 0;
		}

#pragma endregion//UI

#pragma region//確認用
		DrawFormatString(0, 30 + 0, GetColor(255, 255, 255), "HP = %d", player.hp);
		DrawFormatString(0, 30 + 15 * 1, GetColor(255, 255, 255), "playerShield.isShieldOn:%d", playerShield.isShieldOn);
		DrawFormatString(0, 30 + 15 * 2, GetColor(255, 255, 255), "shieldtate:%d", playerShield.state);
		DrawFormatString(0, 30 + 15 * 3, GetColor(255, 255, 255), "shield:%f", playerShield.level);
		DrawFormatString(0, 30 + 15 * 4, GetColor(255, 255, 255), "playerShield.rechargeTimer:%d", playerShield.rechargeTimer);
		DrawFormatString(0, 30 + 15 * 5, GetColor(255, 255, 255), "isParry:%d", playerShield.isParry);
		DrawFormatString(0, 30 + 15 * 6, GetColor(255, 255, 255), "parryTimer:%d", playerShield.parryTimer);
		DrawFormatString(0, 30 + 15 * 7, GetColor(255, 255, 255), "parrynow:%d", playerShield.parrynow);
		DrawFormatString(0, 30 + 15 * 8, GetColor(255, 255, 255), "boomerangState:%d", boomerang.state);
		DrawFormatString(0, 30 + 15 * 9, GetColor(255, 255, 255), "bossAttackCount:%d", bossAttackCount);
		DrawFormatString(0, 30 + 15 * 10, GetColor(255, 255, 255), "bossHandLHP:%d", bossLeftHand.hitPoint);
		DrawFormatString(0, 30 + 15 * 11, GetColor(255, 255, 255), "bossHandRHP:%d", bossRightHand.hitPoint);

#pragma endregion

		//	break;

		//case 2:
		//	//--------------ゲームオーバー画面--------------//
		//	if (gameOverAnmTimer != 6) {
		//		gameOverAnmTimer++;
		//	}

		//	DrawGraph(0, 0, gameOverAnm[gameOverAnmTimer], true);
		//	DrawFormatString(320, 390, GetColor(255, 255, 255), "ENTER TO RESET");
		//	break;
		//case 3:
		//	if (gameOverAnmTimer != 6) {
		//		gameOverAnmTimer++;
		//	}

		//	DrawGraph(0, 0, gameClearAnm[gameOverAnmTimer], true);
		//	DrawFormatString(320, 390, GetColor(255, 255, 255), "ENTER TO RESET");
		//	break;


		//}


		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似50FPS)
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

	InitGraph();

	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}