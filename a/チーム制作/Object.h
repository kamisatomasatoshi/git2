#pragma once
#include"Struct.h"

class Object
{
public:

	//クラスに構造体を取り入れる
	Transform transform;


	//コンストラクタ
	Object(Transform transform);
	//デストラクタ
	~Object();

private:

};

