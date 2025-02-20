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

// Starting the server
void Server::start() {
    is_running = true; // The operation of the server directly depends on the flag
    std::cout << "The server has started on port " << server_port << "..." << '\n';
    std::cout << "Waiting the connections...\n";
    while(is_running) {
        tcp::socket socket(io_context);
        boost::system::error_code ec;
        acc.accept(socket, ec); // The accept is a blocking operation
        if (ec) { std::cerr << ec.message() << '\n';
        } else {
            std::cout << "Client connected.\n";
        }
        
    }
    std::cout << "Server is shutting down\n";
}

void Server::stop() {
    is_running = false;
}

void Server::receive_loop(tcp::socket& socket) {
    while (true) {
        std::string message = receive_message(socket);
        if (!message.empty()) {
            std::cout << message << '\n';
        } else {
            std::this_thread::sleep_for(std::chrono::seconds(5));   // Add time-out to reduce CPU load
        }
    }
}

std::string Server::receive_message(tcp::socket& socket) {
    std::array<char, 1024> data;
    boost::system::error_code ec;
    size_t length = socket.read_some(boost::asio::buffer(data), ec);
    if (ec) {
        if(ec != boost::asio::error::eof) {
            std::cerr << "receive_message\n" << ec.message() << '\n';
        } else {
            return std::string(data.data(), length);
        }
    }
    return "";
}