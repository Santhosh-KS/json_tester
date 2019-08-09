#include <fstream>
#include <sstream>
#include <iostream>

#include "generic_json_parser.hpp"

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

bool GenericJsonParser::FileExists(const std::string &file) const
{
    std::ifstream f(file.c_str());
    return f.good();
}

GenericJsonParser::GenericJsonParser(const std::string &file)
    : is_file_exists_(FileExists(file)),
    file_name_(file)
{
}


bool GenericJsonParser::Parse()
{
    auto ret_val{false};
    if(!is_file_exists_) 
    {
        std::cout << "File " << file_name_.c_str() << " does not exists\n";
        return ret_val;
    }

    std::ifstream file(file_name_);
    std::stringstream json;
    json << file.rdbuf();

    return ValidateJson(json.str());
}

// Checks if the given Json data is in valid format without any errors.
bool GenericJsonParser::ValidateJson(const std::string &json_data) 
{
    document_.Parse(json_data.c_str());

    return document_.IsObject();
}

bool GenericJsonParser::HasMember(const std::string &key) const
{
    return document_.HasMember(key.c_str());
}

bool GenericJsonParser::IsArray(const std::string &key) const
{
    return document_[key.c_str()].IsArray();
}

bool GenericJsonParser::IsNumber(const std::string &key) const
{
    return document_[key.c_str()].IsNumber();
}

bool GenericJsonParser::IsDouble(const std::string &key) const
{
    return document_[key.c_str()].IsDouble();
}

bool GenericJsonParser::IsBool(const std::string &key) const
{
    return document_[key.c_str()].IsBool();
}

bool GenericJsonParser::IsString(const std::string &key) const
{
    return document_[key.c_str()].IsString();
}

std::uint32_t GenericJsonParser::ArraySize(const std::string &key) const
{
    std::uint32_t retVal{0};
    if (IsArray(key))
    {
        retVal = static_cast<std::uint32_t>(document_[key.c_str()].Capacity());
    }
    return retVal;
}

bool GenericJsonParser::ArrayElements(const std::string &key) const
{
    const rapidjson::Value& val = document_[key.c_str()];
    for (auto &v : val.GetArray())
    {
        //const auto &lanes_boundaries{v["lanes_boundaries"] };
        const rapidjson::Value& lanes_boundaries{v["lanes_boundaries"] };
        // std::cout << "lanes_boundaries type " << (lanes_boundaries.GetType()) << "\n";
        for(size_t i = 0 ; i < lanes_boundaries.Size(); i++)
        {
            std::cout << " ################# \n";
            std::cout << "my lanes_boundaries = " << i << "\n";
            const rapidjson::Value& poly_line = lanes_boundaries[i]["polyline"];
            std::cout << "my polyline type " << (poly_line.GetType()) << "\n";
            std::cout << " ################# \n";
            for(size_t j = 0 ; j < poly_line.Size(); j++)
            {
                std::cout << "my poly_line = " << j << "\n";
                std::vector<std::string> start_end_points{"point_end", "point_start"};
                std::vector<std::vector<double>> points_vector = GetAllPoints(start_end_points, j, poly_line);
            }
        }
    }
    return true;
}

double GenericJsonParser::GetDoubleValue(const std::string &key, const rapidjson::Value& val) const
{
    if (val.HasMember(key.c_str()))
    {
        std::cout << "my point " << key.c_str() << " = " << val[key.c_str()].GetDouble() << "\n";
        return val[key.c_str()].GetDouble();
    }
    return 0.0;
}

std::vector<double> GenericJsonParser::GetPoints(const std::vector<std::string> &keys,  const rapidjson::Value &points) const
{
    std::vector<double> x_y_vector;
    for(auto &x_y: keys)
    {
        x_y_vector.push_back(GetDoubleValue(x_y, points));
    }
    return x_y_vector;
}

std::vector<std::vector<double>> GenericJsonParser::GetAllPoints(const std::vector<std::string> &start_end_points, int index,  const rapidjson::Value &poly_line) const
{
    std::vector<std::vector<double>> points_vector;
    for (auto &plp: start_end_points)
    {
        std::cout << " ################# " << plp.c_str() << " #################\n";
        const rapidjson::Value &points = poly_line[index][plp.c_str()];
        std::vector<std::string> x_y_vec{"x", "y"};
        points_vector.push_back(GetPoints(x_y_vec, points));
        std::cout << " ################# \n";
    }
    return points_vector;
}
