//
//  Clickable.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 01.12.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Input/InputEvents.hpp"
#include "CallbackComponents.hpp"
#include "../Pipelines/EventPipeline.hpp"

class Clickable : public CallbackSender, public virtual EventProcessor, public virtual sf::Transformable {
protected:
    sf::RectangleShape* _boundingShape = nullptr;
    sf::FloatRect boundingRectangle;
    void (CallbackTarget::*_callback)(Clickable* _sender) = nullptr;
    bool mouseOver = false;
public:
    Clickable() : _callback(nullptr) { };
    bool isMouseOver() { return mouseOver; };
    void setBoundingShape(sf::RectangleShape* _shape) { _boundingShape = _shape; };
    void setBoundingRect(sf::FloatRect boundingRect) { boundingRectangle = boundingRect; };
    sf::FloatRect getBoundingRect() { return boundingRectangle; };
    
    template <class Type, class CallbackArg>
    void setCallback(void (Type::*callback)(CallbackArg* _callbackArg), CallbackTarget* _target) {
        _callback = transformCallback(callback);
        setCallbackTarget(_target);
    };
    
    void triggerClickCallback(CallbackTarget* _target);
    virtual void process(Input::State* _inputState) override;
    virtual bool clicked(CallbackTarget* _target) = 0;
    virtual void dragged(CallbackTarget* _target) = 0;
    virtual void mouseEntered(CallbackTarget* _target) = 0;
    virtual void mouseLeft(CallbackTarget* _target) = 0;
};
