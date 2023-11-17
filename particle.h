//===================================================
//粒子(particle.h)
//Auhor:渡邉 修	Date:2023.9.9
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define PARTICLE_MAX			(1000)//キャラクターの数
#define PARTICLE_WIDTH		(40)//画像横幅
#define PARTICLE_HEIGHT		(40)//画像縦高さ
#define PARTICLE_HITBOX_WIDTH		(DEFAULT_TILE_SIZE * 0.3f)//粒子のヒットボックス横
#define PARTICLE_HITBOX_HEIGHT	(DEFAULT_TILE_SIZE * 0.3f)//粒子のヒットボックス縦
#define PARTICLE_WIDTH_PATTERN	(1)//横アニメパターン数
#define PARTICLE_HEIGHT_PATTERN	(1)//縦アニメパターン数
#define PARTICLE_FRAME_MAX	(PARTICLE_WIDTH_PATTERN * PARTICLE_HEIGHT_PATTERN)//フレーム数
#define PARTICLE_FRAME_SPAN	(2)//アニメーションのスパン
#define PARTICLE_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct PARTICLE {
	D3DXVECTOR2	pos;	//位置ベクトル
	D3DXVECTOR2	vel;	//速度ベクトル
	D3DXCOLOR color;	//頂点カラー
	bool use;			//使用中フラグ
	D3DXVECTOR2 size;	//サイズ
	float rot;
	float sp;
	D3DXVECTOR2 uv;
	int animePattern;
	int animeWidthPattern;
	int animeBasePattern;
	int animeSkipFrame;
	float releaseX;
	float releaseY;
	float grv;
	D3DXVECTOR2 scale;
	D3DXCOLOR color255;
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);

PARTICLE* GetParticle();
void SetParticle(float posX, float posY, int num, float r = 172, float g = 50, float b = 50);
void SetParticleRelease(int index, float power, float radian);

