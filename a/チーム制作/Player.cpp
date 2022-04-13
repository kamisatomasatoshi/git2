#include"DxLib.h"
#include"Player.h"

//コンストラクタ
//座標の初期化
Player::Player(Transform transform, CollisionPoint collisionPoint)
{
	this->transform = transform;
	this->collisionPoint = collisionPoint;
}

//デストラクタ
Player::~Player()
{
}

void Player::PlayerMove()
{

	transform.oldX = transform.posX;
	transform.oldY = transform.posY;

	//右上
	collisionPoint.rightTopX = (transform.posX + transform.radiusX - 1) / BLOCK_SIZE;
	collisionPoint.rightTopY = (transform.posY + transform.radiusY) / BLOCK_SIZE;
	//右下
	collisionPoint.rightTopX = (transform.posX + transform.radiusX - 1) / BLOCK_SIZE;
	collisionPoint.rightTopY = (transform.posY + transform.radiusY - 1) / BLOCK_SIZE;
	//左上
	collisionPoint.rightTopX = (transform.posX + transform.radiusX) / BLOCK_SIZE;
	collisionPoint.rightTopY = (transform.posY + transform.radiusY) / BLOCK_SIZE;
	//左下
	collisionPoint.rightTopX = (transform.posX + transform.radiusX) / BLOCK_SIZE;
	collisionPoint.rightTopY = (transform.posY + transform.radiusY - 1) / BLOCK_SIZE;

	/*if (keys[KEY_INPUT_D] == 1)
	{
		collisionPoint.rightTopX = ((transform.posX + transform.radiusX - 1) + transform.speedX) / BLOCK_SIZE;
		collisionPoint.rightBottomX = ((transform.posX + transform.radiusX - 1) + transform.radiusX - 1) / BLOCK_SIZE;
		if (map[collisionPoint.rightTopY][collisionPoint.rightTopX] == 0 && map[collisionPoint.rightBottomY][collisionPoint.rightBottomX] == 0)
		{
			transform.posX += transform.speedX;
		}
	}*/
	/*if (keys[KEY_INPUT_A] == 1)
	{
		collisionPoint.leftTopX = (transform.posX - transform.radiusX - transform.speedX) / BLOCK_SIZE;
		collisionPoint.leftBottomX = (transform.posX - transform.radiusX - transform.speedX) / BLOCK_SIZE;
		if (map[collisionPoint.leftTopY][collisionPoint.leftTopX] == 0 && map[collisionPoint.leftBottomY][collisionPoint.leftBottomX] == 0)
		{
			transform.posX -= transform.speedX;
		}
	}*/

	/*if (keys[KEY_INPUT_W] == 1)
	{
		transform.posY -= transform.speedY;
	}*/
	/*if (keys[KEY_INPUT_S] == 1)
	{
		transform.posY += transform.speedY;
	}*/

	if (keys[KEY_INPUT_A] == 1)
	{
		if (transform.posX > BLOCK_SIZE) //画面内で動くように範囲を設定
		{
			collisionPoint.rightTopX = ((transform.posX - transform.speedX) + transform.radiusX - 1) / BLOCK_SIZE;
			collisionPoint.rightBottomX = ((transform.posX - transform.speedX) + transform.radiusX - 1) / BLOCK_SIZE;
			collisionPoint.leftTopX = ((transform.posX - transform.speedX) - transform.radiusX) / BLOCK_SIZE;
			collisionPoint.leftBottomX = ((transform.posX - transform.speedX) - transform.radiusX) / BLOCK_SIZE;
			collisionPoint.leftTopY = (transform.posY - transform.radiusX) / BLOCK_SIZE;
			collisionPoint.leftBottomY = (transform.posY + transform.radiusX - 1) / BLOCK_SIZE;

			if (map[collisionPoint.leftTopY][collisionPoint.leftTopX] == BLOCK)
			{
				transform.speedX /= 2;

				//縦隣りにも横隣りの両方に進める
				if (map[collisionPoint.leftTopY][collisionPoint.leftTopX + 1] != BLOCK && map[collisionPoint.leftTopY + 1][collisionPoint.leftTopX] != BLOCK)
				{

				}
				//縦隣りには進めないが横隣りには進める場合
				else if (map[collisionPoint.leftTopY][collisionPoint.leftTopX + 1] == BLOCK && map[collisionPoint.leftTopY + 1][collisionPoint.leftTopX] != BLOCK)
				{
					transform.posY = transform.oldY;
					/*scrollY = transform.oldY;*/
				}
				//縦隣りには進めるが横隣りには進めない場合
				else if (map[collisionPoint.leftTopY][collisionPoint.leftTopX + 1] != BLOCK && map[collisionPoint.leftTopY + 1][collisionPoint.leftTopX] == BLOCK)
				{
					transform.posX = transform.oldX;
				}
				//縦隣りにも横隣りにも進めない場合
				else if (map[collisionPoint.leftTopY][collisionPoint.leftTopX + 1] == BLOCK && map[collisionPoint.leftTopY + 1][collisionPoint.leftTopX] == BLOCK)
				{
					transform.posY = transform.oldY;
					transform.posX = transform.oldX;
				}
			}
			else if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX] == BLOCK)
			{
				transform.speedX /= 2;

				//縦隣りにも横隣りの両方に進める
				if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] != BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] != BLOCK)
				{

				}
				//縦隣りには進めないが横隣りには進める場合
				else if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] == BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] != BLOCK)
				{
					transform.posY = transform.oldY;
				}
				//縦隣りには進めるが横隣りには進めない場合
				else if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] != BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] == BLOCK)
				{
					transform.posX = transform.oldX;
				}
				//縦隣りにも横隣りにも進めない場合
				else if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] == BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] == BLOCK)
				{
					transform.posY = transform.oldY;
					transform.posX = transform.oldX;
				}
			}
			else
			{
				transform.posX -= transform.speedX;
			}
		}
	}

	if (keys[KEY_INPUT_D] == 1)
	{
		if (transform.posX < MAP_SIZE_X * BLOCK_SIZE) //画面内で動くように範囲を設定
		{
			collisionPoint.rightTopX = ((transform.posX + transform.speedX) + transform.radiusX - 1) / BLOCK_SIZE;
			collisionPoint.rightBottomX = ((transform.posX + transform.speedX) + transform.radiusX - 1) / BLOCK_SIZE;
			collisionPoint.leftTopX = ((transform.posX + transform.speedX) - transform.radiusX) / BLOCK_SIZE;
			collisionPoint.leftBottomX = ((transform.posX + transform.speedX) - transform.radiusX) / BLOCK_SIZE;
			collisionPoint.rightTopY = (transform.posY - transform.radiusY) / BLOCK_SIZE;
			collisionPoint.rightBottomY = (transform.posY + transform.radiusY - 1) / BLOCK_SIZE;

			//ブロックに当たった際の押し戻しの処理
			if (map[collisionPoint.rightTopY][collisionPoint.rightTopX] == BLOCK)
			{
				//縦隣りにも横隣りの両方に進める
				if (map[collisionPoint.rightTopY][collisionPoint.rightTopX - 1] != BLOCK && map[collisionPoint.rightTopY + 1][collisionPoint.rightTopX] != BLOCK)
				{

				}
				//縦隣りには進めないが横隣りには進める場合
				else if (map[collisionPoint.rightTopY][collisionPoint.rightTopX - 1] == BLOCK && map[collisionPoint.rightTopY + 1][collisionPoint.rightTopX] != BLOCK)
				{
					transform.posY = transform.oldY;
				}
				//縦隣りには進めるが横隣りには進めない場合
				else if (map[collisionPoint.rightTopY][collisionPoint.rightTopX - 1] != BLOCK && map[collisionPoint.rightTopY + 1][collisionPoint.rightTopX] == BLOCK)
				{
					transform.posX = transform.oldX;
				}
				//縦隣りにも横隣りにも進めない場合
				else if (map[collisionPoint.rightTopY][collisionPoint.rightTopX - 1] == BLOCK && map[collisionPoint.rightTopY + 1][collisionPoint.rightTopX] == BLOCK)
				{
					transform.posY = transform.oldY;
					transform.posX = transform.oldX;
				}
			}
			else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX] == BLOCK)
			{
				//縦隣りにも横隣りの両方に進める
				if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] != BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] != BLOCK)
				{

				}
				//縦隣りには進めないが横隣りには進める場合
				else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] == BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] != BLOCK)
				{
					transform.posY = transform.oldY;
				}
				//縦隣りには進めるが横隣りには進めない場合
				else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] != BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] == BLOCK)
				{
					transform.posX = transform.oldX;
				}
				//縦隣りにも横隣りにも進めない場合
				else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] == BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] == BLOCK)
				{
					transform.posY = transform.oldY;
					transform.posX = transform.oldX;
				}
			}
			else
			{
				transform.posX += transform.speedX;
			}
		}
	}

	if (keys[KEY_INPUT_S] == 1)
	{
		if (transform.posY < MAP_SIZE_Y * BLOCK_SIZE) //画面内で動くように範囲を設定
		{
			collisionPoint.leftBottomX = (transform.posX - transform.radiusX) / BLOCK_SIZE;
			collisionPoint.rightBottomX = (transform.posX + transform.radiusX - 1) / BLOCK_SIZE;
			collisionPoint.leftTopY = ((transform.posY - transform.radiusY) + transform.speedY) / BLOCK_SIZE;
			collisionPoint.rightTopY = ((transform.posY - transform.radiusY) + transform.speedY) / BLOCK_SIZE;
			collisionPoint.leftBottomY = ((transform.posY + transform.radiusY - 1) + transform.speedY) / BLOCK_SIZE;
			collisionPoint.rightBottomY = ((transform.posY + transform.radiusY - 1) + transform.speedY) / BLOCK_SIZE;

			//ブロックに当たった際の押し戻しの処理
			if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX] == BLOCK)
			{
				//縦隣りにも横隣りの両方に進める
				if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] != BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] != BLOCK)
				{

				}
				//縦隣りには進めないが横隣りには進める場合
				else if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] == BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] != BLOCK)
				{
					transform.posY = transform.oldY;
				}
				//縦隣りには進めるが横隣りには進めない場合
				else if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] != BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] == BLOCK)
				{
					transform.posX = transform.oldX;
				}
				//縦隣りにも横隣りにも進めない場合
				else if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX + 1] == BLOCK && map[collisionPoint.leftBottomY - 1][collisionPoint.leftBottomX] == BLOCK)
				{
					transform.posY = transform.oldY;
					transform.posX = transform.oldX;
				}
			}
			else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX] == BLOCK)
			{
				//縦隣りにも横隣りの両方に進める
				if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] != BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] != BLOCK)
				{

				}
				//縦隣りには進めないが横隣りには進める場合
				else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] == BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] != BLOCK)
				{
					transform.posY = transform.oldY;
				}
				//縦隣りには進めるが横隣りには進めない場合
				else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] != BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] == BLOCK)
				{
					transform.posX = transform.oldX;
				}
				//縦隣りにも横隣りにも進めない場合
				else if (map[collisionPoint.rightBottomY][collisionPoint.rightBottomX - 1] == BLOCK && map[collisionPoint.rightBottomY - 1][collisionPoint.rightBottomX] == BLOCK)
				{
					transform.posY = transform.oldY;
					transform.posX = transform.oldX;
				}
			}
			else
			{
				transform.posY += transform.speedY;
			}
		}
	}

}

void Player::PlayerDraw()
{
	//自機を中心とする3×3の正方形の描画
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			DrawBox((transform.posX - transform.radiusX) + (x * BLOCK_SIZE), (transform.posY - transform.radiusY) + (y * BLOCK_SIZE),
				(transform.posX + transform.radiusX) + (x * BLOCK_SIZE), (transform.posY + transform.radiusY) + (y * BLOCK_SIZE), GetColor(17, 167, 177), FALSE);
		}
	}
}
