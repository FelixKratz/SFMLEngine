//
//  Pipeline.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 14.09.20.
//  Copyright © 2020 fk. All rights reserved.
//

#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "../Objects/ObjectStore.hpp"

template <class ProcessInput>
class PipelineProcessor {
public:
    virtual void process(ProcessInput processInput) = 0;
};

// Layers are only created in the Pipeline and should only be interfaced through it
template <class PipelineProcessor>
class Group {
protected:
    // The sortID is used to render lowerst sortID layer first and highest sortID layer last
    int sortID = 0;
    std::vector<PipelineProcessor*> _targets;
public:
    // Sorting Logic Interfaces
    void setSortID(int ID) { sortID = ID; };
    int getSortID() const { return sortID; };
    
    void sortGroupAbove(Group* _group) { setSortID(_group->getSortID() + 1); };
    void sortGroupBelow(Group* _group) { setSortID(_group->getSortID() - 1); };
    
    // Add/Remove Drawable to Layer, order matters here: First element in _renderTargets gets drawn first
    void pushBack(PipelineProcessor* _target) { _targets.push_back(_target); };
    void remove(PipelineProcessor* _processor);
    
    // Remove all Drawables from Layer
    void clear() { _targets.clear(); };
    
    // Process all PipelineProcessors in _targets
    template <class ProcessInput>
    void process(ProcessInput processInput) const;
    
    std::vector<PipelineProcessor*>* getTargets() { return &_targets; };
};

template <class PipelineProcessor>
class Pipeline {
protected:
    ObjectStore<Group<PipelineProcessor>> _groups;
    // This list is updated only when changes to a sortID of some Group are performed
    std::vector<Group<PipelineProcessor>*> sortedGroupList;
    void updateSortedGroupList();
    
    void createDefaultGroup() { createGroup("Default", 0); }
public:
    Pipeline() { createDefaultGroup(); };
    
    // Pipeline pushBack logic
    void pushBack(PipelineProcessor* _processor) { pushBack(_processor, "Default"); };
    void pushBack(PipelineProcessor* _processor, std::string group) { _groups.get(group)->pushBack(_processor); };
    void remove(PipelineProcessor* _processor);
    
    // Group operations
    void createGroup(std::string name, int sortID = 0);
    void rearangeGroup(std::string name, int sortID) { _groups.get(name)->setSortID(sortID); updateSortedGroupList(); };
    void sortGroupAbove(std::string sort, std::string above);
    void sortGroupBelow(std::string sort, std::string below);
    void clearGroup(std::string name) { _groups.get(name)->clear(); };
    void clearAllGroups();
    
    // Process all groups
    template <class ProcessInput>
    void process(ProcessInput _processInput) const;
};

// Custom sorting logic for Group objects
template <class PipelineProcessor>
struct GroupSort {
    bool operator()(Group<PipelineProcessor>* _left, Group<PipelineProcessor>* _right) const { return _left->getSortID() < _right->getSortID(); }
};

// Group Implementation
template <class PipelineProcessor>
template <class ProcessInput>
void Group<PipelineProcessor>::process(ProcessInput processInput) const {
    for (auto _target : _targets)
        _target->process(processInput);
}

template <class PipelineProcessor>
void Group<PipelineProcessor>::remove(PipelineProcessor* _processor) {
    typename std::vector<PipelineProcessor*>::iterator iterator = std::find(_targets.begin(), _targets.end(), _processor);
    if (iterator != _targets.end())
        _targets.erase(iterator);
    //else
        //std::cout << "Warning: Processor " << _processor << " not found in Pipeline " << this << std::endl;
}


template <class PipelineProcessor>
void Pipeline<PipelineProcessor>::remove(PipelineProcessor* _processor) {
    for (auto _group : sortedGroupList)
        _group->remove(_processor);
}

// Pipeline Implementation
template <class PipelineProcessor>
void Pipeline<PipelineProcessor>::clearAllGroups() {
    _groups.clear();
    createDefaultGroup();
};

template <class PipelineProcessor>
void Pipeline<PipelineProcessor>::createGroup(std::string name, int sortID) {
    Group<PipelineProcessor>* _addedGroup = _groups.create(name);
    _addedGroup->setSortID(sortID);
    updateSortedGroupList();
};

template <class PipelineProcessor>
void Pipeline<PipelineProcessor>::sortGroupAbove(std::string sort, std::string above) {
    Group<PipelineProcessor>* _sort = _groups.get(sort);
    Group<PipelineProcessor>* _above = _groups.get(above);
    
    _sort->sortGroupAbove(_above);
    updateSortedGroupList();
}

template <class PipelineProcessor>
void Pipeline<PipelineProcessor>::sortGroupBelow(std::string sort, std::string below) {
    Group<PipelineProcessor>* _sort = _groups.get(sort);
    Group<PipelineProcessor>* _below = _groups.get(below);
    
    _sort->sortGroupBelow(_below);
    updateSortedGroupList();
}

template <class PipelineProcessor>
void Pipeline<PipelineProcessor>::updateSortedGroupList() {
    sortedGroupList = _groups.getAll();
    std::sort(sortedGroupList.begin(), sortedGroupList.end(), GroupSort<PipelineProcessor>());
}

template <class PipelineProcessor>
template <class ProcessInput>
void Pipeline<PipelineProcessor>::process(ProcessInput processInput) const {
    for (auto _group : sortedGroupList)
        _group->process(processInput);
};
