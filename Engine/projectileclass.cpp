#include "projectileclass.h"


ProjectileClass::ProjectileClass(float birthday, float px, float py, float pz, float rx, float ry, float rz)
{
	m_positionX = px;
	m_positionY = py;
	m_positionZ = pz;

	m_rotationX = rx;
	m_rotationY = ry;
	m_rotationZ = rz;

	m_secondsAlive = 5.0f;
	m_birthday = birthday;

	m_speed = 0.5f;
}


ProjectileClass::~ProjectileClass(void)
{
}

bool ProjectileClass::IsStillAlive(float gameTime)
{
	return (gameTime - m_birthday) > m_secondsAlive;
}

bool ProjectileClass::RenderModel(ID3D11DeviceContext* deviceContext, ModelClass* model, ModelShaderClass* modelShader, LightClass* light, D3DXMATRIX* viewMatrix, D3DXMATRIX* projectionMatrix)
{
	bool result = true;

	D3DXMATRIX worldMatrix, translationMatrix, scaleMatrix, rotationMatrix;

	D3DXMatrixScaling(&scaleMatrix, 0.10f, 0.10f, 0.10f);
	D3DXMatrixTranslation(&translationMatrix, m_positionX, m_positionY, m_positionZ);
	//D3DXMatrixRotationY(&rotationMatrix, m_rotationY);

	worldMatrix = scaleMatrix * /*rotationMatrix * */translationMatrix;

	// Render the model buffers.
	model->Render(deviceContext);

	// Render the model using the model shader.
	result = modelShader->Render(deviceContext, model->GetIndexCount(), worldMatrix, *viewMatrix, *projectionMatrix, 
									 light->GetAmbientColor(), light->GetDiffuseColor(), light->GetDirection(), model->GetTexture());

	return result;
}

void ProjectileClass::Move()
{
	float radians;

	// Convert degrees to radians.
	radians = m_rotationY * 0.0174532925f;

	// Update the position.
	m_positionX += sinf(radians) * m_speed;
	m_positionZ += cosf(radians) * m_speed;
}
