
#include "cppgfx/cppgfx.hpp"

// Do not write global variables here.
// Use your application class in order to avoid lifetime issues.

// This is your application class which contains all variables and functions
class App : public cppgfx::App {
public:

    // Place all your variables here
    int k = 1;

    // This function is called once at the beginning of the program
    void setup() override {
        size(1024, 768);
        setTitle("cppfx: Simple example");
    }

    // This function is called repeatedly until the program is terminated
    void update() override {
        ImGui::SliderInt("k", &k, 1, 1000000, nullptr, ImGuiSliderFlags_Logarithmic);

        double sum = 1;
        size_t counter = 0;
        for (int n = 3; n < k; n += 2) {
            if (counter % 2 == 0) {
                sum -= 1.0 / n;
            } else {
                sum += 1.0 / n;
            }
            counter++;
        }
        println("Sum * 4: {}", sum * 4);
//        ImGui::ShowDemoWindow();
//        stroke(255, 0, 0);
//        strokeWeight(10);
//        stroke(255, 0, 0);
//        vector(sin(second() / 60.0 * 2 * PI) * 200, -cos(second() / 60.0 * 2 * PI) * 200, width / 2, height / 2);
//        stroke(0, 255, 0);
//        vector(sin(minute() / 60.0 * 2 * PI) * 200, -cos(minute() / 60.0 * 2 * PI) * 200, width / 2, height / 2);
//        stroke(0, 0, 255);
//        vector(sin(hour() / 12.0 * 2 * PI) * 200, -cos(hour() / 12.0 * 2 * PI) * 200, width / 2, height / 2);
//        println("Mouse: {}, {}", mouseX, mouseY);
    }
};

// This is the entry point of the program
// Do not touch this function unless you know what you are doing
int main() {
    App app;
    app.run();
}