#include "colormod.h" // namespace Color
#include <iostream>

int main() {
    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier blink(Color::FG_BLINK);
    Color::Modifier blinkRes(Color::FG_BLINK_DEF);

    //Test Sentences
    std::cout << red << "This sentence should be red." << def << std::endl;
    std::cout << blue << "This sentence should be blue." << def << std::endl;
    std::cout << blink << "This sentence should blink." << blinkRes << std::endl;
}