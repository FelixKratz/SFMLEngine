//
//  Scene.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include "../Manager/AssetManager.hpp"
#include "../Objects/Objects.hpp"
#include "../Objects/CallbackComponents.hpp"
#include "../Pipelines/RenderPipeline.hpp"
#include <cmath>

class WindowRenderer;

class Scene : public DAM::AssetManager, public CallbackTarget {
protected:
    View view;
    
    EventPipeline eventPipeline;
    UpdatePipeline updatePipeline;
    RenderPipeline renderPipeline;
    void clearPipelines();
public:
    bool initialized = false;
    bool isInitialized() { return initialized; };
    
    Scene(WindowRenderer* _windowRenderer);
    virtual ~Scene() { };
    
    Scene* load();
    virtual void unload() { objects.clear(); initialized = false; clearPipelines(); };
    virtual void init() { initialized = true; };
    virtual void resize() = 0;
    View* getView() { return &view; };
    
    virtual void draw() { if (!initialized) return; renderPipeline.draw(_renderer); };
    virtual void updateAllComponents(int elapsedTimeInMicroseconds) { updatePipeline.process(elapsedTimeInMicroseconds);}
    
    virtual void processEvent(sf::Event *event);
};
