#include "mobileentityclass.h"

MobileEntityClass::MobileEntityClass(ModelClass* model, ModelShaderClass* modelShader) : ModeledObjectClass(model, modelShader)
{
	m_state.x.x = 0.0f;
	m_state.x.y = 0.0f;
	m_state.x.z = 0.0f;

	m_state.v.x = 0.0f;
	m_state.v.y = 0.0f;
	m_state.v.z = 0.0f;

	m_state.m = 10.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_frameTime = 0.0f;

	m_leftTurnSpeed  = 0.0f;
	m_rightTurnSpeed = 0.0f;

	m_maxSpeed = 0.05f;
}

float MobileEntityClass::GetHeight()
{
	return m_height;
}

float MobileEntityClass::GetWidth()
{
	return m_width;
}

void MobileEntityClass::GetPosition(float& x, float& y, float& z)	
{
	x = m_state.x.x;
	y = m_state.x.y;
	z = m_state.x.z;

	return;
};

void MobileEntityClass::GetRotation(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;
	return;
};

void MobileEntityClass::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
};

void MobileEntityClass::ApplyForwardForce(bool keydown)
{
	if(keydown)
	{
		float force = 0.0001;
		float radians = m_rotationY * 0.0174532925f;		
		float forceX = sinf(radians) * force;
		float forceZ = cosf(radians) * force;
		
		m_forwardForce = D3DXVECTOR3(forceX, 0.0f, forceZ);
	}
	else
	{
		m_forwardForce = D3DXVECTOR3(0,0,0);	
	}
	return;
}

void MobileEntityClass::ApplyBackwardForce(bool keydown)
{
	if(keydown)
	{
		float force = -0.0001;
		float radians = m_rotationY * 0.0174532925f;		
		float forceX = sinf(radians) * force;
		float forceZ = cosf(radians) * force;
		
		m_backwardForce = D3DXVECTOR3(forceX, 0.0f, forceZ);
	}
	else
	{
		m_backwardForce = D3DXVECTOR3(0,0,0);	
	}
	return;
}

void MobileEntityClass::TurnLeft(bool keydown)
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

void MobileEntityClass::TurnRight(bool keydown)
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
	
Derivative MobileEntityClass::Evaluate(float t)
{
	Derivative output;
	output.dx = m_state.v;
	output.dv = Acceleration(t);
	return output;
}

Derivative MobileEntityClass::Evaluate(float t, float dt, const Derivative &d)
{
        State state;
        state.x = m_state.x + d.dx*dt;
        state.v = m_state.v + d.dv*dt;

        Derivative output;
        output.dx = state.v;
        output.dv = Acceleration(t+dt);
        return output;
}

D3DXVECTOR3 MobileEntityClass::Acceleration(float t)
{
	return GetNetForce()/m_state.m;
}

void MobileEntityClass::Integrate(float t, float dt)
{
        Derivative a = Evaluate(t);
  /*      Derivative b = Evaluate(t, dt*0.5f, a);
        Derivative c = Evaluate(t, dt*0.5f, b);
        Derivative d = Evaluate(t, dt, c);

		const D3DXVECTOR3 dxdt = 1.0f/6.0f * (a.dx + 2.0f*(b.dx + c.dx) + d.dx);
        const D3DXVECTOR3 dvdt = 1.0f/6.0f * (a.dv + 2.0f*(b.dv + c.dv) + d.dv);

        m_state.x = m_state.x + dxdt * dt;
        m_state.v = m_state.v + dvdt * dt;
*/
		m_state.x = m_state.x + a.dx * dt;

		// Put a cap on the velocity
		if (GetMagnitude(m_state.v + a.dv * dt) < m_maxSpeed) 
			m_state.v = m_state.v + a.dv * dt;
}

D3DXVECTOR3 MobileEntityClass::GetNetForce()
{
	return m_forwardForce + m_backwardForce;
}

float MobileEntityClass::GetMagnitude(D3DXVECTOR3 vec)
{
	float mag = sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
	return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}