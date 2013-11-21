#pragma once

#include "modeledobjectclass.h"

class ProjectileClass : public ModeledObjectClass
{
public:
	ProjectileClass(float birthday, float px, float py, float pz, float rx, float ry, float rz);
	~ProjectileClass(void);

	bool RenderModel(ID3D11DeviceContext*, LightClass*, D3DXMATRIX*, D3DXMATRIX*);

	bool IsStillAlive(float gameTime);
	void Move();

protected:		
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	float m_speed;

	float m_birthday;
	float m_secondsAlive;

	float m_frameTime;
};

