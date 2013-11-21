#pragma once
#include "mobileentityclass.h"
class EnemyClass :
	public MobileEntityClass
{
public:
	EnemyClass(void);
	EnemyClass(float x, float y, float z);
	~EnemyClass(void);

	bool	Initialize(ID3D11Device*, HWND hwnd);
	bool	Render(ID3D11DeviceContext*, LightClass*, D3DXMATRIX*, D3DXMATRIX*);
	void	Shutdown();

	void Move();
};

