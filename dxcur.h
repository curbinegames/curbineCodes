#pragma once

#include <tchar.h>
#include <DxLib.h>

#undef PlaySound

#define COLOR_WHITE GetColor(255, 255, 255)
#define COLOR_BLACK GetColor(  0,   0,   0)
#define COLOR_RED   GetColor(255,   0,   0)
#define COLOR_GREEN GetColor(  0, 191,   0) /* (0,255,0)���Ɩ��邷���� */
#define COLOR_BLUE  GetColor(  0,   0, 255)

#define DXLIB_PIC_HAND_DEFAULT -1
#define DXLIB_SND_HAND_DEFAULT -1
#define DXLIB_PIC_NULL -1
#define DXLIB_SND_NULL -1

typedef unsigned int DxColor_t; /* DX���C�u�����̐F���ł��邱�Ƃ������^�Bunsigned int�^ */
typedef int DxPic_t; /* DX���C�u�����̃O���t�B�b�N�̃n���h���ł��邱�Ƃ������^�Bint�^ */
typedef int DxSnd_t; /* DX���C�u�����̃T�E���h�̃n���h���ł��邱�Ƃ������^�Bint�^ */
typedef int DxFile_t; /* DX���C�u�����̃t�@�C���̃n���h���ł��邱�Ƃ������^�Bint�^ */
typedef int DxTime_t; /* DX���C�u������GetNowCount()���Ŏ擾�������Ԃł��邱�Ƃ������^�Bint�^ */

/* ����������2��ȏ㓯���^�C�~���O�łȂ邱�Ƃ�h�����N���X */
class dxcur_snd_c {
private:
	DxTime_t Btime = 0; // �O��Ȃ炵������
	DxTime_t Gtime = 2; // ������鎞��
	DxSnd_t mat; // �����n���h��
public:
	dxcur_snd_c();
	~dxcur_snd_c();
	void SetSound(const TCHAR *path);
	void SetVolume(int val);
	void PlaySound(void);
};

extern int GetMouseKeyCur(int* key, int* posX, int* posY, int* PR);
extern void AvoidKeyRush();
extern int GetKeyHold(int n);
extern int GetKeyPushOnce();
extern void InputAllKeyHold();
extern void AvoidKeyBug();
extern int keycur(int const* const mat, int num);
