#pragma once

#include "DxLib.h"
#include "../RecWindowRescale.h"

int mins(int a, int b);
int maxs(int a, int b);
double mins_D(double a, double b);
double maxs_D(double a, double b);
int betweens(int a, int b, int c);
double betweens_D(double a, double b, double c);
int notzero(int a);
int lins(double x1, double y1, double x2, double y2, double x);
int pals(double x1, double y1, double x2, double y2, double x);
double movecal(int mode, double x1, double y1, double x2, double y2, double x);
double sanrute(double c);
int abss(int a, int b);
int NumLoop(int a, int b);
double sinC(int a);
double cosC(int a);
void rot_xy_pos(int rot, int *x, int *y);
void DrawFixPic(int x1, int y1, int x2, int y2, int pic);
void DrawDeformationPic(int x, int y, double sizeX, double sizeY, int rot, int handle);
void _DrawDeformationPic1(int x, int y, int handle);
void _DrawDeformationPic4(int x, int y, double sizeX, double sizeY, int handle);
void _DrawDeformationPic3(int x, int y, double size, int rot, int handle);
void _DrawDeformationPic2(int x, int y, double sizeX, double sizeY, int rot, int handle);

/**
 * ���̊֐��͂����g������_���A�����mins_2���g���Ă�������
 * �傫���ق���Ԃ�
 */
int mins(int a, int b) {
	if (a < b)a = b;
	return a;
}

/**
 * �������ق���Ԃ�
 */
int mins_2(int a, int b) {
	if (a > b) {
		return b;
	}
	return a;
}

/**
 * ���̊֐��͂����g������_���A�����maxs_2���g���Ă�������
 * �������ق���Ԃ�
 */
int maxs(int a, int b) {
	if (a > b)a = b;
	return a;
}

/**
 * �傫���ق���Ԃ�
 */
int maxs_2(int a, int b) {
	if (a < b) {
		return b;
	}
	return a;
}

//a��b�܂ň����グ�����̂�Ԃ�
double mins_D(double a, double b) {
	if (a < b)a = b;
	return a;
}
//a��b�܂ň������������̂�Ԃ�
double maxs_D(double a, double b) {
	if (a > b)a = b;
	return a;
}
//b��a�܂ň����グ�Ac�܂ň������������̂�Ԃ�
int betweens(int a, int b, int c) {
	if (a > b) { return a; }
	if (b > c) { return c; }
	return b;
}
//b��a�܂ň����グ�Ac�܂ň������������̂�Ԃ�
double betweens_D(double a, double b, double c) {
	if (a > b) { return a; }
	if (b > c) { return c; }
	return b;
}
//a��0��������1�ɂ���
int notzero(int a) {
	if (a == 0)a = 1;
	return a;
}
//�_1(x1,y1)�A�_2(x2,y2)�A��ʂ钼�����l���āAx�̎��̒l��Ԃ��B
int lins(double x1, double y1, double x2, double y2, double x) {
	if (x1 == x2) return x1;
	else return (y2 - y1) / (x2 - x1) * (x - x1) + y1;
}
//���_(x1,y1)�A�_(x2,y2)�A��ʂ�񎟊֐����l���āAx�̎��̒l��Ԃ��B
int pals(double x1, double y1, double x2, double y2, double x) {
	if (x1 == x2) return x1;
	else return (y2 - y1) / (x2 - x1) / (x2 - x1) * (x - x1) * (x - x1) + y1;
}
//mode(1:lin,2:acc,3:dec)�ɍ��킹���v�Z������B
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
//���[�gc��Ԃ�(�Ő؂�덷����)
double sanrute(double c) {
	short int d = 10;
	double a = 0, b = 1;
	while (b * b < c) b *= 10;
	if (b * b == c) return b;
	b /= 10;
	while (b >= 100000 || d == -10) {
		while (a * a < c) a += b;
		if (a * a == c) return a;
		a -= b;
		b /= d;
		if (b == 1) d *= -1;
	}
	return a;
}
//a��b�̐�Βl�����߂�
int abss(int a, int b) {
	a -= b;
	if (a < 0) {
		a *= -1;
	}
	return a;
}
//a��0����b�Ń��[�v������
int NumLoop(int a, int b) {
	while (a < 0) { a += b; }
	while (a > b) { a -= b; }
	return a;
}
//sin"a"���o�͂���
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
	while (a < 0) {
		a += 360;
	}
	while (a >= 360) {
		a -= 360;
	}
	if (91 <= a && a <= 179) {
		return sin[-(a - 180)];
	}
	if (180 <= a && a <= 270) {
		return -sin[a - 180];
	}
	if (271 <= a && a <= 359) {
		return -sin[-(a - 360)];
	}
	return sin[a];
}
//cos"a"���o�͂���
double cosC(int a) {
	a += 90;
	return sinC(a);
}

