//=============================================================================
//
// カメラ処理 [Camera.cpp]
//
//=============================================================================
#include "Camera.h"
#include "Input.h"

// マクロ定義
#define GAMECAMERA_XLIMIT_MIN (    0)
#define GAMECAMERA_XLIMIT_MAX (16400)

#define CtoA_INTERVAL_MAX	(640.0f)	// カメラと注視点間の最大距離
#define CtoA_INTERVAL_MIN	(240.0f)	// カメラと注視点間の最小距離
#define CAMERA_ANGLE		(10)

#ifdef _DEBUG
int g_iAngle = CAMERA_ANGLE;
#endif // _DEBUG


//----コンストラクタ--------
CCamera::CCamera()
{
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Gaze = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	UpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Angle = D3DXVECTOR3(0.0f, D3DXToRadian(90), 0.0f);
	Interval = CtoA_INTERVAL_MIN;
	Sensitivity = GAZE_MOVE_VALUE;
}

//----デストラクタ--------
CCamera::~CCamera()
{

}

//----初期化--------
void CCamera::Init(void)
{
	// カメラの初期化
	Gaze = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Position.x = 0.0f;
	Position.y = Interval * sinf(D3DXToRadian(CAMERA_ANGLE));
	Position.z = Interval * -cosf(D3DXToRadian(CAMERA_ANGLE));
	Position += Gaze;

	UpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	Angle = D3DXVECTOR3(0.0f, D3DXToRadian(90), 0.0f);

	Interval = CtoA_INTERVAL_MIN;
	Sensitivity = GAZE_MOVE_VALUE;
}

//----平行移動--------
void CCamera::Translation(D3DXVECTOR2 moveRate)
{
	/* 十字ベクトル */
	D3DXVECTOR3 LeftVec, FrontVec;
	D3DXVECTOR3 gazeVec = Gaze - Position;
	D3DXVECTOR3 subVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXVec3Cross(&LeftVec, &gazeVec, &subVec);
	D3DXVec3Normalize(&LeftVec, &LeftVec);
	D3DXVec3Cross(&FrontVec, &LeftVec, &gazeVec);
	D3DXVec3Normalize(&FrontVec, &FrontVec);
	D3DXVec3Normalize(&gazeVec, &gazeVec);

	/* 視点平行移動 */
	if (IsMouseCenterPressed())
	{
		Gaze += LeftVec *  moveRate.x * CAMERA_MOVE_VALUE;
		Gaze += FrontVec * moveRate.y * CAMERA_MOVE_VALUE;
	}

#ifdef _DEBUG
	PrintDebugProcess("デバッグカメラ位置 : (%v)\n", Position);
	PrintDebugProcess("デバッグカメラ視線 : (%v)\n", Gaze);
	PrintDebugProcess("デバッグカメラAngl : (%v)\n", Angle);
#endif // _DEBUG

}

//----前後移動--------
void CCamera::Scaling(float moveRate)
{
	D3DXVECTOR3 gazeVec = Gaze - Position;

	/* 拡大・縮小 */
	//gazeVec *= moveRate * 0.001f;
	//Gaze += gazeVec;

	Interval -= moveRate;
}

//----旋回移動--------
void CCamera::Rotation(D3DXVECTOR2 moveRate)
{
	/* カメラ位置 */
	// 移動判定
	if (IsMouseLeftPressed())
	{
		Angle.x -= moveRate.y * Sensitivity;
		Angle.z -= moveRate.x * Sensitivity;
		Angle.y += moveRate.x * Sensitivity;
	}

	/* 移動範囲制限 */
	if (Angle.x > D3DXToRadian(179))
	{
		Angle.x = D3DXToRadian(179);
	}
	if (Angle.x < D3DXToRadian(1))
	{
		Angle.x = D3DXToRadian(1);
	}
	if (Angle.z > D3DX_PI)
	{
		Angle.z -= D3DX_PI * 2.0f;
		Angle.y += D3DX_PI * 2.0f;
	}
	if (Angle.z < -D3DX_PI)
	{
		Angle.z += D3DX_PI * 2.0f;
		Angle.y -= D3DX_PI * 2.0f;
	}

	/* 球体座標へ移動 */
	float sinTheta = sinf(Angle.x);
	Position.x = Interval * sinTheta * cosf(Angle.z);
	Position.y = Interval * cosf(Angle.x);
	Position.z = Interval * sinTheta * sinf(Angle.z);
	// 球体座標の反映
	Position += Gaze;
}

//----追尾--------
void CCamera::Tracking(D3DXVECTOR3 target)
{
	Gaze = target + D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	if (Gaze.x < GAMECAMERA_XLIMIT_MIN)
	{
		Gaze.x = GAMECAMERA_XLIMIT_MIN;
	}
	if (Gaze.x > GAMECAMERA_XLIMIT_MAX)
	{
		Gaze.x = GAMECAMERA_XLIMIT_MAX;
	}
	Position.x = 0.0f;
	Position.y = Interval * sinf(D3DXToRadian(CAMERA_ANGLE));
	Position.z = Interval * -cosf(D3DXToRadian(CAMERA_ANGLE));
	Position += Gaze;
}

