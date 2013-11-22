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
	virtual bool RenderModel(ID3D11DeviceContext*, ModelClass**, ModelShaderClass*, LightClass*, D3DXMATRIX*, D3DXMATRIX*) = 0;
};


#endif