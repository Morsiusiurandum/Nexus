cmake_minimum_required(VERSION 3.24)
# Edit the BuildOptions.cmake file to change build time options
add_definitions(-DUNICODE -D_UNICODE)

include(BuildOptions.cmake)

project(${MAIN_PROJECT_NAME})

if (ENABLE_NOTIFICATION_ICON)
    add_compile_definitions(_ENABLE_NOTIFICATION_ICON)
endif ()

if (SINGLE_INSTANCE_ONLY)
    add_compile_definitions(_SINGLE_INSTANCE_ONLY)
endif ()

add_subdirectory(app)