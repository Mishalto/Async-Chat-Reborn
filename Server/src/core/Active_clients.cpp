#include <Active_clients.hpp>

ActiveClients::ActiveClients() {
    std::thread listening_thread(&ActiveClients::start_listening, this);
    std::cout << "[Active_clients]Listening thread created and detached.\n";
    listening_thread.detach();
}

void ActiveClients::add_client(const std::string& ip, std::shared_ptr<tcp::socket> socket_ptr) {
    active_clients_[ip] = {std::move(socket_ptr)};
    std::cout << "[ActiveClients]Client added\n";
}

void ActiveClients::start_listening()
{
    std::cout << "[Active_clients]Listening started.\n";
    for (;;) {
        for (auto &client : active_clients_) {
            std::lock_guard<std::mutex> guard(mtx);
            if (client.second.check_message()) {
                std::cout << client.second.get_message() << '\n';
            }
        }
    }
}