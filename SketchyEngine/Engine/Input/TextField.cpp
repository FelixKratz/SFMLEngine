//
//  TextField.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 24.04.20.
//  Copyright © 2020 fk. All rights reserved.
//

#include "TextField.hpp"
#include "../Backbone/Scene.hpp"

void TextField::process(Input::State* _inputState) {
    Clickable::process(_inputState);
    if (_target->keyBoardFocus == this) {
        
        // TODO: Redo this with the new KeyBoard Class
        sf::Event* _event = _inputState->getEvent();
        //if (_event == nullptr)
            //return;
        if (_event->type == sf::Event::KeyPressed && (_event->key.code == sf::Keyboard::Key::Left || sf::Keyboard::Key::Right)) {
            sf::Text* _text = getText();
            std::string currText = _text->getString();
            currText.erase(currText.end() - cursorOffset - 1);
            if (_event->key.code == sf::Keyboard::Key::Left)
                moveCursor(1);
            if (_event->key.code == sf::Keyboard::Key::Right)
                moveCursor(-1);
            currText.insert(currText.end() - cursorOffset, '_');
            setText(currText);
            return;
        }
        
        if (_event->type == sf::Event::TextEntered) {
            sf::Text* _text = getText();
            std::string currText = _text->getString();
            currText.erase(currText.end() - cursorOffset - 1);
            sf::Uint32 key = _event->text.unicode;
            if (key >= 128 || key ==  27 || key == 13) return;
            
            if (key == 8) {
                currText.erase(currText.end() - cursorOffset - 1);
                
            }
            else {
                std::string s_key(1, static_cast<char>(key));
                currText.insert(currText.end() - cursorOffset, static_cast<char>(key));
            }
            
            currText.insert(currText.end() - cursorOffset, '_');
            setText(currText);
        }
    }
    
}
