//
//  MovableView.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 30.08.20.
//  Copyright © 2020 fk. All rights reserved.
//
#pragma once
#include "Movable.hpp"

class WindowRenderer;

class View : public sf::View, public virtual Movable, public virtual UpdateProcessor {
    WindowRenderer* _renderer;
    using sf::View::View;
    using Movable::Movable;
    
public:
    void setRenderer(WindowRenderer* renderer) { _renderer = renderer; };
    virtual void process(int elapsedTimeInMircoseconds) override { update(updateTimer.getElapsedTime()); updateTimer.start(); };
    void update(sf::Time deltaTime);
    
    void setCenter(float x, float y) { setCenter(sf::Vector2f(x, y)); };
    void setCenter(sf::Vector2f center);
    
    sf::View* getSfView() {
        return (sf::View*)this;
    }
};
