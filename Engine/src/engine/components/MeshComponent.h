#pragma once
#include "Component.h"
#include <string>
#include <vector>
#include "../../ext/glm/glm.hpp"
#include "../LightSource.h"
#include "../../gl/Texture.h"

namespace engine {
	
	struct Material
	{
		std::string diffuse_texture;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};

	class GameObject;
	class CameraComponent;
	class LightSource;

	class MeshComponent :
		public Component
	{
		float* m_vertices = nullptr;
		unsigned int m_vertexCount = 0;
		unsigned int* m_indices = nullptr;
		unsigned int m_indicesCount = 0;
		gl::Texture* m_texture = nullptr;
		gl::Shader* m_shader = nullptr;
		bool m_isInit = false;

		Material m_mtl;

		//bool loadModelInMemory(const std::string& filePath, int* rCount, float* rVertices, int* rIndex);
		void LoadModel(const std::string& path, const std::string& mtlbasedir);
		void InitTexture();
		void InitShader();
	public:
		MeshComponent();
		MeshComponent(const std::string& modelFilePath, const std::vector<std::string> shaderPaths = std::vector<std::string>());
		~MeshComponent();

		void Render(const CameraComponent* camera, LightSources* lights, float ambientIntensity, glm::vec3 ambientColour);

	};

}
