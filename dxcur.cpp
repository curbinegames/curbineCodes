#pragma once

#include <vector>
#include <DxLib.h>
#include <sancur.h>
#include <dxcur.h>

#undef PlaySound

static int keyhold[256];

#if 1 /* dxcur_pic_c */

dxcur_pic_c::dxcur_pic_c() {}

dxcur_pic_c::dxcur_pic_c(const TCHAR *path) {
	this->pic = LoadGraph(path);
}

dxcur_pic_c::~dxcur_pic_c() {
	if (this->pic != DXLIB_PIC_NULL) {
		DeleteGraph(this->pic);
	}
}

DxPic_t dxcur_pic_c::handle(void) const {
	return this->pic;
}

void dxcur_pic_c::reload(const TCHAR *path) {
	DeleteGraph(this->pic);
	this->pic = LoadGraph(path);
}

#endif /* dxcur_pic_c */

#if 1 /* dxcur_divpic_c */

#if 1 /* コンスト系 */

dxcur_divpic_c::dxcur_divpic_c(void) {}

dxcur_divpic_c::dxcur_divpic_c(const TCHAR *path, int AllNum, int XNum, int YNum)
	: pic(AllNum)
{
	if (XNum <= 0) { return; }
	if (YNum <= 0) { return; }
	if (XNum * YNum < AllNum) { return; }

	int XSize = 0;
	int YSize = 0;
	DxPic_t buf = LoadGraph(path);
	if (buf == DXLIB_PIC_NULL) { return; }

	GetGraphSize(buf, &XSize, &YSize);
	DeleteGraph(buf);
	XSize /= XNum;
	YSize /= YNum;
	dxcur_divpic_c(path, AllNum, XNum, YNum, XSize, YSize);
}

dxcur_divpic_c::dxcur_divpic_c(const TCHAR *path, int AllNum, int XNum, int YNum, int XSize, int YSize)
	: pic(AllNum)
{
	DxPic_t *mem = (DxPic_t *)malloc(sizeof(DxPic_t) * AllNum);
	if (mem == NULL) { return; }
	LoadDivGraph(path, AllNum, XNum, YNum, XSize, YSize, mem);
	for (size_t i = 0; i < AllNum; i++) { this->pic[i] = mem[i]; }
	free(mem);
	this->usable = true;
}

dxcur_divpic_c::dxcur_divpic_c(dxcur_divpic_c &&obj) noexcept {
	this->pic = (std::move(obj.pic));
	obj.usable = false;
}

dxcur_divpic_c& dxcur_divpic_c::operator=(dxcur_divpic_c &&obj) noexcept {
	if (this != &obj) {
		this->clear();
		this->pic = (std::move(obj.pic));
		this->usable = obj.usable;
		obj.usable = false;
	}
	return *this;
}

dxcur_divpic_c::~dxcur_divpic_c() {
	for (size_t i = 0; i < this->pic.size(); i++) {
		DeleteGraph(this->pic[i]);
	}
}

#endif /* コンスト系 */

DxPic_t dxcur_divpic_c::handle(size_t n) const {
	if (!this->usable) { return DXLIB_PIC_NULL; }
	if (n < 0) { this->pic[0]; }
	if (this->pic.size() <= n) { this->pic[this->pic.size() - 1]; }
	return this->pic[n];
}

/* reload1: サイズ計算だけやって後はreload2に任せる */
void dxcur_divpic_c::reload(const TCHAR *path, int AllNum, int XNum, int YNum) {
	if (XNum <= 0) { return; }
	if (YNum <= 0) { return; }
	if (XNum * YNum < AllNum) { return; }

	int XSize = 0;
	int YSize = 0;
	DxPic_t buf = LoadGraph(path);
	if (buf == DXLIB_PIC_NULL) { return; }

	GetGraphSize(buf, &XSize, &YSize);
	DeleteGraph(buf);
	XSize /= XNum;
	YSize /= YNum;
	this->reload(path, AllNum, XNum, YNum, XSize, YSize);
}

/* reload2 */
void dxcur_divpic_c::reload(const TCHAR *path, int AllNum, int XNum, int YNum, int XSize, int YSize) {
	this->clear();
	this->pic.resize(AllNum);

	DxPic_t *mem = (DxPic_t *)malloc(sizeof(DxPic_t) * AllNum);
	if (mem == NULL) { return; }
	LoadDivGraph(path, AllNum, XNum, YNum, XSize, YSize, mem);
	for (size_t i = 0; i < AllNum; i++) { this->pic[i] = mem[i]; }
	free(mem);
	this->usable = true;
}

void dxcur_divpic_c::clear(void) {
	for (size_t i = 0; i < this->pic.size(); i++) {
		DeleteGraph(this->pic[i]);
		this->pic[i] = DXLIB_PIC_NULL;
	}
	this->usable = false;
}

#endif /* dxcur_divpic_c */

#if 1 /* dxcur_snd_c */

