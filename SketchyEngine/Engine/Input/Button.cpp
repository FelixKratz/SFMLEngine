//
//  Button.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 08.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#include "Button.hpp"
#include "../Backbone/Scene.hpp"

sf::Sprite* Button::setSprite(std::string s_sprite) {
    sf::Sprite* _sprite;
    if (sprites.get(s_sprite) == nullptr)
        _sprite = sprites.create(s_sprite);
    else
        _sprite = sprites.get(s_sprite);
        
    SAM::loadSprite(_sprite, &texture, s_sprite);
    _activeSprite = _sprite;
    setBoundingRect(_sprite->getGlobalBounds());
    updateOrigin();
    return _activeSprite;
}
