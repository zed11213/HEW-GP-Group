//===================================================
//���C��(main.cpp)
//Auhor:�n� �C	Date:2023.7.7
//===================================================
#include <time.h>
#include <random>
#include <tchar.h>
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "collision.h"
#include "sound.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "camera.h"
#include "tile.h"
#include "directWrite.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME			"GameWindow"				// �E�C���h�E�̃N���X��
#define WINDOW_CAPTION		"�������Ă��������Ă�..."	// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

#ifdef _DEBUG
int		g_CountFPS;							// FPS�J�E���^
char	g_DebugStr[2048] = WINDOW_CAPTION;	// �f�o�b�O�����\���p

#endif

SCENE g_Scene = SCENE_NONE;

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	//�����_���V�[�h�̏�����
	srand((unsigned int)time(NULL));

	// ���Ԍv���p
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	int window_width = WINDOW_WIDTH;//�����ݒ� 960
	int window_height = WINDOW_HEIGHT;//�����ݒ� 540

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_CAPTION,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// �E�B���h�E�̍����W
		CW_USEDEFAULT,																		// �E�B���h�E�̏���W
		window_width + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// �E�B���h�E����
		window_height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
		NULL,
		NULL,
		hInstance,
		NULL);


	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;
	
	// �E�C���h�E�̕\��(Init()�̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// �V�X�e���������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;							// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;	// ��������������ۑ�

#ifdef _DEBUG	// �f�o�b�O�ł̎�����FPS��\������
				wsprintf(g_DebugStr, WINDOW_CAPTION);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				SetWindowText(hWnd, g_DebugStr);
#endif

				Update();			// �X�V����
				Draw();				// �`�揈��

				dwFrameCount++;		// �����񐔂̃J�E���g�����Z
			}
		}
	}
	
	timeEndPeriod(1);				// ����\��߂�

	// �I������
	Uninit();

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);		// �E�B���h�E��j������悤�w������
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_�����O�����̏�����
	InitRenderer(hInstance, hWnd, bWindow);

	// ���͏����̏�����
	InitInput(hInstance, hWnd);

	// �X�v���C�g�̏�����
	InitSprite();

	//�T�E���h�̏�����
	InitSound(hWnd);

	InitFade();

	switch (g_Scene)//�V�[�����Ƃ̕���
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		InitTitle();
		break;

	case SCENE_GAME:
		InitGame();
		break;

	case SCENE_RESULT:
		InitResult();
		break;
	}

	//�ŏ��̃V�[��
	SetScene(START_SCENE);

	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	switch (g_Scene)//�V�[�����Ƃ̕���
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		UninitTitle();
		break;

	case SCENE_GAME:
		UninitGame();
		break;

	case SCENE_RESULT:
		UninitResult();
		break;
	}

	UninitFade();

	// �X�v���C�g�̏I������
	UninitSprite();

	// ���͏����̏I������
	UninitInput();

	// �����_�����O�̏I������
	UninitRenderer();

	//�T�E���h�̏I������
	StopSoundAll();
	UninitSound();

	// �e�N�X�`���̉��
	UninitTexture();
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	// ���͏����̍X�V����
	UpdateInput();

	UpdateFade();

	UpdateSound();

	switch (g_Scene)//�V�[�����Ƃ̕���
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		UpdateTitle();
		break;

	case SCENE_GAME:
		UpdateGame();
		break;

	case SCENE_RESULT:
		UpdateResult();
		break;
	}

	// �����蔻��̍X�V����
	UpdateCollision();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@�N���A
	Clear();

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();//���W��2D�ϊ�

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	switch (g_Scene)//�V�[�����Ƃ̕���
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		DrawTitle();
		break;

	case SCENE_GAME:
		DrawGame();
		break;

	case SCENE_RESULT:
		DrawResult();
		break;
	}

	DrawFade();

	// �o�b�N�o�b�t�@�A�t�����g�o�b�t�@����ւ�
	Present();
}


float frand(void)
{
	return (float)rand() / RAND_MAX;
}

