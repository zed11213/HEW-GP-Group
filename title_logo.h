//===================================================
//タイトルロゴ(title_logo.h)
//Auhor:渡邉 修	Date:2023.8.5
//===================================================
#pragma once

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define TITLE_LOGO_WIDTH		(220*8)//画像横幅
#define TITLE_LOGO_HEIGHT		(48*8)//画像縦高さ
#define TITLE_LOGO_WIDTH_PATTERN	(2)//横アニメパターン数
#define TITLE_LOGO_HEIGHT_PATTERN	(5)//縦アニメパターン数
#define TITLE_LOGO_MAX			(1)//キャラクターの数
#define TITLE_LOGO_FRAME_MAX	((TITLE_LOGO_WIDTH_PATTERN * TITLE_LOGO_HEIGHT_PATTERN) -1)//フレーム数
#define TITLE_LOGO_FRAME_SPAN	(8)//アニメーションのスパン
#define TITLE_LOGO_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitTitleLogo(void);
void UpdateTitleLogo(void);
void DrawTitleLogo(void);
void UninitTitleLogo(void);
