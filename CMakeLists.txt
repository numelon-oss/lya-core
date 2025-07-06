cmake_minimum_required(VERSION 3.30)
project(lya_core)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        webview
        GIT_REPOSITORY https://github.com/webview/webview
#        GIT_TAG 0.12.0
)
# NOTE: DO NOT USE GIT TAG 0.12.0, IT IS BROKEN!
# it took an hour to figure out why including tag 0.12.0 was catastrophic whereas including core/webview/webview.h from current worked
FetchContent_MakeAvailable(webview)

add_library(lya_core SHARED main.cpp)
target_link_libraries(lya_core PRIVATE webview::core)

if (APPLE)
    target_link_libraries(lya_core PRIVATE "-framework WebKit")

    # we dont really need this because luajit already has a dynamic linker for us
    target_link_libraries(lya_core PRIVATE dl)
endif ()