#include "DxLib.h"
#include "shield.h"
#include <math.h>

//円周率
const double pi = 3.141592;

////シールドの状態のenum
//enum shieldState {
//	nomal,		//0,通常時
//	scraped,	//1,削れた時
//	recharge,	//2,リチャージ時
//	crack,		//3,割れた時
//};

void PlayerShield(
	Object& player,
	Shield& playerShield,
	Mouse& mouseStructure,
	Boomerang& boomerang
) {

	//angleの値を取得
	playerShield.crros[0].angle = atan2((double)mouseStructure.y - player.transform.y, (double)mouseStructure.x - player.transform.x);

	//三角形の頂点の位置を取得
	playerShield.point1.x = player.transform.x + cos(playerShield.crros[0].angle + pi / 6 * playerShield.level / playerShield.max) * playerShield.radius;
	playerShield.point1.y = player.transform.y + sin(playerShield.crros[0].angle + pi / 6 * playerShield.level / playerShield.max) * playerShield.radius;
	playerShield.point2.x = player.transform.x + cos(playerShield.crros[0].angle - pi / 6 * playerShield.level / playerShield.max) * playerShield.radius;
	playerShield.point2.y = player.transform.y + sin(playerShield.crros[0].angle - pi / 6 * playerShield.level / playerShield.max) * playerShield.radius;

	int mouse = GetMouseInput();

	if (boomerang.isThrown == false) {
		// マウスの右ボタンが押されてるとき
		if (mouse & MOUSE_INPUT_RIGHT) {
			if (0 < playerShield.level) {
				if (mouseStructure.isRightPush == false) {//押し始めなら
					//押されてるフラグをtrue
					mouseStructure.isRightPush = true;
					playerShield.level -= 10;				//シールド展開時の消費
					playerShield.parryTimer = 5;			//パリィのタイマーに5を代入

					playerShield.isShieldOn = true;			//シールド展開のフラグをtrueにする
					if (playerShield.level <= 0) {			//もしシールド残量が0以下だったら
						playerShield.level = 0;				//シールド残量を0にして
						playerShield.state = crack;			//シールドの状態を割れた時にする
						playerShield.rechargeTimer = 500;	//シールドリチャージのタイマーに500(10秒)を代入
					}
				}
				//　前フレームから右ボタンが
				//　押され続けている時はelseに来る
				else {
					playerShield.level--;					//毎フレームシールド残量をデクリメント
					playerShield.state = scraped;			//シールドの状態を削れた時にする
					playerShield.rechargeTimer = 250;		//シールドリチャージのタイマーに250(5秒)を代入
					if (0 < playerShield.parryTimer) {		//パリィタイマーが0より大きければ
						playerShield.parryTimer--;			//パリィタイマーをデクリメント
					}
					if (playerShield.level <= 0) {			//シールド残量が0以下になったら
						playerShield.level = 0;				//シールド残量を0にして
						playerShield.state = crack;			//シールドの状態を割れた時にする
						playerShield.rechargeTimer = 500;	//シールドリチャージのタイマーに500(10秒)を代入
					}
				}
			}
		}
		//右ボタン押されてない場合
		else {
			if (mouseStructure.isRightPush == true) {	//押されてるフラグがtrueの時
				mouseStructure.isRightPush = false;		//押されてるフラグfalseにする
				playerShield.isShieldOn = false;		//シールド展開のフラグをfalseにする
			}
		}
	}

	if (playerShield.state == scraped) {			//シールドの状態が削れた時なら
		playerShield.rechargeTimer--;				//シールドリチャージタイマーをデクリメント
		if (playerShield.rechargeTimer <= 0) {		//シールドリチャージタイマーが0以下なら
			playerShield.state = recharge;			//シールドの状態をリチャージ時にする
		}
	}
	else if (playerShield.state == recharge) {			//シールドの状態がリチャージ時なら
		playerShield.level++;							//シールド残量をインクリメント
		if (playerShield.max <= playerShield.level) {	//シールド残量が最大値以上になったら
			playerShield.level = playerShield.max;		//シールド残量を最大値に合わせる
			playerShield.state = nomal;					//シールドの状態を通常時にする
		}
	}
	else if (playerShield.state == crack) {			//シールドの状態が割れた時なら
		playerShield.rechargeTimer--;				//シールドリチャージタイマーをデクリメント
		if (playerShield.rechargeTimer <= 0) {		//シールドリチャージタイマーが0以下なら
			playerShield.state = recharge;			//シールドの状態をリチャージ時にする
		}
		playerShield.isShieldOn = false;			//シールド展開のフラグをfalseにする
	}
}