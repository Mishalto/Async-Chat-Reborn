#include <Session.hpp>

Session::Session(tcp::socket socket) : socket_(std::move(socket)) {
    std::cout << "Session started.\n";
}

void Session::start() {
    for(;;) {
        do_read();
        do_send();
    }
}

void Session::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_), [this, self](const boost::system::error_code err, size_t length){
        if (!err) {
            std::cout << std::string(data_.data(), length);
            do_read();
        } else {
            std::cerr << err.message() << '\n';
        }
    });
}

void Session::do_send() {
    std::cout << "Message: ";
    std::string message;
    std::cin >> message;

    boost::asio::write(socket_, boost::asio::buffer(message));
}