#include "../include/parser.h"
#include <cassert>
#include <iostream>

int main() {
    // Test: valid JSON
    std::string sample = R"({\"f107\": 150.0, \"kp\": 2.0, \"xray\": 1.0})";
    try {
        auto json = Parser::parse(sample);
        assert(json["f107"] == 150.0);
        std::cout << "Parser valid JSON test passed.\n";
    } catch (...) {
        std::cerr << "Parser valid JSON test failed.\n";
        return 1;
    }

    // Test: missing key
    std::string missing_key = R"({\"kp\": 3.0})";
    try {
        auto json = Parser::parse(missing_key);
        assert(json["kp"] == 3.0);
        // Should not throw, but missing keys should be handled by user code
        std::cout << "Parser missing key test passed.\n";
    } catch (...) {
        std::cerr << "Parser missing key test failed.\n";
        return 1;
    }

    // Test: invalid JSON
    std::string invalid_json = R"({\"f107\": 150.0, )";
    try {
        auto json = Parser::parse(invalid_json);
        std::cerr << "Parser invalid JSON test failed (no exception).\n";
        return 1;
    } catch (...) {
        std::cout << "Parser invalid JSON test passed.\n";
    }

    // Test: extra/unexpected key
    std::string extra_key = R"({\"f107\": 100.0, \"kp\": 1.0, \"extra\": 42})";
    try {
        auto json = Parser::parse(extra_key);
        assert(json["extra"] == 42);
        std::cout << "Parser extra key test passed.\n";
    } catch (...) {
        std::cerr << "Parser extra key test failed.\n";
        return 1;
    }

    // Test: wrong type
    std::string wrong_type = R"({\"f107\": \"not_a_number\"})";
    try {
        auto json = Parser::parse(wrong_type);
        // Accessing as double may throw in user code, but parsing should succeed
        assert(json["f107"].is_string());
        std::cout << "Parser wrong type test passed.\n";
    } catch (...) {
        std::cerr << "Parser wrong type test failed.\n";
        return 1;
    }

    return 0;
}
