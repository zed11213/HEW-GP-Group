//===================================================
//タイトルトマト(title_tomato.h)
//Auhor:渡邉 修	Date:2023.8.5
//===================================================
#pragma once
#include "main.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define TITLE_TOMATO_WIDTH		(600*1.5)//画像横幅
#define TITLE_TOMATO_HEIGHT		(600*1.5)//画像縦高さ
#define TITLE_TOMATO_WIDTH_PATTERN	(11)//横アニメパターン数
#define TITLE_TOMATO_HEIGHT_PATTERN	(1)//縦アニメパターン数
#define TITLE_TOMATO_MAX			(1)//キャラクターの数
#define TITLE_TOMATO_FRAME_MAX	((TITLE_TOMATO_WIDTH_PATTERN * TITLE_TOMATO_HEIGHT_PATTERN) -1)//フレーム数
#define TITLE_TOMATO_FRAME_SPAN	(15)//アニメーションのスパン
#define TITLE_TOMATO_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitTitleTomato(void);
void UpdateTitleTomato(void);
void DrawTitleTomato(void);
void UninitTitleTomato(void);
