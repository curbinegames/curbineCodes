/**
 * @file strcur.cpp
 * @brief �����񑀍�ŕ֗��Ȃ��̂��W�߂��R�[�h
 * @author curbine
 * @date 2024/7/19
 * @note �l����Ő��삵�����̂Ȃ̂ŁA�i���͕ۏ؂��܂���B���̃R�[�h���g�p�������Ƃɂ��g���u���̐ӔC�͕������˂܂��B
 */

#pragma once

#include <stdarg.h>
#include <tchar.h>
#include <string.h>
#include "strcur.h"
#include "sancur.h"

/**
 * p1�̐擪��p2�����邩�ǂ����𒲂ׂ�
 * @param[in] p1 �T���ꏊ
 * @param[in] p1size p1�̒����A�z�񐔂Ŏw��
 * @param[in] p2 �T��������
 * @param[in] p2size p2�̒����A�z�񐔂Ŏw��
 * @return int ��������true�A�Ȃ�������false
 */
int strands_2(const TCHAR *p1, size_t p1size, const TCHAR *p2, size_t p2size) {
	for (int i = 0; (i < p1size) && (i < p2size); i++) {
		if (p2[i] == _T('\0')) { break; }
		if (p1[i] != p2[i]) { return false; }
	}
	return true;
}

/**
 * p1����擪a����������
 * @param[out] p1 �Ώۂ̕�����
 * @param[in] size p1�̃T�C�Y
 * @param[in] a ����������
 */
void strmods_2(TCHAR *p1, size_t size, int a) {
	int i;
	TCHAR *p2 = p1;
	for (i = 0; (i < a) && (i < size); i++) {
		if (p1[i] == _T('\0')) {
			p1[0] = _T('\0');
			return;
		}
	}
	for (i = 0; p2[i + a] != _T('\0'); i++) {
		p1[i] = p2[i + a];
	}
	p1[i] = _T('\0');
	return;
}

/**
 * p1�̍Ō��p2��t����
 * @param[out] p1 ������镶����
 * @param[in] size p1�̃T�C�Y�A�z�񐔂Ŏw��
 * @param[in] p2 ����������
 * @note 1���������ǉ��������Ƃ���stradds_2���g���Ă�������
 * @sa stradds_2
 */
void strcats_2(TCHAR p1[], size_t size, const TCHAR *p2) {
	int offset = -1;

	for (int i = 0; i < size; i++) {
		if (p1[i] == _T('\0')) {
			offset = i;
			break;
		}
	}

	if (offset == -1) { return; }

	strcopy_2(p2, &p1[offset], size - offset);

	p1[size - 1] = _T('\0');
	return;
}

/**
 * ������s�̒������擾����
 * @param[in] s �ΏۂƂȂ镶����
 * @param[in] size s�̂̃T�C�Y�A�z�񐔂Ŏw��
 * @return int s�̒���
 */
int strlens_2(const TCHAR* s, size_t size) {
	int ret = 0;
	for (ret = 0; ret < size; ret++) {
		if (s[ret] == _T('\0')) {
			break;
		}
	}
	return ret;
}

/**
 * ������𐔒l�ɕϊ��ɂ���B
 * @param[in] p1 �ϊ����镶����
 * @param[in] size p1�̃T�C�Y�A�z�񐔂Ŏw��
 * @return int �ϊ�����
 * @su strsansD
 * @note �����ȉ��͖�������܂��B�����ȉ����ϊ��������ꍇ��strsansD()���g�p���Ă�������
 * �r���ɐ���,�}�C�i�X�ȊO�̕�������������I���.
 */
int strsans_3(const TCHAR *p1, size_t size) {
	int a = 0, b = 1;

	for (int i = 0; i < size; i++) {
		if (IS_NUMBER_CHAR(*p1)) { a = a * 10 + (*p1 - _T('0')); }
		else if (*p1 == _T('-')) { b *= -1; }
		else { break; }
		p1++;
	}

	return a * b;
}

/**
 * ������𐔒l�ɕϊ��ɂ���B
 * @param[in] p1 �ϊ����镶����
 * @param[in] size p1�̃T�C�Y�A�z�񐔂Ŏw��
 * @return double �ϊ�����
 * @sa strsans_3
 * @note ���̊֐��͏����ȉ����ϊ����܂��B�����݂̂ŗǂ��ꍇ��strsans_3���g�p���Ă��������B
 */
