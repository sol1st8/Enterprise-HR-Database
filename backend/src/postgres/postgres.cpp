#include "postgres.h"
#include "../ui/view.h"

#include <pqxx/zview.hxx>
#include <pqxx/pqxx>

#include <stdexcept>

#include <iostream>

namespace postgres {
using namespace std::literals;
using pqxx::operator"" _zv;

std::string BusinessTripRepositoryImpl::GetStartDateOfBusinessTrip(int trip_id) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Командировка ORDER BY НомерЗаписи;"s;

    auto resp = tr.query<int, std::string, std::string, std::string,
                         std::string, std::string, int, std::string>(query);

    for (const auto& [tr_id, country, city, organization, from_date, to_date, days, target] : resp) {
        if (trip_id == tr_id) {
            return from_date;
        }
    }

    return ""s;
}

std::string BusinessTripRepositoryImpl::GetOrganization(int trip_id) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Командировка ORDER BY НомерЗаписи;"s;

    auto resp = tr.query<int, std::string, std::string, std::string,
                         std::string, std::string, int, std::string>(query);

    for (const auto& [tr_id, country, city, organization,
                      from_date, to_date, days, target] : resp) {
        if (trip_id == tr_id) {
            return organization;
        }
    }

    return ""s;
}

int BusinessTripRepositoryImpl::GetTripId(const std::string& organization) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Командировка ORDER BY НомерЗаписи;"s;

    auto resp = tr.query<int, std::string, std::string, std::string,
                         std::string, std::string, int, std::string>(query);

    for (const auto& [trip_id, country, city, org,
                      from_date, to_date, days, target] : resp) {
        if (organization == org) {
            return trip_id;
        }
    }

    return -1;
}

std::vector<ui::detail::BusinessTripInfo> BusinessTripRepositoryImpl::Get() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Командировка ORDER BY НомерЗаписи;"s;

    auto resp = tr.query<int, std::string, std::string, std::string,
                         std::string, std::string, int, std::string>(query);

    std::vector<ui::detail::BusinessTripInfo> result;

    for (const auto& [trip_id, country, city, organization, from_date, to_date, days, target] : resp) {
        ui::detail::BusinessTripInfo trip{trip_id, country, city, organization,
                                          from_date, to_date, days, target};
        result.push_back(trip);
    }

    return result;
}

std::vector<ui::detail::BusinessTripInfo> BusinessTripRepositoryImpl::GetForPerson(int personnel_number) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    CompositionBusinessTripRepositoryImpl comp_trip(pool_);
    std::vector<int> ids = comp_trip.GetTripIds(personnel_number);

    std::string query = "SELECT * FROM Командировка ORDER BY НомерЗаписи;"s;

    auto resp = tr.query<int, std::string, std::string, std::string,
                         std::string, std::string, int, std::string>(query);

    std::vector<ui::detail::BusinessTripInfo> result;

    for (const auto& [trip_id, country, city, organization, from_date, to_date, days, target] : resp) {
        for (int id : ids) {
            if (trip_id != id) {
                continue;
            }
            ui::detail::BusinessTripInfo trip{trip_id, country, city, organization,
                                              from_date, to_date, days, target};
            result.push_back(trip);
        }
    }

    return result;
}

int BusinessTripRepositoryImpl::GetCount() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT COUNT(*) FROM Командировка;"s;

    auto count = tr.query_value<int>(query);

    return count;
}

std::vector<int> CompositionBusinessTripRepositoryImpl::GetTripIds(int personnel_number) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM СоставКомандировки ORDER BY ТабельныйНомер;"s;

    auto resp = tr.query<int, int>(query);

    std::vector<int> ids;

    for (const auto& [personnel_num, trip_id] : resp) {
        if (personnel_number != personnel_num) {
            continue;
        }
        ids.push_back(trip_id);
    }

    return ids;
}

