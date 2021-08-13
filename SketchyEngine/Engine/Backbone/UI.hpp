//
//  UI.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include "Scene.hpp"

class UI : public Scene {
protected:
    Movable anchor;
    Scene* _activeScene = nullptr;
    bool show = false;
public:
    UI(WindowRenderer* _windowRenderer) : Scene(_windowRenderer) { };
    
    virtual void draw() {
        if (!show || !initialized)
            return;
        anchor.update();
        renderPipeline.draw(_renderer);
    };
    
    virtual void init() { Scene::init(); };

    virtual void unload() { _activeScene = nullptr; anchor.deactivate(); Scene::unload(); };
    
    void setActiveScene(Scene* _scene) { _activeScene = _scene; };
};
