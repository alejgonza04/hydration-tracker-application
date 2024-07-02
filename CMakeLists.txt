cmake_minimum_required(VERSION 3.27)
project(waterTrackerProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(waterTrackerProject main.cpp
        WelcomeWindow.h
        ApplicationWindow.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include/SFML)
target_link_libraries(waterTrackerProject sfml-system sfml-window sfml-graphics sfml-audio)
