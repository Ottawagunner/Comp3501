#pragma once

#include "mobileentityclass.h"

class PlayerClass :
	public MobileEntityClass
{
public:
	PlayerClass(ModelClass* model, ModelShaderClass* modelShader);
	~PlayerClass(void);

	// Player only methods
	void LookUpward(bool);
	void LookDownward(bool);

	D3DXMATRIX GetWorldMatrix();

private:
	float m_lookUpSpeed, m_lookDownSpeed;
};

