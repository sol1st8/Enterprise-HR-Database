#pragma once

#include "department.h"
#include "job_title.h"
#include "time_sheet.h"
#include "../ui/view.h"

#include <string>

namespace domain {

class Worker {
  public:
    virtual void AddJobTitle(const domain::JobTitle& job_title) = 0;
    virtual void DeleteJobTitle(const domain::JobTitle& job_title) = 0;
    virtual void UpdateJobTitle(const domain::JobTitle& job_title) = 0;

    virtual void AddDepartment(const domain::Department& dep) = 0;
    virtual void DeleteDepartment(const domain::Department& dep) = 0;
    virtual void UpdateDepartment(const domain::Department& dep) = 0;

    virtual void AddTimeSheet(const domain::TimeSheet& time_sheet) = 0;
    virtual void DeleteTimeSheet(const domain::TimeSheet& time_sheet) = 0;
    virtual void UpdateTimeSheet(const domain::TimeSheet& time_sheet) = 0;

    virtual void Commit() = 0;

  protected:
    virtual ~Worker() = default;
};

} // namespace domain
