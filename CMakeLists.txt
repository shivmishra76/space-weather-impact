cmake_minimum_required(VERSION 3.10)
project(space-weather-impact)

set(CMAKE_CXX_STANDARD 17)

# Add source files
add_executable(space-weather-impact
    src/main.cpp
    src/fetcher.cpp
    src/parser.cpp
    src/model.cpp
    src/config.cpp
    src/webhook.cpp
)

# Include directories
include_directories(include)

# Find and link libcurl
find_package(CURL REQUIRED)
target_link_libraries(space-weather-impact PRIVATE CURL::libcurl)

# nlohmann/json is header-only, so just add include
find_path(NLOHMANN_JSON_INCLUDE_DIR nlohmann/json.hpp)
if(NLOHMANN_JSON_INCLUDE_DIR)
    target_include_directories(space-weather-impact PRIVATE ${NLOHMANN_JSON_INCLUDE_DIR})
endif()

# Tests
enable_testing()
add_subdirectory(tests)
