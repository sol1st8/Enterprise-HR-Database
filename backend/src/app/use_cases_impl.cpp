#include "../domain/worker.h"
#include "use_cases_impl.h"

namespace app {

UseCasesImpl::UseCasesImpl(domain::BusinessTripRepository& trips,
                           domain::CompositionBusinessTripRepository& composition_trips,
                           domain::DepartmentRepository& deps,
                           domain::EmployeeRepository& employees,
                           domain::JobTitleRepository& job_titles,
                           domain::OrderRepository& orders,
                           domain::StaffingTableRepository& staffing_table,
                           domain::TimeSheetRepository& time_sheet,
                           domain::VacationRepository& vacations) : trips_{trips}
                                                                  , composition_trips_{composition_trips}
                                                                  , deps_{deps}
                                                                  , employees_{employees}
                                                                  , job_titles_{job_titles}
                                                                  , orders_{orders}
                                                                  , staffing_table_{staffing_table}
                                                                  , time_sheet_{time_sheet}
                                                                  , vacations_{vacations} {}

void UseCasesImpl::AddBusinessTrip(const ui::detail::BusinessTripInfo& trip) {
    auto worker = trips_.GetWorker();
    worker->AddBusinessTrip({trip.trip_id, trip.city, trip.organization, trip.from_date, trip.to_date,
                             trip.days, trip.target, trip.country});
}

void UseCasesImpl::DeleteBusinessTrip(const ui::detail::BusinessTripInfo& trip) {
    auto worker = trips_.GetWorker();
    worker->DeleteBusinessTrip({trip.trip_id, trip.city, trip.organization, trip.from_date, trip.to_date,
                                trip.days, trip.target, trip.country});
}

void UseCasesImpl::UpdateBusinessTrip(const ui::detail::BusinessTripInfo& trip) {
    auto worker = trips_.GetWorker();
    worker->UpdateBusinessTrip({trip.trip_id, trip.city, trip.organization, trip.from_date, trip.to_date,
                                trip.days, trip.target, trip.country});
}

std::vector<ui::detail::BusinessTripInfo> UseCasesImpl::GetBusinessTrips() const {
    return trips_.Get();
}

void UseCasesImpl::AddCompositionBusinessTrip(const ui::detail::CompositionBusinessTripInfo& trip) {
    auto worker = composition_trips_.GetWorker();
    worker->AddCompositionBusinessTrip({trip.personnel_number, trip.trip_id});
}

void UseCasesImpl::DeleteCompositionBusinessTrip(const ui::detail::CompositionBusinessTripInfo& trip) {
    auto worker = composition_trips_.GetWorker();
    worker->DeleteCompositionBusinessTrip({trip.personnel_number, trip.trip_id});
}

void UseCasesImpl::UpdateCompositionBusinessTrip(const ui::detail::CompositionBusinessTripInfo& trip) {
    auto worker = composition_trips_.GetWorker();
    worker->UpdateCompositionBusinessTrip({trip.personnel_number, trip.trip_id});
}

std::vector<ui::detail::CompositionBusinessTripInfo> UseCasesImpl::GetCompositionBusinessTrips() const {
    return composition_trips_.Get();
}

void UseCasesImpl::AddDepartment(const ui::detail::DepartmentInfo& dep) {
    auto worker = deps_.GetWorker();
    worker->AddDepartment({dep.department_id, dep.manager_personnel_number, dep.dep_name, dep.office_num});
}

void UseCasesImpl::DeleteDepartment(const ui::detail::DepartmentInfo& dep) {
    auto worker = deps_.GetWorker();
    worker->DeleteDepartment({dep.department_id, dep.manager_personnel_number, dep.dep_name, dep.office_num});
}

void UseCasesImpl::UpdateDepartment(const ui::detail::DepartmentInfo& dep) {
    auto worker = deps_.GetWorker();
    worker->UpdateDepartment({dep.department_id, dep.manager_personnel_number, dep.dep_name, dep.office_num});
}

std::vector<ui::detail::DepartmentInfo> UseCasesImpl::GetDepartments() const {
    return deps_.Get();
}

void UseCasesImpl::AddEmployee(const ui::detail::EmployeeInfo& employee) {
    auto worker = employees_.GetWorker();
    worker->AddEmployee({employee.personnel_number, employee.full_name, employee.job_title_id,
                         employee.experience, employee.number, employee.registration, employee.education,
                         employee.mail, employee.gender, employee.marital_status, employee.date});
}

void UseCasesImpl::DeleteEmployee(const ui::detail::EmployeeInfo& employee) {
    auto worker = employees_.GetWorker();
    worker->DeleteEmployee({employee.personnel_number, employee.full_name, employee.job_title_id,
                            employee.experience, employee.number, employee.registration, employee.education,
                            employee.mail, employee.gender, employee.marital_status, employee.date});
}

void UseCasesImpl::UpdateEmployee(const ui::detail::EmployeeInfo& employee) {
    auto worker = employees_.GetWorker();
    worker->UpdateEmployee({employee.personnel_number, employee.full_name, employee.job_title_id,
                            employee.experience, employee.number, employee.registration, employee.education,
                            employee.mail, employee.gender, employee.marital_status, employee.date});
}

std::vector<ui::detail::EmployeeInfo> UseCasesImpl::GetEmployees() const {
    return employees_.Get();
}

void UseCasesImpl::AddJobTitle(const ui::detail::JobTitleInfo& job_title) {
    auto worker = job_titles_.GetWorker();
    worker->AddJobTitle({job_title.job_title_id, job_title.job_title});
}

void UseCasesImpl::DeleteJobTitle(const ui::detail::JobTitleInfo& job_title) {
    auto worker = job_titles_.GetWorker();
    worker->DeleteJobTitle({job_title.job_title_id, job_title.job_title});
}

void UseCasesImpl::UpdateJobTitle(const ui::detail::JobTitleInfo& job_title) {
    auto worker = job_titles_.GetWorker();
    worker->UpdateJobTitle({job_title.job_title_id, job_title.job_title});
}

std::vector<ui::detail::JobTitleInfo> UseCasesImpl::GetJobTitles() const {
    return job_titles_.Get();
}

void UseCasesImpl::AddOrder(const ui::detail::OrderInfo& order) {
    auto worker = orders_.GetWorker();
    worker->AddOrder({order.order_id, order.personnel_number, order.content, order.date});
}

void UseCasesImpl::DeleteOrder(const ui::detail::OrderInfo& order) {
    auto worker = orders_.GetWorker();
    worker->DeleteOrder({order.order_id, order.personnel_number, order.content, order.date});
}

void UseCasesImpl::UpdateOrder(const ui::detail::OrderInfo& order) {
    auto worker = orders_.GetWorker();
    worker->UpdateOrder({order.order_id, order.personnel_number, order.content, order.date});
}

std::vector<ui::detail::OrderInfo> UseCasesImpl::GetOrders() const {
    return orders_.Get();
}

void UseCasesImpl::AddStaffingTable(const ui::detail::StaffingTableInfo& staffing_table) {
    auto worker = staffing_table_.GetWorker();
    worker->AddStaffingTable({staffing_table.staffing_table_id, staffing_table.job_title_id,
                              staffing_table.department_id, staffing_table.salary, staffing_table.time_job});
}

void UseCasesImpl::DeleteStaffingTable(const ui::detail::StaffingTableInfo& staffing_table) {
    auto worker = staffing_table_.GetWorker();
    worker->DeleteStaffingTable({staffing_table.staffing_table_id, staffing_table.job_title_id,
                                 staffing_table.department_id, staffing_table.salary, staffing_table.time_job});
}

void UseCasesImpl::UpdateStaffingTable(const ui::detail::StaffingTableInfo& staffing_table) {
    auto worker = staffing_table_.GetWorker();
    worker->UpdateStaffingTable({staffing_table.staffing_table_id, staffing_table.job_title_id,
                                 staffing_table.department_id, staffing_table.salary, staffing_table.time_job});
}

std::vector<ui::detail::StaffingTableInfo> UseCasesImpl::GetStaffingTable() const {
    return staffing_table_.Get();
}

void UseCasesImpl::AddTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) {
    auto worker = time_sheet_.GetWorker();
    worker->AddTimeSheet({time_sheet.time_sheet_id, time_sheet.personnel_number, time_sheet.time_worked, time_sheet.month});
}

