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

	void SetPosition(float x, float y, float z)
	{
		m_positionX = x;
		m_positionY = y;
		m_positionZ = z;
		return;
	};

	void SetRotation(float x, float y, float z)
	{
		m_rotationX = x;
		m_rotationY = y;
		m_rotationZ = z;
		return;
	};

	void GetPosition(float& x, float& y, float& z)	
	{
		x = m_positionX;
		y = m_positionY;
		z = m_positionZ;
		return;
	};

	void GetRotation(float& x, float& y, float& z)
	{
		x = m_rotationX;
		y = m_rotationY;
		z = m_rotationZ;
		return;
	};

	void SetFrameTime(float time)
	{
		m_frameTime = time;
		return;
	};

	virtual void MoveForward(bool) = 0;
	virtual void MoveBackward(bool) = 0;
	virtual void MoveUpward(bool) = 0;
	virtual void MoveDownward(bool) = 0;
	virtual void TurnLeft(bool) = 0;
	virtual void TurnRight(bool) = 0;

protected:
	ModelClass*			m_Model;
	ModelShaderClass*	m_ModelShader;

	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	float m_frameTime;

	float m_forwardSpeed, m_backwardSpeed;
	float m_upwardSpeed, m_downwardSpeed;
	float m_leftTurnSpeed, m_rightTurnSpeed;
	float m_lookUpSpeed, m_lookDownSpeed;
};

#endif

