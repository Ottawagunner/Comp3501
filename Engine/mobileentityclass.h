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

struct State {
	D3DXVECTOR3 x; // position
	D3DXVECTOR3 v; // velocity
	float m; // mass
};
	
struct Derivative {
	D3DXVECTOR3 dx; // derivative of position; velocity
	D3DXVECTOR3 dv; // derivative of velocity; acceleration
	float dm; // derivative of mass; momentum?
};

class MobileEntityClass : public ModeledObjectClass
{
public:
	MobileEntityClass(ModelClass* model, ModelShaderClass* modelShader);
	
	void Integrate(float t, float dt);

	void GetPosition(float& x, float& y, float& z);
	void GetRotation(float& x, float& y, float& z);

	void SetFrameTime(float time);

	// Physics
	void ApplyForwardForce(bool);
	void ApplyBackwardForce(bool);
	
	void TurnLeft(bool);
	void TurnRight(bool);

	float GetWidth();
	float GetHeight();
	void SetGrid(int, int, float); 

protected:
	State m_state;

	Derivative Evaluate(float t);
	Derivative Evaluate(float t, float dt, const Derivative &d); 
	D3DXVECTOR3 Acceleration(float t);
	D3DXVECTOR3 GetNetForce();

	float m_rotationX, m_rotationY, m_rotationZ;

	float m_frameTime;

	D3DXVECTOR3 m_forwardForce, m_backwardForce;
	float m_leftTurnSpeed, m_rightTurnSpeed;

	float m_width;
	float m_height;
	float m_maxSpeed;

	float grid[2000][2000]; 

	float GetMagnitude(D3DXVECTOR3 vec);
};

#endif

