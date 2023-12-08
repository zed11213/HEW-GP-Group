//===================================================
//弾(bullet.h)
//Auhor:渡邉 修	Date:2023.8.28
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"
#include "enemy.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define BULLET_MAX			(100)//キャラクターの数
#define BULLET_WIDTH		(40)//画像横幅
#define BULLET_HEIGHT		(40)//画像縦高さ
#define BULLET_HITBOX_WIDTH		(40 * 0.3f)//弾のヒットボックス横
#define BULLET_HITBOX_HEIGHT	(40 * 0.3f)//弾のヒットボックス縦
#define BULLET_WIDTH_PATTERN	(2)//横アニメパターン数
#define BULLET_HEIGHT_PATTERN	(1)//縦アニメパターン数
#define BULLET_FRAME_MAX	(BULLET_WIDTH_PATTERN * BULLET_HEIGHT_PATTERN)//フレーム数
#define BULLET_FRAME_SPAN	(2)//アニメーションのスパン
#define BULLET_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）

//---------------------------------------------------
//列挙体宣言
//---------------------------------------------------
typedef enum
{
	BULLET_TYPE_NORMAL = 0,
	BULLET_TYPE_MISSILE,
}BULLET_TYPE;

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct BULLET {
	int bulletType;
	D3DXVECTOR2	pos;	//位置ベクトル
	D3DXVECTOR2	oldPos;
	D3DXVECTOR2 goalPos;
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
	bool hetList[ENEMY_MAX];
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET* GetBullet();
void SetBullet(int type, float posX, float posY, float velX, float velY, float rot, float sp);
void DeleteBullet(int index);

