#pragma once

#include <vector>

#include <tchar.h>
#include <DxLib.h>
#include <sancur.h>
#include <stdcur.h>

#undef PlaySound

#define COLOR_WHITE  GetColor(255, 255, 255)
#define COLOR_BLACK  GetColor(  0,   0,   0)
#define COLOR_RED    GetColor(255,   0,   0)
#define COLOR_YELLOW GetColor(255, 255,   0)
#define COLOR_GREEN  GetColor(  0, 191,   0) /* (0,255,0)だと明るすぎる */
#define COLOR_CYAN   GetColor(  0, 255, 255)
#define COLOR_BLUE   GetColor(  0,   0, 255)

#define DXLIB_PIC_HAND_DEFAULT  -1
#define DXLIB_SND_HAND_DEFAULT  -1
#define DXLIB_FILE_HAND_DEFAULT  0 /* なぜかfileだけ0なので注意 */

#define DXLIB_PIC_NULL  DXLIB_PIC_HAND_DEFAULT
#define DXLIB_SND_NULL  DXLIB_SND_HAND_DEFAULT
#define DXLIB_FILE_NULL DXLIB_FILE_HAND_DEFAULT

typedef unsigned int DxColor_t; /* DXライブラリの色情報であることを示す型。unsigned int型 */
typedef int DxPic_t; /* DXライブラリのグラフィックのハンドルであることを示す型。int型 */
typedef int DxSnd_t; /* DXライブラリのサウンドのハンドルであることを示す型。int型 */
typedef int Dx3Dobj_t; /* DXライブラリの3Dモデルのハンドルであることを示す型。int型 */
typedef int Dx3Danim_t; /* DXライブラリの3Dアニメーションのハンドルであることを示す型。int型 */
typedef int DxFile_t; /* DXライブラリのファイルのハンドルであることを示す型。int型 */
typedef int DxTime_t; /* DXライブラリのGetNowCount()等で取得した時間であることを示す型。int型 */

/* TODO: ファイル整理いるか? */
#include <dxdraw.h>

/* DeleteGraphを自動でやるクラス */
class dxcur_pic_c {
private:
	DxPic_t pic = DXLIB_PIC_NULL;

public:
	dxcur_pic_c();
	dxcur_pic_c(const TCHAR *path);
	~dxcur_pic_c();

public:
	DxPic_t handle(void) const;
	void reload(const TCHAR *path);
	bool IsValid(void) const;
};

/* LoadDivGraph関連 */
class dxcur_divpic_c {
	bool usable = false;
	std::vector<DxPic_t> pic;

public:
	dxcur_divpic_c(void);
	dxcur_divpic_c(const TCHAR *path, int AllNum, int XNum, int YNum); /* XSizeとYSizeを自動計算する */
	dxcur_divpic_c(const TCHAR *path, int AllNum, int XNum, int YNum, int XSize, int YSize);
	dxcur_divpic_c(dxcur_divpic_c &&obj) noexcept;
	dxcur_divpic_c& operator=(dxcur_divpic_c &&obj) noexcept;
	~dxcur_divpic_c();

	DxPic_t handle(size_t n) const;
	void reload(const TCHAR *path, int AllNum, int XNum, int YNum); /* XSizeとYSizeを自動計算する */
	void reload(const TCHAR *path, int AllNum, int XNum, int YNum, int XSize, int YSize);
	void clear(void);
};

/* 同じ音声が2回以上同じタイミングでなることを防いだクラス */
class dxcur_snd_c {
private:
	DxTime_t Btime = 0; // 前回ならした時間
	DxTime_t Gtime = 10; // 回避する時間
	DxSnd_t mat = -1; // 音声ハンドル
public:
	dxcur_snd_c(const TCHAR *path);
	dxcur_snd_c();
	~dxcur_snd_c();
	void SetSound(const TCHAR *path);
	void SetVolume(int val);
	void PlaySound(bool loop = false);
	DxSnd_t handle(void) const;
	void reload(const TCHAR *path);
};

