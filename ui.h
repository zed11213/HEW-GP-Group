//===================================================
//ui(ui.h)
//Auhor:渡邉 修	Date:2023.9.11
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
class UI {
	//ICON_DATA iconData;
	//std::string name;
public:
	bool use;			//使用中フラグ

	D3DXVECTOR2	pos;	//位置ベクトル
	D3DXCOLOR color;	//頂点カラー
	D3DXVECTOR2 size;	//サイズ

	float _U = 0;
	float _V = 0;
	bool _reverse = false;
	int _animState = 0;
	int _animPattern = 0;
	int _basePattern = 0;

	int _animSkipFrame = 0;
	//int anumeFrameSpan;
	bool anime;
	float scale;
	int texture;

public:
	void ChangeAnimState(int changeTo);
	void AnimFold();
};


//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);





