#pragma once

typedef struct Transform {
	float x;
	float y;
	float r;
}Transform;

typedef struct Object {
	Transform transform;
	float velocityX;
	float velocityY;
	float speedX;
	float speedY;
	int hp;
	int invincibleTime;
}Object;

typedef struct Mouse {
	int x;
	int y;
	int isLeftPush;
	int isRightPush;
}Mouse;

typedef struct Cross {
	float first;
	float seccond;
	float third;
	float angle;
}Crros;

typedef struct Shield {
	Crros crros[16];
	Transform point1;
	Transform point2;

	int state;
	int isShieldOn;

	float level;
	const int max;
	int rechargeTimer;
	int radius;

	int parryTimer;
	int isParry;
	int parrynow;
}Shield;

//�V�[���h�̏�Ԃ�enum
enum shieldState {
	nomal,		//0,�ʏ펞
	scraped,	//1,��ꂽ��
	recharge,	//2,���`���[�W��
	crack,		//3,���ꂽ��
};

typedef struct Boomerang {

	Object object;
	Crros crros;
	float accerarationX;
	float accerarationY;
	int isThrown;
	int state;
	int flyingTimer;
	float returnSpeed;
	int damage;
}Boomerang;

//�G�̏�����
typedef struct ATK {
	int isAtk;
	int atkJudgmentRadius;
	int atkPower;
	int moveFaze;
	double speedX;
	double speedY;
};

typedef struct ENEMY {
	ATK atk;
	double posX;
	double posY;
	int radius;
	int hitPoint;
	int initPosX;	//�����ʒu
	int initPosY;
	int attackType;
	int invincibleTime;
	int respawnTimer;
};

typedef struct Bullet {
	Object object;
	Crros crros;
	int isShot;
	int damage;
	int speed;
	float enemyBullet2playerX;
	float enemyBullet2playerY;
	int timer;
	int coolTime;
};