#include <Client.hpp>

#include <iostream>
#include <thread>
#include <array>
#include <chrono>

Client::Client() : ep(boost::asio::ip::make_address_v4("127.0.0.1"), 12345) {}

void Client::start_connection() {
    tcp::socket socket(io_context);
    boost::system::error_code ec;
    socket.connect(ep, ec);
    if (ec) {
        std::cerr << "start_connection error\n" << ec.message() << '\n';
    } else {
        std::cout << "Connected.\n";
        chat(socket);
    }
}

void Client::chat(tcp::socket& socket) {
    std::thread receive_th(&Client::receive_loop, this, std::ref(socket));
    for(;;) {
        
    }
    receive_th.join();
}

std::string Client::receive_message(tcp::socket& socket) {
    std::array<char, 1024> data;
    boost::system::error_code ec;
    size_t length = boost::asio::read(socket, boost::asio::buffer(data), ec);
    if (ec) {
        if(ec != boost::asio::error::eof) {
            std::cerr << "receive message error\n" << ec.message() << '\n';
        }
    } else {
        return std::string(data.data(), length);
    }

    return "";
}

void Client::receive_loop(tcp::socket& socket) {
    while(true) {
        std::string message = receive_message(socket);
        if(!message.empty()) {
            std::cout << message << '\n';
        }
        else {
            std::cout << "<blank>\n" << '\n';
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
}