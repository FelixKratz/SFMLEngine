//
//  Animation.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 28.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "ObjectStore.hpp"
#include "../Utility/Animation.hpp"
#include "../Pipelines/UpdatePipeline.hpp"
#include "CallbackComponents.hpp"
#include "../Utility/Tileset.hpp"

class Scene;

// TODO: All Animations should have their own callback

// An AnimatedSprite stores and handles animations
class AnimatedSprite : public sf::Sprite, public UpdateProcessor, public CallbackSender {
private:
    // The animations ObjectStore holds a map to as many animation objects as needed
    ObjectStore<Animation<AnimatedSprite>> animations;
    
    // Pointer to the currently active animation
    Animation<AnimatedSprite>* _currentAnimation = nullptr;
    
    // The animationCallback function is called by the Animation after the animation has finished
    void animationCallback(Animation<AnimatedSprite>* _anim);
    void (CallbackTarget::*_completionHandler)(AnimatedSprite* _sender) = nullptr;
public:
    AnimatedSprite() {  };
    
    // Add/Remove animations and setup callbacks
    void addAnimation(std::string name, std::string spriteSet, float refreshRate, float looped, sf::Vector2u splices = sf::Vector2u(32, 32));
    void setCallbackForAnimation(std::string name, void (CallbackTarget::*_handler)(AnimatedSprite* _sender), CallbackTarget* _target);
    void removeAnimation(std::string name) { animations.destroy(name); };
    
    // Start animation with name
    void start(std::string name);
    // Stop active animation
    void stop();
    
    // Update function, called by the UpdatePipeline
    virtual void process(int elapsedTimeInMircoseconds) override;
};