//----デバッグ軌道--------
#ifdef _DEBUG
void CCamera::UNIQ_DebugMove(void)
{
	float move = 2.0f;

	// ホールド・オン
	if (GetKeyboardPress(DIK_W))
	{
		Position.z += move;
		Gaze.z += move;
	}
	if (GetKeyboardPress(DIK_S))
	{
		Position.z -= move;
		Gaze.z -= move;
	}
	if (GetKeyboardPress(DIK_E))
	{
		Position.y += move;
		Gaze.y += move;
	}
	if (GetKeyboardPress(DIK_D))
	{
		Position.y -= move;
		Gaze.y -= move;
	}
	if (GetKeyboardTrigger(DIK_Q))
	{
		g_iAngle++;
		Position.y = 100.0f * sinf(D3DXToRadian(g_iAngle));
		Position.z = 100.0f * -cosf(D3DXToRadian(g_iAngle));
		Position += Gaze;
	}
	if (GetKeyboardTrigger(DIK_A))
	{
		g_iAngle--;
		Position.y = 100.0f * sinf(D3DXToRadian(g_iAngle));
		Position.z = 100.0f * -cosf(D3DXToRadian(g_iAngle));
		Position += Gaze;
	}

	PrintDebugProcess("カメラ位置 : (%f, %f, %f)\n", Position.x, Position.y, Position.z);
	PrintDebugProcess("カメラ視線 : (%f, %f, %f)\n", Gaze.x, Gaze.y, Gaze.z);
	PrintDebugProcess("カメラ角度 : (%d)\n", g_iAngle);
}
#endif // _DEBUG

//----視線先追従--------
void CCamera::FollowingFocus(D3DXVECTOR3 correction)
{
	Position = Gaze + correction;
}

//----マトリックス生成--------
void CCamera::CreateMatrix(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/* ビューマトリックス */
	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&ViewMatrix);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&ViewMatrix,
		&Position,		// カメラの視点
		&Gaze,			// 視線先
		&UpVector);		// 上方向

						// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &ViewMatrix);


	/* プロジェクションマトリックス */
	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&ProjectionMatrix);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&ProjectionMatrix,
		VIEW_ANGLE,		// ビュー平面の視野角
		VIEW_ASPECT,	// ビュー平面のアスペクト比
		VIEW_NEAR_Z,	// ビュー平面のNearZ値
		VIEW_FAR_Z);	// ビュー平面のFarZ値

						// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix);
}

/*----取得関数----*/
D3DXVECTOR3 CCamera::GetPosition(void)			{ return Position; }			//--カメラの座標
D3DXVECTOR3 CCamera::GetFocus(void)				{ return Gaze; }				//--カメラの注視点
D3DXVECTOR3 CCamera::GetGazeVector(void)		{ return (Gaze - Position); }	//--カメラの視線
D3DXVECTOR3 CCamera::GetAngle(void)				{ return Angle; }				//--カメラのアングル
D3DXVECTOR3 CCamera::GetUpVector(void)			{ return UpVector; }			//--カメラの上方向
D3DXMATRIX  CCamera::GetViewMatrix(void)		{ return ViewMatrix; }			//--ビューマトリックス
D3DXMATRIX  CCamera::GetProjectionMatrix(void)	{ return ProjectionMatrix; }	//--プロジェクションマトリックス
float       CCamera::GetIntervel(void)			{ return Interval; }			//--距離

/*----上書関数----*/
void CCamera::SetPosition(D3DXVECTOR3 vector)	{ Position = vector; }	//--カメラの座標
void CCamera::SetFocus(D3DXVECTOR3 vector)		{ Gaze = vector; }		//--カメラの注視点
void CCamera::SetAngle(D3DXVECTOR3 vector)		{ Angle = vector; }		//--カメラのアングル
void CCamera::SetUpVector(D3DXVECTOR3 vector)	{ UpVector = vector; }	//--カメラの上方向
void CCamera::SetIntervel(float distance)		{ Interval = distance; }//--距離


//*****************************************************************************
// グローバル変数
//*****************************************************************************
CCamera GameCamera;

#if _DEBUG
CCamera DebugCamera;
bool DebugCameraFlag = false;
#endif // _DEBUG


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCamera(void)
{
	// ゲームカメラ
	GameCamera.Init();

#if _DEBUG
	// デバックカメラ
	DebugCamera.Init();
#endif // _DEBUG


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCamera(D3DXVECTOR3 target)
{
	// ゲームカメラ
#if _DEBUG
	GameCamera.UNIQ_DebugMove();
	GameCamera.Scaling(GetMouseZ() / 10.0f);
#endif // _DEBUG
	GameCamera.Tracking(target);

#if _DEBUG
	// 切り替え
	if (GetKeyboardTrigger(DIK_C))
	{
		DebugCameraFlag = DebugCameraFlag ? false : true;
	}

	if (DebugCameraFlag)
	{
		// デバックカメラ
		D3DXVECTOR3 MouseMovement = D3DXVECTOR3((float)GetMouseX(), (float)GetMouseY(), (float)GetMouseZ());
		DebugCamera.Translation(D3DXVECTOR2(MouseMovement.x, MouseMovement.y));
		DebugCamera.Scaling(MouseMovement.z);
		DebugCamera.Rotation(D3DXVECTOR2(MouseMovement.x, MouseMovement.y));
	}
#endif // _DEBUG

}

//=============================================================================
// 描画処理
//=============================================================================
void SetCamera(void)
{
#if _DEBUG
	if (DebugCameraFlag)
	{
		// デバックカメラ
		DebugCamera.CreateMatrix();
	}
	else
	{
		// ゲームカメラ
		GameCamera.CreateMatrix();
	}
#else
	// ゲームカメラ
	GameCamera.CreateMatrix();
#endif // _DEBUG

}

//=============================================================================
// ビューマトリックス取得関数
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return GameCamera.GetViewMatrix();
}

