//
//  Renderer.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#include "WindowRenderer.hpp"
#include "Scene.hpp"

void WindowRenderer::init(sf::VideoMode videoMode, std::string title) {
    // Create the Window
    window.create(videoMode, title);
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void WindowRenderer::setFullscreen(bool on) {
    sf::VideoMode mode;
    
    if (on) {
        window.create(mode.getFullscreenModes()[0], "");
    }
    else {
        mode.width = 1440;
        mode.height = 900;
        window.create(mode, "");
    }
    window.setView(window.getDefaultView());
    resizeAll();
}

void WindowRenderer::showMouse(bool on) {
    window.setMouseCursorVisible(on);
}

void WindowRenderer::grabMouse(bool on) {
    window.setMouseCursorGrabbed(on);
}

void WindowRenderer::resizeAll() {
    for (auto i : _overlays) i->resize();
    _currentScene->resize();
}

void WindowRenderer::processEvents() {
    // Process events
    sf::Event event;
    sf::View currentView = window.getView();
    while (window.pollEvent(event))
    {
        // Close window: exit
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        if (event.type == sf::Event::Resized) {
            // Handle Resize
            // TODO : if view is already set: only enlarge current view
            //sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            //window.setView(sf::View(visibleArea));
            resizeAll();
        }

        if (_currentScene != nullptr && _overlays.size() == 0) {
            _currentScene->processEvent(&event);
        }
        else if (_currentScene != nullptr) {
            currentEventHandler = _overlays.size() - 1;
            window.setView(window.getDefaultView());
            _overlays[currentEventHandler]->processEvent(&event);
            window.setView(currentView);
        }
        else
            std::cout << "No scene loaded." << std::endl;
    }
}

void WindowRenderer::pipeEvent(sf::Event *_event) {
    currentEventHandler--;
    sf::View currentView = window.getView();
    if (currentEventHandler >= 0) {
        window.setView(window.getDefaultView());
        _overlays[currentEventHandler]->processEvent(_event);
        window.setView(currentView);
    }
    else {
        window.setView(*_currentScene->getView()->getSfView());
        _currentScene->processEvent(_event);
    }
}

bool WindowRenderer::isOverlayDrawn(UI *_overlay) {
    for (int i = 0; i < _overlays.size(); i++) {
        if (_overlays[i] == _overlay) return true;
    }
    return false;
}

void WindowRenderer::p_pushBackOverlay(std::string ui) {
    UI* _ui = uiManager.get(ui);
    if (_ui == nullptr) { std::cout << "Error, UI: " + ui + " is not loaded" << std::endl; return; };
    if (isOverlayDrawn(_ui)) { removeOverlay(ui); };
    _ui = uiManager.load(ui);
    _ui->setActiveScene(_currentScene);
    _overlays.push_back(_ui);
}

void WindowRenderer::p_removeOverlay(std::string ui) {
    UI* _ui = uiManager.get(ui);
    if (_ui == nullptr) { std::cout << "Error, UI: " + ui + " is not loaded" << std::endl; return; };
    for (int i = 0; i < _overlays.size(); i++) {
        if (_overlays[i] == _ui) _overlays.erase(_overlays.begin() + i);
    }
    _ui->unload();
}

void WindowRenderer::p_insertOverlay(std::string ui, int level) {
    UI* _ui = uiManager.get(ui);
    if (_ui == nullptr) { std::cout << "Error, UI: " + ui + " is not loaded" << std::endl; return; };
    if (isOverlayDrawn(_ui)) { removeOverlay(ui); };
    _ui = uiManager.load(ui);
    if (level <= _overlays.size())
        _overlays.insert(_overlays.begin() + level, _ui);
    else {
        std::cout << "Position out of range... overlay pushed back" << std::endl;
        pushBackOverlay(ui);
    }
    _ui->setActiveScene(_currentScene);
};

void WindowRenderer::p_loadScene(std::string scene) {
    if (_currentScene != nullptr) sceneManager.unload(_currentScene);
    setScene(sceneManager.load(scene));
    for (auto i : _overlays) {
        i->setActiveScene(_currentScene);
    }
}

void WindowRenderer::p_unloadScene(std::string scene) {
    sceneManager.unload(scene);
    _currentScene = nullptr;
    for (auto i : _overlays) {
        i->setActiveScene(nullptr);
    }
}

void WindowRenderer::pushBackOverlay(std::string ui) {
    for (auto i : overlayLoadBuffer)
        if (i == ui) return;
    
    overlayLoadBuffer.push_back(ui);
}

void WindowRenderer::removeOverlay(std::string ui) {
    for (auto i : overlayUnLoadBuffer)
        if (i == ui) return;
    
    overlayUnLoadBuffer.push_back(ui);
}

void WindowRenderer::insertOverlay(std::string ui, int level) {
    for (auto i : overlayLoadBuffer)
        if (i == ui) return;
    
    overlayLoadBuffer.push_back(ui);
    std::cout << "Overlay will not get inserted correctly! Still TODO..." << std::endl;
};

void WindowRenderer::loadScene(std::string scene) {
    for (auto i : sceneLoadBuffer)
        if (i == scene) return;
    
    sceneLoadBuffer.push_back(scene);
}

void WindowRenderer::unloadScene(std::string scene) {
    for (auto i : sceneUnloadBuffer)
        if (i == scene) return;
    
    sceneUnloadBuffer.push_back(scene);
}

void WindowRenderer::updateScenes() {
    for (auto i : sceneUnloadBuffer)
        p_unloadScene(i);
    for (auto i : sceneLoadBuffer)
        p_loadScene(i);
    for (auto i : overlayUnLoadBuffer)
        p_removeOverlay(i);
    for (auto i : overlayLoadBuffer)
        p_pushBackOverlay(i);
    
    sceneUnloadBuffer.clear();
    sceneLoadBuffer.clear();
    overlayUnLoadBuffer.clear();
    overlayLoadBuffer.clear();
}


void WindowRenderer::drawFrame(int elapsedTimeInMircoseconds) {
    sf::View currentView = window.getView();
    if (_currentScene != nullptr) {
        _currentScene->updateAllComponents(elapsedTimeInMircoseconds);
        _currentScene->draw();
    }
    
    window.setView(window.getDefaultView());
    for (auto i : _overlays) {
        i->updateAllComponents(elapsedTimeInMircoseconds);
        i->draw();
    }
    window.setView(currentView);
}
