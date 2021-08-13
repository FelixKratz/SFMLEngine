//
//  SettingsMenu.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 04.01.20.
//  Copyright © 2020 fk. All rights reserved.
//

#pragma once
#include "../../Engine/Backbone/UI.hpp"

namespace SettingsMenu {

class SettingsMenu : public UI {
    void buttonBackEvent(Clickable* _clickable);
public:
    SettingsMenu(WindowRenderer* _renderer) : UI(_renderer) { };
    
    void init() override;
    void unload() override{ UI::unload(); show = false; };
    void resize() override;
};
}
