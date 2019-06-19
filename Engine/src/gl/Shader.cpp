#include "Shader.h"
#if !defined(__gl_h_) && !defined(__GL_H__) && !defined(_GL_H) && !defined(__X_GL_H)
#include <GL/glew.h>
#endif
#include <sstream>
#include <fstream>
#include <iostream>
#include <malloc.h>

#include "Renderer.h"
#include <iterator>
#include <algorithm>
#include <utility>

namespace engine
{
	namespace gl
	{
		ShaderProgramSource::ShaderProgramSource()
		= default;

		ShaderProgramSource::~ShaderProgramSource()
		= default;

		void ShaderProgramSource::SetVertexSource(const std::string& source) {
			m_vertexSource = source;
		}

		void ShaderProgramSource::SetFragmentSource(const std::string& source) {
			m_fragmentSource = source;
		}

		std::string& ShaderProgramSource::GetVertexSource() {
			return m_vertexSource;
		}

		std::string& ShaderProgramSource::GetFragmentSource() {
			return m_fragmentSource;
		}

		void ShaderProgramSource::AddUniformArray(UniformArray array) {
			m_uniformArrays.push_back(array);
		}

		UniformArray* ShaderProgramSource::GetUniformArray(const std::string& name)
		{
			for (int i = 0; i < m_uniformArrays.size(); i++)
			{
				if (m_uniformArrays[i].name == name)
				{
					return &m_uniformArrays[i];
				}
			}
			return nullptr;
		}

		std::vector<UniformArray> ShaderProgramSource::GetUniformArrayListVertex()
		{
			auto results = std::vector<UniformArray>();
			for (auto uArray : m_uniformArrays)
			{
				if (uArray.shaderType == GL_VERTEX_SHADER)
				{
					results.push_back(uArray);
				}
			}
			return results;
		}

		std::vector<UniformArray> ShaderProgramSource::GetUniformArrayListFragment()
		{
			auto results = std::vector<UniformArray>();
			for (auto uArray : m_uniformArrays)
			{
				if (uArray.shaderType == GL_FRAGMENT_SHADER)
				{
					results.push_back(uArray);
				}
			}
			return results;
		}

		std::vector<UniformArray>* ShaderProgramSource::GetUniformArrayList()
		{
			return &m_uniformArrays;
		}

		Shader::Shader(std::vector<std::string> sourcePaths)
			: m_rendererId(0)
		{
			if (!sourcePaths.empty())
			{
				m_shaderPaths = std::vector<std::string>(std::move(sourcePaths));
				m_source = ParseShader(&m_shaderPaths);
			}
		}

		Shader::~Shader()
		{
			GlCall(glDeleteProgram(m_rendererId));
		}

		void Shader::Bind() const
		{
			GlCall(glUseProgram(m_rendererId));
		}

		void Shader::Unbind() const
		{
			GlCall(glUseProgram(0));
		}

		void Shader::SetUniform1i(const std::string& name, int i1)
		{
			GlCall(glUseProgram(m_rendererId));
			GlCall(glUniform1i(GetUniformLocation(name), i1));
		}

		void Shader::SetUniform1f(const std::string& name, float v1)
		{
			GlCall(glUseProgram(m_rendererId));
			GlCall(glUniform1f(GetUniformLocation(name), v1));
		}

		void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
		{
			GlCall(glUseProgram(m_rendererId));
			GlCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
		}

		void Shader::SetUniformVec3(const std::string& name, glm::vec3 v0)
		{
			GlCall(glUseProgram(m_rendererId))
			GlCall(glUniform3f(GetUniformLocation(name), v0.x, v0.y, v0.z));
		}

		void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
		{
			GlCall(glUseProgram(m_rendererId));
			GlCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
		}

		void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
		{
			GlCall(glUseProgram(m_rendererId));
			GlCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
		}

		void Shader::SetUniformArraySize(std::string name, unsigned size)
		{
			UniformArray* uArray = m_source.GetUniformArray(name);
			if (uArray->size != size)
			{
				uArray->size = size;
				CreateShader();
			}
		}

		int Shader::GetUniformLocation(const std::string& name)
		{
			if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
				return m_uniformLocationCache[name];

			GlCall(int location = glGetUniformLocation(m_rendererId, name.c_str()))
				if (location == -1)
					std::cout << "Warning: uniform '" << name << "' doesnt exist";
			return location;
		}

