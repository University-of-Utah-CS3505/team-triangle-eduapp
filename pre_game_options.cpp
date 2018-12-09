#include "pre_game_options.h"
#include "ui_pre_game_options.h"
#include <iostream>

const std::pair<int, int> resolutions[] = {{1920, 1080}, {1280, 720}};

pre_game_options::pre_game_options(QWidget* parent)
    : QDialog(parent, Qt::WindowSystemMenuHint), _ui(new Ui::pre_game_options) {
    setWindowModality(Qt::WindowModality::ApplicationModal);
    _ui->setupUi(this);
    // options are default constructed to null so no need to handle reject case
    connect(_ui->finish_buttons, &QDialogButtonBox::accepted, [this] {
        _options.emplace(launch_options{
                resolutions[_ui->resolution->currentIndex()],
                _ui->is_fullscreen->checkState() == Qt::CheckState::Checked});
    });
}

pre_game_options::~pre_game_options() { delete _ui; }

std::optional<launch_options> pre_game_options::get_options() {
    return _options;
}
