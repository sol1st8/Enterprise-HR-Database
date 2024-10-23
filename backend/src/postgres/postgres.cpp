#include "../domain/department.h"
#include "postgres.h"
#include "../ui/view.h"

#include <pqxx/zview.hxx>
#include <pqxx/pqxx>

namespace postgres {
using namespace std::literals;
using pqxx::operator"" _zv;

std::vector<ui::detail::DepartmentInfo> DepartmentRepositoryImpl::Get() {
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

DataBase::DataBase(const std::string& db_url)
    : pool_{std::thread::hardware_concurrency(),
  [&db_url](){ return std::make_shared<pqxx::connection>(db_url); } }, deps_{pool_} {
    auto conn = pool_.GetConnection();
}

WorkerImpl::WorkerImpl(pqxx::connection& conn) : conn_(conn), work_(conn) {}

void WorkerImpl::AddDepartment(const domain::Department& dep) {
    ui::detail::DepartmentInfo info;

    info.id = dep.GetId();
    info.manager_personal_num = dep.GetManagerPersonalNum();
    info.dep_name = dep.GetDepName();
    info.office_num = dep.GetOfficeNum();

    work_.exec_params(
        R"(
    INSERT INTO Отдел (КодОтдела, ТабельныйНомерРуководителя, Название, НомерКабинета) VALUES ($1, $2, $3, $4);
    )"_zv,
        info.id, info.manager_personal_num, info.dep_name, info.office_num);
}

void WorkerImpl::Commit() {;
    work_.commit();
}

WorkerImpl::~WorkerImpl() {
    work_.commit();
}

} // namespace postgres
