#include "Enemy_Spider.h"
#include "EnemybulletSpawn.h"
#include "sprite.h"

void Enemy_Spider::Dropitems()
{
}

void Enemy_Spider::Dead()
{
	_use = false;
}

void Enemy_Spider::Attack(D3DXVECTOR2 targetPos)
{
	EnemyBulletSpawn::Instance()->SetBullet(_pos, targetPos,30,0.5f);
}

void Enemy_Spider::Draw()
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_MIRROR);//テクスチャのフィルターをOFF
	D3DXVECTOR2 uv = SetAnimation( _animeBasePattern,  _animePattern, ENEMY_WIDTH_PATTERN, ENEMY_HEIGHT_PATTERN,  _animeWidthPattern,  _reverse);
	_U = uv.x;
	_V = uv.y;

	 _animeSkipFrame = Counter( _animeSkipFrame, ENEMY_FRAME_SPAN/_walksp);
	if ( _animeSkipFrame == 0)
	{
		 _animePattern = Counter( _animePattern,  _animeFrameMax);
	}

	DrawSpriteColorRotateCamera( _textureNo,
		(int) _pos.x,
		(int) _pos.y,
		_size.x,  _size.y,	//幅、高さ
		_U, _V,		//中心UV座標
		_UW, _VH,		//テクスチャ幅、高さ
		 _color.r,  _color.g,  _color.b,  _color.a,
		0.0f
	);
}

void Enemy_Spider::Update()
{
	fsm->Update();
}
