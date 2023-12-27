#include "EnemybulletSpawn.h"

void EnemyBulletSpawn::SetBullet(D3DXVECTOR2 startPoint, D3DXVECTOR2 targetPoint, int high,float time)
{
	for (int i = 0; i < 50; i++)
	{
		if (SBullet[i]._bUse != true)
		{
			SBullet[i]._bUse = true;
			SBullet[i]._pos = startPoint;
			D3DXVECTOR2 point1 = startPoint;
			D3DXVECTOR2 point3 = targetPoint;
			int width = point3.x - point1.x;
			D3DXVECTOR2 point2 = D3DXVECTOR2(point1.x + width/2, point1.y - high);
			//”ŠwŒöŽ®@y=ax^2+bx+c
			SBullet[i]._b = ((point1.y - point3.y) * (pow(point1.x, 2) - pow(point2.x, 2)) - (point1.y - point2.y) * (pow(point1.x, 2) - pow(point3.x, 2))) /
									((point1.x - point3.x) * (pow(point1.x, 2) - pow(point3.x, 2)) - (point1.x - point2.x) * (pow(point1.x, 2) - pow(point3.x, 2)));
			SBullet[i]._a = ((point1.y - point2.y) - SBullet[i]._b * (point1.x - point2.x)) / (pow(point1.x, 2) - pow(point3.x, 2));
			SBullet[i]._c = point1.y - SBullet[i]._a * pow(point1.x, 2) - SBullet[i]._b * point1.x;
			SBullet[i]._vel = D3DXVECTOR2(width / (time * 60), 0);
			break;
		}
	}
}
