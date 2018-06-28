#include <filesystem>

#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#endif 

#include "MeshComponent.h"
#include "../gl/Renderer.h"
#include "../gl/VertexBufferLayout.h"
#include "../vendor/tiny_obj_loader.h"
#include "../vendor/glm/gtx/transform.hpp"


namespace engine
{
	MeshComponent::MeshComponent()
		= default;

	MeshComponent::MeshComponent(const std::string& modelFilePath)
	{
		auto modelPath = std::experimental::filesystem::path(modelFilePath);
		auto absoluteModelPath = std::experimental::filesystem::absolute(modelFilePath);
		std::cout << "loading model: " << absoluteModelPath << std::endl;
		//m_model = loadModelInMemory(absoluteModelPath.string(), absoluteModelPath.parent_path().string());
		loadModel(absoluteModelPath.string());
	}

	MeshComponent::~MeshComponent()
	{
		_freea(m_texture);
	}

	void MeshComponent::loadModel(const std::string& path)
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
		for (float vert : attrib.vertices)
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
		for (const auto& o : shapes)
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

		m_uvCount = attrib.texcoords.size();


		//TODO: retrieve more data
	}

	void MeshComponent::Render(const Camera& camera, GameObject* obj)
	{
		//Calculate Model view and projection matrices
		glm::mat4 model = glm::translate(glm::mat4(1.0f), obj->GetComponent<Transform>()->GetPosition());
		glm::mat4 mvp = camera.GetProjection() * camera.GetView() * model;

		//Bind data
		gl::VertexBuffer vb = gl::VertexBuffer(static_cast<void*>(vertices), sizeof(float) * vertexCount);
		gl::IndexBuffer ib = gl::IndexBuffer(indices, indicesCount);
		gl::VertexBufferLayout layout = gl::VertexBufferLayout();
		layout.Push<float>(3);

		gl::VertexArray va = gl::VertexArray();
		va.AddBuffer(vb, layout);

		gl::Shader shader = gl::Shader("res/shaders/Basic.shader");
		shader.SetUniformMat4f("u_MVP", mvp);
		shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);

		gl::Renderer r = gl::Renderer();
		r.Draw(va, ib, shader);

	}
}
