#include "DxLib.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "variable.h"
#include "mapchip.h"
#include "shield.h"
#include "boomerang.h"
#include "boss.h"
#include "hit.h"



#define pi 3.14159
#define G           9.81                // �d�͉����x

//enum shieldState {
//	nomal,		//0,�ʏ펞
//	scraped,	//1,��ꂽ��
//	recharge,	//2,���`���[�W��
//	crack,		//3,���ꂽ��
//};

enum boomerangState {
	hold,			//0,�v���C���[�������Ă��鎞
	fly2target,		//1,�^�[�Q�b�g�Ɍ������Ĕ��ł��鎞
	stop,			//2,�󒆒�~���Ă��鎞
	return2player,	//3,�v���C���[�̂��ƂɋA���Ă��Ă��鎞
};


// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LC1B_23_�z�\�C�^�C�Z�C:�^�J�~�����U�Z";


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
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
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���

	backgroundBack = LoadGraph("resource/runnerbgFore.png");
	backgroundFore = LoadGraph("resource/runnerbgBack.png");
	backgroundSky = LoadGraph("resource/runnerbgSky.png");
	jumpPng = LoadGraph("resource/jumpMotion_64x96.png");
	jumpPngNB = LoadGraph("resource/jumpMotionNoneB.png");
	airJumpPng = LoadGraph("resource/airJump.png");
	airJumpPngNB = LoadGraph("resource/airJumpNoneB.png");
	charaIdlePng = LoadGraph("resource/charaIdle.png");
	charaIdleNBPng = LoadGraph("resource/charaIdleNoneB.png");
	stagePng = LoadGraph("resource/stage1.png");

	moveKeys = LoadGraph("resource/keys.png");
	moveKeysA = LoadGraph("resource/A_keys.png");
	moveKeysD = LoadGraph("resource/D_keys.png");
	spece = LoadGraph("resource/space.png");
	speceUse = LoadGraph("resource/space_use.png");

	mousenone = LoadGraph("resource/mouse.png");
	mouseRight = LoadGraph("resource/mouse_right.png");
	mouseLeft = LoadGraph("resource/mouse_left.png");
	notUse = LoadGraph("resource/not.png");
	boomerangIcon = LoadGraph("resource/boomerang.png");
	shieldIcon = LoadGraph("resource/shield.png");

	handPng = LoadGraph("resource/enemyHand.png");
	boomerangPng = LoadGraph("resource/boomerang2.png");

	int bossGraph = LoadGraph("resource/boss.png");

	int parryAtkAnmPng[9] = {};
	LoadDivGraph(
		"resource/parryAtkAnm.png",
		9, 9, 1, 100, 64,
		parryAtkAnmPng
	);

	LoadDivGraph(
		"resource/runAnmNoneB.png",
		4, 4, 1, 64, 64,
		runAnmNB
	);

	LoadDivGraph(
		"resource/runAnm.png",
		4, 4, 1, 64, 64,
		runAnm
	);

	LoadDivGraph(
		"resource/gameclearAnmS.png",
		7, 7, 1, 768, 512,
		gameClearAnm
	);

	//�w�i



	LoadDivGraph(
		"resource/maptipTile.png",
		20, 4, 5, 64, 64,
		mapchip
	);

	LoadDivGraph(
		"resource/roboRunAll.png",
		6, 6, 1, 32, 32,
		charaAnm
	);

	LoadDivGraph(
		"resource/roboRun.png",
		3, 3, 1, 32, 32,
		roboRunAnm
	);

	LoadDivGraph(
		"resource/roboIdle.png",
		2, 2, 1, 32, 32,
		roboIdleAnm
	);
	srand(time(nullptr));	//�����̐錾





	enum mapInfo {
		NONE,	//0
		ground1	//1

	};

	//�}�b�v
	const int MAP_COUNT_X = sizeof(map[0]) / sizeof(map[0][0]);
	const int MAP_COUNT_Y = sizeof(map) / sizeof(map[0]);

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; ++i) {
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);
		GetMousePoint(&mouse_x, &mouse_y);
		int Mouse = GetMouseInput();


		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		//�O�̃t���[���̏��
		posOldX = (int)player.transform.x;
		posOldY = (int)player.transform.y;

		// �X�V����--------------------------------------------------------------------------//

		if (playerShield.parrynow <= 0) {
			//�u�[�������̃_���[�W��ݒ�
			boomerang.damage = 5 * downCount;

#pragma region//�{�X�̍X�V����

			MOVE_ROULETTE(bossAttackCoolTime, bossLeftHand, bossRightHand, bossAttackPattern, bossAttackCount);

			//�G�̘r�̓���
			ATK_MOVE(bossRightHand, player, bossAttackCoolTime, bossTimer, isShake);
			ATK_MOVE(bossLeftHand, player, bossAttackCoolTime, bossTimer, isShake);

			//�{�X�̒e
			BOSS_BULLET(player, bossFace, enemyBullet);

			ugoku += ugokuSpeed;
			if (10 <= ugoku) {
				ugokuSpeed *= -1;
			}
			else if (ugoku <= -10) {
				ugokuSpeed *= -1;
			}

			bossFace.posY = bossFace.initPosY + ugoku;

#pragma endregion//�{�X�̍X�V����

#pragma region//�v���C���[�̍X�V����
#pragma region//�ړ�����
			if (keys[KEY_INPUT_D] == 1) {
				orientation = 1;
				isRun = 1;
				isIdle = 0;
				if (player.transform.x + playerRadius >= WIN_WIDTH) {
					isRightWallSlip = 1;
					isLeftWallSlip = 0;
				}
				else {
					isRightWallSlip = 0;
					isLeftWallSlip = 0;
				}
				if (player.speedX <= 10) {
					player.speedX += 1;
				}
				else if (player.speedX > 10) {
					player.speedX -= 1;
				}

			}
			else if (keys[KEY_INPUT_A] == 1) {
				orientation = 0;
				isRun = 1;
				isIdle = 0;
				if (player.transform.x - playerRadius <= 0) {
					player.transform.x = playerRadius;
					isLeftWallSlip = 1;
					isRightWallSlip = 0;
				}
				else {
					isLeftWallSlip = 0;
					isRightWallSlip = 0;
				}
				if (player.speedX >= -10) {
					player.speedX -= 1;
				}

			}
			else {
				isRun = 0;
				isIdle = 1;
				if (player.speedX != 0) {
					if (player.speedX > 0) {
						player.speedX -= 1;
					}
					else if (player.speedX < 0) {
						player.speedX += 1;
					}
				}
			}

			if (player.speedX > 10) {	//�I�[�o�[�X�s�[�h������
				player.speedX -= 1;
			}
			else if (player.speedX < -10) {
				player.speedX += 1;
			}

			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && isAirjump == 0 ||
				keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && isRightWallSlip == 1 ||
				keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && isLeftWallSlip == 1) {
				isJump = 1;

				if (map[leftBottomY][leftBottomX] == 0 && map[oldleftBottomY][oldleftBottomX] == 0 &&
					map[rightBottomY][rightBottomX] == 0 && map[oldrightBottomY][oldrightBottomX] == 0) {
					isAirjump = 1;
				}
				else {
					isAirjump = 0;
				}

				if (isRightWallSlip == 1) {
					player.transform.x -= 1;
					player.speedX -= 20;
				}
				else if (isLeftWallSlip == 1) {
					player.transform.x += 1;
					player.speedX += 20;
				}
				else {

				}
			}

			if (isJump == 1) {
				jumpCount += 1;
				if (jumpCount > 0) {
					player.transform.y -= (jumpHeight - 3 * jumpCount);
				}
			}

			if (jumpCount == 10) {
				jumpCount = 0;
				isJump = 0;
			}

			if (map[oldleftBottomY][leftBottomX] == 0 && map[leftBottomY][oldleftBottomX] == 0 &&
				map[oldrightBottomY][rightBottomX] == 0 && map[rightBottomY][oldrightBottomX] == 0) {
				isAir = 1;
			}
			else {
				isAir = 0;
			}


			if (map[rightBottomY][rightBottomX] == 0 && map[oldrightBottomY][oldrightBottomX] == 0 &&
				map[leftBottomY][leftBottomX] == 0 && map[oldleftBottomY][oldleftBottomX] == 0 && isJump == 0) {

				if (player.speedY <= 15) {
					player.speedY += 0.8;

				}
			}
			else {

				player.speedY = 2;

			}

			player.transform.y += (int)player.speedY;	//���t���[���̈ړ�����
			player.transform.x += (int)player.speedX;

