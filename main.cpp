#include <mutex>
#include <queue>

#include "webview/webview.h"

static webview_t w = nullptr;

enum MsgType {
    EVAL,
    SET_TITLE,

    // in the future might add:
    // set icon, resize, quit? (probably can just do os.exit from lua)
    // etc.
};

struct LuxMessage {
    MsgType type;
    std::string payload;
};

// thread safe msg queue
static std::queue<LuxMessage> queue;
static std::mutex queue_mutex;

extern "C" {
    // webview instance created by lux init, etc.
    void lux_create(const bool debug) {
        // TODO: allow multiple webview instances (multiple windows)
        // instead of just a single window
        // that will be something for the future
        w = webview_create(debug, nullptr);
    }

    void lux_navigate(const char* url) {
        webview_navigate(w, url);
    }

    // main blocking c loop ran by lux.run()
    void lux_run() {
        webview_run(w);
    }
    // TODO: maybe just call lux_run() immediately after lux.main()?






    // we don't actually use dispatch_trampoline from within lua with ffi
    void dispatch_trampoline(const webview_t w, void* idk) {
        std::lock_guard lock(queue_mutex);

        while (!queue.empty()) {
            LuxMessage msg = queue.front();
            queue.pop();

            switch (msg.type) {
                case SET_TITLE:
                    webview_set_title(w, msg.payload.c_str());
                    break;

                case EVAL:
                    webview_eval(w, msg.payload.c_str());
                    break;

                // default:
                //     // could do std::cout etc but is there even a point
                //     break;
            }
        }
    }

    // TODO: we will likely run into limitations with our single payload lol
    // in the future we might have to expand this
    void lux_dispatch(const MsgType type, const char* payload) {
        std::lock_guard lock(queue_mutex);
        queue.push({ type, std::string(payload) });

        webview_dispatch(w, dispatch_trampoline, nullptr);
    }
}