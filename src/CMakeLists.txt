cmake_minimum_required(VERSION 3.15)
project(TrayApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_executable(TrayApp
        WIN32
        main.cpp
        resource.rc
        Config.cpp
        TrayAppWindow.cpp
        TrayIcon.cpp
        TrayMenu.cpp
        Autostart.cpp
        Version.cpp
        Hotkeys.cpp
        Resolution.cpp
        About.cpp
        About.rc
)

set_property(TARGET TrayApp PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_compile_definitions(TrayApp
        PRIVATE
        "_UNICODE"
        "UNICODE"
)

target_link_libraries(TrayApp PRIVATE shell32 shlwapi version)
