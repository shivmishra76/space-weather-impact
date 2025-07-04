#include "model.h"
#include <nlohmann/json.hpp>
#include <stdexcept>

// Example: Use F10.7 solar flux and Kp index for drag
// These are placeholder formulas for demonstration

double Model::calculateAtmosphericDrag(const nlohmann::json& data, double area, double mass) {
    double f107 = data.value("f107", 150.0);
    double kp = data.value("kp", 2.0);
    double drag = (f107 * 1e-6 + kp * 1e-3) * area / mass;
    return drag;
}

double Model::calculateCommDegradation(const nlohmann::json& data) {
    double xray = data.value("xray", 1.0);
    double degradation = xray * 0.1; // Placeholder
    return degradation;
}
