/* SIE CONFIDENTIAL
PlayStation(R)4 Programmer Tool Runtime Library Release 04.008.061
* Copyright (C) 2013 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/

#ifndef __PT_SHADER_CONSTANTS__
#define __PT_SHADER_CONSTANTS__

#include "../toolkit/shader_common/shader_base.h"
#include "ptLightCount.h"


unistruct ptShaderConstants
{
	Matrix4Unaligned shc_modelProjMx[__PT_LIGHT_COUNT__];
	Matrix4Unaligned shc_normalTransMx[__PT_LIGHT_COUNT__];
	Matrix4Unaligned shc_modelWorldMx[__PT_LIGHT_COUNT__];
	Vector4Unaligned shc_cameraPositionWorldVx[__PT_LIGHT_COUNT__];
	Vector4Unaligned shc_lightADSVx[__PT_LIGHT_COUNT__];
		//shc_lightADSVx		(x,y,z) = (ambient, diffuse, specular) intensity 0-1, 0=off.		w = <spare>
	Vector4Unaligned shc_lightColourVx[__PT_LIGHT_COUNT__];
		//shc_lightColourVx	(x,y,z) = (r,g,b)		w = on/off (1/0)
	Vector4Unaligned shc_lightLocationVX[__PT_LIGHT_COUNT__];
		//shc_lightLocationVX	(x,y,z) = light location for positional lights, negative direction for infinite lights. w = positional/infinite (1/0)
	Vector4Unaligned shc_lightSpotDirectionVx[__PT_LIGHT_COUNT__];
		//shc_lightSpotDirectionVx	(x,y,z) = direction for spotlights.		w = cutoff angle cosine, 1.0 or above = no cutoff cone
	Vector4Unaligned shc_lightAttenuationVx[__PT_LIGHT_COUNT__];
		//shc_lightAttenuationVx	x = fixed, y = linear, z = quadratic. [attn = 1/(f + l*d + q*d*d)]	w = on/off (1/0) for attn calcs.
	float shc_angle[__PT_LIGHT_COUNT__];
};

#endif

#pragma once


