#include "modeledobjectclass.h"

ModeledObjectClass::ModeledObjectClass(ModelClass* model, ModelShaderClass* modelShader)
{
	m_model = model;
	m_modelShader = modelShader;
}

bool ModeledObjectClass::RenderModel(ID3D11DeviceContext* deviceContext, LightClass* light, D3DXMATRIX* viewMatrix, D3DXMATRIX* projectionMatrix)
{
	bool result = true;

	// Render the model buffers.
	m_model->Render(deviceContext);

	// Render the model using the model shader.
	result = m_modelShader->Render(deviceContext, m_model->GetIndexCount(), GetWorldMatrix(), *viewMatrix, *projectionMatrix, 
									 light->GetAmbientColor(), light->GetDiffuseColor(), light->GetDirection(), m_model->GetTexture());

	return result;
}