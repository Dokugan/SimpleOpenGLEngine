#include <malloc.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include "Shader.h"
#include "Renderer.h"



Shader::Shader(const std::string& filepath)
	: m_filePath(filepath), m_rendererId(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_rendererId = CreateShader(source.vertexSource, source.fragmentSource);

	
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

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
		return m_uniformLocationCache[name];

	GlCall(int location = glGetUniformLocation(m_rendererId, name.c_str()))
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesnt exist";
	return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[static_cast<int>(type)] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string source)
{
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
		char* message = (char*) _malloca(length * sizeof(char));
		GlCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		GlCall(glDeleteShader(id));
		_freea(message);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string vertexShader, const std::string fragmentShader)
{
	
	GlCall(auto program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GlCall(glAttachShader(program, vs));
	GlCall(glAttachShader(program, fs));
	GlCall(glLinkProgram(program));
	GlCall(glValidateProgram(program));

	GlCall(glDeleteShader(vs));
	GlCall(glDeleteShader(fs));

	return program;
}



