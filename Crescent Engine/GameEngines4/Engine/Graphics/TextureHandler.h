#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <memory>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "../Core/Debugger.h"
#include <glew.h>

struct Texture
{
	GLuint textureId = 0;
	float width, height = 0.0f;
	std::string textureName = "";
};

class TextureHandler
{
public:

	static TextureHandler* GetInstance();

	TextureHandler(const TextureHandler&) = delete;
	TextureHandler(TextureHandler&&) = delete;
	TextureHandler& operator=(const TextureHandler&) = delete;
	TextureHandler& operator=(TextureHandler&&) = delete;

	void OnDestroy();

	void CreateTexture(const std::string& textureName_, const std::string& textureFilePath_);

	static const GLuint GetTexture(const std::string& textureName_);

	static const Texture* GetTextureData(const std::string& textureName_);



private:

	TextureHandler();
	~TextureHandler();

	static std::unique_ptr<TextureHandler>textureInstance;
	friend std::default_delete<TextureHandler>;

	static std::vector<Texture*> textures;

};
#endif

