/*#include "http_server.h"
#include "sdk.h"

#include <boost/asio/signal_set.hpp>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

namespace {
using namespace std::literals;
namespace net = boost::asio;
namespace sys = boost::system;
namespace http = boost::beast::http;

using StringRequest = http::request<http::string_body>;
using StringResponse = http::response<http::string_body>;

struct ContentType {
    ContentType() = delete;
    constexpr static std::string_view TEXT_HTML = "text/html"sv;
};

StringResponse MakeStringResponse(http::status status, std::string_view body,
unsigned http_version, bool keep_alive, std::string_view content_type =
ContentType::TEXT_HTML) { StringResponse response(status, http_version);
    response.set(http::field::content_type, content_type);
    response.body() = body;
    response.content_length(body.size());
    response.keep_alive(keep_alive);
    return response;
}

StringResponse HandleRequest(StringRequest&& req) {
    const auto text_response = [&req](http::status status, std::string_view
text) { return MakeStringResponse(status, text, req.version(),
req.keep_alive());
    };
    if (req.method_string() == "GET"sv) {
        return text_response(http::status::ok, std::string("Hello, "s +
std::string(req.target()).substr(1)));
    }
    else if (req.method_string() == "HEAD"sv) {
        return text_response(http::status::ok, ""sv);
    }
    return text_response(http::status::method_not_allowed, "Invalid method"sv);
}

template <typename Fn>
void RunWorkers(unsigned n, const Fn& fn) {
    n = std::max(1u, n);
    std::vector<std::jthread> workers;
    workers.reserve(n - 1);
    while (--n) {
        workers.emplace_back(fn);
    }
    fn();
}

} // namespace

int main() {
    const unsigned num_threads = std::thread::hardware_concurrency();

    net::io_context ioc(num_threads);

    net::signal_set signals(ioc, SIGINT, SIGTERM);
    signals.async_wait([&ioc](const sys::error_code& ec, [[maybe_unused]] int
signal_number) { if (!ec) { ioc.stop();
        }
    });

    const auto address = net::ip::make_address("0.0.0.0");
    constexpr net::ip::port_type port = 8080;
    http_server::ServeHttp(ioc, {address, port}, [](auto&& req, auto&& sender) {
        sender(HandleRequest(std::forward<decltype(req)>(req)));
    });

    std::cout << "Server has started..."sv << std::endl;

    RunWorkers(num_threads, [&ioc] {
        ioc.run();
    });
}
*/

#include "db.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std::literals;

namespace {

constexpr const char DB_URL_ENV_NAME[]{"DB_URL"};

db::AppConfig GetConfigFromEnv() {
    db::AppConfig config;
    if (const auto* url = std::getenv(DB_URL_ENV_NAME)) {
        config.db_url = url;
    }
    else {
        throw std::runtime_error(DB_URL_ENV_NAME + " environment variable not found"s);
    }
    return config;
}

}  // namespace

int main([[maybe_unused]] int argc, [[maybe_unused]] const char* argv[]) {
    try {
        db::Application app{GetConfigFromEnv()};
        app.Run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
