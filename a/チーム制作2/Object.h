#pragma once
#include"Struct.h"

class Object
{
public:

	//クラスに構造体を取り入れる
	//座標
	Transform transform;
	//当たり判定用の角
	CollisionPoint collisionPoint;

	//重力
	int hasGravity;
	//空中にいるかどうか
	int isFlying;
	float gravitySpeed;

	float BottomYInfo;
	float BottomYMaptip;
	float BottomYHeight;
	float BottomYHeightPlus;
	float BottomYMaptipPlus;
	float TopYInfo;
	float TopYMaptip;
	float TopYHeight;
	float MoveCollision;

	//重力
	void gravity();

	//落下処理
	void fallProcess();

	//現在位置を測定する用の関数
	void posInfo();

	void ObjectMoveCollision();

	//コンストラクタ
	Object(Transform transform, CollisionPoint collisionPoint);
	//デストラクタ
	~Object();

private:

};

