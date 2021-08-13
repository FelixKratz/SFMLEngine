//
//  MainCamera.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 31.08.20.
//  Copyright © 2020 fk. All rights reserved.
//

#pragma once
#include "../../Engine/Objects/MovableView.hpp"
#include "../../Engine/Input/InputEvents.hpp"
#include "../../Engine/Pipelines/EventPipeline.hpp"
#include "../../Engine/Pipelines/UpdatePipeline.hpp"

class MainCamera : public virtual EventProcessor, public virtual UpdateProcessor {
public:
    void unload() {  _view->unload(); _view = nullptr; };
    View* _view;
    void setView(View* view) { _view = view; };
    virtual void process(Input::State* _inputState) override;
    virtual void process(int elapsedTimeInMircoseconds) override { _view->process(elapsedTimeInMircoseconds); };
};
