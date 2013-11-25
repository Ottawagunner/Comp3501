////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>

////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRelativeToReference(float, float, float, float);
	void SetRotation(float, float, float);

	void GetPosition(float &x, float &y, float &z);
	void GetRotation(float &x, float &y, float &z);

	void Render();
	void GetViewMatrix(D3DXMATRIX&);

	void ToggleView(float time);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	float m_turretRotationY;

	D3DXVECTOR3 m_personReference;

	D3DXMATRIX m_viewMatrix;

	D3DXVECTOR3 m_avatarPosition;

	float m_lastRecordedTime;
};

#endif