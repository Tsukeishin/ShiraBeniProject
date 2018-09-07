//=============================================================================
//
// ���C�g���� <Light.cpp>
//
//=============================================================================
#include "Light.h"
#include "Direct3D.h"


//----�R���X�g���N�^--------
Dx9Light::Dx9Light()
{
	this->Type = D3DLIGHT_DIRECTIONAL;
	this->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	this->Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	this->Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	this->Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->Direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->Range = 0.0f;
	this->Falloff = 0.0f;
	this->Attenuation0 = 0.0f;
	this->Attenuation1 = 0.0f;
	this->Attenuation2 = 0.0f;
	this->Theta = 0.0f;
	this->Phi = 0.0f;
}

//----�I�[�o�[���[�h--------
Dx9Light::operator D3DLIGHT9()
{
	D3DLIGHT9 light;
	light.Type          = this->Type;
	light.Diffuse       = this->Diffuse;
	light.Specular      = this->Specular;
	light.Ambient       = this->Ambient;
	light.Position      = this->Position;
	light.Direction     = this->Direction;
	light.Range         = this->Range;
	light.Falloff       = this->Falloff;
	light.Attenuation0  = this->Attenuation0;
	light.Attenuation1  = this->Attenuation1;
	light.Attenuation2  = this->Attenuation2;
	light.Theta         = this->Theta;
	light.Phi           = this->Phi;
	return light;
}

//----���C�g��o�^���L��--------
void Dx9Light::SetLight()
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(0, &(D3DLIGHT9)*this);

	// ���C�g�̐ݒ�
	pDevice->LightEnable(0, TRUE);
}