std::vector<ui::detail::CompositionBusinessTripInfo> CompositionBusinessTripRepositoryImpl::Get() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    BusinessTripRepositoryImpl t(pool_);

    std::string query = "SELECT * FROM СоставКомандировки ORDER BY ТабельныйНомер;"s;

    auto resp = tr.query<int, int>(query);

    std::vector<ui::detail::CompositionBusinessTripInfo> result;

    for (const auto& [personnel_number, trip_id] : resp) {
        ui::detail::CompositionBusinessTripInfo trip{personnel_number, t.GetOrganization(trip_id)};
        result.push_back(trip);
    }

    return result;
}

std::vector<ui::detail::CompositionBusinessTripInfo> CompositionBusinessTripRepositoryImpl::GetForPerson(int personnel_number) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM СоставКомандировки ORDER BY ТабельныйНомер;"s;

    BusinessTripRepositoryImpl t(pool_);

    auto resp = tr.query<int, int>(query);

    std::vector<ui::detail::CompositionBusinessTripInfo> result;

    if (GetTripIds(personnel_number).empty()) { return result; }

    for (const auto& [personnel_num, trip_id] : resp) {
        for (int id : GetTripIds(personnel_number)) {
            if (trip_id != id) {
                continue;
            }
            ui::detail::CompositionBusinessTripInfo trip{personnel_num, t.GetOrganization(trip_id)};
            result.push_back(trip);
        }
    }

    return result;
}

std::string DepartmentRepositoryImpl::GetDep(int id) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Отдел ORDER BY КодОтдела;"s;

    auto resp = tr.query<int, int, std::string, int>(query);

    for (const auto& [dep_id, manager_personnel_num, dep_name, office_num] : resp) {
        if (dep_id == id) {
            return dep_name;
        }
    }

    return ""s;
}

int DepartmentRepositoryImpl::GetDepId(const std::string& dep) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Отдел ORDER BY КодОтдела;"s;

    auto resp = tr.query<int, int, std::string, int>(query);

    for (const auto& [dep_id, manager_personnel_num, dep_name, office_num] : resp) {
        if (dep_name == dep) {
            return dep_id;
        }
    }

    return -1;
}

std::vector<ui::detail::DepartmentInfo> DepartmentRepositoryImpl::Get() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    EmployeeRepositoryImpl emp(pool_);

    std::string query = "SELECT * FROM Отдел ORDER BY КодОтдела;"s;

    auto resp = tr.query<int, int, std::string, int>(query);

    std::vector<ui::detail::DepartmentInfo> result;

    for (const auto& [id, manager_pers, dep_name, office_num] : resp) {
        ui::detail::DepartmentInfo department{id, emp.GetFio(manager_pers), dep_name, office_num};
        result.push_back(department);
    }

    return result;
}

int DepartmentRepositoryImpl::GetCount() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT COUNT(*) FROM Отдел;"s;

    auto count = tr.query_value<int>(query);

    return count;
}

std::optional<std::string> EmployeeRepositoryImpl::GetDateOfDismissal(int personnel_number) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    JobTitleRepositoryImpl job_titles(pool_);

    std::string query = "SELECT * FROM Сотрудник ORDER BY ТабельныйНомер;"s;

    auto resp = tr.query<int, std::string, std::string, std::string, int, int, std::optional<int>, std::string,
                         std::string, std::string, std::string, std::string, std::string,
                         std::optional<std::string>>(query);

    std::vector<ui::detail::EmployeeInfo> result;

    for (const auto& [personnel_num, full_name, gender, birthday, job_title_id, dep_id, experience, number,
                      registration, education, date, mail, merial_status, date_of_dismissal] : resp) {
        if (personnel_number == personnel_num) {
            return date_of_dismissal;
        }
    }

    return ""s;
}

std::string EmployeeRepositoryImpl::GetFio(int id) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Сотрудник ORDER BY ТабельныйНомер;"s;

    auto resp = tr.query<int, std::string, std::string, std::string, int, int, std::optional<int>, std::string,
                         std::string, std::string, std::string, std::string, std::string,
                         std::optional<std::string>>(query);

    for (const auto& [personnel_num, full_name, gender, birthday, job_title_id, dep_id, experience, number,
                      registration, education, date, mail, merial_status, date_of_dismissal] : resp) {
        if (personnel_num == id) {
            return full_name;;
        }
    }

    return ""s;
}

