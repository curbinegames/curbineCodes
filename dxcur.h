#pragma once

#define COLOR_WHITE 0xffffffff

typedef int DxPic_t; /* DX���C�u�����̃O���t�B�b�N�̃n���h���ł��邱�Ƃ������^�Bint�^ */
typedef int DxSnd_t; /* DX���C�u�����̃T�E���h�̃n���h���ł��邱�Ƃ������^�Bint�^ */

extern int GetMouseKeyCur(int* key, int* posX, int* posY, int* PR);
extern void AvoidKeyRush();
extern int GetKeyHold(int n);
extern int GetKeyPushOnce();
extern void InputAllKeyHold();
extern void AvoidKeyBug();
extern int keycur(int const* const mat, int num);
