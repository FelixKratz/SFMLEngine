//
//  GameScene.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 08.09.19.
//  Copyright © 2019 fk. All rights reserved.
//
#pragma once
#include "../../Engine/Backbone/Scene.hpp"
#include "../Camera/MainCamera.hpp"

namespace GameScreen {
    class GameScreen : public Scene {
        MainCamera camera;
    public:
        GameScreen(WindowRenderer* _windowRenderer) : Scene(_windowRenderer) {};
        void init() override;
        void resize() override {};
        virtual void unload() override;
    };
}
