#pragma once

#include "../domain/business_trip_fwd.h"
#include "../domain/composition_business_trip_fwd.h"
#include "../domain/department_fwd.h"
#include "../domain/employee_fwd.h"
#include "../domain/job_title_fwd.h"
#include "../domain/order_fwd.h"
#include "../domain/staffing_table_fwd.h"
#include "../domain/time_sheet_fwd.h"
#include "../domain/vacation_fwd.h"
#include "use_cases.h"

namespace app {

class UseCasesImpl : public UseCases {
  public:
    explicit UseCasesImpl(domain::BusinessTripRepository& trips,
                          domain::CompositionBusinessTripRepository& composition_trips,
                          domain::DepartmentRepository& deps,
                          domain::EmployeeRepository& employees,
                          domain::JobTitleRepository& job_titles,
                          domain::OrderRepository& order,
                          domain::StaffingTableRepository& staffing_table,
                          domain::TimeSheetRepository& time_sheet,
                          domain::VacationRepository& vacation);

    void AddBusinessTrip(const ui::detail::BusinessTripInfo& trip) override;
    void DeleteBusinessTrip(const ui::detail::BusinessTripInfo& trip) override;
    void UpdateBusinessTrip(const ui::detail::BusinessTripInfo& trip) override;
    std::vector<ui::detail::BusinessTripInfo> GetBusinessTrips() const override;

    void AddCompositionBusinessTrip(const ui::detail::CompositionBusinessTripInfo& trip) override;
    void DeleteCompositionBusinessTrip(const ui::detail::CompositionBusinessTripInfo& trip) override;
    void UpdateCompositionBusinessTrip(const ui::detail::CompositionBusinessTripInfo& trip) override;
    std::vector<ui::detail::CompositionBusinessTripInfo> GetCompositionBusinessTrips() const override;

    void AddDepartment(const ui::detail::DepartmentInfo& dep) override;
    void DeleteDepartment(const ui::detail::DepartmentInfo& dep) override;
    void UpdateDepartment(const ui::detail::DepartmentInfo& dep) override;
    std::vector<ui::detail::DepartmentInfo> GetDepartments() const override;

    void AddEmployee(const ui::detail::EmployeeInfo& employee) override;
    void DeleteEmployee(const ui::detail::EmployeeInfo& employee) override;
    void UpdateEmployee(const ui::detail::EmployeeInfo& employee) override;
    std::vector<ui::detail::EmployeeInfo> GetEmployees() const override;

    void AddJobTitle(const ui::detail::JobTitleInfo& job_title) override;
    void DeleteJobTitle(const ui::detail::JobTitleInfo& job_title) override;
    void UpdateJobTitle(const ui::detail::JobTitleInfo& job_title) override;
    std::vector<ui::detail::JobTitleInfo> GetJobTitles() const override;

    void AddOrder(const ui::detail::OrderInfo& order) override;
    void DeleteOrder(const ui::detail::OrderInfo& order) override;
    void UpdateOrder(const ui::detail::OrderInfo& order) override;
    std::vector<ui::detail::OrderInfo> GetOrders() const override;

    void AddStaffingTable(const ui::detail::StaffingTableInfo& staffing_table) override;
    void DeleteStaffingTable(const ui::detail::StaffingTableInfo& staffing_table) override;
    void UpdateStaffingTable(const ui::detail::StaffingTableInfo& staffing_table) override;
    std::vector<ui::detail::StaffingTableInfo> GetStaffingTable() const override;

    void AddTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) override;
    void DeleteTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) override;
    void UpdateTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) override;
    std::vector<ui::detail::TimeSheetInfo> GetTimeSheet() const override;

    void AddVacation(const ui::detail::VacationInfo& vacation) override;
    void DeleteVacation(const ui::detail::VacationInfo& vacation) override;
    void UpdateVacation(const ui::detail::VacationInfo& vacation) override;
    std::vector<ui::detail::VacationInfo> GetVacations() const override;

    int GetCountBusinessTrips() const override;
    int GetCountDepartments() const override;
    int GetCountEmployees() const override;
    int GetCountJobTitles() const override;
    int GetCountOrders() const override;
    int GetCountStaffingTable() const override;
    int GetCountTimeSheet() const override;
    int GetCountVacations() const override;

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
