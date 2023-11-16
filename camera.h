//===================================================
//�J����(camera.h)
//Auhor:�n� �C	Date:2023.8.27
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define CAMERA_MAX			(1)//�L�����N�^�[�̐�
#define CAMERA_WIDTH		(DEFAULT_TILE_SIZE)//�摜����
#define CAMERA_HEIGHT		(DEFAULT_TILE_SIZE)//�摜�c����
#define CAMERA_WIDTH_PATTERN	(1)//���A�j���p�^�[����
#define CAMERA_HEIGHT_PATTERN	(1)//�c�A�j���p�^�[����
#define CAMERA_FRAME_MAX	((CAMERA_WIDTH_PATTERN * CAMERA_HEIGHT_PATTERN) -1)//�t���[����
#define CAMERA_FRAME_SPAN	(8)//�A�j���[�V�����̃X�p��
#define CAMERA_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
#define CAMERA_SPEED		(8.0f)//�J�����̈ړ����x

//---------------------------------------------------
//�񋓑̐錾
//---------------------------------------------------


//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct CAMERA {
	D3DXVECTOR2	pos;	//�ʒu�x�N�g��
	D3DXVECTOR2	oldPos;	//�ʒu�x�N�g��
	D3DXVECTOR2	vel;	//���x�x�N�g��
	D3DXCOLOR color;	//���_�J���[
	bool use;			//�g�p���t���O
	D3DXVECTOR2 size;	//�T�C�Y
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
//�v���g�^�C�v�錾
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

