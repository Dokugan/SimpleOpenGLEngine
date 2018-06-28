#pragma once
#include "component.h"

#include "Camera.h"
#include "../main/Game.h"



class MeshComponent :
	public Component
{
	float* vertices;
	unsigned int vertexCount;
	unsigned int* indices;
	unsigned int indicesCount;

private:
	bool loadModelInMemory(const std::string& filePath, int* rCount, float* rVertices, int* rIndex);
	void loadModel(std::string path);

public:
	MeshComponent();
	MeshComponent(const std::string& filePath);
	void Render(const Camera& camera, GameObject* obj);

};





