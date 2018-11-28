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
#include "level_menu.h"

typedef std::chrono::duration<int, std::ratio<1, 10>> frame_duration;

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
    auto window = sf::RenderWindow(sf::VideoMode(options->resolution.first,
                                                 options->resolution.second),
                                   "Snake Tanks (working title)",
                                   options->fullscreen ? sf::Style::Fullscreen
                                                       : sf::Style::Default);
    auto event_handlers =
            std::map<sf::Event::EventType,
                     std::vector<std::function<bool(sf::Event)>>>();
    event_handlers[sf::Event::EventType::Closed].push_back(
            [&window](sf::Event) {
                window.close();
                return true;
            });
    event_handlers[sf::Event::EventType::KeyPressed].push_back(
            [&window](sf::Event e) {
                if (e.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return true;
                } else {
                    return false;
                }
            });

    auto state = std::unique_ptr<game_state>(std::make_unique<gameplay>(window));
    while (window.isOpen()) {
        auto frame_start = std::chrono::high_resolution_clock::now();
        auto event = sf::Event();
        while (window.pollEvent((event))) {
            for (auto& f : event_handlers[event.type]) {
                if (f(event)) {
                    break;
                }
            }
        }
        state->update(state);

        std::this_thread::sleep_until(frame_start + frame_duration(1));
    }
    return EXIT_SUCCESS;
}
