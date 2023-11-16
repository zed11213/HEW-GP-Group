
#pragma once

#include <windows.h>
#include "xaudio2.h"


bool InitSound(HWND hWnd);
void UninitSound(void);
void UpdateSound(void);

int LoadSound(char* pFilename);				//WAV�f�[�^�̓ǂݍ���
void PlaySound(int index, int loopCount);	//�T�E���h�̍Đ�
void StopSound(int index);					//�T�E���h�Đ���~
void StopSoundAll(void);					//�S�T�E���h�Đ���~
void SetVolume(int index, float vol);		//���ʐݒ�
