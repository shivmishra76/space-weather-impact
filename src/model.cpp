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

// Advanced drag model using exponential atmosphere and physics-based drag equation
// Inputs:
//   data: JSON with keys "altitude_km", "f107", "kp" (optional)
//   area: cross-sectional area (m^2)
//   mass: satellite mass (kg)
// Returns: drag acceleration (m/s^2)
double Model::calculateAtmosphericDragAdvanced(const nlohmann::json& data, double area, double mass) {
    // Constants
    constexpr double R0 = 6371.0; // Earth radius (km)
    constexpr double rho0 = 4e-12; // Reference density at 400 km (kg/m^3)
    constexpr double H = 60.0;     // Scale height (km)
    constexpr double Cd = 2.2;     // Drag coefficient (typical)
    constexpr double v = 7700.0;   // Orbital velocity (m/s, LEO)

    double altitude = data.value("altitude_km", 400.0);
    double f107 = data.value("f107", 150.0);
    double kp = data.value("kp", 2.0);

    // Adjust scale height and density for solar activity (simple empirical fit)
    double H_mod = H + 0.01 * (f107 - 150.0) + 0.5 * (kp - 2.0);
    double rho = rho0 * std::exp(-(altitude - 400.0) / H_mod);

    // Drag force: F = 0.5 * Cd * A * rho * v^2
    double F_drag = 0.5 * Cd * area * rho * v * v;
    // Acceleration: a = F/m
    double a_drag = F_drag / mass;
    return a_drag;
}

double Model::calculateCommDegradation(const nlohmann::json& data) {
    double xray = data.value("xray", 1.0);
    double degradation = xray * 0.1; // Placeholder
    return degradation;
}

double Model::estimateOrbitDecay(const nlohmann::json& data, double area, double mass, double altitude_km) {
    // Simplified: decay rate increases with drag, decreases with altitude
    double drag = calculateAtmosphericDrag(data, area, mass);
    double baseDecay = 0.01; // km/day baseline
    double decay = baseDecay + drag * 10.0 / (altitude_km / 400.0); // 400km = ISS
    return decay;
}

double Model::estimateSolarPanelDegradation(const nlohmann::json& data) {
    // Placeholder: degradation increases with X-ray and solar flux
    double f107 = data.value("f107", 150.0);
    double xray = data.value("xray", 1.0);
    double degradation = 0.5 + 0.002 * (f107 - 100.0) + 0.05 * xray; // percent/year
    return degradation;
}

double Model::estimateRadiationDose(const nlohmann::json& data, double altitude_km) {
    // Placeholder: dose increases with altitude and Kp index
    double kp = data.value("kp", 2.0);
    double baseDose = 0.5; // mSv/day at 400km
    double dose = baseDose * (altitude_km / 400.0) * (1.0 + kp * 0.1);
    return dose;
}

// Estimate Single Event Upset (SEU) rate using a simplified model
// Inputs:
//   data: JSON with keys "proton_flux" (protons/cm^2/s), "LET_threshold" (MeV*cm^2/mg)
//   area: sensitive area in cm^2
//   duration_s: duration in seconds
// Returns: estimated number of SEUs
double Model::estimateSEURate(const nlohmann::json& data, double area, double duration_s) {
    // Default values if not provided
    double proton_flux = data.value("proton_flux", 1e2); // protons/cm^2/s
    double LET_threshold = data.value("LET_threshold", 10.0); // MeV*cm^2/mg
    // Simple model: SEU rate = proton_flux * area * duration * P(LET > threshold)
    // For demo, assume P(LET > threshold) ~ exp(-LET_threshold/20)
    double p_let = std::exp(-LET_threshold / 20.0);
    double seu_count = proton_flux * area * duration_s * p_let;
    return seu_count;
}
