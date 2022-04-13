#include "boss.h"
#include "stdlib.h"
#include "math.h"

const double pi = 3.141592;

void MOVE_ROULETTE(int& bossAttackCoolTime, ENEMY& bossLeftHand, ENEMY& bossRightHand, int bossAttackPattern, int& bossAttackCount) {

	if (bossAttackCoolTime <= 0) {
		if (bossLeftHand.attackType == 0 && bossRightHand.attackType == 0) {
			bossAttackPattern = rand() % 100 + 1;
		}

		if (0 < bossAttackPattern && bossAttackPattern <= 30) {
			if (0 < bossLeftHand.hitPoint) {
				bossLeftHand.attackType = 1;
				bossLeftHand.atk.atkPower = 1;
			}
			if (0 < bossRightHand.hitPoint) {
				bossRightHand.attackType = 1;
				bossRightHand.atk.atkPower = 1;
			}
			if (0 < bossLeftHand.hitPoint || 0 < bossRightHand.hitPoint) {
				bossAttackCount++;
			}
		}
		else if (0 < bossAttackPattern && bossAttackPattern <= 45) {
			if (0 < bossLeftHand.hitPoint) {
				bossLeftHand.attackType = 2;
				bossLeftHand.atk.atkPower = 1;
			}
			bossAttackCount++;
		}
		else if (0 < bossAttackPattern && bossAttackPattern <= 60) {
			if (0 < bossRightHand.hitPoint) {
				bossRightHand.attackType = 2;
				bossRightHand.atk.atkPower = 1;
				bossAttackCount++;
			}
		}
		else if (0 < bossAttackPattern && bossAttackPattern <= 75) {
			if (0 < bossRightHand.hitPoint) {
				bossRightHand.attackType = 3;
				bossRightHand.atk.atkPower = 1;
				bossAttackCount++;
			}
		}
		else if (0 < bossAttackPattern && bossAttackPattern <= 90) {
			if (0 < bossLeftHand.hitPoint) {
				bossLeftHand.attackType = 4;
				bossLeftHand.atk.atkPower = 1;
				bossAttackCount++;
			}
		}
		else if (0 < bossAttackPattern && bossAttackPattern <= 100) {
			if (10 <= bossAttackCount) {
				if (0 < bossLeftHand.hitPoint && 0 < bossRightHand.hitPoint) {
					bossRightHand.attackType = 5;
					bossLeftHand.attackType = 6;
					bossLeftHand.atk.atkPower = 3;
					bossRightHand.atk.atkPower = 3;
					bossAttackCount++;
				}
			}
		}
		bossAttackPattern = 0;
	}
	else {
		bossAttackCoolTime--;
	}

}

