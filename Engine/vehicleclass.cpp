#include "vehicleclass.h"


VehicleClass::VehicleClass(ModelClass* model, ModelShaderClass* modelShader) : MobileEntityClass(model, modelShader)
{
}


VehicleClass::~VehicleClass(void)
{
}

bool VehicleClass::IsAlive()
{
	return m_health > 0.0f;
}

float VehicleClass::TakeDamage(float damageAmount)
{
	m_health -= damageAmount;

	return m_health;
}

bool VehicleClass::CanShoot(float time)
{
	if (time - m_lastRecordedTime > 0.5f)
	{
		m_lastRecordedTime = time;
		return true;
	}
	return false;;
}