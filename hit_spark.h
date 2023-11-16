//===================================================
//ヒットエフェクト(hit_spark.h)
//Auhor:渡邉 修	Date:2023.9.3
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define HIT_SPARK_MAX			(100)//キャラクターの数
#define HIT_SPARK_WIDTH		(DEFAULT_TILE_SIZE)//画像横幅
#define HIT_SPARK_HEIGHT	(DEFAULT_TILE_SIZE)//画像縦高さ
#define HIT_SPARK_HITBOX_WIDTH		(DEFAULT_TILE_SIZE)//ヒットエフェクトのヒットボックス横
#define HIT_SPARK_HITBOX_HEIGHT		(DEFAULT_TILE_SIZE)//ヒットエフェクトのヒットボックス縦
#define HIT_SPARK_WIDTH_PATTERN	(5)//横アニメパターン数
#define HIT_SPARK_HEIGHT_PATTERN	(1)//縦アニメパターン数
#define HIT_SPARK_FRAME_MAX	(HIT_SPARK_WIDTH_PATTERN * HIT_SPARK_HEIGHT_PATTERN)//フレーム数
#define HIT_SPARK_FRAME_SPAN	(5)//アニメーションのスパン
#define HIT_SPARK_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
#define HIT_SPARK_SPEED		(8.0f)//ヒットエフェクトの移動速度

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct HIT_SPARK {
	D3DXVECTOR2	pos;	//位置ベクトル
	D3DXCOLOR color;	//頂点カラー
	bool use;			//使用中フラグ
	D3DXVECTOR2 size;	//サイズ
	float rot;
	D3DXVECTOR2 uv;
	int animePattern;
	int animeWidthPattern;
	int animeBasePattern;
	int animeSkipFrame;
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitHitSpark(void);
void UninitHitSpark(void);
void UpdateHitSpark(void);
void DrawHitSpark(void);

HIT_SPARK* GetHitSpark();
void SetHitSpark(float posX, float posY, float rot, float r = 0.0f, float g = 0.0f, float b = 0.0f);




