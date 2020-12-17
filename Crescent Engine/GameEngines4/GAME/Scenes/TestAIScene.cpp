#include "TestAIScene.h"
#include "../../Engine/Math/Frustum.h"

TestAIScene::TestAIScene() : Scene()
{
	hasObjects = true; 
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

	/*Model* DiceModel = new Model("./Resources/Models/Dice.obj", "./Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(DiceModel); 
	GameObject* DiceObject = new GameObject(DiceModel, glm::vec3(0.0f));
	DiceObject->SetScale(glm::vec3(0.5f));
	DiceObject->AddComponent<AIComponent>(glm::vec3());
	SceneGraph::GetInstance()->AddGameObject(DiceObject, "Dice");*/

	std::vector<Model*> models(10);
	std::vector<GameObject*> dices(10);
	for (int i = 0; i < 10; i++) {
		models[i] = new Model("./Resources/Models/Dice.obj", "./Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
		SceneGraph::GetInstance()->AddModel(models[i]);
		dices[i] = new GameObject(models[i], glm::vec3(i, std::rand() % 10, 0.0f));
		dices[i]->SetScale(glm::vec3(0.5f));
		
		dices[i]->AddComponent<AIComponent>(glm::vec3()); 
		SceneGraph::GetInstance()->AddGameObject(dices[i]);
	}

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

	ImGui::Begin("Hierachy");
	ImGui::SetWindowSize(ImVec2(100, 500), ImGuiCond_FirstUseEver);

	if (hasObjects) {
		std::map<std::string, GameObject*> sceneGameObjects = SceneGraph::GetInstance()->GetSceneGameObjects();
		std::map<std::string, GameObject*>::iterator it;

		for (it = sceneGameObjects.begin(); it != sceneGameObjects.end(); it++) {

			if (ImGui::Button(it->second->GetTag().c_str(), ImVec2(350, 20))) {
				propertiesWindowOpen = true;
				selectedObject = it->second->GetTag();
			}
		}
	}
	ImGui::End();

	if (propertiesWindowOpen) {
		ImGui::Begin("Properties Panel");
		ImGui::Text("Currently Editing: %s", selectedObject.c_str());
		ImGui::Text("Position X:");
		ImGui::SameLine();

		float currentPosition = SceneGraph::GetInstance()->GetGameObject(selectedObject.c_str())->GetPosition().x;
		ImGui::SliderFloat("", &currentPosition, currentPosition - 0.1f, currentPosition + 0.1f);
		SceneGraph::GetInstance()->GetGameObject(selectedObject.c_str())->SetPosition(glm::vec3(currentPosition, SceneGraph::GetInstance()->GetGameObject(selectedObject.c_str())->GetPosition().y, SceneGraph::GetInstance()->GetGameObject(selectedObject.c_str())->GetPosition().z));
		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());
}
