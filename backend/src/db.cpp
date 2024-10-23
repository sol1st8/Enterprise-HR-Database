#include "app/use_cases.h"
#include "db.h"
#include "postgres/postgres.h"
#include "ui/view.h"

#include <iostream>

namespace db {
using namespace std::literals;

Application::Application(const AppConfig& config)
    : db_(config.db_url) {}

void Application::Run() {
    ui::detail::DepartmentInfo dep{16, 16, "Отдел бухгалтерии", 116};
    use_cases_.AddDepartment(dep);
    for (auto& dep : use_cases_.GetDepartments()) {
        std::cout << dep.id << ' ' << dep.manager_personal_num << ' ' << dep.dep_name<< ' ' << dep.office_num << std::endl;
    }
}

} // namespace db
