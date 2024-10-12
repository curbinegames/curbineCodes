/**
 * @file sancur.cpp
 * @brief ���l�v�Z�ŕ֗��Ȃ��̂��W�߂��R�[�h
 * @author curbine
 * @date 2024/7/19
 * @note �l����Ő��삵�����̂Ȃ̂ŁA�i���͕ۏ؂��܂���B���̃R�[�h���g�p�������Ƃɂ��g���u���̐ӔC�͕������˂܂��B
 */

#include <stdbool.h>
#include "sancur.h"

/**
 * �������ق���Ԃ�
 * @param[in] a ����1
 * @param[in] b ����2
 * @return int �������ق��̐��l
 */
int mins_2(int a, int b) {
	if (a > b) { return b; }
	return a;
}

/**
 * �{����max�֐��Ɨp�r���t�ׁ̈A���̊֐��͂����g������_���A�����mins_2���g���Ă�������
 * @param[in] a ����1
 * @param[in] b ����2
 * @return int �������ق��̐��l
 * @details �������ق���Ԃ�
 */
int maxs(int a, int b) {
	return mins_2(a, b);
}

/**
 * �傫���ق���Ԃ�
 * @param[in] a ����1
 * @param[in] b ����2
 * @return int �傫���ق��̐��l
 */
int maxs_2(int a, int b) {
	if (a < b) { return b; }
	return a;
}

/**
 * �{����min�֐��Ɨp�r���t�ׁ̈A���̊֐��͂����g������_���A�����maxs_2���g���Ă�������
 * @param[in] a ����1
 * @param[in] b ����2
 * @return int �傫���ق��̐��l
 * @details �傫���ق���Ԃ�
 */
int mins(int a, int b) {
	return maxs_2(a, b);
}

/**
 * a��b�܂ň����グ�����̂�Ԃ�
 * @param[in] a ����1
 * @param[in] b ����2
 * @return double �傫���ق��̐��l
 */
double mins_D(double a, double b) {
	if (a < b) { a = b; }
	return a;
}

/**
 * a��b�܂ň������������̂�Ԃ�
 * @param[in] a ����1
 * @param[in] b ����2
 * @return double �������ق��̐��l
 */
double maxs_D(double a, double b) {
	if (a > b) { a = b; }
	return a;
}

/**
 * b��a�܂ň����グ�Ac�܂ň������������̂�Ԃ�
 * @param[in] a ����
 * @param[in] b �������鐔�l
 * @param[in] c ���
 * @return int a�ň����グ�Ac�ň���������b
 */
int betweens(int a, int b, int c) {
	if (a > b) { return a; }
	if (b > c) { return c; }
	return b;
}

/**
 * b��a�܂ň����グ�Ac�܂ň������������̂�Ԃ�
 * @param[in] a ����
 * @param[in] b �������鐔�l
 * @param[in] c ���
 * @return double a�ň����グ�Ac�ň���������b
 */
double betweens_D(double a, double b, double c) {
	if (a > b) { return a; }
	if (b > c) { return c; }
	return b;
}

/**
 * a��0��������1�ɂ���
 * @param[in] a �������鐔�l
 * @return int a��0��������1, ����ȊO�Ȃ�a
 */
int notzero(int a) {
	if (a == 0) { a = 1; }
	return a;
}

/**
 * a / b ��Ԃ��B������b��0�������ꍇ��c��Ԃ��B
 * @param[in] a �����鐔
 * @param[in] b ���鐔
 * @param[in] c 0���莞�̕Ԃ�l
 * @return int a / b, 0���莞��c
 */
#define divzero(a, b, c) (((b) == 0) ? (c) : ((a) / (b)))

/**
 * �_1(x1,y1)�A�_2(x2,y2)�A��ʂ钼�����l���āAx�̎��̒l��Ԃ��B
 * @param[in] x1 �_1��x���W
 * @param[in] y1 �_1��y���W
 * @param[in] x2 �_2��x���W
 * @param[in] y2 �_2��y���W
 * @param[in] x �]������l
 * @return double �_1(x1,y1)�A�_2(x2,y2)�A��ʂ钼�����l��������x�̒l
 */
double lins(double x1, double y1, double x2, double y2, double x) {
	if (x1 == x2) { return x1; }
	return (y2 - y1) * (x - x1) / (x2 - x1) + y1;
}

/**
 * ���_(x1,y1)�A�ʉߓ_(x2,y2)�A��ʂ�񎟊֐����l���āAx�̎��̒l��Ԃ��B
 * @param[in] x1 ���_��x���W
 * @param[in] y1 ���_��y���W
 * @param[in] x2 �ʉߓ_��x���W
 * @param[in] y2 �ʉߓ_��y���W
 * @param[in] x �]������l
 * @return double ���_(x1,y1)�A�ʉߓ_(x2,y2)��ʂ�񎟊֐����l��������x�̒l
 */
