#include "Renderer.h"

#include <Walnut/Random.h>

#include "Ray.h"

namespace Utils {

	static uint32_t ConvertToRGBA(const glm::vec4& color)
	{
		uint8_t r = (uint8_t)(color.r * 255.0f);
		uint8_t g = (uint8_t)(color.g * 255.0f);
		uint8_t b = (uint8_t)(color.b * 255.0f);
		uint8_t a = (uint8_t)(color.a * 255.0f);

		uint32_t result = (a << 24) | (b << 16) | (g << 8) | r;
		return result;
	}

}

void Renderer::OnResize(uint32_t width, uint32_t height)
{
	if (!m_Image)
	{
		m_Image = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
		m_ImageData = new uint32_t[width * height];
		return;
	}
	if (m_Image->GetWidth() != width || m_Image->GetHeight() != height)
	{
		m_Image->Resize(width, height);

		delete[] m_ImageData;
		m_ImageData = new uint32_t[width * height];
	}
}

void Renderer::Render(const Camera& camera)
{
	m_ActiveCamera = &camera;

	for (uint32_t y = 0; y < m_Image->GetHeight(); ++y)
	{
		for (uint32_t x = 0; x < m_Image->GetWidth(); ++x)
		{
			m_ImageData[y*m_Image->GetWidth()+x] = Utils::ConvertToRGBA(PerPixel(x, y));
		}
	}
	m_Image->SetData(m_ImageData);
}

glm::vec4 Renderer::PerPixel(uint32_t x, uint32_t y) const
{
	const Ray ray(m_ActiveCamera->GetPosition(), m_ActiveCamera->GetRayDirections()[y * m_Image->GetWidth() + x]);
	if (HitSphere({0, 0, 2}, 0.5, ray))
		return {1.f, 0.2f, 1.f, 1.f};

    const float a = 0.5f*(glm::normalize(ray.GetDirection()).y + 1.f);
    return glm::vec4((1.f-a)*glm::vec3(1.0, 1.0, 1.0) + a*glm::vec3(0.5, 0.7, 1.0), 1.0);
}

bool Renderer::HitSphere(const glm::vec3& center, float radius, const Ray& ray)
{
	const glm::vec3 rayDirection = ray.GetDirection(), rayOrigin = ray.GetOrigin(), oc = rayOrigin - center;
	const float a = glm::dot(rayDirection, rayDirection), b = 2.f * glm::dot(rayDirection, oc), c = glm::dot(oc, oc) - radius * radius;
	const float delta = b * b - 4.f * a * c;
	return delta >= 0;
}
