//
//  FrameRateOverlay.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 12.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include "../../Engine/Backbone/UI.hpp"

namespace FrameRateOverlay {
    class FrameRateOverlay : public UI {
        Label fpsLabel;
        sf::Clock clock;
        int counter = 0;
        double FPS = 0;
    public:
        FrameRateOverlay(WindowRenderer* _renderer) : UI(_renderer) { init(); };
        
        virtual void draw() override;
        void init() override;
        void unload() override { UI::unload(); show = false; };
        void processEvent(sf::Event *event) override;
        void resize() override {};
    };
}
