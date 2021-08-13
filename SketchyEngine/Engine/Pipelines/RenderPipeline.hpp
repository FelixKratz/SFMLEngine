//
//  RenderPipeline.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.20.
//  Copyright © 2020 fk. All rights reserved.
//

#pragma once
#include "Pipeline.hpp"
#include <SFML/Graphics.hpp>
#include "../Objects/ObjectStore.hpp"

class WindowRenderer;

// TODO: Is it possible to do the draw call in the default process function? => more flexible

// The RenderPipeline is used to draw all Drawable objects, sorted by a layering system
// Every Scene object has its own RenderPipeline
class RenderPipeline : public Pipeline<sf::Drawable> {
public:
    // Override the process function because sf::Drawable can not process
    template <class ProcessInput>
    void process(ProcessInput processInput) {};
    
    // Define the specialized task for this pipeline
    void draw(WindowRenderer* _renderer) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
