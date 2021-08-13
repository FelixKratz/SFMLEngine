//
//  Animation.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 28.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#include "AnimatedSprite.hpp"
#include "../Manager/AssetManager.hpp"

void AnimatedSprite::animationCallback(Animation<AnimatedSprite>* _anim) {
    if (_completionHandler != nullptr && _target != nullptr)
        (_target->*_completionHandler)(this);
}

void AnimatedSprite::addAnimation(std::string name, std::string spriteSet, float refreshRate, float looped, sf::Vector2u splices) {
    Animation<AnimatedSprite>* _anim = animations.create(name);
    _anim->loadAnimation(spriteSet, refreshRate, looped, splices);
}

void AnimatedSprite::setCallbackForAnimation(std::string name, void (CallbackTarget::*_handler)(AnimatedSprite* _sender), CallbackTarget* target) {
    Animation<AnimatedSprite>* _anim = animations.get(name);
    _anim->setCompletionHandler(&AnimatedSprite::animationCallback, this);
    _completionHandler = _handler;
    setCallbackTarget(target);
}

void AnimatedSprite::start(std::string name) {
    Animation<AnimatedSprite>* _anim = animations.get(name);
    if (_currentAnimation != nullptr) _currentAnimation->stop();
    _currentAnimation = _anim;
    _anim->start(this);
}

void AnimatedSprite::stop() {
    _currentAnimation->stop();
    _currentAnimation = nullptr;
}

void AnimatedSprite::process(int elapsedTimeInMircoseconds) {
    if (_currentAnimation != nullptr)
        _currentAnimation->update(this);
}
