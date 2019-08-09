#ifndef GENERIC_JSON_PARSER_HPP
#define GENERIC_JSON_PARSER_HPP

#include <string>
#include <vector>

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
        bool ArrayElements(const std::string &key) const;
        std::uint32_t ArraySize(const std::string &key) const;
        bool GetElement(const std::vector<std::string> vec) const;
        double GetDoubleValue(const std::string &key, const rapidjson::Value& val) const;
        std::vector<double> GetPoints(const std::vector<std::string> &keys,  const rapidjson::Value &points) const;
        std::vector<std::vector<double>> GetAllPoints(const std::vector<std::string> &start_end_points, int index,  const rapidjson::Value &poly_line) const;
    private:
        bool FileExists(const std::string &file) const;

        std::string file_name_{""};
        bool is_file_exists_{false};
        rapidjson::Document document_;

};

#endif // GENERIC_JSON_PARSER_HPP
