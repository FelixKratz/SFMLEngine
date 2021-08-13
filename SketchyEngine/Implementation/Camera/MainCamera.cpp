//
//  MainCamera.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 31.08.20.
//  Copyright © 2020 fk. All rights reserved.
//

#include "MainCamera.hpp"

void MainCamera::process(Input::State* _inputState) {
    sf::Vector2f positionChange;
    float angularVel = 0;
    
    if (_inputState->KeyBoard::isKeyPressed(sf::Keyboard::W))
        positionChange += sf::Vector2f(0,-1);
    if (_inputState->KeyBoard::isKeyPressed(sf::Keyboard::S))
        positionChange += sf::Vector2f(0,1);
    if (_inputState->KeyBoard::isKeyPressed(sf::Keyboard::A))
        positionChange += sf::Vector2f(-1,0);
    if (_inputState->KeyBoard::isKeyPressed(sf::Keyboard::D))
        positionChange += sf::Vector2f(1,0);
    if (_inputState->KeyBoard::isKeyPressed(sf::Keyboard::Q))
        angularVel = 50.f;
    if (_inputState->KeyBoard::isKeyPressed(sf::Keyboard::E))
        angularVel = -50.f;
    
    _view->moveWithVelocity(_view->derotateVector(positionChange), 50);
    _view->rotateWithAngularVelocity(angularVel);
    if (_inputState->mouseScrolled)
        _view->zoom(1. + _inputState->Mouse::scrollDelta/100.);
}
