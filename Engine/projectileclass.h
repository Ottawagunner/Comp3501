#pragma once

#include "modeledobjectclass.h"

class ProjectileClass : public ModeledObjectClass
{
public:
	ProjectileClass(ModelClass* model, ModelShaderClass* modelShader, float px, float py, float pz, float rx, float ry, float rz);
	~ProjectileClass(void);

	void Stop();
	bool IsStillAlive();
	void Move();
	
	D3DXMATRIX GetWorldMatrix();

protected:		
	float m_initialPositionX, m_initialPositionY, m_initialPositionZ;
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	float m_speed;
	float m_maxDistance;
	bool m_isDead;
};

