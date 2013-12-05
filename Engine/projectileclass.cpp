#include "projectileclass.h"


ProjectileClass::ProjectileClass(ModelClass* model, ModelShaderClass* modelShader, float px, float py, float pz, float rx, float ry, float rz) : MobileEntityClass(model, modelShader)
{
	m_rotationX = rx;
	m_rotationY = ry;
	m_rotationZ = rz;

	m_state.x.x = m_initialPositionX = px;
	// We add a constant value to the y coordinate to position the projectile correctly in front of the turret
	m_state.x.y = m_initialPositionY = py + 4.0f;
	m_state.x.z = m_initialPositionZ = pz;

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
	float a = m_state.x.x - m_initialPositionX;
	float b = m_state.x.z - m_initialPositionZ;

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
	D3DXMatrixTranslation(&translationMatrix, m_state.x.x, m_state.x.y, m_state.x.z);
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
	m_state.x.x += sinf(radians) * m_forwardSpeed;
	m_state.x.z += cosf(radians) * m_forwardSpeed;
}