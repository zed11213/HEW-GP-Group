//===================================================
//ミニマップ表示	(minimap.h)
//Author:名倉 彪		Date:2023/12/15
//===================================================
#pragma once

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define MINIMAP_MAX					(100)
#define MINIMAP_WIDTH				(80)//画像横幅
#define MINIMAP_HEIGHT				(80)//画像縦高さ
#define MINIMAP_MAP_WIDTH			(40)//配置指定間隔幅
#define MINIMAP_MAP_HEIGHT			(40)//配置指定間隔高さ
#define MINIMAP_WIDTH_PATTERN		(2)
#define MINIMAP_HEIGHT_PATTERN		(3)
#define MINIMAP_FRAME_MAX			(10)//文字の全種類
#define MINIMAP_SCREEN_SIZE_X		(49)
#define MINIMAP_SCREEN_SIZE_Y		(27)

//---------------------------------------------------
// 列挙体宣言
//---------------------------------------------------
enum MINIMAP_ATTRIB
{
	MINIMAP_NONE = 0,
	MINIMAP_ADLE,
	MINIMAP_TURN_RIGHT,
	MINIMAP_TURN_LEFT
};

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct MINIMAP_DATA
{
	MINIMAP_ATTRIB attrib;
	int animeBasePattern;
	int animeWidthPattern;
	int animeHeightPattern;
	int animeFrameMax;
	int texture;
};

struct MINIMAP {
	MINIMAP_DATA minimapData;
	std::string name;
	D3DXVECTOR2	pos;	//位置ベクトル
	D3DXCOLOR color;	//頂点カラー
	bool use;			//使用中フラグ
	D3DXVECTOR2 size;	//サイズ

	int animePattern;
	int animeSkipFrame;
	int anumeFrameSpan;
	bool anime;
	float scale;
	int texture;
};
//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitMinimap(void);
void UninitMinimap(void);
void UpdateMinimap(void);
void DrawMinimap(void);
void SetMinimapData(MINIMAP_DATA data, std::string name, int texture, float posX, float posY, float sizeX = MINIMAP_WIDTH, float sizeY = MINIMAP_HEIGHT, bool anime = false, int frameSpan = 60);
void ChangeMinimap(std::string name, MINIMAP_DATA iconData, bool anime, int frameSpan = 60);
float GetMinimapU(int index);
float GetMinimapV(int index);
D3DXVECTOR2 GetMinimapUV(int index);





