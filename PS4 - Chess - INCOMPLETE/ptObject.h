#ifndef __PT_OBJECT__
#define __PT_OBJECT__

#include "ptModel.h"
#include "ptShaderConstants.h"
#include <gnmx.h>

class ptObject
{
public:
	ptModel*  m_myModel;
	Matrix4 m_modelWorldMx;
	Gnm::Sampler* m_mySampler = NULL;
	Gnm::Texture* m_myTexture = NULL;
	bool textureUse = false;

	ptObject();
	~ptObject();

	void setTexture(Gnm::Texture* texture);
	void setSampler(Gnm::Sampler* sampler);
};

#endif // !__PT_OBJECT__