void UseCasesImpl::DeleteTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) {
    auto worker = time_sheet_.GetWorker();
    worker->DeleteTimeSheet({time_sheet.time_sheet_id, time_sheet.personnel_number, time_sheet.time_worked, time_sheet.month});
}

void UseCasesImpl::UpdateTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) {
    auto worker = time_sheet_.GetWorker();
    worker->UpdateTimeSheet({time_sheet.time_sheet_id, time_sheet.personnel_number, time_sheet.time_worked, time_sheet.month});
}

std::vector<ui::detail::TimeSheetInfo> UseCasesImpl::GetTimeSheet() const {
    return time_sheet_.Get();
}

void UseCasesImpl::AddVacation(const ui::detail::VacationInfo& vacation) {
    auto worker = vacations_.GetWorker();
    worker->AddVacation({vacation.vacation_id, vacation.personnel_number, vacation.type, vacation.from_date,
                         vacation.to_date, vacation.days, vacation.leave_basis});
}

void UseCasesImpl::DeleteVacation(const ui::detail::VacationInfo& vacation) {
    auto worker = vacations_.GetWorker();
    worker->DeleteVacation({vacation.vacation_id, vacation.personnel_number, vacation.type, vacation.from_date,
                             vacation.to_date, vacation.days, vacation.leave_basis});
}

void UseCasesImpl::UpdateVacation(const ui::detail::VacationInfo& vacation) {
    auto worker = vacations_.GetWorker();
    worker->UpdateVacation({vacation.vacation_id, vacation.personnel_number, vacation.type, vacation.from_date,
                             vacation.to_date, vacation.days, vacation.leave_basis});
}

std::vector<ui::detail::VacationInfo> UseCasesImpl::GetVacations() const {
    return vacations_.Get();
}

int UseCasesImpl::GetCountBusinessTrips() const { return trips_.GetCount(); }
int UseCasesImpl::GetCountDepartments() const { return deps_.GetCount(); }
int UseCasesImpl::GetCountEmployees() const { return employees_.GetCount(); }
int UseCasesImpl::GetCountJobTitles() const { return job_titles_.GetCount(); }
int UseCasesImpl::GetCountOrders() const { return orders_.GetCount(); }
int UseCasesImpl::GetCountStaffingTable() const { return staffing_table_.GetCount(); }
int UseCasesImpl::GetCountTimeSheet() const { return time_sheet_.GetCount(); }
int UseCasesImpl::GetCountVacations() const { return vacations_.GetCount(); }

} // namespace app
