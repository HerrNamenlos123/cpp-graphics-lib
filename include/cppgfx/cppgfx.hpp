
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
/// @defgroup Input
/// @brief Input devices like mouse, keyboard, etc.
///

///
/// @defgroup Graphics
/// @brief Drawing primitives and styles
///

///
/// @defgroup Output
/// @brief Console output and formatting
///

///
/// @defgroup Timing
/// @brief Time, Sleep and Date
///

///
/// @defgroup Events
/// @brief All cppgfx functions you can override, including Events.
///

enum class TextAlign {
    Left,
    Center,
    Right
};

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
        /// @ingroup Input
        /// @details This is the current mouse position X in pixels relative to the top left corner of the window.
        ///          This variable is automatically updated and will not affect anything if you change it.
        int mouseX = 0;

        /// @brief The current mouse position Y [read only]
        /// @ingroup Input
        /// @details This is the current mouse position Y in pixels relative to the top left corner of the window.
        ///          The down direction is positive.
        ///          This variable is automatically updated and will not affect anything if you change it.
        int mouseY = 0;

        /// @brief The previous mouse position X [read only]
        /// @ingroup Input
        /// @details This is the mouse position X from the last frame. You can use it in conjunction with mouseX to
        ///          calculate the difference between the current and previous mouse position.
        ///          This variable is automatically updated and will not affect anything if you change it.
        int pmouseX = 0;

        /// @brief The previous mouse position Y [read only]
        /// @ingroup Input
        /// @details This is the mouse position Y from the last frame. You can use it in conjunction with mouseY to
        ///          calculate the difference between the current and previous mouse position.
        ///          This variable is automatically updated and will not affect anything if you change it.
        int pmouseY = 0;

        /// @brief Delta X: The difference between the current and previous mouse position X [read only]
        /// @ingroup Input
        /// @details This is the difference between the current and previous mouse position X.
        ///          This variable is automatically updated and will not affect anything if you change it.
        int dmouseX = 0;

        /// @brief Delta Y: The difference between the current and previous mouse position Y [read only]
        /// @ingroup Input
        /// @details This is the difference between the current and previous mouse position Y.
        ///          This variable is automatically updated and will not affect anything if you change it.
        int dmouseY = 0;




        // =======================================
        // =====     Virtual Functions    ========
        // =======================================

        /// @brief This function is called once at the beginning of the program.
        /// @ingroup Events
        /// @details It must be overridden in your class which inherits from cppgfx::App.
        virtual void setup() = 0;

        /// @brief This function is called repeatedly until the program is terminated.
        /// @ingroup Events
        /// @details It must be overridden in your class which inherits from cppgfx::App.
        virtual void update() = 0;

        /// @brief This function is called once at the end of the program.
        /// @ingroup Events
        /// @details It can be overridden in your class which inherits from cppgfx::App.
        virtual void cleanup() {}

        /// @brief This function can be used to intercept the window close event.
        /// @ingroup Events
        /// @details This function is called when the window wants to be closed. Using this function, you can
        ///          decide if you really want to close it or continue, by returning true or false. Returning true
        ///          will close the window immediately, returning false will ignore the event.
        ///          It can optionally be overridden in your class which inherits from cppgfx::App.
        virtual bool onWindowClose() { return true; }

        /// @brief This function is called when keys on the keyboard are pressed. To be used for text input.
        /// @ingroup Events
        /// @details This function is to be used if you want the user to type text on the keyboard. If you want
        ///          to capture key events with key bindings, use onKeyPressed() instead.
        ///          It can optionally be overridden in your class which inherits from cppgfx::App.
        virtual void onTextInput(const sf::Event::TextEvent& event) {}

        /// @brief This function is called when keys on the keyboard are pressed. To be used for key bindings, not text.
        /// @ingroup Events
        /// @details This function is to be used if you want to capture key events that are tied to specific keys.
        ///          If you want the user to write text, use onTextInput() instead.
        ///          It can optionally be overridden in your class which inherits from cppgfx::App.
        virtual void onKeyPressed(const sf::Event::KeyEvent& event) {}

        /// @brief This function is called when keys on the keyboard are released.
        /// @ingroup Events
        /// @details It can optionally be overridden in your class which inherits from cppgfx::App.
        virtual void onKeyReleased(const sf::Event::KeyEvent& event) {}

        /// @brief This function is called when a mouse button is pressed.
        /// @ingroup Events
        /// @details It can optionally be overridden in your class which inherits from cppgfx::App.
        virtual void onMousePressed(const sf::Event::MouseButtonEvent& event) {}

        /// @brief This function is called when a mouse button is released.
        /// @ingroup Events
        /// @details It can optionally be overridden in your class which inherits from cppgfx::App.
        virtual void onMouseReleased(const sf::Event::MouseButtonEvent& event) {}

        /// @brief This function is called when the mouse is moved.
        /// @ingroup Events
        /// @details It can optionally be overridden in your class which inherits from cppgfx::App.
        virtual void onMouseMoved(const sf::Event::MouseMoveEvent& event) {}

        /// @brief This function is called when the mouse wheel is scrolled.
        /// @ingroup Events
        /// @details It can optionally be overridden in your class which inherits from cppgfx::App.
        virtual void onMouseWheel(const sf::Event::MouseWheelScrollEvent& event) {}

        /// @brief This function is called when the mouse enters the window.
        /// @ingroup Events
        /// @details It can optionally be overridden in your class which inherits from cppgfx::App.
        virtual void onMouseEnter() {}

        /// @brief This function is called when the mouse leaves the window.
        /// @ingroup Events
        /// @details It can optionally be overridden in your class which inherits from cppgfx::App.
        virtual void onMouseLeave() {}

        /// @brief This function is called when the window is resized.
        /// @ingroup Events
        /// @details It can optionally be overridden in your class which inherits from cppgfx::App.
        virtual void onWindowResize() {}

        /// @brief This function is called when the window is focused.
        /// @ingroup Events
        /// @details It can optionally be overridden in your class which inherits from cppgfx::App.
        virtual void onWindowFocus() {}

        /// @brief This function is called when the window loses focus.
        /// @ingroup Events
        /// @details It can optionally be overridden in your class which inherits from cppgfx::App.
        virtual void onWindowUnfocus() {}




        // =======================================
        // =====        Graphics API      ========
        // =======================================

        /// @brief Set the background color of the window for the current frame
        /// @ingroup Graphics
        /// @param color The background color
        void background(const sf::Color& color);

        /// @brief Set the background color of the window for the current frame
        /// @ingroup Graphics
        /// @param shade The background color for r, g and b [0-255]
        void background(uint8_t shade);

        /// @brief Set the background color of the window
        /// @ingroup Graphics
        /// @param r The red component of the background color [0-255]
        /// @param g The green component of the background color [0-255]
        /// @param b The blue component of the background color [0-255]
        /// @param a The alpha component of the background color [0-255] (optional)
        void background(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

        /// @brief Set the infill color for primitives
        /// @ingroup Graphics
        /// @param color The infill color
        void fill(const sf::Color& color);

        /// @brief Set the infill color for primitives
        /// @ingroup Graphics
        /// @param shade The infill color for r, g and b [0-255]
        void fill(uint8_t shade);

        /// @brief Set the infill color for primitives
        /// @ingroup Graphics
        /// @param r The red component of the infill color [0-255]
        /// @param g The green component of the infill color [0-255]
        /// @param b The blue component of the infill color [0-255]
        /// @param a The alpha component of the infill color [0-255] (optional)
        void fill(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

        /// @brief Disable the infill color for primitives
        /// @ingroup Graphics
        void noFill();

        /// @brief Set the outline color for primitives
        /// @ingroup Graphics
        void stroke(const sf::Color& color);

        /// @brief Set the outline color for primitives
        /// @ingroup Graphics
        /// @param shade The outline color for r, g and b [0-255]
        void stroke(uint8_t shade);

        /// @brief Set the outline color for primitives
        /// @ingroup Graphics
        /// @param r The red component of the outline color [0-255]
        /// @param g The green component of the outline color [0-255]
        /// @param b The blue component of the outline color [0-255]
        /// @param a The alpha component of the outline color [0-255] (optional)
        void stroke(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

        /// @brief Disable the outline color for primitives
        /// @ingroup Graphics
        void noStroke();

        /// @brief Set the thickness of the outline for primitives
        /// @ingroup Graphics
        /// @param weight The thickness of the outline in pixels
        void strokeWeight(float weight);

        /// @brief Push the current draw style onto the stack
        /// @ingroup Graphics
        /// @details This function will push the current draw style onto the stack, so that it can be restored later.
        ///          This mechanism is very useful when you want to temporarily change the draw style, and later
        ///          change it back to what it was.
        void push();

        /// @brief Pop the current draw style from the stack
        /// @ingroup Graphics
        /// @details This function will pop the current draw style from the stack, so that it can be restored later.
        ///          This mechanism is very useful when you want to temporarily change the draw style, and later
        ///          change it back to what it was.
        void pop();

        /// @brief Draw a line from (x1, y1) to (x2, y2)
        /// @ingroup Graphics
        /// @param x1 The x coordinate of the first point in pixels, relative to the top left corner of the window
        /// @param y1 The y coordinate of the first point in pixels, relative to the top left corner of the window
        /// @param x2 The x coordinate of the second point in pixels, relative to the top left corner of the window
        /// @param y2 The y coordinate of the second point in pixels, relative to the top left corner of the window
        void line(float x1, float y1, float x2, float y2);

        /// @brief Set the line cap style
        /// @ingroup Graphics
        /// @param cap The line cap style
        void lineCap(LineCap cap);

        /// @brief Draw a rectangle at (x, y) with the given width and height
        /// @ingroup Graphics
        /// @details What the x, y, w and h parameters mean depends on the current rectMode.
        /// @param x The first x coordinate in pixels, relative to the top left corner of the window
        /// @param y The first y coordinate in pixels, relative to the top left corner of the window
        /// @param w The second x coordinate in pixels, relative to the top left corner of the window
        /// @param h The second y coordinate in pixels, relative to the top left corner of the window
        void rect(float x, float y, float w, float h);

        /// @brief Where the origin of the rectangle is
        /// @ingroup Graphics
        /// @details This function will change the meaning of the x, y, w and h parameters of the rect() function.
        ///          The default is RectMode::Corner. RectMode::Corner means that x and y are the top left corner
        ///          of the rectangle and w and h are the width and height of the rectangle. RectMode::Center means
        ///          that x and y are the center of the rectangle and w and h are the width and height of the rectangle.
        ///          RectMode::Corners means that x and y are the top left corner of the rectangle and w and h are the
        ///          bottom right corner of the rectangle.
        /// @param mode The rectMode
        void rectMode(RectMode mode);

        /// @brief Draw a circle at (x, y) with the given radius
        /// @ingroup Graphics
        /// @param x The x coordinate of the center of the circle in pixels, relative to the top left corner of the window
        /// @param y The y coordinate of the center of the circle in pixels, relative to the top left corner of the window
        /// @param radius The radius of the circle in pixels
        void circle(float x, float y, float radius);

        /// @brief Draw an ellipse at (x, y) with the given width and height
        /// @ingroup Graphics
        /// @param x The x coordinate of the center of the ellipse in pixels, relative to the top left corner of the window
        /// @param y The y coordinate of the center of the ellipse in pixels, relative to the top left corner of the window
        /// @param w The width of the ellipse in pixels
        /// @param h The height of the ellipse in pixels
        void ellipse(float x, float y, float w, float h);

        /// @brief Draw a triangle with the given points
        /// @ingroup Graphics
        /// @param x1 The x coordinate of the first point in pixels, relative to the top left corner of the window
        /// @param y1 The y coordinate of the first point in pixels, relative to the top left corner of the window
        /// @param x2 The x coordinate of the second point in pixels, relative to the top left corner of the window
        /// @param y2 The y coordinate of the second point in pixels, relative to the top left corner of the window
        /// @param x3 The x coordinate of the third point in pixels, relative to the top left corner of the window
        /// @param y3 The y coordinate of the third point in pixels, relative to the top left corner of the window
        void triangle(float x1, float y1, float x2, float y2, float x3, float y3);

        /// @brief Draw a vector arrow from the origin to origin + vector
        /// @ingroup Graphics
        /// @details This function will draw a vector arrow from the origin to origin + vector. It is meant to be used
        ///          for scientific visualization purposes.
        /// @param vectorX The x component of the vector
        /// @param vectorY The y component of the vector
        /// @param originX The x coordinate of the origin of the vector in pixels, relative to the top left corner of the window
        /// @param originY The y coordinate of the origin of the vector in pixels, relative to the top left corner of the window
        void vector(float vectorX, float vectorY, float originX, float originY);

        /// @brief Set the current font to be used for rendering from now on
        /// @ingroup Graphics
        /// @param font The SFML font to use
        void textFont(const sf::Font& font);

        /// @brief Load a font from a file with a specific size
        /// @ingroup Graphics
        /// @param filename The filename of the font to load
        /// @return The loaded font
        sf::Font loadFont(const std::string& filename);

        /// @brief Set the current alignment for drawing text
        /// @ingroup Graphics
        /// @param alignment The alignment
        void textAlign(TextAlign alignment);

        /// @brief Calculate the width of a text string in pixels
        /// @ingroup Graphics
        /// @param text The text to measure
        /// @return The width of the text in pixels
        float textWidth(const std::string& text);

        /// @brief Set the font size of the currently active font
        /// @ingroup Graphics
        /// @param size The font size in pixels
        void textSize(uint32_t size);

        /// @brief Draw text at (x, y)
        /// @ingroup Graphics
        /// @param text The text to draw
        /// @param x The x coordinate of the text in pixels, relative to the top left corner of the window
        /// @param y The y coordinate of the text in pixels, relative to the top left corner of the window
        void text(const std::string& text, float x, float y);



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

        /// @brief Print a formatted string without newline to the console (FMT/Python formatting supported)
        /// @ingroup Output
        /// @param args Arguments to pass to fmt::print.
        template<typename... Args>
        void print(Args&&... args) {
            fmt::print(std::forward<Args>(args)...);
        }

        /// @brief Print a formatted string with newline to the console (FMT/Python formatting supported)
        /// @ingroup Output
        /// @param args Arguments to pass to fmt::print.
        template<typename... Args>
        void println(Args&&... args) {
            fmt::print(std::forward<Args>(args)...);
            fmt::print("\n");
        }

        /// @brief Encode an arbitrary resource in base-64 encoding
        /// @param input The byte sequence to encode. This can be a string, or any arbitrary byte sequence.
        /// @return The base-64 encoded string
        std::string encodeBase64(const std::vector<uint8_t>& input) {
            return encode_base64(input);
        }

        /// @brief Decode a base-64 encoded string into its original form
        /// @param input The base-64 encoded string to decode. The result can be a string, or any arbitrary byte sequence.
        /// @return The decoded byte sequence or string
        std::vector<uint8_t> decodeBase64(const std::string& input) {
            return decode_base64(input);
        }




        // =======================================
        // =====         Math API         ========
        // =======================================

        /// @brief Get the distance between two points
        /// @ingroup Math
        /// @param x1 The x coordinate of the first point
        /// @param y1 The y coordinate of the first point
        /// @param x2 The x coordinate of the second point
        /// @param y2 The y coordinate of the second point
        /// @return The distance between the two points
        float dist(float x1, float y1, float x2, float y2);

        /// @brief Convert degrees to radians
        /// @ingroup Math
        /// @param degrees The angle in degrees
        /// @return The angle in radians
        float radians(float degrees);

        /// @brief Convert radians to degrees
        /// @ingroup Math
        /// @param radians The angle in radians
        /// @return The angle in degrees
        float degrees(float radians);

        /// @brief Get the greater of two values
        /// @ingroup Math
        /// @param a The first value
        /// @param b The second value
        /// @return The greater of the two
        template<typename T>
        T max(T a, T b) {
            return std::max(a, b);
        }

        /// @brief Get the lesser of two values
        /// @ingroup Math
        /// @param a The first value
        /// @param b The second value
        /// @return The lesser of the two values
        template<typename T>
        T min(T a, T b) {
            return std::min(a, b);
        }

        /// @brief Clamp the value between the given min and max
        /// @ingroup Math
        /// @param value The value to clamp
        /// @param min The minimum value
        /// @param max The maximum value
        /// @return The clamped value
        template<typename T>
        T clamp(T value, T min, T max) {
            return std::clamp(value, min, max);
        }




        // =======================================
        // =====     Time and Date API    ========
        // =======================================

        /// @brief Get the number of microseconds since the program started
        /// @ingroup Timing
        /// @return The elapsed number of microseconds
        uint64_t micros();

        /// @brief Get the number of milliseconds since the program started
        /// @ingroup Timing
        /// @return The elapsed number of milliseconds
        uint64_t millis();

        /// @brief Get the current second from the system clock [0-59]
        /// @ingroup Timing
        /// @return The current second
        int second();

        /// @brief Get the current minute from the system clock [0-59]
        /// @ingroup Timing
        /// @return The current minute
        int minute();

        /// @brief Get the current hour from the system clock [0-23]
        /// @ingroup Timing
        /// @return The current hour
        int hour();

        /// @brief Get the current day of the month [1-31]
        /// @ingroup Timing
        /// @return The current day of the month
        int day();

        /// @brief Get the current month of the year [1-12]
        /// @ingroup Timing
        /// @return The current month of the year
        int month();

        /// @brief Get the current year
        /// @ingroup Timing
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

        inline static sf::Font m_defaultFont;

        struct DrawStyle {
            sf::Color m_fillColor = sf::Color::White;
            sf::Color m_strokeColor = sf::Color::Black;
            float m_strokeWeight = 0.f;
            sf::Font m_font = m_defaultFont;
            uint32_t m_fontSize = 18;

            LineCap m_lineCap = LineCap::Round;
            RectMode m_rectMode = RectMode::Corner;
            TextAlign m_textAlign = TextAlign::Left;
        };
        std::vector<DrawStyle> m_drawStyleStack;

    };

}

#endif //CPP_GRAPHICS_LIB_CPPGFX_HPP