double strsansD(const TCHAR *p1, size_t size) {
	short b = 1, c = 0, d = 99, i;
	double a = 0;

	for (int ip = 0; ip < size; ip++) {
		if (IS_NUMBER_CHAR(*p1)) {
			c++;
			a = a * 10 + (*p1 - _T('0'));
		}
		else if (*p1 == _T('-')) { b *= -1; }
		else if (*p1 == _T('.')) { d = c; }
		else {
			for (i = c; i > d; i--) { a /= 10.0; }
			break;
		}
		p1++;
	}

	return b * a;
}

/**
 * ����'/'��':'������Ƃ���܂ŏ���
 * @param[out] p1 �ΏۂƂȂ镶����
 * @param[in] size p1�̃T�C�Y�A�z�񐔂Ŏw��
 */
void strnex_2(TCHAR *p1, size_t size) {
	int i = 1;
	for (i = 0; (i < size) && IS_NORMAL_CHAR(p1[i]) && p1[i] != _T('/') && p1[i] != _T(':') && p1[i] != _T('\0'); i++) { ; }
	if (p1[i] == _T('/') || p1[i] == _T(':')) { i++; }
	strmods(p1, i);
	return;
}

/**
 * �w��̕���p3������Ƃ���܂ŏ���
 * @param[out] p1 �ΏۂƂȂ镶����
 * @param[in] p3 �w��̕���
 */
void strnex_EX2(TCHAR *p1, size_t size, TCHAR p3) {
	TCHAR *p2 = p1;
	short a = 1;
	for (uint inum = 0; (inum < size) && IS_NORMAL_CHAR(*p1) && *p1 != p3 && *p1 != _T('\0'); inum++) {
		a++;
		p1++;
	}
	strmods(p2, a);
	return;
}

/**
 * p1�̍Ō��a�̕�����ǉ�����
 * @param[out] p1 ������镶����
 * @param[in] size p1�̃T�C�Y�A�z�񐔂Ŏw��
 * @param[in] a ��������
 * @note �������ǉ��������Ƃ���strcats_2���g���Ă�������
 * @sa strcats_2
 */
void stradds_2(TCHAR p1[], size_t size, TCHAR a) {
	int offset = -1;

	for (int i = 0; i < size; i++) {
		if (p1[i] == _T('\0')) {
			offset = i;
			break;
		}
	}

	if (offset == -1) { return; }

	p1[offset] = a;
	p1[offset + 1] = _T('\0');
	p1[size - 1] = _T('\0');
	return;
}

/**
 * ���l�𕶎���ɂ���B�����_�ȉ��͖��������
 * @param[out] ret �ϊ����ꂽ������̊i�[�ꏊ
 * @param[in] val �ϊ����鐔�l
 * @param[in] size ret�̒����B�z�񐔂Ŏw��
 * @note �����_�ȉ���������ɂ������ꍇ��strnumsD���g���Ă�������
 * @sa strnumsD
 */
void strnums(TCHAR ret[], int val, size_t size) {
	int keta = 1;
	int buf = val;
	int minFG = 0;

	if (size < 2) { return; }

	while (buf != 0) {
		buf /= 10;
		if (buf != 0) { keta++; }
	}

	if (val < 0) {
		ret[0] = _T('-');
		minFG = 1;
	}

	keta = mins_2(size - minFG - 1, keta);

	buf = val;
	if (val < 0) { buf *= -1; }

	for (int i = 0; i < keta; i++) {
		ret[minFG + keta - i - 1] = (TCHAR)(_T('0') + buf % 10);
		buf /= 10;
	}

	ret[minFG + keta] = _T('\0');
	ret[size - 1] = _T('\0');

	return;
}

/**
 * ���l�𕶎���ɂ���B�����_�ȉ����ϊ�����
 * @param[out] ret �ϊ����ꂽ������̊i�[�ꏊ
 * @param[in] val �ϊ����鐔�l
 * @param[in] size ret�̒����B�z�񐔂Ŏw��
 * @param[in] under �����_�ȉ��̌���
 * @note �����_�ȉ��𖳎�����ꍇ��strnums���g���Ă�������
 * @sa strnums
 */
