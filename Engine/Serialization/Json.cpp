#include "Json.h"
#include "rapidjson/istreamwrapper.h"
#include "Core/Logger.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Rect.h"
#include <fstream>

namespace jemgine
{
    bool json::Load(const std::string& filename, rapidjson::Document& document)
    {

        std::ifstream stream(filename);
        if(stream.is_open() == false)
        {
            LOG("error opening file %s.", filename.c_str());
            return false;
        }

        rapidjson::IStreamWrapper istream(stream);
        document.ParseStream(istream);
        if (document.IsObject() == false)
        {
            LOG("json file cannot be read %s.", filename.c_str());
            return false;
        }


        return true;
    }

    bool json::Get(const rapidjson::Value& value, const std::string& name, int& data)
    {
        // check if 'name' member exists and is of type 

        if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsInt() == false)
        {
            LOG("error reading json data %s", name.c_str());
            return false;
        }

        // set data 
        data = value[name.c_str()].GetInt();

        return true;
    }

    bool json::Get(const rapidjson::Value& value, const std::string& name, float& data)
    {
        if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsNumber() == false)
        {
            LOG("error reading json data %s", name.c_str());
            return false;
        }

        // set data 
        data = value[name.c_str()].GetFloat();

        return true;
    }

    bool json::Get(const rapidjson::Value& value, const std::string& name, bool& data)
    {
        if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsBool() == false)
        {
            LOG("error reading json data %s", name.c_str());
            return false;
        }

        // set data 
        data = value[name.c_str()].GetBool();

        return true;
    }

    bool json::Get(const rapidjson::Value& value, const std::string& name, std::string& data)
    {
        if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsString() == false)
        {
            LOG("error reading json data %s", name.c_str());
            return false;
        }

        // set data 
        data = value[name.c_str()].GetString();

        return true;
    }

    bool json::Get(const rapidjson::Value& value, const std::string& name, Vector2& data)
    {
        if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 2)
        {
            LOG("error reading json data %s", name.c_str());
            return false;

        }

        // create json array object 
        auto& array = value[name.c_str()];
        // get array values 
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {

                LOG("error reading json data (not a float) %s", name.c_str());
                return false;
            }

            data[i] = array[i].GetFloat();
        }

        return true;
    }

    bool json::Get(const rapidjson::Value& value, const std::string& name, Color& data)
    {
        if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 4)
        {
            LOG("error reading json data %s", name.c_str());
            return false;

        }

        // create json array object 
        auto& array = value[name.c_str()];
        // get array values 
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsInt())
            {
                LOG("error reading json data (not a float) %s", name.c_str());
                return false;
            }

            data[i] = array[i].GetInt();
        }

        return true;
    }

    bool json::Get(const rapidjson::Value& value, const std::string& name, Rect& data)
    {
        if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 4)
        {
            LOG("error reading json data %s", name.c_str());
            return false;

        }

        // create json array object 
        auto& array = value[name.c_str()];
        // get array values 

        data.x = array[0].GetInt();
        data.y = array[1].GetInt();
        data.w = array[2].GetInt();
        data.h = array[3].GetInt();

        return true;
    }

}