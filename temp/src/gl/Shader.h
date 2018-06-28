#pragma once
#include <string>
#include <unordered_map>
#include "../vendor/glm/glm.hpp"

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
	unsigned int m_rendererId;
	std::string m_filePath;
	std::unordered_map<std::string, int> m_uniformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int i1);
	void SetUniform1f(const std::string& name, float v1);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4&);

	static ShaderProgramSource ParseShader(const std::string& filePath);
	static unsigned int CreateShader(std::string vertexShader, std::string fragmentShader);
	static unsigned int CompileShader(unsigned type, const std::string source);

private:
	
	
	int GetUniformLocation(const std::string& name);
};

