project(networld LANGUAGES C)
cmake_minimum_required(VERSION 3.10)

# Activate C99 standard:
SET(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra" )

# project configuration :
include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/src/includes)

# RayLib:
find_package(raylib 3.0 REQUIRED)
#set(raylib_VERBOSE 1)

add_executable(app-50NuancesDeCode src/program.c)
target_link_libraries(app-50NuancesDeCode raylib)

#without cmake package... 
#include_directories(${PROJECT_SOURCE_DIR}/raylib/src)
#link_directories(${PROJECT_SOURCE_DIR}/raylib)
#target_link_libraries(nw-viewer raylib GL m pthread dl rt X11)
