//=============================================================================
//
// ÉâÉCÉgèàóù <Light.h>
//
//=============================================================================
#ifndef __LIGHT_INCLUDE_H__
#define __LIGHT_INCLUDE_H__

#include "LinkLibrary.h"


class Dx9Light
{
	D3DLIGHTTYPE    Type;           /* Type of light source */
	D3DCOLORVALUE   Diffuse;        /* Diffuse color of light */
	D3DCOLORVALUE   Specular;       /* Specular color of light */
	D3DCOLORVALUE   Ambient;        /* Ambient color of light */
	D3DVECTOR       Position;       /* Position in world space */
	D3DVECTOR       Direction;      /* Direction in world space */
	float           Range;          /* Cutoff range */
	float           Falloff;        /* Falloff */
	float           Attenuation0;   /* Constant attenuation */
	float           Attenuation1;   /* Linear attenuation */
	float           Attenuation2;   /* Quadratic attenuation */
	float           Theta;          /* Inner angle of spotlight cone */
	float           Phi;            /* Outer angle of spotlight cone */

public:
	Dx9Light();

	/* Overload */
	operator D3DLIGHT9();

	/* Function */
	void SetLight();

};


#endif
