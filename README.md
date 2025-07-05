# space-weather-impact

A C++ project to fetch real-time space weather data from NOAA APIs, parse JSON responses, and model the impact of space weather on satellites (e.g., atmospheric drag, communication degradation).

## Features
* Fetches data using libcurl
* Parses JSON with nlohmann/json
* Modular code: fetcher, parser, model
* CLI for querying solar indices and satellite impact
* Event detection for solar flares and geomagnetic storms
* Exports solar index history (F10.7, Kp) to CSV for plotting
* Estimates advanced satellite effects (e.g., SEU rate)
* Unit tests for each module

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

### Solar Indices Command

```
./space-weather-impact solar-indices
```
* Prints the latest F10.7, sunspot number, X-ray flux, and Kp index
* Detects and highlights solar flare and geomagnetic storm events
* Saves F10.7 and Kp index history to `solar_indices_plot.csv` for plotting
* Example plot command (using gnuplot):
  ```
  gnuplot -e "set datafile separator ','; plot 'solar_indices_plot.csv' using 0:2 with lines title 'F10.7', '' using 0:3 with lines title 'Kp'"
  ```

### Satellite Impact Command

```
./space-weather-impact satellite-impact
```
* Calculates atmospheric drag, comm degradation, orbit decay, solar panel degradation, radiation dose, and SEU rate using the latest indices

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
