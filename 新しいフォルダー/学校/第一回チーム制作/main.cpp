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


// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "�w�Дԍ� ���O:�^�C�g��";

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

//�v���C���[�̈ʒu�Ȃǂ�������Ԃɂ���֐�
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
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0xFF);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	//��
	int startBgm;
	startBgm = LoadSoundMem("resource\\start.mp3");

	//�摜
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
	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	int drawTimer = 0;//�t�B�[�o�[����box�̐F�ς�
	int gradCount = 0;//�t�B�[�o�[���̐F�ς��p�̃J�E���g

	int allScore = 0;//���U���g��ʗp�X�R�A

	int left = 0;
	int right = 1;

	int pushSpace = 0;

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}

		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����


		switch (gameScene)
		{
			case title://�^�C�g����ʂ̏���

				if (sceneSwitchingX <= 0)
				{
					sceneSwitchingX = 0;
				}

				//�^�C�g������Q�[���v���C�ɐ؂�ւ�
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
					DrawFormatString((WIN_WIDTH / 2), (WIN_HEIGHT / 2), GetColor(255, 0, 0), "SPACE��JUMP");
				}
				break;

			case game://�Q�[���v���C��ʂ̏���


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
					//�J�E���g�_�E��(3...2...1...)
					if (startTimer >= 0)
					{
						if (CheckSoundMem(startBgm) == 0)
						{
							PlaySoundMem(startBgm, DX_PLAYTYPE_BACK);
						}
						startTimer--;
					}
				}

				//�������Ԃ̌���

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
				//	player.x = player.x + playerSpeed;//�E�ړ�
				//}

				//if (keys[KEY_INPUT_A] == 1)
				//{
				//	player.x = player.x - playerSpeed;//���ړ�
				//}

				//�ړ�����
				if (wallTouchCount <= 8 && player.x + player.w >= blockSize * 12)//9��ڂ܂ł̉E�ǂƂԂ������Ƃ�
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



				//�X�^�[�g(�������瑀�삪�\)
				if (startTimer <= 50)
				{

					//�ړ�����
					if (right == 1)
					{
						player.x = player.x + playerSpeed;
					}
					if (left == 1)
					{
						player.x = player.x - playerSpeed;
					}

					//�W�����v�̉�

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

				//�|�[�Y��ʂ�
				if (keys[KEY_INPUT_P] == 1 && oldkeys[KEY_INPUT_P] == 0)
				{
					gameScene = pose;
				}

				//���U���g��ʂ�
				if (wallTouchCount == MAX_WALL_COUNT)
				{
					gameScene = result;
				}

				//�_�̃X�N���[��
				cloudScroll--;
				if (cloudScroll <= -1024)
				{
					cloudScroll = 0;
				}


				// �`�揈��

				//�w�i
				//��
				DrawRectGraph(scrollX / 5, scrollY / 5, 1024, 0, 1024, 2048, backGround, TRUE);
				DrawRectGraph(scrollX / 5 + 1024, scrollY / 5, 1024, 0, 1024, 2048, backGround, TRUE);

				//�_
				DrawRectGraph(cloudScroll + scrollX / 4, 500 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(1024 + cloudScroll + scrollX / 4, 500 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(cloudScroll + scrollX / 4, 1000 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(1024 + cloudScroll + scrollX / 4, 1000 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);

				//�X�R
				DrawRectGraph(0 + scrollX / 3, 1900 + scrollY / 3, 0, 0, 1024, 639, backGround, TRUE);
				DrawRectGraph(0 + scrollX / 2, 3000 + scrollY / 2, 0, 1377, 1024, 1672, backGround, TRUE);
				DrawRectGraph(1024 + scrollX / 2, 3000 + scrollY / 2, 0, 1377, 1024, 1672, backGround, TRUE);

				//�v���C���[
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

				//�Q�[���X�^�[�g�O�̃J�E���g�_�E��
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

				//�t�B�[�o�[
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
					DrawFormatString((WIN_WIDTH / 2), (WIN_HEIGHT / 2), GetColor(255, 0, 0), "SPACE��JUMP");
				}


				break;

			case result://���U���g��ʂ̏���
				score = allScore;
				//�^�C�g����ʂ�
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

				//�_�̃X�N���[��
				cloudScroll--;
				if (cloudScroll <= -1024)
				{
					cloudScroll = 0;
				}

				//�w�i
				//��
				DrawRectGraph(scrollX / 5, scrollY / 5, 1024, 0, 1024, 2048, backGround, TRUE);
				DrawRectGraph(scrollX / 5 + 1024, scrollY / 5, 1024, 0, 1024, 2048, backGround, TRUE);

				//�_
				DrawRectGraph(cloudScroll + scrollX / 4, 500 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(1024 + cloudScroll + scrollX / 4, 500 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(cloudScroll + scrollX / 4, 1000 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(1024 + cloudScroll + scrollX / 4, 1000 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);

				//�X�R
				DrawRectGraph(0 + scrollX / 3, 1900 + scrollY / 3, 0, 0, 1024, 639, backGround, TRUE);
				DrawRectGraph(0 + scrollX / 2, 3000 + scrollY / 2, 0, 1377, 1024, 1672, backGround, TRUE);
				DrawRectGraph(1024 + scrollX / 2, 3000 + scrollY / 2, 0, 1377, 1024, 1672, backGround, TRUE);

				DrawString(400, 400, "RESULT", GetColor(0, 0, 0));
				DrawString(400, 420, "Q...TITLE", GetColor(0, 0, 0));
				graphNumberDisplayScore(300, 200, score, 4, number, 32, 64);

				DrawBox(0, 0, sceneSwitchingX, WIN_HEIGHT, GetColor(0, 0, 0), TRUE);
				break;

			case pose://�|�[�Y��ʂ̏���

				////�Q�[���v���C��ʂ�
				//if (keys[KEY_INPUT_Q] == 1 && oldkeys[KEY_INPUT_Q] == 0)
				//{
				//	gameScene = game;
				//}

				////�^�C�g����ʂ�
				//if (keys[KEY_INPUT_Z] == 1 && oldkeys[KEY_INPUT_Z] == 0)
				//{
				//	Init_Game();
				//	gameScene = title;
				//}

				//DrawGraph(0 + backX / 2, 360 + backY / 2, backGround, TRUE);
				//DrawGraph(1024 + backX / 2, 360 + backY / 2, backGround, TRUE);
				//�Q�[���v���C��ʂ�
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
				{
					gameScene = game;
				}

				//�^�C�g����ʂ�
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

				//�w�i
				//��
				DrawRectGraph(scrollX / 5, scrollY / 5, 1024, 0, 1024, 2048, backGround, TRUE);
				DrawRectGraph(scrollX / 5 + 1024, scrollY / 5, 1024, 0, 1024, 2048, backGround, TRUE);

				//�_
				DrawRectGraph(cloudScroll + scrollX / 4, 500 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(1024 + cloudScroll + scrollX / 4, 500 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(cloudScroll + scrollX / 4, 1000 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);
				DrawRectGraph(1024 + cloudScroll + scrollX / 4, 1000 + scrollY / 4, 0, 736, 1024, 528, backGround, TRUE);

				//�X�R
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
		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}

	//���f�[�^
	DeleteSoundMem(startBgm);
	//�摜�f�[�^
	DeleteGraph(number);
	DeleteGraph(fever);
	DeleteGraph(block);
	DeleteGraph(rightPengin);
	DeleteGraph(leftPengin);
	DeleteGraph(item);
	DeleteGraph(backGround);
	DeleteGraph(block);
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
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
//�����蔻��
bool BoxCld(float objx, float objy, float objw, float objh, float objx2, float objy2, float objr2)
{
	return  objx + objw > objx2 - objr2 &&
		objy + objh > objy2 - objr2 &&
		objx - objw < objx2 + objr2 &&
		objy - objh < objy2 + objr2;
}
//�W�����v
void Jump()
{
	/*oldPosx = playerX;*/
	oldPosy = player.y;
	jumpTimer--;
	player.y = player.y - jumpTimer;

	//�I�[���x
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

//�}�b�v�X�N���[��
void MapScroll()
{
	//�E�ւ̃X�N���[��
	if (player.x > WIN_WIDTH / 2 + 10 && scrollX > MAX_SCROLL_X)
	{
		scrollX = scrollX - scrollSpeed;
		player.x = WIN_WIDTH / 2 + 10;
	}
	//���ւ̃X�N���[��
	if (player.x < WIN_WIDTH / 2 - 10 && scrollX < 0)
	{
		scrollX = scrollX + scrollSpeed;
		player.x = WIN_WIDTH / 2 - 10;
	}
	//�㉺�ւ̃X�N���[��
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
//�������ߑS�Ăɐ������摜�ŕ\������֐�(�������Ȃ��ꍇ�͂O���o��)
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

//�ݏ�̊֐�
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


