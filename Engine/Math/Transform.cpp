#include "Transform.h"

bool jemgine::Transform::Write(const rapidjson::Value& value) const
{
    return false;
}

bool jemgine::Transform::Read(const rapidjson::Value& value)
{
    READ_DATA(value, position);
    READ_DATA(value, scale);
    READ_DATA(value, rotation);

    return true;
}
