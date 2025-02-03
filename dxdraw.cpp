
#include "DxLib.h"
#include "dxdraw.h"
#include "dxcur.h"
#include "sancur.h"
#include "strcur.h"
#include "system.h"

void DrawBoxAnchor(int left, int up, int right, int down, uint color, dxdraw_anchor_t anchor, int FillFg) {
	int drawX = left;
	int drawY = up;
	int sizeX = right - left;
	int sizeY = down - up;

	if (anchor == DXDRAW_ANCHOR_TOP_LEFT) {
		DrawBox(left, up, right, down, color, FillFg);
		return;
	}

	switch (anchor) {
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
		drawX = left;
		break;
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
		drawX = (WINDOW_SIZE_X - sizeX + 2 * left) / 2;
		break;
	case DXDRAW_ANCHOR_TOP_RIGHT:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawX = WINDOW_SIZE_X + left;
		break;
	}

	switch (anchor) {
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_TOP_RIGHT:
		drawY = up;
		break;
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
		drawY = (WINDOW_SIZE_Y - sizeY + 2 * up) / 2;
		break;
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawY = WINDOW_SIZE_Y + up;
		break;
	}

	DrawBox(drawX, drawY, drawX + sizeX, drawY + sizeY, color, FillFg);

	return;
}

/**
 * DrawGraph�Ɋ�_��ǉ���������
 * @param[in] x x�ʒu
 * @param[in] y y�ʒu
 * @param[in] pic �摜�n���h��
 * @param[in] anchor ��_
 * @details DrawGraphAnchor(xxx, xxx, xxx, DXDRAW_ANCHOR_TOP_LEFT)��DrawGraph(xxx,xxx,xxx,TRUE)�Ɠ����B
 */
void DrawGraphAnchor(int x, int y, int pic, dxdraw_anchor_t anchor) {
	int drawX = 0;
	int drawY = 0;
	int sizeX = 0;
	int sizeY = 0;

	if (anchor == DXDRAW_ANCHOR_TOP_LEFT) {
		DrawGraph(x, y, pic, TRUE);
		return;
	}

	GetGraphSize(pic, &sizeX, &sizeY);

	switch (anchor) {
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
		drawX = x;
		break;
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
		drawX = (WINDOW_SIZE_X - sizeX + 2 * x) / 2;
		break;
	case DXDRAW_ANCHOR_TOP_RIGHT:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawX = WINDOW_SIZE_X - sizeX + x;
		break;
	}

	switch (anchor) {
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_TOP_RIGHT:
		drawY = y;
		break;
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
		drawX = (WINDOW_SIZE_Y - sizeY + 2 * y) / 2;
		break;
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawY = WINDOW_SIZE_Y - sizeY + y;
		break;
	}

	DrawGraph(drawX, drawY, pic, TRUE);

	return;
}

/**
 * DrawGraphAnchor�Ɋg��ʂ�ǉ���������
 * @param[in] x x�ʒu
 * @param[in] y y�ʒu
 * @param[in] size �g��ʁA100�œ��{
 * @param[in] pic �摜�n���h��
 * @param[in] anchor ��_
 * @details size��100���������ꍇ�ADrawGraphAnchor�����s����
 */
void DrawZoomGraphAnchor(int x, int y, intx100_t size, int pic, dxdraw_anchor_t anchor) {
	int drawLeft = 0;
	int drawUp = 0;
	int drawRight = 0;
	int drawDown = 0;
	int sizeX = 0;
	int sizeY = 0;

	if (size == 100) {
		DrawGraphAnchor(x, y, pic, anchor);
		return;
	}

	GetGraphSize(pic, &sizeX, &sizeY);
	sizeX = sizeX * size / 100;
	sizeY = sizeY * size / 100;

	switch (anchor) {
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
		drawLeft = x;
		break;
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
		drawLeft = (WINDOW_SIZE_X - sizeX + 2 * x) / 2;
		break;
	case DXDRAW_ANCHOR_TOP_RIGHT:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawLeft = WINDOW_SIZE_X - sizeX + x;
		break;
	}
	drawRight = x + sizeX;

	switch (anchor) {
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_TOP_RIGHT:
		drawUp = y;
		break;
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
		drawUp = (WINDOW_SIZE_Y - sizeY + 2 * y) / 2;
		break;
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawUp = WINDOW_SIZE_Y - sizeY + y;
		break;
	}
	drawDown = x + sizeX;

	DrawExtendGraph(drawLeft, drawUp, drawRight, drawDown, pic, TRUE);

	return;
}

