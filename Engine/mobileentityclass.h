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
	MobileEntityClass() 
	{
		m_positionX = 0.0f;
		m_positionY = 0.0f;
		m_positionZ = 0.0f;
	
		m_rotationX = 0.0f;
		m_rotationY = 0.0f;
		m_rotationZ = 0.0f;

		m_frameTime = 0.0f;

		m_forwardSpeed   = 0.0f;
		m_backwardSpeed  = 0.0f;
		m_upwardSpeed    = 0.0f;
		m_downwardSpeed  = 0.0f;
		m_leftTurnSpeed  = 0.0f;
		m_rightTurnSpeed = 0.0f;

		m_health = 0.0f;
	}

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

	void MoveForward(bool keydown)
	{
		float radians;


		// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
		if(keydown)
		{
			m_forwardSpeed += m_frameTime * 0.001f;

			if(m_forwardSpeed > (m_frameTime * 0.03f))
			{
				m_forwardSpeed = m_frameTime * 0.03f;
			}
		}
		else
		{
			m_forwardSpeed -= m_frameTime * 0.0007f;

			if(m_forwardSpeed < 0.0f)
			{
				m_forwardSpeed = 0.0f;
			}
		}

		// Convert degrees to radians.
		radians = m_rotationY * 0.0174532925f;

		// Update the position.
		m_positionX += sinf(radians) * m_forwardSpeed;
		m_positionZ += cosf(radians) * m_forwardSpeed;

		return;
	}

	void MoveBackward(bool keydown)
	{
		float radians;


		// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
		if(keydown)
		{
			m_backwardSpeed += m_frameTime * 0.001f;

			if(m_backwardSpeed > (m_frameTime * 0.03f))
			{
				m_backwardSpeed = m_frameTime * 0.03f;
			}
		}
		else
		{
			m_backwardSpeed -= m_frameTime * 0.0007f;
		
			if(m_backwardSpeed < 0.0f)
			{
				m_backwardSpeed = 0.0f;
			}
		}

		// Convert degrees to radians.
		radians = m_rotationY * 0.0174532925f;

		// Update the position.
		m_positionX -= sinf(radians) * m_backwardSpeed;
		m_positionZ -= cosf(radians) * m_backwardSpeed;

		return;
	}

	void MoveUpward(bool keydown)
	{
		// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
		if(keydown)
		{
			m_upwardSpeed += m_frameTime * 0.003f;

			if(m_upwardSpeed > (m_frameTime * 0.03f))
			{
				m_upwardSpeed = m_frameTime * 0.03f;
			}
		}
		else
		{
			m_upwardSpeed -= m_frameTime * 0.002f;

			if(m_upwardSpeed < 0.0f)
			{
				m_upwardSpeed = 0.0f;
			}
		}

		// Update the height position.
		m_positionY += m_upwardSpeed;

		return;
	}

	void MoveDownward(bool keydown)
	{
		// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
		if(keydown)
		{
			m_downwardSpeed += m_frameTime * 0.003f;

			if(m_downwardSpeed > (m_frameTime * 0.03f))
			{
				m_downwardSpeed = m_frameTime * 0.03f;
			}
		}
		else
		{
			m_downwardSpeed -= m_frameTime * 0.002f;

			if(m_downwardSpeed < 0.0f)
			{
				m_downwardSpeed = 0.0f;
			}
		}

		// Update the height position.
		m_positionY -= m_downwardSpeed;

		return;
	}

	void TurnLeft(bool keydown)
	{
		// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
		if(keydown)
		{
			m_leftTurnSpeed += m_frameTime * 0.01f;

			if(m_leftTurnSpeed > (m_frameTime * 0.15f))
			{
				m_leftTurnSpeed = m_frameTime * 0.15f;
			}
		}
		else
		{
			m_leftTurnSpeed -= m_frameTime* 0.005f;

			if(m_leftTurnSpeed < 0.0f)
			{
				m_leftTurnSpeed = 0.0f;
			}
		}

		// Update the rotation.
		m_rotationY -= m_leftTurnSpeed;

		// Keep the rotation in the 0 to 360 range.
		if(m_rotationY < 0.0f)
		{
			m_rotationY += 360.0f;
		}

		return;
	}

	void TurnRight(bool keydown)
	{
		// Update the right turn speed movement based on the frame time and whether the user is holding the key down or not.
		if(keydown)
		{
			m_rightTurnSpeed += m_frameTime * 0.01f;

			if(m_rightTurnSpeed > (m_frameTime * 0.15f))
			{
				m_rightTurnSpeed = m_frameTime * 0.15f;
			}
		}
		else
		{
			m_rightTurnSpeed -= m_frameTime* 0.005f;

			if(m_rightTurnSpeed < 0.0f)
			{
				m_rightTurnSpeed = 0.0f;
			}
		}

		// Update the rotation.
		m_rotationY += m_rightTurnSpeed;

		// Keep the rotation in the 0 to 360 range.
		if(m_rotationY > 360.0f)
		{
			m_rotationY -= 360.0f;
		}

		return;
	}

protected:
	ModelClass*			m_Model;
	ModelShaderClass*	m_ModelShader;

	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	float m_frameTime;

	float m_forwardSpeed, m_backwardSpeed;
	float m_upwardSpeed, m_downwardSpeed;
	float m_leftTurnSpeed, m_rightTurnSpeed;

	float m_health;
};

#endif

