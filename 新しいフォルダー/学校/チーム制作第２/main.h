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
	498.0f,
	13,
	0.0f,
	18,
};
typedef struct obj2
{
	int x;
	int y;
	int r;

};
obj2 player =
{
	100,
	64 * 12,
	16,
};

// ウィンドウ横幅
const int WIN_WIDTH = 64 * 13;

// ウィンドウ縦幅
const int WIN_HEIGHT = 64 * 13;

const int MAP_WIDTH = 40;
const int MAP_HEIGHT = 30;

const int MAX_SCROLL_X = (-64 * MAP_WIDTH) + WIN_WIDTH;
const int MAX_SCROLL_Y = (-64 * MAP_HEIGHT) + WIN_HEIGHT;

int blockSize = 64;

int isJumping[2] = {0};
int jumpTimer = 0;
int playerX = 100;
int playerY = 350;
int playerR = 16;

int oldPosX = 0;
int oldPosY = 0;

int playerLeft = 0;
int playerRight = 0;
int playerTop = 0;
int playerBottom = 0;

int playerSpeed = 6;
int scrollSpeed = playerSpeed;

//スコア
int score = 0;
int count = 0;
//タイム
int timer = 60;
int countTimer = 60;
//フィーバー
int feverX = 450;
int feverY = 10;
int addFever = 1;
int deFever = 0;

int scoreX = 600;
int numberX2 = 50;
int scoreY = 0;

int yoko;
int tate;
int br;
int backX = 0;
int backY = MAX_SCROLL_Y;

// 最新のキーボード情報用
char keys[256] = { 0 };

// 1ループ(フレーム)前のキーボード情報
char oldkeys[256] = { 0 };
