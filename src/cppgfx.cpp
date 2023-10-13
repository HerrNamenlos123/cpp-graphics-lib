
#include "cppgfx.hpp"

namespace cppgfx {

    App::App() {

    }

    App::~App() {

    }

    void App::run() {
        if (!setup()) {
            return;
        }
        while (true) {
            update();
        }
    }

} // namespace cppgfx