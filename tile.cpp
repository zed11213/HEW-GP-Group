//===================================================
//タイル(tile.cpp)
//Auhor:渡邉 修	Date:2023.8.26
//===================================================
#include "tile.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "score.h"
#include "gun.h"
#include <list>
#include <array>
#include <vector>


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_Ground;	//背景用のテクスチャ番号
static int g_Filter;
static float g_UW;
static float g_VH;
static TILE_DATA g_Tile[MAP_SIZE_Y][MAP_SIZE_X];
static int g_SpawnTimeCou;
static int g_SpawnTime;
static int g_SpawnNum;
static int g_Wave;

MAP_DATA_T g_MapInfo[MAP_FRAME_MAX] =
{
	//左上座標とマップチップ属性の設定
	{ GetTileUV(0), MAP_ATTRIB_NONE},	//無
	{ GetTileUV(1), MAP_ATTRIB_STOP},	//地面上
	{ GetTileUV(2), MAP_ATTRIB_STOP},	//地面下
	{ GetTileUV(3), MAP_ATTRIB_STOP},	//地面右
	{ GetTileUV(4), MAP_ATTRIB_STOP},	//地面左
	{ GetTileUV(5), MAP_ATTRIB_STOP},	//塗りつぶし
	{ GetTileUV(6), MAP_ATTRIB_STOP},	//角左上
	{ GetTileUV(7), MAP_ATTRIB_STOP},	//角右上
	{ GetTileUV(8), MAP_ATTRIB_STOP},	//角左下
	{ GetTileUV(9), MAP_ATTRIB_STOP},	//角右下
	{ GetTileUV(10), MAP_ATTRIB_STOP},	//凹左上
	{ GetTileUV(11), MAP_ATTRIB_STOP},	//凹右上
	{ GetTileUV(12), MAP_ATTRIB_STOP},	//凹左下
	{ GetTileUV(13), MAP_ATTRIB_STOP},	//凹右下
	{ GetTileUV(14), MAP_ATTRIB_STOP},	//塗りつぶし
	//マップチップの種類分作成する
};

//マップデーター(1画面分)
const int P = 'P';	// プレイヤー
const int E = 'E';	// エネミー
const int 口 = 1;	// 地面上
//const int 口 = 6;	// 角左上
//const int 口 = 7;	// 角右上
//const int 口 = 10;	// 凹左上
//const int 口 = 11;	// 凹右上

