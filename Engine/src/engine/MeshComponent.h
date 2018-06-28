#pragma once
#include "Component.h"
#include "GameObject.h"
#include "../gl/Texture.h"

namespace engine {

	class MeshComponent :
		public Component
	{
		float* vertices = nullptr;
		unsigned int vertexCount = 0;
		unsigned int* indices = nullptr;
		unsigned int indicesCount = 0;
		float* m_uvBuffer = nullptr;
		int m_uvCount = 0;
		gl::Texture* m_texture = nullptr;

	private:
		bool loadModelInMemory(const std::string& filePath, int* rCount, float* rVertices, int* rIndex);
		void loadModel(const std::string& path);

	public:
		MeshComponent();
		MeshComponent(const std::string& modelFilePath);
		~MeshComponent();

		void Render(const Camera& camera, GameObject* obj);

	};

}
