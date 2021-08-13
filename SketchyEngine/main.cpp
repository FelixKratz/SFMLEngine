//
//  main.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#include "Engine/Backbone/RenderLoop.hpp"

int main(int, char const**) {
    RenderLoop loop(sf::VideoMode(1440, 900), "Development Build");
    loop.loadScene("Main Menu");
    loop.start();
    return EXIT_SUCCESS;
}
