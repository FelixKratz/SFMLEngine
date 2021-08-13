//
//  Clickable.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 01.12.19.
//  Copyright © 2019 fk. All rights reserved.
//

#include "Clickable.hpp"
#include "../Backbone/Scene.hpp"

void Clickable::triggerClickCallback(CallbackTarget *_target) {
    if (!clicked(_target)) {
        (_target->*_callback)(this);
    }
}

void Clickable::process(Input::State* _inputState) {
    Mouse* _mouseState = _inputState->getMouseState();
    if (_boundingShape != nullptr) {
        if (_boundingShape->getGlobalBounds().contains(getInverseTransform().transformPoint(_mouseState->currentPosition))) {
            if (!mouseOver) mouseEntered(_target);
            mouseOver = true;
        }
        else {
            if (mouseOver) mouseLeft(_target);
            mouseOver = false;
        }
    }
    else {
        if (boundingRectangle.contains(getInverseTransform().transformPoint(_mouseState->currentPosition))) {
            if (!mouseOver) mouseEntered(_target);
            mouseOver = true;
        }
        else {
            if (mouseOver) mouseLeft(_target);
            mouseOver = false;
        }
    }
    
    if (mouseOver && _mouseState->buttonReleased)  {
        if (!clicked(_target) && _callback != nullptr && _target != nullptr)
            (_target->*_callback)(this);
    }
}
