#include <iostream>
#include <string>
#include "fetcher.h"
#include "parser.h"
#include "model.h"

void printUsage() {
    std::cout << "Usage: space-weather-impact <command> [options]\n";
    std::cout << "Commands:\n";
    std::cout << "  solar-indices         Query current solar indices\n";
    std::cout << "  satellite-impact      Calculate satellite impact metrics\n";
}

int main(int argc, char* argv[]) {
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
            std::cout << "Current Solar Indices:\n";
            std::cout << json.dump(2) << std::endl;
        } else if (command == "satellite-impact") {
            std::string url = "https://services.swpc.noaa.gov/json/solar-cycle/observed-solar-cycle-indices.json";
            std::string response = Fetcher::fetch(url);
            auto json = Parser::parse(response);
            // Use the latest entry
            auto latest = json.back();
            double area = 10.0; // m^2, example
            double mass = 1000.0; // kg, example
            double drag = Model::calculateAtmosphericDrag(latest, area, mass);
            double comm = Model::calculateCommDegradation(latest);
            std::cout << "Atmospheric Drag: " << drag << "\n";
            std::cout << "Comm Degradation: " << comm << "\n";
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
