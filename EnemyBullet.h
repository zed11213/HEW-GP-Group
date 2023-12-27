#pragma once
#include"main.h"

class EnemyBullet
{
public:
	D3DXVECTOR2	_pos;		//位置ベクトル
	D3DXVECTOR2	_vel;			//速度ベクトル
	D3DXVECTOR2	_size;		//サイズ
	D3DXVECTOR2	_uv;			//UV
	D3DXCOLOR		_color;		//color
	bool						_bUse;		//使用中フラグ
	unsigned int		_texNo;	//texture
	int						_animePattern;
	int						_animeWidthPattern;
	int						_animeBasePattern;
	int						_animeSkipFrame;
	float						_rot;
	bool						_reverse;
};

void EnemyBulletInit();
void EnemyBulletUpdate();
void EnemyBulletDraw();
void EnemyBulletUnInit();
