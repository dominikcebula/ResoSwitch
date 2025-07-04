cmake_minimum_required(VERSION 3.15)
project(TrayApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

foreach (flag_var
        CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_DEBUG)
    string(REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
endforeach ()

add_executable(TrayApp
        WIN32
        main.cpp
        Config.cpp
        TrayAppWindow.cpp
        TrayIcon.cpp
        TrayMenu.cpp
        Autostart.cpp
        Version.cpp
        resource.rc
)

target_compile_definitions(TrayApp
        PRIVATE
        "_UNICODE"
        "UNICODE"
)

target_link_libraries(TrayApp PRIVATE shell32 shlwapi version)
