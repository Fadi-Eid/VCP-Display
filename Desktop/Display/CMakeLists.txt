cmake_minimum_required(VERSION 3.10)
project(vcp_display)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

# Find SDL2 first
find_package(SDL2 REQUIRED)

# Define the executable
add_executable(vcp_display
    src/main.cpp
    src/display.cpp
    src/communication.cpp
)

# Include SDL2 headers + project headers
target_include_directories(vcp_display PRIVATE
    ${SDL2_INCLUDE_DIRS}
    include
)

# Link SDL2 libraries
target_link_libraries(vcp_display PRIVATE ${SDL2_LIBRARIES})
