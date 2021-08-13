//
//  PauseMenu.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 10.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#include "PauseMenu.hpp"
#include "../../Engine/Backbone/WindowRenderer.hpp"

namespace PauseMenu {
    void PauseMenu::buttonBackToMainMenuEvent(Clickable* _clickable) {
        _renderer->removeOverlay("Pause Menu");
        _renderer->removeOverlay("Frame Rate Overlay");
        //_renderer->unloadScene("Game Screen");
        show = false;
        _renderer->loadScene("Main Menu");
    }
    
    void PauseMenu::buttonBackEvent(Clickable* _clickable) {
        show = false;
    }
    
    void PauseMenu::init() {
        UI::init();
        
        _activeScene = _renderer->getScene();
        
        sf::Sprite* _pauseMenuBackground = objects.sprites.create("Pause Menu Background");
        renderPipeline.pushBack(_pauseMenuBackground);
        
        Button* _button = objects.buttons.create("Back to Main Menu");
        _button->setCallback(&PauseMenu::buttonBackToMainMenuEvent, this);
        sf::Text* _text = _button->getText();
        
        _button->setText("Back to Main Menu");
        _button->setFontSize(30);
        _button->setColor(sf::Color::Green);
        _text->setOutlineThickness(2);
        renderPipeline.pushBack(_button);
        eventPipeline.pushBack(_button);
        
        _button = objects.buttons.create("Back");
        _button->setCallback(&PauseMenu::buttonBackEvent, this);
        _text = _button->getText();
        _button->setText("Back");
        _button->setFontSize(30);
        _button->setColor(sf::Color::Green);
        _text->setOutlineThickness(2);
        renderPipeline.pushBack(_button);
        eventPipeline.pushBack(_button);
        
        resize();
    }

    void PauseMenu::resize() {
        Button* _button = objects.buttons.get("Back");
        setPosition(_button, "50%40%");
        _button->activate();
        
        _button = objects.buttons.get("Back to Main Menu");
        setPosition(_button, "50%60%");
        _button->activate();
    }
    
    void PauseMenu::processEvent(sf::Event *event) {
        UI::processEvent(event);
        if (!show) _renderer->pipeEvent(event);
        if (event->type == event->KeyPressed && event->key.code == sf::Keyboard::Escape)
            show = !show;
    }
}
