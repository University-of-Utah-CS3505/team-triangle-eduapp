#include "engine.h"
#include "main_menu.h"
#include <memory>
#include <thread>
#include "gameplay.h"

typedef std::chrono::duration<int, std::ratio<1, 60>> frame_duration;

engine::engine(launch_options options)
    : _window(sf::VideoMode(options.resolution.first,
                            options.resolution.second),
              "Snake Tanks (working title)",
              options.fullscreen ? sf::Style::Fullscreen : sf::Style::Default),

      _esc_quit(add_event_listener(sf::Event::EventType::Closed,
                                   [this](sf::Event) {
                                       _window.close();
                                       return true;
                                   })),
      _close_quit(add_event_listener(sf::Event::KeyPressed,
                                     [this](sf::Event e) {
                                         if (e.key.code ==
                                             sf::Keyboard::Escape) {
                                             _window.close();
                                             return true;
                                         } else {

                                             return false;
                                         }
                                     })),
      _state(std::make_unique<gameplay>(*this)) {}

event_handle engine::add_event_listener(
        sf::Event::EventType type, std::function<bool(sf::Event)> listener) {
    auto handle = std::make_shared<std::function<bool(sf::Event)>>(
            std::move(listener));
    _event_handlers[type].push_back(std::weak_ptr(handle));
    return handle;
}

sf::RenderWindow& engine::window() { return _window; }

void engine::run() {
    while (_window.isOpen()) {
        auto frame_start = std::chrono::high_resolution_clock::now();
        auto event = sf::Event();
        while (_window.pollEvent((event))) {
            auto& handlers = _event_handlers[event.type];
            std::remove_if(handlers.begin(), handlers.end(), [](auto weak_ptr) {
                return weak_ptr.expired();
            });
            for (auto& weak_f : handlers) {
                auto f_ptr = weak_f.lock();
                if (f_ptr && (*f_ptr)(event)) {
                    break;
                }
            }
        }

        auto _new_state = _state->update();
        if (_new_state) {
            _state.swap(_new_state);
        }
        _window.display();
        std::this_thread::sleep_until(frame_start + frame_duration(1));
    }
}

const sf::Texture& engine::load_texture(const std::string& path) {
    if (_texture_cache.find(path) == _texture_cache.end()) {
        _texture_cache[path].loadFromFile(path);
    }
    return _texture_cache[path];
}
