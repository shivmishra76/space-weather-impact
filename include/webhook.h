#pragma once
#include <string>
#include <nlohmann/json.hpp>

void sendWebhook(const std::string& url, const nlohmann::json& payload); 