#pragma endregion//�ړ�����
#pragma region//�}�b�v�`�b�v
			leftTopX = ((int)player.transform.x - (int)player.transform.r) / BLOCK_SIZE;	//4�_�����߂�
			leftTopY = ((int)player.transform.y - (int)player.transform.r) / BLOCK_SIZE;
			leftBottomX = ((int)player.transform.x - (int)player.transform.r) / BLOCK_SIZE;
			leftBottomY = ((int)player.transform.y + (int)player.transform.r - 1) / BLOCK_SIZE;
			rightTopX = ((int)player.transform.x + (int)player.transform.r - 1) / BLOCK_SIZE;
			rightTopY = ((int)player.transform.y - (int)player.transform.r) / BLOCK_SIZE;
			rightBottomX = ((int)player.transform.x + (int)player.transform.r - 1) / BLOCK_SIZE;
			rightBottomY = ((int)player.transform.y + (int)player.transform.r - 1) / BLOCK_SIZE;
			//---------------�n��ړ�----------------//
			oldleftTopX = ((int)posOldX - (int)player.transform.r) / BLOCK_SIZE;
			oldleftTopY = ((int)posOldY - (int)player.transform.r) / BLOCK_SIZE;
			oldleftBottomX = ((int)posOldX - (int)player.transform.r) / BLOCK_SIZE;
			oldleftBottomY = ((int)posOldY + (int)player.transform.r - 1) / BLOCK_SIZE;
			oldrightTopX = ((int)posOldX + (int)player.transform.r - 1) / BLOCK_SIZE;
			oldrightTopY = ((int)posOldY - (int)player.transform.r) / BLOCK_SIZE;
			oldrightBottomX = ((int)posOldX + (int)player.transform.r - 1) / BLOCK_SIZE;
			oldrightBottomY = ((int)posOldY + (int)player.transform.r - 1) / BLOCK_SIZE;


			//�}�b�v�`�b�v�����蔻��
			if (map[leftTopY][leftTopX] >= 1 && map[leftTopY][leftTopX] <= 14) {
				if (map[leftTopY][leftTopX] >= 9 && map[leftTopY][leftTopX] <= 13 && isInvincible == 0) {
					playerLife -= 1;
					isInvincible = 1;
				}
				if (map[oldleftTopY][leftTopX] == 0 && map[leftTopY][oldleftTopX] == 0) {

				}
				else if (map[oldleftTopY][leftTopX] == 0 && map[leftTopY][oldleftTopX] >= 1) {
					player.transform.y = (int)posOldY;

				}
				else if (map[oldleftTopY][leftTopX] >= 1 && map[leftTopY][oldleftTopX] == 0) {
					player.transform.x = (int)posOldX;
					player.speedX = 0;
				}
				else if (map[oldleftTopY][leftTopX] >= 1 && map[leftTopY][oldleftTopX] >= 1) {
					player.transform.y = (int)posOldY;
					player.transform.x = (int)posOldX;

				}
			}

			if (map[leftBottomY][leftBottomX] == 0 && map[leftBottomY][leftBottomX] >= 15//��
				) {
				if (oldleftBottomY < leftBottomY) {
					player.transform.y = ((int)player.transform.y / BLOCK_SIZE + 1) * BLOCK_SIZE - (int)player.transform.r - 1;
				}
			}
			if (map[rightBottomY][rightBottomX] == 0 && map[rightBottomY][rightBottomX] >= 15//��
				) {
				if (oldrightBottomY < rightBottomY) {
					player.transform.y = ((int)player.transform.y / BLOCK_SIZE + 1) * BLOCK_SIZE - (int)player.transform.r - 1;
				}
			}


			if (map[leftBottomY][leftBottomX] >= 1 && map[leftBottomY][leftBottomX] <= 14) {
				if (map[leftBottomY][leftBottomX] >= 9 && map[leftBottomY][leftBottomX] <= 13 && isInvincible == 0) {
					playerLife -= 1;
					isInvincible = 1;
				}
				if (map[oldleftBottomY][leftBottomX] == 0 && map[leftBottomY][oldleftBottomX] == 0) {

				}
				else if (map[oldleftBottomY][leftBottomX] == 0 && map[leftBottomY][oldleftBottomX] >= 1) {
					player.transform.y = ((int)player.transform.y / BLOCK_SIZE + 1) * BLOCK_SIZE - (int)player.transform.r - 1;
					isAirjump = 0;
					isAir = 0;
				}
				else if (map[oldleftBottomY][leftBottomX] >= 1 && map[leftBottomY][oldleftBottomX] == 0) {
					player.transform.x = (int)posOldX;
					player.speedX = 0;
				}
				else if (map[oldleftBottomY][leftBottomX] >= 1 && map[leftBottomY][oldleftBottomX] >= 1) {
					player.transform.y = (int)posOldY;
					player.transform.x = (int)posOldX;
				}
			}


			if (map[rightBottomY][rightBottomX] >= 1 && map[rightBottomY][rightBottomX] <= 14) {
				if (map[rightBottomY][rightBottomX] >= 9 && map[rightBottomY][rightBottomX] <= 13 && isInvincible == 0) {
					playerLife -= 1;
					isInvincible = 1;
				}
				if (map[oldrightBottomY][rightBottomX] == 0 && map[rightBottomY][oldrightBottomX] == 0) {

				}
				else if (map[oldrightBottomY][rightBottomX] == 0 && map[rightBottomY][oldrightBottomX] >= 1) {
					player.transform.y = ((int)player.transform.y / BLOCK_SIZE + 1) * BLOCK_SIZE - (int)player.transform.r - 1;
					isAirjump = 0;
					isAir = 0;
				}
				else if (map[oldrightBottomY][rightBottomX] >= 1 && map[rightBottomY][oldrightBottomX] == 0) {
					player.transform.x = (int)posOldX;
					player.speedX = 0;
				}
				else if (map[oldrightBottomY][rightBottomX] >= 1 && map[rightBottomY][oldrightBottomX] >= 1) {
					player.transform.y = (int)posOldY;
					player.transform.x = (int)posOldX;
				}
			}


			if (map[rightTopY][rightTopX] >= 1 && map[rightTopY][rightTopX] <= 14) {
				if (map[rightTopY][rightTopX] >= 9 && map[rightTopY][rightTopX] <= 13 && isInvincible == 0) {
					playerLife -= 1;
					isInvincible = 1;
				}
				if (map[oldrightTopY][rightTopX] == 0 && map[rightTopY][oldrightTopX] == 0) {

				}
				else if (map[oldrightTopY][rightTopX] == 0 && map[rightTopY][oldrightTopX] >= 1) {
					player.transform.y = (int)posOldY;
				}
				else if (map[oldrightTopY][rightTopX] >= 1 && map[rightTopY][oldrightTopX] == 0) {
					player.transform.x = (int)posOldX;
					player.speedX = 0;
				}
				else if (map[oldrightTopY][rightTopX] >= 1 && map[rightTopY][oldrightTopX] >= 1) {
					player.transform.y = (int)posOldY;
					player.transform.x = (int)posOldX;
				}
			}
