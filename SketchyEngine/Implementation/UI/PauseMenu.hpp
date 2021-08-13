//
//  PauseMenu.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 10.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include "../../Engine/Backbone/UI.hpp"

namespace PauseMenu {
    class PauseMenu : public UI {
        void buttonBackToMainMenuEvent(Clickable* _clickable);
        void buttonBackEvent(Clickable* _clickable);
    public:
        PauseMenu(WindowRenderer* _renderer) : UI(_renderer) { };
        
        void init() override;
        void unload() override{ UI::unload(); show = false; };
        void processEvent(sf::Event *event) override;
        void resize() override;
    };
}
