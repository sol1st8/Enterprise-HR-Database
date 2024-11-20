#pragma once

#include "../ui/view.h"

#include <memory>

namespace domain {

class Worker;

class Order {
  public:
    Order(int order_id, int personnel_number,
          std::string date, std::string content) : order_id_(order_id)
                                                 , personnel_number_(personnel_number)
                                                 , date_(std::move(date))
                                                 , content_(std::move(content)) {}

    int GetOrderId() const noexcept {
        return order_id_;
    }

    int GetPersonnelNumber() const noexcept {
        return personnel_number_;
    }

    const std::string& GetDate() const noexcept {
        return date_;
    }

    const std::string& GetContent() const noexcept {
        return content_;
    }

  private:
    int order_id_;
    int personnel_number_;
    std::string date_;
    std::string content_;
};

class OrderRepository {
  public:
    virtual std::vector<ui::detail::OrderInfo> Get() const = 0;
    virtual std::vector<ui::detail::OrderInfo> GetForPerson(int personnel_number) const = 0;

    virtual std::shared_ptr<domain::Worker> GetWorker() const = 0;

    virtual int GetCount() const = 0;

  protected:
    ~OrderRepository() = default;
};

} // namespace domain
