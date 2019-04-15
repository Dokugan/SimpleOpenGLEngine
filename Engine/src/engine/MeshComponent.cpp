#include "MeshComponent.h"
#include <filesystem>

#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#endif 

//#include <GLFW/glfw3.h>
#include "../gl/Renderer.h"
#include "../gl/VertexBufferLayout.h"
#include "../ext/tiny_obj_loader.h"
#include "../ext/glm/gtx/transform.hpp"
#include "../gl/Texture.h"


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
		loadModel(absoluteModelPath.string(), absoluteModelPath.parent_path().string());
	}

	MeshComponent::~MeshComponent()
	{
		delete(m_texture);
		delete(m_vertices);
		delete(m_indices);
	}

	void MeshComponent::loadModel(const std::string& path, const std::string& basedir)
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string err;
		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str(), basedir.c_str(), true);

		if (!err.empty()) { // `err` may contain warning message.
			std::cerr << err << std::endl;
		}

		if (!ret) {
			return;
		}

		// vertexCount = attrib.vertices.size();
		// vertices = static_cast<float*>(malloc(sizeof(float) * vertexCount));
		// int i = 0;
		// for (float vert : attrib.vertices)
		// {
		// 	vertices[i] = vert;
		// 	i++;
		// }
  //
		// indicesCount = 0;
		// for (auto o : shapes)
		// {
		// 	indicesCount += o.mesh.indices.size();
		// }
  //
		// indices = static_cast<unsigned int*> (malloc(sizeof(unsigned int) * indicesCount));
		// i = 0;
		// for (const auto& o : shapes)
		// {
		// 	for (auto indice : o.mesh.indices)
		// 	{
		// 		indices[i] = indice.vertex_index;
		// 		i++;
		// 	}
		// }
  //
		// m_uvCount = attrib.texcoords.size();
		// m_uvBuffer = static_cast<float*>(malloc(sizeof(float) * m_uvCount));
  //
		// i = 0;
		// for (float tex : attrib.texcoords)
		// {
		// 	m_uvBuffer[i] = tex;
		// 	i++;
		// }

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

		
		struct position
		{
			float x;
			float y;
			float z;
		};
		struct uv
		{
			float u;
			float v;
		};
		struct normal
		{
			float x;
			float y;
			float z;
		};
		struct vertex
		{
			position p;
			uv uv;
			normal normal;
		};

		struct indice
		{
			unsigned int index;
			unsigned int v;
			unsigned int vt;
			unsigned int vn;
		};

		std::vector<vertex> vertices;
		std::vector<indice> madeCombination;
		std::vector<int> indices;
		//int idx = 0;
		for (auto i : shapes[0].mesh.indices)
		{
			unsigned int v = i.vertex_index;
			unsigned int vt = i.texcoord_index;
			unsigned int vn = i.normal_index;

			bool shouldBreakOuter = false;
			for (auto c : madeCombination)
			{
				if (c.v == v && c.vt == vt && c.vn == vn)
				{
					indices.push_back(c.index);
					//idx++;
					shouldBreakOuter = true;
				}
			}
			if (shouldBreakOuter)
			{
				continue;
			}
			vertices.push_back(vertex
			{
				{
					attrib.vertices[3 * v + 0],
					attrib.vertices[3 * v + 1],
					attrib.vertices[3 * v + 2]
				},
				{
					attrib.texcoords[vt * 2 + 0],
					attrib.texcoords[vt * 2 + 1]
				},
				{
					attrib.normals[vn * 3 + 0],
					attrib.normals[vn * 3 + 1],
					attrib.normals[vn * 3 + 2]
				}
			});

			madeCombination.push_back({ static_cast<unsigned int>(madeCombination.size()) ,v, vt, vn});
			indices.push_back(madeCombination[madeCombination.size() - 1].index);
			//m_indices[idx] = madeCombination[madeCombination.size() - 1].index;
			//idx++;
		}

		m_vertexCount = vertices.size();
		m_vertices = static_cast<float*>(malloc(m_vertexCount * sizeof(float) * 8));

		int i = 0;
		for (auto v : vertices)
		{
			m_vertices[i * 8 + 0] = v.p.x;
			m_vertices[i * 8 + 1] = v.p.y;
			m_vertices[i * 8 + 2] = v.p.z;
			m_vertices[i * 8 + 3] = v.uv.u;
			m_vertices[i * 8 + 4] = v.uv.v;
			m_vertices[i * 8 + 5] = v.normal.x;
			m_vertices[i * 8 + 6] = v.normal.y;
			m_vertices[i * 8 + 7] = v.normal.z;
			i++;
		}

		m_indicesCount = indices.size();
		m_indices = static_cast<unsigned int*>(malloc(shapes[0].mesh.indices.size() * sizeof(int)));

		i = 0;
		for (auto ind : indices)
		{
			m_indices[i] = ind;
			i++;
		}

		if (!materials.empty())
		{
			m_texturePath = basedir + "\\" + materials[0].diffuse_texname;
			//TODO more textures per model
		}
	}

	void MeshComponent::Render(const CameraComponent& camera, GameObject* obj)
	{
		//Calculate Model view and projection matrices
		glm::mat4 model = glm::translate(glm::mat4(1.0f), obj->GetComponent<TransformComponent>()->GetPosition());
		glm::mat4 mvp = camera.GetProjection() * camera.GetView() * model;

		//Bind data
		gl::VertexBuffer vb = gl::VertexBuffer(static_cast<void*>(m_vertices), sizeof(float) * m_vertexCount * 8);
		gl::IndexBuffer ib = gl::IndexBuffer(m_indices, m_indicesCount);
		gl::VertexBufferLayout layout = gl::VertexBufferLayout();
		layout.Push<float>(3);

		if (!m_texture)
		{
			if (!m_texturePath.empty())
			{
				m_texture = new gl::Texture(m_texturePath);
				//TODO more textures per model
			}
		}

		if (!m_shader)
		{
			if (!m_texturePath.empty())
			{
				m_shader = new gl::Shader("res/shaders/TextureShader.shader");
				m_shader->SetUniformMat4f("u_MVP", mvp);
				m_shader->SetUniform1i("u_TextureSampler", 0);
			}
			else
			{
				m_shader = new gl::Shader("res/shaders/Basic.shader");
				m_shader->SetUniformMat4f("u_MVP", mvp);
				m_shader->SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
			}
		}

		if (m_texture)
		{
			//texture coords
			layout.Push<float>(2);
			//normals
			layout.Push<float>(3);
			gl::VertexArray va = gl::VertexArray();
			va.AddBuffer(vb, layout);
			m_texture->Bind();
			gl::Renderer r = gl::Renderer();
			r.Draw(va, ib, *m_shader);
		}
		else
		{
			layout.Push<float>(3);
			gl::VertexArray va = gl::VertexArray();
			va.AddBuffer(vb, layout);
			gl::Renderer r = gl::Renderer();
			r.Draw(va, ib, *m_shader);
		}
	}
}
