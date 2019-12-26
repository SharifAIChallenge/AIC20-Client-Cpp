cmake_minimum_required (VERSION 3.1)

IF(APPLE)
    SET(CMAKE_C_COMPILER clang)
    SET(CMAKE_CXX_COMPILER clang++)
ENDIF()

project (aic20-client-cpp
        LANGUAGES CXX)

add_subdirectory (client)
#add_subdirectory (jsoncpp EXCLUDE_FROM_ALL)
