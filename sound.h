
#pragma once

#include <windows.h>
#include "xaudio2.h"


bool InitSound(HWND hWnd);
void UninitSound(void);
void UpdateSound(void);

int LoadSound(char* pFilename);				//WAVデータの読み込み
void PlaySound(int index, int loopCount);	//サウンドの再生
void StopSound(int index);					//サウンド再生停止
void StopSoundAll(void);					//全サウンド再生停止
void SetVolume(int index, float vol);		//音量設定