void rot_xy_pos(int rot, int *x, int *y) {
	int G = *x;
	*x = *x * cosC(rot) - *y * sinC(rot);
	*y = G * sinC(rot) + *y * cosC(rot);
}

void DrawFixPic(int x1, int y1, int x2, int y2, int pic) {
	int SizeX = 640;
	int SizeY = 480;
	int CSizeX = mins(x2 - x1, 2);
	int CSizeXHalf = CSizeX / 2;
	int CSizeY = mins(y2 - y1, 2);
	int CSizeYHalf = CSizeY / 2;
	double ratio = double(x2 - x1) / double(y2 - y1);
	if (ratio < 0.01) {
		ratio = 0.01;
	}
	GetGraphSize(pic, &SizeX, &SizeY);
	if (SizeX / ratio >= SizeY) {
		RecRescaleDrawExtendGraph(
			x1,
			CSizeYHalf - CSizeYHalf * SizeY * ratio / SizeX + y1,
			CSizeX + x1,
			CSizeYHalf + CSizeYHalf * SizeY * ratio / SizeX + y1, pic, TRUE
		);
	}
	else {
		RecRescaleDrawExtendGraph(
			CSizeXHalf - CSizeXHalf * SizeX / ratio / SizeY + x1,
			y1,
			CSizeXHalf + CSizeXHalf * SizeX / ratio / SizeY + x1,
			CSizeY + y1, pic, TRUE
		);
	}
	return;
}

void DrawDeformationPic(int x, int y, double sizeX, double sizeY, int rot, int handle) {
	if (sizeX == 1 && sizeY == 1 && rot % 360 == 0) {
		_DrawDeformationPic1(x, y, handle);
	}
	else if ((sizeX != 1 || sizeY != 1) && rot % 360 == 0) {
		_DrawDeformationPic4(x, y, sizeX, sizeY, handle);
	}
	else if (sizeX == sizeY && rot % 360 != 0) {
		_DrawDeformationPic3(x, y, sizeX, rot, handle);
	}
	else {
		_DrawDeformationPic2(x, y, sizeX, sizeY, rot, handle);
	}
	return;
}

void _DrawDeformationPic1(int x, int y, int handle) {
	int PSizeX = 1;
	int PSizeY = 1;
	GetGraphSize(handle, &PSizeX, &PSizeY);
	x -= PSizeX / 2;
	y -= PSizeY / 2;
	RecRescaleDrawGraph(x, y, handle, TRUE);
	return;
}

void _DrawDeformationPic4(int x, int y, double sizeX, double sizeY, int handle) {
	int TSizeX = 1;
	int TSizeY = 1;
	GetGraphSize(handle, &TSizeX, &TSizeY);
	TSizeX *= sizeX;
	TSizeY *= sizeY;
	int pos[4] = {
		x - TSizeX / 2, y - TSizeY / 2, 0, 0
	};
	pos[2] = pos[0] + TSizeX + 1;
	pos[3] = pos[1] + TSizeY + 1;
	RecRescaleDrawExtendGraph(pos[0], pos[1], pos[2], pos[3], handle, TRUE);
	return;
}

void _DrawDeformationPic3(int x, int y, double size, int rot, int handle) {
	int PSizeX = 1;
	int PSizeY = 1;
	GetGraphSize(handle, &PSizeX, &PSizeY);
	PSizeX /= 2;
	PSizeY /= 2;
	DrawRotaGraph2(x, y, PSizeX, PSizeY, size, 3.14 * rot / 180, handle, TRUE);
	return;
}

void _DrawDeformationPic2(int x, int y, double sizeX, double sizeY, int rot, int handle) {
	int TSizeX = 1;
	int TSizeY = 1;
	GetGraphSize(handle, &TSizeX, &TSizeY);
	int PSizeX = TSizeX / 2;
	int PSizeY = TSizeY / 2;
	int pos[8] = {
		-PSizeX * sizeX, -PSizeY * sizeY,
		PSizeX * sizeX, -PSizeY * sizeY,
		PSizeX * sizeX, PSizeY * sizeY,
		-PSizeX * sizeX, PSizeY * sizeY
	};
	int G = 0;
	for (int i = 0; i < 8; i += 2) {
		G = pos[i];
		pos[i] = pos[i] * cosC(rot) - pos[i + 1] * sinC(rot) + x;
		pos[i + 1] = G * sinC(rot) + pos[i + 1] * cosC(rot) + y;
	}
	DrawModiGraph(pos[0], pos[1], pos[2], pos[3], pos[4], pos[5], pos[6], pos[7], handle, TRUE);
	return;
}
