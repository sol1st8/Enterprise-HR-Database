#pragma once

#include "use_cases.h"
#include "../domain/business_trip_fwd.h"
#include "../domain/composition_business_trip_fwd.h"
#include "../domain/department_fwd.h"
#include "../domain/employee_fwd.h"
#include "../domain/job_title_fwd.h"
#include "../domain/order_fwd.h"
#include "../domain/staffing_table_fwd.h"
#include "../domain/time_sheet_fwd.h"
#include "../domain/vacation_fwd.h"

namespace app {

class UseCasesImpl : public UseCases {
  public:
    explicit UseCasesImpl(domain::BusinessTripRepository& trips,
                          domain::CompositionBusinessTripRepository& composition_trips,
                          domain::DepartmentRepository& deps,
                          domain::EmployeeRepository& employees,
                          domain::JobTitleRepository& job_titles,
                          domain::OrderRepository& orders,
                          domain::StaffingTableRepository& staffing_table,
                          domain::TimeSheetRepository& time_sheet,
                          domain::VacationRepository& vacations);

    void AddBusinessTrip(const ui::detail::BusinessTripInfo& trip) override;
    void UpdateBusinessTrip(const ui::detail::BusinessTripInfo& trip, int id) override;
    std::vector<ui::detail::BusinessTripInfo> GetBusinessTrips() const override;
    std::vector<ui::detail::BusinessTripInfo> GetBusinessTripsForPerson(int personnel_number) const override;

    void AddCompositionBusinessTrip(const ui::detail::CompositionBusinessTripInfo& trip) override;
    void DeleteCompositionBusinessTrip(const ui::detail::CompositionBusinessTripInfo& trip, int id) override;
    void UpdateCompositionBusinessTrip(const ui::detail::CompositionBusinessTripInfo& trip, int id) override;
    std::vector<ui::detail::CompositionBusinessTripInfo> GetCompositionBusinessTrips() const override;
    std::vector<ui::detail::CompositionBusinessTripInfo> GetCompositionBusinessTripsForPerson(int personnel_number) const override;

    void AddDepartment(const ui::detail::DepartmentInfo& dep) override;
    void UpdateDepartment(const ui::detail::DepartmentInfo& dep, int id) override;
    std::vector<ui::detail::DepartmentInfo> GetDepartments() const override;

    void AddEmployee(const ui::detail::EmployeeInfo& employee) override;
    void UpdateEmployee(const ui::detail::EmployeeInfo& employee, int id) override;
    std::vector<ui::detail::EmployeeInfo> GetEmployees() const override;
    std::vector<ui::detail::EmployeeInfo> GetEmployeeForPerson(int personnel_number) const override;

    void AddJobTitle(const ui::detail::JobTitleInfo& job_title) override;
    void UpdateJobTitle(const ui::detail::JobTitleInfo& job_title, int id) override;
    std::vector<ui::detail::JobTitleInfo> GetJobTitles() const override;

    void AddOrder(const ui::detail::OrderInfo& order) override;
    void UpdateOrder(const ui::detail::OrderInfo& order, int id) override;
    std::vector<ui::detail::OrderInfo> GetOrders() const override;
    std::vector<ui::detail::OrderInfo> GetOrdersForPerson(int personnel_number) const override;

    void AddStaffingTable(const ui::detail::StaffingTableInfo& staffing_table) override;
    void UpdateStaffingTable(const ui::detail::StaffingTableInfo& staffing_table, int id) override;
    std::vector<ui::detail::StaffingTableInfo> GetStaffingTable() const override;

    void AddTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) override;
    void UpdateTimeSheet(const ui::detail::TimeSheetInfo& time_sheet, int id) override;
    std::vector<ui::detail::TimeSheetInfo> GetTimeSheet() const override;
    std::vector<ui::detail::TimeSheetInfo> GetTimeSheetForPerson(int personnel_number) const override;

    void AddVacation(const ui::detail::VacationInfo& vacation) override;
    void UpdateVacation(const ui::detail::VacationInfo& vacation, int id) override;
    std::vector<ui::detail::VacationInfo> GetVacations() const override;
    std::vector<ui::detail::VacationInfo> GetVacationForPerson(int personnel_number) const override;

    int GetCountBusinessTrips() const override;
    int GetCountDepartments() const override;
    int GetCountEmployees() const override;
    int GetCountJobTitles() const override;
    int GetCountOrders() const override;
    int GetCountStaffingTable() const override;
    int GetCountTimeSheet() const override;
    int GetCountVacations() const override;

    std::string GetOrganization(int trip_id) const override;
    int GetTripId(const std::string& organization) const override;

    std::string GetDepartment(int id) const override;
    int GetDepartmentId(const std::string& dep) const override;

    std::unordered_set<std::string> GetEmails() const override;

    std::optional<std::string> GetDateOfDismissal(int personnel_number) const override;
    std::string GetStartDateOfBusinessTrip(int trip_id) const override;

    int GetPersonnelNumberForEmail(const std::string& email) const override;

    std::string GetJobTitle(int id) const override;
    int GetJobTitleId(const std::string& job_title) const override;

  private:
    domain::BusinessTripRepository& trips_;
    domain::CompositionBusinessTripRepository& composition_trips_;
    domain::DepartmentRepository& deps_;
    domain::EmployeeRepository& employees_;
    domain::JobTitleRepository& job_titles_;
    domain::OrderRepository& orders_;
    domain::StaffingTableRepository& staffing_table_;
    domain::TimeSheetRepository& time_sheet_;
    domain::VacationRepository& vacations_;
};

} // namespace app
