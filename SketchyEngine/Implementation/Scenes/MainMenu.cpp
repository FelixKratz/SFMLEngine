//
//  MainMenu.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#include "MainMenu.hpp"
#include "../../Engine/Backbone/WindowRenderer.hpp"

namespace MainMenu {
    void MainMenuButton::mouseEntered(CallbackTarget* _target) {
        getText()->setFillColor(sf::Color::Green);
    }

    void MainMenuButton::mouseLeft(CallbackTarget* _target) {
        getText()->setFillColor(sf::Color::Black);
    }
    
    // Button Event Callbacks
    void MainMenu::buttonExitEvent(Clickable* _clickable) {
        exit(0);
    }

    void MainMenu::buttonNewGameClicked(Clickable* _clickable) {
        _renderer->unloadScene("Main Menu");
        _renderer->loadScene("Game Screen");
    }

    void MainMenu::buttonSettingsEvent(Clickable* _clickable) {
        _renderer->pushBackOverlay("Settings Menu");
    }


    // Init
    void MainMenu::init() {
        Scene::init();
        // Background Music and Image
        //sf::Music* _backgroundMusic = loadMusic("nice_music.ogg", "backgroundMusic");
        sf::Sprite* _backgroundImage = loadSprite("cute_image.jpg", "Background Image");
        
        // Labels
        mainMenuLabel.setText("Main Menu");
        mainMenuLabel.setFontSize(50);
        mainMenuLabel.setColor(sf::Color::Magenta);
        
        // Definition of Buttons
        newGameButton.setText("New Game");
        newGameButton.setFontSize(30);
        
        exitButton.setText("Exit");
        exitButton.setFontSize(30);
        
        settingsButton.setText("Settings");
        settingsButton.setFontSize(30);
        
        //// Callback Defintion ////
        // First Argument is the function that should be called,
        // second argument is the instance of the object that should be called
        newGameButton.setCallback(&MainMenu::buttonNewGameClicked, this);
        settingsButton.setCallback(&MainMenu::buttonSettingsEvent, this);
        exitButton.setCallback(&MainMenu::buttonExitEvent, this);
        
        //// Render Pipeline ////
        
        // Create a new Layer that sorts lowest for background
        renderPipeline.createGroup("Background", -1);
        // renderPipeline.sortLayerBelow("Background", "Default");
        
        // Push backgroundImage to Background Layer
        renderPipeline.pushBack(_backgroundImage, "Background");
        
        // Default Layer has sortID 0
        renderPipeline.pushBack(&mainMenuLabel);
        renderPipeline.pushBack(&newGameButton);
        renderPipeline.pushBack(&settingsButton);
        renderPipeline.pushBack(&exitButton);
        
        // Event Pipeline
        eventPipeline.pushBack(&newGameButton);
        eventPipeline.pushBack(&settingsButton);
        eventPipeline.pushBack(&exitButton);
        
        // Set Size for all elements
        resize();
    }

    void MainMenu::resize() {
        setPosition(&networkConnectionLabel, "90%10%");
        setPosition(&mainMenuLabel, "50%5%");
        
        sf::Sprite* _backgroundImage = objects.sprites.get("Background Image");
        setSize(_backgroundImage, "100%");
        
        setPosition(&newGameButton, "50%20%");
        setPosition(&settingsButton, "50%30%");
        setPosition(&exitButton, "50%40%");
        
        
        // Activate all buttons (Default: Disabled)
        newGameButton.activate();
        settingsButton.activate();
        exitButton.activate();
    }
}


//// Testing Networking
/*_renderer->pushBackOverlay("Console");

networkConnectionLabel.setText("Disconnected");
networkConnectionLabel.setFontSize(20);
networkConnectionLabel.setColor(sf::Color::Red);
if (netMan.connect("localhost", 33334)) {
    if (!netMan.receive().find("connected")) {
        netMan.send("noice");
        networkConnectionLabel.setText("Connected");
        networkConnectionLabel.setFontSize(20);
        networkConnectionLabel.setColor(sf::Color::Green);
    }
}*/
/////////////
