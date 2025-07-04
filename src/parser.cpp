#include "parser.h"
#include <nlohmann/json.hpp>
#include <stdexcept>

nlohmann::json Parser::parse(const std::string& jsonStr) {
    try {
        return nlohmann::json::parse(jsonStr);
    } catch (const nlohmann::json::parse_error& e) {
        throw std::runtime_error(e.what());
    }
}
