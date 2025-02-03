#pragma once

#include "dxcur.h"
#include "sancur.h"

/** dxdraw�Ŏg����_�̗񋓌^ */
typedef enum dxdraw_anchor_e {
	DXDRAW_ANCHOR_TOP_LEFT = 0,  /** ��̍� */
	DXDRAW_ANCHOR_TOP_CENTRE,    /** ��̐^�� */
	DXDRAW_ANCHOR_TOP_RIGHT,     /** ��̉E */
	DXDRAW_ANCHOR_CENTRE_LEFT,   /** �^�񒆂̍� */
	DXDRAW_ANCHOR_CENTRE,        /** �^�� */
	DXDRAW_ANCHOR_CENTRE_RIGHT,  /** �^�񒆂̉E */
	DXDRAW_ANCHOR_BOTTOM_LEFT,   /** ���̍� */
	DXDRAW_ANCHOR_BOTTOM_CENTRE, /** ���̐^�� */
	DXDRAW_ANCHOR_BOTTOM_RIGHT,  /** ���̉E */
} dxdraw_anchor_t;

extern void DrawGraphAnchor(int x, int y, int pic, dxdraw_anchor_t anchor);
extern void DrawZoomGraphAnchor(int x, int y, intx100_t size, int pic, dxdraw_anchor_t anchor);
extern void DrawRotaGraphAnchor(int x, int y, double size, double rot, DxPic_t pic, dxdraw_anchor_t anchor, int TransFlag, int ReverseXFlag = 0, int ReverseYFlag = 0);
extern void DrawStringAnchor(int x, int y, const TCHAR *s, DxColor_t cr, dxdraw_anchor_t anchor);
extern void DrawStringToHandleAnchor(int x, int y, const TCHAR *s, DxColor_t cr, int handle, dxdraw_anchor_t anchor);
extern void DrawFormatStringAnchor(int x, int y, DxColor_t cr, dxdraw_anchor_t anchor, const TCHAR *s, ...);
extern void DrawFormatStringToHandleAnchor(int x, int y, DxColor_t cr, int handle, dxdraw_anchor_t anchor, const TCHAR *s, ...);
extern void DrawDeformationPic(int x, int y, double sizeX, double sizeY, int rot, int handle);