int EmployeeRepositoryImpl::GetId(const std::string& fio) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Сотрудник ORDER BY ТабельныйНомер;"s;

    auto resp = tr.query<int, std::string, std::string, std::string, int, int, std::optional<int>, std::string,
                         std::string, std::string, std::string, std::string, std::string,
                         std::optional<std::string>>(query);

    for (const auto& [personnel_num, full_name, gender, birthday, job_title_id, dep_id, experience, number,
                      registration, education, date, mail, merial_status, date_of_dismissal] : resp) {
        if (fio == full_name) {
            return personnel_num;
        }
    }

    return -1;
}

std::unordered_set<std::string> EmployeeRepositoryImpl::GetEmails() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT Почта FROM Сотрудник ORDER BY ТабельныйНомер;"s;

    pqxx::result resp = tr.exec(query);

    std::unordered_set<std::string> emails;

    for (const auto& row : resp) {
        std::string email = row["Почта"].as<std::string>();
        emails.insert(email);
    }

    return emails;
}

int EmployeeRepositoryImpl::GetPersonnelNumberForEmail(const std::string& email) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT ТабельныйНомер FROM Сотрудник WHERE Почта = '" + email + "'"s + ";"s;

    auto id = tr.query_value<int>(query);

    return id;
}

std::vector<ui::detail::EmployeeInfo> EmployeeRepositoryImpl::Get() const {
    auto conn = pool_.GetConnection();

    {
        pqxx::work txn(*conn);
        std::string delete_query = R"(
            DELETE FROM Сотрудник
            WHERE EXTRACT(YEAR FROM CURRENT_DATE) - EXTRACT(YEAR FROM ДатаУвольнения) > 10;
        )";
        txn.exec(delete_query);
        txn.commit();
    }

    pqxx::read_transaction tr(*conn);

    JobTitleRepositoryImpl job_titles(pool_);
    DepartmentRepositoryImpl dep(pool_);

    std::string query = "SELECT * FROM Сотрудник ORDER BY ТабельныйНомер;"s;

    auto resp = tr.query<int, std::string, std::string, std::string, int, int, std::optional<int>, std::string,
                         std::string, std::string, std::string, std::string, std::string,
                         std::optional<std::string>>(query);

    std::vector<ui::detail::EmployeeInfo> result;

    for (const auto& [personnel_num, full_name, gender, birthday, job_title_id, dep_id, experience, number,
                      registration, education, date, mail, merial_status, date_of_dismissal] : resp) {
        ui::detail::EmployeeInfo employee{personnel_num, full_name, gender, birthday,
                                          job_titles.GetJobTitle(job_title_id),
                                          dep.GetDep(dep_id),
                                          experience, number, registration, education,
                                          date, mail, merial_status, date_of_dismissal};
        result.push_back(employee);
    }

    return result;
}

std::vector<ui::detail::EmployeeInfo> EmployeeRepositoryImpl::GetForPerson(int personnel_number) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    JobTitleRepositoryImpl job_titles(pool_);
    DepartmentRepositoryImpl dep(pool_);

    std::string query = "SELECT * FROM Сотрудник ORDER BY ТабельныйНомер;"s;

    auto resp = tr.query<int, std::string, std::string, std::string, int, int, std::optional<int>, std::string,
                         std::string, std::string, std::string, std::string, std::string,
                         std::optional<std::string>>(query);

    std::vector<ui::detail::EmployeeInfo> result;

    for (const auto& [personnel_num, full_name, gender, birthday, job_title_id, dep_id, experience, number,
                      registration, education, date, mail, merial_status, date_of_dismissal] : resp) {
        if (personnel_number != personnel_num) {
            continue;
        }
        ui::detail::EmployeeInfo employee{personnel_num, full_name, gender, birthday,
                                          job_titles.GetJobTitle(job_title_id),
                                          dep.GetDep(dep_id),
                                          experience, number, registration, education,
                                          date, mail, merial_status, date_of_dismissal};
        result.push_back(employee);
    }

    return result;
}

