/**
 * @file strcur.h
 * @brief �����񑀍�ŕ֗��Ȃ��̂��W�߂��R�[�h
 * @author curbine
 * @date 2025/2/17
 * @note �l����Ő��삵�����̂Ȃ̂ŁA�i���͕ۏ؂��܂���B���̃R�[�h���g�p�������Ƃɂ��g���u���̐ӔC�͕������˂܂��B
 */

#pragma once

#include <string.h>
#include <tchar.h>

/* p1��p2�ɃR�s�[���� */
#define strcopy_2(p1, p2, size) _tcscpy_s(p2, size, p1)

/* strands_2�֐��̈���p2�𒼐ڎw�肷�鎞�Ɏg����}�N�� */
#define strands_direct(p1, p2) strands_2(p1, sizeof(p2) / sizeof(TCHAR), p2, sizeof(p2) / sizeof(TCHAR))

/* ����c�������ł����TRUE��Ԃ� */
#define IS_NUMBER_CHAR(c) (IS_BETWEEN(_T('0'), (c), _T('9')))

/* ����c�������ł����TRUE��Ԃ� */
#define IS_NORMAL_CHAR(c) (IS_BETWEEN(_T(' '), (c), _T('~')))

extern int strands_2(const TCHAR *p1, size_t p1size, const TCHAR *p2, size_t p2size);
extern void strmods_2(TCHAR *p1, size_t size, int a);
extern void strcats_2(TCHAR p1[], size_t size, const TCHAR *p2);
extern int strlens_2(const TCHAR* s, size_t size);
extern int strsans_3(const TCHAR *p1, size_t size);
extern double strsansD(const TCHAR *p1, size_t size);
extern void strnex_2(TCHAR *p1, size_t size);
extern void strnex_EX2(TCHAR *p1, size_t size, TCHAR p3);
extern void stradds_2(TCHAR p1[], size_t size, TCHAR a);
extern void strnums(TCHAR ret[], int val, size_t size);
extern void strnumsD(TCHAR ret[], double val, size_t size, int under);
extern void vScanPrintfStr(TCHAR *ret, size_t size, const TCHAR s[], va_list as);
extern void ScanPrintfStr(TCHAR *ret, size_t size, const TCHAR s[], ...);
extern int strrans(const TCHAR *p1);
extern void strbox(TCHAR dest[], size_t size, const TCHAR src[], TCHAR c);

/* �g�p���Ă͂����Ȃ��֐��B�ߋ��Ɏg���Ă������Ƃ�����̂ŁA�݊��̂��߂Ɏc�� */
#define strcopy(p1, p2, c) _tcscpy_s(p2, 255, p1)
#define strands(p1, p2) strands_2(p1, 64, p2, 64)
#define strmods(p1, a) strmods_2(p1, 255, a)
#define strcats(p1, p2) strcats_2(p1, 255, p2)
#define strlens(s) strlens_2(s, 255)
#define strsans(p1) strsans_3(p1, 255)
#define strsans2(p1) strsansD(p1, 255)
#define strnex(p1) strnex_2(p1, 255)
#define strnex_EX(p1, p3) strnex_EX2(p1, 255, p3)
#define stradds(p1, a) stradds_2(p1, 255, a)
