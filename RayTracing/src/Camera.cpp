#include "Camera.h"


void Camera::OnUpdate(float ts)
{
}

void Camera::OnResize(uint32_t width, uint32_t height)
{
	if (m_ViewportWidth != width || m_ViewportHeight != height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		RecalculateRayDirections();
	}
}

void Camera::RecalculateRayDirections()
{
	m_RayDirections.resize(size_t(m_ViewportWidth * m_ViewportHeight));

	for (uint32_t y = 0; y < m_ViewportHeight; y++)
	{
		for (uint32_t x = 0; x < m_ViewportWidth; x++)
		{
			glm::vec2 coord = {float(x) / float(m_ViewportWidth), float(y) / float(m_ViewportHeight)};
			coord = coord * 2.0f - 1.0f;

			m_RayDirections[y * m_ViewportWidth + x] = {coord.x, coord.y, -1.0f};
		}
	}
}