//=============================================================================
// �V�[���؂�ւ����N�G�X�g
//=============================================================================
void SetScene(SCENE scene)
{
	switch (g_Scene)//���̃V�[���̏I������
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		UninitTitle();
		break;

	case SCENE_GAME:
		UninitGame();
		break;

	case SCENE_RESULT:
		UninitResult();
		break;
	}


	g_Scene = scene;


	switch (g_Scene)//�J�ڌ�̃V�[���̏���������
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		InitTitle();
		break;

	case SCENE_GAME:
		InitGame();
		break;

	case SCENE_RESULT:
		InitResult();
		break;
	}
}

//=============================================================================
// �V�[����Ԃ�
//=============================================================================
SCENE GetScene()
{
	return g_Scene;
}

//-----------------------------------------------------------------------------
// 0�Ȃ�0�A���̕����Ȃ�1�A�s�̕����Ȃ�-1��Ԃ�
//-----------------------------------------------------------------------------
int Sign(float value)
{
	if (value == 0)return 0;
	else if (value > 0)return 1;
	else return -1;
}

//-----------------------------------------------------------------------------
// ���R����Ԃ�
//-----------------------------------------------------------------------------
int Nat(float value)
{
	if (value < 0)return 0;

	return (int)value;
}

//-----------------------------------------------------------------------------
// �����̐؂�̂� (digit = 10, 100, 1000...)
//-----------------------------------------------------------------------------
float Round(float num, int digit)
{
	num = int(num * digit);
	num = num / digit;
	return num;
}

//-----------------------------------------------------------------------------
// ���W����p�x���v�Z����֐� �x
//-----------------------------------------------------------------------------
double PointDirection(double x1, double y1, double x2, double y2)
{
	// ���W�A���P�ʂ̊p�x���v�Z
	double angle = std::atan2(y2 - y1, x2 - x1);

	// ���W�A����x�ɕϊ�
	double degrees = angle * 180.0f / 3.14159f;

	// 0����360�x�͈̔͂ɒ���
	if (degrees < 0)
	{
		degrees += 360.0;
	}

	return degrees;
}

//-----------------------------------------------------------------------------
// ���W����p�x���v�Z����֐� ���W�A��
//-----------------------------------------------------------------------------
double PointDirectionRadian(double x1, double y1, double x2, double y2)
{
	// ���W�A���P�ʂ̊p�x���v�Z
	double angle = std::atan2(y2 - y1, x2 - x1);

	return angle;
}

//-----------------------------------------------------------------------------
// �Ώۂ܂ł�x��y�̋�����Ԃ�
//-----------------------------------------------------------------------------
D3DXVECTOR2 PointDistance(double x1, double y1, double x2, double y2)
{
	D3DXVECTOR2 distance;
	distance.x = x2 - x1;
	distance.y = y2 - y1;
	
	return distance;
}

//-----------------------------------------------------------------------------
// �p�x�ƒ�������x�N�g�� (x, y) ���v�Z
//-----------------------------------------------------------------------------
D3DXVECTOR2 CalculateVector(double length, double angleRadians)
{
	D3DXVECTOR2 result;

	result.x = cos(angleRadians);
	result.y = sin(angleRadians);

	D3DXVec2Normalize(&result, &result);
	result *= length;//�ړI�̃X�s�[�h�ɂ��邽�߂ɃX�s�[�h����Z����

	return result;
}

////-----------------------------------------------------------------------------
//// �E�B���h�E���擾
////-----------------------------------------------------------------------------
//HWND GethWnd()
//{
//	HWND hWnd = FindWindow("GameWindow", NULL);
//	if (hWnd)
//	{
//		return hWnd;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
////-----------------------------------------------------------------------------
//// ���b�Z�[�W���擾
////-----------------------------------------------------------------------------
//MSG GetMsg()
//{
//	HWND hWnd = FindWindow("GameWindow", NULL);  // �E�B���h�E�n���h�����擾
//	if (hWnd)
//	{
//		MSG msg;
//		while (GetMessage(&msg, NULL, 0, 0)) {
//			TranslateMessage(&msg);// �L�[�{�[�h���b�Z�[�W������
//			DispatchMessage(&msg); // ���b�Z�[�W���E�B���h�E�v���V�[�W���ɑ���
//			return msg;
//		}
//	}
//}

