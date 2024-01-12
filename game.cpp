//===================================================
//�Q�[�����(game.cpp)
//Auhor:�n� �C	Date:2023.8.4
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
//�O���[�o���ϐ�
//---------------------------------------------------
static int g_TILEM;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitGame()
{
	// �}�E�X���\���ɂ���
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
<<<<<<< HEAD
	InitMinimap();
=======
	InitUI();
>>>>>>> origin/231215_tei
	InitScore();
	InitTextDW();
	SetFadeColor(0.0f, 0.0f, 0.0f);//�Ȃ񂩓K���ȐF���Z�b�g
	SetFadeTime(240.0f);//time:���t���[���Ńt�F�[�h�������������������H
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateGame()
{
	if (GetFadeState() == FADE_STATE_OUT)
	{
		SetFadeColor(0.0f, 0.0f, 0.0f);//�Ȃ񂩓K���ȐF���Z�b�g
		SetFadeTime(30.0f);//time:���t���[���Ńt�F�[�h�������������������H
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
<<<<<<< HEAD
	UpdateMinimap();
=======
	UpdateUI();
>>>>>>> origin/231215_tei
	UpdateScore();
	UpdateTextDW();
}

//---------------------------------------------------
//�`��
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
	//DrawCamera();//�f�o�b�O�p
	DrawTextCreate();
	DrawIcon();
<<<<<<< HEAD
	DrawMinimap();
=======
	DrawUI();
>>>>>>> origin/231215_tei
	DrawScore();
	DrawTextDW();
	EnemyBulletDraw();
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitGame()
{
<<<<<<< HEAD
	UninitMinimap();
=======
	UninitUI();
>>>>>>> origin/231215_tei
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
