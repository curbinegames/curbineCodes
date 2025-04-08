#pragma once

/* a/b��Ԃ��A�������Ab��0�̎���c��Ԃ��B0���Z����ׂ̈ɍ���� */
#define DIV_AVOID_ZERO(a, b, c) ( ((b) == 0) ? (c) : ((a) / (b)) )

#define LOOP_ADD(mat, loop) ( ((mat) + 1) % (loop) )
#define LOOP_SUB(mat, loop) ( ((mat) + (loop) - 1) % (loop) )

/* �������ق���Ԃ� */
#define mins_2(a, b) ( ((a) < (b)) ? (a) : (b) )

/* �傫���ق���Ԃ� */
#define maxs_2(a, b) ( ((a) > (b)) ? (a) : (b) )

/* b��a�܂ň����グ�Ac�܂ň������������̂�Ԃ� */
#define betweens(a, b, c) mins_2(maxs_2((a), (b)), (c))

/* cos"a"���o�͂��� */
#define cosC(a) sinC((a) + 90)

/* b��a�ȏ�c�ȉ��Ȃ�true��Ԃ� */
#define IS_BETWEEN(a, b, c)            ( (a) <= (b) && (b) <= (c) )

/* b��a����c�����Ȃ�true��Ԃ� */
#define IS_BETWEEN_LESS(a, b, c)       ( (a) <  (b) && (b) <  (c) )

/* b��a����c�ȉ��Ȃ�true��Ԃ� */
#define IS_BETWEEN_LEFT_LESS(a, b, c)  ( (a) <  (b) && (b) <= (c) )

/* b��a�ȏ�c�����Ȃ�true��Ԃ� */
#define IS_BETWEEN_RIGHT_LESS(a, b, c) ( (a) <= (b) && (b) <  (c) )

/* �������̈Ӑ}�A"="���Ȃ�(LESS���Ă���)����IS_BETWEEN_"LESS" */

/* �z�񐔂�Ԃ� */
#define ARRAY_COUNT(a) ( sizeof(a) / sizeof(a[0]) )

typedef unsigned int uint;
typedef int intx100_t; /** 100�{���Ă��邱�Ƃ�����int�^ */

typedef enum cur_move_e {
	CUR_MOVE_LINE = 1,
	CUR_MOVE_ACC,
	CUR_MOVE_DEC
} cur_move_type_t;

extern double lins(double x1, double y1, double x2, double y2, double x);
extern double pals(double x1, double y1, double x2, double y2, double x);
extern double movecal(int mode, double x1, double y1, double x2, double y2, double x);
extern double sanrute(double c);
extern int    abss(int a, int b);
extern double sinC(int a);
extern void   rot_xy_pos(int rot, int *x, int *y);
extern uint   GetColorFromHSV(int hue, int saturation, int value);
extern uint   GetColorCurRainbow(int hueParam, int saturation, int value);

/* �g�p���Ă͂����Ȃ��֐��B�ߋ��Ɏg���Ă������Ƃ�����̂ŁA�݊��̂��߂Ɏc�� */
#define maxs(a, b)          mins_2((a), (b))
#define mins(a, b)          maxs_2((a), (b))
#define mins_D(a, b)        maxs_2(a, b)
#define maxs_D(a, b)        mins_2(a, b)
#define betweens_D(a, b, c) betweens(a, b, c)
#define notzero(a)          ( ((a) == 0) ? 1 : (a) )
extern int NumLoop(int a, int b);
