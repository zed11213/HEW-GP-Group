//===================================================
//死体(dead.h)
//Auhor:渡邉 修	Date:2023.8.1
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define DEAD_WIDTH		(27 * 4)//画像横幅(元画像27ピクセルの画像を4倍にして使用)
#define DEAD_HEIGHT		(27 * 4)//画像縦高さ
#define DEAD_WIDTH_PATTERN	(4)//横アニメパターン数
#define DEAD_HEIGHT_PATTERN	(1)//縦アニメパターン数
#define DEAD_MAX			(1)//キャラクターの数
#define DEAD_FRAME_MAX	((DEAD_WIDTH_PATTERN * DEAD_HEIGHT_PATTERN) -1)//フレーム数
#define DEAD_FRAME_SPAN	(5)//アニメーションのスパン
#define DEAD_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
#define DEAD_SPEED		(1.0f)//死体の移動速度
#define DEAD_WIDTH_MAX	(DEAD_WIDTH * 4)
#define DEAD_HEIGHT_MAX	(DEAD_HEIGHT * 4)
#define DEAD_BASE_ZOOM_RATE	(0.01f)	//基本の手前に来る速さ
#define DEAD_ADD_ZOOM_RATE	(8.5f)	//手前に来た時の速さの増加率
#define DEAD_DIS_SPEED_RATE	(10)	//距離によるスピードの増減

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct DEAD {
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2		oldPos;	//前フレームの位置ベクトル
	D3DXVECTOR2		vel;	//速度ベクトル
	D3DXCOLOR		color;	//頂点カラー
	int				dir;	//向き
	bool			use;	//使用中フラグ
	D3DXVECTOR2		size;	//サイズ
	float			dis;	//遠近距離
	int				BufferIndex;//リングバッファの参照インデクス
	D3DXVECTOR2		initSize;	//初期サイズ
	float			disRate;	//0(最奥)～1(最前)
	float			speed;
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitDead(void);
void UninitDead(void);
void UpdateDead(void);
void DrawDead(void);

DEAD* GetDead();
void SetDead(D3DXVECTOR2 pos);
