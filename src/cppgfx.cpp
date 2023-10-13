
#include "cppgfx.hpp"
#include "win32.hpp"

#include <chrono>

namespace cppgfx {

    App::App() {
        m_drawStyleStack.push_back(DrawStyle());
    }

    App::~App() {

    }




    // =======================================
    // =====        Graphics API      ========
    // =======================================

    void App::background(const sf::Color& color) {
        window.clear(color);
    }

    void App::background(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        window.clear(sf::Color(r, g, b, a));
    }

    void App::fill(const sf::Color& color) {
        m_drawStyleStack.back().m_fillColor = color;
    }

    void App::fill(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        m_drawStyleStack.back().m_fillColor = sf::Color(r, g, b, a);
    }

    void App::noFill() {
        m_drawStyleStack.back().m_fillColor = sf::Color::Transparent;
    }

    void App::stroke(const sf::Color& color) {
        m_drawStyleStack.back().m_strokeColor = color;
    }

    void App::stroke(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        m_drawStyleStack.back().m_strokeColor = sf::Color(r, g, b, a);
    }

    void App::noStroke() {
        m_drawStyleStack.back().m_strokeColor = sf::Color::Transparent;
    }

    void App::strokeWeight(float weight) {
        m_drawStyleStack.back().m_strokeWeight = weight;
    }

    void App::push() {
        m_drawStyleStack.push_back(m_drawStyleStack.back());
    }

    void App::pop() {
        if (m_drawStyleStack.size() <= 1) {
            throw std::runtime_error("Cannot pop any more style from the stack: Nothing to pop");
        }
        m_drawStyleStack.pop_back();
    }

    void App::line(float x1, float y1, float x2, float y2) {
        sf::RectangleShape line;
        line.setFillColor(m_drawStyleStack.back().m_strokeColor);
        line.setSize({ dist(x1, y1, x2, y2), m_drawStyleStack.back().m_strokeWeight });
        line.setOrigin({ 0, m_drawStyleStack.back().m_strokeWeight / 2.0f });
        line.setPosition({ x1, y1 });
        line.setRotation(degrees(atan2f(y2 - y1, x2 - x1)));
        window.draw(line);

        if (m_drawStyleStack.back().m_lineCap == LineCap::Round) {
            sf::CircleShape circle;
            circle.setFillColor(m_drawStyleStack.back().m_strokeColor);
            circle.setRadius(m_drawStyleStack.back().m_strokeWeight / 2.0f);
            circle.setOrigin({ m_drawStyleStack.back().m_strokeWeight / 2.0f, m_drawStyleStack.back().m_strokeWeight / 2.0f });
            circle.setPosition({ x1, y1 });
            window.draw(circle);
            circle.setPosition({ x2, y2 });
            window.draw(circle);
        }
    }

    void App::lineCap(LineCap cap) {
        m_drawStyleStack.back().m_lineCap = cap;
    }

    void App::rect(float x, float y, float width, float height) {
        if (m_drawStyleStack.back().m_rectMode == RectMode::Center) {
            x -= width / 2.0f;
            y -= height / 2.0f;
        }
        else if (m_drawStyleStack.back().m_rectMode == RectMode::Corner) {
            // Do nothing
        }
        else if (m_drawStyleStack.back().m_rectMode == RectMode::Corners) {
            width -= x;
            height -= y;
        }
        else {
            throw std::runtime_error("Unknown rect mode");
        }
        sf::RectangleShape rect;
        rect.setFillColor(m_drawStyleStack.back().m_fillColor);
        rect.setOutlineColor(m_drawStyleStack.back().m_strokeColor);
        rect.setOutlineThickness(m_drawStyleStack.back().m_strokeWeight);
        rect.setPosition({ x, y });
        rect.setSize({ width, height });
        window.draw(rect);
    }

    void App::rectMode(RectMode mode) {
        m_drawStyleStack.back().m_rectMode = mode;
    }




    // =======================================
    // =====         Window API       ========
    // =======================================

    void App::size(int width, int height) {
        this->width = width;
        this->height = height;
        window.setSize(sf::Vector2u(width, height));
    }

    void App::setTitle(const std::string& title) {
        this->title = title;
        window.setTitle(title);
    }

    void App::setFrameRate(float framerate) {
        window.setFramerateLimit(static_cast<unsigned int>(framerate));
    }

