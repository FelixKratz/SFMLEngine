//
//  Console.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 24.04.20.
//  Copyright © 2020 fk. All rights reserved.
//

#include "Console.hpp"
#include "../../Engine/Backbone/WindowRenderer.hpp"
#include "../../Engine/Manager/GlobalConsoleHandler.hpp"

namespace Console {
    void Console::init() {
        UI::init();
        
        keyBoardFocus = &input;
        input.setCallbackTarget(this);
        input.setMode('l', 'b');
        input.setColor(sf::Color::Green);
        input.setText("DEV-Console: \n _");
        
        backgroundRect.setOrigin(0, 0);
        backgroundRect.setSize(transformRelativeToAbsolute("100%70%"));
        backgroundRect.setFillColor(sf::Color::Black);
        renderPipeline.pushBack(&backgroundRect);
        renderPipeline.pushBack(&input);
        
        resize();
    }

    void Console::resize() {
        setPosition(&input, "15%50%");
    }

    void Console::processEvent(sf::Event *event) {
        UI::processEvent(event);
        
        if (event->type == event->KeyPressed && event->key.code == sf::Keyboard::Key::Comma) {
            show = !show;
            return;
        }
        if (event->type == event->KeyReleased && event->key.code == sf::Keyboard::Key::Comma) return;
        
        if (event->type == event->KeyPressed && event->key.code == sf::Keyboard::Key::Enter) {
            std::string consoleOutput = input.getText()->getString();
            consoleOutput.pop_back();
            std::vector<std::string> consoleLines;
            tokenize(consoleOutput, '\n', &consoleLines);
            std::string command = consoleLines.back();
            
            std::string response = handleConsoleGlobal(command, _renderer);
            std::stringstream sstream;
            sstream << consoleOutput << "\n" << response << "\n";
            input.setText(sstream.str());
            
            std::cout << "Command: " << command << std::endl;
        }
        
        if (show)
            input.process(eventPipeline.getInputState());
        if (!show)
            _renderer->pipeEvent(event);
    }
}