#pragma endregion//�}�b�v�`�b�v

			GetMousePoint(&mouseStructure.x, &mouseStructure.y);

			PlayerShield(	//�V�[���h�֐�
				player,
				playerShield,
				mouseStructure,
				boomerang
			);

			PlayerBoomerang(player, boomerang, mouseStructure, target, isAirjump);	//�u�[�������֐�

			if (player.transform.x + player.transform.r >= WIN_WIDTH) {	//���̉�ʊO�ɐi�܂Ȃ�����
				player.transform.x = WIN_WIDTH - player.transform.r;
			}
			if (player.transform.x - player.transform.r <= 0) {
				player.transform.x = player.transform.r;
			}
#pragma endregion//�v���C���[�̍X�V����

			//�����蔻��
			HitDecision(player, boomerang, playerShield, bossLeftHand, bossRightHand, bossFace, enemyBullet, downCount);
		}

		//�p���B�̎�
		if (playerShield.isParry == 1) {		//�p���B��Ԃ̃t���O��true�̎�
			playerShield.parrynow--;			//�p���B�������̃^�C�}�[���f�N�������g
			playerShield.isShieldOn = false;
			isShake = 1;

			if (playerShield.parrynow <= 0) {	//�p���B�������̃^�C�}�[��0�ȉ��ɂȂ�����
				playerShield.isParry = 0;		//�p���B��Ԃ̃t���O��false�ɂ���
				playerShield.parrynow = 0;		//�p���B�������̃^�C�}�[��0�ɂ���
				player.transform.x += cos(playerShield.crros[0].angle) * 200;	//�J�[�\�������Ƀ��[�v
				player.transform.y += sin(playerShield.crros[0].angle) * 200;
			}
		}

