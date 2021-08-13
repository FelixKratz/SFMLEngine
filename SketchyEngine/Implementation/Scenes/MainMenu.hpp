//
//  MainMenu.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include "../../Engine/Backbone/Scene.hpp"
#include "../../Engine/Manager/NetworkManager.hpp"

namespace MainMenu {

    // Definition of Custom Buttons for the Main Menu
    class MainMenuButton : public Button {
        using Button::Button;
        virtual void mouseEntered(CallbackTarget* _mainMenu) override;
        virtual void mouseLeft(CallbackTarget* _mainMenu) override;
    };

    class MainMenu : public Scene {
    private:
        // Views
        NetworkManager netMan;
        
        // Labels
        Label mainMenuLabel;
        Label networkConnectionLabel;
        
        // Buttons
        MainMenuButton newGameButton;
        MainMenuButton settingsButton;
        MainMenuButton exitButton;

        // Declaration of Callback Functions
        void buttonNewGameClicked(Clickable* _clickable);
        void buttonSettingsEvent(Clickable* _clickable);
        void buttonExitEvent(Clickable* _clickable);
    public:
        MainMenu(WindowRenderer* _windowRenderer) : Scene(_windowRenderer) {};
        void init() override;
        void resize() override;
    };
}
