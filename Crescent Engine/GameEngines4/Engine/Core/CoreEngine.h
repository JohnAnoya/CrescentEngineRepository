#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>
#include "Window.h"
#include "Timer.h"
#include "GameInterface.h"
#include "Scene.h"
#include "Debugger.h"
#include "../Rendering/3D/GameObject.h"
#include "../Rendering/SceneGraph.h"
#include "../Graphics/ShaderHandler.h"
#include "../Graphics/TextureHandler.h"
#include "../Graphics/AudioHandler.h"
#include "../Camera/Camera.h"
#include "../Events/EventListener.h"
#include "../Rendering/2D/imgui/imgui.h"
#include "../Rendering/2D/imgui/imgui_impl_sdl_gl3.h"
#include "Renderers/OpenGLRenderer.h"
#include "Renderers/VulkanRenderer.h"

using namespace std::string_literals;

class CoreEngine
{
public:
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;
	
	bool OnCreate(std::string name_, int width_, int height_);

	void Run();
	bool GetIsRunning() const;

	void EventHandler();

	static CoreEngine* GetInstance();

	void SetGameInterface(GameInterface* gameInterface_, RendererType rendererType_ = RendererType::OPENGL);

	int GetCurrentScene();
	void SetCurrentScene(int sceneNum_);

	glm::vec2 GetWindowSize() const;
	SDL_Window* GetWindow() const; 
	
	Camera* GetCamera() const;
	void SetCamera(Camera* camera_);

	RendererType GetRendererType();
	Renderer* GetRenderer(); 

	void Exit();

	void NotifyOfMousePressed(glm::vec2 mouse_, int buttonType_);
	void NotifyOfMouseReleased(glm::vec2 mouse_, int buttonType_); 
	void NotifyOfMouseMove(glm::vec2 mouse__);
	void NotifyOfMouseScroll(int y_);

	void NotifyOfKeyPressed(SDL_Keysym keyPressed_);
	void DoubleKeyPressedRight();
	void DoubleKeyPressedLeft();
private:
	CoreEngine();
	~CoreEngine();

	SDL_Event eventWindow;

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();
	void ImGuiDestroy(); 

	Window* window;
	bool isRunning;

	Timer timer;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;

	Camera* camera;

	RendererType rendererType; 
	Renderer* renderer; 
};
#endif

