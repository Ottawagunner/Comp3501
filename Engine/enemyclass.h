#pragma once
#include "mobileentityclass.h"
class EnemyClass :
	public MobileEntityClass
{
public:
	EnemyClass(ModelClass* model, ModelShaderClass* modelShader, float x, float y, float z);
	~EnemyClass(void);

	D3DXMATRIX GetWorldMatrix();

	void Move();
};

