// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// LevelScreen
//      Main game screen. properties can be customized to change level appearance.


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "LevelScreen.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
LevelScreen::LevelScreen() :
    Screen(),
    m_particles(0),
	m_fireball(0),
	m_flash(0),
	m_player(0),
	m_objective1(0),
	m_objective2(0),
	m_objective3(0),
	m_dialogue(0),
	m_loss(0),
	m_win(0),
    m_crosshair(0)
{
	DebugLog ("LevelScreen: object instantiated.");
}
     

// |----------------------------------------------------------------------------|
// |							  Copy Constructor								|
// |----------------------------------------------------------------------------|
LevelScreen::LevelScreen(const LevelScreen&) {
	DebugLog ("LevelScreen: object copied.");
}


// |----------------------------------------------------------------------------|
// |							   Destructor									|
// |----------------------------------------------------------------------------|
LevelScreen::~LevelScreen() {
	DebugLog ("LevelScreen: object destroyed.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool LevelScreen::Initialize() {

    // Initialize parent class
    Screen::Initialize();

    // Define Variables
    Planet* planet;
    GameObject* gameObject;
    PointLight pLight;
    Graphic* graphic;
    ParticleSystem* particleSystem;
    Text* text;

    // Set next screen to SCREEN_QUIT
	SetNextScreen(SCREEN_QUIT);

    // Set Post-Processing Effects
    m_glow = true;

    // Set lighting
    LightManager::GetRef()->SetAmbient(0.15f,0.15f,0.15f);

    // Set fog
    LightManager::GetRef()->SetFogColor(0.8f,0.6f,0.6f);
    LightManager::GetRef()->SetFogDensity(0.03f);
    
    // Set up camera
    m_camera = new MouseLookCamera;
    m_camera->SetPosition(Coord(0.0f, 15.0f, -10.0f));

    // Set up skybox
    m_skybox->SetTexture("default");
    m_skybox->SetTint(0.8f,0.6f,0.6f);

    // Set up sun
	m_sun = new SkyBox;
    m_sun->SetTint(1.0f,1.0f,0.8f,1.0f);
    m_sun->SetRenderTarget(m_renderTexture);
    m_sun->SetShader("Texture");
    m_sun->SetModel("sphere");
    m_sun->Initialize();
    m_sun->SetPosition(Coord(10.0f,5.0f,10.0f));

    // Sun Light
    float intensity = 0.07;
    LightManager::GetRef()->SetDiffuseColor(m_sun->GetTintR(),m_sun->GetTintG(),m_sun->GetTintB());
    LightManager::GetRef()->SetDiffuseDirection(-1*intensity*m_sun->GetPosition().x,-1*intensity*m_sun->GetPosition().y,-1*intensity*m_sun->GetPosition().z);

    // Set up floor
    gameObject = new GameObject;
    gameObject->Initialize();
    graphic = new Graphic;
    graphic->SetTint(0.8f,0.6f,0.4f,1.0f);
    graphic->SetShader("Light");
    Mesh* mesh = new Mesh;
    mesh->Initialize(300,300,10.0f);
    graphic->SetModel(mesh);
    graphic->Initialize();
    gameObject->SetGraphic(graphic);
    gameObject->SetPosition(Coord(0.0f,-5.0f,0.0f));
    m_gameObjects.push_back(gameObject);
	m_terrain = mesh;
	
    // Set up explosion
    particleSystem = new ParticleSystem;
    particleSystem->Initialize();
    graphic = new Billboard;
    graphic->SetShader("Texture");
    graphic->SetTexture("fireball");
    graphic->SetAlphaBlend(true);
    graphic->SetScale(Coord(0.05f,0.05f,0.05f));
    graphic->Initialize();
    particleSystem->SetGraphic(graphic);
	particleSystem->SetSpawnParticles(false);
    particleSystem->SetParticleVelocity(Coord(0.0f,0.1f,0.0f));
    particleSystem->SetParticleVelocityVariation(Coord(0.05f,0.05f,0.05f));
    particleSystem->SetParticleDeviation(Coord(0.1f,0.1f,0.1f));
    particleSystem->SetParticleLifetime(3.0f);
    particleSystem->SetParticleFadeout(1.0f);
	particleSystem->SetParticleDarken(0.45f);
    particleSystem->SetMaxParticles(10);
    particleSystem->SetTint(1.0f,0.7f,0.4f);
    particleSystem->SetTintVar(0.3f,0.3f,0.3f);
    m_gameObjects.push_back(particleSystem);
	m_fireball = particleSystem;
	// Flash
    particleSystem = new ParticleSystem;
    particleSystem->Initialize();
    graphic = new Billboard;
    graphic->SetShader("Texture");
    graphic->SetTexture("flash");
    graphic->SetAlphaBlend(true);
    graphic->SetScale(Coord(0.05f,0.05f,0.05f));
    graphic->Initialize();
	graphic->SetZBuffer(false);
    particleSystem->SetGraphic(graphic);
	particleSystem->SetSpawnParticles(false);
    particleSystem->SetParticleLifetime(0.4f);
    particleSystem->SetParticleFadeout(0.2f);
    particleSystem->SetMaxParticles(1);
    particleSystem->SetTint(1.0f,1.0f,0.9f);
    m_gameObjects.push_back(particleSystem);
	m_flash = particleSystem;

	// Set up player
	m_player = new Player;
    m_player->Initialize();
    m_gameObjects.push_back(m_player);


    // Set up particle system
    particleSystem = new ParticleSystem;
    particleSystem->Initialize();
    graphic = new Billboard;
    graphic->SetTint(01.0f,0.4f,0.0f,1.0f);
    graphic->SetShader("Texture");
    graphic->SetAlphaBlend(true);
    graphic->SetTexture("particle_point");
    graphic->Initialize();
    graphic->SetRenderTarget(m_renderTexture);
    graphic->SetScale(Coord(0.005f,0.005f,0.005f));
    particleSystem->SetGraphic(graphic);
    particleSystem->SetParticleVelocity(Coord(0.0f,0.0f,0.0f));
    particleSystem->SetParticleVelocityVariation(Coord(1.0f,1.0f,1.0f));
    particleSystem->SetParticleSpawnFrequency(0.01f);
    particleSystem->SetParticleDeviation(Coord(5.0f,5.0f,5.0f));
    particleSystem->SetParticleLifetime(1.0f);
    particleSystem->SetParticleFadeout(0.5f);
    particleSystem->SetMaxParticles(100);
    particleSystem->SetTint(1.0f,0.7f,0.4f);
    particleSystem->SetTintVar(0.3f,0.3f,0.3f);
    m_particles = particleSystem;
    m_gameObjects.push_back(particleSystem);

	// Set up crosshair
    graphic = new Image;
    graphic->SetTexture("crosshair");
    graphic->Initialize();
	graphic->SetScale(Coord(0.1f,0.1f,1.0f));
    graphic->SetRenderToBackBuffer(true);
    gameObject = new GameObject;
    gameObject->Initialize();
    gameObject->SetGraphic(graphic);
	gameObject->SetPosition(Coord(SCREEN_WIDTH/2 - 46.6/2,SCREEN_HEIGHT/2 - 46.6/2,0.0f));
    m_crosshair = gameObject;
    m_overlayObjects.push_back(gameObject);

	// Set up dialoge box
    m_dialogue = new Image;
    m_dialogue->SetTexture("default");
    m_dialogue->Initialize();
	m_dialogue->SetTint(0.3f,0.3f,0.3f,0.5f);
	m_dialogue->SetScale(Coord(400.0f,200.0f,1.0f));
	m_dialogue->SetPosition(Coord(SCREEN_WIDTH / 2.0f - 200.0f,SCREEN_HEIGHT / 2.0f - 100.0f,0.0f));
    m_dialogue->SetRenderToBackBuffer(true);
	
	// Win Dialogue
    m_win = new Text;
    m_win->SetFont("radio_space_regular_20");
    m_win->Initialize();
    m_win->SetRenderToBackBuffer(true);
	m_win->SetText("You win!");
	m_win->SetPosition(Coord(SCREEN_WIDTH / 2.0f - 50.0f,SCREEN_HEIGHT / 2.0f - 25.0f,0.0f));

	// Loss Dialogue
    m_loss = new Text;
    m_loss->SetFont("radio_space_regular_20");
    m_loss->Initialize();
    m_loss->SetRenderToBackBuffer(true);
	m_loss->SetText("You lose!");
	m_loss->SetPosition(Coord(SCREEN_WIDTH / 2.0f - 50.0f,SCREEN_HEIGHT / 2.0f - 25.0f,0.0f));

	// Temporarily Disable Post-Processing
	EnablePostProcessing();

	DebugLog ("LevelScreen: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							    Shutdown									|
// |----------------------------------------------------------------------------|
bool LevelScreen::Shutdown() {

	DebugLog ("LevelScreen: object shutdown.");
	return true;
}


// |----------------------------------------------------------------------------|
// |							     Logic()									|
// |----------------------------------------------------------------------------|
// The logic function, which will be called by the main game loop.
bool LevelScreen::Logic() {
	DebugLog ("LevelScreen: Logic() called.", DB_LOGIC, 10);

    Screen::Logic();

	// If we are in a win/loss dialogue...
	if (m_player->HasCrashed() || (!m_objective1 && !m_objective2 && !m_objective3))
	{
		// Check if the player has clicked, and if so, return to the title screen
		if(InputManager::GetRef()->IsMouseButtonDown(1))
		{
			m_nextScreen = SCREEN_TITLE;
			m_done = true;
		}
		return true;
	}

    // Update dust mote location
    if (m_particles && m_camera)
		m_particles->SetPosition(m_camera->GetPosition());

	// Determine if player has crashed
	if ( m_player->GetPosition().y < m_terrain->GetHeight(m_player->GetPosition().x,m_player->GetPosition().z) )
	{
        m_crosshair->Disable();
		m_player->Crash();
		((MouseLookCamera*)m_camera)->SetActive(false);
		m_fireball->SetPosition(m_player->GetPosition());
		m_flash->SetPosition(m_player->GetPosition());
		m_fireball->EmitAllParticles();
		m_flash->EmitAllParticles();
	}

	// Check for mouse click, fire bullet
	if(InputManager::GetRef()->IsMouseButtonDown(1))
	{
		Bullet* bullet = new Bullet;
		bullet->Initialize();
		bullet->SetPosition(m_player->GetPosition());
		bullet->SetLinearVelocity(m_camera->GetLinearVelocity()*100.0f);
		m_bullets.push_back(bullet);
        if (m_postProcessingEnabled) bullet->EnablePostProcessing(m_renderTexture);
        else bullet->DisablePostProcessing();
		if (m_bullets.size() > 100)
		{
			m_gameObjects.remove( *(m_bullets.begin()) );
			delete *(m_bullets.begin());
			m_bullets.pop_front();
		}
		m_gameObjects.push_back(bullet);
	}

	// Check if bullets are colliding with objectives
    std::list<Bullet*>::iterator it;
    for (it=m_bullets.begin(); it!=m_bullets.end(); ++it)
    {
		if (m_objective1)
		{
			Coord direction = m_objective1->GetPosition() - (*it)->GetPosition();
			float distance = direction.Magnitude();
			if ((*it)->GetGraphic()->GetScale().x + m_objective1->GetGraphic()->GetScale().x > distance )
			{
				// blow up objective
				m_fireball->SetPosition(m_objective1->GetPosition());
				m_flash->SetPosition(m_objective1->GetPosition());
				m_fireball->EmitAllParticles();
				m_flash->EmitAllParticles();
			
				m_gameObjects.remove( m_objective1 );
				delete m_objective1;
				m_objective1 = 0;
			}
		}
		if (m_objective2)
		{
			Coord direction = m_objective2->GetPosition() - (*it)->GetPosition();
			float distance = direction.Magnitude();
			if ((*it)->GetGraphic()->GetScale().x + m_objective2->GetGraphic()->GetScale().x > distance )
			{
				// blow up objective
				m_fireball->SetPosition(m_objective2->GetPosition());
				m_flash->SetPosition(m_objective2->GetPosition());
				m_fireball->EmitAllParticles();
				m_flash->EmitAllParticles();
			
				m_gameObjects.remove( m_objective2 );
				delete m_objective2;
				m_objective2 = 0;
			}
		}
		if (m_objective3)
		{
			Coord direction = m_objective3->GetPosition() - (*it)->GetPosition();
			float distance = direction.Magnitude();
			if ((*it)->GetGraphic()->GetScale().x + m_objective3->GetGraphic()->GetScale().x > distance )
			{
				// blow up objective
				m_fireball->SetPosition(m_objective3->GetPosition());
				m_flash->SetPosition(m_objective3->GetPosition());
				m_fireball->EmitAllParticles();
				m_flash->EmitAllParticles();
			
				m_gameObjects.remove( m_objective3 );
				delete m_objective3;
				m_objective3 = 0;
			}
		}

		
	}

	// Check if there are any objectives left
	if (!m_objective1 && !m_objective2 && !m_objective3)
    {
        m_crosshair->Disable();
		((MouseLookCamera*)m_camera)->SetActive(false);
    }

	return true;
}

// |----------------------------------------------------------------------------|
// |							     Draw()										|
// |----------------------------------------------------------------------------|
// The draw function, which will be called by the main game loop.
bool LevelScreen::Draw() {
	DebugLog ("LevelScreen: Draw() called.", DB_GRAPHICS, 10);

    Screen::Draw();

	// Win/Loss Dialogue
	if (m_player->HasCrashed())
	{
		m_dialogue->Render();
		m_loss->Render();
	}
	else if(!m_objective1 && !m_objective2 && !m_objective3)
	{
		m_dialogue->Render();
		m_win->Render();
	}


	return true;
}

// |----------------------------------------------------------------------------|
// |							    OnLoad()									|
// |----------------------------------------------------------------------------|
// Called when the screen is loaded.
bool LevelScreen::OnLoad() {
	DebugLog("LevelScreen: OnLoad called");

	m_done = false;

    m_crosshair->Enable();

	m_player->Reset();
	((MouseLookCamera*)m_camera)->SetActive(true);
    m_camera->SetPosition(Coord(0.0f, 20.0f, -10.0f));
	m_camera->SetOrientation(Coord(0.0f,0.0f,0.0f));

	
	// Set up Objectives
	// Objective 1
	m_objective1 = new Planet;
	m_objective1->Initialize();
	Graphic* graphic = new Graphic;
    graphic->SetTint(1.0f,0.0f,0.0f,1.0f);
    graphic->SetShader("Light");
	graphic->SetTexture("default");
    graphic->SetModel("sphere");
	graphic->SetReflectiveness(0.9f);
    graphic->SetScale(Coord(1.0f,1.0f,1.0f));
    graphic->Initialize();
	m_objective1->SetGraphic(graphic);
	m_objective1->SetOrbitCenter(Coord(0.0f,15.0f,200.0f));
	m_objective1->SetOrbitRadius(2.0f);
	m_objective1->SetOrbitSpeed(2.0f);
	m_gameObjects.push_back(m_objective1);
    if (m_postProcessingEnabled) m_objective1->EnablePostProcessing(m_renderTexture);
    else m_objective1->DisablePostProcessing();

	// Objective 2
	m_objective2 = new Planet;
	m_objective2->Initialize();
	graphic = new Graphic;
    graphic->SetTint(0.0f,0.0f,1.0f,1.0f);
    graphic->SetShader("Light");
	graphic->SetTexture("default");
    graphic->SetModel("sphere");
	graphic->SetReflectiveness(0.9f);
    graphic->SetScale(Coord(3.0f,3.0f,3.0f));
    graphic->Initialize();
	m_objective2->SetGraphic(graphic);
	m_objective2->SetOrbitCenter(Coord(-100.0f,10.0f,150.0f));
	m_objective2->SetOrbitRadius(50.0f);
	m_objective2->SetOrbitSpeed(2.0f);
	m_gameObjects.push_back(m_objective2);
    if (m_postProcessingEnabled) m_objective2->EnablePostProcessing(m_renderTexture);
    else m_objective2->DisablePostProcessing();

	// Objective 3
	m_objective3 = new Planet;
	m_objective3->Initialize();
	graphic = new Graphic;
    graphic->SetTint(0.0f,1.0f,0.0f,1.0f);
    graphic->SetShader("Light");
	graphic->SetTexture("default");
    graphic->SetModel("sphere");
	graphic->SetReflectiveness(0.9f);
    graphic->SetScale(Coord(3.0f,3.0f,3.0f));
    graphic->Initialize();
	m_objective3->SetGraphic(graphic);
	m_objective3->SetOrbitCenter(Coord(100.0f,20.0f,100.0f));
	m_objective3->SetOrbitRadius(25.0f);
	m_objective3->SetOrbitSpeed(0.5f);
	m_gameObjects.push_back(m_objective3);
    if (m_postProcessingEnabled) m_objective3->EnablePostProcessing(m_renderTexture);
    else m_objective3->DisablePostProcessing();

	return true;
}

// |----------------------------------------------------------------------------|
// |							    OnExit()									|
// |----------------------------------------------------------------------------|
// Called when switching to a different screen
bool LevelScreen::OnExit() {

	DebugLog ("LevelScreen: OnExit called.");
	
	if (m_objective1)
	{
		m_gameObjects.remove( m_objective1 );
		delete m_objective1;
		m_objective1 = 0;
	}
	if (m_objective2)
	{
		m_gameObjects.remove( m_objective2 );
		delete m_objective2;
		m_objective2 = 0;
	}
	if (m_objective3)
	{
		m_gameObjects.remove( m_objective3 );
		delete m_objective3;
		m_objective3 = 0;
		return true;
	}
}