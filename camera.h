//===================================================
//カメラ(camera.h)
//Auhor:渡邉 修	Date:2023.8.27
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define CAMERA_MAX			(1)//キャラクターの数
#define CAMERA_WIDTH		(DEFAULT_TILE_SIZE)//画像横幅
#define CAMERA_HEIGHT		(DEFAULT_TILE_SIZE)//画像縦高さ
#define CAMERA_WIDTH_PATTERN	(1)//横アニメパターン数
#define CAMERA_HEIGHT_PATTERN	(1)//縦アニメパターン数
#define CAMERA_FRAME_MAX	((CAMERA_WIDTH_PATTERN * CAMERA_HEIGHT_PATTERN) -1)//フレーム数
#define CAMERA_FRAME_SPAN	(8)//アニメーションのスパン
#define CAMERA_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
#define CAMERA_SPEED		(8.0f)//カメラの移動速度

//---------------------------------------------------
//列挙体宣言
//---------------------------------------------------


//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct CAMERA {
	D3DXVECTOR2	pos;	//位置ベクトル
	D3DXVECTOR2	oldPos;	//位置ベクトル
	D3DXVECTOR2	vel;	//速度ベクトル
	D3DXCOLOR color;	//頂点カラー
	bool use;			//使用中フラグ
	D3DXVECTOR2 size;	//サイズ
	float hsp;
	float vsp;
	D3DXVECTOR2 cameraMove;
	D3DXVECTOR2 notLoopPos;
	D3DXVECTOR2 oldNotLoopPos;
	D3DXVECTOR2 trackingDelay;
	D3DXVECTOR2 cameraTotalMove;
	int loopTrigger;
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void DrawCamera(void);

CAMERA* GetCamera();
D3DXVECTOR2 GetCameraPos(int cameraIndex = 0);
D3DXVECTOR2 GetCameraNotLoopPos(int cameraIndex = 0);
D3DXVECTOR2 GetCameraMoveVolume(int cameraIndex = 0);
D3DXVECTOR2 GetCameraMoveTotalVolume(int cameraIndex = 0);
void Shake(float shakeMagnitude, float shakeLength);

