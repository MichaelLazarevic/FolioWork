#ifndef __PT_MODEL__
#define __PT_MODEL__

#include "ptVertex.h"
#include "ptHardModels.h"
#include "../common/allocator.h"
#include "../common/danFileParser.h"
#include "../toolkit/geommath/geommath.h"
#include "../common//danRandom.h"
#include "../common/danOBJHelpers.h"
#include "ptAssetType.h"

using namespace sce;

enum class PT_HARD_MODEL
{
	CUBE,
	TETRA,
	OCTA,
	ICOS,
	CUBE_PVC,
	TETRA_PVC,
	OCTA_PVC,
	ICOS_PVC
};//PT_HARD_MODEL

class ptModel
{
public:
	char m_word[25];
	char l_lineType[50];				//read in the data type
	char l_vertexString[50];			//for vertex-index triples
	const char* m_filename;
	PT_ASSET_TYPE m_assetType;

	bool m_verbose = false;
	bool m_generateNormals = true;
	bool m_gotTexcoords = false;

	//vertex data
	ptTriangle* m_triangles;
	size_t m_onionMemorySize = 16 * 1024 * 1024;
	ptVertex* m_vertices;
	uint16_t m_vertexCount;
	size_t m_verticesSize;
	//indices
	uint16_t* m_indices;
	uint32_t m_indexCount;
	size_t m_indicesSize;

	uint32_t m_textureCount;

	ptVertex* m_gpuVertexData;
	uint16_t* m_gpuIndexData;

	Vector3 m_defaultColour = { 0.5, 0.5, 0.5 };

	Gnm::Buffer m_vertexBuffers[PT_VERTEX_ELEM_COUNT];

	bool m_validData = false;
	bool m_oneColour = true;
	bool m_noColour = false;
	bool m_genSequentialTris = false;

	ptModel();
	void fillColour(Vector3 _colour);
	void fillRandomColour();
	void modelToPTM();
	void genSequentialTris(LinearAllocator* _onionAlloc);
	int loadModelPTM(const char* _filename, LinearAllocator* _garlicAlloc);
	void loadHardModel(PT_HARD_MODEL _model, LinearAllocator* _garlicAlloc);
	int loadModelOBJ(const char* _filename, LinearAllocator* _garlicAlloc);
	int copyDataToGPU(LinearAllocator* _garlicAlloc);

	void cleanNormals();
	void generateNormals();
	void normalizeNormals();
	void initAsVertexBuffer();
	void printPositions();
	void printTriangles();
	void printColours();
	void printNormals();
};//ptModel

#endif