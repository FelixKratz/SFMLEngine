//
//  RenderLoop.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#include "RenderLoop.hpp"
#include "WindowRenderer.hpp"
#include "UI.hpp"
#include "Scene.hpp"
#include "../Objects/Objects.hpp"

void RenderLoop::start() {
    sf::Clock clock;
    clock.restart();
    while (windowRenderer.windowOpen())
    {
        windowRenderer.processEvents();
        
        windowRenderer.clearScreen();
        
        // Draw frame
        windowRenderer.drawFrame((int)clock.getElapsedTime().asMicroseconds());
        clock.restart();
        
        // Update the window-
        windowRenderer.displayFrame();
        windowRenderer.updateScenes();
    }
}

void RenderLoop::loadScene(std::string sceneName) {
    windowRenderer.loadScene(sceneName);
}
