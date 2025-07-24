#pragma once
#include <string>
#include <vector>

struct WebhookConfig {
    std::string url;
    std::vector<std::string> events;
};

struct Config {
    std::vector<WebhookConfig> webhooks;
};

Config loadConfig(const std::string& filename); 