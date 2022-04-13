#include "DxLib.h"
#include "struct.h"
#define PI    3.1415926535897932384626433832795f

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "106_LossLeft ";
// ウィンドウ横幅
const int WIN_WIDTH = 1376;
// ウィンドウ縦幅
const int WIN_HEIGHT = 896;
// 最新のキーボード情報用
char keys[256] = { 0 };
// 1ループ(フレーム)前のキーボード情報
char oldkeys[256] = { 0 };

enum MapInfo
{
	NONE, //0
	BLOCK,//1
	RAZOR, //2
	RAZOR_S,// 3
	KEY,//4
	SWITCH_RAZOR,//5
	SWITCH_BLOCK,//6
};

// マップ
const int block_size = 32;// ブロックのサイズ
const int mapHeight = 28; // ブロック全体の高さ
const int mapWidth = 43;  // ブロック全体の横幅
//int block_handle[2] = { 0 }; // ブロック画像
//int blue_block_handle = 0;
//int player_handle;			 // プレイヤー画像
int razordevice_handle;		 // レイザーデバイス画像
//int razor_handle;			 // レイザー画像
//int goal_handle;			 // ゴール画像
//int switch_handle[5] = { 0 }; //スイッチ画像
//int key_handle; //スイッチ画像

int gameclear_text_handle;          // ゲームクリアテキスト
int gameover_text_handle;          // ゲームオーバーテキスト
int goal_handle[2] = { 0 };          // ゴール
int block_handle[4] = { 0 };      // ブロック
int player_ko_handle[2] = { 0 };  // プレイヤーKO
int player_stay_handle[4] = { 0 };// プレイヤー待機
int player_move_handle[6] = { 0 };// プレイヤー移動
int razor_a_handle[4] = { 0 };      // レーザー地面
int razor_b_handle[4] = { 0 };      // レーザー
int button_handle[5] = { 0 };      // スイッチ
int left_hp_handle[2] = { 0 };
int gametitle_text_handle[13] = { 0 }; //タイトル
int arrow_handle[2] = { 0 };// 矢印
//音楽の変数
int main_bgm_handle;
int jump_sound_handle;
int goal_sound_handle;
int goal_open_handle;
int button_sound_handle;
int electricshock_handle;
int key_pickup_handle;

int map[28][43] = {
		{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,5,0,0, 0,0,0,0,0, 0,0,3,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1},
		{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1}
};

//マップの列(縦)の数
const int map_count_x = sizeof(map[0]) / sizeof(map[0][0]);
//マップの行(横)の数
const int map_count_y = sizeof(map) / sizeof(map[0]);

void MAP_Init()
{
	//blue_block_handle = LoadGraph("blue_block_2.png");
	LoadDivGraph("Resource/player_ko.png", 2, 2, 1, 32, 32, player_ko_handle);     // プレイヤーKO画像
	LoadDivGraph("Resource/player_stay.png", 4, 4, 1, 32, 32, player_stay_handle);// プレイヤー待機画像
	LoadDivGraph("Resource/player_walk.png", 6, 6, 1, 32, 32, player_move_handle);// プレイヤー移動画像
	LoadDivGraph("Resource/Razor_v2.png", 4, 4, 1, 32, 32, razor_b_handle);         // レーザー根本画像
	LoadDivGraph("Resource/Razor-sheet.png", 4, 4, 1, 32, 32, razor_a_handle);     // レーザー画像
	LoadDivGraph("Resource/switch.png", 5, 5, 1, 32, 11, button_handle);             // ボタン画像
	LoadDivGraph("Resource/mapchip_mix .png", 4, 4, 1, 32, 32, block_handle);         // ブロック画像
	LoadDivGraph("Resource/goa_mix.png", 2, 2, 1, 64, 96, goal_handle);             // ゴール画像
	LoadDivGraph("Resource/heart.png", 2, 2, 1, 32, 32, left_hp_handle);             // HP画像
	LoadDivGraph("Resource/title.png", 13, 13, 1, 1376, 896, gametitle_text_handle);//タイトル画像
	LoadDivGraph("Resource/arrow_mix.png", 2, 2, 1, 16, 16, arrow_handle);
	
	gameclear_text_handle = LoadGraph("Resource/GAMECLEAR.png");// ゲームクリアテキスト画像
	gameover_text_handle = LoadGraph("Resource/GAMEOVER.png");// ゲームオーバーテキスト画像

	main_bgm_handle = LoadSoundMem("bgm/main_bgm.mp3");                                 // BGM
	//PlaySoundMem(main_bgm_handle, DX_PLAYTYPE_LOOP, FALSE);
	jump_sound_handle = LoadSoundMem("bgm/Jump15.wav");                                 // ジャンプ音
	goal_sound_handle = LoadSoundMem("bgm/gate.mp3");                                 // ゴール音
	goal_open_handle = LoadSoundMem("bgm/goal_open.wav");                             // ゴール開閉音
	button_sound_handle = LoadSoundMem("bgm/button_sound.wav");                         // スイッチ音
	electricshock_handle = LoadSoundMem("bgm/electric_shock.wav");                     // 感電音
	key_pickup_handle = LoadSoundMem("bgm/key_pickup.wav");                             // カギ入手音

}

//場面切り替え用の変数
int scene = 0;

// 自機のマップチップ上での座標を取得
// -----右側のプレイヤー-----
// 左上
int R_left_top_x;
int R_left_top_y;
// 左下
int R_left_bottom_x;
int R_left_bottom_y;
// 右上
int R_right_top_x;
int R_right_top_y;
// 右下
int R_right_bottom_x;
int R_right_bottom_y;
// 仮移動
int R_speed_tmp = 4;

//// -----左側のプレイヤー-----
// 左上
int L_left_top_x;
int L_left_top_y;
// 左下
int L_left_bottom_x;
int L_left_bottom_y;
// 右上
int L_right_top_x;
int L_right_top_y;
// 右下
int L_right_bottom_x;
int L_right_bottom_y;
// 仮移動
int L_speed_tmp = 4;

//ステイしているときのアニメタイマー
int R_stay_timer = 40;
int L_stay_timer = 40;
bool R_stay_flag = 0;
bool L_stay_flag = 0;


//歩いているときのアニメタイマー
int R_walk_timer = 60;
int L_walk_timer = 60;
bool R_walk_flag = 0;
bool L_walk_flag = 0;

//ジャンプ用の変数
bool jump_flag = 0;
bool jump_flag_twice = 0;
float jump_speed_timer = 12.0f;
int jump_count = 0; //ジャンプ数を数えて、回数を制限する用の変数
int jump_count_timer = 0;
bool jump_count_flag = 0;
float bottom_y = 0;

//重力
float gravity_speed = 4;
bool gravity_flag = 0;

//レーザー
//死亡フラグ
bool death_flag_R = 0;
bool death_flag_L = 0;
int death_count_timer_R = 100;
int death_count_timer_L = 100;
int R_ko_anime_timer = 40;
int L_ko_anime_timer = 40;


//スイッチ
int switch_flag[5] = { 0 };
bool switch_razor_flag = 0;

//鍵
bool Get_key = 0;
bool move_change_flag = 0;
int get_key_count = 0;

//ライフ
int left_hp[3] = { 1,1,1 };
int hp_count[3] = { 1,1,1 };

//タイトルタイマー

int title_ani_timer = 130;

//ゲームオーバータイマー
int game_over_time = 60;
//ゲームクリアタイマー
int game_clear_time = 60;

//for分用のj
int razor_number;
int razor_ani_timer = 80;

void Deviece_Draw()
{
	if (switch_razor_flag == 0)
	{
		DrawGraph(864, 32, block_handle[1], true);
	}
	if (switch_razor_flag == 1)
	{
		DrawGraph(864, 32, block_handle[2], true);
	}
}