dxcur_snd_c::dxcur_snd_c(const TCHAR *path) {
	this->mat = LoadSoundMem(path);
}

dxcur_snd_c::dxcur_snd_c() {}

dxcur_snd_c::~dxcur_snd_c() {
	DeleteSoundMem(this->mat);
}

void dxcur_snd_c::SetSound(const TCHAR *path) {
	this->mat = LoadSoundMem(path);
}

void dxcur_snd_c::SetVolume(int val) {
	ChangeVolumeSoundMem(val, this->mat);
}

void dxcur_snd_c::PlaySound(bool loop) {
	DxTime_t Ntime = GetNowCount();
	if ((this->Btime + this->Gtime) < Ntime) {
		PlaySoundMem(this->mat, loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK);
		this->Btime = Ntime;
	}
}

DxSnd_t dxcur_snd_c::handle(void) const {
	return this->mat;
}

void dxcur_snd_c::reload(const TCHAR *path) {
	DeleteSoundMem(this->mat);
	this->mat = LoadSoundMem(path);
}

#endif /* dxcur_snd_c */

#if 1 /* cur_camera_c */

void cur_camera_c::CalDrawPos(int *x, int *y) const {
	int bufx = *x;
	int bufy = *y;

	bufx = bufx - this->cam_xpos;
	bufy = bufy - this->cam_ypos;

	rot_xy_pos(this->cam_rot, &bufx, &bufy);

	*x = bufx * this->cam_zoom + this->cam_xpos;
	*y = bufy * this->cam_zoom + this->cam_ypos;
}

cur_camera_c::cur_camera_c(void) {
	GetScreenSize(&this->ScXsize, &this->ScYsize);
}

void cur_camera_c::DrawLineOnCam(int x1, int y1, int x2, int y2, DxColor_t color, uint thick) const {
	int DrawX  = x1;
	int DrawY  = y1;
	int DrawX2 = x2;
	int DrawY2 = y2;
	this->CalDrawPos(&DrawX,  &DrawY);
	this->CalDrawPos(&DrawX2, &DrawY2);
	DrawLine(DrawX, DrawY, DrawX2, DrawY2, color, thick);
}

void cur_camera_c::DrawLineCurveOnCam(int x1, int y1, int x2, int y2, int mode, unsigned int color, int thick) const {
	int DrawX  = x1;
	int DrawY  = y1;
	int DrawX2 = x2;
	int DrawY2 = y2;
	this->CalDrawPos(&DrawX,  &DrawY);
	this->CalDrawPos(&DrawX2, &DrawY2);
	DrawLineCurve(DrawX, DrawY, DrawX2, DrawY2, mode, color, thick);
}

void cur_camera_c::DrawStringOnCam(int x, int y, const TCHAR *str, DxColor_t cr) const {
	int DrawX = x;
	int DrawY = y;
	this->CalDrawPos(&DrawX, &DrawY);
	DrawString(DrawX, DrawY, str, cr);
}

void cur_camera_c::DrawGraphOnCam(int x, int y, DxPic_t pic) const {
	int DrawX  = x;
	int DrawY  = y;
	int DrawX2 = x;
	int DrawY2 = y;
	int sizeX  = 0;
	int sizeY  = 0;
	GetGraphSize(pic, &sizeX, &sizeY);
	DrawX2 = x + sizeX;
	DrawY2 = y + sizeY;
	this->CalDrawPos(&DrawX,  &DrawY);
	this->CalDrawPos(&DrawX2, &DrawY2);
	DrawExtendGraph(DrawX, DrawY, DrawX2, DrawY2, pic, TRUE);
}

void cur_camera_c::DrawTurnGraphOnCam(int x, int y, DxPic_t pic) const {
	int DrawX  = x;
	int DrawY  = y;
	int DrawX2 = x;
	int DrawY2 = y;
	int sizeX  = 0;
	int sizeY  = 0;
	GetGraphSize(pic, &sizeX, &sizeY);
	DrawX2 = x + sizeX;
	DrawY2 = y + sizeY;
	this->CalDrawPos(&DrawX,  &DrawY);
	this->CalDrawPos(&DrawX2, &DrawY2);
	DrawExtendGraph(DrawX2, DrawY, DrawX, DrawY2, pic, TRUE);
}

