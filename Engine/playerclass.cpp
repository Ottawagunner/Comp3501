#include "playerclass.h"


PlayerClass::PlayerClass(void)
{
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


PlayerClass::~PlayerClass(void)
{
}

bool PlayerClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result = true;

	m_Model = new ModelClass;

	// Initialize the model object.
	result = m_Model->Initialize(device, "../Engine/data/HUMMWV.obj", L"../Engine/data/Hummwv.dds");
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

bool PlayerClass::Render(ID3D11DeviceContext* deviceContext, LightClass* light, D3DXMATRIX* viewMatrix, D3DXMATRIX* projectionMatrix)
{
	bool result = true;
	D3DXMATRIX *worldMatrix = new D3DXMATRIX();
	D3DXMatrixIdentity(worldMatrix);

	// Render the model buffers.
	m_Model->Render(deviceContext);

	// Render the model using the model shader.
	result = m_ModelShader->Render(deviceContext, m_Model->GetIndexCount(), *worldMatrix, *viewMatrix, *projectionMatrix, 
									 light->GetAmbientColor(), light->GetDiffuseColor(), light->GetDirection(), m_Model->GetTexture());

	return result;
}

void PlayerClass::Shutdown()
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