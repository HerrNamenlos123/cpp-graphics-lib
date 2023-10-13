
#include "cppgfx.hpp"
#include "win32.hpp"

namespace cppgfx {

    App::App() {

    }

    App::~App() {

    }

    void App::size(int width, int height) {
        this->width = width;
        this->height = height;
        window.setSize(sf::Vector2u(width, height));
    }

    void App::setTitle(const std::string& title) {
        this->title = title;
        window.setTitle(title);
    }

    void App::close() {
        window.close();
    }

    void App::run() {
        setup();
        window.create(sf::VideoMode(width, height), title);
        window.setFramerateLimit(60);

        while (window.isOpen()) {

            // Handle dark title bar
            if (darkTitleBar != m_isDarkTitleBar) {
                EnableDarkTitleBar(window.getSystemHandle(), darkTitleBar);
                m_isDarkTitleBar = darkTitleBar;
            }

            // Handle events
            sf::Event event {};
            while (window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        if (onWindowClose()) {
                            window.close();
                        }
                        break;
                    case sf::Event::Resized:
                        width = event.size.width;
                        height = event.size.height;
                        break;
                    default:
                        break;
                }
            }

            // Call the user's update function
            window.clear(m_defaultBackgroundColor);
            update();

            // Display the window
            window.display();
        }
    }

} // namespace cppgfx