void MAP_Draw()
{
	// ブロックの描画
	// 行の繰り返し
	for (int y = 0; y < mapHeight; y++)
	{
		// 列の繰り返し
		for (int x = 0; x < mapWidth; x++)
		{
			if (map[y][x] == BLOCK) // 1があるところにブロックを描画する
			{
				// 行と列それぞれの位置にブロックサイズを掛けて描画する。
				DrawGraph(x * block_size, y * block_size, block_handle[0], TRUE);
			}
			if (map[y][x] == RAZOR)
			{
				DrawGraph(x * block_size, y * block_size, razor_a_handle[razor_number], TRUE);
				razor_number = 0;
				razor_ani_timer--;
				if (razor_ani_timer <= 80 && razor_ani_timer >= 60)
				{
					razor_number = 0;
				}
				if (razor_ani_timer < 60 && razor_ani_timer >= 40)
				{
					razor_number = 1;
				}
				if (razor_ani_timer < 40 && razor_ani_timer >= 20)
				{
					razor_number = 2;
				}
				if (razor_ani_timer < 20 && razor_ani_timer >= 0)
				{
					razor_number = 3;
				}
				if (razor_ani_timer <= 0)
				{
					razor_ani_timer = 80;
				}

			}
			if (map[y][x] == RAZOR_S)
			{
				DrawGraph(x * block_size, y * block_size, razor_b_handle[razor_number], TRUE);
				razor_number = 0;
				razor_ani_timer--;
				if (razor_ani_timer <= 80 && razor_ani_timer >= 60)
				{
					razor_number = 0;
				}
				if (razor_ani_timer < 60 && razor_ani_timer >= 40)
				{
					razor_number = 1;
				}
				if (razor_ani_timer < 40 && razor_ani_timer >= 20)
				{
					razor_number = 2;
				}
				if (razor_ani_timer < 20 && razor_ani_timer >= 0)
				{
					razor_number = 3;
				}
				if (razor_ani_timer <= 0)
				{
					razor_ani_timer = 80;
				}
				
			}
			if (map[y][x] == SWITCH_RAZOR)
			{
				if (scene == 0)
				{
					if (switch_razor_flag == 0)
					{
						DrawGraph(18 * block_size, 26 * block_size + 22, button_handle[0], TRUE);
					}
					if (switch_razor_flag == 1)
					{
						DrawGraph(18 * block_size, 26 * block_size + 22, button_handle[4], TRUE);
					}
				}

				if (scene == 1)
				{
					if (switch_razor_flag == 0)
					{
						DrawGraph(24 * block_size, 26 * block_size + 22, button_handle[0], TRUE);
					}
					if (switch_flag[0] == 1 && map[26][24] == SWITCH_RAZOR)
					{
						DrawGraph(24 * block_size, 26 * block_size + 22, button_handle[4], TRUE);
					}
				}
				if (scene == 2)
				{
					if (switch_razor_flag == 0)
					{
						DrawGraph(24 * block_size, 12 * block_size + 22, button_handle[0], TRUE);
					}
					if (switch_razor_flag == 1 && map[12][24] == SWITCH_RAZOR)
					{
						DrawGraph(24 * block_size, 12 * block_size + 22, button_handle[4], TRUE);
					}
				}
				if (scene == 3)
				{
					if (switch_razor_flag == 0)
					{
						DrawGraph(29 * block_size, 26 * block_size + 22, button_handle[0], TRUE);
					}
					if ( map[26][29] == SWITCH_RAZOR && switch_razor_flag == 1)
					{
						DrawGraph(29 * block_size, 26 * block_size + 22, button_handle[4], TRUE);
					}
				}
				if (scene == 4)
				{
					if (switch_razor_flag == 0)
					{
						DrawGraph(17 * block_size, 14 * block_size + 22, button_handle[0], TRUE);
					}
					if (switch_razor_flag == 1)
					{
						DrawGraph(17 * block_size, 14 * block_size + 22, button_handle[4], TRUE);
					}
				}
				
			}
			if (map[y][x] == SWITCH_BLOCK )
			{
				if (scene == 1)
				{
					if (switch_flag[0] == 0)
					{
						DrawGraph(19 * block_size, 26 * block_size + 22, button_handle[3], TRUE);
					}
					if (switch_flag[1] == 0)
					{
						DrawGraph(20 * block_size, 26 * block_size + 22, button_handle[3], TRUE);
					}
					if (switch_flag[2] == 0)
					{
						DrawGraph(21 * block_size, 26 * block_size + 22, button_handle[3], TRUE);
					}
					if (switch_flag[3] == 0)
					{
						DrawGraph(22 * block_size, 26 * block_size + 22, button_handle[3], TRUE);
					}
					if (switch_flag[4] == 0)
					{
						DrawGraph(23 * block_size, 26 * block_size + 22, button_handle[3], TRUE);
					}
					if (switch_flag[0] == 1 && map[26][19] == SWITCH_BLOCK)
					{
						DrawGraph(19 * block_size, 26 * block_size + 22, button_handle[4], TRUE);
					}
					if (switch_flag[1] == 1 && map[26][20] == SWITCH_BLOCK)
					{
						DrawGraph(20 * block_size, 26 * block_size + 22, button_handle[4], TRUE);
					}
					if (switch_flag[2] == 1 && map[26][21] == SWITCH_BLOCK)
					{
						DrawGraph(21 * block_size, 26 * block_size + 22, button_handle[4], TRUE);
					}
					if (switch_flag[3] == 1 && map[26][22] == SWITCH_BLOCK)
					{
						DrawGraph(22 * block_size, 26 * block_size + 22, button_handle[4], TRUE);
					}
					if (switch_flag[4] == 1 && map[26][23] == SWITCH_BLOCK)
					{
						DrawGraph(23 * block_size, 26 * block_size + 22, button_handle[4], TRUE);
					}
				}
				if (scene == 2)
				{
					if (switch_flag[0] == 0)
					{
						DrawGraph(35 * block_size, 26 * block_size + 22, button_handle[3], TRUE);
					}
					else if (switch_flag[0] == 1)
					{
						DrawGraph(35 * block_size, 26 * block_size + 22, button_handle[4], TRUE);
					}
					
				}
				if (scene == 3)
				{
					if (switch_flag[0] == 0)
					{
						DrawGraph(19 * block_size, 26 * block_size + 22, button_handle[3], TRUE);
					}
					if (switch_flag[1] == 0)
					{
						DrawGraph(20 * block_size, 26 * block_size + 22, button_handle[3], TRUE);
					}
					if (switch_flag[2] == 0)
					{
						DrawGraph(21 * block_size, 26 * block_size + 22, button_handle[3], TRUE);
					}
					if (switch_flag[3] == 0)
					{
						DrawGraph(22 * block_size, 26 * block_size + 22, button_handle[3], TRUE);
					}
					if (switch_flag[4] == 0)
					{
						DrawGraph(23 * block_size, 26 * block_size + 22, button_handle[3], TRUE);
					}
					if (switch_flag[0] == 1 && map[26][19] == SWITCH_BLOCK)
					{
						DrawGraph(19 * block_size, 26 * block_size + 22, button_handle[4], TRUE);
					}
					if (switch_flag[1] == 1 && map[26][20] == SWITCH_BLOCK)
					{
						DrawGraph(20 * block_size, 26 * block_size + 22, button_handle[4], TRUE);
					}
					if (switch_flag[2] == 1 && map[26][21] == SWITCH_BLOCK)
					{
						DrawGraph(21 * block_size, 26 * block_size + 22, button_handle[4], TRUE);
					}
					if (switch_flag[3] == 1 && map[26][22] == SWITCH_BLOCK)
					{
						DrawGraph(22 * block_size, 26 * block_size + 22, button_handle[4], TRUE);
					}
					if (switch_flag[4] == 1 && map[26][23] == SWITCH_BLOCK)
					{
						DrawGraph(23 * block_size, 26 * block_size + 22, button_handle[4], TRUE);
					}
				}
				if (scene == 4)
				{
					if (switch_flag[0] == 0)
					{
						DrawGraph(11 * block_size, 22 * block_size + 22, button_handle[3], TRUE);
					}
					if (switch_flag[1] == 0)
					{
						DrawGraph(14 * block_size, 18 * block_size + 22, button_handle[3], TRUE);
					}
					if (switch_flag[0] == 1 && map[22][11] == SWITCH_BLOCK)
					{
						DrawGraph(11 * block_size, 22 * block_size + 22, button_handle[4], TRUE);
					}
					if (switch_flag[1] == 1 && map[18][14] == SWITCH_BLOCK)
					{
						DrawGraph(14 * block_size, 18 * block_size + 22, button_handle[4], TRUE);
					}
				}

			}

			if (map[y][x] == KEY)
			{
				DrawGraph(x * block_size, y * block_size, block_handle[3], TRUE);
			}
		}
	}
}

void PLAYER_Move_Fusion()
{
	// --------------- 上移動 --------------- //
	if (keys[KEY_INPUT_UP] == 1)
	{
	}
	// ---------- 下移動 ---------- //
	else if (keys[KEY_INPUT_DOWN] == 1)
	{
		//左下
		R_left_bottom_x = (right_player.pos_x - right_player.radius) / block_size;
		R_left_bottom_y = (right_player.pos_y + right_player.radius - 1 + R_speed_tmp) / block_size;
		//右下
		R_right_bottom_x = (right_player.pos_x + right_player.radius - 1) / block_size;
		R_right_bottom_y = (right_player.pos_y + right_player.radius - 1 + R_speed_tmp) / block_size;

		//左下同時押しの処理
		if (keys[KEY_INPUT_LEFT] == 1)
		{
			R_left_top_x = (right_player.pos_x - right_player.radius - R_speed_tmp) / block_size;
			R_left_top_y = (right_player.pos_y - right_player.radius + R_speed_tmp) / block_size;
			R_left_bottom_x = (right_player.pos_x - right_player.radius - R_speed_tmp) / block_size;
			R_right_bottom_x = (right_player.pos_x + right_player.radius - 1 - R_speed_tmp) / block_size;

			if (map[R_left_bottom_y][R_left_bottom_x] == NONE && map[R_right_bottom_y][R_right_bottom_x] == NONE && map[R_left_top_y][R_left_top_x] == NONE)
			{
				right_player.speed_x = -R_speed_tmp /2;
				right_player.speed_y = +R_speed_tmp /2;
			}
			else
			{
				if (right_player.pos_y + right_player.radius <= (R_left_bottom_y)*block_size)
				{
					if (map[R_left_bottom_y - 1][R_left_bottom_x] == NONE)
					{
						right_player.speed_x = -R_speed_tmp;
					}
				}

				if (right_player.pos_x - right_player.radius >= (R_left_bottom_x + 1) * block_size)
				{
					if (map[R_left_bottom_y][R_left_bottom_x + 1] == NONE)
					{
						right_player.speed_y = +R_speed_tmp;
					}
				}
			}
		}

		else //斜め移動以外の場合の移動処理、バグってたら先にこいつ疑ったほうが早いかも
		{
			if (map[R_left_bottom_y][R_left_bottom_x] == NONE && map[R_right_bottom_y][R_right_bottom_x] == NONE)
			{
				right_player.speed_y = +R_speed_tmp;
			}
		}

		//右上同時押しの処理
		if (keys[KEY_INPUT_RIGHT] == 1)
		{
			R_right_top_x = (right_player.pos_x + right_player.radius - 1 + R_speed_tmp) / block_size;
			R_right_top_y = (right_player.pos_y - right_player.radius + R_speed_tmp) / block_size;
			R_right_bottom_x = (right_player.pos_x + right_player.radius - 1 + R_speed_tmp) / block_size;
			R_left_bottom_x = (right_player.pos_x - right_player.radius + R_speed_tmp) / block_size;

			if (map[R_left_bottom_y][R_left_bottom_x] == NONE && map[R_right_bottom_y][R_right_bottom_x] == NONE && map[R_right_top_y][R_right_top_x] == NONE)
			{
				right_player.speed_x = +R_speed_tmp / 2;
				right_player.speed_y = +R_speed_tmp / 2;
			}
			else {
				if (right_player.pos_y + right_player.radius <= (R_right_bottom_y)*block_size)
				{
					if (map[R_right_bottom_y - 1][R_right_bottom_x] == NONE)
					{
						right_player.speed_x = +R_speed_tmp;
					}
				}
				if (right_player.pos_x + right_player.radius <= (R_right_bottom_x)*block_size)
				{
					if (map[R_right_bottom_y][R_right_bottom_x - 1] == NONE)
					{
						right_player.speed_y = +R_speed_tmp;
					}
				}
			}
		}
	}
	else if (keys[KEY_INPUT_LEFT] == 1)
	{
			//左上
			R_left_top_x = (right_player.pos_x - right_player.radius - R_speed_tmp) / block_size;
			R_left_top_y = (right_player.pos_y - right_player.radius) / block_size;
			//左下
			R_left_bottom_x = (right_player.pos_x - right_player.radius - R_speed_tmp) / block_size;
			R_left_bottom_y = (right_player.pos_y + right_player.radius - 1) / block_size;

			if (map[R_left_top_y][R_left_top_x] == NONE && map[R_left_bottom_y][R_left_bottom_x] == NONE)
			{
				right_player.speed_x = -R_speed_tmp;
			}
			if (map[R_left_top_y][R_left_top_x] == SWITCH_BLOCK || map[R_left_bottom_y][R_left_bottom_x] == SWITCH_BLOCK)
			{
				right_player.speed_x = -R_speed_tmp;
			}
			if (map[R_left_top_y][R_left_top_x] == SWITCH_RAZOR || map[R_left_bottom_y][R_left_bottom_x] == SWITCH_RAZOR)
			{
				right_player.speed_x = -R_speed_tmp;
			}

			L_walk_timer--;

			if (L_walk_timer <= 0)
			{
				L_walk_timer = 60;
			}
	}

	else if (keys[KEY_INPUT_RIGHT] == 1)
	{
		//右上
		R_right_top_x = (right_player.pos_x + right_player.radius - 1 + R_speed_tmp) / block_size;
		R_right_top_y = (right_player.pos_y - right_player.radius) / block_size;
		//右下
		R_right_bottom_x = (right_player.pos_x + right_player.radius - 1 + R_speed_tmp) / block_size;
		R_right_bottom_y = (right_player.pos_y + right_player.radius - 1) / block_size;

		if (map[R_right_top_y][R_right_top_x] == NONE && map[R_right_bottom_y][R_right_bottom_x] == NONE)
		{
			right_player.speed_x = +R_speed_tmp;
		}
		if (map[R_right_top_y][R_right_top_x] == SWITCH_BLOCK || map[R_right_bottom_y][R_right_bottom_x] == SWITCH_BLOCK)
		{
			right_player.speed_x = +R_speed_tmp;
		}
		if (map[R_right_top_y][R_right_top_x] == SWITCH_RAZOR || map[R_right_bottom_y][R_right_bottom_x] == SWITCH_RAZOR)
		{
			right_player.speed_x = +R_speed_tmp;
		}

		R_walk_timer--;

		if (R_walk_timer <= 0)
		{
			R_walk_timer = 60;
		}
	}
	
	if (keys[KEY_INPUT_RIGHT] == 0 && keys[KEY_INPUT_SPACE] == 0 && keys[KEY_INPUT_DOWN] == 0)
	{
		R_stay_timer--;
		if (R_stay_timer <= 0)
		{
			R_stay_timer = 40;
		}
	}
}