std::vector<ui::detail::FreeJobTitleInfo> EmployeeRepositoryImpl::GetFreeJobTitles() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    JobTitleRepositoryImpl job_titles(pool_);
    DepartmentRepositoryImpl dep(pool_);

    std::string query = R"(
        SELECT
            sr.КодДолжности,
            sr.КодОтдела,
           (sr.КоличествоСтавок - COALESCE(COUNT(s.КодДолжности), 0)) AS СвободныеВакансии
        FROM
            ШтатноеРасписание sr
        LEFT JOIN
            Сотрудник s ON sr.КодДолжности = s.КодДолжности AND sr.КодОтдела = s.КодОтдела
        GROUP BY
            sr.КодОтдела, sr.КодДолжности, sr.КоличествоСтавок
        HAVING
           (sr.КоличествоСтавок - COALESCE(COUNT(s.КодДолжности), 0)) > 0
    )";

    auto resp = tr.query<int, int, int>(query);

    std::vector<ui::detail::FreeJobTitleInfo> result;

    for (const auto& [job_title_id, dep_id, free_job] : resp) {
        ui::detail::FreeJobTitleInfo free_job_title{job_titles.GetJobTitle(job_title_id),
                                                    dep.GetDep(dep_id), free_job};
        result.push_back(free_job_title);
    }

    return result;
}

int EmployeeRepositoryImpl::GetCount() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT COUNT(*) FROM Сотрудник;"s;

    auto count = tr.query_value<int>(query);

    return count;
}

std::string JobTitleRepositoryImpl::GetJobTitle(int id) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Должность ORDER BY КодДолжности;"s;

    auto resp = tr.query<int, std::string>(query);

    for (const auto& [job_title_id, job_title] : resp) {
        if (id == job_title_id) {
            return job_title;
        }
    }

    return ""s;
}

int JobTitleRepositoryImpl::GetJobTitleId(const std::string& job_title) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Должность ORDER BY КодДолжности;"s;

    auto resp = tr.query<int, std::string>(query);

    for (const auto& [id, j_title] : resp) {
        if (job_title == j_title) {
            return id;
        }
    }

    return -1;
}

std::vector<ui::detail::JobTitleInfo> JobTitleRepositoryImpl::Get() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Должность ORDER BY КодДолжности;"s;

    auto resp = tr.query<int, std::string>(query);

    std::vector<ui::detail::JobTitleInfo> result;

    for (const auto& [id, job_title] : resp) {
        ui::detail::JobTitleInfo job_title_info{id, job_title};
        result.push_back(job_title_info);
    }

    return result;
}

int JobTitleRepositoryImpl::GetCount() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT COUNT(*) FROM Должность;"s;

    auto count = tr.query_value<int>(query);

    return count;
}

std::vector<ui::detail::OrderInfo> OrderRepositoryImpl::Get() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Приказ ORDER BY НомерПриказа;"s;

    auto resp = tr.query<int, int, std::string, std::string>(query);

    std::vector<ui::detail::OrderInfo> result;

    for (const auto& [order_id, personnel_number, date, content] : resp) {
        ui::detail::OrderInfo order{order_id, personnel_number, date, content};
        result.push_back(order);
    }

    return result;
}

std::vector<ui::detail::OrderInfo> OrderRepositoryImpl::GetForPerson(int personnel_number) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Приказ ORDER BY НомерПриказа;"s;

    auto resp = tr.query<int, int, std::string, std::string>(query);

    std::vector<ui::detail::OrderInfo> result;

    for (const auto& [order_id, personnel_num, date, content] : resp) {
        if (personnel_num != personnel_number){
            continue;
        }
        ui::detail::OrderInfo order{order_id, personnel_number, date, content};
        result.push_back(order);
    }

    return result;
}

