#include <Server.hpp>
#include <iostream>
#include <thread>
#include <array>
#include <string>

// They must be initialized through the constructor initializer list
Server::Server() : ep(tcp::v4(), server_port), acc(io_context, ep) {
    is_running = false; // The default state of the server is disabled
    std::cout << "Server initialized successfully.\n";
}