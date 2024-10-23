#pragma once

#include "department.h"
#include "job_title.h"
#include "../ui/view.h"

#include <string>

namespace domain {

class Worker {
  public:
    virtual void AddDepartment(const domain::Department& dep) = 0;
    virtual void DeleteDepartment(const domain::Department& dep) = 0;
    virtual void UpdateDepartment(const domain::Department& dep) = 0;

    virtual void AddJobTitle(const domain::JobTitle& dep) = 0;
    virtual void DeleteJobTitle(const domain::JobTitle& dep) = 0;
    virtual void UpdateJobTitle(const domain::JobTitle& dep) = 0;

    virtual void Commit() = 0;

  protected:
    virtual ~Worker() = default;
};

} // namespace domain
