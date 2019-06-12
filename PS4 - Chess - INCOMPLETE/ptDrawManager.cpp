#include "ptDrawManager.h"


ptDrawManager::ptDrawManager(ptLight* lightSystem)
{
	m_myLights = lightSystem;
}

void ptDrawManager::draw(Gnmx::GnmxGfxContext* _gfxc, ptObject* _object, ptCamera* _camera)
{
	if (_object->m_myModel->m_validData)
	{
		static float t_angle = 0.0f;
		t_angle += 1.0f / 120.0f;

		ptShaderConstants *l_shaderConstants = static_cast<ptShaderConstants*>(
			_gfxc->allocateFromCommandBuffer(sizeof(ptShaderConstants), Gnm::kEmbeddedDataAlignment4));
		m_myLights[3].m_colour = Vector3(1.0, 0.5, 0);
		m_myLights[3].m_locationVx = Vector3(0.0, 1.0, 0.5);
		if (l_shaderConstants)
		{
			for (int i = 0; i < __PT_LIGHT_COUNT__; i++)
			{

				l_shaderConstants->shc_modelProjMx[i] = _camera->m_projectionMx * _camera->m_worldViewMx * _object->m_modelWorldMx;
				l_shaderConstants->shc_normalTransMx[i] = transpose(inverse(_object->m_modelWorldMx));
				l_shaderConstants->shc_angle[i] = t_angle;
				Gnm::Buffer t_constBuffer;
				l_shaderConstants->shc_modelWorldMx[i] = _object->m_modelWorldMx;
				Matrix4 t_invWorldView = inverse(_camera->m_worldViewMx);
				t_invWorldView.getCol3();

				//assign Light

				l_shaderConstants->shc_lightADSVx[i] = Vector4(m_myLights[i].m_ambientFactor, m_myLights[i].m_diffuseFactor, m_myLights[i].m_specularFactor, 0);

				float t_colour = 0.0;
				if (m_myLights[i].m_isOn)
				{
					t_colour = 1.0;
				}
				l_shaderConstants->shc_lightColourVx[i] = Vector4(m_myLights[i].m_colour, t_colour);

				float t_infinite = 0.0;
				if (m_myLights[i].m_isInfinite)
				{
					t_infinite = 1.0;
				}
				l_shaderConstants->shc_lightLocationVX[i] = Vector4(m_myLights[i].m_locationVx, t_infinite);

				float t_directional = 1.1;
				if (m_myLights[i].m_isDirectional)
				{
					t_directional = 0.0;
				}
				l_shaderConstants->shc_lightSpotDirectionVx[i] = Vector4(m_myLights[i].m_directionVx, t_directional);

				float t_distance = 0.0;
				if (m_myLights[i].m_useDistanceAttn)
				{
					t_distance = 1.0;
				}
				l_shaderConstants->shc_lightAttenuationVx[i] = Vector4(m_myLights[i].m_fixedAttnFactor, m_myLights[i].m_linearAttnFactor, m_myLights[i].m_quadAttnFactor, t_distance);

				//assign textures 
				// Setup the texture and its sampler on the pixel shader stage
				_gfxc->setTextures(Gnm::kShaderStagePs, 0, 1, _object->m_myTexture);
				_gfxc->setSamplers(Gnm::kShaderStagePs, 0, 1, _object->m_mySampler);

				t_constBuffer.initAsConstantBuffer(l_shaderConstants, sizeof(ptShaderConstants));
				_gfxc->setConstantBuffers(Gnm::kShaderStageVs, 0, 1, &t_constBuffer);
				_gfxc->setConstantBuffers(Gnm::kShaderStagePs, 0, 1, &t_constBuffer);
			}
		}

		_gfxc->setVertexBuffers(Gnm::kShaderStageVs, 0, PT_VERTEX_ELEM_COUNT, _object->m_myModel->m_vertexBuffers);

		// Submit a draw call
		_gfxc->setPrimitiveType(Gnm::kPrimitiveTypeTriList);
		_gfxc->setIndexSize(Gnm::kIndexSize16);
		_gfxc->drawIndex(_object->m_myModel->m_indexCount, _object->m_myModel->m_gpuIndexData);
	}
	//else printf("Invalid Model Data\n");
}

