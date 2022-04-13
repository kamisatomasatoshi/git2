#pragma once
#include "structure.h"
// �E�B���h�E����
const int WIN_WIDTH = 1280;

// �E�B���h�E�c��
const int WIN_HEIGHT = 768;

//�~����
const double pi = 3.141592;

//�n�ʂ̍���
const int groundHeightY = 192;

const int BLOCK_SIZE = 64;

//�`��
int randomX = 0;
int randomY = 0;
int isShake = 0;
int shakeTimer = 10;
int runAnmNB[4] = {};	//NB��Ԃ̑���A�j���[�V����
int runAnm[4] = {};	//����A�j���[�V����
int jumpPng = 0;
int jumpPngNB = 0;
int airJumpPng = 0;
int airJumpPngNB = 0;
int charaIdlePng = 0;
int charaIdleNBPng = 0;
int stagePng = 0;
int gameOverAnm[7] = {};	//�Q�[���N���A���
int gameClearAnm[7] = {};	//�Q�[���N���A���
int gameOverAnmTimer = 0;	//�Q�[���I�[�o�[�̃A�j���[�V�����^�C�}�[
int backgroundBack;
int backgroundFore;
int backgroundSky;

int backgroundScroll[3] = { 0,0,0 };	//�w�i�A�j���[�V�����^�C�}�[�J�E���g
int mapchip[20];	//�n�ʂ��Q��
int charaAnm[6] = {};
int roboRunAnm[3] = {};
int roboIdleAnm[2] = {};
int goalGraph;

int moveKeys;
int moveKeysA;
int moveKeysD;
int spece;
int speceUse;

int mousenone;
int mouseRight;
int mouseLeft;
int notUse;
int boomerangIcon;
int shieldIcon;

int handPng;
int boomerangPng;

float boomerangAngle = 0;
float airJumpCharaAngle = 0;

// �Q�[�����[�v�Ŏg���ϐ��̐錾
const int mapCountX = 38;	//�}�b�v�̍ő�l
const int mapCountY = 52;	//�}�b�v�̍ő�l
const int blockSize = 64;	//�u���b�N�T�C�Y
int mouse_x = 0;	//�}�E�X���W
int mouse_y = 0;
bool pushFlagW = false;
bool pushFlagA = false;
bool pushFlagS = false;
bool pushFlagD = false;
bool isPendulumMode = false;

//�G�̋���
int bossAttackCoolTime = 0;
int bossAttackPattern = 0;
int bossTimer = 0;
int bossAttackCount = 0;

const int enemyBulletNum = 16;

int downCount = 1;

//���@�̋���

int playerLife = 5;	//�q�b�g�|�C���g
int posX = 50;	//X���W�̈ʒu
int posY = 20;	//Y���W�̈ʒu
int posOldX = 0;
int posOldY = 0;
double playerSpeedX = 0.0;	//X���W�̃X�s�[�h
double playerSpeedY = 0.0;	//Y���W�̃X�s�[�h
int leftTopX = 0;
int leftTopY = 0;
int leftBottomX = 0;
int leftBottomY = 0;
int rightTopX = 0;
int rightTopY = 0;
int rightBottomX = 0;
int rightBottomY = 0;
int playerRadius = 16;
int oldleftTopX = 0;
int oldleftTopY = 0;
int oldleftBottomX = 0;
int oldleftBottomY = 0;
int oldrightTopX = 0;
int oldrightTopY = 0;
int oldrightBottomX = 0;
int oldrightBottomY = 0;
int rightScrStartX = 470;	//�X�N���[���J�n�̈ʒu
int leftScrStartX = 350;
int upScrStartY = 150;	//�X�N���[���J�n�̈ʒu
int downScrStartY = 460;
int jumpCount = 0;
int jumpHeight = 32;
int isJump = 0;
int isAirjump = 0;
int isIdle = 0;
int isRun = 0;
int isLeftRun = 0;
int isAir = 0;
int isRightWallSlip = 0;
int isLeftWallSlip = 0;
int isInvincible = 0;
int cAnimCount = 0;
int orientation = 0;
double fallDistance = 0.0;	//��������
int invinsibleTimer = 0;

int parryAtkAnmTimer = 0;

float ugoku = 0;
float ugokuSpeed = 0.2;

ENEMY bossRightHand{
	{	//ATK
		0,	//isAtk
		64,//atkJudgmentRadius
		10,	//atkPower
		0	//moveFaze
	},
	880,//posX
	300,//posY
	64,	//radius
	100,//hitPoint
	880,//initPosX
	300,//initPosY
	0	//attackType
};

ENEMY bossLeftHand{
	{	//ATK
		0,	//isAtk;
		64,//atkJudgmentRadius;
		10,	//atkPower;
		0	//moveFaze;
	},
	400,//posX
	300,//posY
	64,	//radius
	100,//hitPoint
	400,//initPosX	
	300,//initPosY
	0	//attackType
};

ENEMY bossFace{
		{	//ATK
		0,	//isAtk;
		48,//atkJudgmentRadius;
		10,	//atkPower;
		0	//moveFaze;
	},
	640,//posX
	200,//posY
	96,	//radius
	2000,//hitPoint
	640,//initPosX	
	200,//initPosY
	0	//attackType
};

Bullet enemyBullet{
	{//Object
		{//Transfrom
			0,//x
			0,//y
			16//r
		},
		0,//verocityX
		0,//verocityY
		0,//speedX
		0//speedY
		},
	{//crros
		0,//first
		0,//second
		0,//third
		pi / 2//angle
	},
	0,//isShot
	1,//damage
	20,//speed
	0,//enemyBullet2playerX
	0,//enemyBullet2playerY
	0,//timer
	0 //coolTime

};

Object player{
		{//transform
			300,//x
			200,//y
			20	//r
		},
	10,//velocityX;
	10,//velocityY;
	0, //speedX;
	0, //speedY;
	3, //hp;
	0  //invincibleTime
};

Shield playerShield{
	{//Crros
		{0},//cross1
		{0},//cross2
		{0}, //cross3
		0//angle
	},
	{//point1
		0,//x
		0,//y
		0//r,
	},
	{//point2
		0,//x
		0,//y
		0//r
	},
	0,//state
	0,//isShieldOn

	80,//level
	80,//max
	0,//rechargeTimer
	70,//radius
	0,//parryTimer
	0,//isParry
	0,//parrynow

};


Mouse mouseStructure{
	0,//x
	0,//y
	0,//isLeftPush;
	0,//isRihgtPush
};

Boomerang boomerang{
	{//Object
		{//Transfrom
			0,//x
			0,//y
			16//r
		},
		0,//verocityX
		0,//verocityY
		0,//speedX
		0//speedY
		},
	{//crros
		0,//first
		0,//second
		0,//third
		pi / 2//angle
	},
	0,//accerarationX
	0,//accerarationY
	0,//isTrown
	0,//state
	0,//flyingTimer
	0.2,//returnSpeed
	5,//damage
};
Transform target{
	0,//x
	0,//y
	1.5//r
};

//�V�[���Ǘ�
int scene = 0;
int startSceneTimer = 0;

// �ŐV�̃L�[�{�[�h���p
char keys[256] = { 0 };

// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
char oldkeys[256] = { 0 };
