#include <Session.hpp>

void Session::start() {
    do_read();
}

void Session::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_), [this, self](const boost::system::error_code err, size_t length){
        if(!err) {
            std::cout << std::string(data_.data(), length);
            do_read();
        } else {
            if(err == boost::asio::error::eof) {
                std::cerr << "Client disconnected.\n";
            } else {
                std::cerr << err.message() << '\n';
            }
        }
    });
}