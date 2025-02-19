#include <Server.hpp>
#include <iostream>

// Since tcp::endpoint and tcp::acceptor are complex object
// They must be initialized through the constructor initializer list
Server::Server() : ep(tcp::v4(), server_port), acc(io_context, ep) {
    is_running.store(false); // The default state of the server is disabled
    std::cout << "Server initialized successfully.\n";
}

void Server::send_message(tcp::socket& socket) {
    std::string message;
    std::cout << "you: ";
    std::getline(std::cin, message);

    boost::system::error_code ec;
    boost::asio::write(socket, boost::asio::buffer(message), ec);
    if(ec) {
        std::cerr << "send_message error\n" << ec.message() << '\n';
    }
}

// Starting the server
void Server::start() {
    is_running.store(true); // The operation of the server directly depends on the flag
    std::cout << "The server has started on port " << server_port << "..." << '\n';
    std::cout << "Waiting the connections...\n";
    while(is_running) {
        // Create a socket, error_code
        // and wait for connection
        tcp::socket socket(io_context);
        boost::system::error_code ec;
        acc.accept(socket, ec); // The accept is a blocking operation
        // Error handler
        if (ec) {
            std::cout << ec.message() << '\n';
        }
        else {
            std::cout << "Client connected.\n";
            send_message(socket);
        }
    }
    std::cout << "Server is shutting down\n";
}

// Stoping the server
void Server::stop() {
    is_running.store(false);
}