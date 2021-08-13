//
//  TextField.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 24.04.20.
//  Copyright © 2020 fk. All rights reserved.
//
#pragma once

#include "../Objects/Label.hpp"
#include "../Objects/Clickable.hpp"

class TextField : public virtual EventProcessor, public Label, public Clickable, virtual public Movable {
    int cursorOffset = 0;
public:
    TextField() {};
    ~TextField() {};
    
    virtual bool clicked(CallbackTarget* _target) override { return false; };
    virtual void dragged(CallbackTarget* _target) override { };
    virtual void mouseEntered(CallbackTarget* _target) override { };
    virtual void mouseLeft(CallbackTarget* _target) override { };
    
    void moveCursor(int dir) { if (cursorOffset + dir >= 0) cursorOffset += dir; };
    
    virtual void process(Input::State* _inputState) override;
};