void strnumsD(TCHAR ret[], double val, size_t size, int under) {
	int keta = 1;
	int buf = (int)val;
	double bufD = val;
	int minFG = 0;

	strnums(ret, (int)val, size);

	if (under <= 0) { return; }

	stradds_2(ret, size, _T('.'));

	for (int i = 0; i < under; i++) {
		bufD *= 10;
		buf = ((int)bufD) % 10;
		stradds_2(ret, size, (TCHAR)(_T('0') + (int)buf));
	}

	ret[size - 1] = _T('\0');

	return;
}

/**
 * ����Ă邱�Ƃ�vsprintf_s�ƈꏏ�ׁ̈A�킴�킴���̊֐����g���K�v�Ȃ��Bvsprintf_s���g���Ă��������B
 * @param[out] ret �ϊ�������������i�[����ꏊ
 * @param[in] size ret�̑傫���B�z�񐔂Ŏw��
 * @param[in] s �ϊ����镶����
 * @param[in] as valist�̎���
 */
void vScanPrintfStr(TCHAR *ret, size_t size, const TCHAR s[], va_list as) {
	_vstprintf_s(ret, size, s, as);
	return;
}

/**
 * ����Ă邱�Ƃ�sprintf_s�ƈꏏ�ׁ̈A�킴�킴���̊֐����g���K�v�Ȃ��Bsprintf_s���g���Ă��������B
 * @param[out] ret �ϊ�������������i�[����ꏊ
 * @param[in] size ret�̑傫���B�z�񐔂Ŏw��
 * @param[in] s �ϊ����镶����
 */
void ScanPrintfStr(TCHAR *ret, size_t size, const TCHAR s[], ...) {
	va_list as;
	va_start(as, s);
	_vstprintf_s(ret, size, s, as);
	va_end(as);
	return;
}

/**
 * �^����ꂽ�������()���𒊏o����B
 * @param[out] dest ���o����������̊i�[�ꏊ
 * @param[in] size dest�̔z��
 * @param[in] src ���ƂȂ镶����
 * @param[in] c ���o���銇�ʂ̎�ށB�Ή����Ă��銇�ʂ́A(), [], {}, <>�B�����ȕ������w�肳�ꂽ�ꍇ�A()�Ƃ��ď���
 * @details ��: ���� = "qw[cr{tg(iasd]e(knw)asd)v[vur]ne>", �w�蕶�� = '(', �o�� = "iasd]e(knw)asd"
 *          ��: ���� = "qw[cr{tg(iasd]e(knw)asd)v[vur]ne>", �w�蕶�� = '[', �o�� = "cr{tg(iasd"
 *          ��: ���� = "qw[cr{tg(iasd]e(knw)asd)v[vur]ne>", �w�蕶�� = '<', �o�� = ""
 *          ��: ���� = "qw[cr{tg(iasd]e(knw)asd)v[vur]ne>", �w�蕶�� = '{', �o�� = "tg(iasd]e(knw)asd)v[vur]ne>"
 *          ��: ���� = "qw[cr{tg(iasd]e(knw)asd)v[vur]ne>", �w�蕶�� = '3', �o�� = "iasd]e(knw)asd" (�w�蕶���������ׁ̈A'('�Ƃ��ď���)
 */
void strbox(TCHAR dest[], size_t size, const TCHAR src[], TCHAR c) {
	TCHAR sc = _T('(');
	TCHAR ec = _T(')');
	uint count = 1;
	uint srcp = 0;

	switch (c) {
	case _T('['):
	case _T(']'):
		sc = _T('[');
		ec = _T(']');
		break;
	case _T('{'):
	case _T('}'):
		sc = _T('{');
		ec = _T('}');
		break;
	case _T('<'):
	case _T('>'):
		sc = _T('<');
		ec = _T('>');
		break;
	}

	while (src[srcp] != sc) {
		if (src[srcp] == _T('\0')) { return; }
		srcp++;
	}
	srcp++;
	dest[0] = _T('\0');
	while (1) {
		if (src[srcp] == _T('\0')) { return; }
		if (src[srcp] == sc) { count++; }
		if (src[srcp] == ec) { count--; }
		if (count <= 0) { break; }
		stradds_2(dest, size, src[srcp]);
		srcp++;
	}
	return;
}
