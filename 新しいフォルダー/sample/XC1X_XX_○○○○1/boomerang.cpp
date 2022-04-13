#include "DxLib.h"
#include "boomerang.h"

//円周率
const double pi = 3.141592;

//ブーメランの状態のenum
enum boomerangState {
	hold,			//0,プレイヤーが持っている時
	fly2target,		//1,ターゲットに向かって飛んでいる時
	return2player,	//2,プレイヤーのもとに帰ってきている時
};

void PlayerBoomerang(Object& player, Boomerang& boomerang, Mouse& mouseStructure, Transform& target, int isAirjump) {

	if (boomerang.isThrown == false) {
		//ターゲットの位置をマウスの位置に合わせる
		//target.x = mouseStructure.x;
		//target.y = mouseStructure.y;

		if (mouseStructure.x - 20 <= 0) {
			target.x = 0 + 20;
		}
		else if (mouseStructure.x + 20 >= 1280) {
			target.x = 1280 - 20;
		}
		else {
			target.x = mouseStructure.x;
		}

		if (mouseStructure.y - 20 <= 0) {
			target.y = 0 + 20;
		}
		else if (mouseStructure.y + 20 >= 768 - 192) {
			target.y = 768 - 192 - 20;
		}
		else {
			target.y = mouseStructure.y - target.r;
		}

		//ブーメランの位置をプレイヤーの位置に合わせる
		boomerang.object.transform.x = player.transform.x;
		boomerang.object.transform.y = player.transform.y;

		int mouse = GetMouseInput();
		if (mouse & MOUSE_INPUT_LEFT) {
			if (isAirjump != 1) {
				if (mouseStructure.isLeftPush == false) {	//押し始めなら
					mouseStructure.isLeftPush = true;		//押されてるフラグをtrue
					boomerang.isThrown = true;

					//ターゲットとブーメランの距離から初速度を計算
					boomerang.object.velocityX = (target.x - boomerang.object.transform.x) / 25;
					boomerang.object.velocityY = (target.y - boomerang.object.transform.y) / 25;

					//ブーメランの初速度から約49フレームでターゲットに到達するような加速度を計算
					boomerang.accerarationX = boomerang.object.velocityX / 49;
					boomerang.accerarationY = boomerang.object.velocityY / 49;
				}
			}
		}
		else {
			if (mouseStructure.isLeftPush == true) {	//押されてるフラグがtrueの時
				mouseStructure.isLeftPush = false;		//押されてるフラグfalseにする
			}
		}
	}
	else if (boomerang.isThrown == true) {
		if (boomerang.state == hold) {		//プレイヤーが持ってる時
			boomerang.state = fly2target;	//ブーメランの状態をターゲットに向かって飛んで行ってる時にする
		}

		else if (boomerang.state == fly2target) {//ターゲットに向かって飛んで行ってる時

			//ブーメランの早さを計算
			boomerang.object.speedX = boomerang.object.velocityX - boomerang.accerarationX * boomerang.flyingTimer;
			boomerang.object.speedY = boomerang.object.velocityY - boomerang.accerarationY * boomerang.flyingTimer;
			boomerang.flyingTimer++;

			//ブーメランがターゲットまで来たとき
			if (boomerang.object.transform.x <= target.x + target.r && boomerang.object.transform.x >= target.x - target.r) {
				if (boomerang.object.transform.y <= target.y + target.r && boomerang.object.transform.y >= target.y - target.r) {

					//ブーメランの状態をプレイヤーのもとに帰ってきている時
					boomerang.state = return2player;
					//ブーメランの動きに関する変数をすべて0にする
					boomerang.object.speedX = 0;
					boomerang.object.speedY = 0;
					boomerang.object.velocityX = 0;
					boomerang.object.velocityY = 0;
					boomerang.accerarationX = 0;
					boomerang.accerarationY = 0;
					boomerang.flyingTimer = 0;
				}
			}
		}

		else if (boomerang.state == return2player) {//プレイヤーのもとに帰ってきている時

			//速度ベクトルと向かうべき方向のベクトルの外積をとる
			//成分を計算
			if (boomerang.object.transform.y + boomerang.object.transform.r >= 768 - 192) {
				boomerang.crros.angle = -boomerang.crros.angle;
			}

			boomerang.object.speedX = boomerang.returnSpeed * boomerang.flyingTimer * cos(boomerang.crros.angle);
			boomerang.object.speedY = boomerang.returnSpeed * boomerang.flyingTimer * sin(boomerang.crros.angle);
			//ブーメランとプレイヤーとの距離を計算
			float b2pX = boomerang.object.transform.x - player.transform.x;
			float b2pY = boomerang.object.transform.y - player.transform.y;

			//外積を計算
			boomerang.crros.first = boomerang.object.speedX * b2pY - boomerang.object.speedY * b2pX;
			if (boomerang.crros.first <= 0) {		//弾から見て敵が左なら
				boomerang.crros.angle += pi / 36;	//左に曲がる
			}
			else if (boomerang.crros.first >= 0) {	//弾から見て敵が右なら
				boomerang.crros.angle += -pi / 36;	//右に曲がる
			}

			if (boomerang.flyingTimer <= 100) {
				boomerang.flyingTimer++;	//飛んでる時間をインクリメント
			}

			//ブーメランの速度を計算
			boomerang.object.speedX = boomerang.returnSpeed * boomerang.flyingTimer * cos(boomerang.crros.angle);
			boomerang.object.speedY = boomerang.returnSpeed * boomerang.flyingTimer * sin(boomerang.crros.angle);
			//プレイヤーの半径の範囲に到達したら
			if (boomerang.object.transform.x <= player.transform.x + player.transform.r &&
				boomerang.object.transform.x >= player.transform.x - player.transform.r) {
				if (boomerang.object.transform.y <= player.transform.y + player.transform.r &&
					boomerang.object.transform.y >= player.transform.y - player.transform.r) {

					//ブーメランの状態をプレイヤーが持っている状態にする
					boomerang.state = hold;

					//ブーメランの動きに関する変数をすべて0にする
					boomerang.object.speedX = 0;
					boomerang.object.speedY = 0;
					boomerang.object.velocityX = 0;
					boomerang.object.velocityY = 0;
					boomerang.accerarationX = 0;
					boomerang.accerarationY = 0;
					boomerang.flyingTimer = 0;
					boomerang.isThrown = false;

				}
			}
		}

		//ブーメランの座標にブーメランの速さを足す
		boomerang.object.transform.x += boomerang.object.speedX;
		boomerang.object.transform.y += boomerang.object.speedY;

	}

}