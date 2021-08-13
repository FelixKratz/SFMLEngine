//
//  MouseEvents.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 09.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "../Objects/ObjectStore.hpp"

class MouseButton {
public:
    bool pressed = false;
    bool gotReleased = false;
};

class Mouse {
protected:
    sf::RenderWindow* _window = nullptr;
    
    bool didChange = false;
    
    void init() {buttons.push_back(&leftButton); buttons.push_back(&middleButton); buttons.push_back(&rightButton); };
    void clearStates();
    std::vector<MouseButton*> buttons;
public:
    MouseButton leftButton;
    MouseButton rightButton;
    MouseButton middleButton;
    
    sf::Vector2f currentPosition;
    sf::Vector2i pixelPos;
    sf::Vector2f lastPosition;
    sf::Vector2f deltaPosition;
    
    float scrollDelta = 0;
    
    bool mouseMoved = false;
    bool isMouseEvent = false;
    bool isDragging = false;
    bool buttonPressed = false;
    bool buttonReleased = false;
    bool mouseScrolled = false;
    
    Mouse() { init(); };
    Mouse(sf::Event* _event) { Mouse::update(_event); };
    
    void setWindow(sf::RenderWindow* _win) { _window = _win; };
    
    sf::Vector2f convertToWorld(sf::View* _view) { return _window->mapPixelToCoords(pixelPos, *_view); };
    
    bool update(sf::Event* _event);
};

class KeyBoard : public sf::Keyboard {
    KeyBoard::Key key;
public:
    KeyBoard::Key getKey() { return key; };
    bool update(sf::Event* _event)
    {
        if (_event->KeyPressed || _event->KeyReleased) {
            if (key == _event->key.code)
                return false;
        
            if (_event->KeyPressed || _event->KeyReleased)
                key = _event->key.code;
            return true;
        }
        else {
            key = sf::Keyboard::Unknown;
            return false;
        }
    };
};

namespace Input {
    class State : public Mouse, public KeyBoard {
        sf::Event* _event = nullptr;
    public:
        bool update(sf::Event* event);
        sf::Event* getEvent() { return _event; };
        
        Mouse* getMouseState() { return (Mouse*)this; };
        KeyBoard* getKeyBoardState() { return (KeyBoard*)this; };
    };
}
