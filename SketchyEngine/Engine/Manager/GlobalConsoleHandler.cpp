//
//  GlobalConsoleHandler.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 26.04.20.
//  Copyright © 2020 fk. All rights reserved.
//

#include "GlobalConsoleHandler.hpp"

std::string handleConsoleGlobal(std::string command, WindowRenderer* _renderer) {
    if (command == "") return "Not a valid command";
    std::vector<std::string> commandParts;
    tokenize(command, ' ', &commandParts);
    if (commandParts.size() == 0) return "> Invalid";
    
    while(commandParts.size() > 0 && commandParts[0] == "") commandParts.erase(commandParts.begin());
    
    if (commandParts[0] == "fps_max")
        if (commandParts.size() > 1) {
            _renderer->setFrameRateCap(std::stoi(commandParts[1]));
            return "> Framerate Cap Set";
        }
    
    if (commandParts[0] == "resolution") {
        if (commandParts.size() > 2) {
            _renderer->setResolution(std::stoi(commandParts[1]), std::stoi(commandParts[2]));
            return "> Resolution Set";
        }
    }
    
    if (commandParts[0] == "fullscreen") {
        if (commandParts.size() > 1) {
            bool activate;
            if (commandParts[1] == "on") activate = true;
            else activate = false;
            
            _renderer->setFullscreen(activate);
            return "> Fullscreen Mode Set";
        }
    }
    
    if (commandParts[0] == "mouse_grab") {
        if (commandParts.size() > 1) {
            bool on;
            if (commandParts[1] == "on") on = true;
            else on = false;
            _renderer->grabMouse(on);
            if (on) return "> Mouse Grabbed";
            else return "> Mouse Released";
        }
    }
    
    if (commandParts[0] == "mouse_show") {
        if (commandParts.size() > 1) {
            bool on;
            if (commandParts[1] == "on") on = true;
            else on = false;
            _renderer->showMouse(on);
            return "> Changed Mouse Visibility";
        }
    }
    
    if (commandParts[0] == "echo") {
        if (commandParts.size() > 1) {
            std::stringstream sstream;
            sstream << "> ";
            for (int i = 1; i < commandParts.size(); i++) {
                sstream << commandParts[i] << " ";
            }
            return sstream.str();
        }
    }
    
    if (commandParts[0] == "quit") {
        exit(0);
    }
    
    return "> Invalid";
}
