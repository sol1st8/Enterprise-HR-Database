#include "../domain/department.h"
#include "../domain/job_title.h"
#include "../domain/worker.h"
#include "use_cases_impl.h"

namespace app {

UseCasesImpl::UseCasesImpl(domain::DepartmentRepository& deps, domain::JobTitleRepository& job_titles) : deps_(deps)
                                                               , job_titles_{job_titles} {}

void UseCasesImpl::AddDepartment(const ui::detail::DepartmentInfo& dep) {
    auto worker = deps_.GetWorker();
    worker->AddDepartment({dep.id, dep.manager_personal_num, dep.dep_name, dep.office_num});
    worker->Commit();
}

void UseCasesImpl::DeleteDepartment(const ui::detail::DepartmentInfo& dep) {
    auto worker = deps_.GetWorker();
    worker->DeleteDepartment({dep.id, dep.manager_personal_num, dep.dep_name, dep.office_num});
    worker->Commit();
}

void UseCasesImpl::UpdateDepartment(const ui::detail::DepartmentInfo& dep) {
    auto worker = deps_.GetWorker();
    worker->UpdateDepartment({dep.id, dep.manager_personal_num, dep.dep_name, dep.office_num});
    worker->Commit();
}

std::vector<ui::detail::DepartmentInfo> UseCasesImpl::GetDepartments() const {
    return deps_.Get();
}

void UseCasesImpl::AddJobTitle(const ui::detail::JobTitleInfo& job_title) {
    auto worker = job_titles_.GetWorker();
    worker->AddJobTitle({job_title.id, job_title.job_title});
    worker->Commit();
}

void UseCasesImpl::DeleteJobTitle(const ui::detail::JobTitleInfo& job_title) {
    auto worker = job_titles_.GetWorker();
    worker->DeleteJobTitle({job_title.id, job_title.job_title});
    worker->Commit();
}

void UseCasesImpl::UpdateJobTitle(const ui::detail::JobTitleInfo& job_title) {
    auto worker = job_titles_.GetWorker();
    worker->UpdateJobTitle({job_title.id, job_title.job_title});
    worker->Commit();
}

std::vector<ui::detail::JobTitleInfo> UseCasesImpl::GetJobTitles() const {
    return job_titles_.Get();
}

} // namespace app
