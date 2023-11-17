//===================================================
//カーソル(cursor.h)
//Auhor:渡邉 修	Date:2023.8.5
//===================================================
#pragma once
#include "main.h"
#include "game_option.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define CURSOR_WIDTH		(32*5)//画像横幅
#define CURSOR_HEIGHT		(32*5)//画像縦高さ
#define CURSOR_WIDTH_PATTERN	(1)//横アニメパターン数
#define CURSOR_HEIGHT_PATTERN	(1)//縦アニメパターン数
#define CURSOR_MAX			(1)//キャラクターの数
#define CURSOR_FRAME_MAX	((CURSOR_WIDTH_PATTERN * CURSOR_HEIGHT_PATTERN) -1)//フレーム数
#define CURSOR_FRAME_SPAN	(15)//アニメーションのスパン
#define CURSOR_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
#define CURSOR_SPACE	(80)//左右のカーソルの幅

//---------------------------------------------------
//列挙体宣言
//---------------------------------------------------
typedef enum
{
	TITLE_START,
	TITLE_EXIT,
}TITLE_CURSOR;

typedef enum
{
	RESULT_RETRY,
	RESULT_EXIT,
}RESULT_CURSOR;

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitCursor(void);
void UpdateCursor(void);
void DrawCursor(void);
void UninitCursor(void);
void SelectFlash(MESSAGE_PATTERN MessagePattern, SCENE Scene);