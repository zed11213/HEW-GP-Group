#pragma once
#include"main.h"

class EnemyBullet
{
public:
	D3DXVECTOR2	_pos;		//�ʒu�x�N�g��
	D3DXVECTOR2	_vel;			//���x�x�N�g��
	D3DXVECTOR2	_size;		//�T�C�Y
	D3DXVECTOR2	_uv;			//UV
	D3DXCOLOR		_color;		//color
	bool						_bUse;		//�g�p���t���O
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
