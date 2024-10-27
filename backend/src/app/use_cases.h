#pragma once

#include <optional>
#include <string>
#include <vector>

namespace ui {

namespace detail {

struct JobTitleInfo;
//struct BusinessTrip;
struct DepartmentInfo;
//struct Vacation;
//struct Order;
//struct СompositionBusinessTrip;
//struct Employee;
struct TimeSheetInfo;
//struct StaffingTable;

} // namespace detail

} // namespace ui

namespace app {

class UseCases {
  public:
    virtual void AddJobTitle(const ui::detail::JobTitleInfo& job_title) = 0;
    virtual void DeleteJobTitle(const ui::detail::JobTitleInfo& job_title) = 0;
    virtual void UpdateJobTitle(const ui::detail::JobTitleInfo& job_title) = 0;
    virtual std::vector<ui::detail::JobTitleInfo> GetJobTitles() const = 0;

    /*virtual void AddBusinessTrip(const std::string& country, const std::string& city,
                                 const std::string& organization, const std::string& from_date,
                                 const std::string& to_date, int days, const std::string& target) = 0;
    virtual std::vector<ui::detail::BusinessTrip> GetBusinessTrips() = 0;
    */

    virtual void AddDepartment(const ui::detail::DepartmentInfo& dep) = 0;
    virtual void DeleteDepartment(const ui::detail::DepartmentInfo& dep) = 0;
    virtual void UpdateDepartment(const ui::detail::DepartmentInfo& dep) = 0;
    virtual std::vector<ui::detail::DepartmentInfo> GetDepartments() const = 0;

    virtual void AddTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) = 0;
    virtual void DeleteTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) = 0;
    virtual void UpdateTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) = 0;
    virtual std::vector<ui::detail::TimeSheetInfo> GetTimeSheet() const = 0;

  protected:
    ~UseCases() = default;
};

} // namespace app
