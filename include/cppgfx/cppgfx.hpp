
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

#include "imgui.h"

#include "cppgfx/base64.hpp"

///
/// @defgroup Window
/// @brief Everything related to windowing and OS integration
///

///
/// @defgroup Maths
/// @brief Mathematical operations and constants
///

///
/// @defgroup InputDevices
/// @brief Input devices like mouse, keyboard, etc.
///

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

    /// @brief The main application class
    /// @details This class is supposed to be inherited by the user.
    class App {
    public:
        App();
        ~App();

        static App& Get() {
            if (m_instance == nullptr) {
                throw std::logic_error("cppgfx::App::Get(): No instance of cppgfx::App exists. "
                                       "Did you forget to create an instance of your application class?");
            }

            return *m_instance;
        }

        /// @brief The main window of your application
        /// @ingroup Window
        /// @details This is the SFML RenderWindow which is used to draw everything. If you have the knowledge,
        ///          you can use this variable to access the SFML API directly in order to draw more complex things.
        sf::RenderWindow window;

        /// @brief If the dark title bar should be used
        /// @ingroup Window
        /// @details If this variable is set, the window will have a dark title bar instead of a white one.
        /// @note For now, this feature only affects Windows.
        bool darkTitleBar = true;

        /// @brief The current width of the window [read only]
        /// @ingroup Window
        /// @details This variable is automatically updated and will not affect anything if you change it.
        ///          Use the size() function to change the size of the window.
        uint32_t width = 800;

        /// @brief The current height of the window [read only]
        /// @ingroup Window
        /// @details This variable is automatically updated and will not affect anything if you change it.
        ///          Use the size() function to change the size of the window.
        uint32_t height = 600;

        /// @brief The pixel width of the primary monitor [read only]
        /// @ingroup Window
        /// @details This variable is automatically updated and will not affect anything if you change it.
        uint32_t displayWidth = 0;

        /// @brief The pixel height of the primary monitor [read only]
        /// @ingroup Window
        /// @details This variable is automatically updated and will not affect anything if you change it.
        uint32_t displayHeight = 0;

        /// @brief The current title of the window [read only]
        /// @ingroup Window
        /// @details This variable is automatically updated and will not affect anything if you change it.
        ///          Use the setTitle() function to change the title of the window.
        std::string title = "My cppgfx application";

        /// @brief If the window is currently focused or not [read only]
        /// @ingroup Window
        /// @details This variable is automatically updated and will not affect anything if you change it.
        ///          Use focus() to request window to be focused.
        bool focused = true;

        /// @brief The frame count since the program started [read only]
        /// @ingroup Window
        /// @details This variable starts at 0 and is incremented for every frame. Keep in mind that using the framecount
        ///          for timing is not recommended, since the framerate can vary. To get uniform, framerate independent
        ///          movement, use the frameTime variable instead.
        ///          This variable is automatically updated and will not affect anything if you change it.
        uint64_t frameCount = 0;

        /// @brief The elapsed time since the last frame in seconds [read only]
        /// @ingroup Window
        /// @details This is the time in seconds that has passed, since the last frame. Use this variable to get
        ///          framerate independent motion, by multiplying the distance to move with this variable.
        ///          This variable is automatically updated and will not affect anything if you change it.
        float frameTime = 0;

        /// @brief The current frameRate [read only]
        /// @ingroup Window
        /// @details This is the current frameRate in frames per second. It is intended for debugging purposes
        ///          and diagnostics.
        ///          This variable is automatically updated and will not affect anything if you change it.
        float frameRate = 0;

        /// @brief The mathematical constant PI
        /// @ingroup Math
        constexpr static float PI = 3.14159265358979323846f;

        /// @brief The current mouse position X [read only]
        /// @ingroup InputDevices
        /// @details This is the current mouse position X in pixels relative to the top left corner of the window.
        ///          This variable is automatically updated and will not affect anything if you change it.
        int mouseX = 0;

        /// @brief The current mouse position Y [read only]
        /// @ingroup InputDevices
        /// @details This is the current mouse position Y in pixels relative to the top left corner of the window.
        ///          The down direction is positive.
        ///          This variable is automatically updated and will not affect anything if you change it.
        int mouseY = 0;

        /// @brief The previous mouse position X [read only]
        /// @ingroup InputDevices
        /// @details This is the mouse position X from the last frame. You can use it in conjunction with mouseX to
        ///          calculate the difference between the current and previous mouse position.
        ///          This variable is automatically updated and will not affect anything if you change it.
        int pmouseX = 0;

        /// @brief The previous mouse position Y [read only]
        /// @ingroup InputDevices
        /// @details This is the mouse position Y from the last frame. You can use it in conjunction with mouseY to
        ///          calculate the difference between the current and previous mouse position.
        ///          This variable is automatically updated and will not affect anything if you change it.
        int pmouseY = 0;

        /// @brief The difference between the current and previous mouse position X [read only]
        /// @ingroup InputDevices
        /// @details This is the difference between the current and previous mouse position X.
        ///          This variable is automatically updated and will not affect anything if you change it.
        int dmouseX = 0;

        /// @brief The difference between the current and previous mouse position Y [read only]
        /// @ingroup InputDevices
        /// @details This is the difference between the current and previous mouse position Y.
        ///          This variable is automatically updated and will not affect anything if you change it.
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
        void rect(float x, float y, float w, float h);

        /// @brief Where the origin of the rectangle is
        void rectMode(RectMode mode);

        /// @brief Draw a circle at (x, y) with the given radius
        void circle(float x, float y, float radius);

        /// @brief Draw an ellipse at (x, y) with the given width and height
        void ellipse(float x, float y, float w, float h);

        /// @brief Draw a triangle with the given points
        void triangle(float x1, float y1, float x2, float y2, float x3, float y3);

        /// @brief Draw a vector arrow from the origin to origin + vector
        void vector(float vectorX, float vectorY, float originX, float originY);



        // =======================================
        // =====         Window API       ========
        // =======================================

        /// @brief Set the size of the window
        /// @ingroup Window
        /// @details This function will change the size of the window to the given width and height.
        /// @param w The new width of the window in pixel
        /// @param h The new height of the window in pixel
        void size(int w, int h);

        /// @brief Set the title of the window
        /// @ingroup Window
        /// @details This function will change the title of the window to the given text.
        /// @param text The new title of the window
        void setTitle(const std::string& text);

        /// @brief Set the maximum framerate limit in frames per second
        /// @ingroup Window
        /// @details This function will limit the framerate to the given value.
        /// @param framerate The new framerate limit
        void setFrameRate(float framerate);

        /// @brief Switch to fullscreen mode
        /// @ingroup Window
        /// @details This function will switch the window to fullscreen mode.
        void fullscreen();

        /// @brief Exit fullscreen mode
        /// @ingroup Window
        /// @details This function will exit fullscreen mode and restore the window to its previous size.
        void exitFullscreen();

        /// @brief Stop the application
        /// @ingroup Window
        /// @details This function will stop the application and close the window.
        void close();

        /// @brief Request the window to be focused
        /// @ingroup Window
        /// @details This function will not focus the window immediately, but instead request the window to be focused.
        ///          On Windows for example, this is noticable by the taskbar icon flashing orange.
        void focus();





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

        /// @brief Encode a string to base-64
        /// @param input The string to encode
        /// @return The base-64 encoded string
        auto encodeBase64(const std::vector<uint8_t>& input) {
            return encode_base64(input);
        }

        /// @brief Decode a base-64 encoded string
        /// @param input The base-64 encoded string
        /// @return The decoded string
        auto decodeBase64(const std::string& input) {
            return decode_base64(input);
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

        /// @brief Get the greater of two values
        /// @param a The first value
        /// @param b The second value
        /// @return The greater of the two
        template<typename T>
        T max(T a, T b) {
            return a > b ? a : b;
        }

        /// @brief Get the lesser of two values
        /// @param a The first value
        /// @param b The second value
        /// @return The lesser of the two values
        template<typename T>
        T min(T a, T b) {
            return a < b ? a : b;
        }

        /// @brief Clamp the value between the given min and max
        /// @param value The value to clamp
        /// @param min The minimum value
        /// @param max The maximum value
        /// @return The clamped value
        template<typename T>
        T clamp(T value, T min, T max) {
            return value < min ? min : value > max ? max : value;
        }




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

        inline static App* m_instance = nullptr;

        sf::Color m_defaultBackgroundColor = sf::Color(60, 60, 60);
        bool m_isDarkTitleBar = false;
        sf::Clock m_lifetimeClock;
        sf::Clock m_frametimeClock;

        uint32_t m_widthBeforeFullscreen = 0;
        uint32_t m_heightBeforeFullscreen = 0;

        struct DrawStyle {
            sf::Color m_fillColor = sf::Color::White;
            sf::Color m_strokeColor = sf::Color::Black;
            float m_strokeWeight = 0.f;

            LineCap m_lineCap = LineCap::Round;
            RectMode m_rectMode = RectMode::Corner;
        };
        std::vector<DrawStyle> m_drawStyleStack;

    };

}

#endif //CPP_GRAPHICS_LIB_CPPGFX_HPP