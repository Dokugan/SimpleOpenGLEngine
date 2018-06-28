#include "meshcomponent.h"

#include <iostream>
#include <filesystem>
#include <malloc.h>
//#include <PathCch.h>

#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#endif 

#include "../gl/VertexBufferLayout.h"
#include "../gl/VertexBuffer.h"
#include "../vendor/tiny_obj_loader.h"
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtx/transform.hpp"
#include "transform.h"
#include "gameobject.h"


MeshComponent::MeshComponent()
= default;

MeshComponent::MeshComponent(const std::string& path)
{
	auto modelPath = std::experimental::filesystem::path(path);
	auto absoluteModelPath = absolute(modelPath);
	std::cout << "loading model: " << absoluteModelPath << std::endl;
	//m_model = loadModelInMemory(absoluteModelPath.string(), absoluteModelPath.parent_path().string());
	loadModel(absoluteModelPath.string());
}

void MeshComponent::loadModel(std::string path)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str(), nullptr, true);

	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << err << std::endl;
	}

	if (!ret) {
		return;
	}

	vertexCount = attrib.vertices.size();
	vertices = static_cast<float*>(malloc(sizeof(float) * vertexCount));
	int i = 0;
	for(float vert : attrib.vertices)
	{
		vertices[i] = vert;
		i++;
	}

	indicesCount = 0;
	for (auto o : shapes)
	{
		indicesCount += o.mesh.indices.size();
	}

	indices = static_cast<unsigned int*> (malloc(sizeof(unsigned int) * indicesCount));
	i = 0;
	for (const  auto& o : shapes)
	{		
		for (auto indice : o.mesh.indices)
		{
			indices[i] = indice.vertex_index;
			i++;
		}
	}

	 int x = 0;
	//Code for rendering without vertex index
	//				|
	//				v

	// int i = 0;
	// indicesCount = shapes[0].mesh.indices.size();
	// vertexCount = indicesCount * 3;
	// vertices = new float[vertexCount];
	// for (auto indice : shapes[0].mesh.indices)
	// {
	// 	vertices[i * 3] = attrib.vertices[indice.vertex_index * 3];
	// 	vertices[i * 3 + 1] = attrib.vertices[indice.vertex_index * 3 + 1];
	// 	vertices[i * 3 + 2] = attrib.vertices[indice.vertex_index * 3 + 2];
	// 	i++;
	// }

	//TODO: retrieve more data
}

void MeshComponent::Render(const Camera& camera, GameObject* obj)
{
	//Calculate Model view and projection matrices
	glm::mat4 model = glm::translate(glm::mat4(1.0f), obj->GetComponent<Transform>()->GetPosition());
	glm::mat4 mvp = camera.GetProjection() * camera.GetView() * model;

	//Bind data
	VertexBuffer vb = VertexBuffer(static_cast<void*>(vertices), sizeof(float) * vertexCount);
	IndexBuffer ib = IndexBuffer(indices, indicesCount);
	VertexBufferLayout layout = VertexBufferLayout();
	layout.Push<float>(3);

	VertexArray va = VertexArray();
	va.AddBuffer(vb, layout);

	Shader shader = Shader("res/shaders/Basic.shader");
	shader.SetUniformMat4f("u_MVP", mvp);
	shader.SetUniform4f("u_Color", 1.0f,0.0f,0.0f,1.0f);

	Renderer r = Renderer();
	r.Draw(va, ib, shader);

}