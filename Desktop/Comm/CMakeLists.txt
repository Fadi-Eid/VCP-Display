cmake_minimum_required(VERSION 3.10)
project(serial_comm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)


include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# Define the executable
add_executable(serial_comm
    src/main.cpp
)

# Link CppLinuxSerial library
target_link_libraries(serial_comm CppLinuxSerial)
