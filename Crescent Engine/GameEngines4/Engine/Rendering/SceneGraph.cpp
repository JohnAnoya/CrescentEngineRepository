#include "SceneGraph.h"

std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr; 
std::map<GLuint, std::vector<Model*>> SceneGraph::sceneModels = std::map<GLuint, std::vector<Model*>>();
std::map<std::string, GameObject*> SceneGraph::sceneGameObjects = std::map<std::string, GameObject*>(); 

SceneGraph::SceneGraph() {

}

SceneGraph::~SceneGraph() {
	OnDestroy(); 
}

SceneGraph* SceneGraph::GetInstance() {
	if (sceneGraphInstance.get() == nullptr) {
		sceneGraphInstance.reset(new SceneGraph);
	}

	return sceneGraphInstance.get();
}

void SceneGraph::OnDestroy() {
	if (sceneGameObjects.size() > 0) { 
		for (auto gameObject : sceneGameObjects) {
			delete gameObject.second; //We use second here because first is the GameObject's tag! 
			gameObject.second = nullptr; //Delete the GameObjects from memory 
		}
		sceneGameObjects.clear(); 
	}

	if (sceneModels.size() > 0) {
		for (auto entry : sceneModels) { //for each entry in this sceneModel's entry... 
			if (entry.second.size() > 0) {
				for (auto m : entry.second) {
					delete m;
					m = nullptr; 
				}
				entry.second.clear(); 
			}
		}
		sceneModels.clear(); 
	}
}

void SceneGraph::AddModel(Model* model_) {
	if (sceneModels.find(model_->GetShaderProgram()) == sceneModels.end()) {
		std::vector<Model*> tmp = std::vector<Model*>(); 
		tmp.reserve(10);
		tmp.push_back(model_);
		sceneModels.insert(std::pair<GLuint, std::vector<Model*>>(model_->GetShaderProgram(), tmp));
	}

	else {
		sceneModels[model_->GetShaderProgram()].push_back(model_);
	}
}

void SceneGraph::AddGameObject(GameObject* gameObject_, std::string tag_) {
	if (tag_ == "") {
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		gameObject_->SetTag(newTag);
		sceneGameObjects[newTag] = gameObject_;
	}

	else if (sceneGameObjects.find(tag_) == sceneGameObjects.end()) {
		gameObject_->SetTag(tag_); 
		sceneGameObjects[tag_] = gameObject_; 
	}

	else {
		Debugger::Warning("Trying to add a GameObject with tag " + tag_ + " that already exists!", "SceneGraph.cpp", __LINE__);
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		gameObject_->SetTag(newTag);
		sceneGameObjects[newTag] = gameObject_;
	}

	CollisionHandler::GetInstance()->AddObject(gameObject_);
}

GameObject* SceneGraph::GetGameObject(std::string tag_){
	if (sceneGameObjects.find(tag_) != sceneGameObjects.end()) {
		return sceneGameObjects[tag_];
	}
	
	else {
		return nullptr; 
	}
}

std::map<std::string, GameObject*> SceneGraph::GetSceneGameObjects() {
	if (sceneGameObjects.size() > 0) {
		return sceneGameObjects;
	}
}

void SceneGraph::Update(const float deltaTime_) {
	for (auto gameObjects : sceneGameObjects) {
		gameObjects.second->Update(deltaTime_);
	}
}

void SceneGraph::Render(Camera* camera_) {
	for (auto entry : sceneModels) {
		glUseProgram(entry.first); 
		for (auto m : entry.second) {
			m->Render(camera_);
		}
	}
}