void ATK_MOVE(ENEMY& bossHand, Object& player, int& bossAttackCoolTime, int& bossTimer, int& isShake) {

#pragma region//一つ目の攻撃
	if (bossHand.attackType == 1) {
		if (bossHand.atk.moveFaze == 0) {
			if (bossHand.posY < 768 - 192/*地面の高さ*/ - bossHand.radius) {
				bossHand.posY += 3.0;
			}
			else {

				if (bossHand.posX - player.transform.x >= 0) {
					bossHand.atk.speedX = 6;
					bossHand.atk.moveFaze = 2;
				}
				else {
					bossHand.atk.speedX = -6;
					bossHand.atk.moveFaze = 1;
				}
			}
		}

		if (bossHand.atk.moveFaze == 1) {
			bossHand.atk.isAtk = 1;

			bossHand.posX += bossHand.atk.speedX;
			bossHand.atk.speedX += 0.3;
			isShake = 1;

			if (bossHand.posX - bossHand.radius > 1780) {
				bossHand.atk.speedX = 0;
				bossHand.atk.moveFaze = 3;
			}
		}
		else if (bossHand.atk.moveFaze == 2) {
			bossHand.atk.isAtk = 1;

			bossHand.posX += bossHand.atk.speedX;
			bossHand.atk.speedX -= 0.3;
			isShake = 1;

			if (bossHand.posX + bossHand.radius < -500) {
				bossHand.atk.speedX = 0;
				bossHand.atk.moveFaze = 3;
			}
		}

		if (bossHand.atk.moveFaze == 3) {
			bossHand.atk.isAtk = 0;

			bossHand.posX -= cos(atan2(bossHand.posY - bossHand.initPosY, bossHand.posX - bossHand.initPosX)) * 10;
			bossHand.posY -= sin(atan2(bossHand.posY - bossHand.initPosY, bossHand.posX - bossHand.initPosX)) * 10;

			if (bossHand.posX <= (double)bossHand.initPosX + 10 &&
				bossHand.posX >= (double)bossHand.initPosX - 10 &&
				bossHand.posY <= (double)bossHand.initPosY + 10 &&
				bossHand.posY >= (double)bossHand.initPosY - 10
				) {
				bossHand.atk.moveFaze = 0;
				bossHand.atk.speedX = 0;
				bossHand.atk.speedY = 0;
				bossHand.attackType = 0;
				bossHand.posX = (double)bossHand.initPosX;
				bossHand.posY = (double)bossHand.initPosY;
				bossAttackCoolTime = 20;

			}
		}
	}
#pragma endregion//一つ目の攻撃

#pragma region//二つ目の攻撃
	else if (bossHand.attackType == 2) {
		if (bossHand.atk.moveFaze == 0) {//上に上がっていくフェイズ
			if (100 <= bossHand.posY) {
				bossHand.posY -= 3;
			}
			else {
				bossHand.atk.moveFaze = 1;
				bossTimer = 10;
			}
		}

		else if (bossHand.atk.moveFaze == 1) {//プレイヤーの上に移動するフェイズ
			if (bossHand.posX >= player.transform.x - player.transform.r &&
				bossHand.posX <= player.transform.x + player.transform.r) {
				bossTimer--;
			}
			else if (bossHand.posX - player.transform.x >= 0) {
				bossHand.posX -= 10;
			}
			else {
				bossHand.posX += 10;
			}

			if (bossTimer <= 0) {
				bossHand.atk.moveFaze = 2;
				bossTimer = 50;
			}
		}

		else if (bossHand.atk.moveFaze == 2) {//急降下して攻撃するフェイズ
			bossHand.atk.isAtk = 1;

			if (bossHand.posY < 768 - 192/*地面の高さ*/ - bossHand.radius) {
				bossHand.posY += 25;
				if (bossHand.posY >= 768 - 192 /* 地面の高さ */ - bossHand.radius) {
					isShake = 1;
				}
			}
			else {

				bossHand.atk.isAtk = 0;
				bossTimer--;

				if (bossTimer <= 0) {
					bossHand.atk.moveFaze = 3;

				}
			}
		}

		if (bossHand.atk.moveFaze == 3) {//元の位置に戻るフェイズ

			bossHand.posX -= cos(atan2(bossHand.posY - bossHand.initPosY, bossHand.posX - bossHand.initPosX)) * 10;
			bossHand.posY -= sin(atan2(bossHand.posY - bossHand.initPosY, bossHand.posX - bossHand.initPosX)) * 10;

			if (bossHand.posX <= (double)bossHand.initPosX + 10 &&
				bossHand.posX >= (double)bossHand.initPosX - 10 &&
				bossHand.posY <= (double)bossHand.initPosY + 10 &&
				bossHand.posY >= (double)bossHand.initPosY - 10
				) {
				bossHand.atk.moveFaze = 0;
				bossHand.atk.speedX = 0;
				bossHand.atk.speedY = 0;
				bossHand.attackType = 0;
				bossHand.posX = (double)bossHand.initPosX;
				bossHand.posY = (double)bossHand.initPosY;
				bossAttackCoolTime = 20;

			}
		}
	}

#pragma endregion//二つ目の攻撃

#pragma region//三つ目の攻撃

#pragma region//右側の手
	if (bossHand.attackType == 3) {
		//一回目
		if (bossHand.atk.moveFaze == 0) {//スピードの計算をする
			bossHand.atk.speedX = ((1280.0 / 4.0 * 3) - bossHand.posX) / 50;
			bossHand.atk.speedY = (100.0 - bossHand.posY) / 50;
			bossTimer = 50;
			bossHand.atk.moveFaze = 1;
		}
		else if (bossHand.atk.moveFaze == 1) {//移動する
			bossHand.posX += bossHand.atk.speedX;
			bossHand.posY += bossHand.atk.speedY;
			bossTimer--;
			if (bossTimer <= 0) {
				bossHand.atk.moveFaze = 2;
				bossTimer = 50;
			}
		}
		else if (bossHand.atk.moveFaze == 2) {//急降下して攻撃する
			bossHand.atk.isAtk = 1;

			if (bossHand.posY < 768 - 193/*地面の高さ*/ - bossHand.radius) {
				bossHand.posY += 25;
				if (bossHand.posY >= 768 - 192 /* 地面の高さ */ - bossHand.radius) {
					isShake = 1;
				}
			}
			else {
				bossHand.atk.isAtk = 0;
				bossTimer--;
				if (bossTimer <= 0) {
					bossHand.atk.moveFaze = 3;
				}
			}
		}
		//二回目
		else if (bossHand.atk.moveFaze == 3) {//スピードの計算をする

			bossHand.atk.speedX = ((1280.0 / 4.0 * 2) - bossHand.posX) / 50;
			bossHand.atk.speedY = (100.0 - bossHand.posY) / 50;
			bossTimer = 50;
			bossHand.atk.moveFaze = 4;
		}
		else if (bossHand.atk.moveFaze == 4) {//移動する
			bossHand.posX += bossHand.atk.speedX;
			bossHand.posY += bossHand.atk.speedY;
			bossTimer--;
			if (bossTimer <= 0) {
				bossHand.atk.moveFaze = 5;
				bossTimer = 50;
			}
		}
		else if (bossHand.atk.moveFaze == 5) {//急降下して攻撃する
			bossHand.atk.isAtk = 1;

			if (bossHand.posY < 768 - 192/*地面の高さ*/ - bossHand.radius) {
				bossHand.posY += 25;
				if (bossHand.posY >= 768 - 192 /* 地面の高さ */ - bossHand.radius) {
					isShake = 1;
				}
			}
			else {
				bossHand.atk.isAtk = 0;
				bossTimer--;
				if (bossTimer <= 0) {
					bossHand.atk.moveFaze = 6;
				}
			}
		}
		//三回目
		if (bossHand.atk.moveFaze == 6) {//スピードの計算をする

			bossHand.atk.speedX = ((1280.0 / 4.0 * 1) - bossHand.posX) / 50;
			bossHand.atk.speedY = (100.0 - bossHand.posY) / 50;
			bossTimer = 50;
			bossHand.atk.moveFaze = 7;
		}
		else if (bossHand.atk.moveFaze == 7) {//移動する
			bossHand.posX += bossHand.atk.speedX;
			bossHand.posY += bossHand.atk.speedY;
			bossTimer--;
			if (bossTimer <= 0) {
				bossHand.atk.moveFaze = 8;
				bossTimer = 50;
			}
		}
		else if (bossHand.atk.moveFaze == 8) {//急降下して攻撃する
			bossHand.atk.isAtk = 1;

			if (bossHand.posY < 768 - 192/*地面の高さ*/ - bossHand.radius) {
				bossHand.posY += 25;
				if (bossHand.posY >= 768 - 192 /* 地面の高さ */ - bossHand.radius) {
					isShake = 1;
				}
			}
			else {
				bossHand.atk.isAtk = 0;
				bossTimer--;
				if (bossTimer <= 0) {
					bossHand.atk.moveFaze = 9;
				}
			}
		}

		else if (bossHand.atk.moveFaze == 9) {//元の位置に戻る

			bossHand.posX -= cos(atan2(bossHand.posY - bossHand.initPosY, bossHand.posX - bossHand.initPosX)) * 10;
			bossHand.posY -= sin(atan2(bossHand.posY - bossHand.initPosY, bossHand.posX - bossHand.initPosX)) * 10;

			if (bossHand.posX <= (double)bossHand.initPosX + 10 &&
				bossHand.posX >= (double)bossHand.initPosX - 10 &&
				bossHand.posY <= (double)bossHand.initPosY + 10 &&
				bossHand.posY >= (double)bossHand.initPosY - 10
				) {
				bossHand.atk.moveFaze = 0;
				bossHand.atk.speedX = 0;
				bossHand.atk.speedY = 0;
				bossHand.attackType = 0;
				bossHand.posX = (double)bossHand.initPosX;
				bossHand.posY = (double)bossHand.initPosY;
				bossAttackCoolTime = 20;

			}
		}
	}
#pragma endregion//右側の手

#pragma region//左側の手
	if (bossHand.attackType == 4) {
		//一回目
		if (bossHand.atk.moveFaze == 0) {//スピードの計算をする
			bossHand.atk.speedX = ((1280.0 / 4.0 * 1) - bossHand.posX) / 50;
			bossHand.atk.speedY = (100.0 - bossHand.posY) / 50;
			bossTimer = 50;
			bossHand.atk.moveFaze = 1;
		}
		else if (bossHand.atk.moveFaze == 1) {//移動する
			bossHand.posX += bossHand.atk.speedX;
			bossHand.posY += bossHand.atk.speedY;
			bossTimer--;
			if (bossTimer <= 0) {
				bossHand.atk.moveFaze = 2;
				bossTimer = 50;
			}
		}
		else if (bossHand.atk.moveFaze == 2) {//急降下して攻撃する
			bossHand.atk.isAtk = 1;

			if (bossHand.posY < 768 - 192/*地面の高さ*/ - bossHand.radius) {
				bossHand.posY += 25;
				if (bossHand.posY >= 768 - 192 /* 地面の高さ */ - bossHand.radius) {
					isShake = 1;
				}
			}
			else {
				bossHand.atk.isAtk = 0;
				bossTimer--;
				if (bossTimer <= 0) {
					bossHand.atk.moveFaze = 3;
				}
			}
		}
		//二回目
		else if (bossHand.atk.moveFaze == 3) {//スピードの計算をする

			bossHand.atk.speedX = ((1280.0 / 4.0 * 2) - bossHand.posX) / 50;
			bossHand.atk.speedY = (100.0 - bossHand.posY) / 50;
			bossTimer = 50;
			bossHand.atk.moveFaze = 4;
		}
		else if (bossHand.atk.moveFaze == 4) {//移動する
			bossHand.posX += bossHand.atk.speedX;
			bossHand.posY += bossHand.atk.speedY;
			bossTimer--;
			if (bossTimer <= 0) {
				bossHand.atk.moveFaze = 5;
				bossTimer = 50;
			}
		}
		else if (bossHand.atk.moveFaze == 5) {//急降下して攻撃する
			bossHand.atk.isAtk = 1;

			if (bossHand.posY < 768 - 192/*地面の高さ*/ - bossHand.radius) {
				bossHand.posY += 25;
				if (bossHand.posY >= 768 - 192 /* 地面の高さ */ - bossHand.radius) {
					isShake = 1;
				}
			}
			else {
				bossHand.atk.isAtk = 0;
				bossTimer--;
				if (bossTimer <= 0) {
					bossHand.atk.moveFaze = 6;
				}
			}
		}
		//三回目
		if (bossHand.atk.moveFaze == 6) {//スピードの計算をする

			bossHand.atk.speedX = ((1280.0 / 4.0 * 3) - bossHand.posX) / 50;
			bossHand.atk.speedY = (100.0 - bossHand.posY) / 50;
			bossTimer = 50;
			bossHand.atk.moveFaze = 7;
		}
		else if (bossHand.atk.moveFaze == 7) {//移動する
			bossHand.posX += bossHand.atk.speedX;
			bossHand.posY += bossHand.atk.speedY;
			bossTimer--;
			if (bossTimer <= 0) {
				bossHand.atk.moveFaze = 8;
				bossTimer = 50;
			}
		}
		else if (bossHand.atk.moveFaze == 8) {//急降下して攻撃する
			bossHand.atk.isAtk = 1;

			if (bossHand.posY < 768 - 192/*地面の高さ*/ - bossHand.radius) {
				bossHand.posY += 25;
				if (bossHand.posY >= 768 - 192 /* 地面の高さ */ - bossHand.radius) {
					isShake = 1;
				}
			}
			else {
				bossHand.atk.isAtk = 0;
				bossTimer--;
				if (bossTimer <= 0) {
					bossHand.atk.moveFaze = 9;
				}
			}
		}

		else if (bossHand.atk.moveFaze == 9) {//元の位置に戻る

			bossHand.posX -= cos(atan2(bossHand.posY - bossHand.initPosY, bossHand.posX - bossHand.initPosX)) * 10;
			bossHand.posY -= sin(atan2(bossHand.posY - bossHand.initPosY, bossHand.posX - bossHand.initPosX)) * 10;

			if (bossHand.posX <= (double)bossHand.initPosX + 10 &&
				bossHand.posX >= (double)bossHand.initPosX - 10 &&
				bossHand.posY <= (double)bossHand.initPosY + 10 &&
				bossHand.posY >= (double)bossHand.initPosY - 10
				) {
				bossHand.atk.moveFaze = 0;
				bossHand.atk.speedX = 0;
				bossHand.atk.speedY = 0;
				bossHand.attackType = 0;
				bossHand.posX = (double)bossHand.initPosX;
				bossHand.posY = (double)bossHand.initPosY;
				bossAttackCoolTime = 20;

			}
		}
	}
#pragma endregion//左側の手

#pragma endregion//三つ目の攻撃

#pragma region//四つ目の攻撃

#pragma region//右側の手
	if (bossHand.attackType == 5) {
		if (bossHand.atk.moveFaze == 0) {//スピードの計算をする

			bossHand.atk.speedX = ((1280.0 / 2) - bossHand.posX + bossHand.radius / 2) / 50;
			bossHand.atk.moveFaze = 1;

		}
		else if (bossHand.atk.moveFaze == 1) {//移動する
			if (0 < bossTimer) {
				bossHand.posX += bossHand.atk.speedX;
			}
			else {
				bossHand.atk.speedY++;
				bossHand.posY -= bossHand.atk.speedY;
				if (bossHand.posY + bossHand.radius <= 0) {
					bossHand.atk.moveFaze = 2;
				}
			}
		}
		else if (bossHand.atk.moveFaze == 2) {
			if (30 < bossTimer) {
				bossHand.posX = player.transform.x + bossHand.radius / 2;
			}
			else if (0 < bossTimer) {

			}
			else {//急降下して攻撃する
				bossHand.atk.isAtk = 1;

				if (bossHand.posY < 768 - 192/*地面の高さ*/ - bossHand.radius) {
					bossHand.posY += 100;
					if (bossHand.posY >= 768 - 192 /* 地面の高さ */ - bossHand.radius) {
						isShake = 1;
					}
				}
				else {
					bossHand.atk.moveFaze = 3;
				}
			}
		}
		else if (bossHand.atk.moveFaze == 3) {
			bossHand.atk.isAtk = 0;

			bossHand.posY = 768 - 192/*地面の高さ*/ - bossHand.radius;
			if (bossTimer <= 0) {
				bossHand.atk.moveFaze = 4;
			}
		}
		else if (bossHand.atk.moveFaze == 4) {
			bossHand.posX -= cos(atan2(bossHand.posY - bossHand.initPosY, bossHand.posX - bossHand.initPosX)) * 10;
			bossHand.posY -= sin(atan2(bossHand.posY - bossHand.initPosY, bossHand.posX - bossHand.initPosX)) * 10;

			if (bossHand.posX <= (double)bossHand.initPosX + 10 &&
				bossHand.posX >= (double)bossHand.initPosX - 10 &&
				bossHand.posY <= (double)bossHand.initPosY + 10 &&
				bossHand.posY >= (double)bossHand.initPosY - 10
				) {
				bossHand.atk.moveFaze = 0;
				bossHand.atk.speedX = 0;
				bossHand.atk.speedY = 0;
				bossHand.attackType = 0;
				bossHand.posX = (double)bossHand.initPosX;
				bossHand.posY = (double)bossHand.initPosY;
				bossAttackCoolTime = 20;

			}
		}
	}
#pragma endregion//右側の手

#pragma region//左側の手
	if (bossHand.attackType == 6) {
		if (bossHand.atk.moveFaze == 0) {//スピードの計算をする

			bossHand.atk.speedX = ((1280.0 / 2) - bossHand.posX - bossHand.radius / 2) / 50;
			bossTimer = 50;
			bossHand.atk.moveFaze = 1;

		}
		else if (bossHand.atk.moveFaze == 1) {//移動する
			if (0 < bossTimer) {
				bossHand.posX += bossHand.atk.speedX;
			}
			else {
				bossHand.atk.speedY++;
				bossHand.posY -= bossHand.atk.speedY;
				if (bossHand.posY + bossHand.radius <= 0) {
					bossHand.atk.moveFaze = 2;
					bossTimer = 100;
				}
			}
			bossTimer--;
		}
		else if (bossHand.atk.moveFaze == 2) {
			if (30 < bossTimer) {
				bossHand.posX = player.transform.x - bossHand.radius / 2;
			}
			else if (0 < bossTimer) {

			}
			else {//急降下して攻撃する
				bossHand.atk.isAtk = 1;
				if (bossHand.posY < 768 - 192/*地面の高さ*/ - bossHand.radius) {
					bossHand.posY += 100;
					if (bossHand.posY >= 768 - 192 /* 地面の高さ */ - bossHand.radius) {
						isShake = 1;
					}
				}
				else {
					bossHand.atk.moveFaze = 3;
					bossTimer = 150;
				}
			}
			bossTimer--;
		}
		else if (bossHand.atk.moveFaze == 3) {
			bossHand.atk.isAtk = 0;

			bossHand.posY = 768 - 192/*地面の高さ*/ - bossHand.radius;
			if (bossTimer <= 0) {
				bossHand.atk.moveFaze = 4;
			}
			bossTimer--;
		}
		else if (bossHand.atk.moveFaze == 4) {
			bossHand.posX -= cos(atan2(bossHand.posY - bossHand.initPosY, bossHand.posX - bossHand.initPosX)) * 10;
			bossHand.posY -= sin(atan2(bossHand.posY - bossHand.initPosY, bossHand.posX - bossHand.initPosX)) * 10;

			if (bossHand.posX <= (double)bossHand.initPosX + 10 &&
				bossHand.posX >= (double)bossHand.initPosX - 10 &&
				bossHand.posY <= (double)bossHand.initPosY + 10 &&
				bossHand.posY >= (double)bossHand.initPosY - 10
				) {
				bossHand.atk.moveFaze = 0;
				bossHand.atk.speedX = 0;
				bossHand.atk.speedY = 0;
				bossHand.attackType = 0;
				bossHand.posX = (double)bossHand.initPosX;
				bossHand.posY = (double)bossHand.initPosY;
				bossAttackCoolTime = 20;

			}
		}
	}
#pragma endregion//左側の手

#pragma endregion//四つ目の攻撃

	//リスポーン
	if (bossHand.hitPoint <= 0) {
		if (bossHand.respawnTimer <= 0) {
			bossHand.hitPoint = 100;
		}
		else {
			bossHand.respawnTimer--;
		}
	}
};

