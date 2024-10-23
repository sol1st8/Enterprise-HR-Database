#pragma once

#include "../domain/department_fwd.h"
#include "use_cases.h"

namespace app {

class UseCasesImpl : public UseCases {
  public:
    explicit UseCasesImpl(domain::DepartmentRepository& deps);

    void AddDepartment(ui::detail::DepartmentInfo& dep) override;
    std::vector<ui::detail::DepartmentInfo> GetDepartments() override;

  private:
    domain::DepartmentRepository& deps_;
};

} // namespace app
