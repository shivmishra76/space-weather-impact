FROM ubuntu:24.04

# Install build tools and dependencies
RUN apt-get update && \
    apt-get install -y build-essential cmake curl libcurl4-openssl-dev git && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Install nlohmann/json (header-only)
RUN git clone --depth 1 https://github.com/nlohmann/json.git /tmp/json && \
    mkdir -p /usr/local/include/nlohmann && \
    cp /tmp/json/single_include/nlohmann/json.hpp /usr/local/include/nlohmann/json.hpp && \
    rm -rf /tmp/json

WORKDIR /workspace
COPY . /workspace

RUN mkdir -p build && cd build && cmake .. && make

CMD ["/bin/bash"]
