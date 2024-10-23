#include "../domain/department.h"
#include "../domain/job_title.h"
#include "postgres.h"
#include "../ui/view.h"

#include <pqxx/zview.hxx>
#include <pqxx/pqxx>

namespace postgres {
using namespace std::literals;
using pqxx::operator"" _zv;

std::vector<ui::detail::DepartmentInfo> DepartmentRepositoryImpl::Get() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Отдел;";

    auto resp = tr.query<int, int, std::string, int>(query);

    std::vector<ui::detail::DepartmentInfo> result;

    for (auto& [id, manager_personal_num, dep_name, office_num] : resp) {
        ui::detail::DepartmentInfo department{id, manager_personal_num, dep_name, office_num};
        result.push_back(department);
    }

    return result;
}

std::vector<ui::detail::JobTitleInfo> JobTitleRepositoryImpl::Get() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Должность;";

    auto resp = tr.query<int, std::string>(query);

    std::vector<ui::detail::JobTitleInfo> result;

    for (auto& [id, job_title] : resp) {
        ui::detail::JobTitleInfo job_title_info{id, job_title};
        result.push_back(job_title_info);
    }

    return result;
}

DataBase::DataBase(const std::string& db_url)
    : pool_{std::thread::hardware_concurrency(),
  [&db_url](){ return std::make_shared<pqxx::connection>(db_url); } }, deps_{pool_}, job_titles_{pool_} {}

WorkerImpl::WorkerImpl(pqxx::connection& conn) : conn_(conn), work_(conn) {}

void WorkerImpl::AddDepartment(const domain::Department& dep) {
    work_.exec_params(
        R"(
    INSERT INTO Отдел (КодОтдела, ТабельныйНомерРуководителя, Название, НомерКабинета) VALUES ($1, $2, $3, $4);
    )"_zv,
        dep.GetId(), dep.GetManagerPersonalNum(), dep.GetDepName(), dep.GetOfficeNum());
}

void WorkerImpl::DeleteDepartment(const domain::Department& dep) {
    work_.exec_params(
        R"(
    DELETE FROM Отдел WHERE КодОтдела=$1;
    )"_zv,
        dep.GetId());
}

void WorkerImpl::UpdateDepartment(const domain::Department& dep) {
    work_.exec_params(
        R"(
    UPDATE Отдел SET КодОтдела=КодОтдела + 1 WHERE КодОтдела=$1;
    )"_zv,
        dep.GetId());
}

void WorkerImpl::AddJobTitle(const domain::JobTitle& job_title) {
    work_.exec_params(
        R"(
    INSERT INTO Должность (КодДолжности, Название) VALUES ($1, $2);
    )"_zv,
        job_title.GetId(), job_title.GetJobTitle());
}

void WorkerImpl::DeleteJobTitle(const domain::JobTitle& job_title) {
    work_.exec_params(
        R"(
    DELETE FROM Должность WHERE КодДолжности=$1;
    )"_zv,
        job_title.GetId());
}

void WorkerImpl::UpdateJobTitle(const domain::JobTitle& job_title) {
    work_.exec_params(
        R"(
    UPDATE Должность SET КодДолжности=КодДолжности + 1 WHERE КодДолжности=$1;
    )"_zv,
        job_title.GetId());
}

void WorkerImpl::Commit() {;
    work_.commit();
}

WorkerImpl::~WorkerImpl() {
    work_.commit();
}

} // namespace postgres
