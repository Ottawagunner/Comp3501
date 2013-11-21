#pragma once

#include "mobileentityclass.h"

class PlayerClass :
	public MobileEntityClass
{
public:
	PlayerClass(void);
	~PlayerClass(void);

	bool	RenderModel(ID3D11DeviceContext*, LightClass*, D3DXMATRIX*, D3DXMATRIX*);
	
	// Player only methods
	void LookUpward(bool);
	void LookDownward(bool);

private:
	float m_lookUpSpeed, m_lookDownSpeed;
};

