#include "enemyclass.h"


EnemyClass::EnemyClass(void) : MobileEntityClass()
{
}

EnemyClass::EnemyClass(float x, float y, float z) : MobileEntityClass()
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
}


EnemyClass::~EnemyClass(void)
{
}

bool EnemyClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result = true;

	m_Model = new ModelClass;

	// Initialize the model object.
	result = m_Model->Initialize(device, "../Engine/data/buggy.obj", L"../Engine/data/Hummwv.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the model shader object.
	m_ModelShader = new ModelShaderClass;

	// Initialize the terrain shader object.
	result = m_ModelShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model shader object.", L"Error", MB_OK);
		return false;
	}

	return result;
}

bool EnemyClass::Render(ID3D11DeviceContext* deviceContext, LightClass* light, D3DXMATRIX* viewMatrix, D3DXMATRIX* projectionMatrix)
{
	bool result = true;

	D3DXMATRIX worldMatrix, rotationMatrixY, scaleMatrix, translationMatrix;

	//D3DXMatrixScaling(&scaleMatrix, 0.25f, 0.25f, 0.25f);
	//D3DXMatrixRotationY(&rotationMatrixY, (m_rotationY + 180.0f) * 0.0174532925f);
	D3DXMatrixTranslation(&translationMatrix, m_positionX, m_positionY, m_positionZ);

	worldMatrix = /*scaleMatrix * rotationMatrixY * */translationMatrix;

	// Render the model buffers.
	m_Model->Render(deviceContext);

	// Render the model using the model shader.
	result = m_ModelShader->Render(deviceContext, m_Model->GetIndexCount(), worldMatrix, *viewMatrix, *projectionMatrix, 
									 light->GetAmbientColor(), light->GetDiffuseColor(), light->GetDirection(), m_Model->GetTexture());

	return result;
}

void EnemyClass::Shutdown()
{
	if(m_ModelShader)
	{
		m_ModelShader->Shutdown();
		delete m_ModelShader;
		m_ModelShader = 0;
	}

	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}
}

// Simple AI to move the car around
void EnemyClass::Move()
{
	MoveForward(true);
	TurnLeft(true);
}