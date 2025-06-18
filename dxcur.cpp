#pragma once

#include "DxLib.h"
#include "dxcur.h"
#include "sancur.h"

#undef PlaySound

static int keyhold[256];

/* dxcur_snd_c */
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

void dxcur_snd_c::PlaySound(void) {
	DxTime_t Ntime = GetNowCount();
	if ((this->Btime + this->Gtime) < Ntime) {
		PlaySoundMem(this->mat, DX_PLAYTYPE_BACK);
		this->Btime = Ntime;
	}
}

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

/**
 * �}�E�X�̃L�[���͂̏���Ԃ�
 * @param[out] key ���������{�^���̎��
 * @param[out] posX ��������X�ʒu
 * @param[out] posY ��������y�ʒu
 * @param[out] key �����̎��, 0: ������, 1: ������
 * @return 0�̂�
 */
int GetMouseKeyCur(int* key, int* posX, int* posY, int* PR) {
	while (GetMouseInputLog2(key, posX, posY, PR, true) == 0) {}
	return 0;
}

/**
 * �L�[���͂̃o�O���������֐�
 * @return �Ȃ�
 */
void AvoidKeyRush() {
	for (int i = 0; i < 256; i++) {
		keyhold[i] = 2;
	}
	return;
}

/**
 * �w�肳�ꂽ�L�[�̏�Ԃ�Ԃ�
 * @return 0: �����Ă��Ȃ�, 1: �������������ꂽ, 2�ȏ�: ���������Ă���
 */
int GetKeyHold(int n) {
	return keyhold[n];
}

/**
 * ���������������L�[��1�����Ԃ��B���������ɂ͑Ή����Ă��Ȃ�
 * @return ���������������L�[
 * @note ���̊֐����g�p����O�ɁAInputAllKeyHold�ŃL�[�����X�V���Ă�������
 * @note InputAllKeyHold���g�p���Ȃ��ƁA�O��Ɠ����l���Ԃ�܂�
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
 * �L�[�����X�V����
 * @return �Ȃ�
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
 * ���͂����������Ȃ��֐��B�g�p���Ă���ꏊ�����邽�ߎc���Ă���
 * @return �Ȃ�
 */
void AvoidKeyBug() {
	/* nop */
}

/**
 * ���̊֐��͂����Â��̂ŁA�����InputAllKeyHold(),GetKeyPushOnce()���g���Ă��������B
 * @param[in] mat ���g�p
 * @param[in] num ���g�p
 * @return ���������������L�[
 * @details ���������������L�[��1�����Ԃ��B���������ɂ͑Ή����Ă��Ȃ�
 */
int keycur(int const* const mat, int num) {
	InputAllKeyHold();
	return GetKeyPushOnce();
}

/* TODO: �]�T������΃x�W�G��� */

/**
 * TODO: �֐��R�����g����
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
