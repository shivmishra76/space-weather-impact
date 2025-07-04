#pragma once
#include <string>
#include <nlohmann/json.hpp>

class Parser {
public:
    static nlohmann::json parse(const std::string& jsonStr);
};
