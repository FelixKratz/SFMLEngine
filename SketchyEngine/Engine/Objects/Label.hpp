//
//  Label.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 03.04.20.
//  Copyright © 2020 fk. All rights reserved.
//

#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Movable.hpp"
#include "../Manager/StaticAssetManager.hpp"

class Label : public sf::Drawable, virtual public Movable {
protected:
    // Default Text Mode is the "centered" mode
    char mode[2] = {'c', 'c'};
    sf::Font font;
    sf::Text text;
    sf::Color color = sf::Color::Black;
    std::string fontPath = "sansation.ttf";
    
    sf::Text* initialize(std::string s_text, unsigned int size);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(text, states);
    }
    
    void updateOrigin();
public:
    Label() { initialize("", 20); };
    void setText(sf::Text* _text) { text = *_text; updateOrigin(); };
    
    sf::Text* getText() { return &text; }
    void setText(std::string s_text) { text.setString(s_text); updateOrigin(); }
    void setFontSize(int size) { text.setCharacterSize(size); updateOrigin(); }
    void setColor(sf::Color color) { text.setFillColor(color); }
    
    void setMode(char h_align, char v_align = 'c') { mode[0] = h_align; mode[1] = v_align; updateOrigin(); };
};
