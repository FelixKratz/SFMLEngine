//
//  SettingsMenu.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 04.01.20.
//  Copyright © 2020 fk. All rights reserved.
//

#include "SettingsMenu.hpp"
#include "../../Engine/Backbone/WindowRenderer.hpp"

namespace SettingsMenu {

void SettingsMenu::buttonBackEvent(Clickable* _clickable) {
    _renderer->removeOverlay("Settings Menu");
}

void SettingsMenu::init() {
    UI::init();
    
    Button* _background = objects.buttons.create("Background");
    _background->setSprite("background.png");
    renderPipeline.pushBack(_background);
    
    Button* _button = objects.buttons.create("Back Button");
    _button->setText("Back");
    _button->setFontSize(20);
    _button->setCallback(&SettingsMenu::buttonBackEvent, this);
    eventPipeline.pushBack(_button);
    renderPipeline.pushBack(_button);
    
    show = true;

    resize();
}

void SettingsMenu::resize() {
    Button* _background = objects.buttons.get("Background");
    Button* _backButton = objects.buttons.get("Back Button");
    
    setPosition(_backButton, "50%60%");
    _backButton->activate();
    
    sf::Sprite* _sprite = _background->getSprite();
    setSize(_sprite,"40%80%");
    
    setPosition(_background, "30%10%");
}
}
