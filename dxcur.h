#pragma once

#include "sancur.h"

#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0xff000000

typedef int DxPic_t; /* DX���C�u�����̃O���t�B�b�N�̃n���h���ł��邱�Ƃ������^�Bint�^ */
typedef int DxSnd_t; /* DX���C�u�����̃T�E���h�̃n���h���ł��邱�Ƃ������^�Bint�^ */
typedef int DxTime_t; /* DX���C�u������GetNowCount()���Ŏ擾�������Ԃł��邱�Ƃ������^�Bint�^ */
typedef unsigned int DxColor_t; /* DX���C�u�����̐F�Ƃ��Ďg����^�Bunsigned int�^ */

/**
 * FPS���v������N���X
 */
class dxcur_fps_c {
private:
	DxTime_t tick[120];
	uint head = 0;
	uint tail = 0;
	uint num = 0;
public:
	void SetTick();
	uint GetFPS();
};

/**
 * �_�u�����O����������T�E���h�Đ��N���X
 */
class dxcur_snd_c {
private:
	DxTime_t Btime = 0; // �O��Đ���������
	DxTime_t Gtime = 2; // ������鎞��
	DxSnd_t mat;
public:
	dxcur_snd_c(TCHAR *path);
	~dxcur_snd_c();
	void PlaySound();
};

extern int GetMouseKeyCur(int* key, int* posX, int* posY, int* PR);
extern void AvoidKeyRush();
extern int GetKeyHold(int n);
extern int GetKeyPushOnce();
extern void InputAllKeyHold();
extern void AvoidKeyBug();
extern int keycur(int const* const mat, int num);