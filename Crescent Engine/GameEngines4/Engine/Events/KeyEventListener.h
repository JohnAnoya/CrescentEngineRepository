#ifndef KEYEVENTLISTENER_H 
#define KEYEVENTLISTENER_H 

#include <SDL.h>
#include <glm/glm.hpp>

class CoreEngine;
class KeyEventListener
{
public:
	KeyEventListener(const KeyEventListener&) = delete;
	KeyEventListener(KeyEventListener&&) = delete;
	KeyEventListener& operator = (const KeyEventListener&) = delete;
	KeyEventListener& operator = (KeyEventListener&&) = delete;

	KeyEventListener() = delete;
	~KeyEventListener();

	static void RegisterEngineObject(CoreEngine* engine_);
	static void Update(SDL_Event e_);

	static void NotifyOfKeyPressed(SDL_Keysym keyPressed_);
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
private: 
	static CoreEngine* engineInstance;
	 
};
#endif 

