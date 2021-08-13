//
//  MouseEvents.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 09.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#include "InputEvents.hpp"
#include <iostream>

bool Mouse::update(sf::Event* event) {
    if (isDragging && leftButton.gotReleased) isDragging = false;
    didChange = false;
    
    isMouseEvent = false;
    // Mouse Button Presses
    if (event->type == event->MouseButtonPressed)
    {
        if (event->mouseButton.button == sf::Mouse::Button::Left) {
            if (!leftButton.pressed)
                didChange = true;
            leftButton.pressed = true;
        }
        
        if (event->mouseButton.button == sf::Mouse::Button::Middle)
            if (!middleButton.pressed)
                didChange = true;
            middleButton.pressed = true;
        
        if (event->mouseButton.button == sf::Mouse::Button::Right)
            if (!rightButton.pressed)
                didChange = true;
            rightButton.pressed = true;
        
        isMouseEvent = true;
    }
    
    clearStates();

    // Mouse Button Releases
    if (event->type == event->MouseButtonReleased)
    {
        if (event->mouseButton.button == sf::Mouse::Button::Left) {
            leftButton.pressed = false;
            leftButton.gotReleased = true;
        }
        
        if (event->mouseButton.button == sf::Mouse::Button::Middle) {
            middleButton.pressed = false;
            middleButton.gotReleased = true;
        }
        
        if (event->mouseButton.button == sf::Mouse::Button::Right) {
            rightButton.pressed = false;
            rightButton.gotReleased = true;
        }
        
        isMouseEvent = true;
        isDragging = false;
        didChange = true;
    }
    
    // Mouse Moved
    if (event->type == event->MouseMoved) {
        mouseMoved = true;
        isMouseEvent = true;
        didChange = true;
        
        if (leftButton.pressed) isDragging = true;
        
        lastPosition = currentPosition;
        pixelPos = sf::Mouse::getPosition(*_window);
        currentPosition = _window->mapPixelToCoords(pixelPos);
        deltaPosition = currentPosition - lastPosition;
    }
    
    // Mouse Scrolled
    if (event->type == event->MouseWheelScrolled) {
        didChange = true;
        isMouseEvent = true;
        mouseScrolled = true;
        scrollDelta = event->mouseWheelScroll.delta;
    }
    
    // Check if ANY Button has been pressed
    buttonPressed = false;
    buttonReleased = false;
    
    for (auto i : buttons) {
        if (i->pressed) { buttonPressed = true; break; }
        if (i->gotReleased) { buttonReleased = true; break; }
    }
    
    return didChange;
}

void Mouse::clearStates() {
    mouseMoved = false;
    mouseScrolled = false;
    scrollDelta = 0;
    
    for (auto i : buttons) i->gotReleased = false;
}

bool Input::State::update(sf::Event *event) {
    _event = event;
    if (!Mouse::update(_event) && !KeyBoard::update(_event)) {
        return false;
    }
    return true;
}
