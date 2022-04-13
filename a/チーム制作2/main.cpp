#include "DxLib.h"
#include "Object.h"
#include "Player.h"
#include "maptip.h"
#include "Struct.h"

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

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	
	int scene = 0;

	//�C���X�^���X�̐���
	//Object *object = new Object(objectTransform);
	Player* player = new Player();

	// �Q�[�����[�v
	while (true)
	{
		//�L�[����
		KeyUpdate();

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		//�X�V����
		if (scene == 0 || scene == 1 )
		{
		player->PlayerMove();

		}

		//�`�揈��
		
		switch (scene)
		{
		case 0://�X�^�[�g
			if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0)
			{
				scene = 1;
			}
			DrawGraph(player->object->transform.posX - player->object->transform.radiusX, player->object->transform.posY - player->object->transform.radiusY, playerHandle, TRUE);
			break;

		case 1://�Q�[��
			if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0)
			{
				scene = 2;
			}
			DrawFormatString(400, 600, GetColor(255, 255, 255), "scene:%d", scene);
			break;

		case 2://�|�[�Y
			if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0)
			{
				scene = 3;
			}
			DrawFormatString(0, 0, GetColor(255, 255, 255), "POUSE");
			break;

		case 3://�N���A
			if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0)
			{
				scene = 4;
			}
			DrawFormatString(0, 0, GetColor(255, 255, 255), "�Q�[���N���A�I");
			break;

		case 4://�I�[�o�[
			if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0)
			{
				scene = 0;
			}
			DrawFormatString(0, 0, GetColor(255, 255, 255), "�I�[�o�[�c");
			break;

		};
		if (scene == 0 || scene == 1 || scene == 2)
		{
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
		}

		DrawFormatString(400, 600, GetColor(255, 255, 255), "scene:%d", scene);
		//DrawFormatString(400, 620, GetColor(255, 255, 255), "speedY %f", player->transform.speedY);

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












