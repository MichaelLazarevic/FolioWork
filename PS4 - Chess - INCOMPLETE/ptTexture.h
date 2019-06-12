#ifndef __TEXTURE_LOADER__
#define __TEXTURE_LOADER__

#include <gnmx.h>
#include "ptAssetType.h"

using namespace sce;

class ptTexture
{
public:
	ptTexture();
	~ptTexture();

	Gnm::Texture m_texture;
	const char* m_filename = NULL;
	PT_ASSET_TYPE m_assetType = PT_ASSET_TYPE::TEXTURE_GNF;
	bool m_validData = false;
	uint8_t m_index = 0;
};

#endif // !__TEXTURE_LOADER__


