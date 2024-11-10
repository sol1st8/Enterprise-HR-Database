#pragma once

#define BOOST_BEAST_USE_STD_STRING_VIEW

#include "../application.h"
#include "../resp_maker.h"

#include <boost/beast.hpp>
#include <deque>
#include <boost/json.hpp>
#include <functional>
#include <memory>
#include <optional>
#include <unordered_set>
#include <string_view>
#include <string>

namespace api_handler {
namespace net = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace json = boost::json;
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

class TimeTracker {
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;

public:
  TimeTracker() : start_time_(std::chrono::high_resolution_clock::now()) {}

  bool Has20MinutesPassed() {
    auto current_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::minutes>(current_time - start_time_);
    return elapsed_time >= std::chrono::minutes(20);
  }

  void reset_timer() {
    start_time_ = std::chrono::high_resolution_clock::now();
  }
};

struct Person {
    std::string email;
    std::string password;
    std::string role;

    auto operator<=>(const Person&) const = default;
};

struct PersonInfo {
    std::string email;
    std::string password;
    std::string name;
    std::string role;

    auto operator<=>(const PersonInfo&) const = default;
};

struct Tokens {
    std::string access_token;
    std::string refresh_token;
    TimeTracker tracker;

    auto operator<=>(const Tokens&) const = default;
};

struct RequestInfo {
    std::string target;
    std::string body;
    http::verb method;
    std::string content_type;
    int version;
    bool keep_alive;
    std::string auth;
};

class ApiHandler : public std::enable_shared_from_this<ApiHandler> {
  public:
    ApiHandler() = default;

    using ResponseInfo = resp_maker::detail::ResponseInfo;

    template <typename Body, typename Allocator, typename Send>
    void Handle(const http::request<Body, http::basic_fields<Allocator>>& req, Send&& send);

  private:
    std::function<void(ResponseInfo)> send_;
    RequestInfo req_info_{};
    db::Application application_{GetConfigFromEnv()};

    std::random_device random_device_;
    std::mt19937_64 generator1_{[this] {
        std::uniform_int_distribution<std::mt19937_64::result_type> dist;
        return dist(random_device_);
    }()};
    std::mt19937_64 generator2_{[this] {
        std::uniform_int_distribution<std::mt19937_64::result_type> dist;
        return dist(random_device_);
    }()};

    std::string GetUniqueToken() {
        std::stringstream stream;
        stream.fill('0');
        stream << std::hex << std::setw(16) << generator1_();
        stream << std::hex << std::setw(16) << generator2_();
        return stream.str();
    }

    bool CheckEndPath();
    std::string FindAndCutTarget(RequestInfo& req);
    void HandleApiResponse();

    void HandleGet();
    void HandleGetBusinessTrips();
    void HandleGetCompositionBusinessTrips();
    void HandleGetDepartments();
    void HandleGetEmployees();
    void HandleGetJobTitles();
    void HandleGetOrders();
    void HandleGetStaffingTable();
    void HandleGetTimeSheet();
    void HandleGetVacations();

    void HandleAdd();
    void HandleAddBusinessTrip();
    void HandleAddCompositionBusinessTrip();
    void HandleAddDepartment();
    void HandleAddEmployee();
    void HandleAddJobTitle();
    void HandleAddOrder();
    void HandleAddStaffingTable();
    void HandleAddTimeSheet();
    void HandleAddVacation();

    void HandleUpdate();
    void HandleUpdateBusinessTrip();
    void HandleUpdateCompositionBusinessTrip();
    void HandleUpdateDepartment();
    void HandleUpdateEmployee();
    void HandleUpdateJobTitle();
    void HandleUpdateOrder();
    void HandleUpdateStaffingTable();
    void HandleUpdateTimeSheet();
    void HandleUpdateVacation();

    void HandleRegister();
    void HandleLogin();
    void HandleLogout();
    void HandleToken();
    void HandleUser();

    template <typename Body, typename Allocator>
    RequestInfo ParseRequest(const http::request<Body, http::basic_fields<Allocator>>& req);

    ResponseInfo MakeResponse(http::status status, bool no_cache);

    void SendOkResponse(const std::string& body, bool no_cache = true);
    void SendBadRequestResponse(std::string message, std::string code =
                                "badRequest"s, bool no_cache = true);
    void SendBadRequestResponseDefault(bool no_cache = true) {
        SendBadRequestResponse("Bad request"s, "badRequest"s, no_cache);
    }
    void SendNotFoundResponse(const std::string& message =  "Table not found"s,
                              const std::string& key = "tableNotFound"s, bool no_cache = true);

    void SendNoAuthResponse(const std::string& message = "invalidToken"s,
                            const std::string& key = "Something wrong with token"s, bool no_cache = true);

    void SendWrongMethodResponseAllowedDelete(const std::string& message = "Only DELETE method is expected"s, bool no_cache = true);
    void SendWrongMethodResponseAllowedGetHead (const std::string& message = "Only GET/HEAD method is expected"s,
                                                bool no_cache = true);
    void SendWrongMethodResponseAllowedPost(const std::string& message = "Only POST method is expected"s, bool no_cache = true);
    void SendWrongMethodResponseAllowedPut(const std::string& message = "Only PUT method is expected"s, bool no_cache = true);
};

template <typename Body, typename Allocator, typename Send>
void ApiHandler::Handle(const http::request<Body, http::basic_fields<Allocator>>& req, Send&& send) {
    send_ = std::forward<Send>(send);
    req_info_ = ParseRequest(req);
    req_info_.target = req_info_.target.substr("/api"s.size());
    HandleApiResponse();
}

template <typename Body, typename Allocator>
RequestInfo ApiHandler::ParseRequest(const http::request<Body, http::basic_fields<Allocator>>& req) {
    RequestInfo result;
    result.target = req.target();
    result.body = req.body();
    result.method = req.method();
    result.version = req.version();
    result.keep_alive = req.keep_alive();

    if (req.find(http::field::content_type) != req.end()) {
        result.content_type = req.at(http::field::content_type);
    }
    if (req.find(http::field::authorization) != req.end()) {
        result.auth = req.at(http::field::authorization).substr(7);
    }

    return result;
}

template <typename Body, typename Allocator, typename Send>
void HandleApiRequest(http::request<Body, http::basic_fields<Allocator>>&& req,
                      Send&& send) {
    auto handler = std::make_shared<ApiHandler>();

    handler->Handle(req, [send = std::forward<Send>(send)](const resp_maker::detail::ResponseInfo& info){
        send(resp_maker::detail::MakeTextResponse<Body, Allocator>(info));
    });
}

} // namespace api_handler
