#pragma once

#include <cmath>
#include <vector>
#include <DxLib.h>
#include <sancur.h>
#include <stdcur.h>
#include <dxcur.h>

#undef PlaySound

static int keyhold[256];

#if 1 /* dxcur_pic_c */

dxcur_pic_c::dxcur_pic_c() {}

dxcur_pic_c::dxcur_pic_c(const TCHAR *path) {
	this->pic = LoadGraph(path);
}

dxcur_pic_c::~dxcur_pic_c() {
	if (this->IsValid()) {
		DeleteGraph(this->pic);
	}
}

DxPic_t dxcur_pic_c::handle(void) const {
	return this->pic;
}

void dxcur_pic_c::reload(const TCHAR *path) {
	DeleteGraph(this->pic);
	this->pic = DXLIB_PIC_NULL;
	this->pic = LoadGraph(path);
}

bool dxcur_pic_c::IsValid(void) const {
	return (this->handle() != DXLIB_PIC_NULL);
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

	{
		DxPic_t *mem = (DxPic_t *)malloc(sizeof(DxPic_t) * AllNum);
		if (mem == NULL) { return; }
		LoadDivGraph(path, AllNum, XNum, YNum, XSize, YSize, mem);
		for (size_t i = 0; i < AllNum; i++) { this->pic[i] = mem[i]; }
		free(mem);
		this->usable = true;
	}
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
	if (n < 0) { return this->pic[0]; }
	if (this->pic.size() <= n) { return this->pic[this->pic.size() - 1]; }
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
	this->mat = DXLIB_SND_NULL;
	this->mat = LoadSoundMem(path);
}

#endif /* dxcur_snd_c */

#if 1 /* dxcur_camera_c */

dxcur_camera_c::dxcur_camera_c(void) {
	this->updateWindowSize();
}

void dxcur_camera_c::rot_xy_pos(double &x, double &y, double rot) const {
	double bx = x;
	if (!IS_BETWEEN_RIGHT_LESS(0, rot, PI * 2)) {
		rot = std::fmod(rot, PI * 2);
	}
	if (std::abs(rot) < 1e-9) { return; }
	x =  x * std::cos(rot) - y * std::sin(rot);
	y = bx * std::sin(rot) + y * std::cos(rot);
	return;
}

void dxcur_camera_c::WorldToScreen(double &x, double &y) const {
	/* 位置 */
	x -= this->xpos;
	y -= this->ypos;
	/* 中央補正 */
	x -= this->window_sizeX / 2;
	y -= this->window_sizeY / 2;
	/* 拡大 */
	x *= this->zoom;
	y *= this->zoom;
	/* 回転 */
	this->rot_xy_pos(x, y, -(this->rot));
	/* 中央補正解除 */
	x += this->window_sizeX / 2;
	y += this->window_sizeY / 2;
}

void dxcur_camera_c::ScreenToWorld(double &x, double &y) const {
	/* 中央補正 */
	x -= this->window_sizeX / 2;
	y -= this->window_sizeY / 2;
	/* 回転 */
	this->rot_xy_pos(x, y, this->rot);
	/* 拡大 */
	x = DIV_AVOID_ZERO(x, this->zoom, 0);
	y = DIV_AVOID_ZERO(y, this->zoom, 0);
	/* 中央補正解除 */
	x += this->window_sizeX / 2;
	y += this->window_sizeY / 2;
	/* 位置 */
	x += this->xpos;
	y += this->ypos;
}

void dxcur_camera_c::reset(void) {
	this->xpos = 0;
	this->ypos = 0;
	this->zoom = 1.0;
	this->rot  = 0.0;
}

void dxcur_camera_c::updateWindowSize(void) {
	int cr;
	GetScreenState(&this->window_sizeX, &this->window_sizeY, &cr);
}

