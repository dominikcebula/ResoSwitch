cmake_minimum_required(VERSION 3.15)
project(TrayApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(TrayApp
        WIN32
        main.cpp
        TrayAppWindow.cpp
        TrayIcon.cpp
        TrayMenu.cpp
)

target_compile_definitions(TrayApp
        PRIVATE
        "_UNICODE"
        "UNICODE"
)

target_link_libraries(TrayApp PRIVATE shell32)
