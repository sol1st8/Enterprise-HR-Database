#pragma once

#include "app/use_cases_impl.h"
#include "postgres/postgres.h"

#include <pqxx/pqxx>

namespace db {

struct AppConfig {
    std::string db_url;
};

class Application {
  public:
    explicit Application(const AppConfig& config);

    void Run();

  private:
    postgres::DataBase db_;
    app::UseCasesImpl use_cases_{db_.GetDepartments(), db_.GetJobTitles(), db_.GetTimeSheet()};
};

} // namespace db
