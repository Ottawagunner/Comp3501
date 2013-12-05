#include "turretclass.h"


TurretClass::TurretClass(ModelClass* model, ModelShaderClass* modelShader, MobileEntityClass* parent) : MobileEntityClass(model, modelShader)
{
	m_width = 5.0f;
	m_height = 5.0f;

	m_parent = parent;
}


TurretClass::~TurretClass(void)
{
}

D3DXMATRIX TurretClass::GetWorldMatrix()
{
	D3DXMATRIX initialModelFixRotation, rotationMatrixY, scaleMatrix, worldMatrix, parentTranslationMatrix;
	float parentX, parentY, parentZ;

	m_parent->GetPosition(parentX, parentY, parentZ);
	
	// Set own position to that of parent, not the best spot to do this...
	m_state.x.x = parentX;
	m_state.x.y = parentY + 7.0f;
	m_state.x.z = parentZ;

	D3DXMatrixRotationY(&initialModelFixRotation, D3DX_PI/2);
	D3DXMatrixScaling(&scaleMatrix, 0.25f, 0.25f, 0.25f);
	D3DXMatrixRotationY(&rotationMatrixY, m_rotationY * 0.0174532925f);

	D3DXMatrixTranslation(&parentTranslationMatrix, m_state.x.x, m_state.x.y, m_state.x.z);

	worldMatrix = scaleMatrix * initialModelFixRotation * rotationMatrixY * parentTranslationMatrix;

	return worldMatrix;
}