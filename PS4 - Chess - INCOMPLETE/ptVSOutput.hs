/* SIE CONFIDENTIAL
PlayStation(R)4 Programmer Tool Runtime Library Release 04.008.061
* Copyright (C) 2011 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/

#ifndef __PT_VS_OUTPUT__
#define __PT_VS_OUTPUT__

struct ptVSOutput
{
	float4 m_position		: S_POSITION;
	float3 m_colour			: COLOUR;
	float2 m_texcoord		: TEXCOORD0;
	float3 m_normal			: NORMAL0;
	float3 m_positionWorld	: POSITION0;
};//struct

#endif
