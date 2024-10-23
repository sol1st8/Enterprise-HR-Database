#pragma once

#include "../connection_pool.h"
#include "../domain/department.h"
#include "../domain/job_title.h"
#include "../domain/worker.h"
#include "../ui/view.h"

#include <pqxx/connection>
#include <pqxx/transaction>

#include <memory>
#include <vector>

namespace postgres {

class WorkerImpl : public domain::Worker {
  public:
    explicit WorkerImpl(pqxx::connection& conn);

    void AddDepartment(const domain::Department& dep) override;
    void DeleteDepartment(const domain::Department& dep) override;
    void UpdateDepartment(const domain::Department& dep) override;

    void AddJobTitle(const domain::JobTitle& job_title) override;
    void DeleteJobTitle(const domain::JobTitle& job_title) override;
    void UpdateJobTitle(const domain::JobTitle& job_title) override;

    void Commit() override;

    ~WorkerImpl() override;

  private:
    pqxx::connection& conn_;
    pqxx::work work_;
};

class DepartmentRepositoryImpl : public domain::DepartmentRepository {
  public:
    explicit DepartmentRepositoryImpl(connection_pool::ConnectionPool& pool) : pool_{pool} {}

    std::vector<ui::detail::DepartmentInfo> Get() const override;

    std::shared_ptr<domain::Worker> GetWorker() const override {
        auto conn = pool_.GetConnection();
        return std::make_shared<WorkerImpl>(*conn);
    }

  private:
    connection_pool::ConnectionPool& pool_;
};

class JobTitleRepositoryImpl : public domain::JobTitleRepository {
  public:
    explicit JobTitleRepositoryImpl(connection_pool::ConnectionPool& pool) : pool_{pool} {}

    std::vector<ui::detail::JobTitleInfo> Get() const override;

    std::shared_ptr<domain::Worker> GetWorker() const override {
        auto conn = pool_.GetConnection();
        return std::make_shared<WorkerImpl>(*conn);
    }

  private:
    connection_pool::ConnectionPool& pool_;
};

class DataBase {
  public:
    explicit DataBase(const std::string& db_url);

    DepartmentRepositoryImpl& GetDepartments() & {
        return deps_;
    }

    JobTitleRepositoryImpl& GetJobTitles() & {
        return job_titles_;
    }

  private:
    connection_pool::ConnectionPool pool_;
    DepartmentRepositoryImpl deps_;
    JobTitleRepositoryImpl job_titles_;
};

}  // namespace postgres