void DrawRotaGraphAnchor(int x, int y, double size, double rot, DxPic_t pic, dxdraw_anchor_t anchor, int TransFlag, int ReverseXFlag, int ReverseYFlag) {
	int drawX = 0;
	int drawY = 0;

	if (anchor == DXDRAW_ANCHOR_TOP_LEFT) {
		DrawRotaGraph(x, y, size, rot, pic, TRUE, ReverseXFlag, ReverseYFlag);
		return;
	}

	switch (anchor) {
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
		drawX = x;
		break;
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
		drawX = (WINDOW_SIZE_X + 2 * x) / 2;
		break;
	case DXDRAW_ANCHOR_TOP_RIGHT:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawX = WINDOW_SIZE_X + x;
		break;
	}

	switch (anchor) {
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_TOP_RIGHT:
		drawY = y;
		break;
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
		drawX = (WINDOW_SIZE_Y + 2 * y) / 2;
		break;
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawY = WINDOW_SIZE_Y + y;
		break;
	}

	DrawRotaGraph(drawX, drawY, size, rot, pic, TransFlag, ReverseXFlag, ReverseYFlag);
	return;
}

void DrawStringAnchor(int x, int y, const TCHAR *s, DxColor_t cr, dxdraw_anchor_t anchor) {
	int drawX = 0;
	int drawY = 0;

	if (anchor == DXDRAW_ANCHOR_TOP_LEFT) {
		DrawString(x, y, s, cr);
		return;
	}

	switch (anchor) {
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
		drawX = x;
		break;
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
		drawX = (WINDOW_SIZE_X + 2 * x) / 2;
		break;
	case DXDRAW_ANCHOR_TOP_RIGHT:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawX = WINDOW_SIZE_X + x;
		break;
	}

	switch (anchor) {
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_TOP_RIGHT:
		drawY = y;
		break;
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
		drawX = (WINDOW_SIZE_Y + 2 * y) / 2;
		break;
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawY = WINDOW_SIZE_Y + y;
		break;
	}

	DrawString(drawX, drawY, s, cr);
	return;
}

void DrawStringToHandleAnchor(int x, int y, const TCHAR *s, DxColor_t cr, int handle, dxdraw_anchor_t anchor) {
	int drawX = 0;
	int drawY = 0;

	if (anchor == DXDRAW_ANCHOR_TOP_LEFT) {
		DrawStringToHandle(x, y, s, cr, handle);
		return;
	}

	switch (anchor) {
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
		drawX = x;
		break;
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
		drawX = (WINDOW_SIZE_X + 2 * x) / 2;
		break;
	case DXDRAW_ANCHOR_TOP_RIGHT:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawX = WINDOW_SIZE_X + x;
		break;
	}

	switch (anchor) {
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_TOP_RIGHT:
		drawY = y;
		break;
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
		drawX = (WINDOW_SIZE_Y + 2 * y) / 2;
		break;
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawY = WINDOW_SIZE_Y + y;
		break;
	}

	DrawStringToHandle(drawX, drawY, s, cr, handle);
	return;
}

void DrawFormatStringAnchor(int x, int y, DxColor_t cr, dxdraw_anchor_t anchor, const TCHAR *s, ...) {
	va_list as;
	va_start(as, s);

	int drawX = 0;
	int drawY = 0;
	TCHAR buf[256];

	_VSPRINTF_S(buf, s, as);

	if (anchor == DXDRAW_ANCHOR_TOP_LEFT) {
		DrawString(x, y, buf, cr);
		return;
	}

	switch (anchor) {
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
		drawX = x;
		break;
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
		drawX = (WINDOW_SIZE_X + 2 * x) / 2;
		break;
	case DXDRAW_ANCHOR_TOP_RIGHT:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawX = WINDOW_SIZE_X + x;
		break;
	}

	switch (anchor) {
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_TOP_RIGHT:
		drawY = y;
		break;
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
		drawX = (WINDOW_SIZE_Y + 2 * y) / 2;
		break;
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawY = WINDOW_SIZE_Y + y;
		break;
	}

	DrawString(drawX, drawY, buf, cr);

	va_end(as);
	return;
}

