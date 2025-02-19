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
        std::cerr << ec.message() << '\n';
    } else {
        std::cout << "Connected.\n";
        chat(socket);
    }
}

void Client::chat(tcp::socket& socket) {
    for(;;) {
        std::thread receive_th(&Client::receive_message, this, std::ref(socket));
        receive_th.detach();
    }
}

std::string Client::receive_message(tcp::socket& socket) {
    std::array<char, 1024> data;
    boost::system::error_code ec;
    size_t length = boost::asio::read(socket, boost::asio::buffer(data), ec);
    if (ec) {
        std::cerr << "Receive error." << '\n' << ec.message() << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(5));
    } else {
        return std::string(data.data(), length);
    }

    return "";
}