#pragma region//�R�����g�A�E�g�ŕۗ�����Ă���
		//���G����
		/*if (isInvincible == 1) {
			invinsibleTimer++;
			if (invinsibleTimer >= 70) {
				invinsibleTimer = 0;
				isInvincible = 0;
			}
		}

		//�Q�[���[�o�[����
		if (playerLife <= 0 && gameOverAnmTimer < 21) {
			gameOverAnmTimer++;
			if (gameOverAnmTimer == 20) {
				gameOverAnmTimer = 0;
				scene = 2;
			}
		}*/



		//	break;

		//case 2:
		//	if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0) {
		//		playerLife = 5;	//�q�b�g�|�C���g
		//		player.transform.x = 470;	//X���W�̈ʒu
		//		player.transform.y = 3072;	//Y���W�̈ʒu
		//		posOldX = 0;
		//		posOldY = 0;
		//		player.speedX = 0;	//X���W�̃X�s�[�h
		//		player.speedY = 0;	//Y���W�̃X�s�[�h
		//		leftTopX = 0;
		//		leftTopY = 0;
		//		leftBottomX = 0;
		//		leftBottomY = 0;
		//		rightTopX = 0;
		//		rightTopY = 0;
		//		rightBottomX = 0;
		//		rightBottomY = 0;
		//		player.transform.r = 16;
		//		oldleftTopX = 0;
		//		oldleftTopY = 0;
		//		oldleftBottomX = 0;
		//		oldleftBottomY = 0;
		//		oldrightTopX = 0;
		//		oldrightTopY = 0;
		//		oldrightBottomX = 0;
		//		oldrightBottomY = 0;
		//		rightScrStartX = 470;	//�X�N���[���J�n�̈ʒu
		//		leftScrStartX = 350;
		//		upScrStartY = 150;	//�X�N���[���J�n�̈ʒu
		//		downScrStartY = 460;
		//		scrollX = 0;	//�X�N���[���l
		//		scrollY = 2800;
		//		Screenplayer.transform.x = 0;	//��ʏ�ł̎��@�̈ʒu
		//		jumpCount = 0;
		//		jumpHeight = 39;
		//		isJump = 0;
		//		isAirjump = 0;
		//		isIdle = 0;
		//		isRun = 0;
		//		isLeftRun = 0;
		//		isAir = 0;
		//		isRightWallSlip = 0;
		//		isLeftWallSlip = 0;
		//		isInvincible = 0;
		//		cAnimCount = 0;
		//		orientation = 0;
		//		scene = 0;
		//	}
		//	break;


		//case 3:
		//	if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0) {
		//		playerLife = 5;	//�q�b�g�|�C���g
		//		player.transform.x = 470;	//X���W�̈ʒu
		//		player.transform.y = 3072;	//Y���W�̈ʒu
		//		posOldX = 0;
		//		posOldY = 0;
		//		player.speedX = 0;	//X���W�̃X�s�[�h
		//		player.speedY = 0;	//Y���W�̃X�s�[�h
		//		leftTopX = 0;
		//		leftTopY = 0;
		//		leftBottomX = 0;
		//		leftBottomY = 0;
		//		rightTopX = 0;
		//		rightTopY = 0;
		//		rightBottomX = 0;
		//		rightBottomY = 0;
		//		player.transform.r = 16;
		//		oldleftTopX = 0;
		//		oldleftTopY = 0;
		//		oldleftBottomX = 0;
		//		oldleftBottomY = 0;
		//		oldrightTopX = 0;
		//		oldrightTopY = 0;
		//		oldrightBottomX = 0;
		//		oldrightBottomY = 0;
		//		rightScrStartX = 470;	//�X�N���[���J�n�̈ʒu
		//		leftScrStartX = 350;
		//		upScrStartY = 150;	//�X�N���[���J�n�̈ʒu
		//		downScrStartY = 460;
		//		scrollX = 0;	//�X�N���[���l
		//		scrollY = 2800;
		//		Screenplayer.transform.x = 0;	//��ʏ�ł̎��@�̈ʒu
		//		jumpCount = 0;
		//		jumpHeight = 39;
		//		isJump = 0;
		//		isAirjump = 0;
		//		isIdle = 0;
		//		isRun = 0;
		//		isLeftRun = 0;
		//		isAir = 0;
		//		isRightWallSlip = 0;
		//		isLeftWallSlip = 0;
		//		isInvincible = 0;
		//		cAnimCount = 0;
		//		orientation = 0;
		//		scene = 0;
		//	}

		//	break;
		//}
