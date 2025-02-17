#include <Client.hpp>

#include <iostream>

Client::Client() : ep(boost::asio::ip::make_address_v4("127.0.0.1"), 12345) {
    std::cout << "Work!\n";
}

void Client::start_connection() {
    tcp::socket socket(io_context);
    boost::system::error_code ec;
    socket.connect(ep, ec);
    if (ec) {
        std::cerr << ec.message() << '\n';
    } else {
        std::cout << "Connected!\n";
    }
}