//-----------------------------------------------------------------------------
// �E�B���h�E���擾(�E�B���h�E�T�C�Y���ς�����Ƃ��ɑΏۂ���O��Ȃ��悤�ɂ���)
//-----------------------------------------------------------------------------
//HWND GetActiveWindowHandle()
//{
//	return hWnd;
////	HWND prevActiveWindow = GetActiveWindow();
////
////	// �ꎞ�I�ɃE�B���h�E���ŏ������Ă��猳�ɖ߂�
////	ShowWindow(prevActiveWindow, SW_MINIMIZE);
////	ShowWindow(prevActiveWindow, SW_RESTORE);
////
////	// �A�N�e�B�u�E�B���h�E���ύX�����̂�҂�
////	while (true)
////	{
////		HWND currentActiveWindow = GetActiveWindow();
////		if (currentActiveWindow != prevActiveWindow)
////		{
////			return currentActiveWindow;
////		}
////
////		Sleep(100); // 100�~���b�ҋ@���čĎ��s
////	}
//}

//-----------------------------------------------------------------------------
// �E�B���h�E��N���C�A���g�̑傫�����擾����
// [����] 0: �E�B���h�E�T�C�Y, 1: �N���C�A���g�T�C�Y 
//-----------------------------------------------------------------------------
RECT GetWindowContainerSize(int option)
{
	HWND hWnd = GetActiveWindow();//�E�B���h�E���擾
	RECT rect = { 0 };//�l�p�`�\����
	if (option == 0)GetWindowRect(hWnd, &rect);//�E�B���h�E�̍�����ƉE�����̍��W���擾
	else if (option == 1)GetClientRect(hWnd, &rect);//�N���C�A���g(�A�v�����)�̍�����ƉE�����̍��W���擾
	return rect;
}

//-----------------------------------------------------------------------------
// �E�B���h�E�̉������擾����
//-----------------------------------------------------------------------------
LONG GetWindowWidth()
{
	RECT rect = GetWindowContainerSize(0);

	return 	rect.right;
}

//-----------------------------------------------------------------------------
// �E�B���h�E�̏c�����擾����
//-----------------------------------------------------------------------------
LONG GetWindowHeight()
{
	RECT rect = GetWindowContainerSize(0);

	return 	rect.bottom;
}

//-----------------------------------------------------------------------------
// �N���C�A���g(�E�B���h�E�̎���𔲂�����ʕ���)�̉������擾����
//-----------------------------------------------------------------------------
LONG GetClientWidth()
{
	RECT rect = GetWindowContainerSize(1);

	return 	rect.right;
}

//-----------------------------------------------------------------------------
// �N���C�A���g(�E�B���h�E�̎���𔲂�����ʕ���)�̏c�����擾����
//-----------------------------------------------------------------------------
LONG GetClientHeight()
{
	RECT rect = GetWindowContainerSize(1);

	return 	rect.bottom;
}

//-----------------------------------------------------------------------------
// �A�j���[�V������ݒ肷��
// [����] basePattern: �����0�Ƃ����J�n�t���[��, 
//		  widthPattern: ���̃A�j���p�^�[����, 
//-----------------------------------------------------------------------------
D3DXVECTOR2 SetAnimation(int basePattern, int animeCount, int allWidthPattern, int allHeightPattern, int widthPattern, bool reverse)
{
	D3DXVECTOR2 uv;
	//U      W											N�Ԗڂ� % ���̃p�^�[����
	uv.x = (1.0f / allWidthPattern) * ((animeCount + basePattern) % widthPattern);	//���̍��W�v�Z
	//V     H											N�Ԗڂ� / ���̑S�p�^�[��
	uv.y = (1.0f / allHeightPattern) * ((animeCount + basePattern) / allWidthPattern); //�c�̍��W�v�Z

	//�e�N�X�`�����]
	if (reverse)
	{
		
		//float num = int(1.0f / allWidthPattern * 100);
		//num = num / 100.0f;
		uv.x = 1 + (1 - uv.x) - Round(1.0f / allWidthPattern, 100);//���[�Ȃ̂�-0.25
	}

	return uv;
}