#pragma endregion//�R�����g�A�E�g�ŕۗ�����Ă���

		// �`�揈��-----------------------------------------//

		if (isShake == 1) {
			randomX = GetRand(shakeTimer);	//�V�F�C�N�̏���
			randomY = GetRand(shakeTimer);
			shakeTimer -= 2;
			if (shakeTimer <= 0) {
				randomX = 0;
				randomY = 0;
				shakeTimer = 10;
				isShake = 0;
			}
		}

		/*switch (scene) {
		case 0:
			DrawGraph(0, 0, startScreen[startSceneTimer / 5 % 2], true);
			break;

		case 1:*/
		//�w�i
		/*DrawGraph(-(scrollX / 15), 0, backgroundSky, true);
		DrawGraph(-(scrollX / 15 - 768), 0, backgroundSky, true);
		DrawGraph(-(scrollX / 10), 0, backgroundFore, true);
		DrawGraph(-(scrollX / 10 - 768), 0, backgroundFore, true);
		DrawGraph(-scrollX / 5, 0, backgroundBack, true);
		DrawGraph(-(scrollX / 5 - 768), 0, backgroundBack, true);*/


		DrawGraph(0 + randomX, 556 + randomY, stagePng, true);

#pragma region//�G�̕`��
		if (bossFace.hitPoint > 0) {	//��̕`��
			//DrawBox(bossFace.posX - bossFace.radius,
			//	bossFace.posY - bossFace.radius,
			//	bossFace.posX + bossFace.radius,
			//	bossFace.posY + bossFace.radius,
			//	GetColor(100, 255, 100), false);

			DrawGraph(bossFace.posX - bossFace.radius, bossFace.posY - bossFace.radius, bossGraph, true);

			DrawBox(0,
				0,
				WIN_WIDTH,
				30,
				GetColor(100, 100, 100), true);
			DrawBox(5,
				5,
				WIN_WIDTH - 5,
				25,
				GetColor(255, 50, 50), true);

			DrawBox(5,
				5,
				((float)WIN_WIDTH - 5) / 2000 * bossFace.hitPoint,
				25,
				GetColor(50, 255, 50), true);
		}

		if (bossLeftHand.hitPoint > 0) {	//����̕`��
			/*DrawBox(bossLeftHand.posX - bossLeftHand.radius,
				bossLeftHand.posY - bossLeftHand.radius,
				bossLeftHand.posX + bossLeftHand.radius,
				bossLeftHand.posY + bossLeftHand.radius,
				GetColor(100, 100, 255), false);*/
			DrawRotaGraph(bossLeftHand.posX + randomX, bossLeftHand.posY + randomY, 1.0, 0, handPng, true, 1.0);

			DrawBox(bossLeftHand.posX + randomX - 50,
				bossLeftHand.posY + randomY - bossLeftHand.radius - 20,
				bossLeftHand.posX + randomX + 50,
				bossLeftHand.posY + randomY - bossLeftHand.radius - 15,
				GetColor(255, 50, 50), true);

			DrawBox(bossLeftHand.posX + randomX - 50,
				bossLeftHand.posY + randomY - bossLeftHand.radius - 20,
				bossLeftHand.posX + randomX - 50 + bossLeftHand.hitPoint,
				bossLeftHand.posY + randomY - bossLeftHand.radius - 15,
				GetColor(50, 255, 50), true);
		}

		if (bossRightHand.hitPoint > 0) {	//�E��̕`��
			/*DrawBox(bossRightHand.posX - bossRightHand.radius,
				bossRightHand.posY - bossRightHand.radius,
				bossRightHand.posX + bossRightHand.radius,
				bossRightHand.posY + bossRightHand.radius,
				GetColor(255, 100, 100), false);*/
			DrawRotaGraph(bossRightHand.posX + randomX, bossRightHand.posY + randomY, 1.0, 0, handPng, true, 0);
			DrawBox(bossRightHand.posX + randomX - 50,
				bossRightHand.posY + randomY - bossRightHand.radius - 20,
				bossRightHand.posX + randomX + 50,
				bossRightHand.posY + randomY - bossRightHand.radius - 15,
				GetColor(255, 50, 50), true);
			DrawBox(bossRightHand.posX + randomX - 50,
				bossRightHand.posY + randomY - bossRightHand.radius - 20,
				bossRightHand.posX + randomX - 50 + bossRightHand.hitPoint,
				bossRightHand.posY + randomY - bossRightHand.radius - 15,
				GetColor(50, 255, 50), true);
		}

		for (int i = 0; i < MAP_COUNT_X; i++) {
			for (int j = 0; j < MAP_COUNT_Y; j++) {
				for (int k = 1; k < 17; k++) {
					if (map[j][i] == k) {
						DrawGraph(i * blockSize, j * blockSize, mapchip[k], true);
					}
				}

			}
		}

		if (enemyBullet.isShot == 1) {
			DrawCircle(
				enemyBullet.object.transform.x,
				enemyBullet.object.transform.y,
				enemyBullet.object.transform.r,
				GetColor(255, 100, 100), true
			);
		}

		if (bossRightHand.attackType == 5 &&
			bossLeftHand.attackType == 6) {
			if (bossLeftHand.atk.moveFaze == 2) {
				if (0 < bossTimer && bossTimer <= 30) {
					DrawLine(
						bossLeftHand.posX + randomX - bossLeftHand.radius, 0,
						bossLeftHand.posX + randomX - bossLeftHand.radius, 768 - 192,
						GetColor(255, 50, 50), true);
					DrawLine(
						bossRightHand.posX + randomX + bossRightHand.radius, 0,
						bossRightHand.posX + randomX + bossRightHand.radius, 768 - 192,
						GetColor(255, 50, 50), true);

					DrawBox(
						bossLeftHand.posX + randomX + bossLeftHand.radius, 200,
						bossRightHand.posX + randomX - bossRightHand.radius, 350,
						GetColor(255, 50, 50), true);

					DrawBox(
						bossLeftHand.posX + randomX + bossLeftHand.radius, 400,
						bossRightHand.posX + randomX - bossRightHand.radius, 450,
						GetColor(255, 50, 50), true);
				}
			}
		}