void DrawFormatStringToHandleAnchor(int x, int y, DxColor_t cr, int handle, dxdraw_anchor_t anchor, const TCHAR *s, ...) {
	va_list as;
	va_start(as, s);

	int drawX = 0;
	int drawY = 0;
	TCHAR buf[256];

	_VSPRINTF_S(buf, s, as);

	if (anchor == DXDRAW_ANCHOR_TOP_LEFT) {
		DrawStringToHandle(x, y, buf, cr, handle);
		return;
	}

	switch (anchor) {
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
		drawX = x;
		break;
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
		drawX = (WINDOW_SIZE_X + 2 * x) / 2;
		break;
	case DXDRAW_ANCHOR_TOP_RIGHT:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawX = WINDOW_SIZE_X + x;
		break;
	}

	switch (anchor) {
	case DXDRAW_ANCHOR_TOP_CENTRE:
	case DXDRAW_ANCHOR_TOP_RIGHT:
		drawY = y;
		break;
	case DXDRAW_ANCHOR_CENTRE_LEFT:
	case DXDRAW_ANCHOR_CENTRE:
	case DXDRAW_ANCHOR_CENTRE_RIGHT:
		drawX = (WINDOW_SIZE_Y + 2 * y) / 2;
		break;
	case DXDRAW_ANCHOR_BOTTOM_LEFT:
	case DXDRAW_ANCHOR_BOTTOM_CENTRE:
	case DXDRAW_ANCHOR_BOTTOM_RIGHT:
		drawY = WINDOW_SIZE_Y + y;
		break;
	}

	DrawStringToHandle(drawX, drawY, buf, cr, handle);

	va_end(as);
	return;
}

#if 1 /* DrawDeformationPic */

static void DrawDeformationPic_NoDef(int x, int y, int handle) {
	int PSizeX = 1;
	int PSizeY = 1;
	GetGraphSize(handle, &PSizeX, &PSizeY);
	x -= PSizeX / 2;
	y -= PSizeY / 2;
	DrawGraph(x, y, handle, TRUE);
	return;
}

static void DrawDeformationPic_Turn(int x, int y, int handle) {
	int PSizeX = 1;
	int PSizeY = 1;
	GetGraphSize(handle, &PSizeX, &PSizeY);
	x -= PSizeX / 2;
	y -= PSizeY / 2;
	DrawTurnGraph(x, y, handle, TRUE);
	return;
}

static void DrawDeformationPic_Extend(int x, int y, double sizeX, double sizeY, int handle) {
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
	DrawExtendGraph(pos[0], pos[1], pos[2], pos[3], handle, TRUE);
	return;
}

static void DrawDeformationPic_Rot(int x, int y, double size, int rot, int handle) {
	int PSizeX = 1;
	int PSizeY = 1;
	GetGraphSize(handle, &PSizeX, &PSizeY);
	PSizeX /= 2;
	PSizeY /= 2;
	DrawRotaGraph2(x, y, PSizeX, PSizeY, size, 3.14 * rot / 180, handle, TRUE);
	return;
}

static void DrawDeformationPic_FullDef(int x, int y, double sizeX, double sizeY, int rot, int handle) {
	int PSizeX = 1;
	int PSizeY = 1;
	GetGraphSize(handle, &PSizeX, &PSizeY);
	PSizeX /= 2;
	PSizeY /= 2;
	DrawRotaGraph3(x, y, PSizeX, PSizeY, sizeX, sizeY, 3.14 * rot / 180, handle, TRUE);
	return;
}

void DrawDeformationPic(int x, int y, double sizeX, double sizeY, int rot, int handle) {
	if (rot % 360 == 0) { /* ��]��0 */
		if (sizeX == 1 && sizeY == 1) { /* �g�嗦��1 */
			DrawDeformationPic_NoDef(x, y, handle);
		}
		else if (sizeX == -1 && sizeY == 1) { /* ���E���] */
			DrawDeformationPic_Turn(x, y, handle);
		}
		else {
			DrawDeformationPic_Extend(x, y, sizeX, sizeY, handle);
		}
	}
	else {
		if (sizeX == sizeY) { /* XY�g�嗦���ꏏ */
			DrawDeformationPic_Rot(x, y, sizeX, rot, handle);
		}
		else {
			DrawDeformationPic_FullDef(x, y, sizeX, sizeY, rot, handle);
		}
	}
	return;
}

#endif /* DrawDeformationPic */
