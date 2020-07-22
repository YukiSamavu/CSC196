#pragma once

#include "core.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Math/Transform.h"
#include <vector>
#include <string>

namespace nc
{
	class Shape
	{
	public:
		Shape() {};
		Shape(const std::vector<nc::Vector2>& points, const Color& color);

		bool Load(const std::string& filenme);

		void Draw(Core::Graphics& graphics, nc::Vector2 position, float scale = 1.0f, float angle = 0.0f);
		void Draw(Core::Graphics& graphics, const Transform& transform);

		float GetRadius() const { return m_radius; }
		void SetColor(Color color) { m_color = color; }
		const Color& GetColor() const { return m_color; }

	private:
		std::vector<nc::Vector2> m_points;
		Color m_color;
		float m_radius{0};
	};
}