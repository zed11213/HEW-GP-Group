//===================================================
//�^�C��(tile.cpp)
//Auhor:�n� �C	Date:2023.8.26
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
// �O���[�o���ϐ�
//*****************************************************************************
static int g_Ground;	//�w�i�p�̃e�N�X�`���ԍ�
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
	//������W�ƃ}�b�v�`�b�v�����̐ݒ�
	{ GetTileUV(0), MAP_ATTRIB_NONE},	//��
	{ GetTileUV(1), MAP_ATTRIB_STOP},	//�n�ʏ�
	{ GetTileUV(2), MAP_ATTRIB_STOP},	//�n�ʉ�
	{ GetTileUV(3), MAP_ATTRIB_STOP},	//�n�ʉE
	{ GetTileUV(4), MAP_ATTRIB_STOP},	//�n�ʍ�
	{ GetTileUV(5), MAP_ATTRIB_STOP},	//�h��Ԃ�
	{ GetTileUV(6), MAP_ATTRIB_STOP},	//�p����
	{ GetTileUV(7), MAP_ATTRIB_STOP},	//�p�E��
	{ GetTileUV(8), MAP_ATTRIB_STOP},	//�p����
	{ GetTileUV(9), MAP_ATTRIB_STOP},	//�p�E��
	{ GetTileUV(10), MAP_ATTRIB_STOP},	//������
	{ GetTileUV(11), MAP_ATTRIB_STOP},	//���E��
	{ GetTileUV(12), MAP_ATTRIB_STOP},	//������
	{ GetTileUV(13), MAP_ATTRIB_STOP},	//���E��
	{ GetTileUV(14), MAP_ATTRIB_STOP},	//�h��Ԃ�
	//�}�b�v�`�b�v�̎�ޕ��쐬����
};

//�}�b�v�f�[�^�[(1��ʕ�)
const int P = 'P';	// �v���C���[
const int E = 'E';	// �G�l�~�[
const int �� = 1;	// �n�ʏ�
//const int �� = 6;	// �p����
//const int �� = 7;	// �p�E��
//const int �� = 10;	// ������
//const int �� = 11;	// ���E��

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
	{{��,��,��,��,��,��,��,��,��,��,��,}}, //6
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
	{{ 0,��,��,��, 0, 0, 0,��,��, 0, 0,}}, //5
	{{��, 0, 0, 0,��,��,��, 0, 0,��,��,}}, //6
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
	{{��,��,��,��,��,��,��,��,��,��,��,}}, //6
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
//	{��,��,��,��,��,��,��,��,��,��,��}, //7
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //8
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //9
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //0
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //1
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //2
//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //3
//} ;


//=============================================================================
// ����������
//=============================================================================
void InitTile(void)
{
	//�w�i�e�N�X�`���̓ǂݍ���
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

			//�G���e�B�e�B��z�u
			//�v���C���[
			if (g_map[i][j] == P)
			{
				SetPlayer(j * MAPCHIP_SIZE, i * MAPCHIP_SIZE);
			}
			//�G�l�~�[
			if (g_map[i][j] == E)
			{
				SetEnemy(j * MAPCHIP_SIZE, i * MAPCHIP_SIZE, ENEMY_TYPE_4);
			}
		}
	}

	g_SpawnTimeCou = 0;
	g_SpawnTime = MAP_SPAWN_TIME;
	g_Wave = 0;
	g_SpawnNum = g_Wave + 1; //���̃X�|�[����

	SetPlayer(0, 0);
	ChangeTile(g_map, g_mapS1, 1);
	ChangeTile(g_map, g_mapS2, 2);
	ChangeTile(g_map, g_mapS3, 3);

}

//=============================================================================
// �I������
//=============================================================================
void UninitTile(void)
{
	
}

//=============================================================================
// �X�V����
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
			//���W�Ƒ������L�^
			g_Tile[y][x].attrib = g_MapInfo[g_map[y][x]].attrib;
			g_Tile[y][x].pos.x = x * MAPCHIP_SIZE + (MAPCHIP_SIZE * 0.5);
			g_Tile[y][x].pos.y = y * MAPCHIP_SIZE + (MAPCHIP_SIZE * 0.5);

			//�G�X�|�[���ʒu�ݒ�
			if (g_Tile[y][x].attrib == MAP_ATTRIB_STOP && g_Tile[Nat(y - 1)][x].attrib == MAP_ATTRIB_NONE)
			{
				g_Tile[Nat(y - 1)][x].spawn = true;
			}
		}
	}

	//�G�X�|�[���ݒ�
	int ran = 0;
	if (g_Wave != GetWave() && g_Wave != 0)
	{
		EnemyAllDelete();
	}

	g_Wave = GetWave();
	g_SpawnNum = g_Wave + 100; //���̃X�|�[����;

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
// �`�揈��
//=============================================================================
void DrawTile(void)
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);//�e�N�X�`���̃t�B���^�[��OFF

	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			//�}�b�v�f�[�^��0�͉����\�����Ȃ�
			if (g_map[y][x] != 0 && std::isalpha(g_map[y][x]) == false)//std::isalpha: �A���t�@�x�b�g���ǂ������ʂ���
			{
				//�}�b�v�����擾
				MAP_DATA_T mapchip = g_MapInfo[g_map[y][x]];

				DrawSpriteCamera
				(
					g_Ground,
					(int)g_Tile[y][x].pos.x,
					(int)g_Tile[y][x].pos.y,
					MAPCHIP_SIZE, MAPCHIP_SIZE,		//���A����
					mapchip.uv.x, mapchip.uv.y,		//����UV���W
					g_UW, g_VH						//�e�N�X�`�����A��
				);
			}
			
			///*[�f�o�b�O�p]-------------------------------------------*/
			////�}�b�v�������ƂɐF�����\��
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
// U���W���Z�b�g(���� : ����[��0���̉E�ׂ��1,2,3...�Ƃ����Ƃ��̐�)
//=============================================================================
float GetTileU(int index)
{
	return ((index % MAP_WIDTH_PATTERN) * (1.0f / MAP_WIDTH_PATTERN));
}

