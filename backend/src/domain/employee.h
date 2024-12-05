#pragma once

#include "../ui/view.h"

#include <memory>
#include <unordered_set>

namespace domain {

class Worker;

class Employee {
  public:
    Employee(int personnel_number, std::string full_name, std::string gender, std::string birthday,
             int job_title_id, int department_id, std::optional<int> experience, std::string number,
             std::string registration, std::string education, std::string date,
             std::string mail, std::string marital_status, std::optional<std::string> date_of_dismissal) : personnel_number_(personnel_number)
                                                                                                         , full_name_(std::move(full_name))
                                                                                                         , birthday_(std::move(birthday))
                                                                                                         , gender_(std::move(gender))
                                                                                                         , job_title_id_(job_title_id)
                                                                                                         , department_id_(department_id)
                                                                                                         , experience_(experience)
                                                                                                         , number_(std::move(number))
                                                                                                         , registration_(std::move(registration))
                                                                                                         , education_(std::move(education))
                                                                                                         , date_(std::move(date))
                                                                                                         , mail_(std::move(mail))
                                                                                                         , marital_status_(std::move(marital_status))
                                                                                                         , date_of_dismissal_(std::move(date_of_dismissal)) {}

    int GetPersonnelNumber() const noexcept {
        return personnel_number_;
    }

    const std::string& GetFullName() const noexcept {
        return full_name_;
    }

    const std::string& GetGender() const noexcept {
        return gender_;
    }

    const std::string& GetBirthday() const noexcept {
        return birthday_;
    }

    int GetJobTitleId() const noexcept {
        return job_title_id_;
    }

    int GetDepartmentId() const noexcept {
        return department_id_;
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

    const std::string& GetDate() const noexcept {
        return date_;
    }

    const std::string& GetMail() const noexcept {
        return mail_;
    }

    const std::string& GetMerialStatus() const noexcept {
        return marital_status_;
    }

    const std::optional<std::string>& GetDateOfDismissal() const noexcept {
        return date_of_dismissal_;
    }

  private:
    int personnel_number_;
    std::string full_name_;
    std::string gender_;
    std::string birthday_;
    int job_title_id_;
    int department_id_;
    std::optional<int> experience_;
    std::string number_;
    std::string registration_;
    std::string education_;
    std::string date_;
    std::string mail_;
    std::string marital_status_;
    std::optional<std::string> date_of_dismissal_;
};

class EmployeeRepository {
  public:
    virtual std::vector<ui::detail::EmployeeInfo> Get() const = 0;
    virtual std::vector<ui::detail::EmployeeInfo> GetForPerson(int personnel_number) const = 0;
    virtual std::vector<ui::detail::FreeJobTitleInfo> GetFreeJobTitles() const = 0;

    virtual std::shared_ptr<domain::Worker> GetWorker() const = 0;

    virtual int GetCount() const = 0;

    virtual std::optional<std::string> GetDateOfDismissal(int personnel_number) const = 0;
    virtual std::unordered_set<std::string> GetEmails() const = 0;
    virtual int GetPersonnelNumberForEmail(const std::string& email) const = 0;

    virtual std::string GetFio(int id) const = 0;
    virtual int GetId(const std::string& fio) const = 0;

  protected:
    ~EmployeeRepository() = default;
};

} // namespace domain
