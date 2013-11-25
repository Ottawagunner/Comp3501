#pragma once

#include "mobileentityclass.h"

class ProjectileClass : public MobileEntityClass
{
public:
	ProjectileClass(ModelClass* model, ModelShaderClass* modelShader, float px, float py, float pz, float rx, float ry, float rz);
	~ProjectileClass(void);

	void Stop();
	bool IsStillAlive();

	// Override
	void MoveForward(bool redundant = true);
	
	D3DXMATRIX GetWorldMatrix();

protected:		
	float m_initialPositionX, m_initialPositionY, m_initialPositionZ;

	float m_maxDistance;
	bool m_isDead;
};

