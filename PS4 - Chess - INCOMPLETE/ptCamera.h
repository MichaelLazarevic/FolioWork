#ifndef __CAMERA__
#define __CAMERA__

#include "ptShaderConstants.h"

class ptCamera
{
public:
	Matrix4 m_projectionMx;
	Matrix4 m_worldViewMx;

	float m_angle;
	float m_aspectRatio;
	float m_zNear;
	float m_zFar;

	ptCamera();
	~ptCamera();

	void updatePerspective();

	void setPerspective(float _angle, float _aspectRatio, float _zNear, float _zFar);
	
	void updateAngle(float input);
	void updateAspect(float input);
	void updateNear(float input);
	void updateFar(float input);

	void trackLeftRight(float _amount);
	void trackUpDown(float _amount);
	void trackForwardBack(float _amount);
	void trackYaw(float _amount);
	void trackPitch(float _amount);
	void trackRoll(float _amount);
	void reset();
};

#endif // __CAMERA__