#pragma endregion//�G�̕`��

#pragma region//�V�[���h
		if (boomerang.isThrown == false) {
			//if (playerShield.isShieldOn == 0) {
			//	DrawLine(player.transform.x + randomX, player.transform.y + randomY, playerShield.point1.x + randomX, playerShield.point1.y + randomY, GetColor(255, 255, 255));
			//	DrawLine(playerShield.point1.x + randomX, playerShield.point1.y + randomY, playerShield.point2.x + randomX, playerShield.point2.y + randomY, GetColor(255, 255, 255));
			//	DrawLine(playerShield.point2.x + randomX, playerShield.point2.y + randomY, player.transform.x + randomX, player.transform.y + randomY, GetColor(255, 255, 255));
			//}
			if (playerShield.isShieldOn == 1) {
				DrawLine(player.transform.x + randomX, player.transform.y + randomY, playerShield.point1.x + randomX, playerShield.point1.y + randomY, GetColor(255, 255, 255));
				DrawLine(playerShield.point2.x + randomX, playerShield.point2.y + randomY, player.transform.x + randomX, player.transform.y + randomY, GetColor(255, 255, 255));
				DrawLine(playerShield.point1.x + randomX, playerShield.point1.y + randomY, playerShield.point2.x + randomX, playerShield.point2.y + randomY, GetColor(255, 255, 255));
				for (int i = 0; i < 16; i++) {
					if (playerShield.crros[i].first < 0) {
						DrawLine(player.transform.x + randomX, player.transform.y + randomY, playerShield.point1.x + randomX, playerShield.point1.y + randomY, GetColor(255, 255, 255));
					}
					if (playerShield.crros[i].seccond < 0) {
						DrawLine(playerShield.point1.x + randomX, playerShield.point1.y + randomY, playerShield.point2.x + randomX, playerShield.point2.y + randomY, GetColor(255, 255, 255));
					}
					if (playerShield.crros[i].third < 0) {
						DrawLine(playerShield.point2.x + randomX, playerShield.point2.y + randomY, player.transform.x + randomX, player.transform.y + randomY, GetColor(255, 255, 255));
					}
				}
			}
		}
