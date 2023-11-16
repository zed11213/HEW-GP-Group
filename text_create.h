//===================================================
//テキスト(text_create.h)
//Auhor:渡邉 修	Date:2023.9.9
//===================================================
#pragma once

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define TEXT_CREATE_MAX						(30)
#define TEXT_CREATE_WIDTH					(40)//画像横幅
#define TEXT_CREATE_HEIGHT					(40)//画像縦高さ
#define TEXT_CREATE_WIDTH_PATTERN			(37)
#define TEXT_CREATE_HEIGHT_PATTERN			(1)
#define TEXT_CREATE_FRAME_MAX				(TEXT_CREATE_WIDTH_PATTERN * TEXT_CREATE_HEIGHT_PATTERN)//文字の全種類
#define TEXT_CREATE_FANFARE_TEXT_CREATE		(200)
#define TEXT_CREATE_INIT_TEXT_CREATE		(0)

//---------------------------------------------------
//列挙体宣言
//---------------------------------------------------
typedef enum
{
	TEXT_CREATE_FADE_IN,
	TEXT_CREATE_FADE_OUT,
	TEXT_CREATE_DISPLAY,
} TEXT_CREATE_STATE;

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct TEXT_CREATE {
	std::string text;
	D3DXVECTOR2	pos;	//位置ベクトル
	float blankSize;
	float scale;
	D3DXCOLOR color;	//頂点カラー
	bool use;			//使用中フラグ
	float fadeOutSpeed;
	float fadeInSpeed;
	int displayTime;
	int displayTimeCou;
	TEXT_CREATE_STATE state;
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitTextCreate();
void UninitTextCreate();
void UpdateTextCreate();
void DrawTextCreate();

void SetDrawTextCreate(
	std::string text, float posX, float posY, float blankSize = 1, float scale = 1,
	int displayTime = 0, float fadeInSpeed = 0.0f, float fadeOutSpeed = 0.0f,
	float r = 255.0f, float g = 255.0f, float b = 255.0f
);
TEXT_CREATE GetTextCreate();


