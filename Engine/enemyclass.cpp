#include "enemyclass.h"

EnemyClass::EnemyClass(ModelClass* model, ModelShaderClass* modelShader, float x, float y, float z) : VehicleClass(model, modelShader)
{
	m_width = 30.0f;
	m_height = 5.0f;

	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;

	m_health = 2.0f;
}


EnemyClass::~EnemyClass(void)
{
}


D3DXMATRIX EnemyClass::GetWorldMatrix()
{
	D3DXMATRIX worldMatrix, rotationMatrixY, scaleMatrix, translationMatrix;

	//D3DXMatrixScaling(&scaleMatrix, 0.25f, 0.25f, 0.25f);
	D3DXMatrixRotationY(&rotationMatrixY, (m_rotationY + 180.0f) * 0.0174532925f);
	D3DXMatrixTranslation(&translationMatrix, m_positionX, m_positionY, m_positionZ);

	worldMatrix = /*scaleMatrix * */ rotationMatrixY * translationMatrix;

	return worldMatrix;
}

// Simple AI to move the car around
void EnemyClass::Move()
{
	if(m_health > 0.0f)
	{
		MoveForward(true);
		TurnLeft(true);
	}
}