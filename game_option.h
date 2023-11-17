//===================================================
//選択項目(game_option.h)
//Auhor:渡邉 修	Date:2023.8.5
//===================================================
#pragma once
#include "main.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define GAME_OPTION_START_WIDTH		(45*8-1)//画像横幅(-1で周りに出る黒い線を消してます)
#define GAME_OPTION_START_HEIGHT	(10*8-1)//画像縦高さ
#define GAME_OPTION_EXIT_WIDTH		(37*8-1)//画像横幅
#define GAME_OPTION_EXIT_HEIGHT		(10*8-1)//画像縦高さ
#define GAME_OPTION_RETRY_WIDTH		(45*8-1)//画像横幅
#define GAME_OPTION_RETRY_HEIGHT	(10*8-1)//画像縦高さ
#define GAME_OPTION_WIDTH_PATTERN	(1)//横アニメパターン数
#define GAME_OPTION_HEIGHT_PATTERN	(1)//縦アニメパターン数
#define GAME_OPTION_MAX			(30)//キャラクターの数
#define GAME_OPTION_FRAME_MAX	((GAME_OPTION_WIDTH_PATTERN * GAME_OPTION_HEIGHT_PATTERN) -1)//フレーム数
#define GAME_OPTION_FRAME_SPAN	(15)//アニメーションのスパン
#define GAME_OPTION_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）

//---------------------------------------------------
//列挙体宣言
//---------------------------------------------------
typedef enum
{
	MESSAGE_NONE,
	MESSAGE_START,
	MESSAGE_EXIT,
	MESSAGE_RETRY,
}MESSAGE_PATTERN;

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct GAME_OPTION {
	D3DXVECTOR2		pos;	//位置ベクトル
	bool			use;	//使用中フラグ
	MESSAGE_PATTERN		messagePattern;
	D3DXCOLOR		color;	//頂点カラー
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitGameOption(void);
void UpdateGameOption(void);
void DrawGameOption(void);
void UninitGameOption(void);

D3DXVECTOR2 GetGameOptionPos(MESSAGE_PATTERN MessagePattern);
void UseGameOption(MESSAGE_PATTERN MessagePattern);
void SetGameOption(MESSAGE_PATTERN MessagePattern, D3DXVECTOR2 pos);