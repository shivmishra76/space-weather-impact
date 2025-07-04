#include "../include/parser.h"
#include <cassert>
#include <iostream>

int main() {
    std::string sample = R"({\"f107\": 150.0, \"kp\": 2.0, \"xray\": 1.0})";
    try {
        auto json = Parser::parse(sample);
        assert(json["f107"] == 150.0);
        std::cout << "Parser test passed.\n";
    } catch (...) {
        std::cerr << "Parser test failed.\n";
        return 1;
    }
    return 0;
}
