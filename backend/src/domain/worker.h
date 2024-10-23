#pragma once

#include "department.h"
#include "../ui/view.h"

#include <string>

namespace domain {

class Worker {
  public:
    virtual void AddDepartment(const domain::Department& dep) = 0;

    virtual void Commit() = 0;

  protected:
    virtual ~Worker() = default;
};

} // namespace domain
