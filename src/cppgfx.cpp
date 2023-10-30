
#include "cppgfx/cppgfx.hpp"
#include "cppgfx/win32.hpp"
#include "cppgfx/data.hpp"
#include "ImGui-SFML.h"
#include "cppgfx/robotofont.hpp"

#include <chrono>

namespace cppgfx {

    App::App() {
        m_instance = this;

        if (!m_defaultFont.loadFromMemory(ROBOTO_MEDIUM_DATA, ROBOTO_MEDIUM_SIZE)) {
            throw std::runtime_error("[cppgfx]: Failed to load SFML default font: Roboto Medium");
        }

        m_drawStyleStack.emplace_back();
    }

    App::~App() = default;




    // =======================================
    // =====        Graphics API      ========
    // =======================================

    void App::background(const sf::Color& color) {
        window.clear(color);
    }

    void App::background(uint8_t shade) {
        window.clear(sf::Color(shade, shade, shade));
    }

    void App::background(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        window.clear(sf::Color(r, g, b, a));
    }

    void App::fill(const sf::Color& color) {
        m_drawStyleStack.back().m_fillColor = color;
    }

    void App::fill(uint8_t shade) {
        m_drawStyleStack.back().m_fillColor = sf::Color(shade, shade, shade);
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

    void App::stroke(uint8_t shade) {
        m_drawStyleStack.back().m_strokeColor = sf::Color(shade, shade, shade);
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

    void App::rect(float x, float y, float w, float h) {
        if (m_drawStyleStack.back().m_rectMode == RectMode::Center) {
            x -= w / 2.0f;
            y -= h / 2.0f;
        }
        else if (m_drawStyleStack.back().m_rectMode == RectMode::Corner) {
            // Do nothing
        }
        else if (m_drawStyleStack.back().m_rectMode == RectMode::Corners) {
            w -= x;
            h -= y;
        }
        else {
            throw std::runtime_error("Unknown rect mode");
        }
        sf::RectangleShape rect;
        rect.setFillColor(m_drawStyleStack.back().m_fillColor);
        rect.setOutlineColor(m_drawStyleStack.back().m_strokeColor);
        rect.setOutlineThickness(m_drawStyleStack.back().m_strokeWeight);
        rect.setPosition({ x, y });
        rect.setSize({w, h });
        window.draw(rect);
    }

    void App::rectMode(RectMode mode) {
        m_drawStyleStack.back().m_rectMode = mode;
    }

    void App::circle(float x, float y, float radius) {
        sf::CircleShape circle;
        circle.setFillColor(m_drawStyleStack.back().m_fillColor);
        circle.setOutlineColor(m_drawStyleStack.back().m_strokeColor);
        circle.setOutlineThickness(m_drawStyleStack.back().m_strokeWeight);
        circle.setRadius(radius);
        circle.setOrigin({ radius, radius });
        circle.setPosition({ x, y });
        window.draw(circle);
    }

    void App::ellipse(float x, float y, float w, float h) {
        sf::CircleShape circle;
        circle.setFillColor(m_drawStyleStack.back().m_fillColor);
        circle.setOutlineColor(m_drawStyleStack.back().m_strokeColor);
        circle.setOutlineThickness(m_drawStyleStack.back().m_strokeWeight);
        circle.setRadius(w / 2.0f);
        circle.scale(1.0f, h / w); // sfml uses a circle as an ellipse, so we need to scale it
        circle.setOrigin({w / 2.0f, w / 2.0f });
        circle.setPosition({ x, y });
        window.draw(circle);
    }

    void App::triangle(float x1, float y1, float x2, float y2, float x3, float y3) {
        sf::ConvexShape triangle;
        triangle.setFillColor(m_drawStyleStack.back().m_fillColor);
        triangle.setPointCount(3);
        triangle.setPoint(0, { x1, y1 });
        triangle.setPoint(1, { x2, y2 });
        triangle.setPoint(2, { x3, y3 });
        window.draw(triangle);

        line(x1, y1, x2, y2);
        line(x2, y2, x3, y3);
        line(x3, y3, x1, y1);
    }

    void App::vector(float vectorX, float vectorY, float originX, float originY) {
        if (vectorX == 0 && vectorY == 0) {
            return;
        }
        float angle = atan2f(vectorY, vectorX);
        float arrowLength = min(15.f * m_drawStyleStack.back().m_strokeWeight, dist(0, 0, vectorX, vectorY));
        float arrowAngle = radians(15.0f);
        float arrowX1 = originX + vectorX - arrowLength * cosf(angle + arrowAngle / 2.f);
        float arrowY1 = originY + vectorY - arrowLength * sinf(angle + arrowAngle / 2.f);
        float arrowX2 = originX + vectorX - arrowLength * cosf(angle - arrowAngle / 2.f);
        float arrowY2 = originY + vectorY - arrowLength * sinf(angle - arrowAngle / 2.f);
        float arrowCenterX = originX + vectorX - arrowLength * cosf(angle);
        float arrowCenterY = originY + vectorY - arrowLength * sinf(angle);
        line(originX, originY, arrowCenterX, arrowCenterY);
        push();
        fill(m_drawStyleStack.back().m_strokeColor);
        noStroke();
        triangle(originX + vectorX, originY + vectorY, arrowX1, arrowY1, arrowX2, arrowY2);
        pop();
    }

    void App::textFont(const sf::Font& font) {
        m_drawStyleStack.back().m_font = font;
    }

    sf::Font App::loadFont(const std::string& filename) {
        sf::Font font;
        if (!font.loadFromFile(filename)) {
            throw std::runtime_error("[cppgfx] Failed to load font: " + filename);
        }
        return font;
    }

    void App::textAlign(TextAlign align) {
        m_drawStyleStack.back().m_textAlign = align;
    }

    float App::textWidth(const std::string& text) {
        sf::Text sfText;
        sfText.setFont(m_drawStyleStack.back().m_font);
        sfText.setString(text);
        sfText.setCharacterSize(m_drawStyleStack.back().m_fontSize);
        return sfText.getLocalBounds().width;
    }

    void App::textSize(uint32_t size) {
        m_drawStyleStack.back().m_fontSize = size;
    }

    void App::text(const std::string& text, float x, float y) {
        sf::Text sfText;
        sfText.setFont(m_drawStyleStack.back().m_font);
        sfText.setString(text);
        sfText.setCharacterSize(m_drawStyleStack.back().m_fontSize);
        sfText.setFillColor(m_drawStyleStack.back().m_fillColor);
        sfText.setOutlineColor(m_drawStyleStack.back().m_strokeColor);
        sfText.setOutlineThickness(m_drawStyleStack.back().m_strokeWeight);
        sfText.setOrigin({ 0, sfText.getLocalBounds().top });
        if (m_drawStyleStack.back().m_textAlign == TextAlign::Left) {
            sfText.setPosition({ x, y });
        }
        else if (m_drawStyleStack.back().m_textAlign == TextAlign::Center) {
            sfText.setPosition({ x - sfText.getLocalBounds().width / 2.0f, y });
        }
        else if (m_drawStyleStack.back().m_textAlign == TextAlign::Right) {
            sfText.setPosition({ x - sfText.getLocalBounds().width, y });
        }
        else {
            throw std::runtime_error("Unknown text align");
        }
        window.draw(sfText);
    }






    // =======================================
    // =====         Window API       ========
    // =======================================

    void App::size(int w, int h) {
        this->width = w;
        this->height = h;
        window.setSize(sf::Vector2u(w, h));
    }

    void App::setTitle(const std::string& text) {
        this->title = text;
        window.setTitle(text);
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

    void App::focus() {
        window.requestFocus();
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

    void App::randomSeed(uint32_t seed) {
        std::srand(seed);
    }

    int App::randomInt(int min, int max) {
        return min + std::rand() / (RAND_MAX / (max - min));
    }

    int App::randomInt(int max) {
        return random(0, max);
    }

    float App::random(float min, float max) {
        return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    }

    float App::random(float max) {
        return random(0.0f, max);
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

    template<typename T>
    static inline T Lerp(T a, T b, float t) { return (T)(a + (b - a) * t); }
    static inline ImVec2 Lerp(const ImVec2& a, const ImVec2& b, float t) { return {a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t}; }
    static inline ImVec2 Lerp(const ImVec2& a, const ImVec2& b, const ImVec2& t) { return {a.x + (b.x - a.x) * t.x, a.y + (b.y - a.y) * t.y}; }
    static inline ImVec4 Lerp(const ImVec4& a, const ImVec4& b, float t) { return {a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t}; }


    static void LoadDefaultImGuiStyle() {
        auto colors = ImGui::GetStyle().Colors;

        colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.8f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.53f, 0.53f, 0.53f, 0.48f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.42f, 0.42f, 0.42f, 0.80f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 1.00f, 0.00f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.80f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.55f, 0.55f, 0.55f, 0.38f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.59f, 0.59f, 0.59f, 0.80f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.63f, 0.63f, 0.63f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.55f, 0.55f, 0.55f, 0.38f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.59f, 0.59f, 0.59f, 0.80f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.63f, 0.63f, 0.63f, 1.00f);
        colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors[ImGuiCol_Tab] = Lerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f);
        colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
        colors[ImGuiCol_TabActive] = Lerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
        colors[ImGuiCol_TabUnfocused] = Lerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
        colors[ImGuiCol_TabUnfocusedActive] = Lerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.63f, 0.63f, 0.63f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

        auto& style = ImGui::GetStyle();
        style.FrameRounding = 8.0f;
        style.WindowRounding = 10.0f;
        style.ScrollbarRounding = 8.0f;
        style.PopupRounding = 8.0f;
        style.GrabRounding = 10.0f;
    }

    void App::run() {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8.0;

        updateDisplaySize();
        setup();

        window.create(sf::VideoMode({ width, height }), title, sf::Style::Default, settings);
        window.setFramerateLimit(60);
        auto pngData = decodeBase64(CPP_LOGO_BASE64);
        sf::Image icon;
        if (icon.loadFromMemory(pngData.data(), pngData.size())) {
            window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        }

        if (!ImGui::SFML::Init(window)) {
            throw std::runtime_error("[cppgfx]: Failed to initialize ImGui");
        }
        LoadDefaultImGuiStyle();

        ImFontConfig font_cfg;
        font_cfg.FontDataOwnedByAtlas = false;
        ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)ROBOTO_MEDIUM_DATA, ROBOTO_MEDIUM_SIZE, 18.0f, &font_cfg);

        if (!ImGui::SFML::UpdateFontTexture()) {
            throw std::runtime_error("[cppgfx]: Failed to update ImGui font texture");
        }
        ImGui::GetIO().FontDefault = ImGui::GetIO().Fonts->Fonts.back();

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
            mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right);

            // Handle events
            sf::Event event {};
            while (window.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(window, event);
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
            ImGui::SFML::Update(window, m_frametimeClock.restart());
            window.clear(m_defaultBackgroundColor);
            stroke(0, 0, 0);
            strokeWeight(2);
            fill(255, 255, 255);
            update();
            ImGui::SFML::Render(window);

            // Display the window
            window.display();

            // Post update
            frameCount++;
        }

        // Call the user defined cleanup
        cleanup();

        ImGui::SFML::Shutdown();
    }


    // =======================================
    // =====           Private        ========
    // =======================================

    void App::updateDisplaySize() {
        displayWidth = sf::VideoMode::getDesktopMode().width;
        displayHeight = sf::VideoMode::getDesktopMode().height;
    }

} // namespace cppgfx