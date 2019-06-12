#include "ptCamera.h"



ptCamera::ptCamera()
{
	m_worldViewMx = Matrix4::identity();
}


ptCamera::~ptCamera()
{
}

void ptCamera::updatePerspective()
{
	m_projectionMx = Matrix4::perspective(m_angle, m_aspectRatio, m_zNear, m_zFar);
}

void ptCamera::setPerspective(float _angle, float _aspectRatio, float _zNear, float _zFar)
{
	m_angle = _angle;
	m_aspectRatio = _aspectRatio;
	m_zNear = _zNear;
	m_zFar = _zFar;
	updatePerspective();
}

void ptCamera::updateAngle(float input)
{
	m_angle += input;
	updatePerspective();
}

void ptCamera::updateAspect(float input)
{
	m_aspectRatio += input;
	updatePerspective();
}

void ptCamera::updateNear(float input)
{
	m_zNear += input;
	updatePerspective();
}

void ptCamera::updateFar(float input)
{
	m_zFar += input;
	updatePerspective();
}

void ptCamera::trackLeftRight(float _amount)
{
	m_worldViewMx = Matrix4::translation(Vector3(-_amount, 0.0, 0.0)) * m_worldViewMx;
}//trackLeftRight()

void ptCamera::trackUpDown(float _amount)
{
	m_worldViewMx = Matrix4::translation(Vector3(0.0, -_amount, 0.0)) * m_worldViewMx;
}

void ptCamera::trackForwardBack(float _amount)
{
	m_worldViewMx = Matrix4::translation(Vector3(0.0, 0.0, -_amount)) * m_worldViewMx;
}

void ptCamera::trackYaw(float _amount)
{
	m_worldViewMx = Matrix4::rotationY(_amount) * m_worldViewMx; //(Vector3(-_amount, 0.0, 0.0)) * m_worldViewMx;
}

void ptCamera::trackPitch(float _amount)
{
	m_worldViewMx = Matrix4::rotationX(_amount) * m_worldViewMx; //(Vector3(-_amount, 0.0, 0.0)) * m_worldViewMx;
}


void ptCamera::trackRoll(float _amount)
{
	m_worldViewMx = Matrix4::rotationZ(_amount) * m_worldViewMx; //(Vector3(-_amount, 0.0, 0.0)) * m_worldViewMx;
}

void ptCamera::reset()
{
	m_worldViewMx = Matrix4::identity();
}