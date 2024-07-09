
#include "DxLib.h"
#include "dxdraw.h"
#include "../system.h"

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
void DrawZoomGraphAnchor(int x, int y, intx100 size, int pic, dxdraw_anchor_t anchor) {
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
