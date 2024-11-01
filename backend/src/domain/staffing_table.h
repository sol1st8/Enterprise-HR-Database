#pragma once

#include "../ui/view.h"

#include <memory>
#include <string>
#include <vector>

namespace domain {

class Worker;

class StaffingTable {
  public:
    StaffingTable(int staffing_table_id, int job_title_id, int department_id,
                  int salary, int time_job) : staffing_table_id_(staffing_table_id)
                                            , job_title_id_(job_title_id)
                                            , department_id_(department_id)
                                            , salary_(salary)
                                            , time_job_(time_job) {}

    int GetStaffingTableId() const noexcept {
        return staffing_table_id_;
    }

    int GetJobTitleId() const noexcept {
        return job_title_id_;
    }

    int GetDepartmentId() const noexcept {
        return department_id_;
    }

    int GetSalary() const noexcept {
        return salary_;
    }

    int GetTimeJob() const noexcept {
        return time_job_;
    }

  private:
    int staffing_table_id_;
    int job_title_id_;
    int department_id_;
    int salary_;
    int time_job_ = 1;
};

class StaffingTableRepository {
  public:
    virtual std::vector<ui::detail::StaffingTableInfo> Get() const = 0;

    virtual std::shared_ptr<domain::Worker> GetWorker() const = 0;

    virtual int GetCount() const = 0;

  protected:
    ~StaffingTableRepository() = default;
};

} // namespace domain