#pragma endregion//�V�[���h

#pragma region//�u�[������
		/*if (boomerang.isThrown == true) {
			DrawTriangle(
				boomerang.object.transform.x + boomerang.object.transform.r * cos(pi / 3 * 2),
				boomerang.object.transform.y + boomerang.object.transform.r * sin(pi / 3 * 2),
				boomerang.object.transform.x + boomerang.object.transform.r * cos(pi / 3 * 4),
				boomerang.object.transform.y + boomerang.object.transform.r * sin(pi / 3 * 4),
				boomerang.object.transform.x + boomerang.object.transform.r * cos(pi / 3 * 6),
				boomerang.object.transform.y + boomerang.object.transform.r * sin(pi / 3 * 6),
				GetColor(255, 255, 0), true
			);
		}*/

		if (boomerang.isThrown == true) {
			boomerangAngle += 0.5;

			DrawRotaGraph(boomerang.object.transform.x + randomX, boomerang.object.transform.y + randomY, 0.8, boomerangAngle, boomerangPng, true, 0);
		}
		else {
			boomerangAngle = 0.0;
		}

#pragma endregion//�u�[������

#pragma region//�^�[�Q�b�g
		if (boomerang.isThrown == false) {
			DrawCircle(target.x + randomX, target.y + randomY, 5, GetColor(255, 255, 255), false);
			DrawCircle(target.x + randomX, target.y + randomY, 10, GetColor(255, 255, 255), false);
			DrawLine(target.x + randomX, target.y + randomY, target.x + randomX + 20, target.y + randomY, GetColor(255, 255, 255), true);
			DrawLine(target.x + randomX, target.y + randomY, target.x + randomX - 20, target.y + randomY, GetColor(255, 255, 255), true);
			DrawLine(target.x + randomX, target.y + randomY, target.x + randomX, target.y + 20 + randomY, GetColor(255, 255, 255), true);
			DrawLine(target.x + randomX, target.y + randomY, target.x + randomX, target.y - 20 + randomY, GetColor(255, 255, 255), true);
		}
		else if (boomerang.isThrown == true) {
			DrawCircle(target.x + randomX, target.y, 5, GetColor(255, 255, 0), false);
			DrawCircle(target.x + randomX, target.y, 10, GetColor(255, 255, 0), false);
			DrawLine(target.x + randomX, target.y, target.x + randomX + 20, target.y + randomY, GetColor(255, 255, 0), true);
			DrawLine(target.x + randomX, target.y, target.x + randomX - 20, target.y + randomY, GetColor(255, 255, 0), true);
			DrawLine(target.x + randomX, target.y, target.x + randomX, target.y + 20 + randomY, GetColor(255, 255, 0), true);
			DrawLine(target.x + randomX, target.y, target.x + randomX, target.y - 20 + randomY, GetColor(255, 255, 0), true);
		}
#pragma endregion//�^�[�Q�b�g

#pragma region//�v���C���[
		//�@���C���`��
		/*DrawBox(player.transform.x - player.transform.r,
			player.transform.y - player.transform.r,
			player.transform.x + player.transform.r,
			player.transform.y + player.transform.r,
			GetColor(255, 255, 255), true);*/
		if (isAir == 0) {
			if (isIdle == 1) {	//�A�C�h����
				cAnimCount = 0;


				if (boomerang.state == hold) {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY - 12/*���S��y�𑵂��邽��*/, 1.0, 0, charaIdlePng, TRUE, orientation);
				}
				else {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY - 12, 1.0, 0, charaIdleNBPng, TRUE, orientation);
				}

			}
			else if (isRun == 1) {	//�����Ă���Ƃ�
				cAnimCount++;
				if (cAnimCount >= 16) {
					cAnimCount = 0;
				}
				if (boomerang.state == hold) {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY - 12, 1.0, 0, runAnm[cAnimCount / 4], TRUE, orientation);
				}
				else {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY - 12, 1.0, 0, runAnmNB[cAnimCount / 4], TRUE, orientation);
				}
			}
		}
		else {
			if (isAirjump == 0) {	//��
				if (boomerang.state == hold) {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY, 1.0, 0, jumpPng, TRUE, orientation);
				}
				else {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY, 1.0, 0, jumpPngNB, TRUE, orientation);
				}
			}
			else if (isAirjump == 1) {	//2�i�W�����v��

				if (orientation == 1) {	//����
					airJumpCharaAngle += 0.7;
				}
				else {
					airJumpCharaAngle -= 0.7;
				}

				if (boomerang.state == hold) {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY + 12, 1.0, airJumpCharaAngle, airJumpPng, TRUE, orientation);

				}
				else {
					DrawRotaGraph(player.transform.x + randomX, player.transform.y + randomY, 1.0, airJumpCharaAngle, airJumpPngNB, TRUE, orientation);

				}
			}
			else {
				airJumpCharaAngle = 0.0;
			}

		}
