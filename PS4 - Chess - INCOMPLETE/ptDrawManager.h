#ifndef __DRAW_MANAGER__
#define __DRAW_MANAGER__

#include <gnmx.h>
#include "ptModel.h"
#include "../toolkit/toolkit.h"
#include "ptShaderConstants.h"
#include "ptCamera.h"
#include "ptObject.h"
#include "ptLight.h"
#include "ptLightCount.h"
#include "ptHUDTextItem.h"

class ptDrawManager
{
public:
	ptLight* m_myLights;

	ptDrawManager(ptLight* myLights);
	void draw(Gnmx::GnmxGfxContext* _gfxc, ptObject* _object, ptCamera* _camera);
	void draw(Gnmx::GnmxGfxContext* _gfxc, ptHUDTextItem* _object, ptCamera* _camera);
}; //Draw Manager

#endif // !DRAW_MANAGER
