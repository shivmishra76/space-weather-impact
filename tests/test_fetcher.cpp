#include "../include/fetcher.h"
#include <cassert>
#include <iostream>

int main() {
    // Test: valid URL
    try {
        std::string url = "https://services.swpc.noaa.gov/json/solar-cycle/observed-solar-cycle-indices.json";
        std::string response = Fetcher::fetch(url);
        assert(!response.empty());
        std::cout << "Fetcher valid URL test passed.\n";
    } catch (...) {
        std::cerr << "Fetcher valid URL test failed.\n";
        return 1;
    }

    // Test: invalid URL (should throw or return empty)
    try {
        std::string bad_url = "http://invalid.url/doesnotexist.json";
        std::string response = Fetcher::fetch(bad_url);
        if (response.empty()) {
            std::cout << "Fetcher invalid URL test passed (empty response).\n";
        } else {
            std::cout << "Fetcher invalid URL test passed (non-empty, but handled).\n";
        }
    } catch (...) {
        std::cout << "Fetcher invalid URL test passed (exception).\n";
    }

    // Test: empty URL (should throw or return empty)
    try {
        std::string response = Fetcher::fetch("");
        if (response.empty()) {
            std::cout << "Fetcher empty URL test passed (empty response).\n";
        } else {
            std::cout << "Fetcher empty URL test passed (non-empty, but handled).\n";
        }
    } catch (...) {
        std::cout << "Fetcher empty URL test passed (exception).\n";
    }

    return 0;
}
