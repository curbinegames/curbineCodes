#pragma once

#include <DxLib.h>

/* a/bを返す、ただし、bが0の時はcを返す。0除算回避の為に作った */
#define DIV_AVOID_ZERO(a, b, c) (((b) == 0) ? (c) : ((a) / (b)))

#define LOOP_ADD(mat, loop) (mat) = ((mat) + 1) % (loop)
#define LOOP_SUB(mat, loop) (mat) = ((mat) + (loop) - 1) % (loop)

/* 小さいほうを返す */
#define mins_2(a, b) (((a) < (b)) ? (a) : (b))

/* 大きいほうを返す */
#define maxs_2(a, b) (((a) > (b)) ? (a) : (b))

/* bをaまで引き上げ、cまで引き下げたものを返す */
#define betweens(a, b, c) mins_2(maxs_2((a), (b)), (c))

/* cos"a"を出力する */
#define cosC(a) sinC((a) + 90)

typedef unsigned int uint;
typedef int intx100_t; /** 100倍していることを示すint型 */

typedef enum cur_move_e {
	CUR_MOVE_LINE = 1,
	CUR_MOVE_ACC,
	CUR_MOVE_DEC
} cur_move_type_t;

extern double lins(double x1, double y1, double x2, double y2, double x);
extern double pals(double x1, double y1, double x2, double y2, double x);
extern double movecal(int mode, double x1, double y1, double x2, double y2, double x);
extern double sanrute(double c);
extern int abss(int a, int b);
extern double sinC(int a);
extern void rot_xy_pos(int rot, int *x, int *y);

/* 使用してはいけない関数。過去に使っていたことがあるので、互換のために残す */
#define maxs(a, b) (mins_2((a), (b)))
#define mins(a, b) (maxs_2((a), (b)))
#define mins_D(a, b) maxs_2(a, b)
#define maxs_D(a, b) mins_2(a, b)
#define betweens_D(a, b, c) betweens(a, b, c)
#define notzero(a) ((a) == 0) ? 1 : (a)
extern int NumLoop(int a, int b);
