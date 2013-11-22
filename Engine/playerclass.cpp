#include "playerclass.h"


PlayerClass::PlayerClass(void) : MobileEntityClass()
{
	m_lookUpSpeed    = 0.0f;
	m_lookDownSpeed  = 0.0f;
}


PlayerClass::~PlayerClass(void)
{
}

bool PlayerClass::RenderModel(ID3D11DeviceContext* deviceContext,  ModelClass** model, ModelShaderClass* modelShader,  LightClass* light, D3DXMATRIX* viewMatrix, D3DXMATRIX* projectionMatrix)
{
	ModelClass* body = model[0];
	ModelClass* turret = model[1];

	bool result = true;

	D3DXMATRIX worldMatrix, rotationMatrixY, scaleMatrix, translationMatrix, turretRelativeHeight;

	D3DXMatrixScaling(&scaleMatrix, 0.25f, 0.25f, 0.25f);
	D3DXMatrixRotationY(&rotationMatrixY, (m_rotationY + 180.0f) * 0.0174532925f);
	D3DXMatrixTranslation(&translationMatrix, m_positionX, m_positionY, m_positionZ);

	worldMatrix = scaleMatrix * rotationMatrixY * translationMatrix;

	// Render the model buffers.
	body->Render(deviceContext);

	// Render the body using the model shader.
	result = modelShader->Render(deviceContext, body->GetIndexCount(), worldMatrix, *viewMatrix, *projectionMatrix, 
									 light->GetAmbientColor(), light->GetDiffuseColor(), light->GetDirection(), body->GetTexture());

	
	// Render the turret using the model shader
	D3DXMatrixTranslation(&turretRelativeHeight, 0.0f, 5.0f, 0.0f);
	worldMatrix = worldMatrix * turretRelativeHeight;

	turret->Render(deviceContext);

	result = modelShader->Render(deviceContext, turret->GetIndexCount(), worldMatrix, *viewMatrix, *projectionMatrix, 
									 light->GetAmbientColor(), light->GetDiffuseColor(), light->GetDirection(), turret->GetTexture());

	return result;
}

void PlayerClass::LookUpward(bool keydown)
{
	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_lookUpSpeed += m_frameTime * 0.01f;

		if(m_lookUpSpeed > (m_frameTime * 0.15f))
		{
			m_lookUpSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_lookUpSpeed -= m_frameTime* 0.005f;

		if(m_lookUpSpeed < 0.0f)
		{
			m_lookUpSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX -= m_lookUpSpeed;

	// Keep the rotation maximum 90 degrees.
	if(m_rotationX > 90.0f)
	{
		m_rotationX = 90.0f;
	}

	return;
}

void PlayerClass::LookDownward(bool keydown)
{
	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_lookDownSpeed += m_frameTime * 0.01f;

		if(m_lookDownSpeed > (m_frameTime * 0.15f))
		{
			m_lookDownSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_lookDownSpeed -= m_frameTime* 0.005f;

		if(m_lookDownSpeed < 0.0f)
		{
			m_lookDownSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX += m_lookDownSpeed;

	// Keep the rotation maximum 90 degrees.
	if(m_rotationX < -90.0f)
	{
		m_rotationX = -90.0f;
	}

	return;
}