		ShaderProgramSource Shader::ParseShader(std::vector<std::string>* sourcePaths)
		{
			ShaderProgramSource result = ShaderProgramSource();
			std::stringstream ss[2];

			enum class ShaderType
			{
				NONE = -1, VERTEX = 0, FRAGMENT = 1
			};

			for (const std::string& path : *sourcePaths) {
				std::ifstream stream(path);

				int lineNum = 0;
				std::string line;
				ShaderType type = ShaderType::NONE;
				while (std::getline(stream, line))
				{

					if (line.find("//shader") != std::string::npos)
					{
						lineNum = 0;
						if (line.find("vertex") != std::string::npos)
							type = ShaderType::VERTEX;
						else if (line.find("fragment") != std::string::npos)
							type = ShaderType::FRAGMENT;
					}
					else
					{
						ss[static_cast<int>(type)] << line << '\n';
					}

					if (line.find("uniform") != std::string::npos)
					{
						if (line.find('[') != std::string::npos && line.find(']') != std::string::npos)
						{
							std::istringstream iss(line);
							std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
								std::istream_iterator<std::string>{} };
							const int bracketOpenPos = tokens[2].find("[");
							const int bracketClosedPos = tokens[2].find("]");
							std::string name = tokens[2].substr(0, bracketOpenPos);
							std::string dataType = tokens[1];
							unsigned int size = std::stol(tokens[2].substr(bracketOpenPos + 1, bracketClosedPos - (bracketOpenPos + 1)));
							unsigned int shaderType = 0;
							if (type == ShaderType::VERTEX)
								shaderType = GL_VERTEX_SHADER;
							if (type == ShaderType::FRAGMENT)
								shaderType = GL_FRAGMENT_SHADER;
							result.AddUniformArray({ name, dataType, lineNum, shaderType, size });
						}
					}
					lineNum++;
				}
			}

			result.SetVertexSource(ss[0].str());
			result.SetFragmentSource(ss[1].str());
			return result;
		}

		unsigned int Shader::CompileShader(unsigned int type)
		{
			//apply uniform array changes
			std::vector<UniformArray> list;
			std::string source;
			if (type == GL_VERTEX_SHADER)
			{
				source = m_source.GetVertexSource();
				list = m_source.GetUniformArrayListVertex();
			}
			else if (type == GL_FRAGMENT_SHADER)
			{
				source = m_source.GetFragmentSource();
				list = m_source.GetUniformArrayListFragment();
			}
			else { list = std::vector<UniformArray>(); }
			std::stringstream stream(source);
			int lineNum = 1;
			std::string line;
			std::string newSource;


			if (!list.empty())
			{
				for (UniformArray uniform : list)
				{
					while (std::getline(stream, line))
					{
						if (uniform.lineNum == lineNum && type == uniform.shaderType)
						{
							if (uniform.size < 1)
								uniform.size = 1;
							line = "uniform " + uniform.type + " " + uniform.name + "[" + std::to_string(uniform.size) + "];";
						}
						newSource += line + '\n';
						lineNum++;
					}
				}
				source = newSource;
			}

			GlCall(unsigned int id = glCreateShader(type));
			const char* src = source.c_str();
			GlCall(glShaderSource(id, 1, &src, nullptr));
			GlCall(glCompileShader(id));
			
			int result;
			GlCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
			if (result == GL_FALSE)
			{
				int length;
				GlCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
				char* message = (char*)_malloca(length * sizeof(char));
				GlCall(glGetShaderInfoLog(id, length, &length, message));
				std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
				std::cout << message << std::endl;
				GlCall(glDeleteShader(id));
				_freea(message);
				return 0;
			}

			return id;
		}

		ShaderProgramSource* Shader::GetSource()
		{
			return &m_source;
		}

		void Shader::CreateShader()
		{
			GlCall(glDeleteProgram(m_rendererId));
			GlCall(auto program = glCreateProgram());
			unsigned int vs = CompileShader(GL_VERTEX_SHADER);
			unsigned int fs = CompileShader(GL_FRAGMENT_SHADER);

			GlCall(glAttachShader(program, vs));
			GlCall(glAttachShader(program, fs));
			GlCall(glLinkProgram(program));
			GlCall(glValidateProgram(program));

			GlCall(glDeleteShader(vs));
			GlCall(glDeleteShader(fs));

			m_rendererId = program;
		}
	}
}
