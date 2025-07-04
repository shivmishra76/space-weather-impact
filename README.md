# space-weather-impact

A C++ project to fetch real-time space weather data from NOAA APIs, parse JSON responses, and model the impact of space weather on satellites (e.g., atmospheric drag, communication degradation).

## Features
- Fetches data using libcurl
- Parses JSON with nlohmann/json
- Modular code: fetcher, parser, model
- CLI for querying solar indices and satellite impact
- Unit tests for each module

## Build

```
mkdir build && cd build
cmake ..
make
```

## Run

```
./space-weather-impact solar-indices
./space-weather-impact satellite-impact
```

## Test

```
cd build
ctest
```

## Docker Usage

Build the image and start a shell in the container:

```
docker compose build
docker compose run --rm space-weather-impact
```

Inside the container, you can run:

```
cd build
./space-weather-impact solar-indices
./space-weather-impact satellite-impact
ctest
```

This ensures all dependencies are available and builds/tests run in a consistent environment.
