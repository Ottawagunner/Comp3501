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
	ModeledObjectClass(ModelClass* model, ModelShaderClass* modelShader);

	bool RenderModel(ID3D11DeviceContext*, LightClass*, D3DXMATRIX*, D3DXMATRIX*);

	virtual D3DXMATRIX GetWorldMatrix() = 0;

private:
	ModelClass* m_model;
	ModelShaderClass* m_modelShader;
};


#endif