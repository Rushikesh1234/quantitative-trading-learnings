/*
Market data feeds are streams of financial data provided by exchanges, brokers, or data vendors.
Common protocols include:
1.FIX (Financial Information eXchange): A standard protocol for communication in financial markets.
2.WebSocket Feeds: Often used for real-time streaming of stock prices and order book updates.
3.REST APIs: For fetching less time-sensitive data like historical prices.
*/
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = beast::websocket;

int main() {
    try {
        // Create I/O context and SSL context
        asio::io_context ioc;
        asio::ssl::context ctx(asio::ssl::context::tlsv12_client);
        ctx.set_verify_mode(asio::ssl::verify_peer);

        // Set up resolver
        asio::ip::tcp::resolver resolver(ioc);

        // Create the WebSocket stream with SSL support
        websocket::stream<asio::ssl::stream<asio::ip::tcp::socket>> ws(ioc, ctx);

        // Resolve and connect to the server
        auto const results = resolver.resolve("stream.binance.com", "9443");
        asio::connect(ws.next_layer().next_layer(), results.begin(), results.end());

        // Perform the SSL handshake
        ws.next_layer().handshake(asio::ssl::stream_base::client);

        // Perform the WebSocket handshake
        ws.handshake("stream.binance.com", "/ws/btcusdt@trade");

        // Read the message
        beast::flat_buffer buffer;
        ws.read(buffer);

        // Output the message
        std::cout << beast::make_printable(buffer.data()) << std::endl;

        // Close the WebSocket connection
        ws.close(websocket::close_code::normal);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
