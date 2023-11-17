//===================================================
//タイル(tile.h)
//Auhor:渡邉 修	Date:2023.8.26
//===================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAPCHIP_SIZE (DEFAULT_TILE_SIZE) //マップチップサイズ
#define MAP_SIZE_X (64) //1マップ(1画面)横12キャラクター
#define MAP_SIZE_Y (14) //1マップ(1画面)縦7キャラクター
#define MAP_WIDTH_PATTERN (5)
#define MAP_HEIGHT_PATTERN (3)
#define MAP_FRAME_MAX (MAP_WIDTH_PATTERN * MAP_HEIGHT_PATTERN)//フレーム数
#define MAP_SPAWN_TIME (15)	//敵出現間隔
#define STAGE_SIZE  (MAP_SIZE_X * MAPCHIP_SIZE)

//*****************************************************************************
// 列挙体宣言
//*****************************************************************************
enum MAPATTRIB //マップのアトリビュート(属性)
{
	MAP_ATTRIB_NONE = 0,	//通過可能
	MAP_ATTRIB_STOP,		//進入不可
	MAP_ATTRIB_SLOW,		//速度低下
};

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
struct MAP_DATA_T //タイル種類ごとのデータ
{
	D3DXVECTOR2 uv;		//テクスチャの左上座標
	MAPATTRIB attrib;	//このマップチップが持つ属性
};

struct TILE_DATA //タイルごとのデータ
{
	D3DXVECTOR2 pos;	//中心座標
	MAPATTRIB attrib;	//このマップチップが持つ属性
	bool spawn;			//敵がこのブロック位置に湧くかどうか
};

struct POLYGON 
{
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2		vel;	//速度ベクトル
	D3DXCOLOR		color;	//頂点カラー
};

struct DIRECTION
{
	bool right;
	bool down;
	bool up;
	bool left;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTile(void);
void UninitTile(void);
void UpdateTile(void);
void DrawTile(void);
float GetTileU(int index);
float GetTileV(int index);
D3DXVECTOR2 GetTileUV(int index);
TILE_DATA* GetMapInfo(D3DXVECTOR2 pos);//座標直下のマップ情報を返す
DIRECTION TileHit(D3DXVECTOR2 pos, float hsp, float vsp, float hitBoxWidth, float hitBoxHeight);
