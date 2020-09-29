#include "MaterialLoader.h"
#include <algorithm>

MaterialLoader::~MaterialLoader() {

}

void MaterialLoader::LoadMaterial(std::string filePath_) {
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debugger::Error("Cannot open MTL File: " + filePath_, "MaterialLoader.cpp", __LINE__);
		return;
	}

	Material m = Material(); 
	std::string matName = "";
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}

		else if (line.find('\t Ns') || line.find('\t d') || line.find('\t Ka') || line.find('\t Kd') || line.find('\t Ks')) {
			line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
			if (line.substr(0, 3) == "Ns ") {
				std::stringstream Ns(line.substr(2));
				float tempShiny;
				Ns >> tempShiny;
				m.shininess = tempShiny;
			}

			else if (line.substr(0, 2) == "d ") {
				std::stringstream d(line.substr(2));
				float tempTransparency;
				d >> tempTransparency;
				m.transparency = tempTransparency;
			}

			else if (line.substr(0, 3) == "Ka ") {
				std::stringstream Ka(line.substr(2));
				float x, y, z;
				Ka >> x >> y >> z;
				m.ambient.x = x;
				m.ambient.y = y;
				m.ambient.z = z;
			}

			else if (line.substr(0, 3) == "Kd ") {
				std::stringstream Kd(line.substr(2));
				float x, y, z;
				Kd >> x >> y >> z;
				m.diffuse.x = x;
				m.diffuse.y = y;
				m.diffuse.z = z;
			}

			else if (line.substr(0, 3) == "Ks ") {
				std::stringstream Ks(line.substr(2));
				float x, y, z;
				Ks >> x >> y >> z;
				m.specular.x = x;
				m.specular.y = y;
				m.specular.z = z;
			}
		}
	}

	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}

	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_) {
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName_, "./Resources/Textures/" + fileName_ + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}

	return currentTexture;
}