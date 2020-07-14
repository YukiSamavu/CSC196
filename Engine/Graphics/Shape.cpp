#include "pch.h"
#include "Shape.h"
#include "Math/Matrix22.h"
#include <fstream>

namespace nc
{
	bool Shape::Load(const std::string& filename)
	{
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open())
		{
			success = true;

			//read color
			stream >> m_color;

			//read number of points
			std::string line;
			std::getline(stream, line);
			size_t size = stoi(line);

			//read points
			for (size_t i = 0; i < size; i++)
			{
				Vector2 point;
				stream >> point;

				m_points.push_back(point);
			}

			stream.close();
		}

		return success;
	}

	void Shape::Draw(Core::Graphics& graphics, nc::Vector2 position, float scale, float angle)
	{
		graphics.SetColor(m_color);

		nc::Matrix22 mxScale;
		mxScale.Scale(scale);

		nc::Matrix22 mxRotate;
		mxRotate.Rotate(angle);

		nc::Matrix22 mx;
		mx = mxScale * mxRotate;

		for (size_t i = 0; i < m_points.size() - 1; i++)
		{

			// local/object space points
			nc::Vector2 p1 = (m_points[i]);
			nc::Vector2 p2 = (m_points[i + 1]);

			//scale / rotate
			p1 = p1 * mx;
			p2 = p2 * mx;
			//translate
			p1 = p1 + position;
			p2 = p2 + position;

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Shape::Draw(Core::Graphics& graphics, const Transform& transform)
	{
		Draw(graphics, transform.position, transform.scale, transform.angle);
	}
}