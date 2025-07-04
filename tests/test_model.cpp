#include "../include/model.h"
#include <cassert>
#include <iostream>
#include <nlohmann/json.hpp>

int main() {
    nlohmann::json data = { {"f107", 150.0}, {"kp", 2.0}, {"xray", 1.0} };
    double drag = Model::calculateAtmosphericDrag(data, 10.0, 1000.0);
    double comm = Model::calculateCommDegradation(data);
    assert(drag > 0);
    assert(comm > 0);
    std::cout << "Model test passed.\n";
    return 0;
}
