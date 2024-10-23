#include "../domain/department.h"
#include "../domain/worker.h"
#include "use_cases_impl.h"

namespace app {
using namespace domain;

UseCasesImpl::UseCasesImpl(domain::DepartmentRepository& deps) : deps_(deps) {}

void UseCasesImpl::AddDepartment(ui::detail::DepartmentInfo& dep) {
    auto worker = deps_.GetWorker();
    worker->AddDepartment({dep.id, dep.manager_personal_num, dep.dep_name, dep.office_num});
    worker->Commit();
}

std::vector<ui::detail::DepartmentInfo> UseCasesImpl::GetDepartments() {
    return deps_.Get();
}

} // namespace app