double pals(double x1, double y1, double x2, double y2, double x) {
	double s1 = 0;
	double s2 = 0;
	if (x1 == x2) { return x1; }
	s1 = x - x1;
	s2 = x2 - x1;
	return (y2 - y1) * s1 * s1 / (s2 * s2) + y1;
}

/**
 * mode(1:lin,2:acc,3:dec)�ɍ��킹���v�Z������B
 * @param[in] mode ���̎��
 * @param[in] x1 �n�_��x���W
 * @param[in] y1 �n�_��y���W
 * @param[in] x2 �I�_��x���W
 * @param[in] y2 �I�_��y���W
 * @param[in] x �]������l
 * @return double �n�_(x1,y1)�A�I�_(x2,y2)��mode�@�Œʂ�����l��������x�̒l
 */
double movecal(int mode, double startx, double starty, double endx, double endy, double nowx) {
	switch (mode) {
	case 1:
		return lins(startx, starty, endx, endy, nowx);
	case 2:
		return pals(startx, starty, endx, endy, nowx);
	case 3:
		return pals(endx, endy, startx, starty, nowx);
	default:
		return 0;
	}
}

/**
 * ���[�gc��Ԃ�
 * @param[in] c �]������l
 * @return double ���[�g(c)
 */
double sanrute(double c) {
	short int d = 10;
	double a = 0, b = 1;
	while (b * b < c) { b *= 10; }
	if (b * b == c) { return b; }
	b /= 10;
	while (b >= 100000 || d == -10) {
		while (a * a < c) { a += b; }
		if (a * a == c) { return a; }
		a -= b;
		b /= d;
		if (b == 1) { d *= -1; }
	}
	return a;
}

/**
 * a��b�̍��̐�Βl�����߂�
 * @param[in] a ����1
 * @param[in] b ����2
 * @return int |a-b|
 */
int abss(int a, int b) {
	a -= b;
	if (a < 0) { a *= -1; }
	return a;
}

/**
 * a��0����b�Ń��[�v������
 * @param[in] a �]������l
 * @param[in] b �ő�l
 * @return int a % (b + 1)
 * @note ���̊֐��͎g���K�v�Ȃ��B���Z�q�Ŋ撣���Ă��������B
 */
int NumLoop(int a, int b) {
	while (a < 0) { a += b; }
	while (a > b) { a -= b; }
	return a;
}

/**
 * sin(a)���o�͂���B�P�ʂ�deg
 * @param[in] a ����
 * @return double sin(a)
 */
double sinC(int a) {
	bool minFg = false;
	double ret = 0;
	double sin[91] = {
		0.0000,0.0175,0.0349,0.0523,0.0698,
		0.0872,0.1045,0.1219,0.1392,0.1564,
		0.1736,0.1908,0.2079,0.2250,0.2419,
		0.2588,0.2756,0.2924,0.3090,0.3256,
		0.3420,0.3584,0.3746,0.3907,0.4067,
		0.4226,0.4384,0.4540,0.4695,0.4848,
		0.5000,0.5150,0.5299,0.5446,0.5592,
		0.5736,0.5878,0.6018,0.6157,0.6293,
		0.6428,0.6561,0.6691,0.6820,0.6947,
		0.7071,0.7193,0.7314,0.7431,0.7547,
		0.7660,0.7771,0.7880,0.7986,0.8090,
		0.8192,0.8290,0.8387,0.8480,0.8572,
		0.8660,0.8746,0.8829,0.8910,0.8988,
		0.9063,0.9135,0.9205,0.9272,0.9336,
		0.9397,0.9455,0.9511,0.9563,0.9613,
		0.9659,0.9703,0.9744,0.9781,0.9816,
		0.9848,0.9877,0.9903,0.9925,0.9945,
		0.9962,0.9976,0.9986,0.9994,0.9998,1.0000
	};

	/* a -> -359~359 */
	a %= 360;
	/* a -> 0~359 */
	if (a < 0) {
		a += 360;
	}
	/* a -> 0~179 */
	if (180 <= a) {
		a -= 180;
		minFg = true;
	}
	/* a -> 0~90 */
	if (90 < a) {
		a = 180 - a;
	}

	return (minFg ? -1 : 1) * sin[a];
}

/**
 * cos(a)���o�͂���B�P�ʂ�deg
 * @param[in] a ����
 * @return double cos(a)
 */
double cosC(int a) {
	return sinC(a + 90);
}

/**
 * �_(x, y)���@���_(0, 0)�𒆐S��rot�x�E��]������
 * @param[in] rot �p�x
 * @param[out] x x���W
 * @param[out] y y���W
 */
void rot_xy_pos(int rot, int *x, int *y) {
	int G = *x;
	*x = *x * cosC(rot) - *y * sinC(rot);
	*y = G * sinC(rot) + *y * cosC(rot);
	return;
}