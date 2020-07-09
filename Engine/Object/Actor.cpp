#include "pch.h"
#include "Actor.h"

namespace nc
{
    bool Actor::Load(const std::string& filename)
    {
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open())
		{
			success = true;

			//read color
			stream >> m_color;
			//read points
			while (!stream.eof())
			{
				Vector2 point;
				stream >> point;

				if (!stream.eof())
				{
					m_points.push_back(point);
				}
			}
			stream.close();
		}

		return success;
    }

    void Actor::Update(float dt)
    {
    }

    void Actor::Draw(Core::Graphics& graphics)
    {
        // draw shape using transform
    }

}
