#include "../include/model.h"
#include <cassert>
#include <iostream>
#include <nlohmann/json.hpp>

int main() {
    // Test: typical values
    nlohmann::json data = { {"f107", 150.0}, {"kp", 2.0}, {"xray", 1.0} };
    double drag = Model::calculateAtmosphericDrag(data, 10.0, 1000.0);
    double comm = Model::calculateCommDegradation(data);
    assert(drag > 0);
    assert(comm > 0);
    std::cout << "Model typical values test passed.\n";

    // Test: high Kp (geomagnetic storm)
    nlohmann::json storm = { {"f107", 120.0}, {"kp", 7.0}, {"xray", 0.5} };
    double drag_storm = Model::calculateAtmosphericDrag(storm, 10.0, 1000.0);
    assert(drag_storm > drag); // Drag should increase with Kp
    std::cout << "Model high Kp test passed.\n";

    // Test: missing keys (should handle gracefully)
    nlohmann::json missing = { {"f107", 100.0} };
    try {
        double drag_missing = Model::calculateAtmosphericDrag(missing, 10.0, 1000.0);
        std::cout << "Model missing key test passed.\n";
    } catch (...) {
        std::cerr << "Model missing key test failed.\n";
        return 1;
    }

    // Test: edge case (zero area)
    double drag_zero = Model::calculateAtmosphericDrag(data, 0.0, 1000.0);
    assert(drag_zero == 0.0);
    std::cout << "Model zero area test passed.\n";

    // Test: negative/invalid input (should not crash)
    try {
        double drag_neg = Model::calculateAtmosphericDrag(data, -5.0, 1000.0);
        std::cout << "Model negative area test passed.\n";
    } catch (...) {
        std::cerr << "Model negative area test failed.\n";
        return 1;
    }

    // Test: communication degradation with high X-ray
    nlohmann::json flare = { {"f107", 150.0}, {"kp", 2.0}, {"xray", 1e-3} };
    double comm_flare = Model::calculateCommDegradation(flare);
    assert(comm_flare > comm);
    std::cout << "Model comm degradation flare test passed.\n";

    return 0;
}
