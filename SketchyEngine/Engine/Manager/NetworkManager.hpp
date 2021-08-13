//
//  NetworkManager.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 24.04.20.
//  Copyright © 2020 fk. All rights reserved.
//

#include <SFML/Network.hpp>

// Simple Socket-based Networking
class NetworkManager {
private:
    sf::TcpSocket socket;
public:
    bool connect(std::string ip, unsigned int port);
    bool send(std::string message);
    std::string receive();
};