void cur_camera_c::DrawDeformationPicOnCam(int x, int y, double size, int rot, int alpha, DxPic_t pic) {
	int DrawX = x;
	int DrawY = y;
	this->CalDrawPos(&DrawX, &DrawY);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawDeformationPic(DrawX, DrawY, size * this->cam_zoom, size * this->cam_zoom, rot, pic);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

int cur_camera_c::GetXPosOnCam(int x, int y) const {
	int bufX = x;
	int bufY = y;
	this->CalDrawPos(&bufX, &bufY);
	return bufX;
}

int cur_camera_c::GetYPosOnCam(int x, int y) const {
	int bufX = x;
	int bufY = y;
	this->CalDrawPos(&bufX, &bufY);
	return bufY;
}

int    cur_camera_c::GetXPos(void) const { return this->cam_xpos; }
void   cur_camera_c::SetXPos(int val)    { this->cam_xpos  = val; }
void   cur_camera_c::AddXPos(int val)    { this->cam_xpos += val; }
int    cur_camera_c::GetYPos(void) const { return this->cam_ypos; }
void   cur_camera_c::SetYPos(int val)    { this->cam_ypos  = val; }
void   cur_camera_c::AddYPos(int val)    { this->cam_ypos += val; }
double cur_camera_c::GetZoom(void) const { return this->cam_zoom; }
void   cur_camera_c::SetZoom(double val) { this->cam_zoom  = val; }
void   cur_camera_c::AddZoom(double val) { this->cam_zoom *= val; }
int    cur_camera_c::GetRot (void) const { return this->cam_rot ; }
void   cur_camera_c::SetRot (int val)    { this->cam_rot   = val; }
void   cur_camera_c::AddRot (int val)    { this->cam_rot  += val; }

#endif

int GetRandBetween(int min, int max) {
	return GetRand(max - min) + min;
	// return rand() % (max - min) + min - 1; /* DxLibを使わないバージョン */
}

/**
 * マウスのキー入力の情報を返す
 * @param[out] key 反応したボタンの種類
 * @param[out] posX 反応したX位置
 * @param[out] posY 反応したy位置
 * @param[out] key 反応の種類, 0: 押した, 1: 離した
 * @return 0のみ
 */
int GetMouseKeyCur(int* key, int* posX, int* posY, int* PR) {
	while (GetMouseInputLog2(key, posX, posY, PR, true) == 0) {}
	return 0;
}

/**
 * キー入力のバグを回避する関数
 * @return なし
 */
void AvoidKeyRush() {
	for (int i = 0; i < 256; i++) {
		keyhold[i] = 2;
	}
	return;
}

/**
 * 指定されたキーの状態を返す
 * @return 0: 押していない, 1: たった今押された, 2以上: 長押ししている
 */
int GetKeyHold(int n) {
	return keyhold[n];
}

/**
 * たった今押したキーを1個だけ返す。同時押しには対応していない
 * @return たった今押したキー
 * @note この関数を使用する前に、InputAllKeyHoldでキー情報を更新してください
 * @note InputAllKeyHoldを使用しないと、前回と同じ値が返ります
 */
int GetKeyPushOnce() {
	for (int i = 0; i < 256; i++) {
		if (keyhold[i] == 1) {
			return i;
		}
	}
	return -1;
}

/**
 * キー情報を更新する
 * @return なし
 */
void InputAllKeyHold() {
	char recv[256];
	GetHitKeyStateAll(recv);
	for (int i = 0; i < 256; i++) {
		if (recv[i] == 1) {
			keyhold[i]++;
		}
		else {
			keyhold[i] = 0;
		}
	}
	return;
}

/**
 * 今はもう何もしない関数。使用している場所があるため残している
 * @return なし
 */
void AvoidKeyBug() {
	/* nop */
}

/**
 * この関数はもう古いので、代わりにInputAllKeyHold(),GetKeyPushOnce()を使ってください。
 * @param[in] mat 未使用
 * @param[in] num 未使用
 * @return たった今押したキー
 * @details たった今押したキーを1個だけ返す。同時押しには対応していない
 */
int keycur(int const* const mat, int num) {
	InputAllKeyHold();
	return GetKeyPushOnce();
}

/* TODO: 余裕があればベジエ作る */

/**
 * TODO: 関数コメント書く
 */
void DrawLineCurveDiv(int x1, int y1, int x2, int y2, char mode, intx100_t start, intx100_t end,
	uint color, int thick)
{
	if (end <= start) { return; }
	int drawXStart = 0;
	int drawXEnd   = 0;
	int lend = x1 + 10;

	drawXStart = ((100 - start) * x1 + start * x2) / 100;
	drawXEnd   = ((100 - end  ) * x1 + end   * x2) / 100;
	switch (mode) {
	case 1: // lin
		DrawLine(drawXStart, y1, drawXEnd, y2, color, thick);
		break;
	case 2: // acc
		for (int i = drawXStart; i <= drawXEnd; i += 10) {
			lend = mins_2(i + 10, x2);
			DrawLine(i, pals(x1, y1, x2, y2, i), lend, pals(x1, y1, x2, y2, lend), color, thick);
		}
		break;
	case 3: // dec
		for (int i = drawXStart; i <= drawXEnd; i += 10) {
			lend = mins_2(i + 10, x2);
			DrawLine(i, pals(x2, y2, x1, y1, i), lend, pals(x2, y2, x1, y1, lend), color, thick);
		}
		break;
	}
	return;
}

void DrawLineCurve(int x1, int y1, int x2, int y2, char mode, unsigned int color, int thick) {
	DrawLineCurveDiv(x1, y1, x2, y2, mode, 0, 100, color, thick);
	return;
}
