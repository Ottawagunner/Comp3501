#pragma once
#include "mobileentityclass.h"
class EnemyClass :
	public MobileEntityClass
{
public:
	EnemyClass(void);
	EnemyClass(float x, float y, float z);
	~EnemyClass(void);

	bool	RenderModel(ID3D11DeviceContext*, ModelClass*, ModelShaderClass*, LightClass*, D3DXMATRIX*, D3DXMATRIX*);

	void Move();
};

