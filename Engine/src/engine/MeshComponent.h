#pragma once
#include "Component.h"
#include "GameObject.h"

namespace engine {

	namespace gl
	{
		class Texture;
		class Shader;
	}

	class MeshComponent :
		public Component
	{
		float* m_vertices = nullptr;
		unsigned int m_vertexCount = 0;
		unsigned int* m_indices = nullptr;
		unsigned int m_indicesCount = 0;
		gl::Texture* m_texture = nullptr;
		gl::Shader* m_shader = nullptr;
		std::string m_texturePath;

	private:
		bool loadModelInMemory(const std::string& filePath, int* rCount, float* rVertices, int* rIndex);
		void loadModel(const std::string& path, const std::string& mtlbasedir);

	public:
		MeshComponent();
		MeshComponent(const std::string& modelFilePath);
		~MeshComponent();

		void Render(const CameraComponent* camera, GameObject* obj, float ambientIntensity, glm::vec3 ambientColour);

	};

}