std::vector<std::vector<int>> g_map =
{ {
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, //0
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, //1
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, //2
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, //3
	{{ 0, 0, P, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, //4
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, //5
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, //6
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, //7
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, //8
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, //9
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, //0
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, //1
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, //2
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, //3
} };

std::vector<std::vector<int>> g_mapS1 =
{ {
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //0
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //1
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //2
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //3
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //4
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //5
	{{口,口,口,口,口,口,口,口,口,口,口,}}, //6
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //7
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //8
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //9
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //0
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //1
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //2
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //3
} };

std::vector<std::vector<int>> g_mapS2 =
{ {
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //0
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //1
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //2
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //3
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //4
	{{ 0,口,口,口, 0, 0, 0,口,口, 0, 0,}}, //5
	{{口, 0, 0, 0,口,口,口, 0, 0,口,口,}}, //6
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //7
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //8
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //9
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //0
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //1
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //2
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //3
} };

std::vector<std::vector<int>> g_mapS3 =
{ {
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //0
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //1
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //2
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //3
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //4
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //5
	{{口,口,口,口,口,口,口,口,口,口,口,}}, //6
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //7
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //8
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //9
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //0
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //1
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //2
	{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}}, //3
} };

//int g_map[MAP_SIZE_Y][MAP_SIZE_X] =
//{ 
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //0
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //1
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //2
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //3
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //4
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //5
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //6
//	{口,口,口,口,口,口,口,口,口,口,口}, //7
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //8
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //9
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //0
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //1
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //2
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //3
//} ;


//=============================================================================
// 初期化処理
//=============================================================================
void InitTile(void)
{
	//背景テクスチャの読み込み
	g_Ground = LoadTexture((char*)"data/TEXTURE/MapChip.png");
	g_Filter = LoadTexture((char*)"data/TEXTURE/Filter.png");

	g_UW = 1.0f / MAP_WIDTH_PATTERN;
	g_VH = 1.0f / MAP_HEIGHT_PATTERN;

	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for (int j = 0; j < MAP_SIZE_X; j++)
		{
			g_Tile[i][j].attrib = MAP_ATTRIB_NONE;
			g_Tile[i][j].pos = D3DXVECTOR2(0, 0);
			g_Tile[i][j].spawn = false;

			//エンティティを配置
			//プレイヤー
			if (g_map[i][j] == P)
			{
				SetPlayer(j * MAPCHIP_SIZE, i * MAPCHIP_SIZE);
			}
			//エネミー
			if (g_map[i][j] == E)
			{
				SetEnemy(j * MAPCHIP_SIZE, i * MAPCHIP_SIZE, ENEMY_TYPE_4);
			}
		}
	}

	g_SpawnTimeCou = 0;
	g_SpawnTime = MAP_SPAWN_TIME;
	g_Wave = 0;
	g_SpawnNum = g_Wave + 1; //一回のスポーン数

	SetPlayer(0, 0);
	ChangeTile(g_map, g_mapS1, 1);
	ChangeTile(g_map, g_mapS2, 2);
	ChangeTile(g_map, g_mapS3, 3);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTile(void)
{
	
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTile(void)
{
	int ranSpawnX = -1;
	int ranSpawnY = -1;

	g_SpawnTimeCou = Counter(g_SpawnTimeCou, g_SpawnTime);
	if (g_SpawnTimeCou == 0)
	{
		ranSpawnX = GetRandomInt(0, MAP_SIZE_X - 1);
		ranSpawnY = GetRandomInt(0, MAP_SIZE_Y - 1);
	}

	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			//座標と属性を記録
			g_Tile[y][x].attrib = g_MapInfo[g_map[y][x]].attrib;
			g_Tile[y][x].pos.x = x * MAPCHIP_SIZE + (MAPCHIP_SIZE * 0.5);
			g_Tile[y][x].pos.y = y * MAPCHIP_SIZE + (MAPCHIP_SIZE * 0.5);

			//敵スポーン位置設定
			if (g_Tile[y][x].attrib == MAP_ATTRIB_STOP && g_Tile[Nat(y - 1)][x].attrib == MAP_ATTRIB_NONE)
			{
				g_Tile[Nat(y - 1)][x].spawn = true;
			}
		}
	}

	//敵スポーン設定
	int ran = 0;
	if (g_Wave != GetWave() && g_Wave != 0)
	{
		EnemyAllDelete();
	}

	g_Wave = GetWave();
	g_SpawnNum = g_Wave + 100; //一回のスポーン数;

	if (ranSpawnX > 0 || ranSpawnY > 0)
	{
		for (int i = 0; i < g_SpawnNum; i++)
		{
			if (g_Tile[ranSpawnY][ranSpawnX + i].spawn &&
				OffScreenJudge(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, MAPCHIP_SIZE, MAPCHIP_SIZE))
			{
				switch (g_Wave % 5)
				{
				case 1:
					ran = RandomPercent(0, 0, 0, 20);
					if (ran == 1)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, ENEMY_TYPE_1);
					if (ran == 2)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, ENEMY_TYPE_2);
					if (ran == 3)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, ENEMY_TYPE_3);
					if (ran == 4)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y - 1000, ENEMY_TYPE_4);
					break;

				case 2:
					ran = RandomPercent(60, 19, 1, 15);
					if (ran == 1)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, ENEMY_TYPE_1);
					if (ran == 2)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, ENEMY_TYPE_2);
					if (ran == 3)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, ENEMY_TYPE_3);
					if (ran == 4)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y - 3000, ENEMY_TYPE_4);
					break;

				case 3:
					ran = RandomPercent(40, 35, 5, 20);
					if (ran == 1)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, ENEMY_TYPE_1);
					if (ran == 2)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, ENEMY_TYPE_2);
					if (ran == 3)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, ENEMY_TYPE_3);
					if (ran == 4)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y - 3000, ENEMY_TYPE_4);
					break;

				case 4:
					ran = RandomPercent(10, 40, 10, 40);
					if (ran == 1)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, ENEMY_TYPE_1);
					if (ran == 2)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, ENEMY_TYPE_2);
					if (ran == 3)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, ENEMY_TYPE_3);
					if (ran == 4)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y - 3000, ENEMY_TYPE_4);
					break;

				case 0:
					ran = RandomPercent(0, 0, 0, 100);
					if (ran == 1)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, ENEMY_TYPE_1);
					if (ran == 2)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, ENEMY_TYPE_2);
					if (ran == 3)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y, ENEMY_TYPE_3);
					if (ran == 4)SetEnemy(g_Tile[ranSpawnY][ranSpawnX + i].pos.x, g_Tile[ranSpawnY][ranSpawnX + i].pos.y - 3000, ENEMY_TYPE_4);
					break;

				default:
					break;
				}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTile(void)
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);//テクスチャのフィルターをOFF

	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			//マップデータが0は何も表示しない
			if (g_map[y][x] != 0 && std::isalpha(g_map[y][x]) == false)//std::isalpha: アルファベットかどうか判別する
			{
				//マップ情報を取得
				MAP_DATA_T mapchip = g_MapInfo[g_map[y][x]];

				DrawSpriteCamera
				(
					g_Ground,
					(int)g_Tile[y][x].pos.x,
					(int)g_Tile[y][x].pos.y,
					MAPCHIP_SIZE, MAPCHIP_SIZE,		//幅、高さ
					mapchip.uv.x, mapchip.uv.y,		//左上UV座標
					g_UW, g_VH						//テクスチャ幅、高
				);
			}
			
			///*[デバッグ用]-------------------------------------------*/
			////マップ属性ごとに色分け表示
			//switch (g_Tile[y][x].attrib)
			//{
			//case MAP_ATTRIB_STOP:
			//	DrawSpriteColorRotateCamera
			//	(
			//		g_Filter,
			//		g_Tile[y][x].pos.x, g_Tile[y][x].pos.y,
			//		MAPCHIP_SIZE, MAPCHIP_SIZE,
			//		0.5f, 0.5f,
			//		1, 1,
			//		0, 0, 1, 0.2f,
			//		0
			//	);

			//default:
			//	break;
			//}

			//if (g_Tile[y][x].spawn)
			//{
			//	DrawSpriteColorRotateCamera
			//	(
			//		g_Filter,
			//		g_Tile[y][x].pos.x, g_Tile[y][x].pos.y,
			//		MAPCHIP_SIZE, MAPCHIP_SIZE,
			//		0.5f, 0.5f,
			//		1, 1,
			//		1, 0, 1, 0.2f,
			//		0
			//	);
			//}
			///*-------------------------------------------------------*/
		}
	}
}

