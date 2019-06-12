#ifndef __CONTROLLER__
#define __CONTROLLER__

#include <pad.h>
#include <scebase.h>
#include <user_service.h>


//typedef struct ScePadData {
//	uint32_t buttons;
// ScePadAnalogStick leftStick;
//	ScePadAnalogStick rightStick;
//	ScePadAnalogButtons analogButtons;
//	SceFQuaternion orientation;
//	SceFVector3 acceleration;
//	SceFVector3 angularVelocity;
//	ScePadTouchData touchData;
//	bool connected;
//	uint64_t timestamp;
//	ScePadExtensionUnitData extensionUnitData;
//	uint8_t connectedCount;
//	uint8_t reserve[2];
//	uint8_t deviceUniqueDataLen;
//	uint8_t deviceUniqueData[SCE_PAD_MAX_DEVICE_UNIQUE_DATA_SIZE];
//} ScePadData;

//typedef enum ScePadButtonDataOffset {
//	SCE_PAD_BUTTON_L3 = 0x00000002,
//	SCE_PAD_BUTTON_R3 = 0x00000004,
//	SCE_PAD_BUTTON_OPTIONS = 0x00000008,
//	SCE_PAD_BUTTON_UP = 0x00000010,
//	SCE_PAD_BUTTON_RIGHT = 0x00000020,
//	SCE_PAD_BUTTON_DOWN = 0x00000040,
//	SCE_PAD_BUTTON_LEFT = 0x00000080,
//	SCE_PAD_BUTTON_L2 = 0x00000100,
//	SCE_PAD_BUTTON_R2 = 0x00000200,
//	SCE_PAD_BUTTON_L1 = 0x00000400,
//	SCE_PAD_BUTTON_R1 = 0x00000800,
//	SCE_PAD_BUTTON_TRIANGLE = 0x00001000,
//	SCE_PAD_BUTTON_CIRCLE = 0x00002000,
//	SCE_PAD_BUTTON_CROSS = 0x00004000,
//	SCE_PAD_BUTTON_SQUARE = 0x00008000,
//	SCE_PAD_BUTTON_TOUCH_PAD = 0x00100000,
//	SCE_PAD_BUTTON_INTERCEPTED = 0x80000000,
//} ScePadButtonDataOffset;

class ptController
{

	SceUserServiceUserId  m_userId; //id of the user the controller is assigned to
	int32_t m_handle;				//the controller handle, used for all subsequent data collection
	ScePadData m_padState;			//holds the state of the controller when polled 
	bool m_initialised = false;		//flag to show when initialised

public:
	ptController();
	~ptController();
	int initialise();
	int update();
	bool buttonPressed(ScePadButtonDataOffset offset);
	float leftStickX();
	float leftStickY();
	float rightStickX();
	float rightStickY();
	float stickResult(uint8_t value);
};

#endif // !__CONTROLLER__

