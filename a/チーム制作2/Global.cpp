#include"DxLib.h"
#include"Global.h"

// 最新のキーボード情報用
char keys[256] = { 0 };

// 1ループ(フレーム)前のキーボード情報
char prev[256] = { 0 };

//キーボード情報更新関数
void KeyUpdate()
{
	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; ++i) {
		prev[i] = keys[i];
	}

	//キーボード情報を入力
	GetHitKeyStateAll(keys);
}