//-----------------------------------------------------------------------------
// UV���W���Z�b�g(���� : ����[��0���̉E�ׂ��1,2,3...�Ƃ����Ƃ��̐�)
//-----------------------------------------------------------------------------
D3DXVECTOR2 GetUV(int index, int widthPattern, int heightPattern)
{
	float U = (index % widthPattern) * (1.0f / widthPattern);
	float V = (index / widthPattern) * (1.0f / heightPattern);
	D3DXVECTOR2 UV = D3DXVECTOR2(U, V);
	return UV;
}

//-----------------------------------------------------------------------------
// ���������������ɂȂ�����0�ɂ���
//-----------------------------------------------------------------------------
int Counter(int count, int max)
{
	count++;

	if (count >= max)
	{
		count = 0;
	}
	return count;
}

//-----------------------------------------------------------------------------
// �f�o�b�O�̏o��
// �� ("X" + std::to_string(cursorPos.x) + "   Y" + std::to_string(cursorPos.y));
//-----------------------------------------------------------------------------
void DebugPrint(const std::string& message) 
{
	OutputDebugStringA(("�f�o�b�O: " + message + "\n").c_str());
}

void DebugPrint(const float& message1, const float& message2, std::string message3)
{
	OutputDebugStringA(("�f�o�b�O: " + std::to_string(message1) + "		" + std::to_string(message2) + "	:" + message3 + "\n").c_str());
}

//-----------------------------------------------------------------------------
// �����_��
//-----------------------------------------------------------------------------
int GetRandomInt(int min, int max)
{
	std::random_device rd;
	std::uniform_int_distribution<> dist(min, max);
	return dist(rd);
}

float GetRandomFloat(float min, float max)
{
	std::random_device rd;
	std::uniform_real_distribution<> dist(min, max);
	return dist(rd);
}

//-----------------------------------------------------------------------------
// ���Œ��I���܂�
// �����ɉ�%���������������I�΂���1��������Ȃ�2��Ԃ��܂�
// �ǂ���I�΂�Ȃ����0��Ԃ��܂�
//-----------------------------------------------------------------------------
int RandomPercent(float percent1, float percent2, float percent3, float percent4, float percent5, float percent6, float percent7, float percent8, float percent9, float percent10)
{
	float percent[10] = { percent1 , percent2 ,percent3 ,percent4 ,percent5 ,percent6 ,percent7 ,percent8 ,percent9 ,percent10 };
	int ran = GetRandomInt(1, 100);

	for (int i = 0; i < 10; i++)
	{
		if (ran < percent[i])return i + 1;

		ran -= percent[i];
	}

	return 0;
}

//-----------------------------------------------------------------------------
// ��ʊO�ɏo��������
//-----------------------------------------------------------------------------
bool OffScreenJudge(float posX, float posY, float sizeX, float sizeY)
{
	bool judge = false;
	D3DXVECTOR2  cameraPos = GetCameraPos(0);

	//���E����
	//��ʊO�͈͎Z�o
	float offScreenL = (cameraPos.x - SCREEN_WIDTH * 0.5f);
	float offScreenR = (cameraPos.x + SCREEN_WIDTH * 0.5f);
	//����͈̓��[�v���̏���
	if (offScreenL < 0)
	{
		offScreenL += STAGE_SIZE;
		if (posX + sizeX < offScreenL && posX - sizeX > offScreenR)judge = true;
	}
	else if (offScreenR > STAGE_SIZE)
	{
		offScreenR -= STAGE_SIZE;
		if (posX + sizeX < offScreenL && posX - sizeX > offScreenR)judge = true;
	}
	//���[�v���ĂȂ��Ƃ��̏���
	else
	{
		if (posX + sizeX < offScreenL || posX - sizeX > offScreenR)judge = true;
	}
	
	//�㉺����
	if (posY + sizeY < 0 || posY - sizeY > SCREEN_HEIGHT)judge = true;

	return judge;
}
