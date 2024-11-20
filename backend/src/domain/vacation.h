#pragma once

#include "../ui/view.h"

#include <memory>

namespace domain {

class Worker;

class Vacation {
  public:
    Vacation(int vacation_id, int personnel_number, std::string type,
             std::string from_date, std::string to_date,
             int days, std::string leave_basis) : vacation_id_(vacation_id)
                                                , personnel_number_(personnel_number)
                                                , type_(std::move(type))
                                                , from_date_(std::move(from_date))
                                                , to_date_(std::move(to_date))
                                                , days_(days)
                                                , leave_basis_(std::move(leave_basis)) {}

    int GetVacationId() const noexcept {
        return vacation_id_;
    }

    int GetPersonnelNumber() const noexcept {
        return personnel_number_;
    }

    const std::string& GetType() const noexcept {
        return type_;
    }

    const std::string& GetFromDate() const noexcept {
        return from_date_;
    }

    const std::string& GetToDate() const noexcept {
        return to_date_;
    }

    int GetDays() const noexcept {
        return days_;
    }

    std::string GetLeaveBasis() const noexcept {
        return leave_basis_;
    }

  private:
    int vacation_id_;
    int personnel_number_;
    std::string type_;
    std::string from_date_;
    std::string to_date_;
    int days_;
    std::string leave_basis_;
};

class VacationRepository {
  public:
    virtual std::vector<ui::detail::VacationInfo> Get() const = 0;
    virtual std::vector<ui::detail::VacationInfo> GetForPerson(int personnel_number) const = 0;

    virtual std::shared_ptr<domain::Worker> GetWorker() const = 0;

    virtual int GetCount() const = 0;

  protected:
    ~VacationRepository() = default;
};

} // namespace domain
