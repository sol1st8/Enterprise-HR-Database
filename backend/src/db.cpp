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
    ui::detail::StaffingTableInfo staffing_table{101, 8, 11, 170000};
    use_cases_.AddStaffingTable(staffing_table);
    for (auto& st_table : use_cases_.GetStaffingTable()) {
        std::cout << st_table.staffing_table_id << ' ' << st_table.job_title_id << ' ' << st_table.department_id
                  << ' ' << st_table.time_job << ' ' << st_table.salary << std::endl;
    }
    use_cases_.UpdateStaffingTable(staffing_table);
    std::cout << '\n';
    for (auto& st_table : use_cases_.GetStaffingTable()) {
        std::cout << st_table.staffing_table_id << ' ' << st_table.job_title_id << ' ' << st_table.department_id
                  << ' ' << st_table.time_job << ' ' << st_table.salary << std::endl;
    }
}

} // namespace db