#pragma endregion//�v���C���[

#pragma region//UI
		//�ړ��L�[�̕`��
		DrawGraph(200, 660, moveKeys, TRUE);

		if (keys[KEY_INPUT_A])
		{
			DrawGraph(200, 660, moveKeysA, TRUE);
		}

		if (keys[KEY_INPUT_D])
		{
			DrawGraph(200, 660, moveKeysD, TRUE);
		}
		DrawGraph(300, 660, spece, TRUE);
		if (keys[KEY_INPUT_SPACE])
		{
			DrawGraph(300, 660, speceUse, TRUE);
		}

		//�}�E�X�̕`��
		DrawGraph(1080, 650, mousenone, TRUE);
		if (mouseStructure.isLeftPush == true)
		{
			//�u�[�������U��
			DrawGraph(1080, 650, mouseLeft, TRUE);
		}
		if (mouseStructure.isRightPush == true)
		{
			//�K�[�h
			DrawGraph(1080, 650, mouseRight, TRUE);
		}

		//�u�[�������\��
		DrawGraph(1000, 650, boomerangIcon, TRUE);

		//�V�[���h�̕\��
		DrawGraph(1140, 650, shieldIcon, TRUE);

		if (boomerang.isThrown == true)//�����A�u�[�������𓊂��Ă��܂��Ă�����B
		{
			DrawGraph(1000, 650, notUse, TRUE);
			DrawGraph(1140, 650, notUse, TRUE);
		}

		if (isAirjump == true) {
			DrawGraph(1000, 650, notUse, TRUE);
		}

		if (playerShield.state == crack) {
			DrawGraph(1140, 650, notUse, TRUE);
		}

		if (playerShield.parrynow > 0) {
			parryAtkAnmTimer++;
			if (parryAtkAnmTimer >= 27) {
				parryAtkAnmTimer = 0;
			}
			DrawRotaGraph(player.transform.x + cos(playerShield.crros[0].angle) * 100,
				player.transform.y + sin(playerShield.crros[0].angle) * 100,
				1.5, playerShield.crros[0].angle, parryAtkAnmPng[parryAtkAnmTimer / 3], TRUE, 1.0);

		}
		else {
			parryAtkAnmTimer = 0;
		}

#pragma endregion//UI

#pragma region//�m�F�p
		DrawFormatString(0, 30 + 0, GetColor(255, 255, 255), "HP = %d", player.hp);
		DrawFormatString(0, 30 + 15 * 1, GetColor(255, 255, 255), "playerShield.isShieldOn:%d", playerShield.isShieldOn);
		DrawFormatString(0, 30 + 15 * 2, GetColor(255, 255, 255), "shieldtate:%d", playerShield.state);
		DrawFormatString(0, 30 + 15 * 3, GetColor(255, 255, 255), "shield:%f", playerShield.level);
		DrawFormatString(0, 30 + 15 * 4, GetColor(255, 255, 255), "playerShield.rechargeTimer:%d", playerShield.rechargeTimer);
		DrawFormatString(0, 30 + 15 * 5, GetColor(255, 255, 255), "isParry:%d", playerShield.isParry);
		DrawFormatString(0, 30 + 15 * 6, GetColor(255, 255, 255), "parryTimer:%d", playerShield.parryTimer);
		DrawFormatString(0, 30 + 15 * 7, GetColor(255, 255, 255), "parrynow:%d", playerShield.parrynow);
		DrawFormatString(0, 30 + 15 * 8, GetColor(255, 255, 255), "boomerangState:%d", boomerang.state);
		DrawFormatString(0, 30 + 15 * 9, GetColor(255, 255, 255), "bossAttackCount:%d", bossAttackCount);
		DrawFormatString(0, 30 + 15 * 10, GetColor(255, 255, 255), "bossHandLHP:%d", bossLeftHand.hitPoint);
		DrawFormatString(0, 30 + 15 * 11, GetColor(255, 255, 255), "bossHandRHP:%d", bossRightHand.hitPoint);

#pragma endregion

		//	break;

		//case 2:
		//	//--------------�Q�[���I�[�o�[���--------------//
		//	if (gameOverAnmTimer != 6) {
		//		gameOverAnmTimer++;
		//	}

		//	DrawGraph(0, 0, gameOverAnm[gameOverAnmTimer], true);
		//	DrawFormatString(320, 390, GetColor(255, 255, 255), "ENTER TO RESET");
		//	break;
		//case 3:
		//	if (gameOverAnmTimer != 6) {
		//		gameOverAnmTimer++;
		//	}

		//	DrawGraph(0, 0, gameClearAnm[gameOverAnmTimer], true);
		//	DrawFormatString(320, 390, GetColor(255, 255, 255), "ENTER TO RESET");
		//	break;


		//}


		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��50FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}

	InitGraph();

	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}