#include <Client.hpp>

Client::Client() : ep_(boost::asio::ip::make_address_v4("127.0.0.1"), 12345) {}

void Client::start_session() {
    io_context_.run();
    auto socket = std::make_shared<tcp::socket>(io_context_);
    boost::system::error_code err;
    socket->connect(ep_, err);
    if (!err) {
        std::cout << "Connected\n";
    }
}

void Client::run() {
    io_context_.run();
}
