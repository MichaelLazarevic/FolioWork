#include "ptController.h"


ptController::ptController()
{
	initialise();
}

ptController::~ptController()
{
}

int ptController::initialise()
{
	int l_error = SCE_OK;

	l_error = sceUserServiceInitialize(NULL);
	if (l_error != SCE_OK) { printf("Unable to initialise user service (from ptController::initialise())\n");  return SCE_ERROR_ERROR_FLAG; }

	//initialise pad library
	l_error = scePadInit();
	if (l_error != SCE_OK) { printf("Unable to initialise controller library\n");  return SCE_ERROR_ERROR_FLAG; }

	//get id for logged in user
	l_error = sceUserServiceGetInitialUser(&m_userId);
	if (l_error != SCE_OK) { printf("Unable to get initial user id (ptController::initialise())\n");  return SCE_ERROR_ERROR_FLAG; }

	m_handle = scePadOpen(m_userId, SCE_PAD_PORT_TYPE_STANDARD, 0, NULL);
	if (m_handle < 0) { printf("Unable to get controller handle\n");  return SCE_ERROR_ERROR_FLAG; }

	//get first lot of data
	l_error = scePadReadState(m_handle, &m_padState);
	if (l_error != SCE_OK) { printf("Unable to read intial data for controller\n");  return SCE_ERROR_ERROR_FLAG; }

	m_initialised = true;

	return l_error;
}//initialize

 //populates m_padState with the current state of the pad
int ptController::update()
{
	int l_error = SCE_ERROR_ERROR_FLAG;
	if (m_initialised) l_error = scePadReadState(m_handle, &m_padState);
	else printf("Warning: attempting to read controller data for an un-initialised controller\n");
	return l_error;
}//update


 //first set - check if the button is currently pressed
bool ptController::buttonPressed(ScePadButtonDataOffset offset) 
{ 
	return m_padState.buttons & offset;
}


float ptController::leftStickX()
{
	return stickResult(m_padState.leftStick.x);
}

float ptController::leftStickY()
{
	return stickResult(m_padState.leftStick.y);
}

float ptController::rightStickX()
{
	return stickResult(m_padState.rightStick.x);
}

float ptController::rightStickY()
{
	return stickResult(m_padState.rightStick.y);
}

float ptController::stickResult(uint8_t value)
{
	float result = (((value / 256.0f) * 2.0f) - 1.0f);
	if (result > -0.02f && result < 0.2f)
	{
		result = 0.0f;
	}
	return result / 50;
}