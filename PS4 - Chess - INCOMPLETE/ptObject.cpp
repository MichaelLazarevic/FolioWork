#include "ptObject.h"



ptObject::ptObject()
{
}


ptObject::~ptObject()
{
}

void ptObject::setTexture(Gnm::Texture* texture)
{
	if (texture)
	{
		m_myTexture = texture;
		textureUse = true;
	}
}

void ptObject::setSampler(Gnm::Sampler* sampler)
{
	if (sampler)
	{
		m_mySampler = sampler;
	}
}