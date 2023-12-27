//===================================================
//ゲーム画面(game.cpp)
//Auhor:渡邉 修	Date:2023.8.4
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "game.h"
#include "dead.h"
#include "fade.h"
#include "sound.h"
#include "tile.h"
#include "camera.h"
#include "gun.h"
#include "bullet.h"
#include "hit_spark.h"
#include "back_ground.h"
#include "enemy.h"
#include "text_create.h"
#include "particle.h"
#include "minimap.h"
#include "icon.h"
#include "score.h"
#include "item.h"
#include "textDW.h"
#include "EnemyBullet.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
static int g_TILEM;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitGame()
{
	// マウスを非表示にする
	//ShowCursor(FALSE);

	char tilem[] =
	{
		"data\\TILEM\\nc296708.wav"
	};
	//g_TILEM = LoadSound(&tilem[0]);
	//PlaySound(g_TILEM, -1);
	InitPlayer();
	InitEnemy();
	InitGun();
	InitBullet();
	EnemyBulletInit();
	InitHitSpark();
	InitItem();
	InitTile();
	InitBackGround();
	InitDead();
	InitCamera();
	InitTextCreate();
	InitParticle();
	InitIcon();
	InitMinimap();
	InitScore();
	InitTextDW();
	SetFadeColor(0.0f, 0.0f, 0.0f);//なんか適当な色をセット
	SetFadeTime(240.0f);//time:何フレームでフェード処理を完了したいか？
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateGame()
{
	if (GetFadeState() == FADE_STATE_OUT)
	{
		SetFadeColor(0.0f, 0.0f, 0.0f);//なんか適当な色をセット
		SetFadeTime(30.0f);//time:何フレームでフェード処理を完了したいか？
		SetFade(FADE_STATE_IN);
	}
	UpdateCamera();
	UpdateBackGround();
	UpdateTile();
	UpdatePlayer();
	UpdateEnemy();
	UpdateGun();
	UpdateHitSpark();
	UpdateBullet();
	EnemyBulletUpdate();
	UpdateItem();
	UpdateDead();
	UpdateTextCreate();
	UpdateParticle();
	UpdateIcon();
	UpdateMinimap();
	UpdateScore();
	UpdateTextDW();
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawGame()
{
	DrawBackGroundLow();
	DrawParticle();
	DrawTile();
	DrawItem();
	DrawEnemy();
	DrawPlayer();
	DrawGun();
	DrawBullet();
	DrawHitSpark();
	DrawDead();
	DrawBackGroundHigh();
	//DrawCamera();//デバッグ用
	DrawTextCreate();
	DrawIcon();
	DrawMinimap();
	DrawScore();
	DrawTextDW();
	EnemyBulletDraw();
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitGame()
{
	UninitMinimap();
	UninitIcon();
	UninitTextCreate();
	UninitParticle();
	UninitDead();
	UninitItem();
	UninitBackGround();
	UninitTile();
	UninitHitSpark();
	EnemyBulletUnInit();
	UninitBullet();
	UninitGun();
	UninitEnemy();
	UninitPlayer();
	UninitCamera();
	UninitScore();
	UninitTextDW();
	StopSoundAll();
}
