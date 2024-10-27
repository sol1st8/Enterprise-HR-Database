#pragma once

#include "../domain/department_fwd.h"
#include "../domain/job_title_fwd.h"
#include "../domain/staffing_table_fwd.h"
#include "../domain/time_sheet_fwd.h"
#include "use_cases.h"

namespace app {

class UseCasesImpl : public UseCases {
  public:
    explicit UseCasesImpl(domain::DepartmentRepository& deps, domain::JobTitleRepository& job_titles,
                          domain::StaffingTableRepository& staffing_table, domain::TimeSheetRepository& time_sheet);

    void AddDepartment(const ui::detail::DepartmentInfo& dep) override;
    void DeleteDepartment(const ui::detail::DepartmentInfo& dep) override;
    void UpdateDepartment(const ui::detail::DepartmentInfo& dep) override;
    std::vector<ui::detail::DepartmentInfo> GetDepartments() const override;

    void AddJobTitle(const ui::detail::JobTitleInfo& job_title) override;
    void DeleteJobTitle(const ui::detail::JobTitleInfo& job_title) override;
    void UpdateJobTitle(const ui::detail::JobTitleInfo& job_title) override;
    std::vector<ui::detail::JobTitleInfo> GetJobTitles() const override;

    void AddStaffingTable(const ui::detail::StaffingTableInfo& staffing_table) override;
    void DeleteStaffingTable(const ui::detail::StaffingTableInfo& staffing_table) override;
    void UpdateStaffingTable(const ui::detail::StaffingTableInfo& staffing_table) override;
    std::vector<ui::detail::StaffingTableInfo> GetStaffingTable() const override;

    void AddTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) override;
    void DeleteTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) override;
    void UpdateTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) override;
    std::vector<ui::detail::TimeSheetInfo> GetTimeSheet() const override;

  private:
    domain::DepartmentRepository& deps_;
    domain::JobTitleRepository& job_titles_;
    domain::StaffingTableRepository& staffing_table_;
    domain::TimeSheetRepository& time_sheet_;
};

} // namespace app
