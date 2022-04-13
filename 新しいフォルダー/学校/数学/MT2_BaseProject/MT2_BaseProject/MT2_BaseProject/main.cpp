#include "DxLib.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    // �ϐ��錾
    char   keys[256];
    int    mouse_x, mouse_y;
    VECTOR vec_line;        //�@���C���n�_���烉�C���I�_�܂ł̃x�N�g��
    VECTOR vec_cursor;        //�@���C���n�_����J�[�\���܂ł̃x�N�g��
    float  cross;            //�@�O�ς̒l
    bool   push_flag = false;        // ���{�^����������Ă�t���O
    int    start_x = 0, start_y = 0;//  ���C���n�_��XY���W
    int    end_x = 0, end_y = 0;    //  ���C���I�_��XY���W

    int cr = GetColor(255, 255, 0);

    // �E�C���h�E���[�h�ɕύX
    ChangeWindowMode(TRUE);

    // DX ���C�u�����̏���������
    if (DxLib_Init() == -1)return -1;

    while (ScreenFlip() == 0 && ProcessMessage() == 0)
    {
        ClearDrawScreen();

        GetHitKeyStateAll(keys);

        // �J�[�\�����W�擾
        GetMousePoint(&mouse_x, &mouse_y);

        int Mouse = GetMouseInput();

        // �}�E�X�̍��{�^����������Ă�H
        if (Mouse & MOUSE_INPUT_LEFT) {
            //�@������Ă�t���O��false�H
            //�@�i���{�^�������ꏉ�߁H�j
            if (push_flag == false) {
                // ������Ă�t���O��true
                push_flag = true;

                // ���C���̎n�_���W���擾
                GetMousePoint(&mouse_x, &mouse_y);
                start_x = mouse_x;
                start_y = mouse_y;

                //�@1�O�Ɉ��������C���̏I�_����u�Ȃ���̂�����
                //  �̂ɕK�v�ȏ��������Ă݂悤
                //  �i���C���������������o���Ă���̌�񂵂ő��v�ł��j
                end_x = start_x;
                end_y = start_y;
            }
            //�@�O�t���[�����獶�{�^����
            //�@�����ꑱ���Ă��鎞��else�ɗ���
            else {
                //�@���{�^���������ꑱ���Ă���̂�
                //  �J�[�\���̌��݈ʒu�����C���̏I�_�Ɏ擾
                GetMousePoint(&mouse_x, &mouse_y);
                end_x = mouse_x;
                end_y = mouse_y;

            }
        }
        //  ���{�^��������ĂȂ��ꍇ
        else {
            //  �O�t���[���͍��{�^��������Ă�?
            if (push_flag == true) {
                // ������Ă�t���Ofalse
                push_flag = false;

                // �h���b�O�I�����̏���
                //  �J�[�\���̌��݈ʒu�����C���̏I�_�Ɏ擾
                GetMousePoint(&mouse_x, &mouse_y);
                end_x = mouse_x;
                end_y = mouse_y;

            }
        }

        if (start_x != end_x) {
            //�@���C���`��
            DrawLine(start_x, start_y, end_x, end_y, cr, true);

            //�@���C���̓��u���v�`��
            DrawCircle(end_x, end_y, 8, cr, true);

        }

        //  ���C���̃x�N�g�����
        //vec_line = VGet(���g���l���悤);
        vec_line = VGet(start_x - end_x, start_y - end_y, 0);

        //  vec_line �̒l�𐳋K�����Č��ʂ� vec_line �ɑ��
        //vec_line = VNorm(���g���l���悤);
        vec_line = VNorm(vec_line);

        //  ���C���̎n�_����J�[�\���܂ł̃x�N�g�����
        //vec_cursor = VGet(���g���l���悤);
        vec_cursor = VGet(mouse_x - start_x, mouse_y - start_y, 0);

        //  vec_cursor �̒l�𐳋K�����Č��ʂ� vec_cursor �ɑ��
        //vec_cursor = VNorm(���g���l���悤);
        vec_line = VNorm(vec_cursor);

        //�ϐ����g���ĊO�ς��v�Z���ĕϐ�cross�Ɋi�[
        cross = (start_x - end_x) * (mouse_y - start_y) - (start_y - end_y) * (mouse_x - start_x);

        //�ϐ�cross�̒l�ō��E�̔���
        //(�J�[�\�������C�����E�������𕶎��ŕ\��)
        if (cross <= 0)
        {
            cr = GetColor(255, 255, 0);
            DrawString(10, 10, "�E", cr);
        }
        else if (cross >= 0)
        {
            cr = GetColor(255, 0, 0);
            DrawString(10, 10, "��", cr);
        }

    }

    // DX ���C�u��������
    DxLib_End();        // DX ���C�u�����I���̏���

    return 0;            // �\�t�g�I���̏���
}