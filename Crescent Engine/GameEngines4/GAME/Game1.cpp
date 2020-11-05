#include "Game1.h"

Game1::Game1() : GameInterface()
{
	currentSceneNum = 0;
	currentScene = nullptr;
}

Game1::~Game1() 
{
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate()
{
	if (CoreEngine::GetInstance()->GetRendererType() == RendererType::OPENGL) {
		ShaderHandler::GetInstance()->CreateProgram("colourShader",
			"Engine/Shaders/ColourVertexShader.glsl",
			"Engine/Shaders/ColourFragmentShader.glsl");

		ShaderHandler::GetInstance()->CreateProgram("basicShader",
			"Engine/Shaders/VertexShader.glsl",
			"Engine/Shaders/FragementShader.glsl");

		ShaderHandler::GetInstance()->CreateProgram("particleShader", 
			"Engine/Shaders/ParticleVertShader.glsl", 
			"Engine/Shaders/ParticleFragShader.glsl");
	}
	
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0) 
	{
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	}

	Debugger::Error("Engines scene is not initialized to 0", "Game1.cpp", __LINE__);
	return false;
}

void Game1::Update(const float deltaTime_)
{
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene()) 
	{
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void Game1::Render()
{
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	currentScene->Render();
	SDL_GL_SwapWindow(CoreEngine::GetInstance()->GetWindow());
}

void Game1::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;

	switch (CoreEngine::GetInstance()->GetCurrentScene()) 
	{
	case 1:
		currentScene = new GameScene();
		break;
	case 2: 
		currentScene = new TestAIScene(); 
		break; 
	case 3: 
		currentScene = new VulkanTestScene();
		break; 
	default:
		currentScene = new StartScene();
		break;
	}

	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate()) 
	{
		CoreEngine::GetInstance()->Exit();
	}

}

