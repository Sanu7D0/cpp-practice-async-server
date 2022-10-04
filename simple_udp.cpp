#include <boost/asio.hpp>
#include <iostream>

int main()
{
    std::uint16_t port = 15001;

    boost::asio::io_context io_context;
    boost::asio::ip::udp::endpoint receiver(boost::asio::ip::udp::v4(), port);
    boost::asio::ip::udp::socket socket(io_context, receiver);

    std::cout << "UDP listening on " << port << std::endl;

    for (;;)
    {
        char buffer[65536];
        boost::asio::ip::udp::endpoint sender;

        // block
        std::size_t bytes_transferred = socket.receive_from(boost::asio::buffer(buffer), sender);
        socket.send_to(boost::asio::buffer(buffer, bytes_transferred), sender);

        // non block
        // socket.async_receive_from(buffer, sender, [&](boost::system::error_code error, std::size_t bytes_transferred)
        // {
        //     // This lambda will call upon receiving of a message
        //     std::cout << "Message is received, message size is " << bytes_transferred;
        // });
    }

    return 0;
}