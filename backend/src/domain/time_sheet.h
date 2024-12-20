#pragma once

#include "../ui/view.h"

#include <memory>

namespace domain {

class Worker;

class TimeSheet {
  public:
    TimeSheet(int time_sheet_id, int personnel_number,
              int time_worked, std::string month, std::string year) : time_sheet_id_(time_sheet_id)
                                                                    , personnel_number_(personnel_number)
                                                                    , time_worked_(time_worked)
                                                                    , month_(std::move(month))
                                                                    , year_(std::move(year)) {}

    int GetTimeSheetId() const noexcept {
        return time_sheet_id_;
    }

    int GetPersonnelNumber() const noexcept {
        return personnel_number_;
    }

    int GetTimeWorked() const noexcept {
        return time_worked_;
    }

    const std::string& GetMonth() const noexcept {
        return month_;
    }

    const std::string& GetYear() const noexcept {
        return year_;
    }

  private:
    int time_sheet_id_;
    int personnel_number_;
    int time_worked_;
    std::string month_;
    std::string year_;
};

class TimeSheetRepository {
  public:
    virtual std::vector<ui::detail::TimeSheetInfo> Get() const = 0;
    virtual std::vector<ui::detail::TimeSheetInfo> GetForPerson(int personnel_number) const = 0;

    virtual std::shared_ptr<domain::Worker> GetWorker() const = 0;

    virtual int GetCount() const = 0;

  protected:
    ~TimeSheetRepository() = default;
};

}; // namespace domain
