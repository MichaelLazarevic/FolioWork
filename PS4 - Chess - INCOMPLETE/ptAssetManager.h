#ifndef __PT_ASSET_MANAGER__
#define __PT_ASSET_MANAGER__

#include "ptAssetType.h"
#include "ptModel.h"
#include "../common/danTextureLoader.h"
#include "ptTexture.h"

enum ptModelsEnum {
	PT_MODEL_CUBE,
	PT_MODEL_KNIGHT,
	PT_MODEL_QUEEN,
	PT_MODEL_KING,
	PT_MODEL_PAWN,
	PT_MODEL_ROOK,
	PT_MODEL_BISHOP,
	PT_MODEL_BOARD,
	PT_MODEL_COUNT = 8
};

enum ptTexturesEnum {
	PT_TEXTURE_BRICK,
	PT_TEXTURE_COW,
	PT_TEXTURE_COWTEAPOT,
	PT_TEXTURE_DAN,
	PT_TEXTURE_EARTH,
	PT_TEXTURE_GRASS,
	PT_TEXTURE_OIL,
	PT_TEXTURE_OIL1,
	PT_TEXTURE_OIL2,
	PT_TEXTURE_OIL3,
	PT_TEXTURE_OIL4,
	PT_TEXTURE_OIL5,
	PT_TEXTURE_OIL6,
	PT_TEXTURE_TEDDY,
	PT_TEXTURE_MARBLE,
	PT_TEXTURE_MARBLE1,
	PT_TEXTURE_MARBLE2,
	PT_TEXTURE_MARBLE3,
	PT_TEXTURE_MARBLE4,
	PT_TEXTURE_MARBLE5,
	PT_TEXTURE_MARBLE6,
	PT_TEXTURE_YELLOW,
	PT_TEXTURE_RED,
	PT_TEXTURE_GREEN,
	PT_TEXTURE_FONT,
	PT_TEXTURE_COUNT = 26
};

class ptAssetManager
{
public:
	ptModel m_myModels[PT_MODEL_COUNT];
	ptTexture m_myTextures[PT_TEXTURE_COUNT];
	LinearAllocator* garlicAlloc;
	sce::Gnmx::Toolkit::Allocators* toolkitAlloc;
	Gnm::Sampler* mySampler;

	danTextureLoader m_textureLoader;
	int l_error = SCE_OK;

	ptAssetManager(LinearAllocator* garlAlloc, 
		sce::Gnmx::Toolkit::Allocators* toolAlloc,
		Gnm::Sampler* sampler);
	~ptAssetManager();

	void init();
	ptModel* getModel(ptModelsEnum modelName);
	Gnm::Texture* getTexture(ptTexturesEnum _texture);
};

#endif // !__PT_ASSET_MANAGER__


