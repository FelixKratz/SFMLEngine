//
//  Console.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 24.04.20.
//  Copyright © 2020 fk. All rights reserved.
//

#pragma once
#include "../../Engine/Backbone/UI.hpp"
#include "../../Engine/Utility/Tokenize.hpp"

namespace Console {
    class Console : public UI {
        TextField input;
        sf::RectangleShape backgroundRect;
    public:
        Console(WindowRenderer* _renderer) : UI(_renderer) { };
        
        void init() override;
        void unload() override{ UI::unload(); show = false; };
        void processEvent(sf::Event *event) override;
        void resize() override;
    };
}
