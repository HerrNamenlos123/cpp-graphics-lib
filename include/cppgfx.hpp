
#ifndef CPP_GRAPHICS_LIB_CPPGFX_HPP
#define CPP_GRAPHICS_LIB_CPPGFX_HPP

#include "SFML/Graphics.hpp"

namespace cppgfx {

    class App {
    public:
        App();
        ~App();

        sf::RenderWindow window;
        bool darkTitleBar = true;
        uint32_t width = 800;
        uint32_t height = 600;
        std::string title = "My cppgfx application";



        // These functions are supposed to be overridden by the user
        virtual void setup() = 0;
        virtual void update() = 0;

        virtual bool onWindowClose() { return true; }

        // API
        void size(int width, int height);
        void setTitle(const std::string& title);
        void close();

        // Do not call this function manually
        void run();

    private:
        App(const App&) = delete;
        App& operator=(const App&) = delete;

        sf::Color m_defaultBackgroundColor = sf::Color(40, 40, 40);
        bool m_isDarkTitleBar = false;
    };

}

#endif //CPP_GRAPHICS_LIB_CPPGFX_HPP
