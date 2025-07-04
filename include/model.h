#pragma once
#include <nlohmann/json.hpp>
#include <string>

class Model {
public:
    static double calculateAtmosphericDrag(const nlohmann::json& spaceWeatherData, double satelliteArea, double satelliteMass);
    static double calculateCommDegradation(const nlohmann::json& spaceWeatherData);
};
