# .devcontainer/Dockerfile
FROM vcp-diplay-desktop-base:latest

USER root

# RUN apt-get update && apt-get install -y --no-install-recommends \
#         nano \
#         pkg-config \
#         minicom

# RUN pip install pyserial

RUN git clone --depth=1 https://github.com/gbmhunter/CppLinuxSerial.git \
    && cd CppLinuxSerial \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make \
    && make install

# Use the same user as base
USER devuser
WORKDIR /home/devuser/workspace