#include "CoreEngine.h"
#include "Debugger.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine()
{
	window = nullptr;
	isRunning = false;
	fps = 144;
	gameInterface = nullptr;
	currentSceneNum = 0; 
	camera = nullptr;
}

CoreEngine::~CoreEngine()
{
	OnDestroy();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_)
{
	Debugger::DebugInit();
	Debugger::SetSeverity(MessageType::TYPE_INFO);

	std::wstring dir = L"C:/Users/RuthlessLua/Desktop/CrescentEngineRepository/Crescent Engine/GameEngines4/Engine/Core/WatchTest";
	FW::WatchID watchID = fileWatcher.addWatch(dir, &listener, true);

	window = new Window();
	if (!window->OnCreate(name_, width_, height_))
	{
		Debugger::FatalError("Window failed to initialize ", "CoreEngine.cpp ", __LINE__);
		isRunning = false;
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth()/2, window->GetHeight()/2);
	MouseEventListener::RegisterEngineObject(this);
	KeyEventListener::RegisterEngineObject(this);

	ShaderHandler::GetInstance()->CreateProgram("colourShader",
		"Engine/Shaders/ColourVertexShader.glsl",
		"Engine/Shaders/ColourFragmentShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("basicShader", 
		"Engine/Shaders/VertexShader.glsl",
		"Engine/Shaders/FragementShader.glsl");

	if (gameInterface) 
	{
		if (!gameInterface->OnCreate()) 
		{
			Debugger::FatalError("GameInterface failed to initialize! ", "CoreEngine.cpp ", __LINE__);
		}
		
	}

	timer.Start();

	Debugger::Info("Engine launched successfully ", "CoreEngine.cpp ", __LINE__);
	
	return isRunning = true;
}

void CoreEngine::Run()
{

	ImGui::CreateContext();
	ImGui_ImplSdlGL3_Init(window->GetWindow());
	ImGui::StyleColorsDark();

	while (isRunning)
	{
		timer.UpdateFrameTick();
		EventListener::Update();
		Update(timer.GetDeltaTime());
		ImGui_ImplSdlGL3_NewFrame(window->GetWindow());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}

	if (!isRunning) 
	{
		OnDestroy();
	}
}

bool CoreEngine::GetIsRunning() const
{
	return isRunning;
}


void CoreEngine::EventHandler()
{
	// checks if there is a pending event 
	while (SDL_PollEvent(&eventWindow) > 0) 
	{
		// if the event is the close button then set isRunning to false
		if (eventWindow.type == SDL_QUIT) 
		{
			isRunning = false;
		}
	}
}


CoreEngine* CoreEngine::GetInstance()
{
	if (engineInstance.get() == nullptr) 
	{
		engineInstance.reset(new CoreEngine());
	}
	return engineInstance.get();
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_)
{
	gameInterface = gameInterface_;
}

int CoreEngine::GetCurrentScene()
{
	return currentSceneNum;
}

void CoreEngine::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}

glm::vec2 CoreEngine::GetWindowSize() const
{
	return glm::vec2(window->GetWidth(), window->GetHeight());
}

Camera* CoreEngine::GetCamera() const
{
	return camera;
}

void CoreEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}

void CoreEngine::NotifyOfMousePressed(glm::vec2 mouse_, int buttonType_) {
	
}

void CoreEngine::NotifyOfMouseReleased(glm::vec2 mouse_, int buttonType_) {
	CollisionHandler::GetInstance()->MouseUpdate(mouse_, buttonType_);
}

void CoreEngine::NotifyOfMouseMove(glm::vec2 mouse__) {
	if (camera && !ImGui::IsMouseDragging()) {
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset());
	}
}

void CoreEngine::NotifyOfMouseScroll(int y_) {
	if (camera && !ImGui::IsMouseDragging()) {
		camera->ProcessMouseZoom(y_);
	}
}

void CoreEngine::NotifyOfKeyPressed(SDL_Keysym keyPressed_) {
 	if (keyPressed_.scancode == SDL_SCANCODE_W) {
		camera->SetPosition(glm::vec3(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z + (-10.0f) * timer.GetDeltaTime()));
	 }

	else if (keyPressed_.scancode == SDL_SCANCODE_A) {
		camera->SetPosition(glm::vec3(camera->GetPosition().x + (-10.0f) * timer.GetDeltaTime(), camera->GetPosition().y, camera->GetPosition().z));
	}

	else if (keyPressed_.scancode == SDL_SCANCODE_S) {
	   camera->SetPosition(glm::vec3(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z + (10.0f) * timer.GetDeltaTime()));
	}

	else if (keyPressed_.scancode == SDL_SCANCODE_D) {
		camera->SetPosition(glm::vec3(camera->GetPosition().x + (10.0f) * timer.GetDeltaTime(), camera->GetPosition().y, camera->GetPosition().z));
	} 

	else if (keyPressed_.scancode == SDL_SCANCODE_Q) {
		camera->SetPosition(glm::vec3(camera->GetPosition().x, camera->GetPosition().y + (10.0f) * timer.GetDeltaTime(), camera->GetPosition().z));
	}

	else if (keyPressed_.scancode == SDL_SCANCODE_E) {
		camera->SetPosition(glm::vec3(camera->GetPosition().x, camera->GetPosition().y + (-10.0f) * timer.GetDeltaTime(), camera->GetPosition().z));
	}
}

void CoreEngine::DoubleKeyPressedRight() {
	camera->SetPosition(glm::vec3(camera->GetPosition().x + (15.0f) * timer.GetDeltaTime(), camera->GetPosition().y, camera->GetPosition().z + (-15.0f) * timer.GetDeltaTime()));
}

void CoreEngine::DoubleKeyPressedLeft() {
	camera->SetPosition(glm::vec3(camera->GetPosition().x + (-15.0f) * timer.GetDeltaTime(), camera->GetPosition().y, camera->GetPosition().z + (-15.0f) * timer.GetDeltaTime()));
}

void CoreEngine::Exit()
{
	isRunning = false;
}

void CoreEngine::Update(const float deltaTime_)
{
	EventHandler();
	if (gameInterface)
	{
		gameInterface->Update(deltaTime_);
	}

	fileWatcher.update();
}

void CoreEngine::Render()
{
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Rend Game
	if (gameInterface) 
	{
		gameInterface->Render();
	}

	ImGui::Begin("Hierachy");
		ImGui::SetWindowSize(ImVec2(100, 500), ImGuiCond_FirstUseEver);
		if (ImGui::Button("Test", ImVec2(350, 20))) {

		}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy()
{
	delete camera;
	camera = nullptr;

	delete gameInterface;
	gameInterface = nullptr;

	delete window;
	window = nullptr;

	ShaderHandler::GetInstance()->OnDestroy(); 
	TextureHandler::GetInstance()->OnDestroy(); 
	MaterialHandler::GetInstance()->OnDestroy(); 
	SceneGraph::GetInstance()->OnDestroy(); 
	CollisionHandler::GetInstance()->OnDestroy();

	ImGui_ImplSdlGL3_Shutdown();
	ImGui::DestroyContext();
	SDL_Quit();
	exit(0);
}