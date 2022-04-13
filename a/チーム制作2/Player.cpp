#include"DxLib.h"
#include"Player.h"

//コンストラクタ
//座標の初期化
Player::Player()
{
	defaultSpped = 4.0f;
	jumpCount = 1;
	jumpHeight = 20;
}

//デストラクタ
Player::~Player()
{
	delete object;
}

void Player::PlayerMoveCollision()
{
	//右上
	object->collisionPoint.rightTopX = (object->transform.posX + object->transform.radiusX - 1) / BLOCK_SIZE;
	object->collisionPoint.rightBottomX = (object->transform.posX + object->transform.radiusX - 1) / BLOCK_SIZE;
	//右下
	object->collisionPoint.rightTopY = (object->transform.posY - object->transform.radiusY) / BLOCK_SIZE;
	object->collisionPoint.rightBottomY = (object->transform.posY + object->transform.radiusY - 1) / BLOCK_SIZE;
	//左上
	object->collisionPoint.leftTopX = (object->transform.posX - object->transform.radiusX) / BLOCK_SIZE;
	object->collisionPoint.leftBottomX = (object->transform.posX - object->transform.radiusX) / BLOCK_SIZE;
	//左下
	object->collisionPoint.leftTopY = (object->transform.posY - object->transform.radiusY) / BLOCK_SIZE;
	object->collisionPoint.leftBottomY = (object->transform.posY + object->transform.radiusY - 1) / BLOCK_SIZE;
}

