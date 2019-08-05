#include <fstream>
#include <sstream>
#include <iostream>

#include "generic_json_parser.hpp"

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
    return document_.IsArray();
}

bool GenericJsonParser::IsNumber(const std::string &key) const
{
    return document_.IsNumber();
}

bool GenericJsonParser::IsDouble(const std::string &key) const
{
    return document_.IsDouble();
}

bool GenericJsonParser::IsBool(const std::string &key) const
{
    return document_.IsBool();
}

bool GenericJsonParser::IsString(const std::string &key) const
{
    return document_.IsString();
}
