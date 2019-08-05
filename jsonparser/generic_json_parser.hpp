#ifndef GENERIC_JSON_PARSER_HPP
#define GENERIC_JSON_PARSER_HPP

#include <string>

#include "rapidjson/document.h"

class GenericJsonParser
{
    public:
        GenericJsonParser(const std::string &file);
        ~GenericJsonParser() = default;
        GenericJsonParser(const GenericJsonParser&) = delete;
        GenericJsonParser& operator=(const GenericJsonParser&) = delete;

        bool Parse();
        bool ValidateJson(const std::string &str);
        bool HasMember(const std::string &key) const;
        bool IsArray(const std::string &key) const;
        bool IsNumber(const std::string &key) const;
        bool IsDouble(const std::string &key) const;
        bool IsBool(const std::string &key) const;
        bool IsString(const std::string &key) const;
    private:
        bool FileExists(const std::string &file) const;

        std::string file_name_{""};
        bool is_file_exists_{false};
        rapidjson::Document document_;

};

#endif // GENERIC_JSON_PARSER_HPP
