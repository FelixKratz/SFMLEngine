//
//  GlobalConsoleHandler.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 26.04.20.
//  Copyright © 2020 fk. All rights reserved.
//

#pragma once
#include "../Backbone/WindowRenderer.hpp"

// TODO: Make a JSON formatted command list

// Dev-console global events
std::string handleConsoleGlobal(std::string command, WindowRenderer* _renderer);
