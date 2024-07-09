
typedef int intx100; /** 100�{���Ă��邱�Ƃ�����int�^ */

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
extern void DrawZoomGraphAnchor(int x, int y, intx100 size, int pic, dxdraw_anchor_t anchor);
