#pragma once

#include "mobileentityclass.h"

class TurretClass : public MobileEntityClass
{
public:
	TurretClass(ModelClass* model, ModelShaderClass* modelShader, MobileEntityClass* parent);
	~TurretClass(void);

	D3DXMATRIX GetWorldMatrix();

private:
	MobileEntityClass* m_parent;
};

