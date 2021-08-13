//
//  Timer.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 28.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include <SFML/Graphics.hpp>

// It's a timer...
class Timer {
private:
    sf::Time elapsedTime;
    sf::Clock clock;
    
    bool active;
public:
    Timer() { elapsedTime = sf::Time::Zero; };
    ~Timer() {};
    
    void start() { clock.restart(); elapsedTime = sf::Time::Zero; active = true; }
    void stop() { if (active) elapsedTime = clock.getElapsedTime(); active = false; };
    sf::Time getElapsedTime() { if (active) return clock.getElapsedTime(); else return elapsedTime; };
};
