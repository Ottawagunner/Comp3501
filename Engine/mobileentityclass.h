#pragma once

////////////////////////////////////////////////////////////////////////////////
// Filename: mobileentityclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MOBILEENTITYCLASS_H_
#define _MOBILEENTITYCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "modeledobjectclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: MobileEntityClass
////////////////////////////////////////////////////////////////////////////////

class MobileEntityClass : public ModeledObjectClass
{
public:
	MobileEntityClass();

	virtual bool RenderModel(ID3D11DeviceContext*, ModelClass**, ModelShaderClass*,  LightClass*, D3DXMATRIX*, D3DXMATRIX*) = 0;
	
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void GetPosition(float& x, float& y, float& z);
	void GetRotation(float& x, float& y, float& z);

	void SetFrameTime(float time);
	void MoveForward(bool);
	void MoveBackward(bool);
	void MoveUpward(bool);
	void MoveDownward(bool);
	void TurnLeft(bool);
	void TurnRight(bool);

protected:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	float m_frameTime;

	float m_forwardSpeed, m_backwardSpeed;
	float m_upwardSpeed, m_downwardSpeed;
	float m_leftTurnSpeed, m_rightTurnSpeed;

	float m_health;
};

#endif

