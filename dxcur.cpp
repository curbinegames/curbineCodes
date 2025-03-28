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

void DrawLineCurve(int x1, int y1, int x2, int y2, char mode, unsigned int color, int thick) {
	int end = x1 + 10;
	switch (mode) {
	case 1: // lin
		DrawLine(x1, y1, x2, y2, color, thick);
		break;
	case 2: // acc
		for (int i = x1; i <= x2; i += 10) {
			end = mins_2(i + 10, x2);
			DrawLine(i, pals(x1, y1, x2, y2, i), end, pals(x1, y1, x2, y2, end), color, thick);
		}
		break;
	case 3: // dec
		for (int i = x1; i <= x2; i += 10) {
			end = mins_2(i + 10, x2);
			DrawLine(i, pals(x2, y2, x1, y1, i), end, pals(x2, y2, x1, y1, end), color, thick);
		}
		break;
	}
	return;
}