int OrderRepositoryImpl::GetCount() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT COUNT(*) FROM Приказ;"s;

    auto count = tr.query_value<int>(query);

    return count;
}

std::vector<ui::detail::StaffingTableInfo> StaffingTableRepositoryImpl::Get() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    JobTitleRepositoryImpl job_titles(pool_);
    DepartmentRepositoryImpl deps(pool_);

    std::string query = "SELECT * FROM ШтатноеРасписание ORDER BY НомерЗаписи;"s;

    auto resp = tr.query<int, int, int, int, int>(query);

    std::vector<ui::detail::StaffingTableInfo> result;

    for (const auto& [staffing_table_id, job_title_id, department_id, time_job, salary] : resp) {
        ui::detail::StaffingTableInfo staffing_table{staffing_table_id, job_titles.GetJobTitle(job_title_id),
                                                     deps.GetDep(department_id), time_job, salary};
        result.push_back(staffing_table);
    }

    return result;
}

int StaffingTableRepositoryImpl::GetCount() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT COUNT(*) FROM ШтатноеРасписание;"s;

    auto count = tr.query_value<int>(query);

    return count;
}

std::vector<ui::detail::TimeSheetInfo> TimeSheetRepositoryImpl::Get() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM ТабельУчетаРабочегоВремени ORDER BY НомерЗаписи;"s;

    auto resp = tr.query<int, int, int, std::string, std::string>(query);

    std::vector<ui::detail::TimeSheetInfo> result;

    for (const auto& [time_sheet_id, personnel_number, time_worked, month, year] : resp) {
        ui::detail::TimeSheetInfo time_sheet{time_sheet_id, personnel_number, time_worked, month, year};
        result.push_back(time_sheet);
    }

    return result;
}

std::vector<ui::detail::TimeSheetInfo> TimeSheetRepositoryImpl::GetForPerson(int personnel_number) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM ТабельУчетаРабочегоВремени ORDER BY НомерЗаписи;"s;

    auto resp = tr.query<int, int, int, std::string, std::string>(query);

    std::vector<ui::detail::TimeSheetInfo> result;

    for (const auto& [time_sheet_id, personnel_num, time_worked, month, year] : resp) {
        if (personnel_number != personnel_num) {
            continue;
        }
        ui::detail::TimeSheetInfo time_sheet{time_sheet_id, personnel_number, time_worked, month, year};
        result.push_back(time_sheet);
    }

    return result;
}

int TimeSheetRepositoryImpl::GetCount() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT COUNT(*) FROM ТабельУчетаРабочегоВремени;"s;

    auto count = tr.query_value<int>(query);

    return count;
}

std::vector<ui::detail::VacationInfo> VacationRepositoryImpl::Get() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Отпуск ORDER BY НомерЗаписи;"s;

    auto resp = tr.query<int, int, std::string, std::string, std::string, int, std::string, std::string>(query);

    std::vector<ui::detail::VacationInfo> result;

    for (const auto& [vacation_id, personnel_number, type, from_date, to_date, days, leave_basis, status] : resp) {
        ui::detail::VacationInfo time_sheet{vacation_id, personnel_number, type, from_date,
                                            to_date, days, leave_basis, status};
        result.push_back(time_sheet);
    }

    return result;
}

std::vector<ui::detail::VacationInfo> VacationRepositoryImpl::GetForPerson(int personnel_number) const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT * FROM Отпуск ORDER BY НомерЗаписи;"s;

    auto resp = tr.query<int, int, std::string, std::string, std::string, int, std::string, std::string>(query);

    std::vector<ui::detail::VacationInfo> result;

    for (const auto& [vacation_id, personnel_num, type, from_date, to_date, days, leave_basis, status] : resp) {
        if (personnel_number != personnel_num) {
            continue;
        }
        ui::detail::VacationInfo time_sheet{vacation_id, personnel_number, type, from_date,
                                            to_date, days, leave_basis, status};
        result.push_back(time_sheet);
    }

    return result;
}

