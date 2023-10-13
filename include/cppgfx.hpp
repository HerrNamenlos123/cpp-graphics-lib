
#ifndef CPP_GRAPHICS_LIB_CPPGFX_HPP
#define CPP_GRAPHICS_LIB_CPPGFX_HPP

namespace cppgfx {

    class App {
    public:
        App();
        ~App();

        bool setup();

        void update();

        // Do not call this function manually
        void run();
    };

}

#endif //CPP_GRAPHICS_LIB_CPPGFX_HPP
