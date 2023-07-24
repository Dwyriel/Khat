cmake_minimum_required(VERSION 3.25)

project(KtLogger VERSION 0.2.0 LANGUAGES CXX)
configure_file(../SharedFiles/cmake_config.h.in cmake_config.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(PROJECT_SOURCES
        KtLogger.cpp
        )

add_library(KtLogger SHARED ${PROJECT_SOURCES})

target_include_directories(KtLogger PRIVATE "../SharedFiles" ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(KtLogger Qt${QT_VERSION_MAJOR}::Core)