void BOSS_BULLET(Object player, ENEMY& bossFace, Bullet& enemyBullet) {

	if (enemyBullet.coolTime <= 0) {
		if (enemyBullet.isShot == 0) {
			enemyBullet.object.transform.x = bossFace.posX;
			enemyBullet.object.transform.y = bossFace.posY;
			enemyBullet.isShot = 1;
			enemyBullet.timer = 25;
			enemyBullet.coolTime = 100;
		}
	}

	if (enemyBullet.isShot == 1) {
		if (0 <= enemyBullet.timer) {
			//速度ベクトルと向かうべき方向のベクトルの外積をとる
			//成分を計算
			enemyBullet.object.speedX = enemyBullet.speed * cos(enemyBullet.crros.angle);
			enemyBullet.object.speedY = enemyBullet.speed * sin(enemyBullet.crros.angle);

			//敵の弾とプレイヤーとの距離を計算
			enemyBullet.enemyBullet2playerX = enemyBullet.object.transform.x - player.transform.x;
			enemyBullet.enemyBullet2playerY = enemyBullet.object.transform.y - player.transform.y;

			//外積を計算
			enemyBullet.crros.first = enemyBullet.object.speedX * enemyBullet.enemyBullet2playerY -
				enemyBullet.object.speedY * enemyBullet.enemyBullet2playerX;
			if (enemyBullet.crros.first <= 0) {		//弾から見て敵が左なら
				enemyBullet.crros.angle += pi / 90;	//左に曲がる
			}
			else if (enemyBullet.crros.first >= 0) {	//弾から見て敵が右なら
				enemyBullet.crros.angle += -pi / 90;	//右に曲がる
			}

			//敵の弾の速度を計算
			enemyBullet.object.speedX = enemyBullet.speed * cos(enemyBullet.crros.angle);
			enemyBullet.object.speedY = enemyBullet.speed * sin(enemyBullet.crros.angle);
		}
		//画面外に到達したら
		if (enemyBullet.coolTime<=0) {

			//敵の弾の状態をプレイヤーが持っている状態にする
			enemyBullet.isShot = 0;

			//敵の弾の動きに関する変数をすべて0にする
			enemyBullet.object.speedX = 0;
			enemyBullet.object.speedY = 0;
			enemyBullet.object.velocityX = 0;
			enemyBullet.object.velocityY = 0;

		}
	}
	enemyBullet.object.transform.x += enemyBullet.object.speedX;
	enemyBullet.object.transform.y += enemyBullet.object.speedY;
	enemyBullet.timer--;
	enemyBullet.coolTime--;
}