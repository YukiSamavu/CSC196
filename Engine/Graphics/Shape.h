#pragma once

#include "core.h"
#include "Math/Color.h"
#include "Math/Vector2.h"

namespace nc
{
	class Shape
	{
	public:
		Shape();
		Shape(const std::vector<nc::Vector2>& points, const Color& color);

		void Draw(Core::Graphics& graphics, nc::Vector2 position, float scale = 1.0f, float angle = 0.0f);

		void SetColor(Color color);
		const Color& GetColor() const;

	private:
		std::vector<nc::Vector2> m_points;
		Color m_color;
	};
}