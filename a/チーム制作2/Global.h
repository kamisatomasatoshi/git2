#pragma once

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LC1B_20_ニッタシンジ: チーム制作第三回 ";

// ウィンドウ横幅
const int WIN_WIDTH = 1000;

// ウィンドウ縦幅
const int WIN_HEIGHT = 1000;

// 最新のキーボード情報用
extern char keys[256];

// 1ループ(フレーム)前のキーボード情報
extern char prev[256];

//キーボード情報更新関数
void KeyUpdate();

//サイズの変数
const int BLOCK_SIZE = 32;
///const int MAP_SIZE = 32;
const int PLAYER_SIZE = 32;

// ブロック全体の高さ
const int MAP_HEIGHT = 30;
// ブロック全体の横幅
const int MAP_WIDTH = 30;

//jumpheightの最大値
const int MAX_JUMP = 20;

////map全体のサイズ
//const int MAP_SIZE_Y = MAP_HEIGHT * BLOCK_SIZE;
//const int MAP_SIZE_X = MAP_WIDTH * BLOCK_SIZE;

//map全体のサイズ
const int MAP_SIZE_Y = 30;
const int MAP_SIZE_X = 30;



