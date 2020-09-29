#include "LoadOBJModel.h"
#include <sstream>
#include <algorithm>

LoadOBJModel::LoadOBJModel() {
	currentMaterial = Material();
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel() {
	OnDestroy(); 
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_) {
	LoadMaterialLibrary(mtlFilePath_); 
	LoadModel(objFilePath_);
}

void LoadOBJModel::LoadModel(const std::string& filePath_) {
	std::ifstream in(filePath_.c_str(), std::ios::in);
	
	if (!in) {
		Debugger::Error("Cannot open OBJ file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return; 
	}

	std::string line; 

	bool SetMinMaxValues = false; 
	while (std::getline(in, line)) {

		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;

			if (x < box.minVert.x) {
				box.minVert.x = x; 
			}
			
			if (x > box.maxVert.x) {
				box.maxVert.x = x; 
			}

			if (y < box.minVert.y) {
				box.minVert.y = y;
			}

			if (y > box.maxVert.y) {
				box.maxVert.y = y;
			}

			if (z < box.minVert.z) {
				box.minVert.z = z;
			}

			if (z > box.maxVert.z) {
				box.maxVert.z = z;
			}

			vertices.push_back(glm::vec3(x, y, z));

			while (!SetMinMaxValues) { 
				SetMinMaxValues = true; 
				box.minVert.x = box.maxVert.x = vertices[0].x;
				box.minVert.y = box.maxVert.y = vertices[0].y;
				box.minVert.z = box.maxVert.z = vertices[0].z;
			}
		}

		//NORMAL DATA
		else if (line.substr(0, 3) == "vn ") {
			std::stringstream vn(line.substr(2));
			float x, y, z;
			vn >> x >> y >> z;
			//std::cout << "VN: " << x << " " << y << " " << z << "\n" << std::endl;
			normals.push_back(glm::vec3(x, y, z));
		}

		//TEXTURE DATA
		else if (line.substr(0, 3) == "vt ") {
			std::stringstream vt(line.substr(2));
			float x, y, nil;
			vt >> x >> y >> nil;
			//std::cout << "VT: " << x << " " << y << "\n" << std::endl; 
			textureCoords.push_back(glm::vec2(x, y));
		}

		//FACE DATA (VERTEX POSITION/TEXTURE POSITION /TEXTURE NORMAL)
		else if (line.substr(0, 2) == "f ") {	

			if (line.find("/")) {	
				std::replace(line.begin(), line.end(), '/', ' ');
				
				std::stringstream f(line.substr(2));

				int VertexPosition[3];
				int TexturePosition[3];
				int NormalPosition[3];
				
				f >> VertexPosition[0] >> TexturePosition[0] >> NormalPosition[0] >> VertexPosition[1] >> TexturePosition[1] >> NormalPosition[1] >> VertexPosition[2] >> TexturePosition[2] >> NormalPosition[2];
				//std::cout << "F: " << VertexPosition[0] << " "  << TexturePosition[0] << " " << NormalPosition[0] << "   " << VertexPosition[1] << " " << TexturePosition[1] << " "  << NormalPosition[1] << "   " << VertexPosition[2] << " " << TexturePosition[2] << " " << NormalPosition[2] << "\n" << std::endl; 

				indices.push_back(VertexPosition[0]);
				indices.push_back(VertexPosition[1]);
				indices.push_back(VertexPosition[2]);

				textureIndices.push_back(TexturePosition[0]);
				textureIndices.push_back(TexturePosition[1]);
				textureIndices.push_back(TexturePosition[2]);

				normalIndices.push_back(NormalPosition[0]);
				normalIndices.push_back(NormalPosition[1]);
				normalIndices.push_back(NormalPosition[2]);
			}					
		}
		
		//NEW MESH 
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}

	PostProcessing();
}

std::vector<Vertex> LoadOBJModel::GetVerts() {
	return meshVertices;
}

std::vector<int> LoadOBJModel::GetIndices() {
	return indices;
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes(){
	return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox() {
	return box;
}

void LoadOBJModel::OnDestroy() {
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::PostProcessing() {
	for (int i = 0; i < indices.size(); i++) {
		Vertex vert; 
		vert.position = vertices[indices[i] - 1];
		vert.normal = normals[normalIndices[i] - 1];
		vert.texCoords = textureCoords[textureIndices[i] - 1];
		meshVertices.push_back(vert);
	}

	SubMesh subMesh; 

	subMesh.vertextList = meshVertices; 
	subMesh.meshIndices = indices; 
	subMesh.material = currentMaterial; 

	subMeshes.push_back(subMesh);

	indices.clear(); 
	normalIndices.clear(); 
	textureIndices.clear(); 
	meshVertices.clear(); 
	currentMaterial = Material();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_) {
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_) {
	MaterialLoader::LoadMaterial(matFilePath_);
}