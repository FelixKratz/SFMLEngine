//
//  Game.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.19.
//  Copyright © 2019 fk. All rights reserved.
//
#pragma once

#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../Utility/ResourcePath.hpp"
#include "WindowRenderer.hpp"

class RenderLoop {
private:
    WindowRenderer windowRenderer;
public:
    RenderLoop(sf::VideoMode videoMode, std::string title, int framerate = 60) { init(videoMode, title, framerate); };
    ~RenderLoop() {};
    
    void init(sf::VideoMode videoMode, std::string title, int framerate) { windowRenderer.init(videoMode, title); windowRenderer.setFrameRateCap(framerate); };
    void start();
    void loadScene(std::string sceneName);
};
