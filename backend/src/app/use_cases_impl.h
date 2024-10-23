#pragma once

#include "../domain/department_fwd.h"
#include "../domain/job_title_fwd.h"
#include "use_cases.h"

namespace app {

class UseCasesImpl : public UseCases {
  public:
    explicit UseCasesImpl(domain::DepartmentRepository& deps, domain::JobTitleRepository& job_titles);

    void AddJobTitle(const ui::detail::JobTitleInfo& job_title) override;
    void DeleteJobTitle(const ui::detail::JobTitleInfo& job_title) override;
    void UpdateJobTitle(const ui::detail::JobTitleInfo& job_title) override;
    std::vector<ui::detail::JobTitleInfo> GetJobTitles() const override;

    void AddDepartment(const ui::detail::DepartmentInfo& dep) override;
    void DeleteDepartment(const ui::detail::DepartmentInfo& dep) override;
    void UpdateDepartment(const ui::detail::DepartmentInfo& dep) override;
    std::vector<ui::detail::DepartmentInfo> GetDepartments() const override;

  private:
    domain::DepartmentRepository& deps_;
    domain::JobTitleRepository& job_titles_;
};

} // namespace app
