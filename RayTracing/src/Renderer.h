#pragma once

#include <memory>

#include "Camera.h"
#include "Ray.h"
#include "Walnut/Image.h"

class Renderer
{
public:
	Renderer() = default;

	void OnResize(uint32_t width, uint32_t height);
	void Render(const Camera& camera);

	std::shared_ptr<Walnut::Image> GetImage() const { return m_Image; }

private:
	glm::vec4 PerPixel(uint32_t x, uint32_t y) const;
	static bool HitSphere(const glm::vec3& center, float radius, const Ray& ray);

	const Camera* m_ActiveCamera = nullptr;
	std::shared_ptr<Walnut::Image> m_Image;
	uint32_t* m_ImageData = nullptr;
};

