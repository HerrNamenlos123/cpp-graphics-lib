
#ifndef CPPGFX_WIN32_HPP
#define CPPGFX_WIN32_HPP

#ifdef _WIN32

#include "SFML/Window.hpp"

namespace cppgfx {

    void EnableDarkTitleBar(sf::WindowHandle handle, bool darkTitleBar);

}

#endif // _WIN32
#endif //CPPGFX_WIN32_HPP