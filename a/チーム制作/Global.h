#pragma once

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LC1B_20_�j�b�^�V���W: �`�[�������O�� ";

// �E�B���h�E����
const int WIN_WIDTH = 960;

// �E�B���h�E�c��
const int WIN_HEIGHT = 960;

// �ŐV�̃L�[�{�[�h���p
extern char keys[256];

// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
extern char oldkeys[256];

//�L�[�{�[�h���X�V�֐�
void KeyUpdate();

//�T�C�Y�̕ϐ�
const int BLOCK_SIZE = 32;
///const int MAP_SIZE = 32;
const int PLAYER_SIZE = 32;

// �u���b�N�S�̂̍���
const int MAP_HEIGHT = 30;
// �u���b�N�S�̂̉���
const int MAP_WIDTH = 30;

////map�S�̂̃T�C�Y
//const int MAP_SIZE_Y = MAP_HEIGHT * BLOCK_SIZE;
//const int MAP_SIZE_X = MAP_WIDTH * BLOCK_SIZE;

//map�S�̂̃T�C�Y
const int MAP_SIZE_Y = 30;
const int MAP_SIZE_X = 30;