void dxcur_camera_c::drawpic(double x, double y, DxPic_t pic) const {
	double DrawX = x;
	double DrawY = y;
	this->WorldToScreen(DrawX, DrawY);
	DrawRotaGraph2(DrawX, DrawY, 0, 0, this->zoom, -(this->rot), pic, TRUE, FALSE);
}

void dxcur_camera_c::drawpicTurn(double x, double y, DxPic_t pic) const {
	double DrawX = x;
	double DrawY = y;
	this->WorldToScreen(DrawX, DrawY);
	DrawRotaGraph2(DrawX, DrawY, 0, 0, this->zoom, -(this->rot), pic, TRUE, TRUE);
}

void dxcur_camera_c::setX(int x) {
	this->xpos = x;
}

void dxcur_camera_c::setY(int y) {
	this->ypos = y;
}

void dxcur_camera_c::setZoom(double zoom) {
	if (zoom < 1e-9) { return; }
	this->zoom = zoom;
}

void dxcur_camera_c::setAngleRad(double angle) {
	this->rot = angle;
	if (!IS_BETWEEN_RIGHT_LESS(0, this->rot, PI * 2)) {
		this->rot = std::fmod(this->rot, PI * 2);
	}
	if (this->rot < 0) { this->rot += PI * 2; }
}

void dxcur_camera_c::setAngleDeg(double angle) {
	this->rot = angle * PI / 180;
	if (!IS_BETWEEN_RIGHT_LESS(0, this->rot, PI * 2)) {
		this->rot = std::fmod(this->rot, PI * 2);
	}
	if (this->rot < 0) { this->rot += PI * 2; }
}

int dxcur_camera_c::getX(void) const {
	return this->xpos;
}

int dxcur_camera_c::getY(void) const {
	return this->ypos;
}

double dxcur_camera_c::getZoom(void) const {
	return this->zoom;
}

double dxcur_camera_c::getAngleRad(void) const {
	return this->rot;
}

double dxcur_camera_c::getAngleDeg(void) const {
	return 180 * this->rot / PI;
}

#endif /* dxcur_camera_c */

#if 1 /* dxcur_key_c */

/**
* キー情報を更新する
* @return なし
*/
void dxcur_key_c::update(void) {
	char recv[256];
	DxTime_t Ntime = GetNowCount();
	GetHitKeyStateAll(recv);
	for (int i = 0; i < 256; i++) {
		if (recv[i] == 1) {
			this->key[i].hold++;
			this->key[i].rele = 0;
		}
		else {
			this->key[i].hold = 0;
			this->key[i].rele++;
		}
		if (this->key[i].hold == 1) {
			this->key[i].ptime = Ntime;
			this->key[i].btime = Ntime + this->hold_time;
		}
		else if (this->key[i].rele == 1) {
			this->key[i].rtime = Ntime;
		}
	}
}

/**
* 指定されたキーの状態を返す
* @return -1:たった今離された, 0: 押していない, 1: たった今押された, 2以上: 長押ししている
*/
int dxcur_key_c::GetKeyState(uint n) {
	if (255 < n) { return -1; }
	if (this->key[n].rele == 1) { return -1; }
	return this->key[n].hold;
}

/**
* たった今押したキーを1個だけ返す。同時押しには対応していない
* @return たった今押したキー
*/
int dxcur_key_c::GetKeyPushOnce(void) {
	for (int i = 0; i < 256; i++) {
		if (this->key[i].hold == 1) {
			return i;
		}
	}
	return -1;
}

/**
* 反応したキーを1個だけ返す。同時押しには対応していない
* @return 反応したキー
*/
int dxcur_key_c::GetKeyPulseOnce(void) {
	DxTime_t Ntime = GetNowCount();
	for (int i = 0; i < 256; i++) {
		if (this->key[i].hold == 1) {
			return i;
		}
		if (this->key[i].hold >= 2) {
			if (this->key[i].btime <= Ntime) {
				this->key[i].btime = Ntime + this->hold_pulse;
				return i;
			}
		}
	}
	return -1;
}

