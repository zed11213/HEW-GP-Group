//===================================================
//アイテム(item.h)
//Auhor:渡邉 修	Date:2023.9.15
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"
#include "gun.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define ITEM_MAX			(100)//キャラクターの数
#define ITEM_WIDTH		(DEFAULT_TILE_SIZE)//画像横幅
#define ITEM_HEIGHT		(DEFAULT_TILE_SIZE)//画像縦高さ
#define ITEM_HITBOX_WIDTH	(DEFAULT_TILE_SIZE * 0.5f)//アイテムのヒットボックス横
#define ITEM_HITBOX_HEIGHT	(DEFAULT_TILE_SIZE)//アイテムのヒットボックス縦
#define ITEM_WIDTH_PATTERN	(14)//横アニメパターン数
#define ITEM_HEIGHT_PATTERN	(6)//縦アニメパターン数
#define ITEM_FRAME_MAX	((ITEM_WIDTH_PATTERN * ITEM_HEIGHT_PATTERN) -1)//フレーム数
#define ITEM_FRAME_SPAN	(5)//アニメーションのスパン
#define ITEM_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）

//---------------------------------------------------
//列挙体宣言
//---------------------------------------------------
typedef enum
{
	ITEM_STATE_IDLE,
	ITEM_STATE_WALK,
	ITEM_STATE_RISE,
	ITEM_STATE_FALL,
	ITEM_STATE_DEAD
}ITEM_STATE;

typedef enum
{
	ITEM_TYPE_COIN,
	ITEM_TYPE_TMATO,
	ITEM_TYPE_TREASURE_BOX,
	ITEM_TYPE_WEAPON,
}ITEM_TYPE;

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct ITEM {
	D3DXVECTOR2	pos;	//位置ベクトル
	D3DXVECTOR2	vel;	//速度ベクトル
	D3DXCOLOR color;	//頂点カラー
	bool use;			//使用中フラグ
	D3DXVECTOR2 size;	//サイズ

	float hsp;
	float vsp;
	float grv;
	float walksp;
	float controller;
	bool hascontrol;
	float canjump;
	float knockBackX;
	float knockBackY;
	bool ground;

	ITEM_STATE state;
	ITEM_STATE oldState;
	int animeWidthPattern;
	int animeHeightPattern;
	int animeFrameMax;
	int animeBasePattern;
	int animePattern;
	int animeSkipFrame;
	bool anime;

	bool leftMove;
	bool rightMove;
	bool jump;
	int move;
	int stateCou;
	bool reverse;

	ITEM_TYPE type;
	bool animeLoop;
	GUN_TYPE gunType;
	bool fadeOut;
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

ITEM* GetItem();
void SetItemGunKick(int index, float power);
void SetItemKnockBack(int index, float power);
int SetItem(float posX, float posY, ITEM_TYPE type);
void SetWeapon(float posX, float posY, GUN_TYPE type);
void ItemAnime(int index);
void ItemFadeOut(int index);
void ItemAllDelete();
