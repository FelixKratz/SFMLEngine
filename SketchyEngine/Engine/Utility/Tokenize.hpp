//
//  Tokenize.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 24.04.20.
//  Copyright © 2020 fk. All rights reserved.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Tokenize a string str with delimiter delim and output it to the out vector
void tokenize(std::string str, char delim, std::vector<std::string>* out);
