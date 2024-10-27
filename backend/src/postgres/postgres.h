#pragma once

#include "../connection_pool.h"
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

    void AddStaffingTable(const domain::StaffingTable& staffing_table) override;
    void DeleteStaffingTable(const domain::StaffingTable& staffing_table) override;
    void UpdateStaffingTable(const domain::StaffingTable& staffing_table) override;

    void AddTimeSheet(const domain::TimeSheet& time_sheet) override;
    void DeleteTimeSheet(const domain::TimeSheet& time_sheet) override;
    void UpdateTimeSheet(const domain::TimeSheet& time_sheet) override;

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

class StaffingTableRepositoryImpl : public domain::StaffingTableRepository {
  public:
    explicit StaffingTableRepositoryImpl(connection_pool::ConnectionPool& pool) : pool_{pool} {}

    std::vector<ui::detail::StaffingTableInfo> Get() const override;

    std::shared_ptr<domain::Worker> GetWorker() const override {
        auto conn = pool_.GetConnection();
        return std::make_shared<WorkerImpl>(*conn);
    }

  private:
    connection_pool::ConnectionPool& pool_;
};

class TimeSheetRepositoryImpl : public domain::TimeSheetRepository {
  public:
    explicit TimeSheetRepositoryImpl(connection_pool::ConnectionPool& pool) : pool_{pool} {}

    std::vector<ui::detail::TimeSheetInfo> Get() const override;

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

    StaffingTableRepositoryImpl& GetStaffingTable() & {
        return staffing_table_;
    }

    TimeSheetRepositoryImpl& GetTimeSheet() & {
        return time_sheet_;
    }

  private:
    connection_pool::ConnectionPool pool_;
    DepartmentRepositoryImpl deps_;
    JobTitleRepositoryImpl job_titles_;
    StaffingTableRepositoryImpl staffing_table_;
    TimeSheetRepositoryImpl time_sheet_;
};

}  // namespace postgres