void ptDrawManager::draw(Gnmx::GnmxGfxContext* _gfxc, ptHUDTextItem* _object, ptCamera* _camera)
{
	if (_object->m_validData)
	{
		static float t_angle = 0.0f;
		t_angle += 1.0f / 120.0f;

		ptShaderConstants *l_shaderConstants = static_cast<ptShaderConstants*>(
			_gfxc->allocateFromCommandBuffer(sizeof(ptShaderConstants), Gnm::kEmbeddedDataAlignment4));
		m_myLights[3].m_colour = Vector3(1.0, 0.5, 0);
		m_myLights[3].m_locationVx = Vector3(0.0, 1.0, 0.5);
		if (l_shaderConstants)
		{
			for (int i = 0; i < __PT_LIGHT_COUNT__; i++)
			{

				l_shaderConstants->shc_modelProjMx[i] = _camera->m_projectionMx * _camera->m_worldViewMx * _object->m_modelWorldMx;
				l_shaderConstants->shc_normalTransMx[i] = transpose(inverse(_object->m_modelWorldMx));
				l_shaderConstants->shc_angle[i] = t_angle;
				Gnm::Buffer t_constBuffer;
				l_shaderConstants->shc_modelWorldMx[i] = _object->m_modelWorldMx;
				Matrix4 t_invWorldView = inverse(_camera->m_worldViewMx);
				t_invWorldView.getCol3();

				//assign Light

				l_shaderConstants->shc_lightADSVx[i] = Vector4(m_myLights[i].m_ambientFactor, m_myLights[i].m_diffuseFactor, m_myLights[i].m_specularFactor, 0);

				float t_colour = 0.0;
				if (m_myLights[i].m_isOn)
				{
					t_colour = 1.0;
				}
				l_shaderConstants->shc_lightColourVx[i] = Vector4(m_myLights[i].m_colour, t_colour);

				float t_infinite = 0.0;
				if (m_myLights[i].m_isInfinite)
				{
					t_infinite = 1.0;
				}
				l_shaderConstants->shc_lightLocationVX[i] = Vector4(m_myLights[i].m_locationVx, t_infinite);

				float t_directional = 1.1;
				if (m_myLights[i].m_isDirectional)
				{
					t_directional = 0.0;
				}
				l_shaderConstants->shc_lightSpotDirectionVx[i] = Vector4(m_myLights[i].m_directionVx, t_directional);

				float t_distance = 0.0;
				if (m_myLights[i].m_useDistanceAttn)
				{
					t_distance = 1.0;
				}
				l_shaderConstants->shc_lightAttenuationVx[i] = Vector4(m_myLights[i].m_fixedAttnFactor, m_myLights[i].m_linearAttnFactor, m_myLights[i].m_quadAttnFactor, t_distance);

				//assign textures 
				//// Setup the texture and its sampler on the pixel shader stage
				//_gfxc->setTextures(Gnm::kShaderStagePs, 0, 1, _object->m_myTexture);
				//_gfxc->setSamplers(Gnm::kShaderStagePs, 0, 1, _object->m_mySampler);

				t_constBuffer.initAsConstantBuffer(l_shaderConstants, sizeof(ptShaderConstants));
				_gfxc->setConstantBuffers(Gnm::kShaderStageVs, 0, 1, &t_constBuffer);
				_gfxc->setConstantBuffers(Gnm::kShaderStagePs, 0, 1, &t_constBuffer);
			}
		}

		_gfxc->setVertexBuffers(Gnm::kShaderStageVs, 0, PT_VERTEX_ELEM_COUNT, _object->m_vertexBuffers);

		// Submit a draw call
		_gfxc->setPrimitiveType(Gnm::kPrimitiveTypeTriList);
		_gfxc->setIndexSize(Gnm::kIndexSize16);
		_gfxc->drawIndex(_object->m_indexCount, _object->m_indicesGPU);
	}
	//else printf("Invalid Model Data\n");
}