//
//  Movable.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 02.01.20.
//  Copyright © 2020 fk. All rights reserved.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "../Utility/Timer.hpp"
#include "../Pipelines/UpdatePipeline.hpp"

class Movable : public virtual sf::Transformable, public virtual UpdateProcessor {
protected:
    Timer updateTimer;
    Timer targetTimer;
    
    float targetTime = 0;
    float angularVelocity = 0;
    bool rotateWAngVel = false;
    bool accelerated = false;
    bool targeted = false;
    bool active = false;
    
    sf::Vector2f transformAcceleration;
    sf::Vector2f targetVelocity;
    sf::Vector2f transformVelocity;
    
    sf::Vector2f target;
    void activate();
    
    Movable* _parentMovable = nullptr;
    std::vector<Movable*> childMovables;
public:
    void setTarget(sf::Vector2f tar) { target = tar; };
    sf::Vector2f getTarget() { return target; };
    
    void setTransformVelocity(sf::Vector2f velocity) { transformVelocity = velocity; };
    sf::Vector2f getTransformVelocity() { return transformVelocity; };

    void setParentMovable(Movable* _parent) { _parentMovable = _parent; _parent->addChildMovable(this); };
    void addChildMovable(Movable* _child) { childMovables.push_back(_child); };
    
    void setRotation(float angle);
    float getRotation();
    sf::Vector2f derotateVector(sf::Vector2f original);
    
    void rotateAround(sf::Vector2f center, float angle);
    void rotateWithAngularVelocity(float omega);
    void stopRotation() { rotateWAngVel = false; angularVelocity = 0; }
    
    void setPosition(float x, float y) { setPosition(sf::Vector2f(x,y)); };
    void setPosition(sf::Vector2f position);
    
    void setScale(float x, float y) { setScale(sf::Vector2f(x,y)); };
    void setScale(sf::Vector2f scale);
    
    void move(float x, float y) { move(sf::Vector2f(x,y)); };
    void move(sf::Vector2f offset);
    
    void accelerate(sf::Vector2f acceleration);
    void accelerateToVelocityInTime(sf::Vector2f velocity, float time);
    
    void moveWithVelocity(sf::Vector2f dir, float velocity);
    void moveWithVelocity(sf::Vector2f velocity);
    void moveTo(sf::Vector2f to, float velocity);
    
    void update(sf::Time deltaTime);
    virtual void process(int elapsedTimeInMircoseconds) override { update(updateTimer.getElapsedTime()); updateTimer.start(); elapsedTimeInMircoseconds = 0; };
    virtual void update() { update(updateTimer.getElapsedTime()); updateTimer.start(); };
    
    void unload() {
        setPosition(0, 0);
        setRotation(0);
        setScale(1, 1);
        deactivate();
        _parentMovable = nullptr;
        childMovables.clear();
    };
    
    void deactivate();
};
