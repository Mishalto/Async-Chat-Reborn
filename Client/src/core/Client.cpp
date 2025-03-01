#include <Client.hpp>

Client::Client() : ep_(boost::asio::ip::make_address_v4("127.0.0.1"), 12345) {}

void Client::run() {
    io_context_.run();
    auto socket = std::make_shared<tcp::socket>(io_context_);
    socket->async_connect(ep_, [socket](const boost::system::error_code err){
        if (!err) {
            std::cout << "Connected.\n";
            auto session = std::make_shared<Session>(std::move(*socket));
            session->start();
        } else {
            std::cerr << err.message() << '\n';
        }
    });
}
