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

	
	for (XMLElement* it = windowProperties->FirstChildElement("WindowProperties"); it != NULL; it = it->NextSiblingElement())
	{
		std::cout << it->GetText() << std::endl; 
		//std::cout << "Engine Name: " << EngineName << std::endl;
	}
	

	if (!CoreEngine::GetInstance()->OnCreate("Engine Window", 1600, 900)) 
	{
		Debugger::Error("Engine failed to be created ", "main.cpp ", __LINE__);
		return 0;
	}

	CoreEngine::GetInstance()->Run();
			
	return 0;
}