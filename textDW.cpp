//===================================================
//文字(textDW.cpp)
//Auhor:渡邉 修	Date:2023.11.1
//===================================================
#include "textDW.h"
#include "directWrite.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
DirectWrite *Write;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitTextDW(void)
{
	//フォントデータ宣言
	FontData* data = new FontData();

	//フォントデータ改変
	data->fontSize = 60;
	data->fontWeight = DWRITE_FONT_WEIGHT_BOLD;

	//DirectWrite用コンポーネントを作成
	Write = new DirectWrite(data);

	Write->Init();
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateTextDW(void)
{

}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawTextDW(void)
{
	//Write->DrawString("https://islingtonsystem.hatenablog.jp/entry/2022/06/18/222040のコードを使用しています", D2D1::RectF(300, 0, 600, 200), D2D1_DRAW_TEXT_OPTIONS_NONE);
	//Write->DrawString("https://islingtonsystem.hatenablog.jp/entry/2022/06/18/222040のコードを使用しています", D3DXVECTOR2(90, 300), D2D1_DRAW_TEXT_OPTIONS_NONE);
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitTextDW(void)
{
	Write->Release();
}

