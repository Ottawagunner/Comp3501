#include "enemyclass.h"

EnemyClass::EnemyClass(ModelClass* model, ModelShaderClass* modelShader, float x, float y, float z) : VehicleClass(model, modelShader)
{
	m_width = 30.0f;
	m_height = 5.0f;

	m_state.x.x = x;
	m_state.x.y = y;
	m_state.x.z = z;

	m_health = 2.0f;
}


EnemyClass::~EnemyClass(void)
{
}


D3DXMATRIX EnemyClass::GetWorldMatrix()
{
	D3DXMATRIX worldMatrix, initialPositionChangeMatrix, rotationMatrixY, scaleMatrix, translationMatrix;

	D3DXMatrixTranslation(&initialPositionChangeMatrix, 100.0f, 0.0f, -80.0f);
	D3DXMatrixScaling(&scaleMatrix, 0.15f, 0.15f, 0.15f);
	D3DXMatrixRotationY(&rotationMatrixY, (m_rotationY + 180.0f) * 0.0174532925f);
	D3DXMatrixTranslation(&translationMatrix, m_state.x.x, m_state.x.y, m_state.x.z);

	worldMatrix = initialPositionChangeMatrix * scaleMatrix * rotationMatrixY * translationMatrix;

	return worldMatrix;
}

// Simple AI to move the car around
void EnemyClass::Move()
{
	if(m_health > 0.0f)
	{
		ApplyForwardForce(true);
		TurnLeft(true);
	}
}