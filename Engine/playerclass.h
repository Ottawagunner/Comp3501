#pragma once

#include "mobileentityclass.h"

class PlayerClass :
	public MobileEntityClass
{
public:
	PlayerClass(void);
	~PlayerClass(void);

	bool	Initialize(ID3D11Device*, HWND hwnd);
	bool	Render(ID3D11DeviceContext*, LightClass*, D3DXMATRIX*, D3DXMATRIX*);
	void	Shutdown();

	void MoveForward(bool);
	void MoveBackward(bool);
	void MoveUpward(bool);
	void MoveDownward(bool);
	void TurnLeft(bool);
	void TurnRight(bool);
	void LookUpward(bool);
	void LookDownward(bool);
};

