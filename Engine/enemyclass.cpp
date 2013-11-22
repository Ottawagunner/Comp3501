#include "enemyclass.h"


EnemyClass::EnemyClass(void) : MobileEntityClass()
{
}

EnemyClass::EnemyClass(float x, float y, float z) : MobileEntityClass()
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
}


EnemyClass::~EnemyClass(void)
{
}


bool EnemyClass::RenderModel(ID3D11DeviceContext* deviceContext,  ModelClass** model, ModelShaderClass* modelShader, LightClass* light, D3DXMATRIX* viewMatrix, D3DXMATRIX* projectionMatrix)
{
	bool result = true;

	D3DXMATRIX worldMatrix, rotationMatrixY, scaleMatrix, translationMatrix;

	//D3DXMatrixScaling(&scaleMatrix, 0.25f, 0.25f, 0.25f);
	D3DXMatrixRotationY(&rotationMatrixY, (m_rotationY + 180.0f) * 0.0174532925f);
	D3DXMatrixTranslation(&translationMatrix, m_positionX, m_positionY, m_positionZ);

	worldMatrix = /*scaleMatrix * */ rotationMatrixY * translationMatrix;

	// Render the model buffers.
	(*model)->Render(deviceContext);

	// Render the model using the model shader.
	result = modelShader->Render(deviceContext, (*model)->GetIndexCount(), worldMatrix, *viewMatrix, *projectionMatrix, 
									 light->GetAmbientColor(), light->GetDiffuseColor(), light->GetDirection(), (*model)->GetTexture());

	return result;
}

// Simple AI to move the car around
void EnemyClass::Move()
{
	MoveForward(true);
	TurnLeft(true);
}