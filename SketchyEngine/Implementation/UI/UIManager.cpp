//
//  UIManager.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 10.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#include "UIManager.hpp"

UI* UIManager::get(std::string ui) {
    if (ui == "Pause Menu")
        return &pauseMenu;
    else if (ui == "Frame Rate Overlay")
        return &frameRateOverlay;
    else if (ui == "Settings Menu")
        return &settingsMenu;
    else if (ui == "Console")
        return &console;
    else
        return nullptr;
}

UI* UIManager::load(std::string ui) {
    UI* _ui = get(ui);
    if (_ui != nullptr)
        _ui->init();
    return _ui;
}

void UIManager::unload(std::string ui) {
    get(ui)->unload();
}
