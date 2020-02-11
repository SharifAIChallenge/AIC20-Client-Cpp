cmake_minimum_required (VERSION 3.1)

IF(UNIX)
    SET(CMAKE_C_COMPILER clang)
    SET(CMAKE_CXX_COMPILER clang++)
ENDIF()

project (aic20-client-cpp
        LANGUAGES CXX)

add_subdirectory (client)
