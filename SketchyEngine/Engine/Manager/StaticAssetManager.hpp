//
//  StaticAssetManager.hpp
//  StrategyGame
//
//  Created by Felix on 08.10.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifndef StaticAssetManager_hpp
#define StaticAssetManager_hpp

class WindowRenderer;

// The Static Asset Manager is mainly used to load assets and set absolute value positions and sizes
namespace SAM {
    void loadSprite(sf::Sprite* _sprite, sf::Texture* _texture, std::string filename);
    void loadTexture(sf::Texture* _texture, std::string filename);
    void loadText(sf::Text* _text, sf::Font* _font, std::string s_text, unsigned int size, sf::Color color, std::string s_font);

    // Absolute position and size interface
    void setPosition(sf::Transformable* _object, sf::Vector2f position);
    void setPosition(sf::Transformable* _object, float x, float y);
    void setSize(sf::Sprite* _object, sf::Vector2f size);
    void setSize(sf::Sprite* _object, float x, float y);
    sf::Vector2f renderWindowSize(WindowRenderer* _renderer);
}

#endif
