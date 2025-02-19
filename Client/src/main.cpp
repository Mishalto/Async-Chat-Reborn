#include <iostream>
#include <boost/asio.hpp>
#include <Client.hpp>

int main()
{
    setlocale(LC_ALL, "");

    Client cl;
    cl.start_connection();

    return 0;
}