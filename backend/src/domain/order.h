#pragma once

#include "../ui/view.h"

#include <memory>
#include <string>
#include <vector>

namespace domain {

class Worker;

class Order {
  public:
    Order(int order_id, int personnel_number, std::string content, std::string date = "") : order_id_(order_id)
                                                                                          , personnel_number_(personnel_number)
                                                                                          , content_(std::move(content))
                                                                                          , date_(std::move(date)) {
        if (date_.empty()) {
            date_ = std::move(GetCurrentDate());
        }
    }

    int GetOrderId() const noexcept {
        return order_id_;
    }

    int GetPersonnelNumber() const noexcept {
        return personnel_number_;
    }

    const std::string& GetContent() const noexcept {
        return content_;
    }

    const std::string& GetDate() const noexcept {
        return date_;
    }

  private:
    int order_id_;
    int personnel_number_;
    std::string content_;
    std::string date_;

    static std::string GetCurrentDate() {
        const auto now = std::chrono::system_clock::now();
        const auto t_c = std::chrono::system_clock::to_time_t(now);

        std::ostringstream oss;
        oss << std::put_time(std::gmtime(&t_c), "%Y_%m_%d");
        return oss.str();
    }
};

class OrderRepository {
  public:
    virtual std::vector<ui::detail::OrderInfo> Get() const = 0;

    virtual std::shared_ptr<domain::Worker> GetWorker() const = 0;

    virtual int GetCount() const = 0;

  protected:
    ~OrderRepository() = default;
};

} // namespace domain
