#include "TestAIScene.h"
#include "../../Engine/Math/Frustum.h"

TestAIScene::TestAIScene() : Scene()
{

}

TestAIScene::~TestAIScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}

bool TestAIScene::OnCreate()
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

	lightSource = new LightSource(glm::vec3(0.0f), 0.0f, 0.0f, glm::vec3(0.0f));
	lightSource->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	lightSource->SetAmbient(0.1f);
	lightSource->SetDiffuse(0.5f);
	lightSource->SetLightColour(glm::vec3(1.0f, 1.0f, 1.0f));

	CoreEngine::GetInstance()->GetCamera()->AddLightSource(lightSource);

	CollisionHandler::GetInstance()->OnCreate(100.0f);

	Model* model1 = new Model("./Resources/Models/Dice.obj", "./Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));


	SceneGraph::GetInstance()->AddModel(model1);

	GameObject* dice = new GameObject(model1, glm::vec3(20.0f, -1.0f, 0.0f));
	dice->SetScale(glm::vec3(0.5f));
	dice->AddComponent<AIComponent>();
	//apple->AddComponent<ComponentA>();
	//apple->RemoveComponent<ComponentA>();
	SceneGraph::GetInstance()->AddGameObject(dice, "apple");

	return true;
}

void TestAIScene::Update(const float deltaTime_)
{
	//std::cout << deltaTime_ << std::endl;
	SceneGraph::GetInstance()->Update(deltaTime_);
	Frustum::GetInstance()->ExtractFrustumResults();

}

void TestAIScene::Render()
{
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}
