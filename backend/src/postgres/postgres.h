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

    void AddBusinessTrip(const domain::BusinessTrip& trip) override;
    void UpdateBusinessTrip(const domain::BusinessTrip& trip) override;

    void AddCompositionBusinessTrip(const domain::CompositionBusinessTrip& trip) override;
    void UpdateCompositionBusinessTrip(const domain::CompositionBusinessTrip& trip) override;

    void AddDepartment(const domain::Department& dep) override;
    void UpdateDepartment(const domain::Department& dep) override;

    void AddEmployee(const domain::Employee& employee) override;
    void UpdateEmployee(const domain::Employee& employee) override;

    void AddJobTitle(const domain::JobTitle& job_title) override;
    void UpdateJobTitle(const domain::JobTitle& job_title) override;

    void AddOrder(const domain::Order& order) override;
    void UpdateOrder(const domain::Order& order) override;

    void AddStaffingTable(const domain::StaffingTable& staffing_table) override;
    void UpdateStaffingTable(const domain::StaffingTable& staffing_table) override;

    void AddTimeSheet(const domain::TimeSheet& time_sheet) override;
    void UpdateTimeSheet(const domain::TimeSheet& time_sheet) override;

    void AddVacation(const domain::Vacation& vacation) override;
    void UpdateVacation(const domain::Vacation& vacation) override;

    ~WorkerImpl() override;

  private:
    pqxx::connection& conn_;
    pqxx::nontransaction nontr_;
};

class BusinessTripRepositoryImpl : public domain::BusinessTripRepository {
  public:
    explicit BusinessTripRepositoryImpl(connection_pool::ConnectionPool& pool) : pool_{pool} {}

    std::vector<ui::detail::BusinessTripInfo> Get() const override;

    std::shared_ptr<domain::Worker> GetWorker() const override {
        auto conn = pool_.GetConnection();
        return std::make_shared<WorkerImpl>(*conn);
    }

    int GetCount() const override;

  private:
    connection_pool::ConnectionPool& pool_;
};

class CompositionBusinessTripRepositoryImpl : public domain::CompositionBusinessTripRepository {
  public:
    explicit CompositionBusinessTripRepositoryImpl(connection_pool::ConnectionPool& pool) : pool_{pool} {}

    std::vector<ui::detail::CompositionBusinessTripInfo> Get() const override;

    std::shared_ptr<domain::Worker> GetWorker() const override {
        auto conn = pool_.GetConnection();
        return std::make_shared<WorkerImpl>(*conn);
    }

  private:
    connection_pool::ConnectionPool& pool_;
};

class DepartmentRepositoryImpl : public domain::DepartmentRepository {
  public:
    explicit DepartmentRepositoryImpl(connection_pool::ConnectionPool& pool) : pool_{pool} {}

    std::vector<ui::detail::DepartmentInfo> Get() const override;

    std::shared_ptr<domain::Worker> GetWorker() const override {
        auto conn = pool_.GetConnection();
        return std::make_shared<WorkerImpl>(*conn);
    }

    int GetCount() const override;

    std::string GetDep(int id) const override;
    int GetDepId(const std::string& dep) const override;

  private:
    connection_pool::ConnectionPool& pool_;
};

class EmployeeRepositoryImpl : public domain::EmployeeRepository {
  public:
    explicit EmployeeRepositoryImpl(connection_pool::ConnectionPool& pool) : pool_{pool} {}

    std::vector<ui::detail::EmployeeInfo> Get() const override;

    std::shared_ptr<domain::Worker> GetWorker() const override {
        auto conn = pool_.GetConnection();
        return std::make_shared<WorkerImpl>(*conn);
    }

    int GetCount() const override;

    std::unordered_set<std::string> GetEmails() const override;

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

    int GetCount() const override;

    std::string GetJobTitle(int id) const override;
    int GetJobTitleId(const std::string& job_title) const override;

  private:
    connection_pool::ConnectionPool& pool_;
};

class OrderRepositoryImpl : public domain::OrderRepository {
  public:
    explicit OrderRepositoryImpl(connection_pool::ConnectionPool& pool) : pool_{pool} {}

    std::vector<ui::detail::OrderInfo> Get() const override;

    std::shared_ptr<domain::Worker> GetWorker() const override {
        auto conn = pool_.GetConnection();
        return std::make_shared<WorkerImpl>(*conn);
    }

    int GetCount() const override;

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

    int GetCount() const override;

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

    int GetCount() const override;

  private:
    connection_pool::ConnectionPool& pool_;
};

class VacationRepositoryImpl : public domain::VacationRepository {
  public:
    explicit VacationRepositoryImpl(connection_pool::ConnectionPool& pool) : pool_{pool} {}

    std::vector<ui::detail::VacationInfo> Get() const override;

    std::shared_ptr<domain::Worker> GetWorker() const override {
        auto conn = pool_.GetConnection();
        return std::make_shared<WorkerImpl>(*conn);
    }

    int GetCount() const override;

  private:
    connection_pool::ConnectionPool& pool_;
};

class DataBase {
  public:
    explicit DataBase(const std::string& db_url);

    BusinessTripRepositoryImpl& GetBusinessTrips() & {
        return trips_;
    }

    CompositionBusinessTripRepositoryImpl& GetCompositionBusinessTrips() & {
        return composition_trips_;
    }

    DepartmentRepositoryImpl& GetDepartments() & {
        return deps_;
    }

    EmployeeRepositoryImpl& GetEmployees() & {
        return employees_;
    }

    JobTitleRepositoryImpl& GetJobTitles() & {
        return job_titles_;
    }

    OrderRepositoryImpl& GetOrders() & {
        return orders_;
    }

    StaffingTableRepositoryImpl& GetStaffingTable() & {
        return staffing_table_;
    }

    TimeSheetRepositoryImpl& GetTimeSheet() & {
        return time_sheet_;
    }

    VacationRepositoryImpl& GetVacations() & {
        return vacations_;
    }

  private:
    connection_pool::ConnectionPool pool_;

    BusinessTripRepositoryImpl trips_;
    CompositionBusinessTripRepositoryImpl composition_trips_;
    DepartmentRepositoryImpl deps_;
    EmployeeRepositoryImpl employees_;
    JobTitleRepositoryImpl job_titles_;
    OrderRepositoryImpl orders_;
    StaffingTableRepositoryImpl staffing_table_;
    TimeSheetRepositoryImpl time_sheet_;
    VacationRepositoryImpl vacations_;
};

}  // namespace postgres