void PLAYER_Move_Right_Man()
{
	//上キーが入力されている時
	if (keys[KEY_INPUT_UP] == 1)
	{
	}
	//下キーが入力されている時
	else if (keys[KEY_INPUT_DOWN] == 1)
	{
		//左下
		R_left_bottom_x = (right_player.pos_x - right_player.radius) / block_size;
		R_left_bottom_y = (right_player.pos_y + right_player.radius - 1 + R_speed_tmp) / block_size;
		//右下
		R_right_bottom_x = (right_player.pos_x + right_player.radius - 1) / block_size;
		R_right_bottom_y = (right_player.pos_y + right_player.radius - 1 + R_speed_tmp) / block_size;

		//左下同時押しの処理
		if (keys[KEY_INPUT_LEFT] == 1)
		{
		}

		else //斜め移動以外の場合の移動処理、バグってたら先にこいつ疑ったほうが早いかも
		{
			if (map[R_left_bottom_y][R_left_bottom_x] == NONE && map[R_right_bottom_y][R_right_bottom_x] == NONE)
			{
				right_player.speed_y = +R_speed_tmp;
			}
		}

		//右下同時押しの処理
		if (keys[KEY_INPUT_RIGHT] == 1)
		{
			R_right_top_x = (right_player.pos_x + right_player.radius - 1 + R_speed_tmp) / block_size;
			R_right_top_y = (right_player.pos_y - right_player.radius + R_speed_tmp) / block_size;
			R_right_bottom_x = (right_player.pos_x + right_player.radius - 1 + R_speed_tmp) / block_size;
			R_left_bottom_x = (right_player.pos_x - right_player.radius + R_speed_tmp) / block_size;

			if (map[R_left_bottom_y][R_left_bottom_x] == NONE && map[R_right_bottom_y][R_right_bottom_x] == NONE && map[R_right_top_y][R_right_top_x] == NONE)
			{
				right_player.speed_x = +R_speed_tmp / 2;
				right_player.speed_y = +R_speed_tmp / 2;
			}
			else {
				if (right_player.pos_y + right_player.radius <= (R_right_bottom_y)*block_size)
				{
					if (map[R_right_bottom_y - 1][R_right_bottom_x] == NONE)
					{
						right_player.speed_x = +R_speed_tmp;
					}
				}
				if (right_player.pos_x + right_player.radius <= (R_right_bottom_x)*block_size)
				{
					if (map[R_right_bottom_y][R_right_bottom_x - 1] == NONE)
					{
						right_player.speed_y = +R_speed_tmp;
					}
				}
			}
		}
	}
	else if (keys[KEY_INPUT_RIGHT] == 1)
	{
		//右上
		R_right_top_x = (right_player.pos_x + right_player.radius - 1 + R_speed_tmp) / block_size;
		R_right_top_y = (right_player.pos_y - right_player.radius) / block_size;
		//右下
		R_right_bottom_x = (right_player.pos_x + right_player.radius - 1 + R_speed_tmp) / block_size;
		R_right_bottom_y = (right_player.pos_y + right_player.radius - 1) / block_size;

		if (map[R_right_top_y][R_right_top_x] == NONE && map[R_right_bottom_y][R_right_bottom_x] == NONE)
		{
			right_player.speed_x = +R_speed_tmp;
		}
		if (map[R_right_top_y][R_right_top_x] == SWITCH_BLOCK || map[R_right_bottom_y][R_right_bottom_x] == SWITCH_BLOCK)
		{
			right_player.speed_x = +R_speed_tmp;
		}
		if (map[R_right_top_y][R_right_top_x] == SWITCH_RAZOR || map[R_right_bottom_y][R_right_bottom_x] == SWITCH_RAZOR)
		{
			right_player.speed_x = +R_speed_tmp;
		}

		R_walk_timer--;

		if (R_walk_timer <= 0)
		{
			R_walk_timer = 60;
		}
		
	}

	else if(right_player.pos_y + right_player.radius >= 848)
	{
		gravity_speed = 0;
		right_player.pos_y = 848;
	}

	if(keys[KEY_INPUT_RIGHT] == 0 && keys[KEY_INPUT_SPACE] == 0 && keys[KEY_INPUT_DOWN] == 0 )
	{
		R_stay_timer--;
		if (R_stay_timer <= 0)
		{
			R_stay_timer = 40;
		}
	}
}

void PLAYER_Move_Left_Man()
{
	// ---------- 左移動 ---------- //
	if (keys[KEY_INPUT_LEFT] == 1)// ←キー入力
	{
		//左上の座標
		L_left_top_x = (left_player.pos_x - left_player.radius - L_speed_tmp) / block_size;
		L_left_top_y = (left_player.pos_y - left_player.radius) / block_size;
		//左下の座標
		L_left_bottom_x = (left_player.pos_x - left_player.radius - L_speed_tmp) / block_size;
		L_left_bottom_y = (left_player.pos_y + left_player.radius - 1) / block_size;

		if (map[L_left_top_y][L_left_top_x] == NONE && map[L_left_bottom_y][L_left_bottom_x] == NONE)
		{
			left_player.speed_x = -L_speed_tmp;
		}

		if (map[L_left_top_y][L_left_top_x] == SWITCH_BLOCK || map[L_left_bottom_y][L_left_bottom_x] == SWITCH_BLOCK)
		{
			left_player.speed_x = -L_speed_tmp;
		}
		if (map[L_left_top_y][L_left_top_x] == SWITCH_RAZOR || map[L_left_bottom_y][L_left_bottom_x] == SWITCH_RAZOR)
		{
			left_player.speed_x = -L_speed_tmp;
		}

		L_walk_timer--;

		if (L_walk_timer <= 0)
		{
			L_walk_timer = 60;
		}
	}
	else
	{
		L_stay_timer--;
		if (L_stay_timer <= 0)
		{
			L_stay_timer = 100;
		}
	}

	if (keys[KEY_INPUT_LEFT] == 0 )
	{
		L_stay_timer--;
		if (L_stay_timer <= 0)
		{
			L_stay_timer = 40;
		}
	}

	if (map[L_left_top_y][L_left_top_x] == RAZOR || map[L_left_bottom_y][L_left_bottom_x] == RAZOR)
	{
		// 自機の死亡フラグを立てる
		death_flag_L = 1;
	}

	if (map[L_left_top_y][L_left_top_x] == KEY || map[L_left_bottom_y][L_left_bottom_x] == KEY)
	{
		Get_key = 1;
		PlaySoundMem(key_pickup_handle, DX_PLAYTYPE_NORMAL, TRUE);

		if (scene == 2)
		{
			get_key_count = 1;
		}
	}

}

void PLAYER_Move_Jump()
{
	//右上
	R_right_top_x = (right_player.pos_x + right_player.radius - 1) / block_size;
	R_right_top_y = (right_player.pos_y - right_player.radius) / block_size;
	//右下
	R_right_bottom_x = (right_player.pos_x + right_player.radius - 1) / block_size;
	R_right_bottom_y = (right_player.pos_y + right_player.radius - 1) / block_size;

	//左上の座標
	R_left_top_x = (right_player.pos_x - right_player.radius) / block_size;
	R_left_top_y = (right_player.pos_y - right_player.radius) / block_size;
	//左下の座標
	R_left_bottom_x = (right_player.pos_x - right_player.radius ) / block_size;
	R_left_bottom_y = (right_player.pos_y + right_player.radius - 1) / block_size;

	//現在位置の底辺の情報
	right_player.bottom_y_info = right_player.pos_y + right_player.radius - 1;
	//→現在位置の底辺のマップチップ情報(底辺の情報からマップチップ上でのどの整数にいるかを計算する)
	right_player.bottom_y_maptip = int(right_player.pos_y + right_player.radius - 1) / block_size;

	//現在地より１つ下のy座標。自機の底辺の座標は一つ下の左上のy座標になるため。(上の2行からマップ上の自機の整数が取れたので、固定する位置を指定してブロックサイズをかけてあげる)
	right_player.bottom_y_height_plus = (right_player.bottom_y_maptip + 1) * block_size;
	//現在地より１つ下のマップチップの情報
	right_player.bottom_y_maptip_plus = int(right_player.bottom_y_height_plus / block_size);


	//現在位置の頂点の情報 
	right_player.top_y_info = right_player.pos_y - right_player.radius;	//→ここの-1要らない(右でも下でもない) to かわちゃん
	//現在位置の頂点のマップチップ情報
	right_player.top_y_maptip = int(right_player.pos_y - right_player.radius) / block_size;
	//頂点も同様に固定するためのy座標を出すためのy座標を求める。
	right_player.top_y_height = (right_player.top_y_maptip + 1) * block_size;
	//+8分なぞに足されていてピッタリではないが、+1した値が一番完成に近いので+1しておく

	//ジャンプの仕組み
	if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
	{
		jump_flag = 1;
		jump_count += 1;
	}
	// 左プレイヤーが生存しており かつ 地面にいる時に音を鳴らす
	if (jump_flag == 1 && jump_speed_timer == 12.0f && death_flag_R == 0)
	{
		PlaySoundMem(jump_sound_handle, DX_PLAYTYPE_BACK, TRUE);
	}

	if (jump_flag == 1)
	{
		jump_speed_timer--;

		//↓ここの処理の順番か、書き方が違う。
		if (jump_speed_timer < 30 && jump_speed_timer > 0)
		{
			right_player.pos_y -= right_player.jump_speed * jump_speed_timer;

			gravity_speed = 0;

			if (jump_speed_timer <= 0)
			{
				jump_speed_timer = 0;
			}
		}

		if (map[R_left_top_y][R_left_top_x] == BLOCK || map[R_right_top_y][R_right_top_x] == BLOCK)
		{
			right_player.pos_y = right_player.bottom_y_height_plus - right_player.radius;
			jump_speed_timer = 0;
			/*jump_speed_timer--;*/
			right_player.pos_y -= right_player.jump_speed * jump_speed_timer;
		}

		if (jump_speed_timer <= 0)
		{
			gravity_speed = 4;

			if (map[R_right_bottom_y][R_right_bottom_x] == BLOCK || map[R_left_bottom_y][R_left_bottom_x] == BLOCK)
			{
				jump_flag = 0;
				right_player.pos_y = right_player.top_y_height + 8; //どうしても
				jump_speed_timer = 12;
			}
			
			right_player.pos_y -= right_player.jump_speed * jump_speed_timer;

			if (jump_speed_timer <= 0)
			{	
				jump_speed_timer = 0;
			}
		}
	}
}

void PLAYER_Gravity()
{
	//現在位置の底辺の情報
	right_player.bottom_y_info = right_player.pos_y + right_player.radius - 1;
	//→現在位置の底辺のマップチップ情報(底辺の情報からマップチップ上でのどの整数にいるかを計算する)
	right_player.bottom_y_maptip = int(right_player.pos_y + right_player.radius - 1) / block_size;

	//現在地より１つ下のy座標。自機の底辺の座標は一つ下の左上のy座標になるため。(上の2行からマップ上の自機の整数が取れたので、固定する位置を指定してブロックサイズをかけてあげる)
	right_player.bottom_y_height_plus = (right_player.bottom_y_maptip + 1) * block_size;
	//現在地より１つ下のマップチップの情報
	right_player.bottom_y_maptip_plus = int(right_player.bottom_y_height_plus / block_size);
	//現在位置のマップのy座標
	right_player.bottom_y_height = (right_player.bottom_y_maptip) * block_size;

	//右下
	R_right_bottom_x = (right_player.pos_x + right_player.radius ) / block_size;
	R_right_bottom_y = (right_player.pos_y + right_player.radius ) / block_size;

	//左下の座標
	R_left_bottom_x = (right_player.pos_x - right_player.radius) / block_size;
	R_left_bottom_y = (right_player.pos_y + right_player.radius ) / block_size;

	//右下
	L_right_bottom_x = (left_player.pos_x + left_player.radius ) / block_size;
	L_right_bottom_y = (left_player.pos_y + left_player.radius ) / block_size;

	//左下の座標
	L_left_bottom_x = (left_player.pos_x - left_player.radius) / block_size;
	L_left_bottom_y = (left_player.pos_y + left_player.radius ) / block_size;

	if (map[R_right_bottom_y][R_right_bottom_x] == NONE && map[R_left_bottom_y][R_left_bottom_x] == NONE )
	{
		if (right_player.pos_y + right_player.radius <= 862)
		{
			right_player.speed_y += gravity_speed;
		}
	}
	if (map[L_right_bottom_y][L_right_bottom_x] == NONE && map[L_left_bottom_y][L_left_bottom_x] == NONE )
	{
		if (left_player.pos_y + left_player.radius <= 862)
		{
			left_player.speed_y += gravity_speed;
		}
	}
}

