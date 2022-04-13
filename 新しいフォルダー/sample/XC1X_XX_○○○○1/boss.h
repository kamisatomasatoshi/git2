#pragma once
#include "structure.h"

void MOVE_ROULETTE(int& bossAttackCoolTime, ENEMY& bossLeftHand, ENEMY& bossRightHand, int bossAttackPattern, int& bossAttackCount);
void ATK_MOVE(ENEMY& bossLeftHand, Object& player, int& bossAttackCoolTime, int& bossTimer, int& isShake);
void BOSS_BULLET(Object player, ENEMY& bossFace, Bullet& enemyBullet);