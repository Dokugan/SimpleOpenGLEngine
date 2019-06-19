#pragma once
#include <string>
#include <unordered_map>
#include "../ext/glm/glm.hpp"

namespace engine
{
	namespace gl
	{
		

		struct UniformArray
		{
			std::string name, type;
			int lineNum;
			unsigned int shaderType, size;
		};

		class ShaderProgramSource
		{
			std::string m_vertexSource;
			std::string m_fragmentSource;
						
			std::vector<UniformArray> m_uniformArrays;

		public:
			ShaderProgramSource();
			~ShaderProgramSource();

			void SetVertexSource(const std::string& source);
			void SetFragmentSource(const std::string& source);
			std::string& GetVertexSource();
			std::string& GetFragmentSource();
			void AddUniformArray(UniformArray array);
			UniformArray* GetUniformArray(const std::string& name);
			std::vector<UniformArray> GetUniformArrayListVertex();
			std::vector<UniformArray> GetUniformArrayListFragment();
			std::vector<UniformArray>* GetUniformArrayList();
		};

		class Shader
		{
			unsigned int m_rendererId;
			std::vector<std::string> m_shaderPaths;
			std::unordered_map<std::string, int> m_uniformLocationCache;
			ShaderProgramSource m_source;

		public:
			Shader(std::vector<std::string> sourcePaths = std::vector<std::string>());
			~Shader();
			
			void Bind() const;
			void Unbind() const;

			void CreateShader();
			unsigned int CompileShader(unsigned int type);
			ShaderProgramSource* GetSource();

			void SetUniform1i(const std::string& name, int i1);
			void SetUniform1f(const std::string& name, float v1);
			void SetUniform3f(const std::string& name, float v0, float v1, float v2);
			void SetUniformVec3(const std::string& name, glm::vec3 v0);
			void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
			void SetUniformMat4f(const std::string& name, const glm::mat4&);

			void SetUniformArraySize(std::string name, unsigned int size);

			static ShaderProgramSource ParseShader(std::vector<std::string>* sourcePaths);

		private:
			
			int GetUniformLocation(const std::string& name);
		};
	}
}
