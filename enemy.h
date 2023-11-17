//===================================================
//エネミー(enemy.h)
//Auhor:渡邉 修	Date:2023.9.4
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define ENEMY_MAX			(1000)//キャラクターの数
#define ENEMY_WIDTH		(DEFAULT_TILE_SIZE)//画像横幅
#define ENEMY_HEIGHT		(DEFAULT_TILE_SIZE)//画像縦高さ
#define ENEMY_HITBOX_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//エネミーのヒットボックス横
#define ENEMY_HITBOX_HEIGHT	(DEFAULT_TILE_SIZE)//エネミーのヒットボックス縦
#define ENEMY_WIDTH_PATTERN	(4)//横アニメパターン数
#define ENEMY_HEIGHT_PATTERN	(5)//縦アニメパターン数
#define ENEMY_FRAME_MAX	((ENEMY_WIDTH_PATTERN * ENEMY_HEIGHT_PATTERN) -1)//フレーム数
#define ENEMY_FRAME_SPAN	(8)//アニメーションのスパン
#define ENEMY_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
#define ENEMY_SPEED		(8.0f)//エネミーの移動速度
#define ENEMY_UNBEATABLE_TEME (20)//無敵時間

//---------------------------------------------------
//列挙体宣言
//---------------------------------------------------
typedef enum
{
	ENEMY_STATE_IDLE,
	ENEMY_STATE_WALK,
	ENEMY_STATE_RISE,
	ENEMY_STATE_FALL,
	ENEMY_STATE_DEAD
}ENEMY_STATE;

typedef enum
{
	ENEMY_TYPE_1,
	ENEMY_TYPE_2,
	ENEMY_TYPE_3,
}ENEMY_TYPE;

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct ENEMY {
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
	bool oldGround;

	ENEMY_STATE state;
	ENEMY_STATE oldState;
	int animeWidthPattern;
	int animeHeightPattern;
	int animeFrameMax;
	int animeBasePattern;
	int animePattern;
	int animeSkipFrame;

	bool leftMove;
	bool rightMove;
	bool jump;
	int move;
	int stateCou;
	bool reverse;

	int hp;
	int oldHp;
	bool unbeatable;
	int unbeatableTime;
	int unbeatableCou;

	int score;
	ENEMY_TYPE type;
	int textureNo;
	int jumpPower;
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY* GetEnemy();
void SetEnemyGunKick(int index, float power, float radian);
void SetEnemyKnockBack(int index, float power, float radian);
void SetEnemy(float posX, float posY, ENEMY_TYPE type);
void EnemyAllDelete();
void EnemyHpDown(int index, int damage);