#include "CubeComponent.h"
#include <iostream>
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtx/transform.hpp"
#include "transform.h"
#include "../gl/VertexBuffer.h"
#include "../gl/VertexBufferLayout.h"
#include "Camera.h"
#include "gameobject.h"


CubeComponent::CubeComponent()
{	
}


void CubeComponent::Render(const Camera& camera, GameObject* obj) const
{
	std::cout << "Rendering cube.." << std::endl;
	//Calculate Model view and projection matrices
	//glm::mat4 model = glm::translate(glm::mat4(1.0f), obj->GetComponent<Transform>()->GetPosition());
	glm::mat4 model = glm::mat4(1.0f);
	//glm::mat4 view = glm::lookAt(glm::vec3(4,3,3),
									//glm::vec3(0,0,0),
									//glm::vec3(0,1,0));
	//glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f);
	glm::mat4 mvp = camera.GetProjection() * camera.GetView() * model;

	//Get vertices and put them in float buffer
	float m_vertex_buffer_data[] =
	{
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};
	const int vertexCount = 36;

	


	//Bind data
	 std::cout << sizeof(m_vertex_buffer_data) << std::endl;
	 VertexBuffer vb = VertexBuffer(static_cast<void*>(m_vertex_buffer_data), sizeof(m_vertex_buffer_data));
	 VertexBufferLayout layout = VertexBufferLayout();
	 layout.Push<float>(3);
 
	 VertexArray va = VertexArray();
	 va.AddBuffer(vb, layout);

	Shader shader = Shader("res/shaders/Basic.shader");
	shader.SetUniformMat4f("u_MVP", mvp);
	// 	shader.SetUniform4f("u_Color", static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
	// 		static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
	// 		static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
	// 		1.0f);

	shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	Renderer r = Renderer();
	r.Draw(va, shader, vertexCount * 3);
}
