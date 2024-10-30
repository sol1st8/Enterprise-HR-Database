#pragma once

#include "http_server.h"

#include <boost/beast.hpp>
#include <boost/json.hpp>
#include <filesystem>

namespace http_handler {
namespace beast = boost::beast;
namespace http = beast::http;
namespace json = boost::json;
namespace sys = boost::system;
using HttpResponse = http::response<http::string_body>;
using namespace std::literals;
namespace net = boost::asio;

class RequestHandler {
  public:
    explicit RequestHandler(std::filesystem::path static_data_path) : static_data_path_(std::move(static_data_path)) {}

    RequestHandler(const RequestHandler&) = delete;
    RequestHandler& operator=(const RequestHandler&) = delete;

    template <typename Body, typename Allocator, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send);

  private:
    std::filesystem::path static_data_path_;

    template <typename Body, typename Allocator, typename Send>
    void HandleStaticDataResponse(http::request<Body, http::basic_fields<Allocator>>&& req,
                                  std::string_view target, Send&& send);

    template <typename Body, typename Allocator, typename Send>
    void TryToSendFile(http::request<Body, http::basic_fields<Allocator>>&& req,
                       const std::filesystem::path& file, Send&& send);
};

template <typename Body, typename Allocator, typename Send>
void RequestHandler::operator()(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {
    std::string_view target = req.target();

    if (target.starts_with("/api"s)) {
        // ...
    }
    else {
        HandleStaticDataResonse(std::forward<decltype(req)>(req), target, std::forward<Send>(send));
    }
}

template <typename Body, typename Allocator, typename Send>
void RequestHandler::HandleStaticDataResponse(http::request<Body, http::basic_fields<Allocator>>&& req,
                                              std::string_view target, Send&& send) {
    // ...
}

} // namespace http_handler
