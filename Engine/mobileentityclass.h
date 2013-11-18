#pragma once

////////////////////////////////////////////////////////////////////////////////
// Filename: mobileentityclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MOBILENTITYCLASS_H_
#define _MOBILENTITYCLASS_H_


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


////////////////////////////////////////////////////////////////////////////////
// Class name: MobileEntityClass
////////////////////////////////////////////////////////////////////////////////

class MobileEntityClass
{
public:
	virtual bool Initialize(ID3D11Device*, HWND) = 0;
	virtual bool Render(ID3D11DeviceContext*, LightClass*, D3DXMATRIX*, D3DXMATRIX*) = 0;
	virtual void Shutdown() = 0;

	D3DXVECTOR3 GetPosition() { return m_position; };

protected:
	ModelClass*			m_Model;
	ModelShaderClass*	m_ModelShader;

	D3DXVECTOR3 m_position;
};

#endif

