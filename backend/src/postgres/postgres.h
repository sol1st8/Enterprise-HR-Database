#pragma once

#include "../connection_pool.h"
#include "../domain/department.h"
#include "../domain/worker.h"
#include "../ui/view.h"

#include <pqxx/connection>
#include <pqxx/transaction>

#include <memory>
#include <vector>

namespace postgres {

class WorkerImpl : public domain::Worker {
  public:
    WorkerImpl(pqxx::connection& conn);

    void AddDepartment(const domain::Department& dep) override;

    void Commit() override;

    ~WorkerImpl() override;

  private:
    pqxx::connection& conn_;
    pqxx::work work_;
};

class DepartmentRepositoryImpl : public domain::DepartmentRepository {
  public:
    explicit DepartmentRepositoryImpl(connection_pool::ConnectionPool& pool) : pool_{pool} {}

    std::vector<ui::detail::DepartmentInfo> Get() override;

    std::shared_ptr<domain::Worker> GetWorker() override {
        auto conn = pool_.GetConnection();
        return std::make_shared<WorkerImpl>(*conn);
    }

  private:
    connection_pool::ConnectionPool& pool_;
};

class DataBase {
  public:
    explicit DataBase(const std::string& db_url);

    DepartmentRepositoryImpl& GetDepartment() & {
        return deps_;
    }

  private:
    connection_pool::ConnectionPool pool_;
    DepartmentRepositoryImpl deps_;
};

}  // namespace postgres
