#pragma once
#include "mobileentityclass.h"

class VehicleClass :
	public MobileEntityClass
{
public:
	VehicleClass(ModelClass* model, ModelShaderClass* modelShader);
	~VehicleClass(void);

	float TakeDamage(float damageAmount);
	bool CanShoot(float time);

protected:
	float m_health;

	// For staggering shooting
	float m_lastRecordedTime;
};

