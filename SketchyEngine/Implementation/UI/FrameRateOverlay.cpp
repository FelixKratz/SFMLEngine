//
//  FrameRateOverlay.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 12.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#include "FrameRateOverlay.hpp"
#include "../../Engine/Backbone/WindowRenderer.hpp"

namespace FrameRateOverlay {
    void FrameRateOverlay::init() {
        UI::init();
        
        fpsLabel.setText("");
        fpsLabel.setFontSize(30);
        fpsLabel.setColor(sf::Color::Magenta);
        fpsLabel.setPosition(sf::Vector2f(10, 10));
        clock.restart();
        show = true;
    }

    void FrameRateOverlay::processEvent(sf::Event *event) {
        if (event->type == event->KeyPressed && event->key.code == sf::Keyboard::F3) {
            show = !show;
        }
        _renderer->pipeEvent(event);
    }

    void FrameRateOverlay::draw() {
        counter++;
        
        if (clock.getElapsedTime().asSeconds() >= 1) {
            int time = (int)clock.getElapsedTime().asMicroseconds();
            FPS = (double)counter / (double)time * 1e6 + 0.5;
            counter = 0;
            clock.restart();
        }
        if (show && initialized) {
            fpsLabel.getText()->setString(std::to_string(FPS));
            _renderer->draw(fpsLabel);
        }
    }
}
