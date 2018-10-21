#ifndef __COMMON_H_INCLUDE__
#define __COMMON_H_INCLUDE__


#define _CRT_SECURE_NO_WARNINGS // warning防止


//================================================================
// 画面サイズ関係
//================================================================
/* 画面サイズ */
#define SCREEN_WIDTH    (1024)
#define SCREEN_HEIGHT   (576)
#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)	// 画面中央座標
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)	// 画面中央座標

/* 画面座標計算 */
#define RelativeSX(m)   (SCREEN_WIDTH  * m)	// ウインドウ割合位置X
#define RelativeSY(m)   (SCREEN_HEIGHT * m)	// ウインドウ割合位置Y
#define RS_X(m)         RelativeSX(m)		// <略記>
#define RS_Y(m)         RelativeSY(m)		// <略記>
#define RS_IX(m)   (int)RelativeSX(m)		// <略記>int型出力
#define RS_IY(m)   (int)RelativeSY(m)		// <略記>int型出力


//================================================================
// マクロ関数
//================================================================



#endif // !__COMMON_H_INCLUDE__

