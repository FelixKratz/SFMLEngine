//
//  Tokenize.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 24.04.20.
//  Copyright © 2020 fk. All rights reserved.
//

#include "Tokenize.hpp"

void tokenize(std::string str, char delim, std::vector<std::string>* out) {
    std::stringstream ss(str); std::string s;
    while (std::getline(ss, s, delim)) out->push_back(s);
}
