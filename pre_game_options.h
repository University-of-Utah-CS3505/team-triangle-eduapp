#ifndef PRE_GAME_OPTIONS_H
#define PRE_GAME_OPTIONS_H

#include <QDialog>
#include <optional>
#include <tuple>

namespace Ui {
class pre_game_options;
}

struct launch_options {
    std::string font_name;
    std::pair<int, int> resolution;
    bool fullscreen;
};

class pre_game_options : public QDialog {
    Q_OBJECT

public:
    explicit pre_game_options(QWidget* parent = nullptr);
    ~pre_game_options();

    std::optional<launch_options> get_options();

private:
    Ui::pre_game_options* _ui;
    std::optional<launch_options> _options;
};

#endif // PRE_GAME_OPTIONS_H
