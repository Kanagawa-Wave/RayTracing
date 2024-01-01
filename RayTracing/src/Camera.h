#pragma once

#include <vector>
#include <glm/glm.hpp>

class Camera
{
public:
	Camera() = default;

	void OnUpdate(float ts);
	void OnResize(uint32_t width, uint32_t height);

	const glm::vec3& GetPosition() const { return m_Position; }
	const std::vector<glm::vec3>& GetRayDirections() const { return m_RayDirections; }

private:
	void RecalculateRayDirections();

	glm::vec3 m_Position{0};
	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

	std::vector<glm::vec3> m_RayDirections;
};

