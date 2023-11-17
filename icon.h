//===================================================
//アイコン(icon.h)
//Auhor:渡邉 修	Date:2023.9.11
//===================================================
#pragma once

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define ICON_MAX					(100)
#define ICON_WIDTH					(80)//画像横幅
#define ICON_HEIGHT					(80)//画像縦高さ
#define ICON_MAP_WIDTH				(40)//配置指定間隔幅
#define ICON_MAP_HEIGHT				(40)//配置指定間隔高さ
#define ICON_WIDTH_PATTERN			(2)
#define ICON_HEIGHT_PATTERN			(3)
#define ICON_FRAME_MAX				(ICON_WIDTH_PATTERN * ICON_HEIGHT_PATTERN)//文字の全種類
#define ICON_FANFARE_ICON			(200)
#define ICON_INIT_ICON				(0)
#define ICON_SCREEN_SIZE_X			(49)
#define ICON_SCREEN_SIZE_Y			(27)

//---------------------------------------------------
// 列挙体宣言
//---------------------------------------------------
enum ICON_ATTRIB
{
	ICON_NONE = 0,
	ICON_HEART,	//ハート
	ICON_COIN //コイン
};

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct ICON_DATA
{
	ICON_ATTRIB attrib;
	int animeBasePattern;
	int animeWidthPattern;
	int animeHeightPattern;
	int animeFrameMax;
};

struct ICON {
	ICON_DATA iconData;
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
};
//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitIcon();
void UninitIcon();
void UpdateIcon();
void DrawIcon();
void SetIconData(ICON_DATA data, std::string name, float posX, float posY, bool anime);
void ChangeIcon(std::string name, ICON_DATA iconData, bool anime);
float GetIconU(int index);
float GetIconV(int index);
D3DXVECTOR2 GetIconUV(int index);