int VacationRepositoryImpl::GetCount() const {
    auto conn = pool_.GetConnection();
    pqxx::read_transaction tr(*conn);

    std::string query = "SELECT COUNT(*) FROM Отпуск;"s;

    auto count = tr.query_value<int>(query);

    return count;
}

DataBase::DataBase(const std::string& db_url)
    : pool_{std::thread::hardware_concurrency(),
  [&db_url](){ return std::make_shared<pqxx::connection>(db_url); } }
    , trips_{pool_}
    , composition_trips_{pool_}
    , deps_{pool_}
    , employees_{pool_}
    , job_titles_{pool_}
    , orders_{pool_}
    , staffing_table_{pool_}
    , time_sheet_{pool_}
    , vacations_{pool_} {}

WorkerImpl::WorkerImpl(pqxx::connection& conn) : conn_(conn), nontr_(conn) {}

void WorkerImpl::AddBusinessTrip(const domain::BusinessTrip& trip) {
    nontr_.exec_params(
        R"(
    INSERT INTO Командировка (НомерЗаписи, Страна, Город, Организация,
                              СДата, ПоДату, КоличествоДней, Цель) VALUES
                             ($1, $2, $3, $4, $5, $6, $7, $8);
    )"_zv,
        trip.GetTripId(), trip.GetCountry(), trip.GetCity(), trip.GetOrganization(),
        trip.GetFromDate(), trip.GetToDate(), trip.GetDays(), trip.GetTarget());
}

void WorkerImpl::UpdateBusinessTrip(const domain::BusinessTrip& trip, int id) {
    nontr_.exec_params(
        R"(
    UPDATE Командировка SET Страна=$2, Город=$3, Организация=$4, СДата=$5, ПоДату=$6,
                            КоличествоДней=$7, Цель=$8 WHERE НомерЗаписи=$1;
    )"_zv,
        id, trip.GetCountry(), trip.GetCity(), trip.GetOrganization(),
        trip.GetFromDate(), trip.GetToDate(), trip.GetDays(), trip.GetTarget());
}

void WorkerImpl::AddCompositionBusinessTrip(const domain::CompositionBusinessTrip& trip) {
    nontr_.exec_params(
        R"(
    INSERT INTO СоставКомандировки (ТабельныйНомер, НомерЗаписи) VALUES
                                   ($1, $2);
    )"_zv,
        trip.GetPersonnelNumber(), trip.GetTripId());
}

void WorkerImpl::DeleteCompositionBusinessTrip(const domain::CompositionBusinessTrip& trip, int id) {
    nontr_.exec_params(
        R"(
    DELETE FROM СоставКомандировки WHERE ТабельныйНомер=$1 AND НомерЗаписи=$2;
    )"_zv,
        id, trip.GetTripId());
}

void WorkerImpl::UpdateCompositionBusinessTrip(const domain::CompositionBusinessTrip& trip, int id) {
    nontr_.exec_params(
        R"(
    UPDATE СоставКомандировки SET НомерЗаписи=$2 WHERE ТабельныйНомер=$1;
    )"_zv,
        trip.GetPersonnelNumber(), id);
}

void WorkerImpl::AddDepartment(const domain::Department& dep) {
    nontr_.exec_params(
        R"(
    INSERT INTO Отдел (КодОтдела, ТабельныйНомерРуководителя, Название, НомерКабинета) VALUES ($1, $2, $3, $4);
    )"_zv,
        dep.GetDepartmentId(), dep.GetManagerPersonalNum(), dep.GetDepName(), dep.GetOfficeNum());
}

void WorkerImpl::UpdateDepartment(const domain::Department& dep, int id) {
    nontr_.exec_params(
        R"(
    UPDATE Отдел SET ТабельныйНомерРуководителя=$2, Название=$3, НомерКабинета=$4 WHERE КодОтдела=$1;
    )"_zv,
        id, dep.GetManagerPersonalNum(), dep.GetDepName(), dep.GetOfficeNum());
}

