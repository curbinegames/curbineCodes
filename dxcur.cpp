#include <DxLib.h>
#include "dxcur.h"
#include "sancur.h"

/* dxcur_fps_c */
void dxcur_fps_c::SetTick() {
	DxTime_t Ntime = GetNowCount();

	this->tick[this->head] = Ntime;
	this->head = (this->head + 1) % 120;
	this->num++;
	while (120 < this->num || 0 < this->num && this->tick[this->tail] + 1000 < Ntime) {
		this->tail = (this->tail + 1) % 120;
		this->num--;
	}
}

uint dxcur_fps_c::GetFPS() {
	return this->num;
}

/* dxcur_snd_c */
dxcur_snd_c::dxcur_snd_c(TCHAR *path) {
	this->mat = LoadSoundMem(path);
}

dxcur_snd_c::~dxcur_snd_c() {
	DeleteSoundMem(this->mat);
}

void dxcur_snd_c::PlaySound() {
	DxTime_t Ntime = GetNowCount();
	if ((this->Btime + this->Gtime) < Ntime) {
		PlaySoundMem(this->mat, DX_PLAYTYPE_BACK);
		this->Btime = Ntime;
	}
}

/*+++*/

static int keyhold[256];

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