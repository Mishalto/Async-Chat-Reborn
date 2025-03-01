#include <Session.hpp>

Session::Session(tcp::socket socket) : socket_(std::move(socket)) {}