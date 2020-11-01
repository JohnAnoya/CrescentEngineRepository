#include "GameScene.h"
#include "../../Engine/Math/Frustum.h"

GameScene::GameScene() : Scene()
{

}

GameScene::~GameScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}

bool GameScene::OnCreate()
{
	/*
	
	Vertex v;
	std::vector<Vertex> vertexList;

	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	v.colour = glm::vec3(0.0f, 0.5f, 0.0f);
	vertexList.push_back(v);
		
	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	v.colour = glm::vec3(1.0f, 1.0f, 1.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);
	v.colour = glm::vec3(1.0f, 0.0f, 5.0f);

	v.position = glm::vec3(0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.colour = glm::vec3(1.0f, 0.0f, 0.0f);

	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);
	v.colour = glm::vec3(0.5f, 0.0f, 0.0f);

	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.colour = glm::vec3(0.0f, 0.5f, 0.0f);


	Model* model = new Model(ShaderHandler::GetInstance()->GetShader("colourShader"), glm::vec3(0.0f));
	
	model->AddMesh(new Mesh(&vertexList, ShaderHandler::GetInstance()->GetShader("colourShader")));

	shape = new GameObject(model);
	*/
	Debugger::Info("Creating Game Scene ", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera);
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	AudioHandler::GetInstance()->InitializeAudio(CoreEngine::GetInstance()->GetCamera()->GetPosition());

	lightSource = new LightSource(glm::vec3(0.0f), 0.0f, 0.0f, glm::vec3(0.0f));
	lightSource->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	lightSource->SetAmbient(0.1f); 
	lightSource->SetDiffuse(0.5f);
	lightSource->SetLightColour(glm::vec3(1.0f, 1.0f, 1.0f));

	CoreEngine::GetInstance()->GetCamera()->AddLightSource(lightSource);
	CollisionHandler::GetInstance()->OnCreate(100.0f);

	Model* model1 = new Model("./Resources/Models/Apple.obj", "./Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* model2 = new Model("./Resources/Models/Dice.obj", "./Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	
	SceneGraph::GetInstance()->AddModel(model1);
	SceneGraph::GetInstance()->AddModel(model2);

	GameObject* apple = new GameObject(model1, glm::vec3(3.0f, -1.0f, 0.0f));
	apple->SetScale(glm::vec3(0.25f));
	//apple->AddComponent<AIComponent>();
	//apple->AddComponent<ComponentA>();
	//apple->RemoveComponent<ComponentA>();
	apple->AddComponent<AudioSource>("Music1.mp3", false, true, true);
	SceneGraph::GetInstance()->AddGameObject(apple, "apple");

	GameObject* dice = new GameObject(model2, glm::vec3(0.0f, -1.0f, 0.0f));
	dice->SetScale(glm::vec3(0.25f));
	SceneGraph::GetInstance()->AddGameObject(dice, "dice");

	particleEmitter = new ParticleEmitter(15, "diceMap.jpg", "particleShader");

	return true;
}

void GameScene::Update(const float deltaTime_)
{
	//std::cout << deltaTime_ << std::endl;
	AudioHandler::GetInstance()->Update(deltaTime_);
	SceneGraph::GetInstance()->Update(deltaTime_);
	Frustum::GetInstance()->ExtractFrustumResults();
	particleEmitter->Update(deltaTime_);
}

void GameScene::Render()
{
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
	particleEmitter->Render(CoreEngine::GetInstance()->GetCamera());
}
