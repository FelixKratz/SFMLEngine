//
//  WindowRenderer.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once


#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../Utility/ResourcePath.hpp"
#include <iostream>
#include "../../Implementation/Scenes/SceneManager.hpp"
#include "../../Implementation/UI/UIManager.hpp"
#include "../Input/InputEvents.hpp"

// TODO: Update the overlay logic to also use the Layer system defined in the RenderPipeline

class Scene;

// The WindowRenderer manages and renders the window
class WindowRenderer {
private:
    // The actual RenderWindow
    sf::RenderWindow window;
    
    // Managers for scenes and UIs
    SceneManager sceneManager;
    UIManager uiManager;
    
    // The _currentScene holds a ref to the displayed scene
    Scene* _currentScene = nullptr;
    
    // All overlay refs are stored in _overlays
    std::vector<UI*> _overlays;
    
    // Events are handled by the topmost overlay first, from there they are piped to lower levels.
    // The currentEventHandler specifies which overlay currently handles events
    short currentEventHandler;
    bool isOverlayDrawn(UI* _overlay);
    
    // Load and Unload buffers. The buffers are processed *after* a full frame update
    std::vector<std::string> overlayLoadBuffer;
    std::vector<std::string> overlayUnLoadBuffer;
    std::vector<std::string> sceneLoadBuffer;
    std::vector<std::string> sceneUnloadBuffer;
    
    // Overlay private interface
    void p_pushBackOverlay(std::string ui);
    void p_insertOverlay(std::string ui, int level);
    void p_removeOverlay(std::string ui);
    
    // Scene private interface
    void p_loadScene(std::string scene);
    void p_unloadScene(std::string scene);
    void p_setScene(Scene* _scene) { _currentScene = _scene; };
public:
    WindowRenderer() : sceneManager(this), uiManager(this) { };
    ~WindowRenderer() { };
    
    void init(sf::VideoMode videoMode, std::string title);
    void clearScreen() { window.clear(sf::Color::Transparent); };
    bool windowOpen() { return window.isOpen(); };
    
    // Window interface
    void setFrameRateCap(int fps) { window.setFramerateLimit(fps);};
    void setResolution(int width, int height) { window.setSize(sf::Vector2u(width, height)); resizeAll(); };
    void setFullscreen(bool on);
    void showMouse(bool on);
    void grabMouse(bool on);
    void resizeAll();
    
    // Overlay Interface
    void pushBackOverlay(std::string ui);
    void insertOverlay(std::string ui, int level);
    void removeOverlay(std::string ui);
    
    // Scene Interface
    void loadScene(std::string scene);
    void unloadScene(std::string scene);
    void setScene(Scene* _scene) { _currentScene = _scene; };
    Scene* getScene() { return _currentScene; };
    
    // Event Processing
    void pipeEvent(sf::Event* _event);
    void processEvents();
    
    // Post-frame buffer processing
    void updateScenes();
    
    // Interface for drawing a frame to screen
    void setView(sf::View* _view) { window.setView(*_view); };
    void displayFrame() { window.display(); };
    void drawFrame(int elapsedTimeInMircoseconds);
    void draw(const sf::Drawable& drawable) { window.draw(drawable); };
    void draw(sf::Drawable* drawable) { window.draw(*drawable); };
    sf::RenderWindow* getRenderWindow() { return &window; };
};
