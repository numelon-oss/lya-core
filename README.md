# Lya Core
Before getting to know what Lya Core is and what it does, we must understand the entire Lya framework.

**Lya** is a reactive UI framework powered by Lua and WebView. It provides a minimal dispatch system, enabling safe cross-thread communication between Lua logic and native UI operations.

> In simple terms, you can basically think of Lya as Tauri, except it uses Lua instead of Rust.

**Lya Core** is the native C++ part of Lya. WebView functions are wrapped so that they can be easily accessed from within Lua using LuaJIT's FFI, and it also exposes a dispatch function with trampolining so that the background Lua thread can communicate with the WebView UI on the main thread.

Lya Core is currently macOS only. You can probably easily adapt the CMakeLists.txt to add support for Linux and Winodws by looking at the README of the [webview project](https://github.com/webview/webview).