void WorkerImpl::AddEmployee(const domain::Employee& employee) {
    if (employee.GetExperience().has_value()) {
        nontr_.exec_params(
            R"(
        INSERT INTO Сотрудник (ТабельныйНомер, ФИО, Пол, ДатаРождения, КодОтдела, Стаж,
                               Телефон, Прописка, Образование, ДатаПриема,
                               Почта, СемейноеПоложение)
                               VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13);
        )"_zv,
            employee.GetPersonnelNumber(), employee.GetFullName(), employee.GetGender(), employee.GetBirthday(),
            employee.GetJobTitleId(), employee.GetDepartmentId(), *employee.GetExperience(), employee.GetNumber(), employee.GetRegistration(),
            employee.GetEducation(), employee.GetDate(), employee.GetMail(), employee.GetMerialStatus());
    }
    else {
        nontr_.exec_params(
            R"(
        INSERT INTO Сотрудник (ТабельныйНомер, ФИО, Пол, ДатаРождения, КодДолжности, КодОтдела,
                               Телефон, Прописка, Образование, ДатаПриема,
                               Почта, СемейноеПоложение)
                               VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10);
        )"_zv,
            employee.GetPersonnelNumber(), employee.GetFullName(), employee.GetGender(), employee.GetBirthday(),
            employee.GetJobTitleId(), employee.GetDepartmentId(), employee.GetNumber(), employee.GetRegistration(),
            employee.GetEducation(), employee.GetDate(), employee.GetMail(), employee.GetMerialStatus());
    }
}

void WorkerImpl::UpdateEmployee(const domain::Employee& employee, int id) {
    nontr_.exec_params(
        R"(
    UPDATE Сотрудник SET ФИО=$2, Пол=$3, ДатаРождения=$4, КодДолжности=$5, КодОтдела=$6, Стаж=$7,
           Телефон=$8, Прописка=$9, Образование=$10, ДатаПриема=$11,
           Почта=$12, СемейноеПоложение=$13, ДатаУвольнения=$14 WHERE ТабельныйНомер=$1;
    )"_zv,
        id, employee.GetFullName(), employee.GetGender(), employee.GetBirthday(),
        employee.GetJobTitleId(), employee.GetDepartmentId(), *employee.GetExperience(), employee.GetNumber(), employee.GetRegistration(),
        employee.GetEducation(), employee.GetDate(), employee.GetMail(), employee.GetMerialStatus(), employee.GetDateOfDismissal());
}

void WorkerImpl::AddJobTitle(const domain::JobTitle& job_title) {
    nontr_.exec_params(
        R"(
    INSERT INTO Должность (КодДолжности, Название) VALUES ($1, $2);
    )"_zv,
        job_title.GetJobTitleId(), job_title.GetJobTitle());
}

void WorkerImpl::UpdateJobTitle(const domain::JobTitle& job_title, int id) {
    nontr_.exec_params(
        R"(
    UPDATE Должность SET Название=$2 WHERE КодДолжности=$1;
    )"_zv,
       id, job_title.GetJobTitle());
}

void WorkerImpl::AddOrder(const domain::Order& order) {
    nontr_.exec_params(
        R"(
    INSERT INTO Приказ (НомерПриказа, ТабельныйНомер, ДатаОформления, Содержание) VALUES ($1, $2, $3, $4);
    )"_zv,
        order.GetOrderId(), order.GetPersonnelNumber(), order.GetDate(), order.GetContent());
}

void WorkerImpl::UpdateOrder(const domain::Order& order, int id) {
    nontr_.exec_params(
        R"(
    UPDATE Приказ SET ТабельныйНомер=$2, ДатаОформления=$3, Содержание=$4 WHERE НомерПриказа=$1;
    )"_zv,
        id, order.GetPersonnelNumber(), order.GetDate(), order.GetContent());
}

