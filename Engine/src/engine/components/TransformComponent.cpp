#include "TransformComponent.h"
#include "../../ext/glm/glm.hpp"
#include "../../ext/glm/gtx/transform.hpp"
#include "../../ext/glm/gtc/quaternion.hpp"
#include "../../ext/glm/gtx/matrix_decompose.hpp"
#include "../../ext/glm/gtx/quaternion.hpp"
#include "../../ext/glm/gtx/rotate_vector.hpp"
#include <iostream>


namespace engine {

	glm::mat4 GetIdentityMatrix()
	{
		return glm::mat4(1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);
	}

	TransformComponent::TransformComponent()
	{
		//m_model_matrix = GetIdentityMatrix();
		m_rotation = glm::quat(1, 0, 0, 0);
		m_position = glm::vec3(0, 0, 0);
		m_scale = glm::vec3(1, 1, 1);
	}

	TransformComponent::TransformComponent(glm::vec3 position)
	{
		m_position = position;
		m_rotation = glm::quat(1, 0, 0, 0);
		m_scale = glm::vec3(1, 1, 1);
		//m_model_matrix = GetIdentityMatrix();
		//m_model_matrix = glm::translate(m_model_matrix, position);
	}

	TransformComponent::TransformComponent(glm::vec3 position, glm::quat rotation)
	{
		m_position = position;
		m_rotation = rotation;
		m_scale = glm::vec3(1, 1, 1);
		//m_model_matrix = GetIdentityMatrix();
		//m_model_matrix = glm::translate(m_model_matrix, position);
		//m_model_matrix = Rotate()
	}

	glm::mat4 TransformComponent::GetModelMatrix() const
	{
		glm::mat4 translationMat = GetIdentityMatrix();
		translationMat = glm::translate(translationMat, m_position);
		// get rotation matrix from rotation
		float angle = 2 * acos(m_rotation.w);
		glm::mat4 rotationMat;
		// when angle = 0 divide by 0 error occurs
		if (angle != 0.f)
		{
			rotationMat = glm::rotate(GetIdentityMatrix(), angle, glm::vec3(
				m_rotation.x / sqrt(1 - m_rotation.w * m_rotation.w),
				m_rotation.y / sqrt(1 - m_rotation.w * m_rotation.w),
				m_rotation.z / sqrt(1 - m_rotation.w * m_rotation.w)));
		}
		else { rotationMat = GetIdentityMatrix(); }

		glm::mat4 modelMatrix = translationMat * rotationMat;
		modelMatrix = glm::scale(modelMatrix, m_scale);
		return modelMatrix;
	}

	glm::vec3 TransformComponent::GetPosition() const
	{
		return m_position;
	}

	glm::quat TransformComponent::GetRotation() const
	{
		return m_rotation;
	}

	glm::vec3 TransformComponent::Forward()
	{
		return glm::vec3(0);
	}

	void TransformComponent::Scale(glm::vec3 scale)
	{
		m_scale = scale;
	}

	void TransformComponent::Rotate(glm::vec3 axis, float angle)
	{
		m_rotation = glm::rotate(m_rotation, angle, axis);
	}

	void TransformComponent::Rotate(float yaw, float pitch, float roll)
	{
		float rYaw, rPitch, rRoll;
		glm::quat q1 = m_rotation;
		float sqw = q1.w * q1.w;
		float sqx = q1.x * q1.x;
		float sqy = q1.y * q1.y;
		float sqz = q1.z * q1.z;
		float unit = sqx + sqy + sqz + sqw;
		float test = q1.x * q1.y + q1.z * q1.w;
		if (test > 0.49999 * unit) { // singularity at north pole
			rYaw = 2 * atan2(q1.x, q1.w);
			rPitch = 1.5706f;// PI / 2 - ~0.0001
			if (pitch > 0)
				rPitch -= pitch;
			rRoll = 0;
		}
		else if (test < -0.49999 * unit) { // singularity at south pole
			rYaw = -2 * atan2(q1.x, q1.w);
			rPitch = -1.5708f; // -PI / 2 + ~0.0001
			if (pitch < 0)
				rPitch -= pitch;
			rRoll = 0;
		}
		else {
			rYaw = atan2(2 * q1.y * q1.w - 2 * q1.x * q1.z, sqx - sqy - sqz + sqw);
			rPitch = asin(2 * test / unit) - pitch;
			if (rPitch > 1.5706f)
				rPitch = 1.5706f;
			else if (rPitch < -1.5708f)
				rPitch = -1.5708f;
			rRoll = atan2(2 * q1.x * q1.w - 2 * q1.y * q1.z, -sqx + sqy - sqz + sqw);
		}

		rYaw -= yaw;

		//if (rPitch - pitch < 1.57079f && rPitch - pitch > -1.57079f)
		//{
		//	rPitch -= pitch;
		//}
		//else
		//{
		//	
		//}
		//std::cout << rPitch << '\n';
		rRoll -= roll;

		float c1 = cos(rYaw / 2);
		float s1 = sin(rYaw / 2);
		float c2 = cos(rPitch / 2);
		float s2 = sin(rPitch / 2);
		float c3 = cos(rRoll / 2);
		float s3 = sin(rRoll / 2);
		float c1c2 = c1 * c2;
		float s1s2 = s1 * s2;
		glm::quat q = glm::quat();
		m_rotation.w = c1c2 * c3 - s1s2 * s3;
		m_rotation.x = c1c2 * s3 + s1s2 * c3;
		m_rotation.y = s1 * c2 * c3 + c1 * s2 * s3;
		m_rotation.z = c1 * s2 * c3 - s1 * c2 * s3;
	}

	void TransformComponent::Translate(glm::vec3 movement)
	{
		m_position += movement;
	}
}
