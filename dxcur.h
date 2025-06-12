#pragma once

#include <tchar.h>
#include <DxLib.h>
#include <sancur.h>

#undef PlaySound

#define COLOR_WHITE  GetColor(255, 255, 255)
#define COLOR_BLACK  GetColor(  0,   0,   0)
#define COLOR_RED    GetColor(255,   0,   0)
#define COLOR_YELLOW GetColor(255, 255,   0)
#define COLOR_GREEN  GetColor(  0, 191,   0) /* (0,255,0)���Ɩ��邷���� */
#define COLOR_CYAN   GetColor(  0, 255, 255)
#define COLOR_BLUE   GetColor(  0,   0, 255)

#define DXLIB_PIC_HAND_DEFAULT  -1
#define DXLIB_SND_HAND_DEFAULT  -1
#define DXLIB_FILE_HAND_DEFAULT  0 /* �Ȃ���file����0�Ȃ̂Œ��� */

#define DXLIB_PIC_NULL  DXLIB_PIC_HAND_DEFAULT
#define DXLIB_SND_NULL  DXLIB_SND_HAND_DEFAULT
#define DXLIB_FILE_NULL DXLIB_FILE_HAND_DEFAULT

typedef unsigned int DxColor_t; /* DX���C�u�����̐F���ł��邱�Ƃ������^�Bunsigned int�^ */
typedef int DxPic_t; /* DX���C�u�����̃O���t�B�b�N�̃n���h���ł��邱�Ƃ������^�Bint�^ */
typedef int DxSnd_t; /* DX���C�u�����̃T�E���h�̃n���h���ł��邱�Ƃ������^�Bint�^ */
typedef int DxFile_t; /* DX���C�u�����̃t�@�C���̃n���h���ł��邱�Ƃ������^�Bint�^ */
typedef int DxTime_t; /* DX���C�u������GetNowCount()���Ŏ擾�������Ԃł��邱�Ƃ������^�Bint�^ */

/* TODO: �t�@�C���������邩? */
#include <dxdraw.h>

/* DeleteGraph�������ł��N���X */
class dxcur_pic_c {
private:
	DxPic_t pic = DXLIB_PIC_NULL;

public:
	dxcur_pic_c() {}

	dxcur_pic_c(const TCHAR *path) {
		this->pic = LoadGraph(path);
	}

	~dxcur_pic_c() {
		if (this->pic != DXLIB_PIC_NULL) {
			DeleteGraph(this->pic);
		}
	}

public:
	DxPic_t handle(void) const {
		return this->pic;
	}

	void reload(const TCHAR *path) {
		DeleteGraph(this->pic);
		this->pic = LoadGraph(path);
	}
};

/* ����������2��ȏ㓯���^�C�~���O�łȂ邱�Ƃ�h�����N���X */
class dxcur_snd_c {
private:
	DxTime_t Btime = 0; // �O��Ȃ炵������
	DxTime_t Gtime = 10; // ������鎞��
	DxSnd_t mat; // �����n���h��
public:
	dxcur_snd_c();
	~dxcur_snd_c();
	void SetSound(const TCHAR *path);
	void SetVolume(int val);
	void PlaySound(void);
};

class cur_camera_c {
private:
	int cam_xpos = 0;
	int cam_ypos = 0;
	double cam_zoom = 1.0;
	int cam_rot = 0;
	int ScXsize = 640;
	int ScYsize = 480;

private:
	void CalDrawPos(int *x, int *y) const;

public:
	cur_camera_c(void);

public:
	void DrawLineOnCam(int x1, int y1, int x2, int y2, DxColor_t color, uint thick) const;
	void DrawLineCurveOnCam(int x1, int y1, int x2, int y2, int mode, unsigned int color, int thick) const;
	void DrawStringOnCam(int x, int y, const TCHAR *str, DxColor_t cr) const;
	void DrawGraphOnCam(int x, int y, DxPic_t pic) const;
	void DrawTurnGraphOnCam(int x, int y, DxPic_t pic) const;
	void DrawDeformationPicOnCam(int x, int y, double size, int rot, int alpha, DxPic_t pic);

public:
	int GetXPosOnCam(int x, int y) const;
	int GetYPosOnCam(int x, int y) const;

public:
	int    GetXPos(void) const;
	void   SetXPos(int val);
	void   AddXPos(int val);
	int    GetYPos(void) const;
	void   SetYPos(int val);
	void   AddYPos(int val);
	double GetZoom(void) const;
	void   SetZoom(double val);
	void   AddZoom(double val);
	int    GetRot(void) const;
	void   SetRot(int val);
	void   AddRot(int val);
};

extern int GetMouseKeyCur(int* key, int* posX, int* posY, int* PR);
extern void AvoidKeyRush();
extern int GetKeyHold(int n);
extern int GetKeyPushOnce();
extern void InputAllKeyHold();
extern void AvoidKeyBug();
extern int keycur(int const* const mat, int num);
extern void DrawLineCurve(int x1, int y1, int x2, int y2, char mode, unsigned int color, int thick);
