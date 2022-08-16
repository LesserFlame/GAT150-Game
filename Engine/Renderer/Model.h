#pragma once
#include "Renderer.h"
#include "Resource/Resource.h"
#include <vector>
#include <string>

namespace jemgine
{
	class Model : public Resource
	{
	public:
		Model() = default;
		Model(const std::vector<jemgine::Vector2>& points, const jemgine::Color& color) :
			m_points{ points },
			m_color { color } {}

		Model(const std::string filename);

		bool Create(const std::string& filename, void* data) override;

		void Draw(Renderer& renderer, const Vector2& position, float angle, const Vector2& scale = Vector2(1, 1));
		void Draw(Renderer& renderer, const Transform& transform);

		bool Load(const std::string& filename);

		float CalculateRadius();
		float GetRadius() { return m_radius; }

	private:
		jemgine::Color m_color{ 0, 0, 0, 0 };
		std::vector<jemgine::Vector2> m_points;

		float m_radius = 0;
	};
}
