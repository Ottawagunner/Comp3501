////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "applicationclass.h"


ApplicationClass::ApplicationClass()
{
	m_Input = 0;
	m_Direct3D = 0;
	m_Camera = 0;
	m_Terrain = 0;
	m_Timer = 0;
	m_Fps = 0;
	m_Cpu = 0;
	m_FontShader = 0;
	m_Text = 0;
	m_TerrainShader = 0;
	m_Light = 0;
	m_TextureShader = 0;
	m_MiniMap = 0;
	m_ParticleShader = 0;
	m_ParticleSystem = 0;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	float cameraX, cameraY, cameraZ;
	D3DXMATRIX baseViewMatrix;
	char videoCard[128];
	int videoMemory;
	int terrainWidth, terrainHeight;

	m_Hwnd = &hwnd;
	
	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, *m_Hwnd, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(*m_Hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if(!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, *m_Hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(*m_Hwnd, L"Could not initialize DirectX 11.", L"Error", MB_OK);
		return false;
	}

	// Initialize collision manager
	m_CollisionManager = new CollisionManagerClass;

	// Initialize all models, maybe move this into a graphics class?
	
	m_PlayerModel = new ModelClass;
	result = m_PlayerModel->Initialize(m_Direct3D->GetDevice(), "../Engine/data/HUMMWV.obj", L"../Engine/data/HUMMWV.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the player model object.", L"Error", MB_OK);
		return false;
	}

	m_PlayerTurretModel = new ModelClass;
	result = m_PlayerTurretModel->Initialize(m_Direct3D->GetDevice(), "../Engine/data/turret.obj", L"../Engine/data/turret.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the player turret model object.", L"Error", MB_OK);
		return false;
	}
	
	m_BulletModel = new ModelClass;
	result = m_BulletModel->Initialize(m_Direct3D->GetDevice(), "../Engine/data/crystal_1.obj", L"../Engine/data/pumpkin.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bullet model object.", L"Error", MB_OK);
		return false;
	}
	
	m_EnemyModel = new ModelClass;
	result = m_EnemyModel->Initialize(m_Direct3D->GetDevice(),"../Engine/data/buggy3.obj", L"../Engine/data/buggy.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the enemy model object.", L"Error", MB_OK);
		return false;
	}
	
	m_ProjectileModel = new ModelClass;
	result = m_ProjectileModel->Initialize(m_Direct3D->GetDevice(),"../Engine/data/HUMMWV.obj", L"../Engine/data/HUMMWV.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the projectile model object.", L"Error", MB_OK);
		return false;
	}

	// Create the model shader object.
	m_ModelShader = new ModelShaderClass;

	// Initialize the terrain shader object.
	result = m_ModelShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model shader object.", L"Error", MB_OK);
		return false;
	}
	
	// Create the player
	m_Player = new PlayerClass(m_PlayerModel, m_ModelShader);
	m_PlayerTurret = new TurretClass(m_PlayerTurretModel, m_ModelShader, m_Player);

	// Create the enemies
	m_Enemies.push_back(new EnemyClass(m_EnemyModel, m_ModelShader, 5.0f, 0.0f, 280.0f));
	
	// Add to array of modeled objects
	m_Models.push_back(m_Player);
	m_Models.push_back(m_PlayerTurret);
	
	for(std::vector<EnemyClass*>::iterator it = m_Enemies.begin(); it != m_Enemies.end(); ++it) {
		m_Models.push_back(*it);
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Set the initial position of the camera.
	cameraX = 50.0f;
	cameraY = 2.0f;
	cameraZ = -7.0f;

	m_Camera->SetPosition(cameraX, cameraY, cameraZ);

	// Create the terrain object.
	m_Terrain = new TerrainClass;
	if(!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(m_Direct3D->GetDevice(), "../Engine/data/heightmap01.bmp", L"../Engine/data/dirt01.dds", "../Engine/data/colorm01.bmp");
	if(!result)
	{
		MessageBox(*m_Hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if(!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if(!result)
	{
		MessageBox(*m_Hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the fps object.
	m_Fps = new FpsClass;
	if(!m_Fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();

	// Create the cpu object.
	m_Cpu = new CpuClass;
	if(!m_Cpu)
	{
		return false;
	}

	// Initialize the cpu object.
	m_Cpu->Initialize();

	// Create the font shader object.
	m_FontShader = new FontShaderClass;
	if(!m_FontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(m_Direct3D->GetDevice(), *m_Hwnd);
	if(!result)
	{
		MessageBox(*m_Hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the text object.
	m_Text = new TextClass;
	if(!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), *m_Hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(*m_Hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Create the particle shader object.
	m_ParticleShader = new ParticleShaderClass;
	if(!m_ParticleShader)
	{
		return false;
	}

	// Initialize the particle shader object.
	result = m_ParticleShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the particle system object.
	m_ParticleSystem = new ParticleSystemClass;
	if(!m_ParticleSystem)
	{
		return false;
	}

	// Initialize the particle system object.
	result = m_ParticleSystem->Initialize(m_Direct3D->GetDevice(), L"../Engine/data/star.dds");
	if(!result)
	{
		return false;
	}

	// Retrieve the video card information.
	m_Direct3D->GetVideoCardInfo(videoCard, videoMemory);

	// Set the video card information in the text object.
	result = m_Text->SetVideoCardInfo(videoCard, videoMemory, m_Direct3D->GetDeviceContext());
	if(!result)
	{
		MessageBox(*m_Hwnd, L"Could not set video card info in the text object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain shader object.
	m_TerrainShader = new TerrainShaderClass;
	if(!m_TerrainShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_TerrainShader->Initialize(m_Direct3D->GetDevice(), *m_Hwnd);
	if(!result)
	{
		MessageBox(*m_Hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.05f, 0.05f, 0.05f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-0.5f, -1.0f, 0.0f);

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_Direct3D->GetDevice(), *m_Hwnd);
	if(!result)
	{
		MessageBox(*m_Hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Get the size of the terrain as the minimap will require this information.
	m_Terrain->GetTerrainSize(terrainWidth, terrainHeight);

	// Create the mini map object.
	m_MiniMap = new MiniMapClass;
	if(!m_MiniMap)
	{
		return false;
	}

	// Initialize the mini map object.
	result = m_MiniMap->Initialize(m_Direct3D->GetDevice(), *m_Hwnd, screenWidth, screenHeight, baseViewMatrix, (float)(terrainWidth - 1), 
								   (float)(terrainHeight - 1));
	if(!result)
	{
		MessageBox(*m_Hwnd, L"Could not initialize the mini map object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void ApplicationClass::Shutdown()
{
	// Release the mini map object.
	if(m_MiniMap)
	{
		m_MiniMap->Shutdown();
		delete m_MiniMap;
		m_MiniMap = 0;
	}

	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the particle system object.
	if(m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	// Release the particle shader object.
	if(m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the player model.
	if(m_PlayerModel)
	{
		m_PlayerModel->Shutdown();
		delete m_PlayerModel;
		m_PlayerModel = 0;
	}

	// Release the player turret model.
	if(m_PlayerTurretModel)
	{
		m_PlayerTurretModel->Shutdown();
		delete m_PlayerTurretModel;
		m_PlayerTurretModel = 0;
	}

	// Release the enemy model
	if(m_EnemyModel)
	{
		m_EnemyModel->Shutdown();
		delete m_EnemyModel;
		m_EnemyModel = 0;
	}

	// Release the projectile model
	if(m_ProjectileModel)
	{
		m_ProjectileModel->Shutdown();
		delete m_ProjectileModel;
		m_ProjectileModel = 0;
	}

	// Release the terrain shader object.
	if(m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	// Release the text object.
	if(m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the font shader object.
	if(m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the cpu object.
	if(m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}

	// Release the fps object.
	if(m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	// Release the timer object.
	if(m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the terrain object.
	if(m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the Direct3D object.
	if(m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool ApplicationClass::Frame()
{
	bool result;


	// Read the user input.
	result = m_Input->Frame();
	if(!result)
	{
		return false;
	}
	
	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Update the system stats.
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();

	// Make the enemies move
	for(std::vector<EnemyClass*>::iterator it = m_Enemies.begin(); it != m_Enemies.end(); ++it) {
		EnemyClass* enemy = (*it);
		if ( enemy->IsAlive() )
		{
			enemy->SetFrameTime(m_Timer->GetTime());
			enemy->Move();
		}
		else
		{
			// Run the frame processing for the particle system.
			float x, y, z;
			enemy->GetPosition(x, y, z);
			m_ParticleSystem->SetPosition(x,y,z);
			m_ParticleSystem->Frame(m_Timer->GetTime(), m_Direct3D->GetDeviceContext());
		}
	}

	// Move the projectiles
	// TODO: Remove projectile from vector if its dead
	for(std::vector<ProjectileClass*>::iterator it = m_Projectiles.begin(); it != m_Projectiles.end();) {
		
		// If dead, remove
		if (! (*it)->IsStillAlive() )
		{
			delete (*it);
			(*it) = 0;
			it = m_Projectiles.erase(it);
		}
		else
		{
			(*it)->MoveForward();
			it++;
		}
	}

	// Check for collisions
	for(std::vector<EnemyClass*>::iterator it = m_Enemies.begin(); it != m_Enemies.end(); ++it) {
		for(std::vector<ProjectileClass*>::iterator itP = m_Projectiles.begin(); itP != m_Projectiles.end();) 
		{
			if (m_CollisionManager->AreColliding((*it), (*itP)))
			{
				(*it)->TakeDamage(1.0f);
				
				// Remove bullet
				delete (*itP);
				(*itP) = 0;
				itP = m_Projectiles.erase(itP);
			}
			else
			{
				itP++;
			}
		}
	}

	// Update the FPS value in the text object.
	result = m_Text->SetFps(m_Fps->GetFps(), m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}
	
	// Update the CPU usage value in the text object.
	result = m_Text->SetCpu(m_Cpu->GetCpuPercentage(), m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleInput(m_Timer->GetTime());
	if(!result)
	{
		return false;
	}

	// Render the graphics.
	result = RenderGraphics();
	if(!result)
	{
		return false;
	}

	return result;
}


bool ApplicationClass::HandleInput(float frameTime)
{
	bool keyDown, result;
	float posX, posY, posZ;
	float turretPosX, turretPosY, turretPosZ;
	float turretRotX, turretRotY, turretRotZ;
	float cameraPosX, cameraPosY, cameraPosZ;
	float cameraRotX, cameraRotY, cameraRotZ;

	// Update the timer we use for staggering input
	struct tm y2k;
	double seconds;

	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 113; y2k.tm_mon = 0; y2k.tm_mday = 1;

	time(&timer);  /* get current time; same as: timer = time(NULL)  */

	seconds = difftime(timer,mktime(&y2k));

	// Set the frame time for calculating the updated position.
	m_Player->SetFrameTime(frameTime);
	m_PlayerTurret->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsAPressed();
	m_Player->TurnLeft(keyDown);

	keyDown = m_Input->IsDPressed();
	m_Player->TurnRight(keyDown);

	keyDown = m_Input->IsWPressed();
	m_Player->ApplyForwardForce(keyDown);

	keyDown = m_Input->IsSPressed();
	m_Player->ApplyBackwardForce(keyDown);

	m_Player->Integrate(frameTime, frameTime*2);

	keyDown = m_Input->IsLeftPressed();
	m_PlayerTurret->TurnLeft(keyDown);

	keyDown = m_Input->IsRightPressed();
	m_PlayerTurret->TurnRight(keyDown);

	keyDown = m_Input->IsQPressed();
	if(keyDown) m_Camera->ToggleView(seconds);
	
	// Get the view point position of player.
	m_Player->GetPosition(posX, posY, posZ);
	
	// Get position/rotation of turret.
	m_PlayerTurret->GetRotation(turretRotX, turretRotY, turretRotZ);
	m_PlayerTurret->GetPosition(turretPosX, turretPosY, turretPosZ);
	
	// Check if the player is shooting
	keyDown = m_Input->IsSpacePressed();
	if (keyDown)
	{
		if (m_Player->CanShoot(seconds))
		{
			m_Projectiles.push_back(new ProjectileClass(m_BulletModel, m_ModelShader, turretPosX, turretPosY, turretPosZ, turretRotX, turretRotY, turretRotZ));
		}
	}

	// Set the position of the camera.
	m_Camera->SetRelativeToReference(posX, posY, posZ, turretRotY);

	m_Camera->GetPosition(cameraPosX, cameraPosY, cameraPosZ);
	m_Camera->GetRotation(cameraRotX, cameraRotY, cameraRotZ);

	// Update the position values in the text object.
	result = m_Text->SetCameraPosition(cameraPosX, cameraPosY, cameraPosZ, m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Update the rotation values in the text object.
	result = m_Text->SetCameraRotation(cameraRotX, cameraRotY, cameraRotZ, m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Update the location of the camera on the mini map.
	m_MiniMap->PositionUpdate(posX, posZ);

	return true;
}


bool ApplicationClass::RenderGraphics()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;


	// Clear the scene.
	m_Direct3D->BeginScene(0.0f, 0.74f, 1.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	// Render the player
	for(std::vector<ModeledObjectClass*>::iterator it = m_Models.begin(); it != m_Models.end(); ++it) {
		(*it)->RenderModel(m_Direct3D->GetDeviceContext(), m_Light, &viewMatrix, &projectionMatrix);
	}
	
	// Render the projectiles
	for(std::vector<ProjectileClass*>::iterator it = m_Projectiles.begin(); it != m_Projectiles.end(); ++it) {
		(*it)->RenderModel(m_Direct3D->GetDeviceContext(), m_Light, &viewMatrix, &projectionMatrix);
	}

	// Render the terrain buffers.
	m_Terrain->Render(m_Direct3D->GetDeviceContext());

	// Render the terrain using the terrain shader.
	result = m_TerrainShader->Render(m_Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
									 m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), m_Terrain->GetTexture());
	if(!result)
	{
		return false;
	}

	// Turn on alpha blending.
	m_Direct3D->TurnOnAlphaBlending();

	// Put the particle system vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ParticleSystem->Render(m_Direct3D->GetDeviceContext());

	// Render the model using the texture shader.
	result = m_ParticleShader->Render(m_Direct3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
					  m_ParticleSystem->GetTexture());
	if(!result)
	{
		return false;
	}
	// Turn off alpha blending.
	m_Direct3D->TurnOffAlphaBlending();

	// Turn off the Z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();
	
	// Render the mini map.
	result = m_MiniMap->Render(m_Direct3D->GetDeviceContext(), worldMatrix, orthoMatrix, m_TextureShader);
	if(!result)
	{
		return false;
	}

	// Turn on the alpha blending before rendering the text.
	m_Direct3D->TurnOnAlphaBlending();

	// Render the text user interface elements.
	result = m_Text->Render(m_Direct3D->GetDeviceContext(), m_FontShader, worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_Direct3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_Direct3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}