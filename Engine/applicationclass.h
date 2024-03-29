////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include <vector>
#include <time.h>

#include "inputclass.h"
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "terrainclass.h"
#include "timerclass.h"
#include "fpsclass.h"
#include "cpuclass.h"
#include "fontshaderclass.h"
#include "textclass.h"
#include "terrainshaderclass.h"
#include "lightclass.h"
#include "textureshaderclass.h"
#include "minimapclass.h"
#include "modelshaderclass.h"
#include "playerclass.h"
#include "enemyclass.h"
#include "projectileclass.h"
#include "turretclass.h"
#include "collisionmanagerclass.h"
#include "particleshaderclass.h"
#include "particlesystemclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ApplicationClass
////////////////////////////////////////////////////////////////////////////////
class ApplicationClass
{
public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass&);
	~ApplicationClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:
	bool HandleInput(float);
	bool RenderGraphics();

private:
	time_t timer;

	HWND* m_Hwnd;
	InputClass* m_Input;
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	TerrainClass* m_Terrain;
	TimerClass* m_Timer;
	FpsClass* m_Fps;
	CpuClass* m_Cpu;
	CollisionManagerClass* m_CollisionManager;
	FontShaderClass* m_FontShader;
	TextClass* m_Text;
	TerrainShaderClass* m_TerrainShader;
	LightClass* m_Light;
	TextureShaderClass* m_TextureShader;
	MiniMapClass* m_MiniMap;
	PlayerClass* m_Player;
	TurretClass* m_PlayerTurret;
	ModelShaderClass* m_ModelShader;
	ModelClass* m_PlayerModel;
	ModelClass* m_PlayerTurretModel;
	ModelClass* m_EnemyModel;
	ModelClass* m_ProjectileModel;
	ModelClass* m_BulletModel;
	std::vector<EnemyClass*> m_Enemies;
	std::vector<ProjectileClass*> m_Projectiles;

	std::vector<ModeledObjectClass*> m_Models;

	ParticleShaderClass* m_ParticleShader;
	ParticleSystemClass* m_ParticleSystem;

};

#endif