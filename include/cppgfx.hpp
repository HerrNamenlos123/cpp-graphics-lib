
#ifndef CPP_GRAPHICS_LIB_CPPGFX_HPP
#define CPP_GRAPHICS_LIB_CPPGFX_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/fmt.h"
#include "spdlog/fmt/std.h"
#include "spdlog/fmt/ranges.h"
#include <iostream>

enum class LineCap {
    Round,
    Square
};

enum class RectMode {
    Center, // Origin is at center and x y is size
    Corner, // Origin is at top left corner and x y is size
    Corners // Origin is at top left corner and x y is bottom right corner
};

namespace cppgfx {

    class App {
    public:
        App();
        ~App();

        /// @brief The main window of the application [read only]
        sf::RenderWindow window;

        /// @brief If the dark title bar should be used [read only]
        bool darkTitleBar = true;

        /// @brief The current width of the window [read only]
        uint32_t width = 800;

        /// @brief The current height of the window [read only]
        uint32_t height = 600;

        /// @brief The width of the screen or monitor [read only]
        uint32_t displayWidth = 0;

        /// @brief The height of the screen or monitor [read only]
        uint32_t displayHeight = 0;

        /// @brief The title of the window [read only]
        /// @details This variable is updated by the setTitle() function
        std::string title = "My cppgfx application";

        /// @brief If the window is currently focused [read only]
        bool focused = true;

        /// @brief The frame count since the program started [read only]
        uint64_t frameCount = 0;

        /// @brief The elapsed time since the last frame in seconds [read only]
        float frameTime = 0;

        /// @brief The current frameRate [read only]
        float frameRate = 0;

        /// @brief The mathematical constant PI
        constexpr static float PI = 3.14159265358979323846f;

        /// @brief The current mouse position X [read only]
        int mouseX = 0;

        /// @brief The current mouse position Y [read only]
        int mouseY = 0;

        /// @brief The previous mouse position X [read only]
        int pmouseX = 0;

        /// @brief The previous mouse position Y [read only]
        int pmouseY = 0;

        // @brief The difference between the current and previous mouse position X [read only]
        int dmouseX = 0;

        // @brief The difference between the current and previous mouse position Y [read only]
        int dmouseY = 0;


        // These functions are supposed to be overridden by the user
        virtual void setup() = 0;
        virtual void update() = 0;

        virtual bool onWindowClose() { return true; }
        virtual void onTextInput(const sf::Event::TextEvent& event) {}
        virtual void onKeyPressed(const sf::Event::KeyEvent& event) {}
        virtual void onKeyReleased(const sf::Event::KeyEvent& event) {}
        virtual void onMousePressed(const sf::Event::MouseButtonEvent& event) {}
        virtual void onMouseReleased(const sf::Event::MouseButtonEvent& event) {}
        virtual void onMouseMoved(const sf::Event::MouseMoveEvent& event) {}
        virtual void onMouseWheel(const sf::Event::MouseWheelScrollEvent& event) {}
        virtual void onMouseEnter() {}
        virtual void onMouseLeave() {}
        virtual void onWindowResize() {}
        virtual void onWindowFocus() {}
        virtual void onWindowUnfocus() {}




        // =======================================
        // =====        Graphics API      ========
        // =======================================

        /// @brief Set the background color of the window
        void background(const sf::Color& color);

