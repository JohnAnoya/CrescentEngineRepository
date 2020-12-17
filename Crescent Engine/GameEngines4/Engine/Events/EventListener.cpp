#include "EventListener.h"
#include "../Core/CoreEngine.h"

EventListener::~EventListener() {

}

void EventListener::Update() {
	SDL_Event sdlEvent; 
	while (SDL_PollEvent(&sdlEvent)) {
		if (sdlEvent.type == SDL_QUIT) {
			CoreEngine::GetInstance()->Exit();
		}

		switch (sdlEvent.type) {
			case SDL_MOUSEBUTTONDOWN: 
			case SDL_MOUSEBUTTONUP: 
			case SDL_MOUSEMOTION: 
			case SDL_MOUSEWHEEL: 
				MouseEventListener::Update(sdlEvent);
				break; 

		default:
				break;
		}

		switch (sdlEvent.type) {
			case SDL_KEYDOWN:
				switch (sdlEvent.key.keysym.scancode) {
					case SDL_SCANCODE_W:
					case SDL_SCANCODE_A:
					case SDL_SCANCODE_S:
					case SDL_SCANCODE_D:
					case SDL_SCANCODE_Q:
					case SDL_SCANCODE_E:
					case SDL_SCANCODE_UP:
					case SDL_SCANCODE_DOWN:
						KeyEventListener::Update(sdlEvent);
						break;

					default:
						break;
				}

			default:
					break; 
		}
	}
}