cmake_minimum_required(VERSION 3.25)

project(KhatServer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Network Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network Concurrent)

set(PROJECT_SOURCES
        main.cpp
        Source/SignalHandler/SignalHandler.cpp
        Source/SignalHandler/SignalHandler.h
        Source/TcpServer/TcpServer.cpp
        Source/TcpServer/TcpServer.h)

add_executable(KhatServer ${PROJECT_SOURCES})

target_include_directories(KhatServer PRIVATE "../SharedFiles")
target_link_libraries(KhatServer Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Concurrent)

install(TARGETS KhatServer
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )
