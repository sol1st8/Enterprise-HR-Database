#pragma once

#include "../ui/view.h"

#include <memory>
#include <string>
#include <vector>

namespace domain {

class Worker;

class Department {
  public:
    Department(int department_id, int manager_personnel_number, std::string dep_name, int office_num) : department_id_(department_id)
                                                                                                      , manager_personnel_number_(manager_personnel_number)
                                                                                                      , dep_name_(std::move(dep_name))
                                                                                                      , office_num_(office_num) {}

    int GetDepartmentId() const noexcept {
        return department_id_;
    }

    int GetManagerPersonalNum() const noexcept {
        return manager_personnel_number_;
    }

    const std::string& GetDepName() const noexcept {
        return dep_name_;
    }

    int GetOfficeNum() const noexcept {
        return office_num_;
    }

  private:
    int department_id_;
    int manager_personnel_number_;
    std::string dep_name_;
    int office_num_;
};

class DepartmentRepository {
  public:
    virtual std::vector<ui::detail::DepartmentInfo> Get() const = 0;

    virtual std::shared_ptr<domain::Worker> GetWorker() const = 0;

    virtual int GetCount() const = 0;

  protected:
    ~DepartmentRepository() = default;
};

} // namespace domain
