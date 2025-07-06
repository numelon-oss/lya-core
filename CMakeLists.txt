cmake_minimum_required(VERSION 3.30)
project(lya_core)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        webview
        GIT_REPOSITORY https://github.com/webview/webview
        GIT_TAG 0.12.0
)
FetchContent_MakeAvailable(webview)

add_library(lya_core SHARED main.cpp)
target_link_libraries(lya_core PRIVATE webview::core)

if (APPLE)
    target_link_libraries(lya_core PRIVATE "-framework WebKit")
    target_link_libraries(lya_core PRIVATE dl)
endif ()