cmake_minimum_required(VERSION 3.24)

set(PROJECT_NAME ${WINDOWS_APP_NAME})

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)

add_compile_definitions(_UNICODE UNICODE)

# Uncomment the following line to add timeout to wait so that the
# registry handle can be released.  Not really needed and causes
# a very tiny bit of extra CPU to keep checking for exit condition.
#
#add_compile_definitions(_TIDY_TIMEOUT)

include_directories(include)
aux_source_directory(include inc)
add_executable(
        ${PROJECT_NAME}
        include/Resource.h
        resources/targetver.h
        resources/WindowsProject.rc
        ${inc}
        src/WindowsProject.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
target_link_options( ${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")