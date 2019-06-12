#include "ptModel.h"

	Gnm::Buffer m_vertexBuffers[PT_VERTEX_ELEM_COUNT];

	bool m_validData = false;
	ptModel::ptModel()
	{
		//vertex data
		m_vertices = NULL;
		m_vertexCount = 0;
		m_verticesSize = 0;

		//indices
		m_indices = NULL;
		m_indexCount = 0;
		m_indicesSize = 0;
	}


	void ptModel::fillColour(Vector3 _colour)
	{
		for (int i = 0; i < m_vertexCount; i++)
		{
			m_vertices[i].r = _colour[0];
			m_vertices[i].g = _colour[1];
			m_vertices[i].b = _colour[2];
		}
	} //fillColour()

	void ptModel::fillRandomColour()
	{
		danRandom l_Random;
		for (int i = 0; i < m_vertexCount; i++)
		{
			m_vertices[i].r = l_Random.getFraction();
			m_vertices[i].g = l_Random.getFraction();
			m_vertices[i].b = l_Random.getFraction();
		}//for
	}//fillRandomColour()

	void ptModel::modelToPTM()
	{
		for (int i = 0; i < m_vertexCount; i++)
		{
			ptVertex vert = m_gpuVertexData[i];
			printf("P %i %f %f %f", i, vert.x, vert.y, vert.z);
			printf("C %i %f %f %f", i, vert.r, vert.g, vert.b);
		}

		/*for (int k = 0; k < m_indexCount; k++)
		{
			printf("T %i", m_gpuIndexData[k], );
		}*/
	}

	void ptModel::genSequentialTris(LinearAllocator* _onionAlloc)
	{
		m_indices = (uint16_t*)_onionAlloc->allocate(m_vertexCount * sizeof(uint16_t), Gnm::kAlignmentOfBufferInBytes);
		for (uint16_t i = 0; i < m_vertexCount; ++i)
		{
			m_indices[i] = i;
		}
	} //genSequentialTris

	int ptModel::loadModelPTM(const char* _filename, LinearAllocator* _garlicAlloc)
	{
		int l_error = SCE_OK;

		//Lets have our own memory allocator
		LinearAllocator myOnionAllocator;
		l_error = myOnionAllocator.initialize(m_onionMemorySize, SCE_KERNEL_WB_ONION,
			SCE_KERNEL_PROT_CPU_RW | SCE_KERNEL_PROT_GPU_ALL);
		if (l_error != SCE_OK) {
			printf("Onion allocator failed to initialise: 0x%08X\n", l_error);
			return l_error;
		}

		char l_lineType;
		int l_pCount = 0;
		int l_cCount = 0;
		int l_tCount = 0;
		int l_nCount = 0;
		int l_uvCount = 0;

		int l_index;
		float l_A;
		float l_B;
		float l_C;
		int l_ta;
		int l_tb;
		int l_tc;

		bool * t_pCheck;
		bool * t_cCheck;
		bool * t_tCheck;
		bool * t_nCheck;
		bool * t_uvCheck;


		//file parser
		danFileParser myDFP;
		l_error = myDFP.openFile(_filename);
		if (l_error != SCE_OK) {
			printf("Unable to load file in model\n"); return SCE_ERROR_ERROR_FLAG;
		}

		while (!myDFP.atEOF())
		{
			if (myDFP.getChar(l_lineType))
			{
				switch (l_lineType)
				{
				case 'P':
					l_pCount++;
					break;
				case 'C':
					l_cCount++;
					break;
				case 'T':
					l_tCount++;
					break;
				case 'N':
					l_nCount++;
					break;
				case 'U' :
					l_uvCount++;
					break;
				case 'X':
					// printf("X Found\n");
					if (myDFP.getWord(m_word))
					{
						if (myDFP.stringCompare(m_word, "SINGLE_COLOUR"))
						{
							m_oneColour = true;
						}
						else if (myDFP.stringCompare(m_word, "NO_COLOUR"))
						{
							m_noColour = true;
						}
						else if (myDFP.stringCompare(m_word, "GEN_SEQUENTIAL_TRIS"))
						{
							m_genSequentialTris = true;
						}
						else if (myDFP.stringCompare(m_word, "GEN_SPLAYED_NORMALS") || myDFP.stringCompare(m_word, "GEN_NORMALS"))
						{
							m_generateNormals = true;
						}
					}//if
					break;

				}
			}
			myDFP.nextLine();
		}
		if (l_nCount != l_pCount)
		{
			m_generateNormals = true;
		}
		t_pCheck = (bool*)myOnionAllocator.allocate(l_pCount * sizeof(bool),
			sce::Gnm::kAlignmentOfBufferInBytes);
		for (int i = 0; i < m_vertexCount; i++)
		{
			t_pCheck[i] = false;
		}

		t_cCheck = (bool*)myOnionAllocator.allocate(l_cCount * sizeof(bool),
			sce::Gnm::kAlignmentOfBufferInBytes);
		for (int i = 0; i < m_vertexCount; i++)
		{
			t_cCheck[i] = false;
		}

		t_tCheck = (bool*)myOnionAllocator.allocate(l_tCount * sizeof(bool),
			sce::Gnm::kAlignmentOfBufferInBytes);
		for (int i = 0; i < l_tCount; i++)
		{
			t_tCheck[i] = false;
		}

		t_nCheck = (bool*)myOnionAllocator.allocate(l_nCount * sizeof(bool),
			sce::Gnm::kAlignmentOfBufferInBytes);
		for (int i = 0; i < m_vertexCount; i++)
		{
			t_nCheck[i] = false;
		}

		t_uvCheck = (bool*)myOnionAllocator.allocate(l_uvCount * sizeof(bool),
			sce::Gnm::kAlignmentOfBufferInBytes);
		for (int i = 0; i < l_uvCount; i++)
		{
			t_uvCheck[i] = false;
		}

		m_vertexCount = l_pCount;
		m_verticesSize = m_vertexCount * sizeof(ptVertex);
		m_vertices = (ptVertex*)myOnionAllocator.allocate(m_verticesSize,
			Gnm::kAlignmentOfBufferInBytes);
		if (!m_vertices)
		{
			printf("Unable to allocate memory for m_vertices in ptModel::loadModelPTM\n");
			return SCE_ERROR_ERROR_FLAG;
		}

		m_indexCount = 3 * l_tCount;
		m_indicesSize = m_indexCount * sizeof(uint16_t);
		m_indices = (uint16_t*)myOnionAllocator.allocate(m_indicesSize,
			Gnm::kAlignmentOfBufferInBytes);
		if (!m_indices)
		{
			printf("Unable to allocate memory for m_indices in ptModel::loadModelPTM\n");
			return SCE_ERROR_ERROR_FLAG;
		}

		if (m_verbose)
		{
			printf("Found %i positions, %i colours in %i triangles, %i normals\n",
				l_pCount, l_cCount, l_tCount, l_nCount);
			printf("Memory allocated: %i for vertices, %i for indices\n",
				(int)m_verticesSize, (int)m_indicesSize);
		}

		myDFP.reset();
		m_triangles = (ptTriangle*)m_indices;

		while (!myDFP.atEOF())
		{

			if (myDFP.getChar(l_lineType))
			{
				switch (l_lineType)
				{
				case 'P':
					if (myDFP.getInt(l_index) && myDFP.getFloat(l_A) &&
						myDFP.getFloat(l_B) && myDFP.getFloat(l_C))
					{
						if (l_index > l_pCount)
						{
							printf("Position index out of range\n");
							return SCE_ERROR_ERROR_FLAG;
						}
						if (t_pCheck[l_index])
						{
							printf("Duplicate position for index %i, replacing previous data\n",
								l_index);
						}
						m_vertices[l_index].x = l_A;
						m_vertices[l_index].y = l_B;
						m_vertices[l_index].z = l_C;
						// printf("Position[%i] = (%f, %f, %f)\n", l_index, l_A, l_B, l_C);
						t_pCheck[l_index] = true;
					}//if
					break;

				case 'N':
					if (myDFP.getInt(l_index) && myDFP.getFloat(l_A) &&
						myDFP.getFloat(l_B) && myDFP.getFloat(l_C))
					{
						if (l_index > l_nCount)
						{
							printf("Normal index out of range\n");
							return SCE_ERROR_ERROR_FLAG;
						}
						if (t_nCheck[l_index])
						{
							printf("Duplicate position for index %i, replacing previous data\n",
								l_index);
						}
						m_vertices[l_index].nx = l_A;
						m_vertices[l_index].ny = l_B;
						m_vertices[l_index].nz = l_C;
						// printf("Position[%i] = (%f, %f, %f)\n", l_index, l_A, l_B, l_C);
						t_nCheck[l_index] = true;
					}//if
					break;
					
				case 'C':
					if (myDFP.getInt(l_index) && myDFP.getFloat(l_A) &&
						myDFP.getFloat(l_B) && myDFP.getFloat(l_C))
					{
						if (l_index > l_pCount)
						{
							printf("Position index out of range\n");
							return SCE_ERROR_ERROR_FLAG;
						}
						m_vertices[l_index].r = l_A;
						m_vertices[l_index].b = l_B;
						m_vertices[l_index].g = l_C;
						t_cCheck[l_index] = true;
						// printf("Colour[%i] = (%f, %f, %f)\n", l_index, l_A, l_B, l_C);
					}//if
					break;

				case 'T':
					if (myDFP.getInt(l_index) && myDFP.getInt(l_ta) &&
						myDFP.getInt(l_tb) && myDFP.getInt(l_tc) && 
						!m_genSequentialTris)
					{
						if (l_index > l_tCount)
						{
							printf("t Count less than Index");
						}
						if (t_tCheck[l_index])
						{
							printf("Duplicated T data");
						}
						if (l_ta < 0 || l_ta > m_vertexCount - 1 ||
							l_tb < 0 || l_tb > m_vertexCount - 1 ||
							l_tc < 0 || l_tc > m_vertexCount - 1)
						{
							printf("T Vertex Data is the wrong size %i - %i - %i", l_ta, l_tb, l_tc);
						}
						m_triangles[l_index].a = l_ta;
						m_triangles[l_index].b = l_tb;
						m_triangles[l_index].c = l_tc;
						t_tCheck[l_index] = true;
						// printf("Triangle[%i] = (%i, %i, %i)\n", l_index, l_ta, l_tb, l_tc);
					}//if
					break;
				case 'U':
					if (myDFP.getInt(l_index) && myDFP.getFloat(l_A) && myDFP.getFloat(l_B))
					{
						if (l_index > l_uvCount)
						{
							printf("uv Count less than Index");
						}
						if (t_uvCheck[l_index])
						{
							printf("Duplicated UV data");
						}
						m_vertices[l_index].u = l_A;
						m_vertices[l_index].v = l_B;
						printf("UV[%i] = (%f, %f)\n", l_index, l_A, l_B);
						t_uvCheck[l_index] = true;
					}
					break;
				case 'X':
					break;

				}
			}
			myDFP.nextLine();
		}


		if (m_generateNormals || l_nCount == 0)
		{
			generateNormals();
		}

		bool l_uvCheck = true;

		for (int i = 0; i < l_uvCount; i++)
		{
			if (t_uvCheck[i] == false)
			{
				l_uvCheck = false;
				printf("Failed UV Check\n");
			}
		}
		if (l_uvCheck)
		{
			m_gotTexcoords = true;
		}

		for (int i = 0; i < m_vertexCount; i++)
		{
			if (t_pCheck[i] == false)
			{
				return SCE_ERROR_ERROR_FLAG;
			}
		}

		if (!t_cCheck[0] && m_oneColour)
		{
			m_oneColour = false;
			m_noColour = true;
		}
		if (m_oneColour)
		{
			printf("One Colour Selected\n");
			fillColour(Vector3(m_vertices[0].r, m_vertices[0].g, m_vertices[0].b));
		}
		else if (m_noColour)
		{
			printf("Default Colour Selected\n");
			fillColour(m_defaultColour);
		}
		else
		{
			for (int i = 0; i < m_vertexCount; i++)
			{
				if (i > l_cCount)
				{
					fillColour(m_defaultColour);
				}
				else if (t_cCheck[i] == false)
				{
					fillColour(m_defaultColour);
				}
			}
		}

		//fillRandomColour();

		if (m_genSequentialTris)
		{
			genSequentialTris(&myOnionAllocator);
		}

		l_error = copyDataToGPU(_garlicAlloc);

		if (l_error != SCE_OK) 
		{
			printf("Unable to copy model data to GPU memory: 0x%08X\n", l_error); 
			return l_error;
		}

		myOnionAllocator.terminate();
		//leave this near end to protect against bad data
		if ((m_vertexCount > 2) && (m_indexCount > 2))
		{
			m_validData = true;
			printf("Got valid data\n");
		}

		return l_error;
	}

	void ptModel::loadHardModel(PT_HARD_MODEL _model, LinearAllocator* _garlicAlloc)
	{
		switch (_model)
		{
		case PT_HARD_MODEL::CUBE:
			m_vertices = s_vertexDataCube;
			m_indices = s_indexDataCube;
			m_verticesSize = sizeof(s_vertexDataCube);
			m_indicesSize = sizeof(s_indexDataCube);
			break;
		case PT_HARD_MODEL::CUBE_PVC:
			m_vertices = s_vertexDataCubePVC;
			m_indices = s_indexDataCubePVC;
			m_verticesSize = sizeof(s_vertexDataCubePVC);
			m_indicesSize = sizeof(s_indexDataCubePVC);
			break;
		case PT_HARD_MODEL::ICOS:
			m_vertices = s_vertexDataIcosahedron;
			m_indices = s_indexDataIcosahedron;
			m_verticesSize = sizeof(s_vertexDataIcosahedron);
			m_indicesSize = sizeof(s_indexDataIcosahedron);
			break;
		case PT_HARD_MODEL::TETRA:
			m_vertices = s_vertexDataTetrahedron;
			m_indices = s_indexDataTetrahedron;
			m_verticesSize = sizeof(s_vertexDataTetrahedron);
			m_indicesSize = sizeof(s_indexDataTetrahedron);
			break;
		case PT_HARD_MODEL::OCTA:
			m_vertices = s_vertexDataOctahedron;
			m_indices = s_indexDataOctahedron;
			m_verticesSize = sizeof(s_vertexDataOctahedron);
			m_indicesSize = sizeof(s_indexDataOctahedron);
			break;
		default:
			printf("No model data found\n");
			break;
		}//switch

		printf("trying...\n");
		m_vertexCount = m_verticesSize / sizeof(m_vertices[0]);
		m_indexCount = m_indicesSize / sizeof(m_indices[0]);
		if (copyDataToGPU(_garlicAlloc) == SCE_OK && m_vertexCount >= 3)
		{
			printf("Yay valid data");
			m_validData = true;
		}
	}//loadHardModel()


	int ptModel::loadModelOBJ(const char* _filename, LinearAllocator* _garlicAlloc)
	{
		int l_error = SCE_OK;

		//Lets have our own memory allocator
		LinearAllocator myOnionAllocator;
		l_error = myOnionAllocator.initialize(m_onionMemorySize, SCE_KERNEL_WB_ONION,
			SCE_KERNEL_PROT_CPU_RW | SCE_KERNEL_PROT_GPU_ALL);
		if (l_error != SCE_OK) {
			printf("Onion allocator failed to initialise: 0x%08X\n", l_error);
			return l_error;
		}

		//file parser
		danFileParser myDFP;
		l_error = myDFP.openFile(_filename);
		if (l_error != SCE_OK) {
			printf("Unable to load file in model\n"); return SCE_ERROR_ERROR_FLAG;
		}

		int l_pCount = 0; //vertex positions
		int l_uCount = 0; //vertex texture coordinates
		int l_nCount = 0; //vertex normals
		int l_fCount = 0; //faces
		int l_tCount = 0; //triangles
		int l_vCount = 0; //vertex index sets

		float l_A = 0, l_B = 0, l_C = 0;	//for float data
		int l_smoothingGroup;

		while (!myDFP.atEOF())
		{
			if (myDFP.getWord(l_lineType))
			{
				if (myDFP.stringCompare(l_lineType, "v"))
				{
					l_pCount++;
				}
				else if (myDFP.stringCompare(l_lineType, "vt"))
				{
					l_uCount++;
				}
				else if (myDFP.stringCompare(l_lineType, "vn"))
				{
					l_nCount++;
				}
				else if (myDFP.stringCompare(l_lineType, "f"))
				{
					int counter = 0;
					while (myDFP.getWordNoNewLine(l_vertexString)) counter++;
					l_vCount += counter;
					l_tCount += counter - 2;
					l_fCount++;
				}//if
			}
			myDFP.nextLine();
		}

		if (m_verbose) printf("Found %i positions, %i texcoords and %i normals\n", l_pCount, l_uCount, l_nCount);
		if (m_verbose) printf("Found %i triangles, in %i faces (using %i vertices)\n", l_tCount, l_fCount, l_vCount);
		m_indexCount = l_tCount * 3;

		size_t t_objPosSize = l_pCount * sizeof(danObjPosition);
		danObjPosition* l_objPositions = (danObjPosition*)myOnionAllocator.allocate(t_objPosSize, Gnm::kAlignmentOfBufferInBytes);
		if (!l_objPositions) 
		{ 
			printf("Unable to allocate memory for ObjPositions in ptModel::loadModelOBJ\n");
			return SCE_ERROR_ERROR_FLAG;
		}
		
		size_t t_objTexSize = l_uCount * sizeof(danObjTexcoord);
		danObjTexcoord* l_objTexcoords = (danObjTexcoord*)myOnionAllocator.allocate(t_objTexSize, Gnm::kAlignmentOfBufferInBytes);
		if (!l_objTexcoords)
		{
			printf("Unable to allocate memory for ObjTexcoords in ptModel::loadModelOBJ\n");
			return SCE_ERROR_ERROR_FLAG;
		}

		size_t t_objNormSize = l_nCount * sizeof(danObjNormal);
		danObjNormal* l_objNormals = (danObjNormal*)myOnionAllocator.allocate(t_objNormSize, Gnm::kAlignmentOfBufferInBytes);
		if (!l_objNormals)
		{
			printf("Unable to allocate memory for ObjNormals in ptModel::loadModelOBJ\n");
			return SCE_ERROR_ERROR_FLAG;
		}

		size_t t_objTripSize = l_vCount * sizeof(danObjTriple);
		danObjTriple* l_objTriples = (danObjTriple*)myOnionAllocator.allocate(t_objTripSize, Gnm::kAlignmentOfBufferInBytes);
		if (!l_objTriples)
		{
			printf("Unable to allocate memory for ObjTriples in ptModel::loadModelOBJ\n");
			return SCE_ERROR_ERROR_FLAG;
		}

		//m_indices memory. This is will eventually be the final index data
		//indices will start by using indices to danObjTriple objects
		m_indicesSize = sizeof(uint16_t) * m_indexCount;
		m_indices = (uint16_t*)myOnionAllocator.allocate(m_indicesSize, Gnm::kAlignmentOfBufferInBytes);
		if (!m_indices)
		{
			printf("Unable to allocate memory for m_indices in ptModel::loadModelOBJ\n");
			return SCE_ERROR_ERROR_FLAG;
		}
		m_triangles = (ptTriangle*)m_indices;

		myDFP.reset();

		l_pCount = 0;
		l_uCount = 0;
		l_nCount = 0;
		l_fCount = 0;
		l_vCount = 0;
		l_tCount = 0;

		while (!myDFP.atEOF())
		{
			if (myDFP.getWord(l_lineType))
			{
				if (myDFP.stringCompare(l_lineType, "v"))
				{
					if (myDFP.getFloat(l_A) &&
						myDFP.getFloat(l_B) && myDFP.getFloat(l_C))
					{
						l_objPositions[l_pCount].x = l_A;
						l_objPositions[l_pCount].y = l_B;
						l_objPositions[l_pCount].z = l_C;
						l_pCount++;
						if (m_verbose)
						{
							printf("Position[%i] = (%f, %f, %f)\n", l_pCount, l_A, l_B, l_C);
						}
					}//if
				}
				else if (myDFP.stringCompare(l_lineType, "vt"))
				{
					if (myDFP.getFloat(l_A) &&
						myDFP.getFloat(l_B))
					{
						l_objTexcoords[l_uCount].u = l_A;
						l_objTexcoords[l_uCount].v = 1 - l_B;
						l_uCount++;
						if (m_verbose)
						{
							printf("Position[%i] = (%f, %f)\n", l_uCount, l_A, l_B);
						}
					}//if
				}
				else if (myDFP.stringCompare(l_lineType, "vn"))
				{
					if (myDFP.getFloat(l_A) &&
						myDFP.getFloat(l_B) && myDFP.getFloat(l_C))
					{
						l_objNormals[l_nCount].x = l_A;
						l_objNormals[l_nCount].y = l_B;
						l_objNormals[l_nCount].z = l_C;
						l_nCount++;
						if (m_verbose)
						{
							printf("Position[%i] = (%f, %f, %f)\n", l_nCount, l_A, l_B, l_C);
						}
					}//if
				}
				else if (myDFP.stringCompare(l_lineType, "s"))
				{
					if (myDFP.getInt(l_smoothingGroup))
					{
						if (l_smoothingGroup < 0 || l_smoothingGroup > __UINT16_MAX__)
						{
							l_smoothingGroup = 0;
						}
					}
					else
					{
						l_smoothingGroup = 0;
					}
				}
				else if (myDFP.stringCompare(l_lineType, "f"))
				{
					int t_counter = 0;
					int t_triA = l_vCount;
					//printf(l_lineType);
					//parse index data into our ptObjTriples structure
					while (myDFP.getWordNoNewLine(l_vertexString))
					{
						l_objTriples[l_vCount].parseTriple(l_vertexString, l_pCount, l_uCount, l_nCount, l_smoothingGroup);
						t_counter++;
						l_vCount++;
						//printf("l_vCount = %i ", l_vCount);
					}
					//printf("\n");
					//create triangles from faces
					//this is tricky to work out the logic, basically a face is a triangle fan
					int t_secondCounter = 2;
					while (t_secondCounter < t_counter)
					{
						m_triangles[l_tCount].a = t_triA;
						m_triangles[l_tCount].b = t_triA + t_secondCounter - 1;
						m_triangles[l_tCount].c = t_triA + t_secondCounter;
						t_secondCounter++;
						l_tCount++;

						//stage to compress data, by removing duplicate triples
						if (m_verbose)
						{
							printf("Compressing triples data to remove duplicates. Please wait\n");
							printf("Storing triangle %i: %i %i %i\n", l_tCount, m_triangles[l_tCount].a, m_triangles[l_tCount].b, m_triangles[l_tCount].c);
						}

					}//while
					l_fCount++;
				}//if
			}
			myDFP.nextLine();
		}


		//find duplicates
		for (int i = 0; i < l_vCount; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (l_objTriples[i].matchAndMark(&l_objTriples[j], j))
				{
					if (m_verbose)
					{
						printf("Triple %i is a duplicate of %i\n", i, j);
					}
					j = i;
				}
			}//for j
		}//for i

		 //mark "real index" on originals by counting through them
		int l_rCount = 0;
		for (int i = 0; i < l_vCount; i++)
		{
			if (!l_objTriples[i].m_duplicate)
			{
				l_objTriples[i].m_realIndex = l_rCount;
				l_rCount++;
				if (m_verbose)
				{
					printf("R Count for Originals %i\n", l_rCount);
				}
			}//if
		}//for

		 //create memory for final vertex data
		m_vertexCount = l_rCount;
		m_verticesSize = sizeof(ptVertex)*m_vertexCount;
		m_vertices = (ptVertex*)myOnionAllocator.allocate(m_verticesSize, Gnm::kAlignmentOfBufferInBytes);
		if (!m_vertices)
		{
			printf("Unable to allocate memory for m_vertices in ptModel::loadModelOBJ\n");
			return SCE_ERROR_ERROR_FLAG;
		}

		//copy vertex data from intermediate arrays to final array 
		//use counter to ONLY transfer the originals and not duplicates 
		int t_counter = 0;
		for (int i = 0; i < l_vCount; i++)
		{
			if (!l_objTriples[i].m_duplicate)
			{
				if (l_objTriples[i].m_gotPosition)
				{
					m_vertices[t_counter].x = l_objPositions[l_objTriples[i].m_positionIndex].x;
					m_vertices[t_counter].y = l_objPositions[l_objTriples[i].m_positionIndex].y;
					m_vertices[t_counter].z = l_objPositions[l_objTriples[i].m_positionIndex].z;
				}//if
				t_counter++;
			}//if
		}//for

		int n_counter = 0;
		for (int i = 0; i < 1; i++)
		{
			m_vertices[n_counter].nx = l_objNormals[i].x;
			m_vertices[n_counter].ny = l_objNormals[i].y;
			m_vertices[n_counter].nz = l_objNormals[i].z;
			n_counter++;
		}

		 //correct indices in m_indices to point to correct places in m_vertices
		for (int i = 0; i < m_indexCount; i++)
		{
			if (l_objTriples[m_indices[i]].m_duplicate)
			{
				if (m_verbose)
				{
					printf("index %i is %i\n", i, m_indices[i]);
				}
				m_indices[i] = l_objTriples[l_objTriples[m_indices[i]].m_duplicateIndex].m_realIndex;
			}
			else
			{
				if (m_verbose)
				{
					printf("index %i is %i\n", i, m_indices[i]);
				}
				m_indices[i] = l_objTriples[m_indices[i]].m_realIndex;
			}
		}//for

		 //data generation
		//fillRandomColour();
		if (m_generateNormals)
		{
			generateNormals();
		}
		if (m_oneColour)
		{
			fillColour(m_defaultColour);
		}

		l_error = copyDataToGPU(_garlicAlloc);
		if (l_error != SCE_OK)
		{
			printf("Unable to copy model data to GPU memory: 0x%08X\n", l_error); 
			return l_error;
		}

		m_validData = true;
		myOnionAllocator.terminate();

		return l_error;
	}

	int ptModel::copyDataToGPU(LinearAllocator* _garlicAlloc)
	{
		int l_result = SCE_OK;
		// Allocate the vertex buffer memory
		m_gpuVertexData = static_cast<ptVertex*>(_garlicAlloc->allocate(
			m_verticesSize, Gnm::kAlignmentOfBufferInBytes));
		if (!m_gpuVertexData) 
		{ 
			printf("Cannot allocate vertex data\n"); 
			return SCE_KERNEL_ERROR_ENOMEM;
		}

		// Allocate the index buffer memory
		m_gpuIndexData = static_cast<uint16_t*>(_garlicAlloc->allocate(
			m_indicesSize, Gnm::kAlignmentOfBufferInBytes));
		if (!m_gpuIndexData) 
		{ 
			printf("Cannot allocate index data\n");
			return SCE_KERNEL_ERROR_ENOMEM;
		}

		// Copy the vertex/index data onto the GPU mapped memory
		memcpy(m_gpuVertexData, m_vertices, m_verticesSize);
		memcpy(m_gpuIndexData, m_indices, m_indicesSize);
		initAsVertexBuffer();
		if (l_result == SCE_OK)
		{

			printf("Yay valid data\n");
		}
		return l_result;
	}//copyDataToGPU()

	void ptModel::cleanNormals()
	{
		for (int i = 0; i < m_verticesSize; i++)
		{
			m_vertices[i].nx = 0;
			m_vertices[i].ny = 0;
			m_vertices[i].nz = 0;
		}
	}

	void ptModel::generateNormals()
	{
		cleanNormals();
		for (int i = 0; i < m_indexCount / 3; i++)
		{
			Vector3 t_A(m_vertices[m_triangles[i].a].x, m_vertices[m_triangles[i].a].y, m_vertices[m_triangles[i].a].z);
			Vector3 t_B(m_vertices[m_triangles[i].b].x, m_vertices[m_triangles[i].b].y, m_vertices[m_triangles[i].b].z);
			Vector3 t_C(m_vertices[m_triangles[i].c].x, m_vertices[m_triangles[i].c].y, m_vertices[m_triangles[i].c].z);

			Vector3 t_AB = t_B - t_A;
			Vector3 t_AC = t_C - t_A;

			Vector3 t_crossProduct = Vectormath::Scalar::Aos::cross(t_AB, t_AC);

			Vector3 t_normalized = Vectormath::Scalar::Aos::normalize(t_crossProduct);

			m_vertices[m_triangles[i].a].nx += t_normalized.getX();
			m_vertices[m_triangles[i].a].ny += t_normalized.getY();
			m_vertices[m_triangles[i].a].nz += t_normalized.getZ();
			m_vertices[m_triangles[i].b].nx += t_normalized.getX();
			m_vertices[m_triangles[i].b].ny += t_normalized.getY();
			m_vertices[m_triangles[i].b].nz += t_normalized.getZ();
			m_vertices[m_triangles[i].c].nx += t_normalized.getX();
			m_vertices[m_triangles[i].c].ny += t_normalized.getY();
			m_vertices[m_triangles[i].c].nz += t_normalized.getZ();
		}
		normalizeNormals();
	}

	void ptModel::normalizeNormals()
	{
		for (int i = 0; i < m_vertexCount; i++)
		{
			float length = sqrt(m_vertices[i].nx * m_vertices[i].nx +
				m_vertices[i].ny * m_vertices[i].ny +
				m_vertices[i].nz * m_vertices[i].nz);
			m_vertices[i].nx = m_vertices[i].nx / length;
			m_vertices[i].ny = m_vertices[i].ny / length;
			m_vertices[i].nz = m_vertices[i].nz / length;
		}
	}

	void ptModel::initAsVertexBuffer() {
		m_vertexBuffers[PT_VERTEX_POSITION].initAsVertexBuffer(
			&m_gpuVertexData[0].x,
			Gnm::kDataFormatR32G32B32Float,
			sizeof(ptVertex),
			m_vertexCount);

		m_vertexBuffers[PT_VERTEX_COLOUR].initAsVertexBuffer(
			&m_gpuVertexData[0].r,
			Gnm::kDataFormatR32G32B32Float,
			sizeof(ptVertex),
			m_vertexCount);
		
		m_vertexBuffers[PT_VERTEX_NORMAL].initAsVertexBuffer(
			&m_gpuVertexData[0].nx,
			Gnm::kDataFormatR32G32B32Float,
			sizeof(ptVertex),
			m_vertexCount);

		m_vertexBuffers[PT_VERTEX_TEXCOORD].initAsVertexBuffer(
			&m_gpuVertexData[0].u,
			Gnm::kDataFormatR32G32Float,
			sizeof(m_vertices[0]),
			m_vertexCount);
	}

	void ptModel::printPositions()
	{
		for (int i = 0; i < m_vertexCount; i++)
		{
			printf("P %i %f %f %f\n", i, m_gpuVertexData[i].x, m_gpuVertexData[i].y, m_gpuVertexData[i].z);
		}
	}

	void ptModel::printTriangles()
	{
		for (int i = 0; i < m_indexCount; i+=3)
		{
			printf("T %i %i %i %i\n", i, m_gpuIndexData[i], m_gpuIndexData[i+1], m_gpuIndexData[i+2]);
		}
	}

	void ptModel::printColours()
	{
		for (int i = 0; i < m_vertexCount; i++)
		{
			printf("C %i %f %f %f\n", i, m_gpuVertexData[i].r, m_gpuVertexData[i].b, m_gpuVertexData[i].g);
		}
	}

	void ptModel::printNormals()
	{
		for (int i = 0; i < m_vertexCount; i++)
		{
			printf("N %i %f %f %f\n", i, m_gpuVertexData[i].nx, m_gpuVertexData[i].ny, m_gpuVertexData[i].nz);
		}
	}