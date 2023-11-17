//===================================================
//プレイヤー(player.h)
//Auhor:渡邉 修	Date:2023.8.25
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define PLAYER_MAX			(1)//キャラクターの数
#define PLAYER_WIDTH		(DEFAULT_TILE_SIZE)//画像横幅
#define PLAYER_HEIGHT		(DEFAULT_TILE_SIZE)//画像縦高さ
#define PLAYER_HITBOX_WIDTH		(PLAYER_WIDTH * 0.5f)//プレイヤーのヒットボックス横
#define PLAYER_HITBOX_HEIGHT	(PLAYER_HEIGHT)//プレイヤーのヒットボックス縦
#define PLAYER_WIDTH_PATTERN	(17)//横アニメパターン数
#define PLAYER_HEIGHT_PATTERN	(4)//縦アニメパターン数
#define PLAYER_FRAME_MAX	((PLAYER_WIDTH_PATTERN * PLAYER_HEIGHT_PATTERN) -1)//フレーム数
#define PLAYER_FRAME_SPAN	(2)//アニメーションのスパン
#define PLAYER_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
#define PLAYER_SPEED		(8.0f)//プレイヤーの移動速度
#define PLAYER_INIT_HP		(3)//初期体力
#define PLAYER_UNBEATABLE_TEME (180)//無敵時間

//---------------------------------------------------
//列挙体宣言
//---------------------------------------------------
typedef enum
{
	STATE_IDLE,
	STATE_WALK,
	STATE_RISE,
	STATE_FALL
}PLAYER_STATE;

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct PLAYER {
	D3DXVECTOR2	pos;	//位置ベクトル
	D3DXVECTOR2	oldPos;	//位置ベクトル
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
	bool oldGround;

	PLAYER_STATE state; 
	PLAYER_STATE oldState;
	int animeWidthPattern;
	int animeHeightPattern;
	int animeFrameMax;

	float hp;
	float oldHp;
	bool unbeatable;
	int unbeatableCou;
	int unbeatableTime;

	int score;
	D3DXVECTOR2 notLoopPos;
	int loopTrigger;
	int coin;

	int gun;
	float maxHp;
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER* GetPlayer();

void SetPlayerGunKick(float power, float radian);
void SetPlayerKnockBack(float power, float radian);
void SetPlayer(float posX, float posY);
void SetPlayerScore(int add);
