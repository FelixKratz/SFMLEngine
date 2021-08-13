//
//  Animation.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 06.10.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "Timer.hpp"
#include "../Manager/StaticAssetManager.hpp"

// Simple Animation Handler
template <class AnimatedObject>
class Animation {
private:
    sf::Texture texture;
    std::vector<sf::IntRect> textureRects;
    float refreshRate;
    bool looped;
    
    // Completion Handler for the Animation
    void (AnimatedObject::*_completionHandler)(Animation* _sender) = nullptr;
    AnimatedObject* _targetObject;
    
    unsigned int currentTextureRect = 0;
    Timer timer;
    bool active;
public:
    
    // Load Animation from file
    void loadAnimation(std::string filename, float refresh_rate, float loop,  sf::Vector2u splices);
    // Define Completion Handler
    void setCompletionHandler(void (AnimatedObject::*_handler)(Animation* _sender), AnimatedObject* _target);
    
    // Start the animation
    void start(sf::Sprite* _sprite);
    // Stop the animation
    void stop();
    
    void update(sf::Sprite* _sprite);
};

template <class AnimatedObject>
void Animation<AnimatedObject>::loadAnimation(std::string filename, float refresh_rate, float loop,  sf::Vector2u splices) {
    refreshRate = refresh_rate;
    looped = loop;
    SAM::loadTexture(&texture, filename);
    if (splices.x == 0 && splices.y == 0) return;
    for (int j = 0; j < texture.getSize().y / splices.y; j++) {
        for (int i = 0; i < texture.getSize().x / splices.x; i++) {
            textureRects.push_back(sf::IntRect(i*splices.x , j*splices.y, splices.x, splices.y));
        }
    }
}

template <class AnimatedObject>
void Animation<AnimatedObject>::setCompletionHandler(void (AnimatedObject::*_handler)(Animation* _sender), AnimatedObject* _target) {
    _completionHandler = _handler;
    _targetObject = _target;
};

template <class AnimatedObject>
void Animation<AnimatedObject>::start(sf::Sprite* _sprite) {
    timer.start();
    active = true;
    _sprite->setTexture(texture);
    update(_sprite);
}

template <class AnimatedObject>
void Animation<AnimatedObject>::stop() {
    timer.stop();
    active = false;
}

template <class AnimatedObject>
void Animation<AnimatedObject>::update(sf::Sprite* _sprite) {
    if (textureRects.size() == 0) return;
    float time = timer.getElapsedTime().asSeconds();
    int index = time * refreshRate;
    if (index < textureRects.size()) { _sprite->setTextureRect(textureRects[index]); }
    else if (looped && active) {
        timer.start();
        update(_sprite);
    }
    else if (!looped && active && _completionHandler != nullptr && _targetObject != nullptr) {
        (_targetObject->*_completionHandler)(this);
        active = false;
    }
    else active = false;
}
