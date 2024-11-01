#pragma once

#include "../ui/view.h"

#include <memory>

namespace domain {

class Worker;

class Employee {
  public:
    Employee(int personnel_number, std::string full_name, int job_title_id,
             std::optional<int> experience, std::string number, std::string registration,
             std::string education, std::string mail, std::string gender,
             std::string marital_status, std::string date = "") : personnel_number_(personnel_number)
                                                                , full_name_(std::move(full_name))
                                                                , job_title_id_(job_title_id)
                                                                , experience_(experience)
                                                                , number_(std::move(number))
                                                                , registration_(std::move(registration))
                                                                , education_(std::move(education))
                                                                , mail_(std::move(mail))
                                                                , gender_(std::move(gender))
                                                                , marital_status_(std::move(marital_status))
                                                                , date_(std::move(date)) {
        if (date_.empty()) {
            date_ = std::move(GetCurrentDate());
        }
    }

    int GetPersonnelNumber() const noexcept {
        return personnel_number_;
    }

    const std::string& GetFullName() const noexcept {
        return full_name_;
    }

    int GetJobTitleId() const noexcept {
        return job_title_id_;
    }

    std::optional<int> GetExperience() const noexcept {
        return experience_;
    }

    const std::string& GetNumber() const noexcept {
        return number_;
    }

    const std::string& GetRegistration() const noexcept {
        return registration_;
    }

    const std::string& GetEducation() const noexcept {
        return education_;
    }

    const std::string& GetMail() const noexcept {
        return mail_;
    }

    const std::string&  GetGender() const noexcept {
        return gender_;
    }

    const std::string& GetMerialStatus() const noexcept {
        return marital_status_;
    }

    const std::string& GetDate() const noexcept {
        return date_;
    }

  private:
    int personnel_number_;
    std::string full_name_;
    int job_title_id_;
    std::optional<int> experience_;
    std::string number_;
    std::string registration_;
    std::string education_;
    std::string mail_;
    std::string gender_ = "м";
    std::string marital_status_ = "холост";
    std::string date_;

    static std::string GetCurrentDate() {
        const auto now = std::chrono::system_clock::now();
        const auto t_c = std::chrono::system_clock::to_time_t(now);

        std::ostringstream oss;
        oss << std::put_time(std::gmtime(&t_c), "%Y_%m_%d");
        return oss.str();
    }
};

class EmployeeRepository {
  public:
    virtual std::vector<ui::detail::EmployeeInfo> Get() const = 0;

    virtual std::shared_ptr<domain::Worker> GetWorker() const = 0;

    virtual int GetCount() const = 0;

  protected:
    ~EmployeeRepository() = default;
};

} // namespace domain
