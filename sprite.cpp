//=============================================================================
//
// �X�v���C�g���� [sprite.cpp]
// Author : 
//
//=============================================================================
#include "sprite.h"
#include "renderer.h"
#include "texture.h"
#include "camera.h"
#include "tile.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_VERTEX 4	//�K�v�Ȓ��_�̐�


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;	// ���_���


//=============================================================================
// ����������
//=============================================================================
void InitSprite(void)
{
	ID3D11Device *pDevice = GetDevice();

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pDevice->CreateBuffer(&bd, NULL, &g_VertexBuffer);
}

//=============================================================================
// �I������
//=============================================================================
void UninitSprite(void)
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̒��S�_�j
//Y		: Y���W�i�X�v���C�g�̒��S�_�j
//Width : ����
//Height: ����
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
void DrawSprite(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(X - hw, Y - hh, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(X + hw, Y - hh, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(X - hw, Y + hh, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(X + hw, Y + hh, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// �J�����ɒǏ]����X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̒��S�_�j
//Y		: Y���W�i�X�v���C�g�̒��S�_�j
//Width : ����
//Height: ����
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
void DrawSpriteCamera(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	D3DXVECTOR2 cameraMove = GetCameraMoveVolume();

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	D3DXVECTOR2 pcr;
	pcr = PosCameraRevision(X, Y);

	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(pcr.x - hw, pcr.y - hh, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(pcr.x + hw, pcr.y - hh, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(pcr.x - hw, pcr.y + hh, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(pcr.x + hw, pcr.y + hh, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�i����w��j
// ���W�E�T�C�Y�EUV�w��
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̍���j
//Y		: Y���W�i�X�v���C�g�̍���j
//Width : ����
//Height: ����
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
void DrawSpriteLeftTop(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	// ��������_�Ƃ��Đݒ肷��v���O����
	vertex[0].Position = D3DXVECTOR3(X, Y, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	vertex[1].Position = D3DXVECTOR3(X + Width, Y, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	vertex[2].Position = D3DXVECTOR3(X, Y + Height, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	vertex[3].Position = D3DXVECTOR3(X + Width, Y + Height, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// �J�����ɒǏ]����X�v���C�g�f�[�^�ݒ�i����w��j
// ���W�E�T�C�Y�EUV�w��
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̍���j
//Y		: Y���W�i�X�v���C�g�̍���j
//Width : ����
//Height: ����
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
void DrawSpriteLeftTopCamera(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	D3DXVECTOR2 pcr;
	pcr = PosCameraRevision(X, Y);

	// ��������_�Ƃ��Đݒ肷��v���O����
	vertex[0].Position = D3DXVECTOR3(pcr.x, pcr.y, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	vertex[1].Position = D3DXVECTOR3(pcr.x + Width, pcr.y, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	vertex[2].Position = D3DXVECTOR3(pcr.x, pcr.y + Height, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	vertex[3].Position = D3DXVECTOR3(pcr.x + Width, pcr.y + Height, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̒��S�_�j
//Y		: Y���W�i�X�v���C�g�̒��S�_�j
//Width : ����
//Height: ����
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
//color : ���_�̐F�iRGBA�j
void DrawSpriteColor(int texNo, float X, float Y, float Width, float Height,
		float U, float V, float UW, float VH,
		float r, float g, float b, float a)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	D3DXCOLOR Color(r, g, b, a);
	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(X - hw, Y - hh, 0.0f);
	vertex[0].Diffuse = Color;
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(X + hw, Y - hh, 0.0f);
	vertex[1].Diffuse = Color;
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(X - hw, Y + hh, 0.0f);
	vertex[2].Diffuse = Color;
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(X + hw, Y + hh, 0.0f);
	vertex[3].Diffuse = Color;
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}


//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F�E��]�p�x
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̒��S�_�j
//Y		: Y���W�i�X�v���C�g�̒��S�_�j
//Width : ����
//Height: ����
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
//color : ���_�̐F�iRGBA�j
//Rot	: ��]�p�x�i���W�A���l�j
void DrawSpriteColorRotate(int texNo, float X, float Y, float Width, float Height,
	float U, float V, float UW, float VH,
	float r, float g, float b, float a, float Rot)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	// ���W�ϊ�
	vertex[0].Position.x = (-hw) * cosf(Rot) - (-hh) * sinf(Rot) + X;
	vertex[0].Position.y = (-hw) * sinf(Rot) + (-hh) * cosf(Rot) + Y;
	vertex[1].Position.x = ( hw) * cosf(Rot) - (-hh) * sinf(Rot) + X;
	vertex[1].Position.y = ( hw) * sinf(Rot) + (-hh) * cosf(Rot) + Y;
	vertex[2].Position.x = (-hw) * cosf(Rot) - ( hh) * sinf(Rot) + X;
	vertex[2].Position.y = (-hw) * sinf(Rot) + ( hh) * cosf(Rot) + Y;
	vertex[3].Position.x = ( hw) * cosf(Rot) - ( hh) * sinf(Rot) + X;
	vertex[3].Position.y = ( hw) * sinf(Rot) + ( hh) * cosf(Rot) + Y;

	D3DXCOLOR Color(r, g, b, a);
	vertex[0].Diffuse = Color;
	vertex[1].Diffuse = Color;
	vertex[2].Diffuse = Color;
	vertex[3].Diffuse = Color;

	vertex[0].TexCoord = D3DXVECTOR2(U, V);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// REVERSE
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̒��S�_�j
//Y		: Y���W�i�X�v���C�g�̒��S�_�j
//Width : ����
//Height: ����
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
//color : ���_�̐F�iRGBA�j
//Rot	: ��]�p�x�i���W�A���l�j
void DrawSpriteColorReverse(int texNo, float X, float Y, float Width, float Height,
	float U, float V, float UW, float VH,
	float r, float g, float b, float a, float Rot)
{

	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	// ���W�ϊ�
	vertex[0].Position.x = (-hw) * cosf(Rot) - (-hh) * sinf(Rot) + X;
	vertex[0].Position.y = (-hw) * sinf(Rot) + (-hh) * cosf(Rot) + Y;
	vertex[1].Position.x = (hw)*cosf(Rot) - (-hh) * sinf(Rot) + X;
	vertex[1].Position.y = (hw)*sinf(Rot) + (-hh) * cosf(Rot) + Y;
	vertex[2].Position.x = (-hw) * cosf(Rot) - (hh)*sinf(Rot) + X;
	vertex[2].Position.y = (-hw) * sinf(Rot) + (hh)*cosf(Rot) + Y;
	vertex[3].Position.x = (hw)*cosf(Rot) - (hh)*sinf(Rot) + X;
	vertex[3].Position.y = (hw)*sinf(Rot) + (hh)*cosf(Rot) + Y;

	D3DXCOLOR Color(r, g, b, a);
	vertex[0].Diffuse = Color;
	vertex[1].Diffuse = Color;
	vertex[2].Diffuse = Color;
	vertex[3].Diffuse = Color;

	vertex[0].TexCoord = D3DXVECTOR2(U, V);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_MIRROR);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);

	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);
}

//=============================================================================
// �J�����ɒǏ]����X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F�E��]�p�x
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̒��S�_�j
//Y		: Y���W�i�X�v���C�g�̒��S�_�j
//Width : ����
//Height: ����
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
//color : ���_�̐F�iRGBA�j
//Rot	: ��]�p�x�i���W�A���l�j
void DrawSpriteColorRotateCamera(int texNo, float X, float Y, float Width, float Height,
	float U, float V, float UW, float VH,
	float r, float g, float b, float a, float Rot)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	D3DXVECTOR2 cameraMove = GetCameraMoveVolume();

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	D3DXVECTOR2 pcr;
	pcr = PosCameraRevision(X, Y);

	// ���W�ϊ�
	vertex[0].Position.x = (-hw) * cosf(Rot) - (-hh) * sinf(Rot) + pcr.x;
	vertex[0].Position.y = (-hw) * sinf(Rot) + (-hh) * cosf(Rot) + pcr.y;
	vertex[1].Position.x = (hw)*cosf(Rot) - (-hh) * sinf(Rot) + pcr.x;
	vertex[1].Position.y = (hw)*sinf(Rot) + (-hh) * cosf(Rot) + pcr.y;
	vertex[2].Position.x = (-hw) * cosf(Rot) - (hh)*sinf(Rot) + pcr.x;
	vertex[2].Position.y = (-hw) * sinf(Rot) + (hh)*cosf(Rot) + pcr.y;
	vertex[3].Position.x = (hw)*cosf(Rot) - (hh)*sinf(Rot) + pcr.x;
	vertex[3].Position.y = (hw)*sinf(Rot) + (hh)*cosf(Rot) + pcr.y;

	D3DXCOLOR Color(r, g, b, a);
	vertex[0].Diffuse = Color;
	vertex[1].Diffuse = Color;
	vertex[2].Diffuse = Color;
	vertex[3].Diffuse = Color;

	vertex[0].TexCoord = D3DXVECTOR2(U, V);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F�E��]�p�x
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̒��S�_�j
//Y		: Y���W�i�X�v���C�g�̒��S�_�j
//Width : ����
//Height: ����
//CX	: ��]�����WX
//CY	: ��]�����WY
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
//color : ���_�̐F�iRGBA�j
//Rot	: ��]�p�x�i���W�A���l�j
//ScX	: �g�嗦X
//ScY	: �g�嗦Y
void DrawSpriteColorRotateAxis(int texNo, float X, float Y, float Width, float Height, float CX, float CY,
	float U, float V, float UW, float VH,
	float r, float g, float b, float a, float Rot)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	//��CX,CY����]���ƍl����
	//��]����(0,0)�̌��_�Ɉړ����邽�߁A��]���̍��W�̕�������`�S�̂̍��W���}�C�i�X���A���̏�Ԃŉ�]���s��

	// ���W�ϊ�
	vertex[0].Position.x = (-CX - hw) * cosf(Rot) - (-CY - hh) * sinf(Rot);
	vertex[0].Position.y = (-CX - hw) * sinf(Rot) + (-CY - hh) * cosf(Rot);
	vertex[1].Position.x = (-CX + hw) * cosf(Rot) - (-CY - hh) * sinf(Rot);
	vertex[1].Position.y = (-CX + hw) * sinf(Rot) + (-CY - hh) * cosf(Rot);
	vertex[2].Position.x = (-CX - hw) * cosf(Rot) - (-CY + hh) * sinf(Rot);
	vertex[2].Position.y = (-CX - hw) * sinf(Rot) + (-CY + hh) * cosf(Rot);
	vertex[3].Position.x = (-CX + hw) * cosf(Rot) - (-CY + hh) * sinf(Rot);
	vertex[3].Position.y = (-CX + hw) * sinf(Rot) + (-CY + hh) * cosf(Rot);

	//��]�̕ϊ����I�������Ԃŉ�]���̍��W���v���X���A���_�ɖ߂��B����ɕ\�����W�iX,Y�j�܂ňړ�������
	vertex[0].Position.x += CX + X;
	vertex[0].Position.y += CY + Y;
	vertex[1].Position.x += CX + X;
	vertex[1].Position.y += CY + Y;
	vertex[2].Position.x += CX + X;
	vertex[2].Position.y += CY + Y;
	vertex[3].Position.x += CX + X;
	vertex[3].Position.y += CY + Y;

	D3DXCOLOR Color(r, g, b, a);
	vertex[0].Diffuse = Color;
	vertex[1].Diffuse = Color;
	vertex[2].Diffuse = Color;
	vertex[3].Diffuse = Color;

	vertex[0].TexCoord = D3DXVECTOR2(U, V);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F�E��]�p�x
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̒��S�_�j
//Y		: Y���W�i�X�v���C�g�̒��S�_�j
//Width : ����
//Height: ����
//CX	: ��]�����WX
//CY	: ��]�����WY
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
//color : ���_�̐F�iRGBA�j
//Rot	: ��]�p�x�i���W�A���l�j
//ScX	: �g�嗦X
//ScY	: �g�嗦Y
void DrawSpriteColorRotateScale(int texNo, float X, float Y, float Width, float Height, float CX, float CY,
	float U, float V, float UW, float VH,
	float r, float g, float b, float a, float Rot, float ScX, float ScY)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f * ScX;
	hh = Height * 0.5f * ScY;

	//��CX,CY����]���ƍl����
	//��]����(0,0)�̌��_�Ɉړ����邽�߁A��]���̍��W�̕�������`�S�̂̍��W���}�C�i�X���A���̏�Ԃŉ�]���s��

	// ���W�ϊ�
	vertex[0].Position.x = (-CX - hw) * cosf(Rot) - (-CY - hh) * sinf(Rot);
	vertex[0].Position.y = (-CX - hw) * sinf(Rot) + (-CY - hh) * cosf(Rot);
	vertex[1].Position.x = (-CX + hw) * cosf(Rot) - (-CY - hh) * sinf(Rot);
	vertex[1].Position.y = (-CX + hw) * sinf(Rot) + (-CY - hh) * cosf(Rot);
	vertex[2].Position.x = (-CX - hw) * cosf(Rot) - (-CY + hh) * sinf(Rot);
	vertex[2].Position.y = (-CX - hw) * sinf(Rot) + (-CY + hh) * cosf(Rot);
	vertex[3].Position.x = (-CX + hw) * cosf(Rot) - (-CY + hh) * sinf(Rot);
	vertex[3].Position.y = (-CX + hw) * sinf(Rot) + (-CY + hh) * cosf(Rot);

	//��]�̕ϊ����I�������Ԃŉ�]���̍��W���v���X���A���_�ɖ߂��B����ɕ\�����W�iX,Y�j�܂ňړ�������
	vertex[0].Position.x += CX + X;
	vertex[0].Position.y += CY + Y;
	vertex[1].Position.x += CX + X;
	vertex[1].Position.y += CY + Y;
	vertex[2].Position.x += CX + X;
	vertex[2].Position.y += CY + Y;
	vertex[3].Position.x += CX + X;
	vertex[3].Position.y += CY + Y;

	D3DXCOLOR Color(r, g, b, a);
	vertex[0].Diffuse = Color;
	vertex[1].Diffuse = Color;
	vertex[2].Diffuse = Color;
	vertex[3].Diffuse = Color;

	vertex[0].TexCoord = D3DXVECTOR2(U, V);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// �J�����ɒǏ]����X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F�E��]�p�x
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//X     : X���W�i�X�v���C�g�̒��S�_�j
//Y		: Y���W�i�X�v���C�g�̒��S�_�j
//Width : ����
//Height: ����
//CX	: ��]�����WX
//CY	: ��]�����WY
//U		: UV�l�n�_
//V		: UV�l�n�_
//UW	: UV�l����
//VH	: UV�l����
//color : ���_�̐F�iRGBA�j
//Rot	: ��]�p�x�i���W�A���l�j
//ScX	: �g�嗦X
//ScY	: �g�嗦Y
void DrawSpriteColorRotateScaleCamera(int texNo, float X, float Y, float Width, float Height, float CX, float CY,
	float U, float V, float UW, float VH,
	float r, float g, float b, float a, float Rot, float ScX, float ScY)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f * ScX;
	hh = Height * 0.5f * ScY;

	D3DXVECTOR2 pcr;
	pcr = PosCameraRevision(X, Y);

	//��CX,CY����]���ƍl����
	//��]����(0,0)�̌��_�Ɉړ����邽�߁A��]���̍��W�̕�������`�S�̂̍��W���}�C�i�X���A���̏�Ԃŉ�]���s��

	// ���W�ϊ�
	vertex[0].Position.x = (-CX - hw) * cosf(Rot) - (-CY - hh) * sinf(Rot);
	vertex[0].Position.y = (-CX - hw) * sinf(Rot) + (-CY - hh) * cosf(Rot);
	vertex[1].Position.x = (-CX + hw) * cosf(Rot) - (-CY - hh) * sinf(Rot);
	vertex[1].Position.y = (-CX + hw) * sinf(Rot) + (-CY - hh) * cosf(Rot);
	vertex[2].Position.x = (-CX - hw) * cosf(Rot) - (-CY + hh) * sinf(Rot);
	vertex[2].Position.y = (-CX - hw) * sinf(Rot) + (-CY + hh) * cosf(Rot);
	vertex[3].Position.x = (-CX + hw) * cosf(Rot) - (-CY + hh) * sinf(Rot);
	vertex[3].Position.y = (-CX + hw) * sinf(Rot) + (-CY + hh) * cosf(Rot);

	//��]�̕ϊ����I�������Ԃŉ�]���̍��W���v���X���A���_�ɖ߂��B����ɕ\�����W�iX,Y�j�܂ňړ�������
	vertex[0].Position.x += CX + pcr.x;
	vertex[0].Position.y += CY + pcr.y;
	vertex[1].Position.x += CX + pcr.x;
	vertex[1].Position.y += CY + pcr.y;
	vertex[2].Position.x += CX + pcr.x;
	vertex[2].Position.y += CY + pcr.y;
	vertex[3].Position.x += CX + pcr.x;
	vertex[3].Position.y += CY + pcr.y;

	D3DXCOLOR Color(r, g, b, a);
	vertex[0].Diffuse = Color;
	vertex[1].Diffuse = Color;
	vertex[2].Diffuse = Color;
	vertex[3].Diffuse = Color;

	vertex[0].TexCoord = D3DXVECTOR2(U, V);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// �J�����␳
//=============================================================================
D3DXVECTOR2 PosCameraRevision(float posX, float posY)
{
	//�E�[���ڎ��ł���ʒu�ɂ���ꍇ
	int stageSize = MAP_SIZE_X * MAPCHIP_SIZE;
	int stageHalfSize = stageSize * 0.5f;

	D3DXVECTOR2 cameraMove = GetCameraMoveVolume();
	D3DXVECTOR2 posCameraRevision;
	posCameraRevision.x = posX - (int)cameraMove.x;
	posCameraRevision.y = posY - (int)cameraMove.y;

	//���[�v���ʕ\��
	if (posCameraRevision.x < -SCREEN_WIDTH)
	{
		posCameraRevision.x += stageSize;
	}
	if (posCameraRevision.x > SCREEN_WIDTH)
	{
		posCameraRevision.x -= stageSize;
	}

	return posCameraRevision;
}