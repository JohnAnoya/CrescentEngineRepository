#include "Window.h"


Window::Window()
{
	width = 0;
	height = 0;
	window = nullptr;
}

Window::~Window()
{
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_, Renderer* renderer_)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Debugger::FatalError("Failed to initialize SDL ", "Window.cpp ", __LINE__);
		return false;
	}

	width = width_;
	height = height_;

	window = renderer_->CreateWindow(name_, width, height); 

	if (!window) {
		return false;
	}
	
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

