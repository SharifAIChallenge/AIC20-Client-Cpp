cmake_minimum_required(VERSION 3.13)
find_package(nlohmann_json 3.2.0 REQUIRED)# installed from the github source code

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O0 -g")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2")

if (WIN32)
    set (CMAKE_EXE_LINKER_FLAGS "-static")
endif ()

file (GLOB_RECURSE Sources src/*)

add_executable (client ${Sources})

target_include_directories (client PRIVATE src/)

find_package(Threads REQUIRED)
#target_link_libraries (client jsoncpp_lib_static Threads::Threads)
target_link_libraries (client nlohmann_json::nlohmann_json Threads::Threads)

if (WIN32)
    target_link_libraries (client wsock32 ws2_32)
endif ()
