//
//  StaticAssetManager.cpp
//  StrategyGame
//
//  Created by Felix on 08.10.19.
//  Copyright © 2019 fk. All rights reserved.
//

#include "StaticAssetManager.hpp"
#include "../Backbone/WindowRenderer.hpp"

sf::Vector2f SAM::renderWindowSize(WindowRenderer* _renderer) {
    return _renderer->getRenderWindow()->getView().getSize();
}

void SAM::setPosition(sf::Transformable* _object, sf::Vector2f position) {
    _object->setPosition(position);
}

void SAM::setPosition(sf::Transformable* _object, float x, float y) {
    setPosition(_object, sf::Vector2f(x, y));
}

void SAM::setSize(sf::Sprite* _object, sf::Vector2f size) {
    setSize(_object, size.x, size.y);
}

void SAM::setSize(sf::Sprite* _object, float x, float y) {
    sf::Vector2f oldScale = _object->getScale();
    sf::Vector2f oldSize = sf::Vector2f(_object->getGlobalBounds().width, _object->getGlobalBounds().height);
    sf::Vector2f realSize = sf::Vector2f( oldSize.x / oldScale.x, oldSize.y / oldScale.y );
    
    sf::Vector2f newScale = sf::Vector2f( x / realSize.x, y / realSize.y );
    
    // Conserve the aspect ratio, when only one dimension is given:
    if (x == 0)
        newScale.x = newScale.y;
    if (y == 0)
        newScale.y = newScale.x;
    
    _object->setScale(newScale);
}

void SAM::loadSprite(sf::Sprite* _sprite, sf::Texture* _texture, std::string filename) {
    loadTexture(_texture, filename);
    _sprite->setTexture(*_texture);
}

void SAM::loadTexture(sf::Texture* _texture, std::string filename) {
    _texture->loadFromFile(resourcePath() + filename);
}

void SAM::loadText(sf::Text* _text, sf::Font* _font, std::string s_text, unsigned int size, sf::Color color, std::string s_font) {
    _font->loadFromFile(resourcePath() + s_font);
    _text->setFont(*_font);
    _text->setFillColor(color);
    _text->setString(s_text);
    _text->setCharacterSize(size);
}