//=============================================================================
// U座標をセット(引数 : 左上端を0その右隣りを1,2,3...としたときの数)
//=============================================================================
float GetTileU(int index)
{
	return ((index % MAP_WIDTH_PATTERN) * (1.0f / MAP_WIDTH_PATTERN));
}

//=============================================================================
// V座標をセット(引数 : 左上端を0その右隣りを1,2,3...としたときの数)
//=============================================================================
float GetTileV(int index)
{
	return ((index / MAP_WIDTH_PATTERN) * (1.0f / MAP_HEIGHT_PATTERN));
}

//=============================================================================
// UV座標をセット(引数 : 左上端を0その右隣りを1,2,3...としたときの数)
//=============================================================================
D3DXVECTOR2 GetTileUV(int index)
{
	D3DXVECTOR2 UV = D3DXVECTOR2(GetTileU(index), GetTileV(index));
	return UV;
}

//=============================================================================
// 座標直下のマップ情報を返す
// ０１２ 
// ３４５
// ６７８ 4が引数の座標
//=============================================================================
TILE_DATA* GetMapInfo(D3DXVECTOR2 pos)
{
	TILE_DATA* tile = new TILE_DATA[9];

	// 周囲のタイルの位置を計算
	int posX = int(pos.x / MAPCHIP_SIZE);
	int posY = int(pos.y / MAPCHIP_SIZE);

	for (int i = 0; i < 9; i++)
	{
		int offsetX = (i % 3) - 1; // 列（左から中央へのオフセット）
		int offsetY = (i / 3) - 1; // 行（上から中央へのオフセット）

		int checkX = posX + offsetX;
		int checkY = posY + offsetY;

		// 境界チェック（マップの範囲外をチェック）
		if (checkX >= 0 && checkX < MAP_SIZE_X && checkY >= 0 && checkY < MAP_SIZE_Y)
		{
			tile[i] = g_Tile[checkY][checkX];
		}
		else
		{
			// マップの範囲外の場合、デフォルト値を設定するかエラー処理を行う
			tile[i].attrib = MAP_ATTRIB_NONE;
			tile[i].pos = D3DXVECTOR2(-1, -1); // マップ外の座標を示す値など
		}
	}

	return tile;
}

