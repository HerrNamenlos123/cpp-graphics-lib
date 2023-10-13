
#include "cppgfx.hpp"

// Do not write global variables here.
// Use your application class in order to avoid lifetime issues.

// This is your application class which contains all variables and functions
class App : public cppgfx::App {
public:

    // Place all your variables here


    // This function is called once at the beginning of the program
    void setup() override {
        size(1024, 768);
        setTitle("cppfx: Simple example");
    }

    // This function is called repeatedly until the program is terminated
    void update() override {
//        stroke(255, 0, 0);
//        strokeWeight(10);
        rectMode(RectMode::Corners);
        rect(100, 100, mouseX, mouseY);
        println("Mouse: {}, {}", mouseX, mouseY);
    }
};

// This is the true entry point of the program
// Do not touch this function unless you know what you are doing
int main() {
    App app;
    app.run();
}