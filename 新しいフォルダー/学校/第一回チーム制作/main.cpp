#include "DxLib.h"
#include "main.h"

enum MapInfo
{
	None,
	Block,
	Item,
	None2,
	Wall,
};

enum SceneInfo
{
	title, game, result, pose
};

SceneInfo gameScene = title;


// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "学籍番号 名前:タイトル";

int map1[MAP_HEIGHT][MAP_WIDTH] =
{
	//		 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40
	/* 0*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/* 1*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/* 2*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/* 3*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/* 4*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/* 5*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/* 6*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/* 7*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/* 8*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/* 9*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*10*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*11*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*12*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*13*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*14*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*15*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*16*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*17*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*18*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*19*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*20*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*21*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*22*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*23*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*24*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*25*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*26*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*27*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*28*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*29*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*30*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*31*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*32*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*33*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*34*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*35*/ { 4, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*36*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*37*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*38*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*39*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*40*/ { 4, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*41*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*42*/ { 4, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*43*/ { 4, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*44*/ { 4, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*45*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 4},
	/*46*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*47*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 4},
	/*48*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*49*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 4},
	/*50*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*51*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*52*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*53*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*54*/ { 4, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*55*/ { 4, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*56*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*57*/ { 4, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*58*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*59*/ { 4, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*60*/ { 4, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 4},
	/*61*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*62*/ { 4, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 4},
	/*63*/ { 4, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*64*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 4},
	/*65*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*66*/ { 4, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 4},
	/*67*/ { 4, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*68*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*69*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*70*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*71*/ { 4, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*72*/ { 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 4},
	/*73*/ { 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*74*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 4},
	/*75*/ { 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 4},
	/*76*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*77*/ { 4, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*78*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 4},
	/*79*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*80*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 4},
	/*81*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*82*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4},
	/*83*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 4},
	/*84*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*85*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 4},
	/*86*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*87*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 4},
	/*88*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*89*/ { 4, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*90*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*91*/ { 4, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1 ,1, 1, 1, 0, 0, 1, 1, 1, 1, 4},
	/*92*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*93*/ { 4, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 4},
	/*94*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*95*/ { 4, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 2, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 4},
	/*96*/ { 4, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*97*/ { 4, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 4},
	/*98*/ { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	/*99*/ { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

//プレイヤーの位置などを初期状態にする関数
void Init_Game();

bool BoxCld(float objx, float objy, float objw, float objh, float objx2, float objy2, float objr2);

void Jump();

void SetBlock();

void MapScroll();

//void DrawMapGraph();

void graphNumberDisplayScore(float X, float Y, int number, int rank, int numberImage, int imageWidth, int imageHeight);

int exponentiation10(int a);


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0xFF);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	//音
	int startBgm;
	startBgm = LoadSoundMem("resource\\start.mp3");

	//画像
	int number;
	number = LoadGraph("resource\\number.png");
	int fever;
	fever = LoadGraph("resource\\fever.png");
	/*int block;
	block = LoadGraph("resource\\block.png");*/
	int rightPengin;
	rightPengin = LoadGraph("resource\\rightPengin.png");
	int leftPengin;
	leftPengin = LoadGraph("resource\\leftPengin.png");
	int item;
	item = LoadGraph("resource\\feather.png");
	int backGround;
	backGround = LoadGraph("resource\\iceberg_background.png");
	int block;
	block = LoadGraph("resource\\ice_block.png");
	// ゲームループで使う変数の宣言
	int drawTimer = 0;//フィーバー中のboxの色変え
	int gradCount = 0;//フィーバー中の色変え用のカウント

	int allScore = 0;//リザルト画面用スコア

	int left = 0;
	int right = 1;

	int pushSpace = 0;

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}

		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理


		switch (gameScene)
		{
			case title://タイトル画面の処理

				if (sceneSwitchingX <= 0)
				{
					sceneSwitchingX = 0;
				}

				//タイトルからゲームプレイに切り替え
				if (sceneSwitchingX == 0)
				{
					if (keys[KEY_INPUT_SPACE])
					{
						sceneSwitching = 1;
					}
				}

				if (sceneSwitching == 1)
				{
					sceneSwitchingX += 10;
				}
				else
				{
					sceneSwitchingX -= 10;
				}

				if (sceneSwitchingX >= 900)
				{
					gameScene = game;
				}

				DrawRectGraph(0 + scrollX / 4, scrollY / 4, 1024, 0, 1024, 2048, backGround, TRUE);
				DrawRectGraph(1024 + scrollX / 4, scrollY / 4, 1024, 0, 1024, 2048, backGround, TRUE);
				DrawRectGraph(0 + scrollX / 3, 1900 + scrollY / 3, 0, 0, 1024, 1024, backGround, TRUE);
				DrawRectGraph(0 + scrollX / 2, 2600 + scrollY / 2, 0, 1024, 1024, 1024, backGround, TRUE);
				DrawRectGraph(1024 + scrollX / 2, 2600 + scrollY / 2, 0, 1024, 1024, 1024, backGround, TRUE);

				DrawString(400, 400, "SPACE", GetColor(0, 0, 0));
				DrawBox(0, 0, sceneSwitchingX, WIN_HEIGHT, GetColor(200, 230, 255), TRUE);
				if (sceneSwitchingX >= WIN_WIDTH / 2 - 10)
				{
					DrawFormatString((WIN_WIDTH / 2), (WIN_HEIGHT / 2), GetColor(255, 0, 0), "SPACEでJUMP");
				}
				break;

			case game://ゲームプレイ画面の処理


				if (keys[KEY_INPUT_SPACE] == 1 && pushSpace == 0)
				{
					pushSpace = 1;
				}
				if (pushSpace == 1)
				{
					sceneSwitching = 0;
					sceneSwitchingX -= 10;
				}
				if (sceneSwitchingX <= 0)
				{
					pushSpace = 0;
					sceneSwitchingX = 0;
					//カウントダウン(3...2...1...)
					if (startTimer >= 0)
					{
						if (CheckSoundMem(startBgm) == 0)
						{
							PlaySoundMem(startBgm, DX_PLAYTYPE_BACK);
						}
						startTimer--;
					}
				}

				//制限時間の減少

				if (Fever.x + Fever.w < 97)
				{
					deFever = 0;
					addFever = 1;
				}
				else if (Fever.x + Fever.w > 179 && addFever == 1)
				{
					addFever = 0;
					deFever = 1;
				}

				/*if (addFever == 1)
				{
					Fever.w += 0.5f;
				}*/
				else if (deFever == 1)
				{
					Fever.w -= 0.2f;
				}


				//if (keys[KEY_INPUT_D] == 1)
				//{
				//	player.x = player.x + playerSpeed;//右移動
				//}

				//if (keys[KEY_INPUT_A] == 1)
				//{
				//	player.x = player.x - playerSpeed;//左移動
				//}

				//移動処理
				if (wallTouchCount <= 8 && player.x + player.w >= blockSize * 12)//9回目までの右壁とぶつかったとき
				{
					left = 1;
					right = 0;
					wallTouchCount++;
					count += (MAX_SCROLL_Y - scrollY - (player.y - player.y)) * -1;
					allScore += (MAX_SCROLL_Y - scrollY - (player.y - player.y)) * -1;
					/*count += nowScore;
					allScore += nowScore;*/
					for (int y = 0; y < MAP_HEIGHT; y++)
					{
						for (int x = 0; x < MAP_WIDTH; x++)
						{
							if (map1[y][x] == None2)
							{
								map1[y][x] = Item;
							}
						}
					}
				}
				else if (wallTouchCount >= 8 && player.x + player.w >= blockSize * 12)
				{
					wallTouchCount++;
					count += (MAX_SCROLL_Y - scrollY - (player.y - player.y)) * -1;
					allScore += (MAX_SCROLL_Y - scrollY - (player.y - player.y)) * -1;
					for (int y = 0; y < MAP_HEIGHT; y++)
					{
						for (int x = 0; x < MAP_WIDTH; x++)
						{
							if (map1[y][x] == None2)
							{
								map1[y][x] = Item;
							}
							if (map1[y][x] == Wall)
							{
								map1[y][x] = None;
							}
						}
					}
				}
				if (wallTouchCount <= 8 && player.x - player.w <= blockSize)
				{
					left = 0;
					right = 1;
					wallTouchCount++;
					count += (MAX_SCROLL_Y - scrollY - (player.y - player.y)) * -1;
					allScore += (MAX_SCROLL_Y - scrollY - (player.y - player.y)) * -1;
					for (int y = 0; y < MAP_HEIGHT; y++)
					{
						for (int x = 0; x < MAP_WIDTH; x++)
						{
							if (map1[y][x] == None2)
							{
								map1[y][x] = Item;
							}
						}
					}
				}
				else if (wallTouchCount >= 8 && player.x - player.w <= blockSize)
				{
					wallTouchCount++;
					count += (MAX_SCROLL_Y - scrollY - (player.y - player.y)) * -1;
					allScore += (MAX_SCROLL_Y - scrollY - (player.y - player.y)) * -1;
					for (int y = 0; y < MAP_HEIGHT; y++)
					{
						for (int x = 0; x < MAP_WIDTH; x++)
						{
							if (map1[y][x] == None2)
							{
								map1[y][x] = Item;
							}
							if (map1[y][x] == Wall)
							{
								map1[y][x] = None;
							}
						}
					}
				}

				if (count > 0)
				{
					count -= 9;
					score += 9;
				}



				//スタート(ここから操作が可能)
				if (startTimer <= 50)
				{

					//移動処理
					if (right == 1)
					{
						player.x = player.x + playerSpeed;
					}
					if (left == 1)
					{
						player.x = player.x - playerSpeed;
					}

					//ジャンプの回数

					if (isJumping == 0)
					{
						if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
						{
							isJumping = 1;
							jumpTimer = 18;
						}
					}
					if (deFever == 1)
					{
						if (feverJump != 0)
						{
							if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
							{
								jumpTimer = 18;
								feverJump--;
							}
						}
					}
				}
				if (startTimer <= 10)
				{
					StopSoundMem(startBgm);
				}

				Jump();

				SetBlock();

				MapScroll();

				//ポーズ画面へ
				if (keys[KEY_INPUT_P] == 1 && oldkeys[KEY_INPUT_P] == 0)
				{
					gameScene = pose;
				}

				//リザルト画面へ
				if (wallTouchCount == MAX_WALL_COUNT)
				{
					gameScene = result;
				}

				//雲のスクロール
				cloudScroll--;
				if (cloudScroll <= -1024)
				{
					cloudScroll = 0;
				}


				// 描画処理

				//背景
				//空
				DrawRectGraph(scrollX / 5, scrollY / 5, 1024, 0, 1024, 2048, backGround, TRUE);
				DrawRectGraph(scrollX / 5 + 1024, scrollY / 5, 1024, 0, 1024, 2048, backGround, TRUE);

				//雲
				DrawRectGraph(cloudScroll + scrollX / 4, 500 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(1024 + cloudScroll + scrollX / 4, 500 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(cloudScroll + scrollX / 4, 1000 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(1024 + cloudScroll + scrollX / 4, 1000 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);

				//氷山
				DrawRectGraph(0 + scrollX / 3, 1900 + scrollY / 3, 0, 0, 1024, 639, backGround, TRUE);
				DrawRectGraph(0 + scrollX / 2, 3000 + scrollY / 2, 0, 1377, 1024, 1672, backGround, TRUE);
				DrawRectGraph(1024 + scrollX / 2, 3000 + scrollY / 2, 0, 1377, 1024, 1672, backGround, TRUE);

				//プレイヤー
				/*DrawBox(player.x, player.y,
					player.x + player.w, player.y + player.h, GetColor(255, 255, 255), TRUE);*/
				if (right == 1)
				{
					DrawGraph(player.x - player.w, player.y, rightPengin, TRUE);
				}
				else if (left == 1)
				{
					DrawGraph(player.x - player.w, player.y, leftPengin, TRUE);
				}

				for (int y = 0; y < MAP_HEIGHT; y++)
				{
					for (int x = 0; x < MAP_WIDTH; x++)
					{
						br = blockSize / 2;
						yoko = x * blockSize + br + scrollX;
						tate = y * blockSize + br + scrollY;

						if (map1[y][x] == Block)
						{
							/*DrawBox(yoko - br, tate - br, yoko + br, tate + br, GetColor(0, 255, 0), TRUE);*/
							DrawGraph(yoko - br, tate - br, block, TRUE);
							/*	DrawGraph(yoko1 - br, tate - br, block, TRUE);*/
						}
						if (deFever == 0)
						{
							if (map1[y][x] == Item)
							{
								DrawGraph(yoko - br, tate - br, item, TRUE);
							}
						}
						if (map1[y][x] == Wall)
						{
							DrawGraph(yoko - br, tate - br, block, TRUE);
						}
					}
				}
				DrawFormatString(0, 0, GetColor(255, 255, 255), "%d\n %d + %d", scrollX, Fever.x, Fever.w);
				DrawFormatString(0, 60, GetColor(255, 255, 255), "%d\n%d\n%d", scrollY, addFever, deFever);
				DrawFormatString(0, 120, GetColor(255, 255, 255), "%d\n%d\n%d\n%d\n%d", isJumping, jumpTimer, player.y, feverJump, allScore);

				DrawString(10, 810, "Q...POSE", GetColor(0, 0, 0));
				DrawFormatString(400, 300, GetColor(0, 0, 0), "%d/%d\n%d", wallTouchCount, MAX_WALL_COUNT, MAX_SCROLL_Y - scrollY - (player.y - player.y));

				//ゲームスタート前のカウントダウン
				if (startTimer > 50)
				{
					DrawFormatString(400, 400, GetColor(0, 0, 0), "%d", startTimer / 50);
				}
				else if (startTimer <= 50 && startTimer > 0)
				{
					DrawString(400, 400, "START", GetColor(0, 0, 0));
				}
				else
				{

				}

				//フィーバー
				DrawGraph(feverX, feverY, fever, TRUE);
				if (deFever == 1)
				{
					drawTimer++;
					if (drawTimer > 4)
					{
						drawTimer = 0;
						gradCount++;
					}
					if (gradCount > 6)
					{
						gradCount = 0;
					}
					if (gradCount == 0)
					{
						DrawBox(Fever.x, Fever.y,
							Fever.x + Fever.w, Fever.y + Fever.h, GetColor(255, 0, 0), TRUE);
					}
					else if (gradCount == 1)
					{
						DrawBox(Fever.x, Fever.y,
							Fever.x + Fever.w, Fever.y + Fever.h, GetColor(255, 165, 0), TRUE);
					}
					else if (gradCount == 2)
					{
						DrawBox(Fever.x, Fever.y,
							Fever.x + Fever.w, Fever.y + Fever.h, GetColor(255, 255, 0), TRUE);
					}
					else if (gradCount == 3)
					{
						DrawBox(Fever.x, Fever.y,
							Fever.x + Fever.w, Fever.y + Fever.h, GetColor(0, 128, 0), TRUE);
					}
					else if (gradCount == 4)
					{
						DrawBox(Fever.x, Fever.y,
							Fever.x + Fever.w, Fever.y + Fever.h, GetColor(0, 255, 255), TRUE);
					}
					else if (gradCount == 5)
					{
						DrawBox(Fever.x, Fever.y,
							Fever.x + Fever.w, Fever.y + Fever.h, GetColor(0, 0, 255), TRUE);
					}
					else if (gradCount == 6)
					{
						DrawBox(Fever.x, Fever.y,
							Fever.x + Fever.w, Fever.y + Fever.h, GetColor(128, 0, 128), TRUE);
					}
				}
				else
				{
					DrawBox(Fever.x, Fever.y,
						Fever.x + Fever.w, Fever.y + Fever.h, GetColor(255, 0, 0), TRUE);
				}
				graphNumberDisplayScore(scoreX, scoreY, score, 4, number, 32, 64);

				DrawBox(0, 0, sceneSwitchingX, WIN_HEIGHT, GetColor(200, 230, 255), TRUE);
				if (sceneSwitchingX >= WIN_WIDTH / 2)
				{
					DrawFormatString((WIN_WIDTH / 2), (WIN_HEIGHT / 2), GetColor(255, 0, 0), "SPACEでJUMP");
				}


				break;

			case result://リザルト画面の処理
				score = allScore;
				//タイトル画面へ
				/*if (keys[KEY_INPUT_Q] == 1 && oldkeys[KEY_INPUT_Q] == 0)
				{
					gameScene = title;
					Init_Game();
				}

				DrawGraph(0 + backX / 2, 360 + backY / 2, backGround, TRUE);
				DrawGraph(1024 + backX / 2, 360 + backY / 2, backGround, TRUE);
				DrawString(400, 400, "RESULT", GetColor(0, 0, 0));
				DrawString(400, 420, "Q...TITLE", GetColor(0, 0, 0));
				graphNumberDisplayScore(300, 200, score, 4, number, 32, 64);
				break;*/
				if (keys[KEY_INPUT_Z] == 1 && oldkeys[KEY_INPUT_Z] == 0)
				{
					sceneSwitching = 1;
				}

				if (sceneSwitching == 1)
				{
					sceneSwitchingX += 10;
				}

				if (sceneSwitchingX >= 900)
				{
					Init_Game();
					sceneSwitching = 0;
					gameScene = title;
				}

				//雲のスクロール
				cloudScroll--;
				if (cloudScroll <= -1024)
				{
					cloudScroll = 0;
				}

				//背景
				//空
				DrawRectGraph(scrollX / 5, scrollY / 5, 1024, 0, 1024, 2048, backGround, TRUE);
				DrawRectGraph(scrollX / 5 + 1024, scrollY / 5, 1024, 0, 1024, 2048, backGround, TRUE);

				//雲
				DrawRectGraph(cloudScroll + scrollX / 4, 500 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(1024 + cloudScroll + scrollX / 4, 500 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(cloudScroll + scrollX / 4, 1000 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(1024 + cloudScroll + scrollX / 4, 1000 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);

				//氷山
				DrawRectGraph(0 + scrollX / 3, 1900 + scrollY / 3, 0, 0, 1024, 639, backGround, TRUE);
				DrawRectGraph(0 + scrollX / 2, 3000 + scrollY / 2, 0, 1377, 1024, 1672, backGround, TRUE);
				DrawRectGraph(1024 + scrollX / 2, 3000 + scrollY / 2, 0, 1377, 1024, 1672, backGround, TRUE);

				DrawString(400, 400, "RESULT", GetColor(0, 0, 0));
				DrawString(400, 420, "Q...TITLE", GetColor(0, 0, 0));
				graphNumberDisplayScore(300, 200, score, 4, number, 32, 64);

				DrawBox(0, 0, sceneSwitchingX, WIN_HEIGHT, GetColor(0, 0, 0), TRUE);
				break;

			case pose://ポーズ画面の処理

				////ゲームプレイ画面へ
				//if (keys[KEY_INPUT_Q] == 1 && oldkeys[KEY_INPUT_Q] == 0)
				//{
				//	gameScene = game;
				//}

				////タイトル画面へ
				//if (keys[KEY_INPUT_Z] == 1 && oldkeys[KEY_INPUT_Z] == 0)
				//{
				//	Init_Game();
				//	gameScene = title;
				//}

				//DrawGraph(0 + backX / 2, 360 + backY / 2, backGround, TRUE);
				//DrawGraph(1024 + backX / 2, 360 + backY / 2, backGround, TRUE);
				//ゲームプレイ画面へ
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
				{
					gameScene = game;
				}

				//タイトル画面へ
				if (keys[KEY_INPUT_Z] == 1 && oldkeys[KEY_INPUT_Z] == 0)
				{
					if (sceneSwitchingX == 0)
					{
						sceneSwitching = 1;
					}
				}

				if (sceneSwitching == 1)
				{
					sceneSwitchingX += 10;
				}

				if (sceneSwitchingX >= 900)
				{
					Init_Game();
					sceneSwitching = 0;
					gameScene = title;
				}

				//背景
				//空
				DrawRectGraph(scrollX / 5, scrollY / 5, 1024, 0, 1024, 2048, backGround, TRUE);
				DrawRectGraph(scrollX / 5 + 1024, scrollY / 5, 1024, 0, 1024, 2048, backGround, TRUE);

				//雲
				DrawRectGraph(cloudScroll + scrollX / 4, 500 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(1024 + cloudScroll + scrollX / 4, 500 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(cloudScroll + scrollX / 4, 1000 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(1024 + cloudScroll + scrollX / 4, 1000 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);

				//氷山
				DrawRectGraph(0 + scrollX / 3, 1900 + scrollY / 3, 0, 0, 1024, 639, backGround, TRUE);
				DrawRectGraph(0 + scrollX / 2, 3000 + scrollY / 2, 0, 1377, 1024, 1672, backGround, TRUE);
				DrawRectGraph(1024 + scrollX / 2, 3000 + scrollY / 2, 0, 1377, 1024, 1672, backGround, TRUE);

				/*DrawBox(player.x - player.w, player.y , player.x, player.y , GetColor(255, 255, 255), TRUE);*/
				if (right == 1)
				{
					DrawGraph(player.x, player.y, rightPengin, TRUE);
				}
				else if (left == 1)
				{
					DrawGraph(player.x, player.y, leftPengin, TRUE);
				}
				for (int y = 0; y < MAP_HEIGHT; y++)
				{
					for (int x = 0; x < MAP_WIDTH; x++)
					{
						br = blockSize / 2;
						yoko = x * blockSize + br + scrollX;
						tate = y * blockSize + br + scrollY;

						if (map1[y][x] == Block)
						{
							/*DrawBox(yoko - br, tate - br, yoko + br, tate + br, GetColor(0, 255, 0), TRUE);*/
							DrawGraph(yoko - br, tate - br, block, TRUE);
						}
						if (deFever == 0)
						{
							if (map1[y][x] == Item)
							{
								DrawGraph(yoko - br, tate - br, item, TRUE);
							}
						}
						if (map1[y][x] == Wall)
						{
							DrawGraph(yoko - br, tate - br, block, TRUE);
						}

					}
				}
				graphNumberDisplayScore(300, 200, score, 4, number, 32, 64);
				DrawString(400, 400, "POSE", GetColor(0, 0, 0));
				DrawString(400, 420, "Q...BACK", GetColor(0, 0, 0));
				DrawString(400, 440, "Z...TITLE", GetColor(0, 0, 0));

				DrawBox(0, 0, sceneSwitchingX, WIN_HEIGHT, GetColor(0, 0, 0), TRUE);
				break;
		}
		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}

	//音データ
	DeleteSoundMem(startBgm);
	//画像データ
	DeleteGraph(number);
	DeleteGraph(fever);
	DeleteGraph(block);
	DeleteGraph(rightPengin);
	DeleteGraph(leftPengin);
	DeleteGraph(item);
	DeleteGraph(backGround);
	DeleteGraph(block);
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
void Init_Game()
{
	scrollX = 0;
	scrollY = MAX_SCROLL_Y;
	player.x = 150;
	player.y = 64 * 12;
	isJumping = 0;
	jumpTimer = 0;
	wallTouchCount = 0;
	startTimer = 200;

	if (playerSpeed < 0)
	{
		playerSpeed *= -1;
	}

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (map1[y][x] == None2)
			{
				map1[y][x] = Item;
			}
		}
	}
}
//当たり判定
bool BoxCld(float objx, float objy, float objw, float objh, float objx2, float objy2, float objr2)
{
	return  objx + objw > objx2 - objr2 &&
		objy + objh > objy2 - objr2 &&
		objx - objw < objx2 + objr2 &&
		objy - objh < objy2 + objr2;
}
//ジャンプ
void Jump()
{
	/*oldPosx = playerX;*/
	oldPosy = player.y;
	jumpTimer--;
	player.y = player.y - jumpTimer;

	//終端速度
	if (jumpTimer < -18)
	{
		jumpTimer = -18;
	}
}

void SetBlock()
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			br = blockSize / 2;
			yoko = x * blockSize + br + scrollX;
			tate = y * blockSize + br + scrollY;

			if (map1[y][x] == 1)
			{
				if (BoxCld(player.x, player.y, player.w, player.h, yoko, tate, br))
				{
					//
					if (player.y + player.h < tate && jumpTimer <= 0)
					{
						player.y = tate - br - player.h;
						jumpTimer = 0;
						isJumping = 0;
						feverJump = 2;

					}

					else if (player.x - player.w + 18 > yoko + br)
					{
						player.x = yoko + br + player.w;
					}

					else if (player.x + player.w - 18 < yoko - br)
					{
						player.x = yoko - br - player.w;
					}

					else if (player.y - player.h > tate && jumpTimer > 0)
					{
						player.y = tate + br + player.h;
						jumpTimer = 0;
					}
				}
			}
			else if (map1[y][x] == Item)
			{
				/*if(player,y < tate)*/
				if (deFever == 0)
				{
					if (BoxCld(player.x, player.y, player.w, player.h, yoko, tate, br))
					{
						if (player.y + player.h > tate - br)
						{
							map1[y][x] = None2;
							Fever.w += 20.0f;
						}
						else if (player.x - player.w + 18 > yoko + br)
						{
							map1[y][x] = None2;
							Fever.w += 20.0f;
						}

						else if (player.x + player.w - 18 < yoko - br)
						{
							map1[y][x] = None2;
							Fever.w += 20.0f;
						}

						else if (player.y - player.h > tate + br)
						{
							map1[y][x] = None2;
							Fever.w += 20.0f;
						}
					}
				}
			}
		}
	}
}

//void DrawMapGraph()
//{
//	for (int y = 0; y < MAP_HEIGHT; y++)
//	{
//		for (int x = 0; x < MAP_WIDTH; x++)
//		{
//			br = blockSize / 2;
//			yoko1 = x * blockSize + br + backX;
//			tate = y * blockSize + br + backY;
//
//			if (map1[y][x] == 1 || map1[y][x] == 2)
//			{
//				/*DrawBox(yoko1 - br, tate - br, yoko1 + br, tate + br, GetColor(0, 255, 0), TRUE);*/
//				
//			}
//		}
//	}
//}

//マップスクロール
void MapScroll()
{
	//右へのスクロール
	if (player.x > WIN_WIDTH / 2 + 10 && scrollX > MAX_SCROLL_X)
	{
		scrollX = scrollX - scrollSpeed;
		player.x = WIN_WIDTH / 2 + 10;
	}
	//左へのスクロール
	if (player.x < WIN_WIDTH / 2 - 10 && scrollX < 0)
	{
		scrollX = scrollX + scrollSpeed;
		player.x = WIN_WIDTH / 2 - 10;
	}
	//上下へのスクロール
	if (player.y < oldPosy)
	{
		if (player.y < WIN_HEIGHT / 2 - 20 && scrollY < 0)
		{
			player.y = (WIN_HEIGHT / 2 - 20);
			scrollY = scrollY + jumpTimer;
		}
	}
	else if (player.y > oldPosy)
	{
		if (player.y > WIN_HEIGHT / 2 + 20 && scrollY > MAX_SCROLL_Y)
		{
			player.y = (WIN_HEIGHT / 2 + 20) + 5;
			scrollY = scrollY + jumpTimer;
		}
	}

	/*if (player.y < oldPosy)
	{
		if (player.y < WIN_HEIGHT / 2 && backY <= 0)
		{
			player.y = WIN_HEIGHT / 2;
			backY = backY + jumpTimer;
		}
	}
	else if (player.y > oldPosy)
	{
		if (player.y > WIN_HEIGHT / 2 && backY > MAX_SCROLL_Y)
		{
			player.y = WIN_HEIGHT / 2;
			backY = backY + jumpTimer;
		}
	}*/
	if (scrollX > 0)
	{
		scrollX = 0;
	}

	if (scrollY > 0)
	{
		scrollY = 0;
	}

	if (scrollX < MAX_SCROLL_X)
	{
		scrollX = MAX_SCROLL_X;
	}

	if (scrollY < MAX_SCROLL_Y)
	{
		scrollY = MAX_SCROLL_Y;
	}

}
//桁を決め全てに数字を画像で表示する関数(数字がない場合は０を出力)
void graphNumberDisplayScore(float X, float Y, int number, int rank, int numberGraph, int GraphWidth, int GraphHeight)
{
	int outputNumber = 0;
	for (int i = rank; i >= 0; i--)
	{
		outputNumber = number / exponentiation10(i);
		if (outputNumber > 9)
		{
			outputNumber = outputNumber % 10;
		}
		DrawRectGraph(X + GraphWidth * (rank - i), Y, GraphWidth * outputNumber, 0, GraphWidth, GraphHeight, numberGraph, true, false);
	}
}

//累乗の関数
int exponentiation10(int a)
{
	int ans = 0;
	if (a == 0)
	{
		return 1;
	}

	for (int i = 0; i < a; i++)
	{
		if (ans == 0)
		{
			ans = 10;
		}
		else
		{
			ans = ans * 10;
		}
	}

	return ans;
}


