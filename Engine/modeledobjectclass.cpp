#include "modeledobjectclass.h"

bool ModeledObjectClass::InitializeModel(ID3D11Device* device, HWND hwnd)
{
	bool result = true;

	m_Model = new ModelClass;

	// Initialize the model object.
	result = m_Model->Initialize(device, m_modelFileName, m_textureFileName);
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

void ModeledObjectClass::ShutdownModel()
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