#include "../include/fetcher.h"
#include <cassert>
#include <iostream>

int main() {
    try {
        std::string url = "https://services.swpc.noaa.gov/json/solar-cycle/observed-solar-cycle-indices.json";
        std::string response = Fetcher::fetch(url);
        assert(!response.empty());
        std::cout << "Fetcher test passed.\n";
    } catch (...) {
        std::cerr << "Fetcher test failed.\n";
        return 1;
    }
    return 0;
}
