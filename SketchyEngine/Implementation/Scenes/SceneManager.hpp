//
//  SceneManager.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include "MainMenu.hpp"
#include "GameScreen.hpp"

class WindowRenderer;

class SceneManager {
    MainMenu::MainMenu mainMenu;
    GameScreen::GameScreen gameScreen;
public:
    Scene* get(std::string scene);
    SceneManager(WindowRenderer* _windowRenderer) : mainMenu(_windowRenderer), gameScreen(_windowRenderer) {};
    
    Scene* load(std::string scene);
    void load(Scene* _scene) { if (_scene != nullptr) _scene->load(); }
    void unload(std::string scene) { get(scene)->unload(); }
    void unload(Scene* _scene) { _scene->unload(); }
};
