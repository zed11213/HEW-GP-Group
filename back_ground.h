//===================================================
//背景(back_ground.h)
//Auhor:渡邉 修	Date:2023.9.3
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define BACK_GROUND_MAX			(7)//キャラクターの数
#define BACK_GROUND_COPY_MAX	(5)//背景を並べる数
#define BACK_GROUND_WIDTH		(SCREEN_WIDTH * 1)//画像横幅
#define BACK_GROUND_HEIGHT		(SCREEN_HEIGHT)//画像縦高さ
#define BACK_GROUND_WIDTH_PATTERN	(1)//横アニメパターン数
#define BACK_GROUND_HEIGHT_PATTERN	(1)//縦アニメパターン数
#define BACK_GROUND_FRAME_MAX	(BACK_GROUND_WIDTH_PATTERN * BACK_GROUND_HEIGHT_PATTERN)//フレーム数
#define BACK_GROUND_FRAME_SPAN	(5)//アニメーションのスパン
#define BACK_GROUND_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
#define BACK_GROUND_SPEED		(8.0f)//背景の移動速度

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct BACK_GROUND {
	D3DXVECTOR2	pos;	//位置ベクトル
	D3DXVECTOR2	vel;	//速度ベクトル
	D3DXCOLOR color;	//頂点カラー
	bool use;			//使用中フラグ
	D3DXVECTOR2 size;	//サイズ
	float rot;
	D3DXVECTOR2 uv;
	int animePattern;
	int animeWidthPattern;
	int animeBasePattern;
	int animeSkipFrame;
	int texNo;
	float moveSp;
	float moveCou;
	bool autoScroll;
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitBackGround(void);
void UninitBackGround(void);
void UpdateBackGround(void);
void DrawBackGround(void);

BACK_GROUND* GetBackGround();
void SetBackGround(int texNo, int layer, float moveSp = 0.0f, bool autoScroll = false);