void WorkerImpl::AddStaffingTable(const domain::StaffingTable& staffing_table) {
    nontr_.exec_params(
        R"(
    INSERT INTO ШтатноеРасписание (НомерЗаписи, КодДолжности, КодОтдела, КоличествоСтавок, Оклад) VALUES ($1, $2, $3, $4, $5);
    )"_zv,
        staffing_table.GetStaffingTableId(), staffing_table.GetJobTitleId(), staffing_table.GetDepartmentId(),
        staffing_table.GetTimeJob(), staffing_table.GetSalary());
}

void WorkerImpl::UpdateStaffingTable(const domain::StaffingTable& staffing_table, int id) {
    nontr_.exec_params(
        R"(
    UPDATE ШтатноеРасписание SET КодДолжности=$2, КодОтдела=$3, КоличествоСтавок=$4, Оклад=$5 WHERE НомерЗаписи=$1;
    )"_zv,
        id, staffing_table.GetJobTitleId(), staffing_table.GetDepartmentId(),
        staffing_table.GetTimeJob(), staffing_table.GetSalary());
}

void WorkerImpl::AddTimeSheet(const domain::TimeSheet& time_sheet) {
    nontr_.exec_params(
        R"(
    INSERT INTO ТабельУчетаРабочегоВремени (НомерЗаписи, ТабельныйНомер, ОтработанноеВремя, Месяц, Год) VALUES ($1, $2, $3, $4, $5);
    )"_zv,
        time_sheet.GetTimeSheetId(), time_sheet.GetPersonnelNumber(), time_sheet.GetTimeWorked(), time_sheet.GetMonth(),
        time_sheet.GetYear());
}

void WorkerImpl::UpdateTimeSheet(const domain::TimeSheet& time_sheet, int id) {
    nontr_.exec_params(
        R"(
    UPDATE ТабельУчетаРабочегоВремени SET ТабельныйНомер=$2, ОтработанноеВремя=$3, Месяц=$4, Год=$5 WHERE НомерЗаписи=$1;
    )"_zv,
        id, time_sheet.GetPersonnelNumber(), time_sheet.GetTimeWorked(), time_sheet.GetMonth(), time_sheet.GetYear());
}

void WorkerImpl::AddVacation(const domain::Vacation& vacation) {
    nontr_.exec_params(
        R"(
    INSERT INTO Отпуск (НомерЗаписи, ТабельныйНомер, ВидОтпуска, ДатаОтпуска,
                        ДатаОкончания, КоличествоДней, Основание, Статус)
                        VALUES ($1, $2, $3, $4, $5, $6, $7, $8);
    )"_zv,
        vacation.GetVacationId(), vacation.GetPersonnelNumber(), vacation.GetType(),
        vacation.GetFromDate(), vacation.GetToDate(), vacation.GetDays(), vacation.GetLeaveBasis());
}

void WorkerImpl::DeleteVacation(const domain::Vacation& vacation, int id) {
    nontr_.exec_params(
        R"(
    DELETE FROM Отпуск WHERE НомерЗаписи=$1 AND ТабельныйНомер=$2 AND ВидОтпуска=$3 AND ДатаОтпуска=$4
                             AND ДатаОкончания=$5 AND КоличествоДней=$6 AND Основание=$7 AND Статус=$8;
    )"_zv,
        id, vacation.GetPersonnelNumber(), vacation.GetType(),
        vacation.GetFromDate(), vacation.GetToDate(), vacation.GetDays(), vacation.GetLeaveBasis(),
        vacation.GetStatus());
}

void WorkerImpl::UpdateVacation(const domain::Vacation& vacation, int id) {
    nontr_.exec_params(
        R"(
    UPDATE Отпуск SET ТабельныйНомер=$2, ВидОтпуска=$3, ДатаОтпуска=$4,
                      ДатаОкончания=$5, КоличествоДней=$6, Основание=$7, Статус=$8 WHERE НомерЗаписи=$1;
    )"_zv,
        id, vacation.GetPersonnelNumber(), vacation.GetType(),
        vacation.GetFromDate(), vacation.GetToDate(), vacation.GetDays(), vacation.GetLeaveBasis(),
        vacation.GetStatus());
}

WorkerImpl::~WorkerImpl() = default;

} // namespace postgres
