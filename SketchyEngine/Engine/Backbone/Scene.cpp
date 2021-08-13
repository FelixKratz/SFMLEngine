//
//  Scene.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#include "Scene.hpp"
#include "WindowRenderer.hpp"

Scene::Scene(WindowRenderer* _windowRenderer) : AssetManager(_windowRenderer) {
    eventPipeline.getInputState()->setWindow(_windowRenderer->getRenderWindow());
    view.setRenderer(_windowRenderer);
}

Scene* Scene::load()  {
    view.setSize(_renderer->getRenderWindow()->getView().getSize());
    view.setCenter(_renderer->getRenderWindow()->getView().getCenter());
    renderPipeline.clearAllGroups();
    init();
    return this;
}

void Scene::clearPipelines() {
    eventPipeline.clearAllGroups();
    updatePipeline.clearAllGroups();
    renderPipeline.clearAllGroups();
}

void Scene::processEvent(sf::Event *event) {
    if (!initialized) return;
    eventPipeline.process(event);
};
