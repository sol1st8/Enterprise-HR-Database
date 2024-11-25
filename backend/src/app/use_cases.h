#pragma once

#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

namespace ui {

namespace detail {

struct BusinessTripInfo;
struct CompositionBusinessTripInfo;
struct DepartmentInfo;
struct EmployeeInfo;
struct JobTitleInfo;
struct OrderInfo;
struct StaffingTableInfo;
struct TimeSheetInfo;
struct VacationInfo;

} // namespace detail

} // namespace ui

namespace app {

class UseCases {
  public:
    virtual void AddBusinessTrip(const ui::detail::BusinessTripInfo& trip) = 0;
    virtual void UpdateBusinessTrip(const ui::detail::BusinessTripInfo& trip, int id) = 0;
    virtual std::vector<ui::detail::BusinessTripInfo> GetBusinessTrips() const = 0;
    virtual std::vector<ui::detail::BusinessTripInfo> GetBusinessTripsForPerson(int personnel_number) const = 0;

    virtual void AddCompositionBusinessTrip(const ui::detail::CompositionBusinessTripInfo& trip) = 0;
    virtual void DeleteCompositionBusinessTrip(const ui::detail::CompositionBusinessTripInfo& trip, int id) = 0;
    virtual void UpdateCompositionBusinessTrip(const ui::detail::CompositionBusinessTripInfo& trip, int id) = 0;
    virtual std::vector<ui::detail::CompositionBusinessTripInfo> GetCompositionBusinessTrips() const = 0;
    virtual std::vector<ui::detail::CompositionBusinessTripInfo> GetCompositionBusinessTripsForPerson(int personnel_number) const = 0;

    virtual void AddDepartment(const ui::detail::DepartmentInfo& dep) = 0;
    virtual void UpdateDepartment(const ui::detail::DepartmentInfo& dep, int id) = 0;
    virtual std::vector<ui::detail::DepartmentInfo> GetDepartments() const = 0;

    virtual void AddEmployee(const ui::detail::EmployeeInfo& employee) = 0;
    virtual void UpdateEmployee(const ui::detail::EmployeeInfo& employee, int id) = 0;
    virtual std::vector<ui::detail::EmployeeInfo> GetEmployees() const = 0;
    virtual std::vector<ui::detail::EmployeeInfo> GetEmployeeForPerson(int personnel_number) const = 0;

    virtual void AddJobTitle(const ui::detail::JobTitleInfo& job_title) = 0;
    virtual void UpdateJobTitle(const ui::detail::JobTitleInfo& job_title, int id) = 0;
    virtual std::vector<ui::detail::JobTitleInfo> GetJobTitles() const = 0;

    virtual void AddOrder(const ui::detail::OrderInfo& order) = 0;
    virtual void UpdateOrder(const ui::detail::OrderInfo& order, int id) = 0;
    virtual std::vector<ui::detail::OrderInfo> GetOrders() const = 0;
    virtual std::vector<ui::detail::OrderInfo> GetOrdersForPerson(int personnel_number) const = 0;

    virtual void AddStaffingTable(const ui::detail::StaffingTableInfo& staffing_table) = 0;
    virtual void UpdateStaffingTable(const ui::detail::StaffingTableInfo& staffing_table, int id) = 0;
    virtual std::vector<ui::detail::StaffingTableInfo> GetStaffingTable() const = 0;

    virtual void AddTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) = 0;
    virtual void UpdateTimeSheet(const ui::detail::TimeSheetInfo& time_sheet, int id) = 0;
    virtual std::vector<ui::detail::TimeSheetInfo> GetTimeSheet() const = 0;
    virtual std::vector<ui::detail::TimeSheetInfo> GetTimeSheetForPerson(int personnel_number) const = 0;

    virtual void AddVacation(const ui::detail::VacationInfo& vacation) = 0;
    virtual void UpdateVacation(const ui::detail::VacationInfo& vacation, int id) = 0;
    virtual std::vector<ui::detail::VacationInfo> GetVacations() const = 0;
    virtual std::vector<ui::detail::VacationInfo> GetVacationForPerson(int personnel_number) const = 0;

    virtual int GetCountBusinessTrips() const = 0;
    virtual int GetCountDepartments() const = 0;
    virtual int GetCountEmployees() const = 0;
    virtual int GetCountJobTitles() const = 0;
    virtual int GetCountOrders() const = 0;
    virtual int GetCountStaffingTable() const = 0;
    virtual int GetCountTimeSheet() const = 0;
    virtual int GetCountVacations() const = 0;

    virtual std::string GetOrganization(int trip_id) const = 0;
    virtual int GetTripId(const std::string& organization) const = 0;

    virtual std::string GetDepartment(int id) const = 0;
    virtual int GetDepartmentId(const std::string& dep) const = 0;

    virtual std::unordered_set<std::string> GetEmails() const = 0;

    virtual std::optional<std::string> GetDateOfDismissal(int personnel_number) const = 0;
    virtual std::string GetStartDateOfBusinessTrip(int trip_id) const = 0;

    virtual int GetPersonnelNumberForEmail(const std::string& email) const = 0;

    virtual std::string GetJobTitle(int id) const = 0;
    virtual int GetJobTitleId(const std::string& job_title) const = 0;

  protected:
    ~UseCases() = default;
};

} // namespace app
