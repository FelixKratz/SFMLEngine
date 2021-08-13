//
//  MovableView.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 30.08.20.
//  Copyright © 2020 fk. All rights reserved.
//

#include "MovableView.hpp"
#include "../Backbone/WindowRenderer.hpp"

void View::update(sf::Time deltaTime) {
    Movable::update(deltaTime);
    sf::View::setCenter(Movable::getPosition());
    sf::View::setRotation(Movable::getRotation());
    _renderer->setView(getSfView());
}

void View::setCenter(sf::Vector2f center) {
    sf::View::setCenter(center);
    Movable::setPosition(center);
}