void RAZOR_Hit()
{
	//左側のキャラ
	//右上の座標
	R_right_top_x = (right_player.pos_x + right_player.radius) / block_size;
	R_right_top_y = (right_player.pos_y - right_player.radius) / block_size;
	//右下の座標
	R_right_bottom_x = (right_player.pos_x + right_player.radius) / block_size;
	R_right_bottom_y = (right_player.pos_y + right_player.radius) / block_size;
	//左上の座標
	R_left_top_x = (right_player.pos_x - right_player.radius) / block_size;
	R_left_top_y = (right_player.pos_y - right_player.radius) / block_size;
	//左下の座標
	R_left_bottom_x = (right_player.pos_x - right_player.radius) / block_size;
	R_left_bottom_y = (right_player.pos_y + right_player.radius) / block_size;

	//右側のキャラ
	//右上の座標
	L_right_top_x = (left_player.pos_x + left_player.radius -1) / block_size;
	L_right_top_y = (left_player.pos_y - left_player.radius) / block_size;
	//右下の座標
	L_right_bottom_x = (left_player.pos_x + left_player.radius -1) / block_size;
	L_right_bottom_y = (left_player.pos_y + left_player.radius -1) / block_size;
	//左上の座標
	L_left_top_x = (left_player.pos_x - left_player.radius) / block_size;
	L_left_top_y = (left_player.pos_y - left_player.radius) / block_size;
	//左下の座標
	L_left_bottom_x = (left_player.pos_x - left_player.radius) / block_size;
	L_left_bottom_y = (left_player.pos_y + left_player.radius -1) / block_size;

	//現在位置の底辺の情報
	right_player.bottom_y_info = right_player.pos_y + right_player.radius - 1;
	//→現在位置の底辺のマップチップ情報(底辺の情報からマップチップ上でのどの整数にいるかを計算する)
	right_player.bottom_y_maptip = int(right_player.pos_y + right_player.radius - 1) / block_size;

	//現在地より１つ下のy座標。自機の底辺の座標は一つ下の左上のy座標になるため。(上の2行からマップ上の自機の整数が取れたので、固定する位置を指定してブロックサイズをかけてあげる)
	right_player.bottom_y_height_plus = (right_player.bottom_y_maptip + 1) * block_size;
	//現在地より１つ下のマップチップの情報
	right_player.bottom_y_maptip_plus = int(right_player.bottom_y_height_plus / block_size);

	//現在位置の頂点の情報 
	right_player.top_y_info = right_player.pos_y - right_player.radius;    //→ここの-1要らない(右でも下でもない) to かわちゃん
	//現在位置の頂点のマップチップ情報
	right_player.top_y_maptip = int(right_player.pos_y - right_player.radius) / block_size;
	//頂点も同様に固定するためのy座標を出すためのy座標を求める。
	right_player.top_y_height = (right_player.top_y_maptip + 1) * block_size;
	//+8分なぞに足されていてピッタリではないが、+1した値が一番完成に近いので+1しておく

	//左側プレイヤー
	// 自機の右上or右下がレーザー(２)に当たった場合
	if (map[R_right_top_y][R_right_top_x] == RAZOR || map[R_right_bottom_y][R_right_bottom_x] == RAZOR || map[R_right_top_y][R_right_top_x] == RAZOR_S || map[R_right_bottom_y][R_right_bottom_x] == RAZOR_S)
	{
		// 自機の死亡フラグを立てる
		death_flag_R = 1;
	}

	// 死亡フラグが立っている場合
	if (death_flag_R == 1)
	{
		// カウントタイマーを減らす
		death_count_timer_R--;
		R_ko_anime_timer--;

		if (death_count_timer_R <= 0)
		{
			death_count_timer_R = 100;
			if (hp_count[2] == 1)
			{
				hp_count[2] = 0;
			}
			else if (hp_count[1] == 1)
			{
				hp_count[1] = 0;
			}
			else if (hp_count[0] == 1)
			{
				hp_count[0] = 0;
			}
		}
		if (R_ko_anime_timer <= 0)
		{
			R_ko_anime_timer = 40;
		}

		if (death_count_timer_R == 100)
		{
			right_player.pos_x = 96.0f;
			right_player.pos_y = 848.0f;

			death_flag_R = 0;
		}
	}

	if (death_flag_L == 1)
	{
		// カウントタイマーを減らす
		death_count_timer_L--;
		if (death_count_timer_L <= 0)
		{
			death_count_timer_L = 100;
			if (hp_count[2] == 1)
			{
				hp_count[2] = 0;
			}
			else if (hp_count[1] == 1)
			{
				hp_count[1] = 0;
			}
			else if (hp_count[0] == 1)
			{
				hp_count[0] = 0;
			}
		}
		if (death_count_timer_L == 100)
		{
			left_player.pos_x = 1264.0f;
			left_player.pos_y = 848.0f;

			death_flag_L = 0;
		}
	}
}

