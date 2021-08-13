//
//  UIManager.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 10.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include "PauseMenu.hpp"
#include "SettingsMenu.hpp"
#include "../../Engine/Backbone/UI.hpp"
#include "FrameRateOverlay.hpp"
#include "Console.hpp"

class WindowRenderer;

class UIManager {
    PauseMenu::PauseMenu pauseMenu;
    SettingsMenu::SettingsMenu settingsMenu;
    FrameRateOverlay::FrameRateOverlay frameRateOverlay;
    Console::Console console;
public:
    UIManager(WindowRenderer* _windowRenderer) : pauseMenu(_windowRenderer), frameRateOverlay(_windowRenderer), settingsMenu(_windowRenderer), console(_windowRenderer) { };
    
    UI* load(std::string ui);
    void unload(std::string ui);
    UI* get(std::string ui);
};
