#pragma once

////////////////////////////////////////////////////////////////////////////////
// Filename: modeledobjectclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELEDOBJECTCLASS_H_
#define _MODELEDOBJECTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "modelclass.h"
#include "modelshaderclass.h"
#include "lightclass.h"

class ModeledObjectClass
{
public:
	bool	InitializeModel(ID3D11Device*, HWND hwnd);
	void	ShutdownModel();

	virtual bool	RenderModel(ID3D11DeviceContext*, LightClass*, D3DXMATRIX*, D3DXMATRIX*) = 0;

public:
	ModelClass*			m_Model;
	ModelShaderClass*	m_ModelShader;

	char*				m_modelFileName;
	WCHAR*				m_textureFileName;
};


#endif