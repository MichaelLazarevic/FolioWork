#include "ptAssetManager.h"



ptAssetManager::ptAssetManager(LinearAllocator* garlAlloc, 
	sce::Gnmx::Toolkit::Allocators* toolAlloc,
	Gnm::Sampler* sampler)
{
	mySampler = sampler;
	garlicAlloc = garlAlloc;
	toolkitAlloc = toolAlloc;
}


ptAssetManager::~ptAssetManager()
{
}

void ptAssetManager::init()
{
	m_myModels[PT_MODEL_KNIGHT].m_filename = "/app0/assets/models/OBJ/knight.obj";
	m_myModels[PT_MODEL_KNIGHT].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[PT_MODEL_PAWN].m_filename = "/app0/assets/models/OBJ/pawn.obj";
	m_myModels[PT_MODEL_PAWN].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[PT_MODEL_QUEEN].m_filename = "/app0/assets/models/OBJ/queen.obj";
	m_myModels[PT_MODEL_QUEEN].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[PT_MODEL_KING].m_filename = "/app0/assets/models/OBJ/king.obj";
	m_myModels[PT_MODEL_KING].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[PT_MODEL_ROOK].m_filename = "/app0/assets/models/OBJ/rook.obj";
	m_myModels[PT_MODEL_ROOK].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[PT_MODEL_BISHOP].m_filename = "/app0/assets/models/OBJ/bishop.obj";
	m_myModels[PT_MODEL_BISHOP].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[PT_MODEL_CUBE].m_filename = "/app0/assets/models/ptm/cubesplitface.ptm";
	m_myModels[PT_MODEL_CUBE].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

	m_myModels[PT_MODEL_BOARD].m_filename = "/app0/assets/models/OBJ/cube.obj";
	m_myModels[PT_MODEL_BOARD].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myTextures[PT_TEXTURE_BRICK].m_filename = "/app0/assets/textures/brick.gnf";
	m_myTextures[PT_TEXTURE_COW].m_filename = "/app0/assets/textures/cow.gnf";
	m_myTextures[PT_TEXTURE_COWTEAPOT].m_filename = "/app0/assets/textures/cowTeapot.gnf";
	m_myTextures[PT_TEXTURE_DAN].m_filename = "/app0/assets/textures/dan.gnf";
	m_myTextures[PT_TEXTURE_EARTH].m_filename = "/app0/assets/textures/earth.gnf";
	m_myTextures[PT_TEXTURE_GRASS].m_filename = "/app0/assets/textures/grass.gnf";
	m_myTextures[PT_TEXTURE_OIL].m_filename = "/app0/assets/textures/oil.gnf";
	m_myTextures[PT_TEXTURE_OIL1].m_filename = "/app0/assets/textures/oil1.gnf";
	m_myTextures[PT_TEXTURE_OIL2].m_filename = "/app0/assets/textures/oil2.gnf";
	m_myTextures[PT_TEXTURE_OIL3].m_filename = "/app0/assets/textures/oil3.gnf";
	m_myTextures[PT_TEXTURE_OIL4].m_filename = "/app0/assets/textures/oil4.gnf";
	m_myTextures[PT_TEXTURE_OIL5].m_filename = "/app0/assets/textures/oil5.gnf";
	m_myTextures[PT_TEXTURE_OIL6].m_filename = "/app0/assets/textures/oil6.gnf";
	m_myTextures[PT_TEXTURE_TEDDY].m_filename = "/app0/assets/textures/TeddyTexture.gnf";
	m_myTextures[PT_TEXTURE_MARBLE].m_filename = "/app0/assets/textures/marble.gnf";
	m_myTextures[PT_TEXTURE_MARBLE1].m_filename = "/app0/assets/textures/marble1.gnf";
	m_myTextures[PT_TEXTURE_MARBLE2].m_filename = "/app0/assets/textures/marble2.gnf";
	m_myTextures[PT_TEXTURE_MARBLE3].m_filename = "/app0/assets/textures/marble3.gnf";
	m_myTextures[PT_TEXTURE_MARBLE4].m_filename = "/app0/assets/textures/marble4.gnf";
	m_myTextures[PT_TEXTURE_MARBLE5].m_filename = "/app0/assets/textures/marble5.gnf";
	m_myTextures[PT_TEXTURE_MARBLE6].m_filename = "/app0/assets/textures/marble6.gnf";
	m_myTextures[PT_TEXTURE_YELLOW].m_filename = "/app0/assets/textures/yellow.gnf";
	m_myTextures[PT_TEXTURE_GREEN].m_filename = "/app0/assets/textures/green.gnf";
	m_myTextures[PT_TEXTURE_RED].m_filename = "/app0/assets/textures/red.gnf";
	m_myTextures[PT_TEXTURE_FONT].m_filename = "/app0/assets/textures/font.gnf";

}

ptModel* ptAssetManager::getModel(ptModelsEnum modelName)
{
	ptModel* model = &m_myModels[modelName];
	if (!model->m_validData)
	{
		switch (model->m_assetType)
		{
		case PT_ASSET_TYPE::MODEL_OBJ:
			model->loadModelOBJ(model->m_filename, garlicAlloc);
			break;
		case PT_ASSET_TYPE::MODEL_PTM:
			model->loadModelPTM(model->m_filename, garlicAlloc);
			break;
		default:
			break;
		}
	}
	return model;
}

Gnm::Texture* ptAssetManager::getTexture(ptTexturesEnum _texture)
{
	ptTexture* texture = &m_myTextures[_texture];
	Gnm::Texture* texturePointer = nullptr;
	if (!texture->m_validData)
	{
		l_error = m_textureLoader.loadTextureFromGnf(texture->m_filename, 
			texture->m_index, toolkitAlloc, texture->m_texture);
		if (!l_error)
		{
			texture->m_validData = true;
			texturePointer = &texture->m_texture;
		}
	}
	return texturePointer;
}