cmake_minimum_required(VERSION 3.25)

project(Khat)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(KhatServer)
add_subdirectory(KhatClient)
add_subdirectory(KtLogger)
add_subdirectory(Submodules/DArgumentParser)