/**
 * @brief カメラを司るクラス。
 * @details カメラをx方向に10px動かすと、実際に描画される位置はx方向に-10pxずれる。位置の基準はカメラ左上。
 * カメラを2倍ズームにすると、描画されるものが2倍に大きくなる。ズームの中心はカメラ中央。
 * カメラを時計回りに30度回すと、実際に描画されるものは反時計周りに30度回る。回転の中心はカメラ中央。
 * カメラ位置の計算の順序は、位置->拡大->回転。
 * ウィンドウサイズを変えたらupdateWindowSize()で更新しないといけない。
 */
class dxcur_camera_c {
private:
	int xpos = 0;
	int ypos = 0;

	double zoom = 1.0;
	double rot  = 0.0;

	int window_sizeX = 640;
	int window_sizeY = 480;

public:
	dxcur_camera_c(void);

	void rot_xy_pos(double &x, double &y, double rot) const;
	void WorldToScreen(double &x, double &y) const;
	void ScreenToWorld(double &x, double &y) const;
	void reset(void);

	void updateWindowSize(void);

	void drawpic(double x, double y, DxPic_t pic) const;
	void drawpicTurn(double x, double y, DxPic_t pic) const;

	void setX(int x);
	void setY(int y);
	void setZoom(double zoom);
	void setAngleRad(double angle);
	void setAngleDeg(double angle);

	int getX(void) const;
	int getY(void) const;
	double getZoom(void) const;
	double getAngleRad(void) const;
	double getAngleDeg(void) const;
};

class dxcur_key_c {
private:
	struct {
		uint hold = 2;
		uint rele = 0;
		DxTime_t ptime = 0; /* 前回押した時間 */
		DxTime_t rtime = 0; /* 前回離した時間 */
		DxTime_t btime = 0;
	} key[256];

	DxTime_t hold_time  = 500; /* 長押し判定までにかかる時間 */
	DxTime_t hold_pulse = 125; /* 長押し中に反応する間隔 */

public:
	void update(void);
	int GetKeyState(uint n);
	int GetKeyPushOnce(void);
	int GetKeyPulseOnce(void);
};

class dxcur_ui_elem_c {
private:
	int left  = 0;
	int up    = 0;
	int right = 0;
	int down  = 0;
	dxcur_pic_c pic;

public:
	bool box_en = false;
	DxColor_t box_color = COLOR_WHITE;

	tstring text = _T("");
	DxColor_t text_color = COLOR_WHITE;

	dxcur_ui_elem_c(void) = default;
	dxcur_ui_elem_c(int a_left, int a_up, int a_right, int a_down);

	void draw(void) const;
	void SetPosition(int a_left, int a_up, int a_right, int a_down);
	void SetPicture(const TCHAR *path);
	void SetPosByPicture(void);
	bool IsInArea(int x, int y) const;
};

class dxcur_mouse_item_c {
private:
	int NowMouseX = 0;
	int NowMouseY = 0;
	std::vector<dxcur_ui_elem_c> vec;

public:
	dxcur_mouse_item_c(void);
	dxcur_ui_elem_c &operator[](size_t n);
	void AddItem(const dxcur_ui_elem_c &item);

private:
	int SearchInArea(int x, int y) const;

public:
	void update(void);
	void draw(void) const;

private:
	int GetClickedItemBase(int btn) const;

public:
	int GetClickedItem(void) const;
	int GetRightClickedItem(void) const;
	int GetMouseOveredItem(void) const;
};

extern int GetRandBetween(int min, int max);
extern int GetMouseKeyCur(int* key, int* posX, int* posY, int* PR);
extern void AvoidKeyRush();
extern void InputAllKeyHold();
extern int GetKeyHold(int n);
extern int GetKeyPushOnce(bool update_fg = false);
extern void AvoidKeyBug();
extern int keycur(int const* const mat, int num);
extern void DrawLineCurveDiv(int x1, int y1, int x2, int y2, char mode, intx100_t start,
	intx100_t end, uint color, int thick);
extern void DrawLineCurve(int x1, int y1, int x2, int y2, char mode, unsigned int color, int thick);
