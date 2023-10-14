
#include "cppgfx/cppgfx.hpp"

#ifdef _WIN32

#include "Windows.h"
#include "dwmapi.h"

namespace cppgfx {

    void Win32EnableDarkTitleBar(sf::WindowHandle handle, bool darkTitleBar) {
        BOOL useDarkMode = static_cast<BOOL>(darkTitleBar);
        bool const setImmersiveDarkModeSuccess = SUCCEEDED(DwmSetWindowAttribute(
                handle, DWMWINDOWATTRIBUTE::DWMWA_USE_IMMERSIVE_DARK_MODE,
                &useDarkMode, sizeof(useDarkMode)));
        if (!setImmersiveDarkModeSuccess) {
            throw std::runtime_error("Failed to set immersive dark mode on b::window");
        }
    }

}

#endif // _WIN32