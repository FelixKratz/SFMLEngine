//
//  NetworkManager.cpp
//  StrategyGame
//
//  Created by Felix Kratz on 24.04.20.
//  Copyright © 2020 fk. All rights reserved.
//

#include "NetworkManager.hpp"

bool NetworkManager::connect(std::string ip, unsigned int port) {
    sf::Socket::Status status = socket.connect(ip, port);

    if (status != sf::Socket::Done) {
        return false;
    }
    return true;
}

bool NetworkManager::send(std::string message) {
    if (socket.send(message.c_str(), message.length()) != sf::Socket::Done) {
        return false;
    }
    return true;
}

std::string NetworkManager::receive() {
    char data[100] = {'\0'};
    size_t received;
    if (socket.receive(data, 100, received) != sf::Socket::Done) {
        return "";
    }
    return data;
}
