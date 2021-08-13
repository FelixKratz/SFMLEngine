//
//  ObjectStore.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 07.09.19.
//  Copyright © 2019 fk. All rights reserved.
//

#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

template <class Object>
class  ObjectStore {
private:
    std::map<std::string, Object> store;
public:
    Object* create(std::string name) { return &store[name]; };
    void clear() { store.clear(); };
    void destroy(std::string name) { store.erase(name); };
    
    Object* get(std::string name)
    {
        if (store.count(name) > 0)
            return &store.at(name);
        else
            return nullptr;
    };
    
    std::vector<Object*> getAll()
    {
        std::vector<Object*> v;
        for(typename std::map<std::string, Object>::iterator it = store.begin(); it != store.end(); ++it) {
            v.push_back(&it->second);
        }
        return v;
    };
};
