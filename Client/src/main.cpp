#include <Client.hpp>

int main()
{
    setlocale(LC_ALL, "");

    Client cl;
    cl.start_session();
    cl.run();

    return 0;
}