//=============================================================================
// V���W���Z�b�g(���� : ����[��0���̉E�ׂ��1,2,3...�Ƃ����Ƃ��̐�)
//=============================================================================
float GetTileV(int index)
{
	return ((index / MAP_WIDTH_PATTERN) * (1.0f / MAP_HEIGHT_PATTERN));
}

//=============================================================================
// UV���W���Z�b�g(���� : ����[��0���̉E�ׂ��1,2,3...�Ƃ����Ƃ��̐�)
//=============================================================================
D3DXVECTOR2 GetTileUV(int index)
{
	D3DXVECTOR2 UV = D3DXVECTOR2(GetTileU(index), GetTileV(index));
	return UV;
}

//=============================================================================
// ���W�����̃}�b�v����Ԃ�
// �O�P�Q 
// �R�S�T
// �U�V�W 4�������̍��W
//=============================================================================
TILE_DATA* GetMapInfo(D3DXVECTOR2 pos)
{
	TILE_DATA* tile = new TILE_DATA[9];

	// ���͂̃^�C���̈ʒu���v�Z
	int posX = int(pos.x / MAPCHIP_SIZE);
	int posY = int(pos.y / MAPCHIP_SIZE);

	for (int i = 0; i < 9; i++)
	{
		int offsetX = (i % 3) - 1; // ��i�����璆���ւ̃I�t�Z�b�g�j
		int offsetY = (i / 3) - 1; // �s�i�ォ�璆���ւ̃I�t�Z�b�g�j

		int checkX = posX + offsetX;
		int checkY = posY + offsetY;

		// ���E�`�F�b�N�i�}�b�v�͈̔͊O���`�F�b�N�j
		if (checkX >= 0 && checkX < MAP_SIZE_X && checkY >= 0 && checkY < MAP_SIZE_Y)
		{
			tile[i] = g_Tile[checkY][checkX];
		}
		else
		{
			// �}�b�v�͈̔͊O�̏ꍇ�A�f�t�H���g�l��ݒ肷�邩�G���[�������s��
			tile[i].attrib = MAP_ATTRIB_NONE;
			tile[i].pos = D3DXVECTOR2(-1, -1); // �}�b�v�O�̍��W�������l�Ȃ�
		}
	}

	return tile;
}

//�C���O
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
//	//pos���^�C���łǂ��Ȃ̂��T��
//	int posX = int(pos.x / MAPCHIP_SIZE);
//	int posY = int(pos.y / MAPCHIP_SIZE);
//
//	tile[0] = g_Tile[posY - 1][posX - 1];//����
//	tile[1] = g_Tile[posY - 1][posX];//��
//	tile[2] = g_Tile[posY - 1][posX + 1];//�E��
//	tile[3] = g_Tile[posY][posX - 1];//��
//	tile[4] = g_Tile[posY][posX];//���S
//	tile[5] = g_Tile[posY][posX + 1];//�E
//	tile[6] = g_Tile[posY + 1][posX - 1];//����
//	tile[7] = g_Tile[posY + 1][posX];//��
//	tile[8] = g_Tile[posY + 1][posX + 1];//�E��
//
//	return tile;
//}
*/

//=============================================================================
// �����蔻�� [�߂�l] 1: ��, 3: ��, 5: �E, 7: ��
//=============================================================================
DIRECTION TileHit(D3DXVECTOR2 pos, float hsp, float vsp, float hitBoxWidth, float hitBoxHeight)
{
	TILE_DATA* tile = GetMapInfo(pos);
	DIRECTION dir = {false};

	for (int j = 0; j < 9; j++)
	{
		if (tile[j].attrib == MAP_ATTRIB_STOP)
		{
			//���ɕǂ�����ꍇ
			if (CollisionRot(pos.x + hsp, pos.y, tile[j].pos.x, tile[j].pos.y, hitBoxWidth, hitBoxHeight, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (j == 3) dir.left = true;
				if (j == 5) dir.right = true;
			}

			//�c�ɕǂ�����ꍇ
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
// �}�b�v�̃^�C���ύX [����] 1: ���̃}�b�v, 2: �㏑������}�b�v, 3: �㏑������ӏ�
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