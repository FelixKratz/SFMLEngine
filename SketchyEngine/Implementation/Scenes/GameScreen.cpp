//
//  GameScene.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 08.09.19.
//  Copyright © 2019 fk. All rights reserved.
//
#include "GameScreen.hpp"
#include "../../Engine/Backbone/WindowRenderer.hpp"

namespace GameScreen {
    void GameScreen::init() {
        Scene::init();
        
        _renderer->pushBackOverlay("Pause Menu");
        _renderer->pushBackOverlay("Frame Rate Overlay");
        _renderer->pushBackOverlay("Console");
        
        camera.setView(&view);
        
        // Event Pipeline
        eventPipeline.pushBack(&camera);
        
        // Update Pipeline
        updatePipeline.pushBack(&camera);
        
        // Render Pipeline
        
        
    }

    void GameScreen::unload() {
        Scene::unload();
        camera.unload();
    }
}
