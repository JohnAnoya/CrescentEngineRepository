#include "Engine/Core/CoreEngine.h"
#include "Engine/Core/XMLParser/tinyxml2.h"
#include "GAME/Game1.h"

using namespace tinyxml2;

int main(int argc, char* argv[])
{
	CoreEngine::GetInstance()->SetGameInterface(new Game1, RendererType::OPENGL);
	
	XMLDocument* windowProperties = new XMLDocument();
	windowProperties->LoadFile("Resources/XMLFiles/WindowsProperties.xml");

	std::string EngineName;
	int width = 0;
	int height = 0;

	for (XMLElement* it = windowProperties->FirstChildElement("WindowProperties")->FirstChildElement(); it != NULL; it = it->NextSiblingElement())
	{
		std::string ElementName = it->Name();
		if (ElementName == "EngineName") {
			EngineName = it->GetText();
		}

		else if (ElementName == "Width") {
			width = std::stoi(it->GetText());
		}

		else if (ElementName == "Height") {
			height = std::stoi(it->GetText());
		}
	}
	
	if (!CoreEngine::GetInstance()->OnCreate(EngineName, width, height)) 
	{
		Debugger::Error("Engine failed to be created ", "main.cpp ", __LINE__);
		return 0;
	}

	CoreEngine::GetInstance()->Run();
			
	return 0;
}