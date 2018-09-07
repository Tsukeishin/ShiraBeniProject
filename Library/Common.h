#ifndef __COMMON_H_INCLUDE__
#define __COMMON_H_INCLUDE__


#define _CRT_SECURE_NO_WARNINGS // warning�h�~


/* ��ʃT�C�Y */
#define SCREEN_WIDTH (1024)
#define SCREEN_HEIGHT (576)


/* �}�N���֐� */
#define RelativeSX(m) (SCREEN_WIDTH  * m)	// �E�C���h�E�����ʒu
#define RelativeSY(m) (SCREEN_HEIGHT * m)	// �E�C���h�E�����ʒu
#define SCREEN_CENTER_X (RelativeSX(0.5f))
#define SCREEN_CENTER_Y (RelativeSY(0.5f))
#define RS_X(m) RelativeSX(m)
#define RS_Y(m) RelativeSY(m)
#define RS_IX(m) (int)RelativeSX(m)
#define RS_IY(m) (int)RelativeSY(m)



#endif // !__COMMON_H_INCLUDE__

