//
//  AssetManager.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Utility/ResourcePath.hpp"
#include "../Objects/Objects.hpp"
#include "StaticAssetManager.hpp"

class WindowRenderer;

// Dynamic Asset Manager
namespace DAM {
    // Every Scene is a dynamic asset manager
    class AssetManager {
    protected:
        // The dynamic asset manager has knowledge of the Window and is able to resolve
        // relative sizes and positions
        WindowRenderer* _renderer = nullptr;
        // All objects loaded through the dynamic asset manager are stored in the Objects library
        Objects objects;
    public:
        AssetManager(WindowRenderer* _renderer) : _renderer(_renderer) {};
    
        sf::Sprite* loadSprite(std::string filename, std::string name);
        sf::Music* loadMusic(std::string filename, std::string name);
        sf::Text* loadText(std::string name, std::string s_text, unsigned int size, sf::Color color = sf::Color::Black, std::string font = "sansation.ttf");
    
        // Relative Size and Position Interfaces
        void setSize(sf::Sprite* _object, std::string xy_percent);
        void setPosition(sf::Transformable* _object, std::string xy_percent);
        sf::Vector2f transformRelativeToAbsolute(std::string xy_percent);
        sf::Vector2f renderWindowSize();
    };
}

