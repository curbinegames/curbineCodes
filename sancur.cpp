/**
 * @file sancur.cpp
 * @brief ���l�v�Z�ŕ֗��Ȃ��̂��W�߂��R�[�h
 * @author curbine
 * @date 2024/7/19
 * @note �l����Ő��삵�����̂Ȃ̂ŁA�i���͕ۏ؂��܂���B���̃R�[�h���g�p�������Ƃɂ��g���u���̐ӔC�͕������˂܂��B
 */

#include "sancur.h"

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
	double a = 0;
	double b = 1;

	while (b * b < c) { b *= 10; }
	if (b * b == c) { return b; }
	b /= 10;
	for (uint i = 0; i < 10; i++) {
		while (a * a < c) { a += b; }
		if (a * a == c) { return a; }
		a -= b;
		b /= 10;
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
 * sin"a"���o�͂���
 * @param[in] a ����
 * @return double sin(a)
 */
double sinC(int a) {
	double sin[91] = { 0.0000,0.0175,0.0349,0.0523,0.0698,
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
		0.9962,0.9976,0.9986,0.9994,0.9998,1.0000 };
	while (a < 0) { a += 360; }
	while (a >= 360) { a -= 360; }
	if (91 <= a && a <= 179) { return sin[-(a - 180)]; }
	if (180 <= a && a <= 270) { return -sin[a - 180]; }
	if (271 <= a && a <= 359) { return -sin[-(a - 360)]; }
	return sin[a];
}

/**
 * �_(x, y)���@���_(0, 0)�𒆐S��rot�x�E��]������
 * @param[out] x x���W
 * @param[out] y y���W
 * @param[in] rot �p�x
 */
void rot_xy_pos(int rot, int *x, int *y) {
	int G = *x;
	*x = *x * cosC(rot) - *y * sinC(rot);
	*y = G * sinC(rot) + *y * cosC(rot);
	return;
}

/**
* HSV����F���擾����
* @param[in] hue �F�� 0~360
* @param[in] saturation �ʓx 0~100
* @param[in] value ���x 0~100
* @return DxColor_t RGB���
*/
uint GetColorFromHSV(int hue, int saturation, int value) {
	int r = 0;
	int g = 0;
	int b = 0;

	saturation = betweens(0, saturation, 100);
	value = betweens(0, value, 100);
	hue = hue % 360;

	const int scaleHigh = lins(  0, 0, 100,       255, value);
	const int scaleLow  = lins(100, 0,   0, scaleHigh, saturation);

	if (IS_BETWEEN(0, hue, 60)) {
		r = 0xff;
		g = lins(0, 0x00, 60, 0xff, hue);
		b = 0x00;
	}
	else if (IS_BETWEEN(60, hue, 120)) {
		r = lins(60, 0xff, 120, 0x00, hue);
		g = 0xff;
		b = 0x00;
	}
	else if (IS_BETWEEN(120, hue, 180)) {
		r = 0x00;
		g = 0xff;
		b = lins(120, 0x00, 180, 0xff, hue);
	}
	else if (IS_BETWEEN(180, hue, 240)) {
		r = 0x00;
		g = lins(180, 0xff, 240, 0x00, hue);
		b = 0xff;
	}
	else if (IS_BETWEEN(240, hue, 300)) {
		r = lins(240, 0x00, 300, 0xff, hue);
		g = 0x00;
		b = 0xff;
	}
	else if (IS_BETWEEN(300, hue, 360)) {
		r = 0xff;
		g = 0x00;
		b = lins(300, 0xff, 360, 0x00, hue);
	}

	r = lins(0, scaleLow, 255, scaleHigh, r);
	g = lins(0, scaleLow, 255, scaleHigh, g);
	b = lins(0, scaleLow, 255, scaleHigh, b);

	return ( (r << 16) | (g << 8) | (b) );
}

/**
* curbine���l�I���Y�킾�Ǝv�����F���o�͂���
* @param[in] hueParam �F���p�����[�^ 0~255 �f�W�^���ł悭�����F���Ƃ͈Ⴄ�B
*                0�ŐԁA16�ŃI�����W�A64�ŉ��F�A96�ŗ΁A112�Ő��F�A192�ŐA240�Ŏ�
* @param[in] saturation �ʓx 0~100
* @param[in] value ���x 0~100
* @return DxColor_t RGB���
*/
uint GetColorCurRainbow(int hueParam, int saturation, int value) {
	/*                             0      32      64       96       128       160       192       224       256 */
	static const int table[17] = { 0, 30, 40, 50, 60, 90, 120, 150, 180, 190, 200, 215, 240, 278, 290, 300, 360 };
	int h = 0;
	int s = 100;
	int v = 100;

	hueParam = hueParam % 256;

	for (uint iSect = 0; iSect < 16; iSect++) {
		if (IS_BETWEEN(16 * iSect, hueParam, 16 * iSect + 16)) {
			h = lins(16 * iSect, table[iSect], 16 * iSect + 16, table[iSect + 1], hueParam);
			break;
		}
	}

	if (IS_BETWEEN(60, h, 120)) {
		int max_value = lins(60, 100, 120,  75, h);
		v = lins(0, 0, 100, max_value, value);
	}
	else if (IS_BETWEEN(120, h, 180)) {
		int max_value = lins(120, 75, 180, 100, h);
		v = lins(0, 0, 100, max_value, value);
	}

	s = saturation;

	return GetColorFromHSV(h, s, v);
}

#if 1 /* cur_deviation_c */

void cur_deviation_c::add(int val) {
	this->view[this->head] = val;
	if (0x7fffffff < (double)(this->ssum) + val * val) {
		this->sum   /= 2;
		this->ssum  /= 2;
		this->count /= 2;
	}
	this->sum += val;
	this->ssum += val * val;
	this->count++;
	this->head = LOOP_ADD(this->head, 30);
	return;
}

int cur_deviation_c::GetHead(void) const {
	return this->head;
}

int cur_deviation_c::GetList(uint num) const {
	num = betweens(0, num, 29);
	return this->view[num];
}

int cur_deviation_c::GetAverage(void) const {
	if (this->count == 0) { return 0; }
	return this->sum / this->count;
}

int cur_deviation_c::GetDeviation(void) const {
	if (this->count == 0) { return 0; }
	return sanrute((this->ssum * this->count - this->sum * this->sum) / (this->count * this->count));
}

#endif /* cur_deviation_c */
