#include "../domain/department.h"
#include "../domain/job_title.h"
#include "../domain/worker.h"
#include "use_cases_impl.h"

namespace app {

UseCasesImpl::UseCasesImpl(domain::DepartmentRepository& deps, domain::JobTitleRepository& job_titles,
                           domain::TimeSheetRepository& time_sheet) : deps_(deps)
                                                                    , job_titles_{job_titles}
                                                                    , time_sheet_{time_sheet} {}

void UseCasesImpl::AddJobTitle(const ui::detail::JobTitleInfo& job_title) {
    auto worker = job_titles_.GetWorker();
    worker->AddJobTitle({job_title.job_title_id, job_title.job_title});
    worker->Commit();
}

void UseCasesImpl::DeleteJobTitle(const ui::detail::JobTitleInfo& job_title) {
    auto worker = job_titles_.GetWorker();
    worker->DeleteJobTitle({job_title.job_title_id, job_title.job_title});
    worker->Commit();
}

void UseCasesImpl::UpdateJobTitle(const ui::detail::JobTitleInfo& job_title) {
    auto worker = job_titles_.GetWorker();
    worker->UpdateJobTitle({job_title.job_title_id, job_title.job_title});
    worker->Commit();
}

std::vector<ui::detail::JobTitleInfo> UseCasesImpl::GetJobTitles() const {
    return job_titles_.Get();
}

void UseCasesImpl::AddDepartment(const ui::detail::DepartmentInfo& dep) {
    auto worker = deps_.GetWorker();
    worker->AddDepartment({dep.department_id, dep.manager_personnel_number, dep.dep_name, dep.office_num});
    worker->Commit();
}

void UseCasesImpl::DeleteDepartment(const ui::detail::DepartmentInfo& dep) {
    auto worker = deps_.GetWorker();
    worker->DeleteDepartment({dep.department_id, dep.manager_personnel_number, dep.dep_name, dep.office_num});
    worker->Commit();
}

void UseCasesImpl::UpdateDepartment(const ui::detail::DepartmentInfo& dep) {
    auto worker = deps_.GetWorker();
    worker->UpdateDepartment({dep.department_id, dep.manager_personnel_number, dep.dep_name, dep.office_num});
    worker->Commit();
}

std::vector<ui::detail::DepartmentInfo> UseCasesImpl::GetDepartments() const {
    return deps_.Get();
}

void UseCasesImpl::AddTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) {
    auto worker = time_sheet_.GetWorker();
    worker->AddTimeSheet({time_sheet.time_sheet_id, time_sheet.personnel_number, time_sheet.time_worked, time_sheet.month});
    worker->Commit();
}

void UseCasesImpl::DeleteTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) {
    auto worker = time_sheet_.GetWorker();
    worker->DeleteTimeSheet({time_sheet.time_sheet_id, time_sheet.personnel_number, time_sheet.time_worked, time_sheet.month});
    worker->Commit();
}

void UseCasesImpl::UpdateTimeSheet(const ui::detail::TimeSheetInfo& time_sheet) {
    auto worker = time_sheet_.GetWorker();
    worker->UpdateTimeSheet({time_sheet.time_sheet_id, time_sheet.personnel_number, time_sheet.time_worked, time_sheet.month});
    worker->Commit();
}

std::vector<ui::detail::TimeSheetInfo> UseCasesImpl::GetTimeSheet() const {
    return time_sheet_.Get();
}

} // namespace app
