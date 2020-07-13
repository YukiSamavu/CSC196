#include "pch.h"
#include "Transform.h"

namespace nc
{
    std::istream& operator>>(std::istream& stream, Transform& transform)
    {
        stream >> transform.position;

        std::string line;
        std::getline(stream, line);
        transform.scale = stof(line);

        //stream >> transform.scale;

        std::getline(stream, line);
        transform.angle = stof(line);

        //stream >> transform.angle;

        return stream;
    }
}
