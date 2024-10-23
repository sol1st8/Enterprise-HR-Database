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
    ui::detail::JobTitleInfo job_title{16, "Слесарь"s};
    use_cases_.AddJobTitle(job_title);
    for (auto& j_title : use_cases_.GetJobTitles()) {
        std::cout << j_title.id << ' ' << j_title.job_title << std::endl;
    }
    use_cases_.DeleteJobTitle(job_title);
    std::cout << '\n';
    for (auto& j_title : use_cases_.GetJobTitles()) {
        std::cout << j_title.id << ' ' << j_title.job_title << std::endl;
    }
}

} // namespace db
