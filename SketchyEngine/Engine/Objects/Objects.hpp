//
//  Objects.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 10.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include "ObjectStore.hpp"
#include "../Input/Button.hpp"
#include "AnimatedSprite.hpp"
#include "Movable.hpp"
#include "../Input/TextField.hpp"
#include "MovableView.hpp"

class Objects {
public:
    // Object containers
    ObjectStore<sf::Texture> textures;
    ObjectStore<sf::Sprite> sprites;
    ObjectStore<sf::Music> music;
    ObjectStore<sf::Font> fonts;
    ObjectStore<sf::Text> texts;
    ObjectStore<Button> buttons;
    ObjectStore<AnimatedSprite> animatedSprites;
    
    void clear() {
        textures.clear();
        sprites.clear();
        music.clear();
        fonts.clear();
        texts.clear();
        buttons.clear();
        animatedSprites.clear();
    };
};
