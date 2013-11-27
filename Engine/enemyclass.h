#pragma once
#include "vehicleclass.h"
class EnemyClass :
	public VehicleClass
{
public:
	EnemyClass(ModelClass* model, ModelShaderClass* modelShader, float x, float y, float z);
	~EnemyClass(void);

	D3DXMATRIX GetWorldMatrix();

	void Move();
};

