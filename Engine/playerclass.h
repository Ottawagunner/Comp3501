#pragma once

#include "vehicleclass.h"

class PlayerClass :
	public VehicleClass
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

