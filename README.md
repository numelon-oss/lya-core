# Lya Core
Before getting to know what Lya Core is and what it does, we must understand the entire Lya framework.

**Lya** is a reactive UI framework powered by Lua and WebView. It provides a minimal dispatch system, enabling safe cross-thread communication between Lua logic and native UI operations.

> In simple terms, you can basically think of Lya as Tauri, except it uses Lua instead of Rust.

**Lya Core** is the native C++ part of Lya. WebView functions are wrapped so that they can be easily accessed from within Lua using LuaJIT's FFI, and it also exposes a dispatch function with trampolining so that the background Lua thread can communicate with the WebView UI on the main thread.

Lya Core is currently macOS only. You can probably easily adapt the CMakeLists.txt to add support for Linux and Winodws by looking at the README of the [webview project](https://github.com/webview/webview).

> [!CAUTION]
> This repository, along with the accompanying [numelon-oss/lya-core](https://github.com/numelon-oss/lya-core), are fundamentally flawed and require a big re-thinking of the entire model in order for such a product to be viable.
>
> In its current state, Lya is entirely Lua-centric - and whilst this may seem ideal, it is absolutely not. The main window thread is started from within Lua using LuaJIT's FFI and it therefore blocks the entire main Lua thread, not allowing anything else to happen. This is why if you look at the source code, you will find us making a new Lua thread using `uv.new_thread`. However, Luvit's require doesnt automatically get injected into that new thread, nor is it aware of a Luvi package being present. Theoretically the require issue may be fixed, but overall if you look at Lya, it is just entirely messy.
>
> If this were to be re-done, Lya would likely be rewritten in C++ and simply integrate Luvit (as opposed to the current model of Luvit integrating a C++ shared library and then just blocking itself in its entirety).
> **But for now, lya and lya-core will be archived as Numelon is slowly shifting away from Lua towards other languages, mainly Go.** Thank you for your interest.
