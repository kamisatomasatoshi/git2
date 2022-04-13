#include "DxLib.h"
#include "Object.h"
#include "Player.h"
#include "maptip.h"

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

	int blockHandle = 0;
	blockHandle = LoadGraph("resource/block.png");

	int playerHandle = 0;
	playerHandle = LoadGraph("resource/test_player.png");

	Transform playerTransform =
	{
		100.0f,
		100.0f,
		0.0f,
		0.0f,
		16.0f,
		16.0f,
		2.0f,
		2.0f
	};
	Transform objectTransform =
	{
		100.0f,
		100.0f,
		0.0f,
		0.0f,
		16.0f,
		16.0f,
		2.0f,
		2.0f
	};

	CollisionPoint collsionPoint =
	{
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	};

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	
	int scene = 0;

	//�C���X�^���X�̐���
	Object* object = new Object(objectTransform);
	Player* player = new Player(playerTransform, collsionPoint);

	// �Q�[�����[�v
	while (true)
	{
		//�L�[����
		KeyUpdate();

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		player->PlayerMove();

		//switch (scene)//����
		//{
		//case0://�X�^�[�g

		//	break;

		//case1://�Q�[��

		//	break;

		//case2://�N���A

		//	break;

		//case3://�I�[�o�[

		//	break;

		//	
		//}
		// �`�揈��
		switch (scene)
		{
		case0://�X�^�[�g
			DrawGraph(player->transform.posX - player->transform.radiusX, player->transform.posY - player->transform.radiusY, playerHandle, TRUE);
			break;

		case1://�Q�[��

			break;

		case2://�N���A

			break;

		case3://�I�[�o�[

			break;

			
		}

		

		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				if (map[y][x] == BLOCK)
				{
					DrawGraph(x * BLOCK_SIZE, y * BLOCK_SIZE, blockHandle, TRUE);
				}
			}
		}

		player->PlayerDraw();

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
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

	DeleteGraph(blockHandle);
	DeleteGraph(playerHandle);


	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
