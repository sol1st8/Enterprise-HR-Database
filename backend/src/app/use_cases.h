#pragma once

#include <string>
#include <vector>

namespace ui {

namespace detail {

struct JobTitleInfo;
struct BusinessTripInfo;
struct DepartmentInfo;
struct EmployeeInfo;
struct VacationInfo;
struct OrderInfo;
struct CompositionBusinessTripInfo;
struct EmployeeInfo;
struct TimeSheetInfo;
struct StaffingTableInfo;

} // namespace detail

} // namespace ui

namespace app {

class UseCases {
  public:
    virtual void AddBusinessTrip(const ui::detail::BusinessTripInfo& trip) = 0;
    virtual void DeleteBusinessTrip(const ui::detail::BusinessTripInfo& trip) = 0;
    virtual void UpdateBusinessTrip(const ui::detail::BusinessTripInfo& trip) = 0;
    virtual std::vector<ui::detail::BusinessTripInfo> GetBusinessTrips() const = 0;

    virtual void AddCompositionBusinessTrip(const ui::detail::CompositionBusinessTripInfo& trip) = 0;
    virtual void DeleteCompositionBusinessTrip(const ui::detail::CompositionBusinessTripInfo& trip) = 0;
    virtual void UpdateCompositionBusinessTrip(const ui::detail::CompositionBusinessTripInfo& trip) = 0;
    virtual std::vector<ui::detail::CompositionBusinessTripInfo> GetCompositionBusinessTrips() const = 0;

    virtual void AddDepartment(const ui::detail::DepartmentInfo& dep) = 0;
    virtual void DeleteDepartment(const ui::detail::DepartmentInfo& dep) = 0;
    virtual void UpdateDepartment(const ui::detail::DepartmentInfo& dep) = 0;
    virtual std::vector<ui::detail::DepartmentInfo> GetDepartments() const = 0;

    virtual void AddEmployee(const ui::detail::EmployeeInfo& employee) = 0;
    virtual void DeleteEmployee(const ui::detail::EmployeeInfo& employee) = 0;
    virtual void UpdateEmployee(const ui::detail::EmployeeInfo& employee) = 0;
    virtual std::vector<ui::detail::EmployeeInfo> GetEmployees() const = 0;

    virtual void AddJobTitle(const ui::detail::JobTitleInfo& job_title) = 0;
    virtual void DeleteJobTitle(const ui::detail::JobTitleInfo& job_title) = 0;
    virtual void UpdateJobTitle(const ui::detail::JobTitleInfo& job_title) = 0;
    virtual std::vector<ui::detail::JobTitleInfo> GetJobTitles() const = 0;

    virtual void AddOrder(const ui::detail::OrderInfo& order) = 0;
    virtual void DeleteOrder(const ui::detail::OrderInfo& order) = 0;
    virtual void UpdateOrder(const ui::detail::OrderInfo& order) = 0;
    virtual std::vector<ui::detail::OrderInfo> GetOrders() const = 0;

    virtual void AddStaffingTable(const ui::detail::StaffingTableInfo& staffing_table) = 0;
    virtual void DeleteStaffingTable(const ui::detail::StaffingTableInfo& staffing_table) = 0;
    virtual void UpdateStaffingTable(const ui::detail::StaffingTableInfo& staffing_table) = 0;
    virtual std::vector<ui::detail::StaffingTableInfo> GetStaffingTable() const = 0;

    virtual void AddTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) = 0;
    virtual void DeleteTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) = 0;
    virtual void UpdateTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) = 0;
    virtual std::vector<ui::detail::TimeSheetInfo> GetTimeSheet() const = 0;

    virtual void AddVacation(const ui::detail::VacationInfo& vacation) = 0;
    virtual void DeleteVacation(const ui::detail::VacationInfo& vacation) = 0;
    virtual void UpdateVacation(const ui::detail::VacationInfo& vacation) = 0;
    virtual std::vector<ui::detail::VacationInfo> GetVacations() const = 0;

  protected:
    ~UseCases() = default;
};

} // namespace app
