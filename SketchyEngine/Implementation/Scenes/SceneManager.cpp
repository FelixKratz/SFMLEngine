//
//  SceneManager.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#include "SceneManager.hpp"

Scene* SceneManager::get(std::string scene) {
    if (scene == "Main Menu")
        return &mainMenu;
    if (scene == "Game Screen")
        return &gameScreen;
    else
        return nullptr;
}

Scene* SceneManager::load(std::string scene) {
    Scene* _scene = get(scene);
    if (_scene != nullptr)
        return _scene->load();
    return _scene;
}
