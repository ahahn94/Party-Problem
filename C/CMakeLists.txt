cmake_minimum_required(VERSION 3.10)
project(C C)

set(CMAKE_C_STANDARD 11)

include(FindPkgConfig)
pkg_check_modules(GLIB glib-2.0 REQUIRED)
include_directories(${GLIB_INCLUDE_DIRS})

add_executable(C main.c main.h guest.c guest.h)

target_link_libraries(${PROJECT_NAME} ${GLIB_LIBRARIES})