//=============================================================================
//
// カメラ処理 [Camera.h]
//
//=============================================================================
#ifndef _CAMERA_INCLUDE_H_
#define _CAMERA_INCLUDE_H_

#include "Common.h"
#include "Vector.h"
#include <Windows.h>


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VIEW_ANGLE  (D3DXToRadian(45))								// ビュー平面の視野角(45度)
#define	VIEW_ASPECT ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z (10.0f)											// ビュー平面_DEBUG_MODE_CAMERA_のNearZ値
#define	VIEW_FAR_Z  (32768.0f)										// ビュー平面のFarZ値

#if _DEBUG
#define CAMERA_MOVE_VALUE	(2.0f)		// 移動量
#define GAZE_MOVE_VALUE		(0.005f)	// 移動量
#endif // _DEBUG


enum CAMERA_STATUS
{
	CAMERA_POSITION,	// カメラの位置
	CAMERA_FOCUS,		// 注視点
	CAMERA_GAZE,		// 視線ベクトル
	CAMERA_ROTATION,	// カメラの回転
	CAMERA_UPSIDE,		// 上方向ベクトル
};

//*****************************************************************************
// 構造体
//*****************************************************************************


//*****************************************************************************
// クラス設計
//*****************************************************************************
class CCamera
{
public:
	D3DXVECTOR3 Position;			// カメラの座標
	D3DXVECTOR3 Gaze;				// カメラの視線先
	D3DXVECTOR3 UpVector;			// カメラの上方向ベクトル
	D3DXVECTOR3 Angle;				// カメラのアングル
	float       Interval;			// カメラの視点と視線先の距離
	float       Sensitivity;		// マウス感度

	D3DXMATRIX  ViewMatrix;			// ビューマトリックス
	D3DXMATRIX  ProjectionMatrix;	// プロジェクションマトリックス

public:
	CCamera();
	~CCamera();

	void Init(void);

	void Translation(Vector2 moveRate);
	void Rotation(Vector2 moveRate);
	void Scaling(float moveRate);
	void FollowingFocus(Vector3 correction);
	void Tracking(Vector3 target);

	void CreateMatrix(void);

	D3DXMATRIX GetViewMatrix(void);
	D3DXMATRIX GetProjectionMatrix(void);

private:

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera();
void SetCamera(void);

D3DXMATRIX GetViewMatrix(void);
D3DXMATRIX GetProjectionMatrix(void);

#endif
