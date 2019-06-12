#ifndef __LIGHT__
#define __LIGHT__

#include "../toolkit/toolkit.h"

class ptLight
{
public:
	//Colour
	Vector3  m_colour = Vector3(1.0, 1.0, 1.0);

	//direction and position
	Vector3 m_locationVx = Vector3(0.5, 1.0, 0.0);
	Vector3 m_directionVx = Vector3(0, 0, 0);

	//ADS components
	float m_ambientFactor = 0.02;
	float m_diffuseFactor = 1.0;
	float m_specularFactor = 1.0;

	//Distance Attenuation
	float m_fixedAttnFactor = 0.0;
	float m_linearAttnFactor = 0.0;
	float m_quadAttnFactor = 0.25;

	//angle attenuation
	float m_spotAngleCos = 0.985;

	//flags
	bool m_isOn = false;
	bool m_isDirectional = true;
	bool m_isInfinite = false;
	bool m_useDistanceAttn = false;

	ptLight();
	~ptLight();
};

#endif // !__LIGHT__


