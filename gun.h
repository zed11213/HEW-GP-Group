//===================================================
//銃(gun.h)
//Auhor:渡邉 修	Date:2023.8.27
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define GUN_MAX			(1)//キャラクターの数
#define GUN_WIDTH		(DEFAULT_TILE_SIZE*0.5)//画像横幅
#define GUN_HEIGHT		(DEFAULT_TILE_SIZE*0.5)//画像縦高さ
#define GUN_WIDTH_PATTERN	(3)//横アニメパターン数
#define GUN_HEIGHT_PATTERN	(1)//縦アニメパターン数
#define GUN_FRAME_MAX	((GUN_WIDTH_PATTERN * GUN_HEIGHT_PATTERN) -1)//フレーム数
#define GUN_FRAME_SPAN	(1)//アニメーションのスパン
#define GUN_SHOT_DELAY	(1)
#define GUN_BULLET_OFFSET (30)

//---------------------------------------------------
//列挙体宣言
//---------------------------------------------------
typedef enum
{
	GUN_TYPE_INIT,
	GUN_TYPE_FULL_AUTO,
	GUN_TYPE_SEMI_AUTO,
	GUN_TYPE_CHARGE_FULL_AUTO,
}GUN_TYPE;

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct GUN {
	int type;
	int oldType;
	D3DXVECTOR2	pos;	//位置ベクトル
	D3DXCOLOR color;	//頂点カラー
	bool use;			//使用中フラグ
	D3DXVECTOR2 size;	//サイズ
	float rot;
	int firingDelay;
	int recoil;
	int controlleRangle;
	int animeWidthPattern;
	int animeHeightPattern;
	int animeBasePattern;
	int animePattern;
	bool anime;
	int shotDelay;
	int shotCou;
	int charge;
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitGun(void);
void UninitGun(void);
void UpdateGun(void);
void DrawGun(void);

GUN* GetGun();
void ChangeGun(int type);