void Player::PlayerMove()
{
	object->transform.oldX = object->transform.posX;
	object->transform.oldY = object->transform.posY;

	PlayerMoveCollision();

	if (keys[KEY_INPUT_A] == 1)
	{
		if (object->transform.posX > BLOCK_SIZE) //画面内で動くように範囲を設定
		{
			object->collisionPoint.rightTopX = ((object->transform.posX - object->transform.speedX) + object->transform.radiusX - 1) / BLOCK_SIZE;
			object->collisionPoint.rightBottomX = ((object->transform.posX - object->transform.speedX) + object->transform.radiusX - 1) / BLOCK_SIZE;
			object->collisionPoint.leftTopX = ((object->transform.posX - object->transform.speedX) - object->transform.radiusX) / BLOCK_SIZE;
			object->collisionPoint.leftBottomX = ((object->transform.posX - object->transform.speedX) - object->transform.radiusX) / BLOCK_SIZE;
			object->collisionPoint.leftTopY = (object->transform.posY - object->transform.radiusX) / BLOCK_SIZE;
			object->collisionPoint.leftBottomY = (object->transform.posY + object->transform.radiusX - 1) / BLOCK_SIZE;

			if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX] == BLOCK)
			{
				object->transform.speedX /= 2;

				//縦隣りにも横隣りの両方に進める
				if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX + 1] != BLOCK && map[object->collisionPoint.leftTopY + 1][object->collisionPoint.leftTopX] != BLOCK)
				{

				}
				//縦隣りには進めないが横隣りには進める場合
				else if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX + 1] == BLOCK && map[object->collisionPoint.leftTopY + 1][object->collisionPoint.leftTopX] != BLOCK)
				{
					object->transform.posY = object->transform.oldY;
				}
				//縦隣りには進めるが横隣りには進めない場合
				else if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX + 1] != BLOCK && map[object->collisionPoint.leftTopY + 1][object->collisionPoint.leftTopX] == BLOCK)
				{
					object->transform.posX = object->transform.oldX;
				}
				//縦隣りにも横隣りにも進めない場合
				else if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX + 1] == BLOCK && map[object->collisionPoint.leftTopY + 1][object->collisionPoint.leftTopX] == BLOCK)
				{
					object->transform.posY = object->transform.oldY;
					object->transform.posX = object->transform.oldX;
				}
			}
			else if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX] == BLOCK)
			{
				object->transform.speedX /= 2;

				//縦隣りにも横隣りの両方に進める
				if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] != BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] != BLOCK)
				{

				}
				//縦隣りには進めないが横隣りには進める場合
				else if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] == BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] != BLOCK)
				{
					object->transform.posY = object->transform.oldY;
				}
				//縦隣りには進めるが横隣りには進めない場合
				else if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] != BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] == BLOCK)
				{
					object->transform.posX = object->transform.oldX;
				}
				//縦隣りにも横隣りにも進めない場合
				else if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] == BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] == BLOCK)
				{
					object->transform.posY = object->transform.oldY;
					object->transform.posX = object->transform.oldX;
				}
			}
			else
			{
				object->transform.posX -= object->transform.speedX;
			}
		}
	}

	if (keys[KEY_INPUT_D] == 1)
	{
		if (object->transform.posX < MAP_SIZE_X * BLOCK_SIZE) //画面内で動くように範囲を設定
		{
			object->collisionPoint.rightTopX = ((object->transform.posX + object->transform.speedX) + object->transform.radiusX - 1) / BLOCK_SIZE;
			object->collisionPoint.rightBottomX = ((object->transform.posX + object->transform.speedX) + object->transform.radiusX - 1) / BLOCK_SIZE;
			object->collisionPoint.leftTopX = ((object->transform.posX + object->transform.speedX) - object->transform.radiusX) / BLOCK_SIZE;
			object->collisionPoint.leftBottomX = ((object->transform.posX + object->transform.speedX) - object->transform.radiusX) / BLOCK_SIZE;
			object->collisionPoint.rightTopY = (object->transform.posY - object->transform.radiusY) / BLOCK_SIZE;
			object->collisionPoint.rightBottomY = (object->transform.posY + object->transform.radiusY - 1) / BLOCK_SIZE;

			//ブロックに当たった際の押し戻しの処理
			if (map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX] == BLOCK)
			{
				//縦隣りにも横隣りの両方に進める
				if (map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX - 1] != BLOCK && map[object->collisionPoint.rightTopY + 1][object->collisionPoint.rightTopX] != BLOCK)
				{

				}
				//縦隣りには進めないが横隣りには進める場合
				else if (map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX - 1] == BLOCK && map[object->collisionPoint.rightTopY + 1][object->collisionPoint.rightTopX] != BLOCK)
				{
					object->transform.posY = object->transform.oldY;
				}
				//縦隣りには進めるが横隣りには進めない場合
				else if (map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX - 1] != BLOCK && map[object->collisionPoint.rightTopY + 1][object->collisionPoint.rightTopX] == BLOCK)
				{
					object->transform.posX = object->transform.oldX;
				}
				//縦隣りにも横隣りにも進めない場合
				else if (map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX - 1] == BLOCK && map[object->collisionPoint.rightTopY + 1][object->collisionPoint.rightTopX] == BLOCK)
				{
					object->transform.posY = object->transform.oldY;
					object->transform.posX = object->transform.oldX;
				}
			}
			else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX] == BLOCK)
			{
				//縦隣りにも横隣りの両方に進める
				if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] != BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] != BLOCK)
				{

				}
				//縦隣りには進めないが横隣りには進める場合
				else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] == BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] != BLOCK)
				{
					object->transform.posY = object->transform.oldY;
				}
				//縦隣りには進めるが横隣りには進めない場合
				else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] != BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] == BLOCK)
				{
					object->transform.posX = object->transform.oldX;
				}
				//縦隣りにも横隣りにも進めない場合
				else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] == BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] == BLOCK)
				{
					object->transform.posY = object->transform.oldY;
					object->transform.posX = object->transform.oldX;
				}
			}
			else
			{
				object->transform.posX += object->transform.speedX;
			}
		}
	}

	if (keys[KEY_INPUT_S] == 1)
	{
		if (object->transform.posY < MAP_SIZE_Y * BLOCK_SIZE) //画面内で動くように範囲を設定
		{
			object->collisionPoint.leftBottomX = (object->transform.posX - object->transform.radiusX) / BLOCK_SIZE;
			object->collisionPoint.rightBottomX = (object->transform.posX + object->transform.radiusX - 1) / BLOCK_SIZE;
			object->collisionPoint.leftTopY = ((object->transform.posY - object->transform.radiusY) + object->transform.speedY) / BLOCK_SIZE;
			object->collisionPoint.rightTopY = ((object->transform.posY - object->transform.radiusY) + object->transform.speedY) / BLOCK_SIZE;
			object->collisionPoint.leftBottomY = ((object->transform.posY + object->transform.radiusY - 1) + object->transform.speedY) / BLOCK_SIZE;
			object->collisionPoint.rightBottomY = ((object->transform.posY + object->transform.radiusY - 1) + object->transform.speedY) / BLOCK_SIZE;

			//ブロックに当たった際の押し戻しの処理
			if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX] == BLOCK)
			{
				//縦隣りにも横隣りの両方に進める
				if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] != BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] != BLOCK)
				{

				}
				//縦隣りには進めないが横隣りには進める場合
				else if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] == BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] != BLOCK)
				{
					object->transform.posY = object->transform.oldY;
				}
				//縦隣りには進めるが横隣りには進めない場合
				else if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] != BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] == BLOCK)
				{
					object->transform.posX = object->transform.oldX;
				}
				//縦隣りにも横隣りにも進めない場合
				else if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX + 1] == BLOCK && map[object->collisionPoint.leftBottomY - 1][object->collisionPoint.leftBottomX] == BLOCK)
				{
					object->transform.posY = object->transform.oldY;
					object->transform.posX = object->transform.oldX;
				}
			}
			else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX] == BLOCK)
			{
				//縦隣りにも横隣りの両方に進める
				if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] != BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] != BLOCK)
				{

				}
				//縦隣りには進めないが横隣りには進める場合
				else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] == BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] != BLOCK)
				{
					object->transform.posY = object->transform.oldY;
				}
				//縦隣りには進めるが横隣りには進めない場合
				else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] != BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] == BLOCK)
				{
					object->transform.posX = object->transform.oldX;
				}
				//縦隣りにも横隣りにも進めない場合
				else if (map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX - 1] == BLOCK && map[object->collisionPoint.rightBottomY - 1][object->collisionPoint.rightBottomX] == BLOCK)
				{
					object->transform.posY = object->transform.oldY;
					object->transform.posX = object->transform.oldX;
				}
			}
			else
			{
				object->transform.posY += object->transform.speedY;
			}
		}
	}	

	//スピードを規定値に戻す
	object->transform.speedX = defaultSpped;
	object->transform.speedY = defaultSpped;

	//どこかのマップが当たったら速度を半分にする。
	if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX] == BLOCK || map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX] == BLOCK || map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX] == BLOCK || map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX] == BLOCK)
	{
		object->transform.speedX /= 2;
		object->transform.speedY /= 2;
	}
	//何もない斜め移動の際に、スピードを半分にする。
	else if (keys[KEY_INPUT_W] == 1 && keys[KEY_INPUT_D] == 1)
	{
		object->transform.speedX /= 2;
		object->transform.speedY /= 2;
	}
	else if (keys[KEY_INPUT_W] == 1 && keys[KEY_INPUT_A] == 1)
	{
		object->transform.speedX /= 2;
		object->transform.speedY /= 2;
	}
	else if (keys[KEY_INPUT_S] == 1 && keys[KEY_INPUT_D] == 1)
	{
		object->transform.speedX /= 2;
		object->transform.speedY /= 2;
	}
	else if (keys[KEY_INPUT_S] == 1 && keys[KEY_INPUT_A] == 1)
	{
		object->transform.speedX /= 2;
		object->transform.speedY /= 2;
	}

	object->gravity();

	//プレイヤーのジャンプ
	if (jumpCount > 0) {
		if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX] != BLOCK || map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX] != BLOCK) {
			if (keys[KEY_INPUT_W] == 1 && prev[KEY_INPUT_W] == 0) {
				object->isFlying = 1;
				object->gravitySpeed = 0;
				jumpCount -= 1;
				jumpHeight = MAX_JUMP;

				////効果音
				//StopSoundMem(jumpSound);
				//if (CheckSoundMem(jumpSound) == 0) {
				//	PlaySoundMem(jumpSound, DX_PLAYTYPE_BACK, true);
				//}
			}
		}
	}
	//ジャンプの仕組み
	if (jumpCount < 1)
	{
		if (object->isFlying == 1)
		{
			jumpHeight--;
			if (jumpHeight < -10) {
				jumpHeight = -10;
			}

			object->transform.posY -= jumpHeight;
		}
	}

	//地面に着地したら再度ジャンプできるようにする
	if (jumpCount == 0) {
		if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX] == BLOCK || map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX] == BLOCK)
		{
			jumpCount = 1;
		}
	}

	object->fallProcess();

	////飛んでいるとき
	//if (jumpCount < 1) {
	//	//上向きでブロックにぶつかった時の処理
	//	if (object->transform.posY <= (object->BottomYHeightPlus - object->transform.radiusY))
	//	{
	//		if (map[object->collisionPoint.leftTopY][object->collisionPoint.leftTopX] == BLOCK || map[object->collisionPoint.rightTopY][object->collisionPoint.rightTopX] == BLOCK) {
	//			jumpHeight = 0;
	//		}
	//	}
	//}

	//下向きにブロックにぶつかった時の処理
	if (map[object->collisionPoint.leftBottomY][object->collisionPoint.leftBottomX] == BLOCK || map[object->collisionPoint.rightBottomY][object->collisionPoint.rightBottomX] == BLOCK)
	{
		jumpCount = 1;
		jumpHeight = 20;
	}

	//地面と接しているとき
	if (object->transform.posY >= (MAP_HEIGHT - 1) * BLOCK_SIZE - object->transform.radiusY) 
	{
		jumpCount = 1;
		jumpHeight = 20;
	}


}

void Player::PlayerDraw()
{
	//自機を中心とする3×3の正方形の描画
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			DrawBox((object->transform.posX - object->transform.radiusX) + (x * BLOCK_SIZE), (object->transform.posY - object->transform.radiusY) + (y * BLOCK_SIZE),
				(object->transform.posX + object->transform.radiusX) + (x * BLOCK_SIZE), (object->transform.posY + object->transform.radiusY) + (y * BLOCK_SIZE), GetColor(17, 167, 177), FALSE);
		}
	}

	DrawFormatString(200, 200, GetColor(255, 255, 255), "playerTransform.posX %f", playerTransform.posX);
	DrawFormatString(200, 300, GetColor(255, 255, 255), "object->transform.posX %f", object->transform.posX);
	DrawFormatString(200, 320, GetColor(255, 255, 255), "object->isFlying %d", object->isFlying);
	DrawFormatString(200, 340, GetColor(255, 255, 255), "jumpCount %d", jumpCount);

	//DrawFormatString(200, 300, GetColor(255, 255, 255), "object->isFlying %f", object->isFlying);

}
