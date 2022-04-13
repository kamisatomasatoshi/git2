#include "DxLib.h"
#include "hit.h"
#include "math.h"

const double pi = 3.141592;

void HitDecision(Object& player, Boomerang& boomerang, Shield& playerShield, ENEMY& bossLeftHand, ENEMY& bossRightHand, ENEMY& bossFace, Bullet& enemyBullet,int& downCount) {

#pragma region//敵→プレイヤー
	//矩形の当たり判定使ってるよ

	if (0 <= player.invincibleTime) {
		player.invincibleTime--;
	}
	else {
		//左手→プレイヤー
		if (0 < bossLeftHand.hitPoint) {
			if (bossLeftHand.atk.isAtk == 1) {
				if (player.transform.x - player.transform.r <= bossLeftHand.posX + bossLeftHand.atk.atkJudgmentRadius
					&& bossLeftHand.posX - bossLeftHand.atk.atkJudgmentRadius <= player.transform.x - player.transform.r) {
					if (bossLeftHand.posY - bossLeftHand.atk.atkJudgmentRadius <= player.transform.y - player.transform.r
						&& player.transform.y - player.transform.r <= bossLeftHand.posY + bossLeftHand.atk.atkJudgmentRadius) {
						player.hp -= bossLeftHand.atk.atkPower;
						player.invincibleTime = 50;
					}
					else if (bossLeftHand.posY - bossLeftHand.atk.atkJudgmentRadius <= player.transform.y + player.transform.r
						&& player.transform.y + player.transform.r <= bossLeftHand.posY + bossLeftHand.atk.atkJudgmentRadius) {
						player.hp -= bossLeftHand.atk.atkPower;
						player.invincibleTime = 50;
					}
					else {

					}
				}
				else if (player.transform.x + player.transform.r <= bossLeftHand.posX + bossLeftHand.atk.atkJudgmentRadius
					&& bossLeftHand.posX - bossLeftHand.atk.atkJudgmentRadius <= player.transform.x + player.transform.r) {
					if (bossLeftHand.posY - bossLeftHand.atk.atkJudgmentRadius <= player.transform.y - player.transform.r
						&& player.transform.y - player.transform.r <= bossLeftHand.posY + bossLeftHand.atk.atkJudgmentRadius) {
						player.hp -= bossLeftHand.atk.atkPower;
						player.invincibleTime = 50;
					}
					else if (bossLeftHand.posY - bossLeftHand.atk.atkJudgmentRadius <= player.transform.y + player.transform.r
						&& player.transform.y + player.transform.r <= bossLeftHand.posY + bossLeftHand.atk.atkJudgmentRadius) {
						player.hp -= bossLeftHand.atk.atkPower;
						player.invincibleTime = 50;
					}
					else {

					}
				}
				else {

				}
			}
		}

		//右手→プレイヤー
		if (0 < bossRightHand.hitPoint) {
			if (bossRightHand.atk.isAtk == 1) {
				if (player.transform.x - player.transform.r <= bossRightHand.posX + bossRightHand.atk.atkJudgmentRadius
					&& bossRightHand.posX - bossRightHand.atk.atkJudgmentRadius <= player.transform.x - player.transform.r) {
					if (bossRightHand.posY - bossRightHand.atk.atkJudgmentRadius <= player.transform.y - player.transform.r
						&& player.transform.y - player.transform.r <= bossRightHand.posY + bossRightHand.atk.atkJudgmentRadius) {
						player.hp -= bossRightHand.atk.atkPower;
						player.invincibleTime = 50;
					}
					else if (bossRightHand.posY - bossRightHand.atk.atkJudgmentRadius <= player.transform.y + player.transform.r
						&& player.transform.y + player.transform.r <= bossRightHand.posY + bossRightHand.atk.atkJudgmentRadius) {
						player.hp -= bossRightHand.atk.atkPower;
						player.invincibleTime = 50;
					}
					else {

					}
				}
				else if (player.transform.x + player.transform.r <= bossRightHand.posX + bossRightHand.atk.atkJudgmentRadius
					&& bossRightHand.posX - bossRightHand.atk.atkJudgmentRadius <= player.transform.x + player.transform.r) {
					if (bossRightHand.posY - bossRightHand.atk.atkJudgmentRadius <= player.transform.y - player.transform.r
						&& player.transform.y - player.transform.r <= bossRightHand.posY + bossRightHand.atk.atkJudgmentRadius) {
						player.hp -= bossRightHand.atk.atkPower;
						player.invincibleTime = 50;
					}
					else if (bossRightHand.posY - bossRightHand.atk.atkJudgmentRadius <= player.transform.y + player.transform.r
						&& player.transform.y + player.transform.r <= bossRightHand.posY + bossRightHand.atk.atkJudgmentRadius) {
						player.hp -= bossRightHand.atk.atkPower;
						player.invincibleTime = 50;
					}
					else {

					}
				}
				else {

				}
			}
		}

		//敵の弾→プレイヤー
		//弾がプレイヤーの半径の範囲に到達したら
		if (enemyBullet.object.transform.x <= player.transform.x + player.transform.r &&
			enemyBullet.object.transform.x >= player.transform.x - player.transform.r) {
			if (enemyBullet.object.transform.y <= player.transform.y + player.transform.r &&
				enemyBullet.object.transform.y >= player.transform.y - player.transform.r) {

				//ダメージを与える
				player.hp -= enemyBullet.damage;
				player.invincibleTime = 50;

				//敵の弾の状態をプレイヤーが持っている状態にする
				enemyBullet.isShot = 0;

				//敵の弾の動きに関する変数をすべて0にする
				enemyBullet.object.speedX = 0;
				enemyBullet.object.speedY = 0;
				enemyBullet.object.velocityX = 0;
				enemyBullet.object.velocityY = 0;

			}
		}
	}

#pragma endregion//敵→プレイヤー

#pragma region//敵→シールド
	//矩形の当たり判定使ってるよ
	if (playerShield.isShieldOn == true) {
		//左手→プレイヤー
		if (0 < bossLeftHand.hitPoint) {
			if (bossLeftHand.atk.isAtk == 1) {
				if (playerShield.point2.x <= bossLeftHand.posX + bossLeftHand.atk.atkJudgmentRadius
					&& bossLeftHand.posX - bossLeftHand.atk.atkJudgmentRadius <= playerShield.point2.x) {
					if (bossLeftHand.posY - bossLeftHand.atk.atkJudgmentRadius <= playerShield.point2.y
						&& playerShield.point2.y <= bossLeftHand.posY + bossLeftHand.atk.atkJudgmentRadius) {
						if (0 < playerShield.parryTimer) {
							playerShield.level = playerShield.max;
							playerShield.isParry = true;
							playerShield.parrynow = 20;
							bossLeftHand.hitPoint -= 35;
							if (bossLeftHand.hitPoint <= 0) {
								bossLeftHand.hitPoint = 0;
								bossLeftHand.respawnTimer = 50 * 8;
								downCount++;
							}
						}
						else {
							playerShield.level -= bossLeftHand.atk.atkPower * 5;
							if (playerShield.level <= 0) {			//シールド残量が0以下になったら
								playerShield.level = 0;				//シールド残量を0にして
								playerShield.state = crack;			//シールドの状態を割れた時にする
								playerShield.rechargeTimer = 500;	//シールドリチャージのタイマーに500(10秒)を代入
							}
						}
						player.invincibleTime = 50;
					}
					else {

					}
				}
				else if (playerShield.point1.x <= bossLeftHand.posX + bossLeftHand.atk.atkJudgmentRadius
					&& bossLeftHand.posX - bossLeftHand.atk.atkJudgmentRadius <= playerShield.point1.x) {
					if (bossLeftHand.posY - bossLeftHand.atk.atkJudgmentRadius <= playerShield.point1.y
						&& playerShield.point1.y <= bossLeftHand.posY + bossLeftHand.atk.atkJudgmentRadius) {
						if (0 < playerShield.parryTimer) {
							playerShield.level = playerShield.max;
							playerShield.isParry = true;
							playerShield.parrynow = 20;
							bossLeftHand.hitPoint -= 35;
							if (bossLeftHand.hitPoint <= 0) {
								bossLeftHand.hitPoint = 0;
								bossLeftHand.respawnTimer = 50 * 8;
								downCount++;
							}
						}
						else {
							playerShield.level -= bossLeftHand.atk.atkPower * 5;
							if (playerShield.level <= 0) {			//シールド残量が0以下になったら
								playerShield.level = 0;				//シールド残量を0にして
								playerShield.state = crack;			//シールドの状態を割れた時にする
								playerShield.rechargeTimer = 500;	//シールドリチャージのタイマーに500(10秒)を代入
							}
						}
						player.invincibleTime = 20;
					}
					else {

					}
				}
				else {

				}
			}
		}

		//右手→プレイヤー
		if (0 < bossRightHand.hitPoint) {
			if (bossRightHand.atk.isAtk == 1) {
				if (playerShield.point2.x <= bossRightHand.posX + bossRightHand.atk.atkJudgmentRadius
					&& bossRightHand.posX - bossRightHand.atk.atkJudgmentRadius <= playerShield.point2.x) {
					if (bossRightHand.posY - bossRightHand.atk.atkJudgmentRadius <= playerShield.point2.y
						&& playerShield.point2.y <= bossRightHand.posY + bossRightHand.atk.atkJudgmentRadius) {
						if (0 < playerShield.parryTimer) {
							playerShield.level = playerShield.max;
							playerShield.isParry = true;
							playerShield.parrynow = 20;
							bossRightHand.hitPoint -= 35;
							if (bossRightHand.hitPoint <= 0) {
								bossRightHand.hitPoint = 0;
								bossRightHand.respawnTimer = 50 * 8;
								downCount++;
							}
						}
						else {
							playerShield.level -= bossRightHand.atk.atkPower * 5;
							if (playerShield.level <= 0) {			//シールド残量が0以下になったら
								playerShield.level = 0;				//シールド残量を0にして
								playerShield.state = crack;			//シールドの状態を割れた時にする
								playerShield.rechargeTimer = 500;	//シールドリチャージのタイマーに500(10秒)を代入
							}
						}
						player.invincibleTime = 50;
					}
					else {

					}
				}
				else if (playerShield.point1.x <= bossRightHand.posX + bossRightHand.atk.atkJudgmentRadius
					&& bossRightHand.posX - bossRightHand.atk.atkJudgmentRadius <= playerShield.point1.x) {
					if (bossRightHand.posY - bossRightHand.atk.atkJudgmentRadius <= playerShield.point1.y
						&& playerShield.point1.y <= bossRightHand.posY + bossRightHand.atk.atkJudgmentRadius) {
						if (0 < playerShield.parryTimer) {
							playerShield.level = playerShield.max;
							playerShield.isParry = true;
							playerShield.parrynow = 20;
							bossRightHand.hitPoint -= 35;
							if (bossRightHand.hitPoint <= 0) {
								bossRightHand.hitPoint = 0;
								bossRightHand.respawnTimer = 50 * 8;
								downCount++;
							}
						}
						else {
							playerShield.level -= bossRightHand.atk.atkPower * 5;
							if (playerShield.level <= 0) {			//シールド残量が0以下になったら
								playerShield.level = 0;				//シールド残量を0にして
								playerShield.state = crack;			//シールドの状態を割れた時にする
								playerShield.rechargeTimer = 500;	//シールドリチャージのタイマーに500(10秒)を代入
							}
						}
						player.invincibleTime = 50;
					}
					else {

					}
				}
				else {

				}
			}
		}
		//敵の弾→シールド
		if (enemyBullet.isShot == 1) {
			//変数を使って外積を計算して変数crossに格納
			for (int i = 0; i < 16; i++) {
				playerShield.crros[i].first =
					(playerShield.point1.x - player.transform.x) * (enemyBullet.object.transform.y + enemyBullet.object.transform.r * sin(pi / 8 * i) - player.transform.y) -
					(playerShield.point1.y - player.transform.y) * (enemyBullet.object.transform.x + enemyBullet.object.transform.r * cos(pi / 8 * i) - player.transform.x);
				playerShield.crros[i].seccond =
					(playerShield.point2.x - playerShield.point1.x) * (enemyBullet.object.transform.y + enemyBullet.object.transform.r * sin(pi / 8 * i) - playerShield.point1.y) -
					(playerShield.point2.y - playerShield.point1.y) * (enemyBullet.object.transform.x + enemyBullet.object.transform.r * cos(pi / 8 * i) - playerShield.point1.x);
				playerShield.crros[i].third =
					(player.transform.x - playerShield.point2.x) * (enemyBullet.object.transform.y + enemyBullet.object.transform.r * sin(pi / 8 * i) - playerShield.point2.y) -
					(player.transform.y - playerShield.point2.y) * (enemyBullet.object.transform.x + enemyBullet.object.transform.r * cos(pi / 8 * i) - playerShield.point2.x);

				if (playerShield.crros[i].first < 0 &&
					playerShield.crros[i].seccond < 0 &&
					playerShield.crros[i].third < 0) {			//シールドが敵の弾に当たっていたら
					if (0 < playerShield.parryTimer) {
						playerShield.level = playerShield.max;
						playerShield.isParry = true;
						playerShield.parrynow = 20;
					}
						playerShield.level -= enemyBullet.damage * 5;
						if (playerShield.level <= 0) {			//シールド残量が0以下になったら
							playerShield.level = 0;				//シールド残量を0にして
							playerShield.state = crack;			//シールドの状態を割れた時にする
							playerShield.rechargeTimer = 500;	//シールドリチャージのタイマーに500(10秒)を代入
						}
					player.invincibleTime = 50;
					//敵の弾のフラグをfalseにする
					enemyBullet.isShot = 0;

					//敵の弾の動きに関する変数をすべて0にする
					enemyBullet.object.speedX = 0;
					enemyBullet.object.speedY = 0;
					enemyBullet.object.velocityX = 0;
					enemyBullet.object.velocityY = 0;

					break;
				}
			}
		}
	}

#pragma endregion//敵→シールド

#pragma region//ブーメラン→敵
	//矩形の当たり判定使ってるよ

	//ブーメラン→左手
	if (0 <= bossLeftHand.invincibleTime) {
		bossLeftHand.invincibleTime--;
	}
	else {
		if (0 < bossLeftHand.hitPoint) {
			if (boomerang.isThrown == 1) {
				if (boomerang.object.transform.x - boomerang.object.transform.r <= bossLeftHand.posX + bossLeftHand.atk.atkJudgmentRadius
					&& bossLeftHand.posX - bossLeftHand.atk.atkJudgmentRadius <= boomerang.object.transform.x - boomerang.object.transform.r) {
					if (bossLeftHand.posY - bossLeftHand.atk.atkJudgmentRadius <= boomerang.object.transform.y - boomerang.object.transform.r
						&& boomerang.object.transform.y - boomerang.object.transform.r <= bossLeftHand.posY + bossLeftHand.atk.atkJudgmentRadius) {
						bossLeftHand.hitPoint -= boomerang.damage;
						bossLeftHand.invincibleTime = 10;
						if (bossLeftHand.hitPoint <= 0) {
							bossLeftHand.hitPoint = 0;
							bossLeftHand.respawnTimer = 50 * 8;
							downCount++;
						}
					}
					else if (bossLeftHand.posY - bossLeftHand.atk.atkJudgmentRadius <= boomerang.object.transform.y + boomerang.object.transform.r
						&& boomerang.object.transform.y + boomerang.object.transform.r <= bossLeftHand.posY + bossLeftHand.atk.atkJudgmentRadius) {
						bossLeftHand.hitPoint -= boomerang.damage;
						bossLeftHand.invincibleTime = 10;
						if (bossLeftHand.hitPoint <= 0) {
							bossLeftHand.hitPoint = 0;
							bossLeftHand.respawnTimer = 50 * 8;
							downCount++;
						}
					}
					else {

					}
				}
				else if (boomerang.object.transform.x + boomerang.object.transform.r <= bossLeftHand.posX + bossLeftHand.atk.atkJudgmentRadius
					&& bossLeftHand.posX - bossLeftHand.atk.atkJudgmentRadius <= boomerang.object.transform.x + boomerang.object.transform.r) {
					if (bossLeftHand.posY - bossLeftHand.atk.atkJudgmentRadius <= boomerang.object.transform.y - boomerang.object.transform.r
						&& boomerang.object.transform.y - boomerang.object.transform.r <= bossLeftHand.posY + bossLeftHand.atk.atkJudgmentRadius) {
						bossLeftHand.hitPoint -= boomerang.damage;
						bossLeftHand.invincibleTime = 10;
						if (bossLeftHand.hitPoint <= 0) {
							bossLeftHand.hitPoint = 0;
							bossLeftHand.respawnTimer = 50 * 8;
							downCount++;
						}
					}
					else if (bossLeftHand.posY - bossLeftHand.atk.atkJudgmentRadius <= boomerang.object.transform.y + boomerang.object.transform.r
						&& boomerang.object.transform.y + boomerang.object.transform.r <= bossLeftHand.posY + bossLeftHand.atk.atkJudgmentRadius) {
						bossLeftHand.hitPoint -= boomerang.damage;
						bossLeftHand.invincibleTime = 10;
						if (bossLeftHand.hitPoint <= 0) {
							bossLeftHand.hitPoint = 0;
							bossLeftHand.respawnTimer = 50 * 8;
							downCount++;
						}
					}
					else {

					}
				}
				else {

				}
			}
		}
	}
	//ブーメラン→右手
	if (0 <= bossRightHand.invincibleTime) {
		bossRightHand.invincibleTime--;
	}
	else {
		if (0 < bossRightHand.hitPoint) {
			if (boomerang.isThrown == 1) {
				if (boomerang.object.transform.x - boomerang.object.transform.r <= bossRightHand.posX + bossRightHand.atk.atkJudgmentRadius
					&& bossRightHand.posX - bossRightHand.atk.atkJudgmentRadius <= boomerang.object.transform.x - boomerang.object.transform.r) {
					if (bossRightHand.posY - bossRightHand.atk.atkJudgmentRadius <= boomerang.object.transform.y - boomerang.object.transform.r
						&& boomerang.object.transform.y - boomerang.object.transform.r <= bossRightHand.posY + bossRightHand.atk.atkJudgmentRadius) {
						bossRightHand.hitPoint -= boomerang.damage;
						bossRightHand.invincibleTime = 10;
						if (bossRightHand.hitPoint <= 0) {
							bossRightHand.hitPoint = 0;
							bossRightHand.respawnTimer = 50 * 8;
							downCount++;
						}
					}
					else if (bossRightHand.posY - bossRightHand.atk.atkJudgmentRadius <= boomerang.object.transform.y + boomerang.object.transform.r
						&& boomerang.object.transform.y + boomerang.object.transform.r <= bossRightHand.posY + bossRightHand.atk.atkJudgmentRadius) {
						bossRightHand.hitPoint -= boomerang.damage;
						bossRightHand.invincibleTime = 10;
						if (bossRightHand.hitPoint <= 0) {
							bossRightHand.hitPoint = 0;
							bossRightHand.respawnTimer = 50 * 8;
							downCount++;
						}

					}
					else {

					}
				}
				else if (boomerang.object.transform.x + boomerang.object.transform.r <= bossRightHand.posX + bossRightHand.atk.atkJudgmentRadius
					&& bossRightHand.posX - bossRightHand.atk.atkJudgmentRadius <= boomerang.object.transform.x + boomerang.object.transform.r) {
					if (bossRightHand.posY - bossRightHand.atk.atkJudgmentRadius <= boomerang.object.transform.y - boomerang.object.transform.r
						&& boomerang.object.transform.y - boomerang.object.transform.r <= bossRightHand.posY + bossRightHand.atk.atkJudgmentRadius) {
						bossRightHand.hitPoint -= boomerang.damage;
						bossRightHand.invincibleTime = 10;
						if (bossRightHand.hitPoint <= 0) {
							bossRightHand.hitPoint = 0;
							bossRightHand.respawnTimer = 50 * 8;
							downCount++;
						}
					}
					else if (bossRightHand.posY - bossRightHand.atk.atkJudgmentRadius <= boomerang.object.transform.y + boomerang.object.transform.r
						&& boomerang.object.transform.y + boomerang.object.transform.r <= bossRightHand.posY + bossRightHand.atk.atkJudgmentRadius) {
						bossRightHand.hitPoint -= boomerang.damage;
						bossRightHand.invincibleTime = 10;
						if (bossRightHand.hitPoint <= 0) {
							bossRightHand.hitPoint = 0;
							bossRightHand.respawnTimer = 50 * 8;
							downCount++;
						}
					}
					else {

					}
				}
				else {

				}
			}
		}
	}

	//ブーメラン→顔
	if (0 <= bossFace.invincibleTime) {
		bossFace.invincibleTime--;
	}
	else {
		if (0 < bossFace.hitPoint) {
			if (boomerang.isThrown == 1) {
				if (boomerang.object.transform.x - boomerang.object.transform.r <= bossFace.posX + bossFace.atk.atkJudgmentRadius
					&& bossFace.posX - bossFace.atk.atkJudgmentRadius <= boomerang.object.transform.x - boomerang.object.transform.r) {
					if (bossFace.posY - bossFace.atk.atkJudgmentRadius <= boomerang.object.transform.y - boomerang.object.transform.r
						&& boomerang.object.transform.y - boomerang.object.transform.r <= bossFace.posY + bossFace.atk.atkJudgmentRadius) {
						bossFace.hitPoint -= boomerang.damage;
						bossFace.invincibleTime = 10;
						if (bossFace.hitPoint <= 0) {
							bossFace.hitPoint = 0;
						}
					}
					else if (bossFace.posY - bossFace.atk.atkJudgmentRadius <= boomerang.object.transform.y + boomerang.object.transform.r
						&& boomerang.object.transform.y + boomerang.object.transform.r <= bossFace.posY + bossFace.atk.atkJudgmentRadius) {
						bossFace.hitPoint -= boomerang.damage;
						bossFace.invincibleTime = 10;
						if (bossFace.hitPoint <= 0) {
							bossFace.hitPoint = 0;
						}
					}
					else {

					}
				}
				else if (boomerang.object.transform.x + boomerang.object.transform.r <= bossFace.posX + bossFace.atk.atkJudgmentRadius
					&& bossFace.posX - bossFace.atk.atkJudgmentRadius <= boomerang.object.transform.x + boomerang.object.transform.r) {
					if (bossFace.posY - bossFace.atk.atkJudgmentRadius <= boomerang.object.transform.y - boomerang.object.transform.r
						&& boomerang.object.transform.y - boomerang.object.transform.r <= bossFace.posY + bossFace.atk.atkJudgmentRadius) {
						bossFace.hitPoint -= boomerang.damage;
						bossFace.invincibleTime = 10;
						if (bossFace.hitPoint <= 0) {
							bossFace.hitPoint = 0;
						}
					}
					else if (bossFace.posY - bossFace.atk.atkJudgmentRadius <= boomerang.object.transform.y + boomerang.object.transform.r
						&& boomerang.object.transform.y + boomerang.object.transform.r <= bossFace.posY + bossFace.atk.atkJudgmentRadius) {
						bossFace.hitPoint -= boomerang.damage;
						bossFace.invincibleTime = 10;
						if (bossFace.hitPoint <= 0) {
							bossFace.hitPoint = 0;
						}
					}
					else {

					}
				}
				else {

				}
			}
		}
	}

#pragma endregion//ブーメラン→敵

}