#pragma once

#include <tchar.h>
#include <DxLib.h>

#undef PlaySound

#define COLOR_WHITE GetColor(255, 255, 255)
#define COLOR_BLACK GetColor(  0,   0,   0)
#define COLOR_RED   GetColor(255,   0,   0)
#define COLOR_GREEN GetColor(  0, 191,   0) /* (0,255,0)だと明るすぎる */
#define COLOR_BLUE  GetColor(  0,   0, 255)

#define DXLIB_PIC_HAND_DEFAULT -1
#define DXLIB_SND_HAND_DEFAULT -1
#define DXLIB_PIC_NULL -1
#define DXLIB_SND_NULL -1

typedef unsigned int DxColor_t; /* DXライブラリの色情報であることを示す型。unsigned int型 */
typedef int DxPic_t; /* DXライブラリのグラフィックのハンドルであることを示す型。int型 */
typedef int DxSnd_t; /* DXライブラリのサウンドのハンドルであることを示す型。int型 */
typedef int DxFile_t; /* DXライブラリのファイルのハンドルであることを示す型。int型 */
typedef int DxTime_t; /* DXライブラリのGetNowCount()等で取得した時間であることを示す型。int型 */

/* 同じ音声が2回以上同じタイミングでなることを防いだクラス */
class dxcur_snd_c {
private:
	DxTime_t Btime = 0; // 前回ならした時間
	DxTime_t Gtime = 2; // 回避する時間
	DxSnd_t mat; // 音声ハンドル
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
extern void DrawLineCurve(int x1, int y1, int x2, int y2, char mode, unsigned int color, int thick);
