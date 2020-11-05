#ifndef RENDERER_H 
#define RENDERER_H 

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <string>

enum class RendererType {
	OPENGL, 
	VULKAN
};

class Renderer{
public: 
	Renderer() {}
	virtual ~Renderer() {}
	virtual SDL_Window* CreateWindow(std::string name_, int width_, int height_) = 0;
	virtual void Render() = 0;
	virtual void OnDestroy() = 0; 
};

#endif