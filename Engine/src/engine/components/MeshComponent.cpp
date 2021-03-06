#include "MeshComponent.h"
#include <filesystem>

#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#endif 

//#include <GLFW/glfw3.h>
#include "../../gl/Renderer.h"
#include "../../gl/VertexBufferLayout.h"

#include "../../ext/tiny_obj_loader.h"
#include "../../ext/glm/gtx/transform.hpp"
#include "../../gl/Texture.h"
#include "../LightSource.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"
#include "../DirectionalLight.h"

namespace engine
{
	MeshComponent::MeshComponent()
		= default;

	MeshComponent::MeshComponent(const std::string& modelFilePath, const std::vector<std::string> shaderPaths)
	{
		auto modelPath = std::experimental::filesystem::path(modelFilePath);
		auto absoluteModelPath = std::experimental::filesystem::absolute(modelFilePath);
		std::cout << "loading model: " << absoluteModelPath << std::endl;
		//m_model = loadModelInMemory(absoluteModelPath.string(), absoluteModelPath.parent_path().string());
		LoadModel(absoluteModelPath.string(), absoluteModelPath.parent_path().string());
		
		if (shaderPaths.empty())
		{
			if (!m_mtl.diffuse_texture.empty())
			{
				auto absolute = std::experimental::filesystem::absolute("/res/shaders/TextureShader_fs.glsl");
				std::cout << absolute;
				m_shader = new gl::Shader(std::vector<std::string>({"G:/Documents/VS_Projects/SimpleGameEngine/x64/Debug/res/shaders/TextureShader_fs.glsl", "G:/Documents/VS_Projects/SimpleGameEngine/x64/Debug/res/shaders/TextureShader_vs.glsl" }));
			}
			else
			{
				m_shader = new gl::Shader(std::vector<std::string>({ "/res/shaders/basic.glsl"}));
			}
		}
		else {
			m_shader = new gl::Shader(shaderPaths);
		}
	}

	MeshComponent::~MeshComponent()
		= default;

	void MeshComponent::LoadModel(const std::string& path, const std::string& basedir)
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
			m_mtl.diffuse_texture = basedir + "\\" + materials[0].diffuse_texname;
			m_mtl.diffuse = glm::vec3(materials[0].diffuse[0], materials[0].diffuse[1], materials[0].diffuse[2]);
			m_mtl.specular = glm::vec3(materials[0].specular[0], materials[0].specular[1], materials[0].specular[2]);
			m_mtl.shininess = materials[0].shininess;
			//TODO more textures per model
		}
	}

	void MeshComponent::InitTexture()
	{
		if (!m_texture)
		{
			m_texture = new gl::Texture(m_mtl.diffuse_texture);
			//TODO more textures per model
		}
	}

	void MeshComponent::InitShader()
	{
		m_shader->CreateShader();
	}

	void MeshComponent::Render(const CameraComponent* camera, LightSources* lights, float ambientIntensity, glm::vec3 ambientColour)
	{
		//initialization has to happen on openGL context thread
		if (!m_isInit)
		{
			InitShader();
			InitTexture();
			m_isInit = true;
		}

		//Calculate Model view and projection matrices
		glm::mat4 model = m_parent->GetComponent<TransformComponent>()->GetModelMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera->GetFov()), camera->GetWidth() / camera->GetHeight(),
			camera->GetNear(), camera->GetFar());
		glm::mat4 view = camera->GetView();
		glm::mat4 mvp = projection * view * model;

		//Bind data
		gl::VertexBuffer vb = gl::VertexBuffer(static_cast<void*>(m_vertices), sizeof(float) * m_vertexCount * 8);
		gl::IndexBuffer ib = gl::IndexBuffer(m_indices, m_indicesCount);
		gl::VertexBufferLayout layout = gl::VertexBufferLayout();
		layout.Push<float>(3);

		if (!m_mtl.diffuse_texture.empty())
		{
			m_shader->SetUniformArraySize("u_DirectionalLights", lights->directionalLights.size());
			m_shader->SetUniform1i("u_TextureSampler", 0);
		}
		else
		{
			m_shader->SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
		}

		m_shader->SetUniform3f("u_ViewPos", camera->GetTransform()->GetPosition().x,
			camera->GetTransform()->GetPosition().y,
			camera->GetTransform()->GetPosition().z);
		m_shader->SetUniform1i("u_NumDirLights", lights->directionalLights.size());

		for (int i = 0; i < lights->directionalLights.size(); i++)
		{
			DirectionalLight& l = lights->directionalLights.at(i);
			m_shader->SetUniformVec3("u_DirectionalLights[" + std::to_string(i) + "].direction", l.m_direction);
			m_shader->SetUniformVec3("u_DirectionalLights[" + std::to_string(i) + "].diffuse", l.m_diffuse);
			m_shader->SetUniformVec3("u_DirectionalLights[" + std::to_string(i) + "].specular", l.m_specular);
		}

		//m_shader->SetUniform3f("u_Material.diffuse", m_mtl.diffuse.x, m_mtl.diffuse.y, m_mtl.diffuse.z);
		//m_shader->SetUniform3f("u_Material.specular", m_mtl.specular.x, m_mtl.specular.y, m_mtl.specular.z);
		m_shader->SetUniform1f("u_Material.shininess", m_mtl.shininess);
		m_shader->SetUniformMat4f("u_Model", model);
		m_shader->SetUniformMat4f("u_MVP", mvp);
		m_shader->SetUniform1f("u_AmbientIntensity", ambientIntensity);
		m_shader->SetUniform3f("u_AmbientColour", ambientColour.x, ambientColour.y, ambientColour.z);

		

		if (!m_texture->m_filePath.empty())
		{
			//texture coords
			layout.Push<float>(2);
			//normals
			layout.Push<float>(3);
			gl::VertexArray va = gl::VertexArray();
			va.AddBuffer(vb, layout);
			m_shader->Bind();
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
