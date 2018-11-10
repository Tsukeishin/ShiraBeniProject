#ifndef __TSULIB_COLOR_H_INCLUDE__
#define __TSULIB_COLOR_H_INCLUDE__


#include "Math.h"
#include <d3dx9math.h>

typedef D3DCOLOR COLOR, DxColor;


#define RANDOMCOLOR (0xFF000000 | Random(0, 255) << 16 | Random(0, 255) << 8 | Random(0, 255))


#define DX9COLOR_BLACK       (0xFF000000)
#define DX9COLOR_RED         (0xFFFF0000)
#define DX9COLOR_GREEN       (0xFF00FF00)
#define DX9COLOR_BLUE        (0xFF0000FF)
#define DX9COLOR_YELLOW      (0xFFFFFF00)
#define DX9COLOR_MAGENTA     (0xFFFF00FF)
#define DX9COLOR_CYAN        (0xFF00FFFF)
#define DX9COLOR_WHITE       (0xFFFFFFFF)


#endif // !__TSULIB_COLOR_INCLUDE__
