////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"


// This determines camera's position relative to player
const D3DXVECTOR3*	m_thirdPersonReference = new D3DXVECTOR3(0, 25.0f, -40.0f);

CameraClass::CameraClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}

void CameraClass::SetRelativeToReference(float px, float py, float pz, float ry)
{
	D3DXMATRIX rotationMatrixY;
	D3DXVECTOR3 cameraPosition;
	D3DXVECTOR4 transformedReference;

	// Update avatar position
	m_avatarPosition = D3DXVECTOR3(px, py, pz);
	
	// Perform calculations to position camera behind avatar
	D3DXMatrixRotationY(&rotationMatrixY, ry * 0.0174532925f);
	D3DXVec3Transform(&transformedReference, m_thirdPersonReference, &rotationMatrixY);
	cameraPosition = D3DXVECTOR3(transformedReference.x, transformedReference.y, transformedReference.z) + m_avatarPosition;

	m_positionX = cameraPosition.x;
	m_positionY = cameraPosition.y;
	m_positionZ = cameraPosition.z;

	return;
}

void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}


D3DXVECTOR3 CameraClass::GetPosition()
{
	return D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);
}


D3DXVECTOR3 CameraClass::GetRotation()
{
	return D3DXVECTOR3(m_rotationX, m_rotationY, m_rotationZ);
}


void CameraClass::Render()
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw   = m_rotationY * 0.0174532925f;
	roll  = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&m_avatarPosition, &m_avatarPosition, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	D3DXVec3Add(&lookAt, &m_avatarPosition, &D3DXVECTOR3(0.0f, 10.0f, 0.0f));
	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);

	return;
}


void CameraClass::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}