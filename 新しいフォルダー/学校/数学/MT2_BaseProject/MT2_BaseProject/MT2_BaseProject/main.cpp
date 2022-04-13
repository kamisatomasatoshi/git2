#include "DxLib.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    // 変数宣言
    char   keys[256];
    int    mouse_x, mouse_y;
    VECTOR vec_line;        //　ライン始点からライン終点までのベクトル
    VECTOR vec_cursor;        //　ライン始点からカーソルまでのベクトル
    float  cross;            //　外積の値
    bool   push_flag = false;        // 左ボタンが押されてるフラグ
    int    start_x = 0, start_y = 0;//  ライン始点のXY座標
    int    end_x = 0, end_y = 0;    //  ライン終点のXY座標

    int cr = GetColor(255, 255, 0);

    // ウインドウモードに変更
    ChangeWindowMode(TRUE);

    // DX ライブラリの初期化処理
    if (DxLib_Init() == -1)return -1;

    while (ScreenFlip() == 0 && ProcessMessage() == 0)
    {
        ClearDrawScreen();

        GetHitKeyStateAll(keys);

        // カーソル座標取得
        GetMousePoint(&mouse_x, &mouse_y);

        int Mouse = GetMouseInput();

        // マウスの左ボタンが押されてる？
        if (Mouse & MOUSE_INPUT_LEFT) {
            //　押されてるフラグがfalse？
            //　（左ボタン押され初め？）
            if (push_flag == false) {
                // 押されてるフラグをtrue
                push_flag = true;

                // ラインの始点座標を取得
                GetMousePoint(&mouse_x, &mouse_y);
                start_x = mouse_x;
                start_y = mouse_y;

                //　1つ前に引いたラインの終点を一瞬なぞるのを消す
                //  のに必要な処理を入れてみよう
                //  （ラインを引く処理が出来てからの後回しで大丈夫です）
                end_x = start_x;
                end_y = start_y;
            }
            //　前フレームから左ボタンが
            //　押され続けている時はelseに来る
            else {
                //　左ボタンが押され続けているので
                //  カーソルの現在位置をラインの終点に取得
                GetMousePoint(&mouse_x, &mouse_y);
                end_x = mouse_x;
                end_y = mouse_y;

            }
        }
        //  左ボタン押されてない場合
        else {
            //  前フレームは左ボタン押されてた?
            if (push_flag == true) {
                // 押されてるフラグfalse
                push_flag = false;

                // ドラッグ終了時の処理
                //  カーソルの現在位置をラインの終点に取得
                GetMousePoint(&mouse_x, &mouse_y);
                end_x = mouse_x;
                end_y = mouse_y;

            }
        }

        if (start_x != end_x) {
            //　ライン描画
            DrawLine(start_x, start_y, end_x, end_y, cr, true);

            //　ラインの頭「●」描画
            DrawCircle(end_x, end_y, 8, cr, true);

        }

        //  ラインのベクトル作る
        //vec_line = VGet(中身を考えよう);
        vec_line = VGet(start_x - end_x, start_y - end_y, 0);

        //  vec_line の値を正規化して結果を vec_line に代入
        //vec_line = VNorm(中身を考えよう);
        vec_line = VNorm(vec_line);

        //  ラインの始点からカーソルまでのベクトル作る
        //vec_cursor = VGet(中身を考えよう);
        vec_cursor = VGet(mouse_x - start_x, mouse_y - start_y, 0);

        //  vec_cursor の値を正規化して結果を vec_cursor に代入
        //vec_cursor = VNorm(中身を考えよう);
        vec_line = VNorm(vec_cursor);

        //変数を使って外積を計算して変数crossに格納
        cross = (start_x - end_x) * (mouse_y - start_y) - (start_y - end_y) * (mouse_x - start_x);

        //変数crossの値で左右の判定
        //(カーソルがラインより右か左かを文字で表示)
        if (cross <= 0)
        {
            cr = GetColor(255, 255, 0);
            DrawString(10, 10, "右", cr);
        }
        else if (cross >= 0)
        {
            cr = GetColor(255, 0, 0);
            DrawString(10, 10, "左", cr);
        }

    }

    // DX ライブラリ処理
    DxLib_End();        // DX ライブラリ終了の処理

    return 0;            // ソフト終了の処理
}