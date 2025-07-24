#include <iostream>
#include <string>
#include <fstream>
#include "fetcher.h"
#include "parser.h"
#include "model.h"
#include "config.h"
#include "webhook.h"

void printUsage() {
    std::cout << "Usage: space-weather-impact <command> [options]\n";
    std::cout << "Commands:\n";
    std::cout << "  solar-indices         Query current solar indices\n";
    std::cout << "  satellite-impact      Calculate satellite impact metrics\n";
}

int main(int argc, char* argv[]) {
    // Load config (webhooks)
    Config config = loadConfig("config.json");
    if (argc < 2) {
        printUsage();
        return 1;
    }
    std::string command = argv[1];
    try {
        if (command == "solar-indices") {
            std::string url = "https://services.swpc.noaa.gov/json/solar-cycle/observed-solar-cycle-indices.json";
            std::string response = Fetcher::fetch(url);
            auto json = Parser::parse(response);
            std::cout << "Current Solar Indices (latest):\n";
            if (!json.is_array() || json.empty()) {
                std::cerr << "No data available.\n";
                return 1;
            }
            auto latest = json.back();
            // Print key indices
            double f107 = latest.value("f107", -1.0);
            double sunspot = latest.value("ssn", -1.0);
            double xray = latest.value("xray", -1.0);
            double kp = latest.value("kp", -1.0);
            std::cout << "  F10.7: " << f107 << "\n";
            std::cout << "  Sunspot Number: " << sunspot << "\n";
            std::cout << "  X-ray Flux: " << xray << "\n";
            std::cout << "  Kp Index: " << kp << "\n";

            // Event detection: highlight if X-ray flux or Kp index is high
            if (xray > -2) {
                std::cout << "  [Event] Solar flare detected (X-ray flux > 1e-4 W/m^2)!\n";
                // Send webhook for solar flare
                nlohmann::json payload = {
                    {"event", "solar_flare"},
                    {"xray_flux", xray},
                    {"timestamp", latest.value("time-tag", "")}
                };
                for (const auto& wh : config.webhooks) {
                    if (std::find(wh.events.begin(), wh.events.end(), "solar_flare") != wh.events.end()) {
                        try { sendWebhook(wh.url, payload); } catch (...) { /* ignore errors */ }
                    }
                }
            }
            if (kp >= 5.0) {
                std::cout << "  [Event] Geomagnetic storm conditions (Kp >= 5)!\n";
                // Send webhook for geomagnetic storm
                nlohmann::json payload = {
                    {"event", "geomagnetic_storm"},
                    {"kp_index", kp},
                    {"timestamp", latest.value("time-tag", "")}
                };
                for (const auto& wh : config.webhooks) {
                    if (std::find(wh.events.begin(), wh.events.end(), "geomagnetic_storm") != wh.events.end()) {
                        try { sendWebhook(wh.url, payload); } catch (...) { /* ignore errors */ }
                    }
                }
            }

            // Prepare data for plotting (F10.7 and Kp over time)
            std::ofstream plotfile("solar_indices_plot.csv");
            plotfile << "date,f107,kp\n";
            for (const auto& entry : json) {
                std::string date = entry.value("time-tag", "");
                double f = entry.value("f107", -1.0);
                double k = entry.value("kp", -1.0);
                plotfile << date << "," << f << "," << k << "\n";
            }
            plotfile.close();
            std::cout << "\nSaved F10.7 and Kp index history to solar_indices_plot.csv\n";
            std::cout << "You can plot this data with: gnuplot -e \"set datafile separator ','; plot 'solar_indices_plot.csv' using 0:2 with lines title 'F10.7', '' using 0:3 with lines title 'Kp'\"\n";
        } else if (command == "satellite-impact") {
            std::string url = "https://services.swpc.noaa.gov/json/solar-cycle/observed-solar-cycle-indices.json";
            std::string response = Fetcher::fetch(url);
            auto json = Parser::parse(response);
            // Use the latest entry
            auto latest = json.back();
            double area = 10.0; // m^2, example
            double mass = 1000.0; // kg, example
            double altitude = 400.0; // km, example (ISS)
            // Add altitude to the JSON for advanced drag model
            nlohmann::json latest_with_alt = latest;
            latest_with_alt["altitude_km"] = altitude;
            double drag_simple = Model::calculateAtmosphericDrag(latest, area, mass);
            double drag_advanced = Model::calculateAtmosphericDragAdvanced(latest_with_alt, area, mass);
            double comm = Model::calculateCommDegradation(latest);
            double decay = Model::estimateOrbitDecay(latest, area, mass, altitude);
            double panelDeg = Model::estimateSolarPanelDegradation(latest);
            double radDose = Model::estimateRadiationDose(latest, altitude);
            // Example SEU rate calculation
            // Assume sensitive area = 1 cm^2, duration = 1 day
            double seu_area = 1.0; // cm^2
            double seu_duration = 86400.0; // seconds in a day
            double seu_rate = Model::estimateSEURate(latest, seu_area, seu_duration);
            std::cout << "Atmospheric Drag (Simple): " << drag_simple << "\n";
            std::cout << "Atmospheric Drag (Advanced): " << drag_advanced << " m/s^2\n";
            std::cout << "Comm Degradation: " << comm << "\n";
            std::cout << "Estimated Orbit Decay Rate: " << decay << " km/day\n";
            std::cout << "Solar Panel Degradation: " << panelDeg << " %/year\n";
            std::cout << "Radiation Dose: " << radDose << " mSv/day\n";
            std::cout << "Estimated SEU Events (1 cm^2, 1 day): " << seu_rate << "\n";
        } else {
            printUsage();
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
