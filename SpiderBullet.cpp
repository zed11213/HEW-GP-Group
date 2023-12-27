#include "SpiderBullet.h"
#include "Sprite.h"

void SpiderBullet::Init()
{
	_vel = D3DXVECTOR2(0, 0);
	_size = D3DXVECTOR2(40, 40);
	_pos = D3DXVECTOR2(0, 0);
	_bUse = false;
	_animePattern = 0;
	_animeWidthPattern = 2;
	_animeBasePattern = 1;
	_animeSkipFrame = 0;
	_rot =0.0f;
	_reverse = false;
	_a = _b = _c = 0;
	_color.r = _color.g = _color.b = _color.a = 1;
}

void SpiderBullet::Update()
{
	if (_bUse)
	{
		_pos += _vel;
		_pos.y = _a * pow(_pos.x, 2) + _b * _pos.x + _c;
	}
}

void SpiderBullet::Draw()
{

	if (_bUse)
	{
		_uv = SetAnimation(_animeBasePattern, _animePattern, 2, 1, _animeWidthPattern, _reverse);
		_animeSkipFrame = Counter(_animeSkipFrame, 2);

		if (_animeSkipFrame == 0)
		{
			_animePattern = Counter(_animePattern, 2);
			if (_animePattern == 0)
				_animeWidthPattern = 1;//アニメをループさせない
		}

		DrawSpriteColorRotateCamera(_texNo,
			_pos.x,
			_pos.y,
			_size.x, _size.y,	//幅、高さ
			_uv.x, _uv.y,		//中心UV座標
			1.0f / 2, 1.0f,		//テクスチャ幅、高さ
			_color.r, _color.g, _color.b, _color.a,
			_rot);
	}
}

void SpiderBullet::Uninit()
{
}
