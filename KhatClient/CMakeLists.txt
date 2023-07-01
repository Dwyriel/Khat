cmake_minimum_required(VERSION 3.25)

project(KhatClient VERSION 0.1.0 LANGUAGES CXX)
configure_file(../SharedFiles/cmake_config.h.in cmake_config.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        Source/MainWindow/MainWindow.cpp
        Source/MainWindow/MainWindow.h)

add_executable(KhatClient ${PROJECT_SOURCES})

IF (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(KhatClient PROPERTIES BUILD_RPATH_USE_ORIGIN TRUE)
ELSE ()
    set_target_properties(KhatClient PROPERTIES
            BUILD_WITH_INSTALL_RPATH TRUE
            LINK_FLAGS "-Wl,-rpath,$ORIGIN/")
ENDIF (CMAKE_BUILD_TYPE MATCHES Debug)

target_include_directories(KhatClient PRIVATE "../SharedFiles" "../KtLogger" ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(KhatClient KtLogger Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)