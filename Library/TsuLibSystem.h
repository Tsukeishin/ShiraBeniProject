#ifndef __TSULIB_STSTEM_H_INCLUDE__
#define __TSULIB_STSTEM_H_INCLUDE__

#include <Windows.h>

typedef class TSULibrarySystem
{
public:
	static HRESULT Initialize(HINSTANCE hInstance);
	static void    Uninitialize();
	static void    CoordinateAxis();

private:
	TSULibrarySystem() {};

}TsuSystem;



#endif // !__TSULIB_STSTEM_H_INCLUDE__
