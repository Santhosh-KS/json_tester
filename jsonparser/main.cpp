#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "generic_json_parser.hpp"
#include "rapidjson/document.h"


int main()
{
#if 0
    //using namespace rapidjson;
    std::ifstream t("data/example_data.json");
    std::stringstream buffer;
    buffer << t.rdbuf();

    rapidjson::Document document;
    document.Parse(buffer.str().c_str());
#endif
    std::string file("data/example_data.json");
    GenericJsonParser parser(file);

    std::cout << (parser.Parse() ? " TRUE " : " FALSE ") << "\n";

#if 0
    std::vector<std::string> keys{"frames", "santhosh", "lane_orientation", "label_spec_version"};
    for(auto &key: keys)
    {
        std::cout << key.c_str() << " is " << (parser.HasMember(key)? "TRUE":"FALSE")<< "\n";
    }
#endif
    std::string key{"frames"};

    if (parser.HasMember(key))
    {
        parser.IsArray(key);
        std::cout << key.c_str() << " is " << (parser.HasMember(key)? "ARRAY ":"NOT AN ARRAY")<< "\n";

    }
    return 0;
}
