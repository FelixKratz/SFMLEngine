//
//  Label.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 03.04.20.
//  Copyright © 2020 fk. All rights reserved.
//

#include "Label.hpp"

sf::Text* Label::initialize(std::string s_text, unsigned int size) {
    SAM::loadText(&text, &font, s_text, size, color, fontPath);
    updateOrigin();
    return &text;
}

void Label::updateOrigin() {
    sf::Vector2f origin;
    switch (mode[0]) {
        case 'l':
            origin = sf::Vector2f(0, text.getLocalBounds().height / 2.f);
            break;
        case 'r':
            origin = sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height / 2.f);
            break;
        case 'c':
            origin = sf::Vector2f(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
            break;
        default:
            break;
    }
    
    switch (mode[1]) {
        case 't':
            origin = sf::Vector2f(origin.x, 0);
            break;
        case 'b':
            origin = sf::Vector2f(origin.x, text.getLocalBounds().height);
            break;
        case 'c':
            origin = sf::Vector2f(origin.x, text.getLocalBounds().height / 2.f);
            break;
        default:
            break;
    }
    
    text.setOrigin(origin);
}
