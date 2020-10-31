#ifndef OPENGLRENDERER_H 
#define OPENGLRENDERER_H 

#include "../Debugger.h"
#include "Renderer.h"
class OpenGLRenderer : public Renderer{
public: 
	OpenGLRenderer();
	virtual ~OpenGLRenderer();
	SDL_Window* CreateWindow(std::string name_, int width_, int height_) override;
	void OnDestroy() override; 
private: 
	void SetPreAttributes();
	void SetPostAttributes();

	SDL_GLContext context;
};
#endif 

