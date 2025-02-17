#include <iostream>
#include <boost/asio.hpp>
#include <Client.hpp>

int main()
{
    Client cl;
    cl.start_connection();

    return 0;
}