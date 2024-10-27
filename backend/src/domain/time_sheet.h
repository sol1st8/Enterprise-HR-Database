#pragma once

#include "../ui/view.h"

#include <optional>
#include <memory>
#include <string>
#include <vector>

namespace domain {

class Worker;

class TimeSheet {
  public:
    TimeSheet(int time_sheet_id, int job_title_id, int department_id, int time_job, int salary) : time_sheet_id_(time_sheet_id)
                                                                                                , job_title_id_(job_title_id)
                                                                                                , department_id_(department_id)
                                                                                                , salary_(salary)
                                                                                                , time_job_(time_job) {}

    int GetTimeSheetId() const noexcept {
        return time_sheet_id_;
    }

    int GetJobTitleId() const noexcept {
        return job_title_id_;
    }

    int GetDepartmentId() const noexcept {
        return department_id_;
    }

    int GetTimeJob() const noexcept {
        return time_job_;
    }

    int GetSalary() const noexcept {
        return salary_;
    }

  private:
    int time_sheet_id_;
    int job_title_id_;
    int department_id_;
    int salary_;
    int time_job_ = 1;
};

class TimeSheetRepository {
  public:
    virtual std::vector<ui::detail::TimeSheetInfo> Get() const = 0;

    virtual std::shared_ptr<domain::Worker> GetWorker() const = 0;

  protected:
    ~TimeSheetRepository() = default;
};

}; // namespace domain
