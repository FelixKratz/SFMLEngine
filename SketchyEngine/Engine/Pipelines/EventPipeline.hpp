//
//  EventProcessor.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.20.
//  Copyright © 2020 fk. All rights reserved.
//

#pragma once
#include "Pipeline.hpp"
#include "../Input/InputEvents.hpp"

// TODO: Allow for the removal of an EventProcessor

// All objects that process events should inherit from this class
// Dummy Class at the moment
class EventProcessor : public PipelineProcessor<Input::State*> {
public:
    EventProcessor() {};
};

// Handles the event processing of all EventProcessor objects pushed into it
class EventPipeline : public Pipeline<EventProcessor> {
protected:
    // The EventPipeline contains an Input::State object that holds all input events
    Input::State inputState;
public:
    // Input::State interface
    Input::State* getInputState() { return &inputState; };
    bool updateInputState(sf::Event* _event) { return inputState.update(_event); }
    
    // Additional process function to allow for direct event processing
    void process(sf::Event* _event) { if (updateInputState(_event)) Pipeline<EventProcessor>::process(&inputState); }
};


