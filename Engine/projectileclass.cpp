#include "projectileclass.h"


ProjectileClass::ProjectileClass(ModelClass* model, ModelShaderClass* modelShader, float px, float py, float pz, float rx, float ry, float rz) : MobileEntityClass(model, modelShader)
{
	m_positionX = m_initialPositionX = px;
	m_positionY = m_initialPositionY = py;
	m_positionZ = m_initialPositionZ = pz;

	m_rotationX = rx;
	m_rotationY = ry;
	m_rotationZ = rz;

	m_forwardSpeed = 1.5f;

	m_width = 5.0f;
	
	m_maxDistance = 120.0f;
	m_isDead = false;
}


ProjectileClass::~ProjectileClass(void)
{
}

bool ProjectileClass::IsStillAlive()
{
	// Check to see if the projectile has gone farther than its max distance
	float a = m_positionX - m_initialPositionX;
	float b = m_positionZ - m_initialPositionZ;

	float c = sqrt(a*a + b*b);

	return c <= m_maxDistance && !m_isDead;
}

void ProjectileClass::Stop()
{
	m_isDead = true;
}

D3DXMATRIX ProjectileClass::GetWorldMatrix()
{
	D3DXMATRIX worldMatrix, translationMatrix, scaleMatrix, rotationMatrix;

	D3DXMatrixScaling(&scaleMatrix, 0.5f, 0.5f, 0.5f);
	D3DXMatrixTranslation(&translationMatrix, m_positionX, m_positionY, m_positionZ);
	//D3DXMatrixRotationY(&rotationMatrix, m_rotationY);

	worldMatrix = scaleMatrix * /*rotationMatrix * */translationMatrix;

	return worldMatrix;
}

void ProjectileClass::MoveForward(bool redundant)
{
	float radians;

	// Convert degrees to radians.
	radians = m_rotationY * 0.0174532925f;

	// Update the position.
	m_positionX += sinf(radians) * m_forwardSpeed;
	m_positionZ += cosf(radians) * m_forwardSpeed;
}