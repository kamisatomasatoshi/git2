#include"Object.h"

//コンストラクタ
Object::Object(Transform transform, CollisionPoint collisionPoint)
{
	this->transform = transform;
	this->collisionPoint = collisionPoint;
	hasGravity = 1;
	isFlying = 0;
	gravitySpeed = 2.0f;

	BottomYInfo = 0;
	BottomYMaptip = 0;
	BottomYHeight = 0;
	BottomYHeightPlus = 0;
	BottomYMaptipPlus = 0;
	TopYInfo = 0;
	TopYMaptip = 0;
	TopYHeight = 0;
}

//デストラクタ
Object::~Object()
{
}

//現在位置の情報関数（重力処理で使う）
void Object::posInfo()
{
	////現在位置の底辺の情報
	//BottomYInfo = transform.posY + transform.radiusY - 1;
	////→現在位置の底辺のマップチップ情報(底辺の情報からマップチップ上でのどの整数にいるかを計算する)
	//BottomYMaptip = (transform.posY + transform.radiusY - 1) / BLOCK_SIZE;
	////→底辺がめり込んだ時に戻す用のマップのy座標
	//BottomYHeight = (BottomYMaptip)*BLOCK_SIZE;

	//現在地より１つ下のy座標。自機の底辺の座標は一つ下の左上のy座標になるため。(上の2行からマップ上の自機の整数が取れたので、固定する位置を指定してブロックサイズをかけてあげる)
	BottomYHeightPlus = (BottomYMaptip + 1) * BLOCK_SIZE;
	//現在地より１つ下のマップチップの情報
	BottomYMaptipPlus = (BottomYHeightPlus / BLOCK_SIZE);

	//現在位置の頂点の情報 
	TopYInfo = transform.posY - transform.radiusY;
	 
	 
	//現在位置の頂点のマップチップ情報
	TopYMaptip = (transform.oldY - transform.radiusY) / BLOCK_SIZE;
	//頂点も同様に固定するためのy座標を出すためのy座標を求める。
	TopYHeight = (TopYMaptip + 1) * BLOCK_SIZE;
}

//各角の現在地の座標計算
void Object::ObjectMoveCollision()
{
	//右上
	collisionPoint.rightTopX = (transform.posX + transform.radiusX - 1) / BLOCK_SIZE;
	collisionPoint.rightBottomX = (transform.posX + transform.radiusX - 1) / BLOCK_SIZE;
	//右下
	collisionPoint.rightTopY = (transform.posY - transform.radiusY) / BLOCK_SIZE;
	collisionPoint.rightBottomY = (transform.posY + transform.radiusY - 1) / BLOCK_SIZE;
	//左上
	collisionPoint.leftTopX = (transform.posX - transform.radiusX) / BLOCK_SIZE;
	collisionPoint.leftBottomX = (transform.posX - transform.radiusX) / BLOCK_SIZE;
	//左下
	collisionPoint.leftTopY = (transform.posY - transform.radiusY) / BLOCK_SIZE;
	collisionPoint.leftBottomY = (transform.posY + transform.radiusY - 1) / BLOCK_SIZE;

}

//重力
void Object::gravity()
{
	//下にブロックがなければ落下する処理
	if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX] != BLOCK && map[collisionPoint.rightBottomY][collisionPoint.rightBottomX] != BLOCK && hasGravity == 1) {
		if (transform.posY + transform.radiusY <= MAP_SIZE_Y * BLOCK_SIZE)
		{
			if (isFlying == 0) {
				gravitySpeed--;

				transform.posY -= gravitySpeed;

				if (gravitySpeed < -10) {
					gravitySpeed = -10;
				}
			}
		}
	}
}

void Object::fallProcess()
{
	posInfo();

	ObjectMoveCollision();

	//空中などの足場にいる時にY座標を固定
	if (map[collisionPoint.leftBottomY][collisionPoint.leftBottomX] == BLOCK || map[collisionPoint.rightBottomY][collisionPoint.rightBottomX] == BLOCK) {
		transform.posY = TopYHeight - transform.radiusY;

		gravitySpeed = 0;
		isFlying = 0;
		
	}

	//地面にめり込みないように対策
	if (transform.posY >= (MAP_HEIGHT - 1) * BLOCK_SIZE - transform.radiusY) {
		transform.posY = (MAP_HEIGHT - 1) * BLOCK_SIZE - transform.radiusY;

		isFlying = 0;
	};
}