#endif /* dxcur_key_c */

#if 1 /* dxcur_ui_elem_c */

dxcur_ui_elem_c::dxcur_ui_elem_c(int a_left, int a_up, int a_right, int a_down) {
	this->SetPosition(a_left, a_up, a_right, a_down);
}

void dxcur_ui_elem_c::draw(void) const {
	if (this->pic.IsValid()) {
		DrawExtendGraph(this->left, this->up, this->right, this->down, this->pic.handle(), TRUE);
	}
	if (box_en) {
		DrawBox(this->left, this->up, this->right, this->down, box_color, FALSE);
	}
	if (!this->text.empty()) {
		DrawString(this->left, this->up, this->text.c_str(), text_color);
	}
}

void dxcur_ui_elem_c::SetPosition(int a_left, int a_up, int a_right, int a_down) {
	this->left  = min(a_left, a_right);
	this->right = max(a_left, a_right);
	this->up    = min(a_up,   a_down );
	this->down  = max(a_up,   a_down );
}

void dxcur_ui_elem_c::SetPicture(const TCHAR *path) { this->pic.reload(path); }

void dxcur_ui_elem_c::SetPosByPicture(void) {
	if (!this->pic.IsValid()) { return; }
	int sizeX = 0;
	int sizeY = 0;
	if (GetGraphSize(this->pic.handle(), &sizeX, &sizeY) == -1) { return; }
	this->right = this->left + sizeX;
	this->down  = this->up   + sizeY;
}

bool dxcur_ui_elem_c::IsInArea(int x, int y) const {
	return (this->left <= x && x <= this->right && this->up <= y && y <= this->down);
}

#endif /* dxcur_ui_elem_c */

#if 1 /* dxcur_mouse_item_c */

dxcur_mouse_item_c::dxcur_mouse_item_c(void) {
	GetMousePoint(&this->NowMouseX, &this->NowMouseY);
}

dxcur_ui_elem_c &dxcur_mouse_item_c::operator[](size_t n) {
	return this->vec[n];
}

void dxcur_mouse_item_c::AddItem(const dxcur_ui_elem_c &item) {
	this->vec.push_back(item);
}

int dxcur_mouse_item_c::SearchInArea(int x, int y) const {
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec[i].IsInArea(x, y)) { return i; }
	}
	return -1;
}

void dxcur_mouse_item_c::update(void) {
	GetMousePoint(&this->NowMouseX, &this->NowMouseY);
}

void dxcur_mouse_item_c::draw(void) const {
	for (size_t i = 0; i < vec.size(); i++) { vec[i].draw(); }
}

int dxcur_mouse_item_c::GetClickedItemBase(int btn) const {
	int mouseBtn = 0;
	int mouseX   = 0;
	int mouseY   = 0;
	int mouseAct = 0;
	if (GetMouseInputLog2(&mouseBtn, &mouseX, &mouseY, &mouseAct, true) == -1) {
		return -1;
	}
	if (mouseBtn != btn || mouseAct != MOUSE_INPUT_LOG_DOWN) { return -1; }
	return this->SearchInArea(mouseX, mouseY);
}

int dxcur_mouse_item_c::GetClickedItem(void) const {
	return this->GetClickedItemBase(MOUSE_INPUT_LEFT);
}

int dxcur_mouse_item_c::GetRightClickedItem(void) const {
	return this->GetClickedItemBase(MOUSE_INPUT_RIGHT);
}

int dxcur_mouse_item_c::GetMouseOveredItem(void) const {
	return this->SearchInArea(this->NowMouseX, this->NowMouseY);
}

#endif /* dxcur_mouse_item_c */

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
int GetKeyPushOnce(bool update_fg) {
	if (update_fg) { InputAllKeyHold(); }
	for (int i = 0; i < 256; i++) {
		if (keyhold[i] == 1) {
			return i;
		}
	}
	return -1;
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