        /// @brief Set the background color of the window
        void background(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

        /// @brief Set the infill color for primitives
        void fill(const sf::Color& color);

        /// @brief Set the infill color for primitives
        void fill(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

        /// @brief Disable the infill color for primitives
        void noFill();

        /// @brief Set the outline color for primitives
        void stroke(const sf::Color& color);

        /// @brief Set the outline color for primitives
        void stroke(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

        /// @brief Disable the outline color for primitives
        void noStroke();

        /// @brief Set the thickness of the outline for primitives
        void strokeWeight(float weight);

        /// @brief Push the current draw style onto the stack
        void push();

        /// @brief Pop the current draw style from the stack
        void pop();

        /// @brief Draw a line from (x1, y1) to (x2, y2)
        void line(float x1, float y1, float x2, float y2);

        /// @brief Set the line cap style
        void lineCap(LineCap cap);

        /// @brief Draw a rectangle at (x, y) with the given width and height
        void rect(float x, float y, float width, float height);

        /// @brief Where the origin of the rectangle is
        void rectMode(RectMode mode);



        // =======================================
        // =====         Window API       ========
        // =======================================

        /// @brief Set the size of the window
        void size(int width, int height);

        /// @brief Set the title of the window
        void setTitle(const std::string& title);

        /// @brief Set the maximum framerate limit in frames per second
        void setFrameRate(float framerate);

        /// @brief Switch to fullscreen mode
        void fullscreen();

        /// @brief Exit fullscreen mode
        void exitFullscreen();

        /// @brief Stop the application
        void close();





        // =======================================
        // =====        System API        ========
        // =======================================

        /// @brief Print a message without newline to the console (FMT/Python formatting supported)
        /// @param message The message to print
        template<typename... Args>
        auto print(Args&&... args) {
            fmt::print(std::forward<Args>(args)...);
        }

        /// @brief Print a message including newline to the console (FMT/Python formatting supported)
        /// @param message The message to print
        template<typename... Args>
        auto println(Args&&... args) {
            fmt::print(std::forward<Args>(args)...);
            fmt::print("\n");
        }




        // =======================================
        // =====         Math API         ========
        // =======================================

        /// @brief Get the distance between two points
        /// @param x1 The x coordinate of the first point
        /// @param y1 The y coordinate of the first point
        /// @param x2 The x coordinate of the second point
        /// @param y2 The y coordinate of the second point
        /// @return The distance between the two points
        float dist(float x1, float y1, float x2, float y2);

        /// @brief Convert degrees to radians
        /// @param degrees The angle in degrees
        /// @return The angle in radians
        float radians(float degrees);

        /// @brief Convert radians to degrees
        /// @param radians The angle in radians
        /// @return The angle in degrees
        float degrees(float radians);




        // =======================================
        // =====     Time and Date API    ========
        // =======================================

        /// @brief Get the number of microseconds since the program started
        /// @return The elapsed number of microseconds
        uint64_t micros();

        /// @brief Get the number of milliseconds since the program started
        /// @return The elapsed number of milliseconds
        uint64_t millis();

        /// @brief Get the current second from the system clock [0-59]
        /// @return The current second
        int second();

        /// @brief Get the current minute from the system clock [0-59]
        /// @return The current minute
        int minute();

        /// @brief Get the current hour from the system clock [0-23]
        /// @return The current hour
        int hour();

        /// @brief Get the current day of the month [1-31]
        /// @return The current day of the month
        int day();

        /// @brief Get the current month of the year [1-12]
        /// @return The current month of the year
        int month();

        /// @brief Get the current year
        /// @return The current year
        int year();




        // =======================================
        // =====        Reserved API      ========
        // =======================================

        /// @brief Run the application
        /// @warning Do not call this function if you don't know what you are doing. It should
        ///          only be called once in the main function, where it should already be in the template.
        void run();

    private:
        App(const App&) = delete;
        App& operator=(const App&) = delete;

        void updateDisplaySize();

        sf::Color m_defaultBackgroundColor = sf::Color(60, 60, 60);
        bool m_isDarkTitleBar = false;
        sf::Clock m_lifetimeClock;
        sf::Clock m_frametimeClock;

        uint32_t m_widthBeforeFullscreen = 0;
        uint32_t m_heightBeforeFullscreen = 0;

        struct DrawStyle {
            sf::Color m_fillColor = sf::Color::White;
            sf::Color m_strokeColor = sf::Color::Black;
            float m_strokeWeight = 1.0f;

            LineCap m_lineCap = LineCap::Round;
            RectMode m_rectMode = RectMode::Corner;
        };
        std::vector<DrawStyle> m_drawStyleStack;

    };

}

#endif //CPP_GRAPHICS_LIB_CPPGFX_HPP
