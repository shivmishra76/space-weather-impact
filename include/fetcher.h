#pragma once
#include <string>
#include <curl/curl.h>

class Fetcher {
public:
    static std::string fetch(const std::string& url);
};
