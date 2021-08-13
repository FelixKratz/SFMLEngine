//
//  Button.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 08.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "InputEvents.hpp"
#include "../Objects/ObjectStore.hpp"
#include "../Objects/Clickable.hpp"
#include "../Objects/Movable.hpp"
#include "../Objects/Label.hpp"

class Scene;

class Button : public Clickable, virtual public Movable, public Label {
private:
    sf::Texture texture;
    ObjectStore<sf::Sprite> sprites;
    sf::Sprite* _activeSprite = nullptr;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        Label::draw(target, states);
        states.transform *= getTransform();
        if (_activeSprite != nullptr)
            target.draw(*_activeSprite, states);
    }
public:
    Button() {};
    
    void activate() { setBoundingRect(text.getGlobalBounds()); };
    virtual bool clicked(CallbackTarget* _target) override { return false; };
    virtual void dragged(CallbackTarget* _target) override { };
    virtual void mouseEntered(CallbackTarget* _target) override { };
    virtual void mouseLeft(CallbackTarget* _target) override { };
    sf::Sprite* setSprite(std::string sprite);
    sf::Sprite* getSprite() { return _activeSprite; };
};
