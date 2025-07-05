#pragma once
#include <nlohmann/json.hpp>
#include <string>

class Model {
public:
    static double calculateAtmosphericDrag(const nlohmann::json& spaceWeatherData, double satelliteArea, double satelliteMass);
    static double calculateCommDegradation(const nlohmann::json& spaceWeatherData);
    static double estimateOrbitDecay(const nlohmann::json& spaceWeatherData, double satelliteArea, double satelliteMass, double altitude_km);
    static double estimateSolarPanelDegradation(const nlohmann::json& spaceWeatherData);
    static double estimateRadiationDose(const nlohmann::json& spaceWeatherData, double altitude_km);
    // Estimate Single Event Upset (SEU) rate
    static double estimateSEURate(const nlohmann::json& data, double area, double duration_s);
};
