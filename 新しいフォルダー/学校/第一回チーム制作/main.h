#pragma once

typedef struct obj
{
	float x;
	int y;
	float w;
	int h;
};
obj Fever =
{
	98.0f,
	13,
	0.0f,
	18,
};
typedef struct obj2
{
	int x;
	int y;
	int w;
	int h;

};
obj2 player =
{
	150,
	64 * 12,
	24,
	16
};

// �E�B���h�E����
const int WIN_WIDTH = 64 * 13;

// �E�B���h�E�c��
const int WIN_HEIGHT = 64 * 13;

const int MAP_WIDTH = 40;
const int MAP_HEIGHT = 100;

const int MAX_SCROLL_X = (-64 * MAP_WIDTH) + WIN_WIDTH;
const int MAX_SCROLL_Y = (-64 * MAP_HEIGHT) + WIN_HEIGHT;

int blockSize = 64;

int isJumping = 0;//�t���O
int jumpTimer = 0;
int jumpCount = 0;//��

int oldPosx;
int oldPosy;

int playerLeft = 0;
int playerRight = 0;
int playerTop = 0;
int playerBottom = 0;

int playerSpeed = 6;
int scrollSpeed = playerSpeed;

//�X�R�A
int score = 0;
int count = 0;
//�^�C��
int timer = 60;
int countTimer = 60;
int startTimer = 200;
//�t�B�[�o�[
int feverX = 50;
int feverY = 10;
int addFever = 1;
int deFever = 0;

int scoreX = 600;
int numberX2 = 50;
int scoreY = 0;

int feverJump = 2;

int yoko;
int tate;
int br;
int scrollX = 0;
int scrollY = MAX_SCROLL_Y;

int cloudScroll = 0;

//�V�[���؂�ւ��̉��o
int sceneSwitching = 0;
int sceneSwitchingX = 0;


//�Ǌ֌W
const int MAX_WALL_COUNT = 10;
int wallTouchCount = 0;

//�V�[��

// �ŐV�̃L�[�{�[�h���p
char keys[256] = { 0 };

// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
char oldkeys[256] = { 0 };