void SWITCH_Hit()
{
	//現在位置の底辺の情報
	right_player.bottom_y_info = right_player.pos_y + right_player.radius - 1;
	//→現在位置の底辺のマップチップ情報(底辺の情報からマップチップ上でのどの整数にいるかを計算する)
	right_player.bottom_y_maptip = int(right_player.pos_y + right_player.radius - 1) / block_size;
	//現在位置のマップのy座標
	right_player.bottom_y_height = (right_player.bottom_y_maptip) * block_size;

	//現在位置の右の情報
	right_player.right_x_info = right_player.pos_x + right_player.radius - 1;
	//現在位置の左の情報
	right_player.left_x_info = right_player.pos_x - right_player.radius ;

	//現在位置の右の情報
	left_player.right_x_info = left_player.pos_x + left_player.radius - 1;
	//現在位置の左の情報
	left_player.left_x_info = left_player.pos_x - left_player.radius ;

	//左側のキャラ
	//右上の座標
	R_right_top_x = (right_player.pos_x + right_player.radius -1) / block_size;
	R_right_top_y = (right_player.pos_y - right_player.radius) / block_size;
	//右下の座標
	R_right_bottom_x = (right_player.pos_x + right_player.radius -1) / block_size;
	R_right_bottom_y = (right_player.pos_y + right_player.radius -1) / block_size;
	//左上の座標
	R_left_top_x = (right_player.pos_x - right_player.radius) / block_size;
	R_left_top_y = (right_player.pos_y - right_player.radius) / block_size;
	//左下の座標
	R_left_bottom_x = (right_player.pos_x - right_player.radius) / block_size;
	R_left_bottom_y = (right_player.pos_y + right_player.radius -1) / block_size;

	//右上の座標
	L_right_top_x = (left_player.pos_x + left_player.radius - 1) / block_size;
	L_right_top_y = (left_player.pos_y - left_player.radius) / block_size;
	//右下の座標
	L_right_bottom_x = (left_player.pos_x + left_player.radius - 1) / block_size;
	L_right_bottom_y = (left_player.pos_y + left_player.radius - 1) / block_size;
	//左上の座標
	L_left_top_x = (left_player.pos_x - left_player.radius) / block_size;
	L_left_top_y = (left_player.pos_y - left_player.radius) / block_size;
	//左下の座標
	L_left_bottom_x = (left_player.pos_x - left_player.radius) / block_size;
	L_left_bottom_y = (left_player.pos_y + left_player.radius - 1) / block_size;

	if (scene == 0)
	{
		if (map[R_right_bottom_y][R_right_bottom_x] == SWITCH_BLOCK || map[R_left_bottom_y][R_left_bottom_x] == SWITCH_BLOCK || map[R_right_bottom_y][R_right_bottom_x] == SWITCH_RAZOR
			|| map[R_left_bottom_y][R_left_bottom_x] == SWITCH_RAZOR)
		{
			if (right_player.left_x_info < 608 && right_player.right_x_info >= 576)
			{
				switch_razor_flag = 1;
			}
		}
		if (right_player.bottom_y_info >= 848)
		{
			if (switch_razor_flag == 1)
			{
				if (right_player.left_x_info <= 608 && right_player.right_x_info > 576)
				{
					right_player.pos_y = 844;
				}
				for (int i = 26; i > 0; i--)
				{
					map[i][27] = NONE;
				}
			}
			
			if (right_player.right_x_info >= 572 && right_player.right_x_info <= 576)
			{
				right_player.pos_y = 848;
			}
			if (right_player.left_x_info == 608)
			{
				right_player.pos_y = 848;
			}
		}
	}

	if (scene == 1)
	{

		if (map[R_right_bottom_y][R_right_bottom_x] == SWITCH_BLOCK || map[R_left_bottom_y][R_left_bottom_x] == SWITCH_BLOCK || map[R_right_bottom_y][R_right_bottom_x] == SWITCH_RAZOR
			|| map[R_left_bottom_y][R_left_bottom_x] == SWITCH_RAZOR)
		{
			if (right_player.left_x_info < 634 && right_player.right_x_info >= 608)
			{
				switch_flag[0] = 1;
			}
			if (right_player.left_x_info < 666 && right_player.right_x_info > 640)
			{
				switch_flag[1] = 1;
			}
			if (right_player.left_x_info < 698 && right_player.right_x_info > 672)
			{
				switch_flag[2] = 1;
			}
			if (right_player.left_x_info < 730 && right_player.right_x_info > 704)
			{
				switch_flag[3] = 1;
			}
			if (right_player.left_x_info < 762 && right_player.right_x_info > 736)
			{
				switch_flag[4] = 1;
			}
			if (right_player.left_x_info < 800 && right_player.right_x_info > 768)
			{
				switch_razor_flag = 1;
			}
		}


		//スイッチの変更処理
		if (right_player.bottom_y_info >= 848)
		{
			if (switch_flag[0] == 1)
			{
				if (right_player.left_x_info <= 640 && right_player.right_x_info > 608)
				{
					right_player.pos_y = 844; //(864 -30)
				}

				if (right_player.right_x_info >= 604 && right_player.right_x_info <= 608)
				{
					right_player.pos_y = 848;
				}

				map[26][36] = NONE;
			}
			if (switch_flag[1] == 1)
			{
				if (right_player.left_x_info <= 672 && right_player.right_x_info > 640)
				{
					right_player.pos_y = 844;
				}

				for (int i = 26; i > 24; i--)
				{
					map[i][35] = NONE;
				}
			}
			if (switch_flag[2] == 1)
			{
				if (right_player.left_x_info <= 704 && right_player.right_x_info > 672)
				{
					right_player.pos_y = 844;
				}
				for (int i = 26; i > 23; i--)
				{
					map[i][34] = NONE;
				}
			}
			if (switch_flag[3] == 1)
			{
				if (right_player.left_x_info <= 736 && right_player.right_x_info > 704)
				{
					right_player.pos_y = 844;
				}
				for (int i = 26; i > 22; i--)
				{
					map[i][33] = NONE;
				}
			}
			if (switch_flag[4] == 1)
			{
				if (right_player.left_x_info <= 768 && right_player.right_x_info > 736)
				{
					right_player.pos_y = 844;
				}
				for (int i = 26; i > 21; i--)
				{
					map[i][32] = NONE;
				}
			}
			if (switch_razor_flag == 1)
			{
				if (right_player.left_x_info <= 800 && right_player.right_x_info > 768)
				{
					right_player.pos_y = 844;
				}
				if (right_player.left_x_info == 800)
				{
					right_player.pos_y = 848;
				}

				for (int i = 26; i > 0; i--)
				{
					map[i][27] = NONE;
				}

			}
		}
	}

	if (scene == 2)
	{
		if (map[L_right_bottom_y][L_right_bottom_x] == SWITCH_BLOCK || map[L_left_bottom_y][L_left_bottom_x] == SWITCH_BLOCK || map[L_right_bottom_y][L_right_bottom_x] == SWITCH_RAZOR
			|| map[L_left_bottom_y][L_left_bottom_x] == SWITCH_RAZOR)
		{
			//普通のスイッチ用
			if (left_player.left_x_info <= 1184 && left_player.right_x_info > 1152)//スイッチの上にどちらかが乗ればフラグをオンにする。
			{
				switch_flag[0] = 1;
			}
			//レーザースイッチ用
			if (left_player.left_x_info <= 768 && left_player.right_x_info > 736)//
			{
				switch_razor_flag = 1;
			}
		}
		if (map[R_right_bottom_y][R_right_bottom_x] == SWITCH_BLOCK || map[R_left_bottom_y][R_left_bottom_x] == SWITCH_BLOCK || map[R_right_bottom_y][R_right_bottom_x] == SWITCH_RAZOR
			|| map[R_left_bottom_y][R_left_bottom_x] == SWITCH_RAZOR)
		{
			//普通のスイッチ用
			if (right_player.left_x_info <= 1184 && right_player.right_x_info > 1152)//スイッチの上にどちらかが乗ればフラグをオンにする。
			{
				switch_flag[0] = 1;
			}
			//レーザースイッチ用
			if (right_player.left_x_info <= 768 && right_player.right_x_info > 736)//
			{
				switch_razor_flag = 1;
			}
		}

		if (left_player.bottom_y_info <= 848)
		{
			if (switch_flag[0] == 1)
			{
				if (left_player.left_x_info <= 1184 && left_player.right_x_info > 1152)
				{
					left_player.pos_y = 844; //(844)
				}
				//端の処理
				if (left_player.right_x_info >= 1132 && left_player.right_x_info <= 1136)
				{
					left_player.pos_y = 848;
				}

				if (left_player.left_x_info <= 1172 && left_player.right_x_info > 1168)
				{
					left_player.pos_y = 844; //(864 -30)
				}
				//端の処理
				if (left_player.right_x_info >= 1116 && left_player.right_x_info <= 1120)
				{
					left_player.pos_y = 848;
				}

				//スイッチ入った時
				for (int i = 16; i < 18; i++)
				{
					map[19][i] = BLOCK;
					map[20][i] = BLOCK;
				}
			}

			if (switch_razor_flag == 1)
			{
				if (right_player.bottom_y_info <= 450)
				{
					if (right_player.left_x_info <= 800 && right_player.right_x_info > 768)
					{
						right_player.pos_y = 395;
					}
					if (right_player.right_x_info >= 764 && right_player.right_x_info < 768)
					{
						right_player.pos_y = 400;
					}
				}

				for (int i = 26; i > 0; i--)
				{
					map[i][27] = NONE;
				}
			}
		}
	}

	if (scene == 3)
	{
		if (map[R_right_bottom_y][R_right_bottom_x] == SWITCH_BLOCK || map[R_left_bottom_y][R_left_bottom_x] == SWITCH_BLOCK || map[R_right_bottom_y][R_right_bottom_x] == SWITCH_RAZOR
			|| map[R_left_bottom_y][R_left_bottom_x] == SWITCH_RAZOR)
		{
			if (right_player.left_x_info < 634 && right_player.right_x_info >= 608)
			{
				switch_flag[0] = 1;
			}
			if (right_player.left_x_info < 666 && right_player.right_x_info > 640)
			{
				switch_flag[1] = 1;
			}
			if (right_player.left_x_info < 698 && right_player.right_x_info > 672)
			{
				switch_flag[2] = 1;
			}
			if (right_player.left_x_info < 730 && right_player.right_x_info > 704)
			{
				switch_flag[3] = 1;
			}
			if (right_player.left_x_info < 762 && right_player.right_x_info > 736)
			{
				switch_flag[4] = 1;
			}
		}

		if (map[L_right_bottom_y][L_right_bottom_x] == SWITCH_BLOCK || map[L_left_bottom_y][L_left_bottom_x] == SWITCH_BLOCK || map[L_right_bottom_y][L_right_bottom_x] == SWITCH_RAZOR
			|| map[L_left_bottom_y][L_left_bottom_x] == SWITCH_RAZOR)
		{
			if (left_player.left_x_info <= 960 && left_player.right_x_info > 928)
			{
				switch_razor_flag = 1;
			}
		}


		//スイッチの変更処理
		if (right_player.bottom_y_info >= 848)
		{
			if (switch_flag[0] == 1)
			{
				if (right_player.left_x_info <= 640 && right_player.right_x_info > 608)
				{
					right_player.pos_y = 844; //(864 -30)
				}

				if (right_player.right_x_info >= 604 && right_player.right_x_info <= 608)
				{
					right_player.pos_y = 848;
				}

				if (left_player.left_x_info <= 640 && left_player.right_x_info > 608)
				{
					left_player.pos_y = 844; //(864 -30)
				}

				if (left_player.right_x_info >= 604 && left_player.right_x_info <= 608)
				{
					left_player.pos_y = 848;
				}

				map[26][36] = NONE;
			}
			if (switch_flag[1] == 1)
			{
				if (right_player.left_x_info <= 672 && right_player.right_x_info > 640)
				{
					right_player.pos_y = 844;
				}
				if (left_player.left_x_info <= 672 && left_player.right_x_info > 640)
				{
					left_player.pos_y = 844;
				}

				for (int i = 26; i > 24; i--)
				{
					map[i][35] = NONE;
				}
			}
			if (switch_flag[2] == 1)
			{
				if (right_player.left_x_info <= 704 && right_player.right_x_info > 672)
				{
					right_player.pos_y = 844;
				}
				if (left_player.left_x_info <= 704 && left_player.right_x_info > 672)
				{
					left_player.pos_y = 844;
				}
				for (int i = 26; i > 23; i--)
				{
					map[i][34] = NONE;
				}
			}
			if (switch_flag[3] == 1)
			{
				if (right_player.left_x_info <= 736 && right_player.right_x_info > 704)
				{
					right_player.pos_y = 844;
				}
				if (left_player.left_x_info <= 736 && left_player.right_x_info > 704)
				{
					left_player.pos_y = 844;
				}
				for (int i = 26; i > 22; i--)
				{
					map[i][33] = NONE;
				}
			}
			if (switch_flag[4] == 1)
			{
				if (right_player.left_x_info <= 768 && right_player.right_x_info > 736)
				{
					right_player.pos_y = 844;
				}
				if (left_player.left_x_info <= 768 && left_player.right_x_info > 736)
				{
					left_player.pos_y = 844;
				}
				for (int i = 26; i > 21; i--)
				{
					map[i][32] = NONE;
				}
			}
			if (switch_razor_flag == 1)
			{
				if (left_player.left_x_info <= 960 && left_player.right_x_info > 928)
				{
					left_player.pos_y = 844;
				}
				if (left_player.right_x_info >= 920 && left_player.right_x_info <= 928)
				{
					left_player.pos_y = 848;
				}
				if (left_player.left_x_info >= 960 && left_player.left_x_info <= 968)
				{
					left_player.pos_y = 848;
				}


				if (right_player.left_x_info <= 960 && right_player.right_x_info > 928)
				{
					right_player.pos_y = 844;
				}

				if (right_player.right_x_info >= 920 && right_player.right_x_info <= 928)
				{
					right_player.pos_y = 848;
				}
				if (right_player.left_x_info >= 960 && right_player.left_x_info <= 968)
				{
					right_player.pos_y = 848;
				}


				for (int i = 26; i > 0; i--)
				{
					map[i][27] = NONE;
				}
			}
		}
	}

	if (scene == 4)
	{
		if (map[R_right_bottom_y][R_right_bottom_x] == SWITCH_BLOCK || map[R_left_bottom_y][R_left_bottom_x] == SWITCH_BLOCK || map[R_right_bottom_y][R_right_bottom_x] == SWITCH_RAZOR
			|| map[R_left_bottom_y][R_left_bottom_x] == SWITCH_RAZOR)
		{
			if (right_player.left_x_info < 384 && right_player.right_x_info >= 352)
			{
				switch_flag[0] = 1;
			}
			if (right_player.left_x_info < 480 && right_player.right_x_info > 448)
			{
				switch_flag[1] = 1;
			}

			if (right_player.left_x_info < 576 && right_player.right_x_info > 544)
			{
				switch_razor_flag = 1;
			}
		}
		else if (right_player.left_x_info >= 576 || right_player.right_x_info <= 544 && switch_razor_flag == 1)
		{
			switch_razor_flag = 0;
		}

		if (right_player.bottom_y_info < 768 && right_player.bottom_y_info >= 700 && jump_flag == 0)
		{
			if (switch_flag[0] == 1)
			{
				if (right_player.left_x_info <= 384 && right_player.right_x_info > 352) //自機の座標に半径分足したもの
				{
					right_player.pos_y = 716;
				}
			}
			
		}
		if (right_player.bottom_y_info < 640 && right_player.bottom_y_info >= 572 && jump_flag == 0)
		{
			if (switch_flag[1] == 1)
			{
				if (right_player.left_x_info <= 480 && right_player.right_x_info > 448) //自機の座標に半径分足したもの
				{
					right_player.pos_y = 588;
				}
			}
		}
		if (right_player.bottom_y_info < 512 && right_player.bottom_y_info >= 0 && jump_flag == 0)
		{
			if (switch_razor_flag == 1)
			{
				if (right_player.left_x_info <= 576 && right_player.right_x_info > 544) //自機の座標に半径分足したもの
				{
					right_player.pos_y = 460;
				}

				for (int i = 26; i > 0; i--)
				{
					map[i][27] = NONE;
				}
			}
		}

		if (switch_flag[2] == 1)
		{
			for (int i = 26; i > 23; i--)
			{
				map[i][38] = NONE;
			}
		}

		if (switch_razor_flag == 0)
		{
			for (int i = 25; i > 0; i--)
			{
				map[i][27] = RAZOR;
			}
			map[26][27] = RAZOR_S;
		}
	}
	// ---------- 下移動 ---------- //
}

