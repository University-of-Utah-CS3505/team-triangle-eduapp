#include "engine.h"
#include "game_state.h"
#include "gameplay.h"
#include "level_menu.h"
#include "main_menu.h"
#include "pre_game_options.h"
#include <QApplication>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <functional>
#include <memory>
#include <thread>
#include <vector>

std::optional<launch_options> launch_dialog(int argc, char** argv) {
    // take that qt
    // you're not polluting my whole program today
    auto qapp = QApplication(argc, argv);
    auto option_dialog = pre_game_options();
    option_dialog.exec();
    return option_dialog.get_options();
}

int main(int argc, char** argv) {
    const auto options = launch_dialog(argc, argv);
    // do we set a global config here?
    if (!options) {
        return 0;
    }

    auto eng = engine(*options);
    eng.run();

    return EXIT_SUCCESS;
}
