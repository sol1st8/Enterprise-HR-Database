#include "application.h"
#include "http_server/http_server.h"
#include "request_handler.h"

#include <boost/asio/signal_set.hpp>
#include <filesystem>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

namespace net = boost::asio;
namespace sys = boost::system;
using tcp = net::ip::tcp;
using namespace std::literals;

namespace {

template <typename Fn>
void RunWorkers(unsigned n, const Fn& fn) {
    n = std::max(1u, n);
    std::vector<std::thread> workers;
    workers.reserve(n - 1);
    while (--n) {
        workers.emplace_back(fn);
    }
    fn();

    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

} // namespace

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: run_server <static-data-path>"sv
                  << std::endl;
        return EXIT_FAILURE;
    }
    try {
        const unsigned num_threads = std::thread::hardware_concurrency();
        net::io_context ioc(num_threads);

        const auto address = net::ip::make_address("0.0.0.0");
        constexpr net::ip::port_type port = 8080;

        net::signal_set signals(ioc, SIGINT, SIGTERM);
        signals.async_wait([&ioc](const sys::error_code& ec, [[maybe_unused]] int signal_number) {
            if (!ec) {
                ioc.stop();
            }
        });

        const std::filesystem::path home_path(std::filesystem::current_path().parent_path());
        const std::filesystem::path static_path(std::filesystem::weakly_canonical(home_path / argv[1]));

        http_handler::RequestHandler handler{static_path};

        http_server::ServeHttp(ioc, {address, port}, [&handler](auto&& req, auto&& send) {
            handler(std::forward<decltype(req)>(req), std::forward<decltype(send)>(send));
        });

        std::cout << "Server has started..."sv << std::endl;

        RunWorkers(num_threads, [&ioc] {
            ioc.run();
        });
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
