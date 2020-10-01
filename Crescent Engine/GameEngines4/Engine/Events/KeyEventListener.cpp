#include "KeyEventListener.h"
#include "../Core/CoreEngine.h"

CoreEngine* KeyEventListener::engineInstance = nullptr;

KeyEventListener::~KeyEventListener() {
	engineInstance = nullptr;
}

void KeyEventListener::RegisterEngineObject(CoreEngine* engine_) {
	engineInstance = engine_;
	
}

void KeyEventListener::Update(SDL_Event e_) {
	if (e_.key.keysym.scancode == SDL_SCANCODE_W) {
		NotifyOfKeyPressed(e_.key.keysym);
	}

	else if (e_.key.keysym.scancode == SDL_SCANCODE_A) {
		NotifyOfKeyPressed(e_.key.keysym);
	}

	else if (e_.key.keysym.scancode == SDL_SCANCODE_S) {
		NotifyOfKeyPressed(e_.key.keysym);
	}

	else if (e_.key.keysym.scancode == SDL_SCANCODE_D) {
		NotifyOfKeyPressed(e_.key.keysym);
	}

	else if (e_.key.keysym.scancode == SDL_SCANCODE_Q) {
		NotifyOfKeyPressed(e_.key.keysym);
	}

	else if (e_.key.keysym.scancode == SDL_SCANCODE_E) {
		NotifyOfKeyPressed(e_.key.keysym);
	}

	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_W] && keystate[SDL_SCANCODE_D]) {
		engineInstance->DoubleKeyPressedRight();
	}

	else if (keystate[SDL_SCANCODE_W] && keystate[SDL_SCANCODE_A]) {
		engineInstance->DoubleKeyPressedLeft();
	}
}

void KeyEventListener::NotifyOfKeyPressed(SDL_Keysym keyPressed_) {
	if (engineInstance) {
		engineInstance->NotifyOfKeyPressed(keyPressed_); 
	}
}