    void App::fullscreen() {
        m_widthBeforeFullscreen = width;
        m_heightBeforeFullscreen = height;
        window.create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen);
    }

    void App::exitFullscreen() {
        window.create(sf::VideoMode({ m_widthBeforeFullscreen, m_heightBeforeFullscreen }), title);
    }

    void App::close() {
        window.close();
    }





    // =======================================
    // =====         Math API         ========
    // =======================================

    float App::dist(float x1, float y1, float x2, float y2) {
        return sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
    }

    float App::radians(float degrees) {
        return degrees * (PI / 180.0f);
    }

    float App::degrees(float radians) {
        return radians * (180.0f / PI);
    }





    // =======================================
    // =====     Time and Date API    ========
    // =======================================

    uint64_t App::micros() {
        return static_cast<uint64_t>(m_lifetimeClock.getElapsedTime().asMicroseconds());
    }

    uint64_t App::millis() {
        return static_cast<uint64_t>(m_lifetimeClock.getElapsedTime().asMilliseconds());
    }

    int App::second() {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        auto now_tm = std::localtime(&now_c);
        return now_tm->tm_sec;
    }

    int App::minute() {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        auto now_tm = std::localtime(&now_c);
        return now_tm->tm_min;
    }

    int App::hour() {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        auto now_tm = std::localtime(&now_c);
        return now_tm->tm_hour;
    }

    int App::day() {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        auto now_tm = std::localtime(&now_c);
        return now_tm->tm_mday;
    }

    int App::month() {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        auto now_tm = std::localtime(&now_c);
        return now_tm->tm_mon + 1;
    }

    int App::year() {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        auto now_tm = std::localtime(&now_c);
        return now_tm->tm_year + 1900;
    }



    // =======================================
    // =====        Reserved API      ========
    // =======================================



    void App::run() {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8.0;

        updateDisplaySize();
        setup();

        window.create(sf::VideoMode({ width, height }), title, sf::Style::Default, settings);
        window.setFramerateLimit(60);

        while (window.isOpen()) {

            // Handle dark title bar
            if (darkTitleBar != m_isDarkTitleBar) {
#ifdef _WIN32
                Win32EnableDarkTitleBar(window.getSystemHandle(), darkTitleBar);
#else
#error "Dark title bar is only supported on Windows"
#endif
                m_isDarkTitleBar = darkTitleBar;
            }

            // Prepare data
            updateDisplaySize();
            focused = window.hasFocus();
            frameTime = m_frametimeClock.restart().asSeconds();
            frameRate = 1.0f / frameTime;
            pmouseX = mouseX;
            pmouseY = mouseY;
            mouseX = sf::Mouse::getPosition(window).x;
            mouseY = sf::Mouse::getPosition(window).y;
            dmouseX = mouseX - pmouseX;
            dmouseY = mouseY - pmouseY;

            // Handle events
            sf::Event event {};
            while (window.pollEvent(event)) {
                switch (event.type) {

                    case sf::Event::TextEntered:
                        onTextInput(event.text);
                        break;

                    case sf::Event::KeyPressed:
                        onKeyPressed(event.key);
                        break;

                    case sf::Event::KeyReleased:
                        onKeyReleased(event.key);
                        break;

                    case sf::Event::MouseButtonPressed:
                        onMousePressed(event.mouseButton);
                        break;

                    case sf::Event::MouseButtonReleased:
                        onMouseReleased(event.mouseButton);
                        break;

                    case sf::Event::MouseMoved:
                        onMouseMoved(event.mouseMove);
                        break;

                    case sf::Event::MouseWheelScrolled:
                        onMouseWheel(event.mouseWheelScroll);
                        break;

                    case sf::Event::MouseEntered:
                        onMouseEnter();
                        break;

                    case sf::Event::MouseLeft:
                        onMouseLeave();
                        break;

                    case sf::Event::Closed:
                        if (onWindowClose()) {
                            window.close();
                        }
                        break;

                    case sf::Event::Resized:
                        width = event.size.width;
                        height = event.size.height;
                        onWindowResize();
                        break;

                    case sf::Event::GainedFocus:
                        onWindowFocus();
                        break;

                    case sf::Event::LostFocus:
                        onWindowUnfocus();
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

            // Post update
            frameCount++;
        }
    }


    // =======================================
    // =====           Private        ========
    // =======================================

    void App::updateDisplaySize() {
        displayWidth = sf::VideoMode::getDesktopMode().width;
        displayHeight = sf::VideoMode::getDesktopMode().height;
    }

} // namespace cppgfx