void Fusion()
{
	//左側のキャラ
  //右上の座標
	R_right_top_x = (right_player.pos_x + right_player.radius) / block_size;
	R_right_top_y = (right_player.pos_y - right_player.radius) / block_size;
	//右下の座標
	R_right_bottom_x = (right_player.pos_x + right_player.radius) / block_size;
	R_right_bottom_y = (right_player.pos_y + right_player.radius) / block_size;
	//左上の座標
	R_left_top_x = (right_player.pos_x - right_player.radius) / block_size;
	R_left_top_y = (right_player.pos_y - right_player.radius) / block_size;
	//左下の座標
	R_left_bottom_x = (right_player.pos_x - right_player.radius -1) / block_size;
	R_left_bottom_y = (right_player.pos_y + right_player.radius -1) / block_size;

	//右上の座標
	L_right_top_x = (left_player.pos_x + left_player.radius - 1) / block_size;
	L_right_top_y = (left_player.pos_y - left_player.radius) / block_size;
	//右下の座標
	L_right_bottom_x = (left_player.pos_x + left_player.radius - 1) / block_size;
	L_right_bottom_y = (left_player.pos_y + left_player.radius - 1) / block_size;
	//左上の座標
	L_left_top_x = (left_player.pos_x - left_player.radius) / block_size;
	L_left_top_y = (left_player.pos_y - left_player.radius) / block_size;
	//左下の座標
	L_left_bottom_x = (left_player.pos_x - left_player.radius) / block_size;
	L_left_bottom_y = (left_player.pos_y + left_player.radius - 1) / block_size;

	if (map[R_right_top_y][R_right_top_x] == KEY || map[R_right_bottom_y][R_right_bottom_x] == KEY)
	{
		Get_key = 1;
		PlaySoundMem(key_pickup_handle, DX_PLAYTYPE_NORMAL, TRUE);
		PlaySoundMem(goal_open_handle, DX_PLAYTYPE_BACK, TRUE);
	}

	if (map[R_left_top_y][R_left_top_x] == KEY || map[R_left_bottom_y][R_left_bottom_x] == KEY)
	{
		Get_key = 1;
		PlaySoundMem(key_pickup_handle, DX_PLAYTYPE_NORMAL, TRUE);
		PlaySoundMem(goal_open_handle, DX_PLAYTYPE_BACK, TRUE);
	}

	if (Get_key == 1)
	{
		left_player.pos_x = -32;
		left_player.pos_y = -32;

		if (scene == 0)
		{
			move_change_flag = 1;
			map[26][30] = NONE;
		}

		if (scene == 1)
		{
			move_change_flag = 1;
			map[26][30] = NONE;
		}

		if (scene == 2)
		{
			move_change_flag = 1;

			if (get_key_count == 1)
			{
				map[26][25] = NONE;

				if (map[R_right_top_y][R_right_top_x] == KEY || map[R_right_bottom_y][R_right_bottom_x] == KEY)
				{
					get_key_count = 2;
				}

				if (map[R_left_top_y][R_left_top_x] == KEY || map[R_left_bottom_y][R_left_bottom_x] == KEY)
				{
					get_key_count = 2;
				}
			}
			if (get_key_count == 2)
			{
				map[11][15] = NONE;
			}
		}

		if (scene == 3)
		{
			move_change_flag = 1;
			map[26][30] = NONE;
		}
		if (scene == 4)
		{
			move_change_flag = 1;
			map[26][25] = NONE;
		}
	}

	if (Get_key == 0)
	{
		if (scene == 0)
		{
			map[26][30] = KEY;
		}

		if (scene == 1)
		{
			map[26][30] = KEY;
		}

		if (scene == 2)
		{
			map[11][15] = KEY;
			map[26][25] = KEY;
		}

		if (scene == 3)
		{
			map[26][27] = KEY;
		}

		if (scene == 4)
		{
			map[26][25] = KEY;
		}
	}
}

void Fusion_Draw()
{
	if (move_change_flag == 1)// 合体後
	{
		DrawGraph(right_player.pos_x - 8, right_player.pos_y - 56, arrow_handle[0], true);// ↑矢印
		DrawRotaGraph(right_player.pos_x + 16, right_player.pos_y - 32, 1.0f, PI / 2, arrow_handle[0], true, true);// →矢印
		DrawRotaGraph(right_player.pos_x - 16, right_player.pos_y - 32, 1.0f, PI / -2, arrow_handle[0], true, true);// ←矢印

		if (keys[KEY_INPUT_LEFT] == 1)
		{
			DrawRotaGraph(right_player.pos_x - 16, right_player.pos_y - 32, 1.0f, PI / -2, arrow_handle[1], true, true);// ←矢印

		}
		else if (keys[KEY_INPUT_RIGHT] == 1)
		{
			DrawRotaGraph(right_player.pos_x + 16, right_player.pos_y - 32, 1.0f, PI / 2, arrow_handle[1], true, true);// →矢印
		}
		else if (keys[KEY_INPUT_SPACE] == 1)
		{
			DrawGraph(right_player.pos_x - 8, right_player.pos_y - 56, arrow_handle[1], true);// ↑矢印
		}

	}
}

void player_draw()
{
	//ゴールの描写
	if (Get_key == 1)
	{	
		if (scene == 0 || scene == 1 || scene == 3 || scene == 4)
		{
			DrawGraph(64, 768, goal_handle[0], true);
		}
		if (scene == 2)
		{
			if (get_key_count == 2)
			{
				DrawGraph(64, 768, goal_handle[0], true);
			}
			else
			{
				DrawGraph(64, 768, goal_handle[1], true);
			}
		}
	}
	else if (Get_key == 0)
	{
		DrawGraph(64, 768, goal_handle[1], true);
	}

	//右のみのキャラの死亡アニメーションと待機モーション
	if (death_flag_R == 0)
	{
		//待機アニメーション
		if (keys[KEY_INPUT_RIGHT] == 0 && keys[KEY_INPUT_LEFT] == 0)
		{
			if (R_stay_timer >= 30 && R_stay_timer <= 40)
			{
				DrawGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_stay_handle[0], true);
			}
			if (R_stay_timer >= 20 && R_stay_timer < 30)
			{
				DrawGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_stay_handle[1], true);
			}
			if (R_stay_timer >= 10 && R_stay_timer < 20)
			{
				DrawGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_stay_handle[2], true);
			}
			if (R_stay_timer >= 0 && R_stay_timer < 10)
			{
				DrawGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_stay_handle[3], true);
			}
		}
		
		//右のキャラの右移動
		else if (keys[KEY_INPUT_RIGHT] == 1)
		{
			if (R_walk_timer >= 50 && R_walk_timer <= 60)
			{
				DrawGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_move_handle[0], true);
			}
			if (R_walk_timer >= 40 && R_walk_timer < 50)
			{
				DrawGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_move_handle[1], true);
			}
			if (R_walk_timer >= 30 && R_walk_timer <= 40)
			{
				DrawGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_move_handle[2], true);
			}
			if (R_walk_timer >= 20 && R_walk_timer < 30)
			{
				DrawGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_move_handle[3], true);
			}
			if (R_walk_timer >= 10 && R_walk_timer < 20)
			{
				DrawGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_move_handle[4], true);
			}
			if (R_walk_timer >= 0 && R_walk_timer < 10)
			{
				DrawGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_move_handle[5], true);
			}
		}

		//右のキャラの左移動のアニメーション
		else if (keys[KEY_INPUT_LEFT] == 1 )
		{
			if (move_change_flag == 1)
			{
				if (L_walk_timer >= 50 && L_walk_timer <= 60)
				{
					DrawTurnGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_move_handle[0], true);
				}
				if (L_walk_timer >= 40 && L_walk_timer < 50)
				{
					DrawTurnGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_move_handle[1], true);
				}
				if (L_walk_timer >= 30 && L_walk_timer <= 40)
				{
					DrawTurnGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_move_handle[2], true);
				}
				if (L_walk_timer >= 20 && L_walk_timer < 30)
				{
					DrawTurnGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_move_handle[3], true);
				}
				if (L_walk_timer >= 10 && L_walk_timer < 20)
				{
					DrawTurnGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_move_handle[4], true);
				}
				if (L_walk_timer >= 0 && L_walk_timer < 10)
				{
					DrawTurnGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_move_handle[5], true);
				}
			}
			else
			{
				DrawGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_stay_handle[0], true);
			}
			
		}

		DrawGraph(right_player.pos_x - 8, right_player.pos_y - 56, arrow_handle[0], true);// ↑矢印
		DrawRotaGraph(right_player.pos_x + 16, right_player.pos_y - 32, 1.0f, PI / 2, arrow_handle[0], true, true);// →矢印
		if (keys[KEY_INPUT_RIGHT] == 1)
		{
			DrawRotaGraph(right_player.pos_x + 16, right_player.pos_y - 32, 1.0f, PI / 2, arrow_handle[1], true, true);// →矢印
		}
		if (keys[KEY_INPUT_SPACE] == 1)
		{
			DrawGraph(right_player.pos_x - 8, right_player.pos_y - 56, arrow_handle[1], true);// ↑矢印
		}
	}
	else if (death_flag_R == 1)
	{
		//死亡アニメーション
		if (death_count_timer_R >= 0)
		{
			if (R_ko_anime_timer >= 20)
			{
				DrawGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_ko_handle[0], true);
			}
			else if (R_ko_anime_timer < 20)
			{
				DrawGraph(right_player.pos_x - right_player.radius, right_player.pos_y - right_player.radius, player_ko_handle[1], true);
			}
		}
	}

	//左のみのキャラの死亡アニメーションと待機モーション
	if (death_flag_L == 0 )
	{
		if (Get_key == 0)
		{
			//待機アニメーション
			if (keys[KEY_INPUT_LEFT] == 0)
			{
				if (L_stay_timer >= 30 && L_stay_timer <= 40)
				{
					DrawTurnGraph(left_player.pos_x - left_player.radius, left_player.pos_y - left_player.radius, player_stay_handle[0], true);
				}
				if (L_stay_timer >= 20 && L_stay_timer < 30)
				{
					DrawTurnGraph(left_player.pos_x - left_player.radius, left_player.pos_y - left_player.radius, player_stay_handle[1], true);
				}
				if (L_stay_timer >= 10 && L_stay_timer < 20)
				{
					DrawTurnGraph(left_player.pos_x - left_player.radius, left_player.pos_y - left_player.radius, player_stay_handle[2], true);
				}
				if (L_stay_timer >= 0 && L_stay_timer < 10)
				{
					DrawTurnGraph(left_player.pos_x - left_player.radius, left_player.pos_y - left_player.radius, player_stay_handle[3], true);
				}

			}
			//左のみのキャラの左移動のアニメーション
			else if (keys[KEY_INPUT_LEFT] == 1)
			{
				if (L_walk_timer >= 50 && L_walk_timer <= 60)
				{
					DrawTurnGraph(left_player.pos_x - left_player.radius, left_player.pos_y - left_player.radius, player_move_handle[0], true);
				}
				if (L_walk_timer >= 40 && L_walk_timer < 50)
				{
					DrawTurnGraph(left_player.pos_x - left_player.radius, left_player.pos_y - left_player.radius, player_move_handle[1], true);
				}
				if (L_walk_timer >= 30 && L_walk_timer <= 40)
				{
					DrawTurnGraph(left_player.pos_x - left_player.radius, left_player.pos_y - left_player.radius, player_move_handle[2], true);
				}
				if (L_walk_timer >= 20 && L_walk_timer < 30)
				{
					DrawTurnGraph(left_player.pos_x - left_player.radius, left_player.pos_y - left_player.radius, player_move_handle[3], true);
				}
				if (L_walk_timer >= 10 && L_walk_timer < 20)
				{
					DrawTurnGraph(left_player.pos_x - left_player.radius, left_player.pos_y - left_player.radius, player_move_handle[4], true);
				}
				if (L_walk_timer >= 0 && L_walk_timer < 10)
				{
					DrawTurnGraph(left_player.pos_x - left_player.radius, left_player.pos_y - left_player.radius, player_move_handle[5], true);
				}
			}

			DrawRotaGraph(left_player.pos_x, left_player.pos_y - 32, 1.0f, PI / -2, arrow_handle[0], true, true);// ←矢印
			if (keys[KEY_INPUT_LEFT] == 1)
			{
				DrawRotaGraph(left_player.pos_x, left_player.pos_y - 32, 1.0f, PI / -2, arrow_handle[1], true, true);// ←矢印
			}
		}
	}
	else if (death_flag_L == 1)
	{
		//死亡アニメーション
		if (death_count_timer_L >= 0)
		{
			if (L_ko_anime_timer >= 20)
			{
				DrawTurnGraph(left_player.pos_x - left_player.radius, left_player.pos_y - left_player.radius, player_ko_handle[0], true);
			}
			else if (L_ko_anime_timer < 20)
			{
				DrawTurnGraph(left_player.pos_x - left_player.radius, left_player.pos_y - left_player.radius, player_ko_handle[1], true);
			}
		}
	}
}

