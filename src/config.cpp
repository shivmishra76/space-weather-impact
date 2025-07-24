#include "config.h"
#include <fstream>
#include <nlohmann/json.hpp>

Config loadConfig(const std::string& filename) {
    Config config;
    std::ifstream file(filename);
    if (!file) return config;
    nlohmann::json j;
    file >> j;
    if (j.contains("webhooks")) {
        for (const auto& wh : j["webhooks"]) {
            WebhookConfig w;
            w.url = wh.value("url", "");
            if (wh.contains("events")) {
                for (const auto& ev : wh["events"]) {
                    w.events.push_back(ev.get<std::string>());
                }
            }
            config.webhooks.push_back(w);
        }
    }
    return config;
} 