#ifndef __COMMON_H_INCLUDE__
#define __COMMON_H_INCLUDE__


#define _CRT_SECURE_NO_WARNINGS // warning防止


/* 画面サイズ */
#define SCREEN_WIDTH (1024)
#define SCREEN_HEIGHT (576)


/* マクロ関数 */
#define RelativeSX(m) (SCREEN_WIDTH  * m)	// ウインドウ割合位置
#define RelativeSY(m) (SCREEN_HEIGHT * m)	// ウインドウ割合位置
#define SCREEN_CENTER_X (RelativeSX(0.5f))
#define SCREEN_CENTER_Y (RelativeSY(0.5f))
#define RS_X(m) RelativeSX(m)
#define RS_Y(m) RelativeSY(m)
#define RS_IX(m) (int)RelativeSX(m)
#define RS_IY(m) (int)RelativeSY(m)



#endif // !__COMMON_H_INCLUDE__