void HP_draw()
{
	if (hp_count[0] == 1)
	{
		DrawGraph(32, 32, left_hp_handle[1], true);
	}
	else if (hp_count[0] == 0)
	{
		DrawGraph(32, 32, left_hp_handle[0], true);
	}
	if (hp_count[1] == 1)
	{
		DrawGraph(64, 32, left_hp_handle[1], true);
	}
	else if (hp_count[1] == 0)
	{
		DrawGraph(64, 32, left_hp_handle[0], true);
	}
	if (hp_count[2] == 1)
	{
		DrawGraph(96, 32, left_hp_handle[1], true);
	}
	else if (hp_count[2] == 0)
	{
		DrawGraph(96, 32, left_hp_handle[0], true);
	}
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);
	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	// タイトルを変更
	SetMainWindowText(TITLE);
	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);
	// 画面の背景色を設定する
	SetBackgroundColor(0x1E, 0x1F, 0x36);
	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }
	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲームループで使う変数の宣言
	// int型の2次元配列の宣言と初期化リストの準備
	MAP_Init();

	// ゲームループで使う変数の宣言

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		// ---------- ここからプログラムを記述 ---------- //
		// ---------- 更新処理 ---------- //
		 
		if (right_player.pos_y + right_player.radius >= 848 && jump_flag == 1)
		{
			jump_flag = 0;
			right_player.pos_y = 848;
			jump_speed_timer = 12;
			jump_count = 0;
		}

		if (left_player.pos_y + left_player.radius >= 848)
		{
			left_player.pos_y = 848;
		}
		
		// マップチップの当たり判定＆移動処理
		right_player.speed_x = 0;
		right_player.speed_y = 0;

		left_player.speed_x = 0;
		left_player.speed_y = 0;

		if (move_change_flag == 1)
		{
			PLAYER_Move_Fusion();
		}
		if (move_change_flag == 0)
		{
			PLAYER_Move_Right_Man();
			PLAYER_Move_Left_Man();
		}
		PLAYER_Gravity();

		right_player.pos_x += right_player.speed_x;
		right_player.pos_y += right_player.speed_y;

		left_player.pos_x += left_player.speed_x;
		left_player.pos_y += left_player.speed_y;

		PLAYER_Move_Jump();
		RAZOR_Hit();
		SWITCH_Hit();
		Fusion();

		// ---------- シーン管理 ---------- //
		if (scene == 0)// タイトル＆チュートリアル画面
		{
			if(keys[KEY_INPUT_RETURN] == 1)
			{
				scene = 4;
				left_player.pos_y = 592.0f;
			}

			title_ani_timer--;

			map[26][32] = BLOCK;

			for (int i = 22; i < 26 ; i++)
			{
				map[i][32] = BLOCK;
			}

			if (Get_key == 1)
			{

				if (right_player.pos_x <= 98 && right_player.pos_x >= 92)
				{
					if (right_player.pos_y <= 848 && right_player.pos_y >= 812)
					{
						PlaySoundMem(goal_sound_handle, DX_PLAYTYPE_NORMAL, TRUE);
						//初期化
						Get_key = 0;
						move_change_flag = 0;
						switch_razor_flag = 0;
						right_player.pos_x = 224.0f;
						right_player.pos_y = 848.0f;
						left_player.pos_x = 1264.0f;
						left_player.pos_y = 848.0f;

						scene = 1;
					}
				}
			}
		}

		if (scene == 1)
		{

			if (Get_key == 0 && switch_razor_flag == 0)
			{
				for (int i = 25; i > 0; i--)
				{
					map[i][27] = RAZOR;
				}
				map[26][27] = RAZOR_S;
			}

			for (int i = 19; i < 24; i++) 
			{
				map[26][i] = SWITCH_BLOCK;
			}

			map[26][24] = SWITCH_RAZOR;

			for (int i = 32; i < 37; i++)
			{
				if (switch_flag[0] == 0)
				{
					map[26][i] = BLOCK;
				}

				if (i < 36)
				{
					if (switch_flag[1] == 0)
					{
						map[25][i] = BLOCK;
					}
				}
				
				if (i < 35)
				{
					if (switch_flag[2] == 0)
					{
						map[24][i] = BLOCK;
					}
				}

				if (i < 34)
				{
					if (switch_flag[3] == 0)
					{
						map[23][i] = BLOCK;
					}
				}

				if (i < 33)
				{
					if (switch_flag[4] == 0)
					{
						map[22][i] = BLOCK;
					}
				}
			}

			if (Get_key == 1)
			{
				if (right_player.pos_x <= 98 && right_player.pos_x >= 92)
				{
					if (right_player.pos_y <= 848 && right_player.pos_y >= 812)
					{
						PlaySoundMem(goal_sound_handle, DX_PLAYTYPE_NORMAL, TRUE);
						//初期化
						Get_key = 0;
						move_change_flag = 0;
						switch_razor_flag = 0;
						right_player.pos_x = 224.0f;
						right_player.pos_y = 848.0f;
						left_player.pos_x = 1264.0f;
						left_player.pos_y = 848.0f;

						for (int i = 0; i < 5; i++)
						{
							switch_flag[i] = 0;
						}

						scene = 3;
					}
				}
			}
		}
		if (scene == 2)
		{
			map[12][20] = NONE;
			map[12][21] = NONE;

			map[26][32] = NONE;
			map[26][30] = NONE;

			for (int i = 10; i < 13; i++)
			{
				map[23][i] = NONE;
			}
			
			for (int i = 15; i < 27; i++)
			{
				map[23][i] = NONE;
			}

			for (int i = 13; i < 27; i++)
			{
				map[19][i] = NONE;
			}
			for (int i = 16; i < 21; i++)
			{
				map[15][i] = NONE;
			}
			
			map[15][25] = NONE;
			map[15][26] = NONE;

			
			if (Get_key == 0 && switch_razor_flag == 0)
			{
				for (int i = 25; i > 0; i--)
				{
					map[i][27] = RAZOR;
				}
				map[26][27] = RAZOR_S;
			}
			for (int i = 10; i < 15; i++)
			{
				map[26][i] = BLOCK;
				if (i > 10)
				{
					map[25][i] = BLOCK;
				}
				if (i > 11)
				{
					map[24][i] = BLOCK;
				}
				if (i > 12)
				{
					map[23][i] = BLOCK;
				}
				if (i > 13)
				{
					map[22][i] = BLOCK;
				}
				if (i > 14)
				{
					map[21][i] = BLOCK;
				}
			}

			for (int i = 19; i < 24; i++)
			{
				map[17][i] = BLOCK;
				if (i > 19)
				{
					map[16][i] = BLOCK;
				}
				if (i > 20)
				{
					map[15][i] = BLOCK;
				}
				if (i > 21)
				{
					map[14][i] = BLOCK;
				}
				if (i > 22)
				{
					map[13][i] = BLOCK;
				}
			}

			for (int i = 13; i < 18; i++)
			{
				map[12][i] = BLOCK;
			}

			for (int i = 13; i < 18; i++)
			{
				map[i][24] = BLOCK;
			}

			for (int i = 22; i < 27; i++)
			{
				map[i][24] = BLOCK;
			}
			map[22][25] = BLOCK;
			map[22][26] = BLOCK;

			map[12][24] = SWITCH_RAZOR;
			map[26][35] = SWITCH_BLOCK;

			if (Get_key == 1 && get_key_count == 2)
			{
				if (right_player.pos_x <= 98 && right_player.pos_x >= 92)
				{
					if (right_player.pos_y <= 848 && right_player.pos_y >= 812)
					{
						PlaySoundMem(goal_sound_handle, DX_PLAYTYPE_NORMAL, TRUE);
						//初期化
						Get_key = 0;
						move_change_flag = 0;
						switch_razor_flag = 0;
						right_player.pos_x = 224.0f;
						right_player.pos_y = 848.0f;
						left_player.pos_x = 1264.0f;
						left_player.pos_y = 848.0f;

						for (int i = 0; i < 5; i++)
						{
							switch_flag[i] = 0;
						}

						scene = 6;
					}
				}
			}
		}

		if (scene == 3)
		{
			
			for (int i = 18; i < 24; i++)
			{
				map[26][i] = NONE;
			}

			map[26][30] = NONE;

			if (Get_key == 0 && switch_razor_flag == 0)
			{
				for (int i = 25; i > 0; i--)
				{
					map[i][27] = RAZOR;
				}

				map[26][27] = RAZOR_S;
			}

			for (int i = 19; i < 24; i++)
			{
				map[26][i] = SWITCH_BLOCK;
			}

			map[26][29] = SWITCH_RAZOR;

			for (int i = 32; i < 37; i++)
			{
				if (switch_flag[0] == 0)
				{
					map[26][i] = BLOCK;
				}

				if (i < 36)
				{
					if (switch_flag[1] == 0)
					{
						map[25][i] = BLOCK;
					}
				}

				if (i < 35)
				{
					if (switch_flag[2] == 0)
					{
						map[24][i] = BLOCK;
					}
				}

				if (i < 34)
				{
					if (switch_flag[3] == 0)
					{
						map[23][i] = BLOCK;
					}
				}

				if (i < 33)
				{
					if (switch_flag[4] == 0)
					{
						map[22][i] = BLOCK;
					}
				}
			}

			if (Get_key == 1)
			{
				if (right_player.pos_x <= 98 && right_player.pos_x >= 92)
				{
					if (right_player.pos_y <= 848 && right_player.pos_y >= 812)
					{
						PlaySoundMem(goal_sound_handle, DX_PLAYTYPE_NORMAL, TRUE);
						//初期化
						Get_key = 0;
						move_change_flag = 0;
						switch_razor_flag = 0;
						right_player.pos_x = 256.0f;
						right_player.pos_y = 848.0f;
						left_player.pos_x = 1264.0f;
						left_player.pos_y = 592.0f;

						for (int i = 0; i < 5; i++)
						{
							switch_flag[i] = 0;
						}

						map[26][20] = NONE;
						map[26][21] = NONE;
						map[26][22] = NONE;
						map[26][23] = NONE;

						scene = 4;
					}
				}
			}
		}

		if (scene == 4)
		{
			/*map[20][16] = NONE;
			map[20][17] = NONE;
			map[26][24] = NONE;
			map[25][24] = NONE;
			map[24][24] = NONE;
			map[22][24] = NONE;
			map[22][25] = NONE;
			map[22][26] = NONE;*/

			map[23][21] = NONE;
			map[25][23] = NONE;
			map[24][23] = NONE;

			map[26][21] = NONE;
			map[26][22] = NONE;

			map[26][30] = NONE;
			map[26][32] = NONE;

			map[22][32] = NONE;
			map[24][32] = NONE;
			map[25][32] = NONE;



			for (int i = 18; i < 24; i++)
			{
				map[26][i] = NONE;
			}

			for (int i = 10; i < 20; i++)
			{
				map[23][i] = BLOCK;
			}

			for (int i = 23; i < 27; i++)
			{
				map[23][i] = BLOCK;
			}


			for (int i = 20; i < 23; i++)
			{
				map[26][i] = BLOCK;
				if (i > 20)
				{
					map[25][i] = BLOCK;
				}
				if (i > 21)
				{
					map[24][i] = BLOCK;
				}
			}


			if (switch_flag[0] == 0)
			{
				for (int i = 28; i < 42; i++)
				{
					map[23][i] = BLOCK;
				}
			}
			else if (switch_flag[0] == 1)
			{
				for (int i = 28; i < 38; i++)
				{
					map[23][i] = NONE;
				}
			}
			
			for (int i = 13; i < 27; i++)
			{
				map[19][i] = BLOCK;
			}

			if (switch_flag[1] == 0)
			{
				for (int i = 28; i < 42; i++)
				{
					map[19][i] = BLOCK;
				}
			}
			else if (switch_flag[1] == 1)
			{
				for (int i = 28; i < 38; i++)
				{
					map[19][i] = NONE;
				}
			}
			
			for (int i = 16; i < 27; i++)
			{
				map[15][i] = BLOCK;
			}

			for (int i = 26; i > 23; i--)
			{
				map[i][23] = BLOCK;
			}

			map[22][11] = SWITCH_BLOCK;
			map[18][14] = SWITCH_BLOCK;
			map[14][17] = SWITCH_BLOCK;

			if (Get_key == 1)
			{
				if (right_player.pos_x <= 98 && right_player.pos_x >= 92)
				{
					if (right_player.pos_y <= 848 && right_player.pos_y >= 812)
					{
						PlaySoundMem(goal_sound_handle, DX_PLAYTYPE_NORMAL, TRUE);
						//初期化
						Get_key = 0;
						move_change_flag = 0;
						switch_razor_flag = 0;
						right_player.pos_x = 256.0f;
						right_player.pos_y = 848.0f;
						left_player.pos_x = 1264.0f;
						left_player.pos_y = 848.0f;

						for (int i = 0; i < 5; i++)
						{
							switch_flag[i] = 0;
						}

						scene = 2;
					}
				}
			}
		}

		if (hp_count[0] == 0)
		{
			//初期化
			Get_key = 0;
			move_change_flag = 0;
			switch_razor_flag = 0;
			right_player.pos_x = 256.0f;
			right_player.pos_y = 848.0f;
			left_player.pos_x = 1264.0f;
			left_player.pos_y = 848.0f;

			//ステージ選択させるならsceneで移動させる前に鍵の位置。またはプレイヤーの位置を初期化

			scene = 5;//ゲームオーバー画面
		}

		if (scene == 5)
		{
			game_over_time--;

			if (game_over_time <= 0)
			{
				game_over_time = 60;
			}
		}

		if (scene == 6)
		{
			game_clear_time--;

			if (game_clear_time <= 0)
			{
				game_clear_time = 60;
			}
		}




		// ---------- 描画処理 ---------- //
		// 描画処理をswitch文で書く
		switch (scene)
		{

		case 0:// タイトル
			MAP_Draw();
			Deviece_Draw();
			HP_draw();
			Fusion_Draw();

			//// タイトル＆チュートリアル画面

			////電撃も含めた描写

			if (title_ani_timer <= 130 && title_ani_timer > 120)
			{
				DrawGraph(0, 0, gametitle_text_handle[0], true);
			}if (title_ani_timer <= 120 && title_ani_timer > 110)
			{
				DrawGraph(0, 0, gametitle_text_handle[1], true);
			}if (title_ani_timer <= 110 && title_ani_timer > 100)
			{
				DrawGraph(0, 0, gametitle_text_handle[2], true);
			}if (title_ani_timer <= 100 && title_ani_timer > 90)
			{
				DrawGraph(0, 0, gametitle_text_handle[3], true);
			}if (title_ani_timer <= 90 && title_ani_timer > 80)
			{
				DrawGraph(0, 0, gametitle_text_handle[4], true);
			}if (title_ani_timer <= 80 && title_ani_timer > 70)
			{
				DrawGraph(0, 0, gametitle_text_handle[5], true);
			}if (title_ani_timer <= 70 && title_ani_timer > 60)
			{
				DrawGraph(0, 0, gametitle_text_handle[6], true);
			}if (title_ani_timer <= 60 && title_ani_timer > 50)
			{
				DrawGraph(0, 0, gametitle_text_handle[7], true);
			}if (title_ani_timer <= 50 && title_ani_timer > 40)
			{
				DrawGraph(0, 0, gametitle_text_handle[8], true);
			}if (title_ani_timer <= 40 && title_ani_timer > 30)
			{
				DrawGraph(0, 0, gametitle_text_handle[9], true);
			}if (title_ani_timer <= 30 && title_ani_timer > 20)
			{
				DrawGraph(0, 0, gametitle_text_handle[10], true);
			}if (title_ani_timer <= 20 && title_ani_timer > 10)
			{
				DrawGraph(0, 0, gametitle_text_handle[11], true);
			}if (title_ani_timer <= 10 && title_ani_timer >= 0)
			{
				DrawGraph(0, 0, gametitle_text_handle[12], true);
			}
			if (title_ani_timer <= 0)
			{
				title_ani_timer = 130;
			}

			Deviece_Draw();
			HP_draw();
			Fusion_Draw();
			player_draw();

			break;

		case 1: // 最初のステージ
			MAP_Draw();
			Deviece_Draw();
			HP_draw();
			Fusion_Draw();
			player_draw();

			break;

		case 2:
			MAP_Draw();
			Deviece_Draw();
			HP_draw();
			Fusion_Draw();
			player_draw();


			break;

		case 3:
			MAP_Draw();
			Deviece_Draw();
			HP_draw();
			Fusion_Draw();
			player_draw();

			break;
		case 4:
			MAP_Draw();
			Deviece_Draw();
			HP_draw();
			Fusion_Draw();
			player_draw();

			break;
			
		case 5:

			if (game_over_time <= 30)
			{
				DrawExtendGraph(380, 100, 1000, 228, gameover_text_handle, true);
			}
			break;

		case 6:
			if (game_clear_time <= 30)
			{
				DrawExtendGraph(380, 100, 1000, 228, gameclear_text_handle, true);
			}
		default:
			break;
		}

		//DrawFormatString(300, 300, GetColor(255, 0, 0), "jump_speed_timerは%f", jump_speed_timer);
		//DrawFormatString(300, 320, GetColor(255, 0, 0), "jump_flag は%d", jump_flag);
		//DrawFormatString(300, 340, GetColor(255, 0, 0), "R_player_pos_x は%f", right_player.pos_x);
		//DrawFormatString(300, 360, GetColor(255, 0, 0), "R_player_pos_y は%f", right_player.pos_y);
		//DrawFormatString(300, 380, GetColor(255, 0, 0), "L_player_pos_x は%f", left_player.pos_x);
		//DrawFormatString(300, 400, GetColor(255, 0, 0), "L_player_pos_y は%f", left_player.pos_y);


		/*DrawFormatString(300, 380, GetColor(255, 0, 0), "player.player_speed_x は%f", right_player.speed_x);
		DrawFormatString(300, 400, GetColor(255, 0, 0), "player.player_speed_y は%f", right_player.speed_y);*/


		/*DrawFormatString(300, 420, GetColor(255, 0, 0), "jump_speed_timer は%f", jump_speed_timer);
		DrawFormatString(300, 440, GetColor(255, 0, 0), "gravity_speed は%f", gravity_speed);
		DrawFormatString(300, 460, GetColor(255, 0, 0), "gravity_flag は%d", gravity_flag);
		DrawFormatString(300, 480, GetColor(255, 0, 0), "death_flag_R は%d", death_flag_R);
		DrawFormatString(300, 500, GetColor(255, 0, 0), "death_flag_L は%d", death_flag_L);
		DrawFormatString(300, 520, GetColor(255, 0, 0), "death_count_timer_L は%d", death_count_timer_L);*/
		/*DrawFormatString(300, 540, GetColor(255, 0, 0), "scene は%d", scene);
		DrawFormatString(100, 440, GetColor(255, 0, 0), "switch_flag[0]は%d", switch_flag[0]);
		DrawFormatString(100, 460, GetColor(255, 0, 0), "switch_flag[1]は%d", switch_flag[1]);
		DrawFormatString(100, 480, GetColor(255, 0, 0), "switch_flag[2]は%d", switch_flag[2]);
		DrawFormatString(100, 500, GetColor(255, 0, 0), "switch_flag[3]は%d", switch_flag[3]);
		DrawFormatString(100, 520, GetColor(255, 0, 0), "switch_flag[4]は%d", switch_flag[4]);
		DrawFormatString(100, 540, GetColor(255, 0, 0), "switch_razar_flagは%d", switch_razor_flag);
		DrawFormatString(100, 560, GetColor(255, 0, 0), "Get_keyは%d", Get_key);
		DrawFormatString(10, 580, GetColor(255, 0, 0), "move_change_flagは%d", move_change_flag);

		DrawFormatString(650, 200, GetColor(255, 0, 0), "hp_count[2]は%d", hp_count[2]);
		DrawFormatString(650, 220, GetColor(255, 0, 0), "death_count_timer_Rは%d", death_count_timer_R);
		DrawFormatString(650, 240, GetColor(255, 0, 0), "R_stay_timerは%d", R_stay_timer);
		DrawFormatString(650, 260, GetColor(255, 0, 0), "get_key_count は%d", get_key_count);
		DrawFormatString(650, 280, GetColor(255, 0, 0), "left_player.speed_y は%d", left_player.speed_y);
		DrawFormatString(650, 300, GetColor(255, 0, 0), "title_ani_timer  は%d", title_ani_timer);



		DrawFormatString(200, 560, GetColor(255, 255, 255), "Left_top: map[%f][%f]", (right_player.pos_x - right_player.radius) / float(block_size), (right_player.pos_y - right_player.radius) / float(block_size));
		DrawFormatString(200, 580, GetColor(255, 255, 255), "right_top: map[%f][%f]", (right_player.pos_x + right_player.radius) / float(block_size), (right_player.pos_y - right_player.radius) / float(block_size));
		DrawFormatString(200, 600, GetColor(255, 255, 255), "Left_bottom: map[%f][%f]", (right_player.pos_x - right_player.radius) / float(block_size), (right_player.pos_y + right_player.radius) / float(block_size));
		DrawFormatString(200, 620, GetColor(255, 255, 255), "right_bottom: map[%f][%f]", (right_player.pos_x + right_player.radius) / float(block_size), (right_player.pos_y + right_player.radius) / float(block_size));

		DrawFormatString(700, 560, GetColor(255, 255, 255), "L_Left_top: map[%f][%f]", (left_player.pos_x - left_player.radius) / float(block_size), (left_player.pos_y - left_player.radius) / float(block_size));
		DrawFormatString(700, 580, GetColor(255, 255, 255), "L_right_top: map[%f][%f]", (left_player.pos_x + left_player.radius) / float(block_size), (left_player.pos_y - left_player.radius) / float(block_size));
		DrawFormatString(700, 600, GetColor(255, 255, 255), "L_Left_bottom: map[%f][%f]", (left_player.pos_x - left_player.radius) / float(block_size), (left_player.pos_y + left_player.radius) / float(block_size));
		DrawFormatString(700, 620, GetColor(255, 255, 255), "L_right_bottom: map[%f][%f]", (left_player.pos_x + left_player.radius) / float(block_size), (left_player.pos_y + left_player.radius) / float(block_size));*/


		// ---------- ここまでにプログラムを記述 ---------- //
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}

	// 画像の削除
	InitGraph();
	InitSoundMem();


	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}