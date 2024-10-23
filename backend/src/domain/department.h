#pragma once

#include "../ui/view.h"

#include <optional>
#include <memory>
#include <string>
#include <vector>

namespace domain {

class Worker;

class Department {
  public:
    Department(int id, int manager_personal_num, std::string dep_name, int office_num) : id_(id)
                                                                                       , manager_personal_num_(manager_personal_num)
                                                                                       , dep_name_(std::move(dep_name))
                                                                                       , office_num_(office_num) {}

    int GetId() const noexcept {
        return id_;
    }

    int GetManagerPersonalNum() const noexcept {
        return manager_personal_num_;
    }

    const std::string& GetDepName() const noexcept {
        return dep_name_;
    }

    int GetOfficeNum() const noexcept {
        return office_num_;
    }

  private:
    int id_;
    int manager_personal_num_;
    std::string dep_name_;
    int office_num_;
};

class DepartmentRepository {
  public:
    virtual std::vector<ui::detail::DepartmentInfo> Get() const = 0;

    virtual std::shared_ptr<domain::Worker> GetWorker() const = 0;

  protected:
    ~DepartmentRepository() = default;
};

} // namespace domain
