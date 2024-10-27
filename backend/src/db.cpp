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
    ui::detail::TimeSheetInfo time_sheet{101, 7, 11, 170000};
    use_cases_.AddTimeSheet(time_sheet);
    for (auto& t_sheet : use_cases_.GetTimeSheet()) {
        std::cout << t_sheet.time_sheet_id << ' ' << t_sheet.job_title_id << ' ' << t_sheet.department_id << ' '
                  << t_sheet.time_job << ' ' << t_sheet.salary << std::endl;
    }
    use_cases_.UpdateTimeSheet(time_sheet);
    std::cout << '\n';
    for (auto& t_sheet : use_cases_.GetTimeSheet()) {
        std::cout << t_sheet.time_sheet_id << ' ' << t_sheet.job_title_id << ' ' << t_sheet.department_id << ' '
                  << t_sheet.time_job << ' ' << t_sheet.salary << std::endl;
    }
}

} // namespace db
