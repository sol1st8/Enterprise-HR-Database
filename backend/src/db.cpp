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
    ui::detail::EmployeeInfo employee{101, "Егоров Вадим Николаевич", 5, std::nullopt, "89018088635", "г. Москва ул.Ташкентская", "высшее", "egorov59r@gmail.com"};
    use_cases_.AddEmployee(employee);
    for (auto& emp : use_cases_.GetEmployees()) {
        std::cout << emp.personnel_number << ' ' << emp.full_name << ' ' << emp.gender << ' '
                  << emp.job_title_id << ' ' << (emp.stage.has_value() ? std::to_string(*emp.stage) : "NULL") << ' '
                  << emp.number << ' ' << emp.registration << ' ' << emp.education << ' ' << emp.date << ' ' << emp.mail << ' '
                  << emp.marital_status << std::endl;
    }
    use_cases_.DeleteEmployee(employee);
    std::cout << std::endl;
    for (auto& emp : use_cases_.GetEmployees()) {
        std::cout << emp.personnel_number << ' ' << emp.full_name << ' ' << emp.gender << ' '
                  << emp.job_title_id << ' ' << (emp.stage.has_value() ? std::to_string(*emp.stage) : "NULL") << ' '
                  << emp.number << ' ' << emp.registration << ' ' << emp.education << ' ' << emp.date << ' ' << emp.mail << ' '
                  << emp.marital_status << std::endl;
    }
}

} // namespace db