//修正前
/*
//TILE_DATA* GetMapInfo(D3DXVECTOR2 pos)
//{
//	TILE_DATA tile[9];
//
//	for (int i = 0; i < 9; i++)
//	{
//		tile[i].attrib = MAP_ATTRIB_NONE;
//		tile[i].pos = D3DXVECTOR2(0, 0);
//	}
//
//	//posがタイルでどこなのか探す
//	int posX = int(pos.x / MAPCHIP_SIZE);
//	int posY = int(pos.y / MAPCHIP_SIZE);
//
//	tile[0] = g_Tile[posY - 1][posX - 1];//左上
//	tile[1] = g_Tile[posY - 1][posX];//上
//	tile[2] = g_Tile[posY - 1][posX + 1];//右上
//	tile[3] = g_Tile[posY][posX - 1];//左
//	tile[4] = g_Tile[posY][posX];//中心
//	tile[5] = g_Tile[posY][posX + 1];//右
//	tile[6] = g_Tile[posY + 1][posX - 1];//左下
//	tile[7] = g_Tile[posY + 1][posX];//下
//	tile[8] = g_Tile[posY + 1][posX + 1];//右下
//
//	return tile;
//}
*/

//=============================================================================
// 当たり判定 [戻り値] 1: 上, 3: 左, 5: 右, 7: 下
//=============================================================================
DIRECTION TileHit(D3DXVECTOR2 pos, float hsp, float vsp, float hitBoxWidth, float hitBoxHeight)
{
	TILE_DATA* tile = GetMapInfo(pos);
	DIRECTION dir = {false};

	for (int j = 0; j < 9; j++)
	{
		if (tile[j].attrib == MAP_ATTRIB_STOP)
		{
			//横に壁がある場合
			if (CollisionRot(pos.x + hsp, pos.y, tile[j].pos.x, tile[j].pos.y, hitBoxWidth, hitBoxHeight, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (j == 3) dir.left = true;
				if (j == 5) dir.right = true;
			}

			//縦に壁がある場合
			if (CollisionRot(pos.x, pos.y + vsp, tile[j].pos.x, tile[j].pos.y, hitBoxWidth, hitBoxHeight, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (j == 1) dir.up = true;
				if (j == 7) dir.down = true;
			}
		}
	}
	delete[] tile;
	return dir;
}

//=============================================================================
// マップのタイル変更 [引数] 1: 元のマップ, 2: 上書きするマップ, 3: 上書きする箇所
//=============================================================================
void ChangeTile(std::vector<std::vector<int>>& map1, std::vector<std::vector<int>> map2, int group)
{
	int startPos = map2[0].size() * (group - 1);

	for (int i = 0; i < map2.size(); i++)
	{
		for (int j = 0; j < map2[0].size(); j++)
		{
			map1[i].insert(map1[i].begin() + j + startPos, map2[i][j]);
		}
	}

}