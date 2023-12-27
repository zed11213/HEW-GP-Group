//===================================================
//僄僱儈乕(enemy.h)
//Auhor:搉绯 廋	Date:2023.9.4
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"
#include "tile.h"


//---------------------------------------------------
//儅僋儘掕媊
//---------------------------------------------------
#define ENEMY_MAX			(50)//僉儍儔僋僞乕偺悢
#define ENEMY_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//夋憸墶暆
#define ENEMY_HEIGHT		(DEFAULT_TILE_SIZE * 0.5f)//夋憸廲崅偝
#define ENEMY_HITBOX_WIDTH		(80)//僄僱儈乕偺僸僢僩儃僢僋僗墶
#define ENEMY_HITBOX_HEIGHT	(80)//僄僱儈乕偺僸僢僩儃僢僋僗廲
#define ENEMY_WIDTH_PATTERN	(4)//墶傾僯儊僷僞乕儞悢
#define ENEMY_HEIGHT_PATTERN	(5)//廲傾僯儊僷僞乕儞悢
#define ENEMY_SPEED		(1.0f)//僄僱儈乕偺堏摦懍搙
#define ENEMY_FRAME_MAX	((ENEMY_WIDTH_PATTERN * ENEMY_HEIGHT_PATTERN) -1)//僼儗乕儉悢
#define ENEMY_FRAME_SPAN	(16)//傾僯儊乕僔儑儞偺僗僷儞
#define ENEMY_FOLLOW_SPAN	(5)//僉儍儔僋僞乕娫偺娫妘乮僼儗乕儉乯
#define ENEMY_UNBEATABLE_TEME (20)//柍揋帪娫

//---------------------------------------------------
//楍嫇懱愰尵
//---------------------------------------------------
typedef enum
{
	ENEMY_STATE_IDLE,
	ENEMY_STATE_WALK,
	ENEMY_STATE_RISE,
	ENEMY_STATE_FALL,
	ENEMY_STATE_DEAD
}_ENEMY_STATE;

typedef enum
{
	ENEMY_TYPE_1,
	ENEMY_TYPE_2,
	ENEMY_TYPE_3,
	ENEMY_TYPE_4,
}ENEMY_TYPE;

//---------------------------------------------------
//峔憿懱愰尵
//---------------------------------------------------
class FSMBase;
class Enemy 
{
public:
	Enemy() { ; }
	virtual ~Enemy() { ; }
	D3DXVECTOR2	_pos;	//埵抲儀僋僩儖
	D3DXVECTOR2	_vel;	//懍搙儀僋僩儖
	D3DXCOLOR _color;	//捀揰僇儔乕
	bool _use;			//巊梡拞僼儔僌
	D3DXVECTOR2 _size;	//僒僀僘
	
	float _hsp;
	float _vsp;
	float _grv;
	float _walksp;
	float _controller;
	bool _hascontrol;
	float _canjump;
	float _knockBackX;
	float _knockBackY;
	bool _ground;
	bool _oldGround;

	bool _leftMove;
	bool _rightMove;
	bool _jump;
	int _move;
	int _stateCou;
	bool _reverse;

	int _hp;
	int _oldHp;
	bool _unbeatable;
	int _unbeatableTime;
	int _unbeatableCou;

	int _score;
	int _textureNo;
	int _jumpPower;
	TILE_DATA* _Tile;
	//anime
	int _animeWidthPattern;
	int _animeHeightPattern;
	int _animeFrameMax;
	int _animeBasePattern;
	int _animePattern;
	int _animeSkipFrame;
	float _U;
	float _V;
	float _UW;
	float _VH;
	int _AnimePattern;
	FSMBase* fsm;

	void Init()
	{
		_use = false;
		_pos.x = SCREEN_WIDTH / 2;
		_pos.y = SCREEN_HEIGHT / 4;
		_vel.x = ENEMY_SPEED;
		_vel.y = ENEMY_SPEED;
		//儀僋僩儖偺惓婯壔
		D3DXVec2Normalize(&_vel, &_vel);
		_vel *= ENEMY_SPEED;//栚揑偺僗僺乕僪偵偡傞偨傔偵僗僺乕僪傪忔嶼偡傞
		_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		_hsp = 0;
		_vsp = 0;
		_grv = 0.3f;
		_walksp = 1.0f;
		_controller = true;
		_hascontrol = false;
		_canjump = 0;
		_knockBackX = 0;
		_knockBackY = 0;
		_ground = false;
		_animeWidthPattern = 4;
		_animeHeightPattern = 5;
		_animeFrameMax = 0;
		_size = D3DXVECTOR2(ENEMY_WIDTH, ENEMY_HEIGHT);
		_leftMove = false;
		_rightMove = false;
		_jump = false;
		_move = 0;
		_stateCou = 0;
		_animeBasePattern = 0;
		_animePattern = 0;
		_animeSkipFrame = 0;
		_reverse = true;
		_hp = 10;
		_oldHp = 0;
		_unbeatable = false;
		_unbeatableTime = ENEMY_UNBEATABLE_TEME;
		_unbeatableCou = 0;
		_score = 0;
		_textureNo = 0;
		_jumpPower = -15;
		_oldGround = false;
		_U = 0.0f;
		_V = 0.0f;
		_UW = 1.0f / ENEMY_WIDTH_PATTERN;
		_VH = 1.0f / ENEMY_HEIGHT_PATTERN;
		_AnimePattern = 0;
	}
	void virtual Dropitems()=0;
	void virtual Dead() = 0;
	void virtual Update()=0;
	void virtual Attack(D3DXVECTOR2 targetPos) = 0;
	void virtual Draw() = 0;
};

//---------------------------------------------------
//僾儘僩僞僀僾愰尵
//---------------------------------------------------
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

Enemy* GetEnemy();
void SetEnemyGunKick(int index, float power, float radian);
void SetEnemyKnockBack(int index, float power, float radian);
void SetEnemy(float posX, float posY);
void EnemyAllDelete();
void EnemyHpDown(int index, int damage);