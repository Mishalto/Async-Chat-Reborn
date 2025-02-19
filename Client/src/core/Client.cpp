#include <Client.hpp>

#include <iostream>
#include <thread>
#include <array>
#include <chrono>

// Спросить факинг Дениса про структуру!!!
Client::Client() : ep(boost::asio::ip::make_address_v4("127.0.0.1"), 12345) {}

// From here we start connecting to the server
void Client::start_connection() {
    tcp::socket socket(io_context);
    boost::system::error_code ec;
    socket.connect(ep, ec);
    if (ec) {
        std::cerr << "start_connection error\n" << ec.message() << '\n';
    } else {
        std::cout << "Connected.\n";
        chat(socket);   // If the connection is established, proceed to the main loop
    }
}

// Main loop
// I'm not sure if the threading implementation is correct
void Client::chat(tcp::socket& socket) {
    std::thread receive_th(&Client::receive_loop, this, std::ref(socket));  // This thread is constantly receiving data from the socket
    for(;;) {   // Infinity loop
        send_message(socket);
    }
    receive_th.join();
}

// This method retrieves/извлекает and processes/обрабатывает the received data from the socket
std::string Client::receive_message(tcp::socket& socket) {
    std::array<char, 1024> data;
    boost::system::error_code ec;
    size_t length = socket.read_some(boost::asio::buffer(data), ec);
    if (ec) {
        if (ec != boost::asio::error::eof) {    // This is where i skip blank processing
            std::cerr << "receive message error\n" << ec.message() << '\n';
        }
    } else {
        return std::string(data.data(), length);
    }

    return "";
}

// Infinity loop, we're constantly trying to get data
void Client::receive_loop(tcp::socket& socket) {
    while(true) {
        std::string message = receive_message(socket);
        if(!message.empty()) {
            std::cout << message << '\n';
        } else {
            std::this_thread::sleep_for(std::chrono::seconds(2));   // Add time-out to reduce load
        }
    }
}

// Just sending messages
void Client::send_message(tcp::socket& socket) {
    std::cout << "You: ";
    std::string message;
    std::getline(std::cin, message);

    boost::system::error_code ec;
    boost::asio::write(socket, boost::asio::buffer(message), ec);
    // Error handling
    if (ec) {
        std::cerr << "send_message error\n" << ec.message() << '\n';
    }
}