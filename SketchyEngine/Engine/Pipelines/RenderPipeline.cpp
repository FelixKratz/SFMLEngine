//
//  RenderPipeline.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 14.09.20.
//  Copyright © 2020 fk. All rights reserved.
//

#include "RenderPipeline.hpp"
#include "../Backbone/WindowRenderer.hpp"

void RenderPipeline::draw(WindowRenderer* _renderer) const {
    for (auto _group : sortedGroupList)
        for (auto _target : *(_group->getTargets()))
            _renderer->draw(_target);
}

void RenderPipeline::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto _group : sortedGroupList)
        for (auto _target : *(_group->getTargets()))
            target.draw(*_target, states);
}
