//
//  Movable.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 02.01.20.
//  Copyright © 2020 fk. All rights reserved.
//

#include "Movable.hpp"

void Movable::activate() {
    active = true;
    updateTimer.start();
    process(0);
}

void Movable::deactivate() {
    accelerated = false;
    active = false;
    targetTime = 0;
    transformVelocity.x = 0;
    transformVelocity.y = 0;
    transformAcceleration.x = 0;
    transformAcceleration.y = 0;
    target.x = 0;
    target.y = 0;
    targetVelocity.x = 0;
    targetVelocity.y = 0;
    targetTimer.stop();
    updateTimer.stop();
}

void Movable::update(sf::Time deltaTime) {
    if (!active && !rotateWAngVel) return;
    sf::Vector2f transform = deltaTime.asSeconds()*transformVelocity;
    
    if (targeted) {
        sf::Vector2f position = -getTransform().transformPoint(getPosition());
        
        // Check if closer to target after transform, if not -> move directly to target
        if (pow((target - position).x, 2) + pow((target - position).y, 2) >=
            pow((target - position + transform).x, 2) + pow((target - position + transform).y, 2)) {
            if (accelerated) transformVelocity += deltaTime.asSeconds()*transformAcceleration;
            move(transform);
        }
        else
            deactivate();
    }
    else if (active)
        move(transform);
    
    if (rotateWAngVel) {
        float deltaPhi = deltaTime.asSeconds() * angularVelocity;
        setRotation(getRotation() + deltaPhi);
    }
}

void Movable::moveTo(sf::Vector2f to, float velocity) {
    target = to;
    sf::Vector2f position = -getTransform().transformPoint(getPosition());
    float norm = std::sqrt(std::pow((target - position).x, 2) + std::pow((target - position).y,2));
    
    transformVelocity = -velocity / norm * (target - position);
    
    targeted = true;
    activate();
}

void Movable::moveWithVelocity(sf::Vector2f dir, float velocity) {
    float norm = std::sqrt(std::pow((dir).x, 2) + std::pow(dir.y,2));
    if (norm == 0) norm = 1;
    moveWithVelocity(velocity / norm * dir);
}

void Movable::moveWithVelocity(sf::Vector2f velocity) {
    if (transformVelocity == velocity && active) return;
    
    transformVelocity = velocity;
    activate();
}

void Movable::accelerate(sf::Vector2f acceleration) {
    transformAcceleration = acceleration;
    accelerated = true;
    activate();
}

void Movable::accelerateToVelocityInTime(sf::Vector2f velocity, float time) {
    targetVelocity = velocity;
    targetTime = time;
    
    std::cout << "Not working currently" << std::endl;
    activate();
}

void Movable::move(sf::Vector2f offset) {
    sf::Transformable::move(offset);
    for (auto _child : childMovables)
        _child->move(offset);
}

void Movable::setScale(sf::Vector2f scale) {
    sf::Transformable::setScale(scale);
    for (auto _child : childMovables)
        _child->setScale(scale);
}

void Movable::setPosition(sf::Vector2f position) {
    sf::Vector2f origin = getOrigin();
    sf::Transformable::setPosition(position);
    for (auto _child : childMovables) {
        _child->move(position - origin);
    }
}

void Movable::rotateWithAngularVelocity(float omega) {
    if (omega == 0) { stopRotation(); return; }
    rotateWAngVel = true;
    angularVelocity = omega;
}

void Movable::rotateAround(sf::Vector2f center, float angle) {
    sf::Vector2f oldOrigin = getOrigin();
    setOrigin(center);
    move(center - oldOrigin);
    setRotation(angle);
}

sf::Vector2f Movable::derotateVector(sf::Vector2f original) {
    return sf::Vector2f(cos(getRotation()/180. *M_PI) * original.x - sin(getRotation()/180. *M_PI) * original.y, sin(getRotation()/180. *M_PI) * original.x + cos(getRotation()/180. *M_PI) * original.y);
}

void Movable::setRotation(float angle) {
    sf::Transformable::setRotation(angle);
    for (auto _child : childMovables)
        _child->rotateAround(_child->getInverseTransform().transformPoint(getTransform().transformPoint(getOrigin())), angle);
}

float Movable::getRotation() {
    return sf::Transformable::getRotation();
}
