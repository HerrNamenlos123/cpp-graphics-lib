# cppgfx

<img src="assets/cpp_logo.png" alt="cppgfx logo" align="right" width=30%>

A simple educational C++ graphics library inspired by the Processing ecosystem

The goal of this library is to provide a simple programming environment for students, where they can learn programming while developing interesting graphics programs instead of boring console applications.

The API is inspired by [Processing](https://processing.org/), although it is not a port.

Students can either write programs in C++ to have the full potential at their fingertips, or they can choose pure C, if they want to learn the language without accidentally using C++ features.

## Documentation/Reference 📃

You can find the documentation and reference at  
https://herrnamenlos123.github.io/cppgfx/

## Portability/Compatibility 📌

This library is written in C++17. It is written to be cross-platform and will work equivalently on all supported platforms. 

### Supported platforms

 - Microsoft Windows 
   - Developed and tested on Windows 11
   - Older versions might work but are untested
 - Linux 
   - Developed and tested on Ubuntu 20.04
   - Other distributions might work but are untested

Any other platforms (such as MacOS, etc) are not officially supported. Due to the libraries used it should build on pretty much any platform, so feel free to test the library on any platform and create an issue if things do not work out.

### Supported compilers

 - MSVC (VS 2022)
 - MinGW
 - gcc 9

Any other compilers will probably work too, but are not officially tested. Feel free to test the library with any compiler and create an issue if things do not work out.

## How to use 💡

Please check the documentation linked above for instructions.  
You will want to visit [The cppgfx example project template](https://github.com/herrnamenlos123/cppgfx-template).

## Building 🛠️

If you are on Linux, you must first install all prerequisites.

Linux:
```bash
sudo apt-get update && sudo apt-get install -y libgl1-mesa-dev libflac-dev libogg-dev libvorbis-dev xorg libfreetype-dev libxrandr-dev libopenal-dev libudev-dev doxygen
```

### Building documentation

```bash
pip install sphinx sphinx_rtd_theme breathe exhale
```

## License 📃

This library is distributed under the MIT license. This means you are free to use it for whatever you like.
This library is distributed without any warranty whatsoever.

## Support 💪

I do all of my projects in my free time and I do not get any money for that. I just like what I do, do it for myself and want to share it so that others can benefit too.

I like to drink beer and any support is greatly apprechiated :)

<a href="https://www.buymeacoffee.com/herrnamenlos123"><img src="https://img.buymeacoffee.com/button-api/?text=Buy me a beer&emoji=🍺&slug=herrnamenlos123&button_colour=FFDD00&font_colour=000000&font_family=Lato&outline_colour=000000&coffee_colour=ffffff" /></a>
