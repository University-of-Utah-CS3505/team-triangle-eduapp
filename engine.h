#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <functional>
#include <game_state.h>
#include <memory>
#include <pre_game_options.h>

using event_handle = std::shared_ptr<std::function<bool(sf::Event)>>;

class engine {
public:
    engine(launch_options);

    event_handle add_event_listener(sf::Event::EventType,
                                    std::function<bool(sf::Event)> listener);

    sf::RenderWindow& window();

    void run();

    const sf::Texture& load_texture(const std::string& path);

    const launch_options& options();

private:
    std::unordered_map<
            sf::Event::EventType,
            std::vector<std::weak_ptr<std::function<bool(sf::Event)>>>>
            _event_handlers;
    sf::RenderWindow _window;
    event_handle _esc_quit;
    event_handle _close_quit;
    std::unique_ptr<game_state> _state;
    std::unordered_map<std::string, sf::Texture> _texture_cache;
    launch_options _options;
};

#endif // ENGINE_H
