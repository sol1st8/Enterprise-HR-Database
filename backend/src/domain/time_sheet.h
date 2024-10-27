#pragma once

#include "../ui/view.h"

#include <memory>
#include <string>
#include <vector>

namespace domain {

class Worker;

class TimeSheet {
  public:
    TimeSheet(int time_sheet_id, int personnel_number, int time_worked, std::string month) : time_sheet_id_(time_sheet_id)
                                                                                                , personnel_number_(personnel_number)
                                                                                                , time_worked_(time_worked)
                                                                                                , month_(month) {}

    int GetTimeSheetId() const noexcept {
        return time_sheet_id_;
    }

    int GetPersonnelNumber() const noexcept {
        return personnel_number_;
    }

    int GetTimeWorked() const noexcept {
        return time_worked_;
    }

    std::string GetMonth() const noexcept {
        return month_;
    }

  private:
    int time_sheet_id_;
    int personnel_number_;
    int time_worked_;
    std::string month_;
};

class TimeSheetRepository {
  public:
    virtual std::vector<ui::detail::TimeSheetInfo> Get() const = 0;

    virtual std::shared_ptr<domain::Worker> GetWorker() const = 0;

  protected:
    ~TimeSheetRepository() = default;
};

}; // namespace domain
