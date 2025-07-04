# Design Documentation

## Overview
This project fetches real-time space weather data from NOAA APIs, parses the JSON response, and models the impact on satellites (e.g., atmospheric drag, communication degradation).

## Modules
- **Fetcher**: Handles HTTP requests using libcurl.
- **Parser**: Parses JSON using nlohmann/json.
- **Model**: Calculates satellite impact metrics.

## Extensibility
- Add new models by extending `model.cpp/h`.
- Add new data sources by updating `fetcher.cpp/h`.

## Error Handling
- All network and parsing errors are caught and reported.
