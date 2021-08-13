//
//  AssetManager.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#include "AssetManager.hpp"
#include "../Backbone/WindowRenderer.hpp"

sf::Music* DAM::AssetManager::loadMusic(std::string filename, std::string name) {
    sf::Music* _music = objects.music.create(name);
    _music->openFromFile(resourcePath() + filename);
    return _music;
}

sf::Sprite* DAM::AssetManager::loadSprite(std::string filename, std::string name) {
    sf::Texture* _texture = objects.textures.create(name);
    sf::Sprite* _sprite = objects.sprites.create(name);
    SAM::loadSprite(_sprite, _texture, filename);
    return _sprite;
}

sf::Text* DAM::AssetManager::loadText(std::string name, std::string s_text, unsigned int size, sf::Color color, std::string font) {
    sf::Font* _font;
    sf::Text* _text = objects.texts.create(name);
    
    if (objects.fonts.get(font) == nullptr)
        _font = objects.fonts.create(font);
    else
        _font = objects.fonts.get(font);
    
    SAM::loadText(_text, _font, s_text, size, color, font);
    
    return _text;
}

// Asset Size and Position

sf::Vector2f DAM::AssetManager::renderWindowSize() {
    return SAM::renderWindowSize(_renderer);
}

void DAM::AssetManager::setSize(sf::Sprite* _object, std::string xy_percent) {
    sf::Vector2f absolute = transformRelativeToAbsolute(xy_percent);
    SAM::setSize(_object, absolute.x, absolute.y);
}

void DAM::AssetManager::setPosition(sf::Transformable* _object, std::string xy_percent) {
    SAM::setPosition(_object, transformRelativeToAbsolute(xy_percent));
}

sf::Vector2f DAM::AssetManager::transformRelativeToAbsolute(std::string xy_percent) {
    std::string delimiter = "%";

    size_t pos = 0;
    std::string token;
    float x = 0;
    float y = 0;
    int i = 0;
    while ((pos = xy_percent.find(delimiter)) != std::string::npos) {
        token = xy_percent.substr(0, pos);
        if (i == 0) x = std::atof(token.c_str());
        else if (i == 1) y = std::atof(token.c_str());
        else break;
        xy_percent.erase(0, pos + delimiter.length());
        i++;
    }
    
    sf::Vector2f absolute;
    absolute.x =  x / 100. * renderWindowSize().x;
    absolute.y =  y / 100. * renderWindowSize().y;
    
    if (absolute.x == 0) absolute.x = absolute.y;
    if (absolute.y == 0) absolute.y = absolute.x;
    
    return absolute;
}
