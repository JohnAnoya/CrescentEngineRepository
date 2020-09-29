#include "Window.h"


Window::Window()
{
	width = 0;
	height = 0;
	window = nullptr;
	context = nullptr;
}

Window::~Window()
{
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Debugger::FatalError("Failed to initialize SDL ", "Window.cpp ", __LINE__);
		return false;
	}
	width = width_;
	height = height_;

	SetPreAttributes();

	window = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	
	if (!window)
	{
		Debugger::Error("Failed to create window ", "Window.cpp ", __LINE__);
		return false;
	}

	context = SDL_GL_CreateContext(window);

	SetPostAttributes();
	
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		Debugger::FatalError("Failied to initialize glew ", "Window.cpp ", __LINE__);
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, width, height);

	// Converting const char to string by storing in new string 
	const GLubyte* GPUInfo = glGetString(GL_VENDOR);
	std::string SgpuInfo((char*)GPUInfo);
	Debugger::Info(SgpuInfo, " Window.cpp ", __LINE__);

	const GLubyte* openGLVer = glGetString(GL_VERSION);
	std::string SopenGLVer((char*)openGLVer);
	Debugger::Info(SopenGLVer, " Window.cpp ", __LINE__);

	return true;
}

void Window::OnDestroy()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetWidth()
{
	return width;
}

int Window::GetHeight()
{
	return height;
}

SDL_Window* Window::GetWindow() const
{
	return window;
}

void Window::SetPreAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	glewExperimental = GL_TRUE;
}

void Window::SetPostAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}