#pragma once

#include <boost/json.hpp>
#include <chrono>
#include <iosfwd>
#include <optional>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

namespace app {
class UseCases;
} // namespace app

namespace ui {

namespace detail {
namespace json = boost::json;
using namespace std::literals;

struct BusinessTripInfo {
    int trip_id;
    std::string country;
    std::string city;
    std::string organization;
    std::string from_date;
    std::string to_date;
    int days;
    std::string target;

    friend void tag_invoke(json::value_from_tag, json::value& jv,
                           const ui::detail::BusinessTripInfo& trip) {
        jv = {
            {"НомерЗаписи"s, trip.trip_id},
            {"Страна"s, trip.country},
            {"Город"s, trip.city},
            {"Организация"s, trip.organization},
            {"СДата"s, trip.from_date},
            {"ПоДату"s, trip.to_date},
            {"КоличествоДней"s, trip.days},
            {"Цель"s, trip.target}
        };
    }

    friend ui::detail::BusinessTripInfo
    tag_invoke(json::value_to_tag<ui::detail::BusinessTripInfo>&, const json::value&
               trip) {
        ui::detail::BusinessTripInfo tr;

        tr.trip_id = trip.at("НомерЗаписи").as_int64();
        tr.country = trip.at("Страна").as_string();
        tr.city = trip.at("Город").as_string();
        tr.organization = trip.at("Организация").as_string();
        tr.from_date = trip.at("СДата").as_string();
        tr.to_date = trip.at("ПоДату").as_string();
        tr.days = trip.at("КоличествоДней").as_int64();
        tr.target = trip.at("Цель").as_string();

        return tr;
    }
};

struct CompositionBusinessTripInfo {
    int personnel_number;
    std::variant<std::string, int> trip;

    friend void tag_invoke(json::value_from_tag, json::value& jv,
                           const ui::detail::CompositionBusinessTripInfo& trip) {
        jv = {
            {"ТабельныйНомер"s, trip.personnel_number},
            {"НомерЗаписи"s, std::get<std::string>(trip.trip)}
        };
    }

    friend ui::detail::CompositionBusinessTripInfo
    tag_invoke(json::value_to_tag<ui::detail::CompositionBusinessTripInfo>&, const
               json::value& trip) {
        ui::detail::CompositionBusinessTripInfo tr;

        tr.personnel_number = trip.at("ТабельныйНомер").as_int64();
        tr.trip = static_cast<int>(trip.at("НомерЗаписи").as_int64());

        return tr;
    }
};

struct DepartmentInfo {
    int department_id;
    std::variant<std::string, int> manager_personnel;
    std::string dep_name;
    int office_num;

    friend void tag_invoke (json::value_from_tag, json::value& jv,
                            const ui::detail::DepartmentInfo& department) {
        jv = {
            {"КодОтдела"s, department.department_id},
            {"ТабельныйНомерРуководителя"s, std::get<std::string>(department.manager_personnel)},
            {"Название"s, department.dep_name},
            {"НомерКабинета"s, department.office_num}
        };
    }

    friend ui::detail::DepartmentInfo
    tag_invoke(json::value_to_tag<ui::detail::DepartmentInfo>&, const json::value&
               department) {
        ui::detail::DepartmentInfo dep;

        dep.department_id = department.at("КодОтдела").as_int64();
        dep.manager_personnel = static_cast<int>(department.at("ТабельныйНомерРуководителя").as_int64());
        dep.dep_name = department.at("Название").as_string();
        dep.office_num = department.at("НомерКабинета").as_int64();

        return dep;
    }
};

struct EmployeeInfo {
    int personnel_number;
    std::string full_name;
    std::string gender;
    std::string birthday;
    std::variant<std::string, int> job_title;
    std::variant<std::string, int> department;
    std::optional<int> experience;
    std::string number;
    std::string registration;
    std::string education;
    std::string date;
    std::string mail;
    std::string marital_status;
    std::optional<std::string> date_of_dismissal;

    friend void tag_invoke(json::value_from_tag, json::value& jv,
                           const ui::detail::EmployeeInfo& employee) {
        jv = {
            {"ТабельныйНомер"s, employee.personnel_number},
            {"ФИО"s, employee.full_name},
            {"Пол"s, employee.gender},
            {"ДатаРождения", employee.birthday},
            {"КодДолжности"s, std::get<std::string>(employee.job_title)},
            {"КодОтдела"s, std::get<std::string>(employee.department)},
            {"Стаж"s, employee.experience ? std::to_string(*employee.experience) : "NULL"s},
            {"Телефон"s, employee.number},
            {"Прописка"s, employee.registration},
            {"Образование"s, employee.education},
            {"ДатаПриема"s, employee.date},
            {"Почта"s, employee.mail},
            {"СемейноеПоложение"s, employee.marital_status},
            {"ДатаУвольнения"s, employee.date_of_dismissal ? *employee.date_of_dismissal : "NULL"s}
        };
    }

    friend ui::detail::EmployeeInfo
    tag_invoke(json::value_to_tag<ui::detail::EmployeeInfo>&, const json::value&
               employee) {
        ui::detail::EmployeeInfo emp;

        emp.personnel_number = employee.at("ТабельныйНомер").as_int64();
        emp.full_name = employee.at("ФИО").as_string();
        emp.gender = employee.at("Пол").as_string();
        emp.birthday = employee.at("ДатаРождения").as_string();
        emp.job_title = static_cast<int>(employee.at("КодДолжности").as_int64());
        emp.department = static_cast<int>(employee.at("КодОтдела").as_int64());
        if (employee.as_object().if_contains("Стаж")) {
            if (employee.at("Стаж").is_int64()) {
                emp.experience = employee.at("Стаж").as_int64();
            }
            if (employee.at("Стаж").is_string()) {
                emp.experience = std::stoi(employee.at("Стаж").as_string().c_str());
            }
        }
        if (employee.as_object().if_contains("ДатаУвольнения")) {
            emp.date_of_dismissal = employee.at("ДатаУвольнения").as_string();
        }
        emp.number = employee.at("Телефон").as_string();
        emp.registration = employee.at("Прописка").as_string();
        emp.education = employee.at("Образование").as_string();
        emp.date = employee.at("ДатаПриема").as_string();
        emp.mail = employee.at("Почта").as_string();
        emp.marital_status = employee.at("СемейноеПоложение").as_string();

        return emp;
    }
};

struct FreeJobTitleInfo {
    std::variant<std::string, int> job_title;
    std::variant<std::string, int> department;
    int free_job;

    friend void tag_invoke(json::value_from_tag, json::value& jv,
                           const ui::detail::FreeJobTitleInfo& free_job_title) {
        jv = {
            {"КодДолжности"s, std::get<std::string>(free_job_title.job_title)},
            {"КодОтдела"s, std::get<std::string>(free_job_title.department)},
            {"СвободныеВакансии"s, free_job_title.free_job}
        };
    }

    friend ui::detail::FreeJobTitleInfo
    tag_invoke(json::value_to_tag<ui::detail::FreeJobTitleInfo>&, const json::value&
               free_job_title) {
        ui::detail::FreeJobTitleInfo free_j_title;

        free_j_title.job_title = static_cast<int>(free_job_title.at("КодДолжности").as_int64());
        free_j_title.department = static_cast<int>(free_job_title.at("КодОтдела").as_int64());
        free_j_title.free_job = free_job_title.at("СвободныеВакансии").as_int64();

        return free_j_title;
    }
};

struct JobTitleInfo {
    int job_title_id;
    std::string job_title;

    friend void tag_invoke(json::value_from_tag, json::value& jv,
                           const ui::detail::JobTitleInfo& job_title) {
        jv = {
            {"КодДолжности"s, job_title.job_title_id},
            {"Название"s, job_title.job_title}
        };
    }

    friend ui::detail::JobTitleInfo
    tag_invoke(json::value_to_tag<ui::detail::JobTitleInfo>&, const json::value&
               job_title) {
        ui::detail::JobTitleInfo job_t;

        job_t.job_title_id = job_title.at("КодДолжности").as_int64();
        job_t.job_title = job_title.at("Название").as_string();

        return job_t;
    }
};

struct OrderInfo {
    int order_id;
    int personnel_number;
    std::string date;
    std::string content;

    friend void tag_invoke(json::value_from_tag, json::value& jv, const
                           ui::detail::OrderInfo& order) {
        jv = {
            {"НомерПриказа"s, order.order_id},
            {"ТабельныйНомер"s, order.personnel_number},
            {"ДатаОформления"s, order.date},
            {"Содержание"s, order.content}
        };
    }

    friend ui::detail::OrderInfo tag_invoke(json::value_to_tag<ui::detail::OrderInfo>&,
                                            const json::value& order) {
        ui::detail::OrderInfo ord;

        ord.order_id = order.at("НомерПриказа").as_int64();
        ord.personnel_number = order.at("ТабельныйНомер").as_int64();
        ord.date = order.at("ДатаОформления").as_string();
        ord.content = order.at("Содержание").as_string();

        return ord;
    }
};

struct StaffingTableInfo {
    int staffing_table_id;
    std::variant<std::string, int> job_title;
    std::variant<std::string, int> department;
    int time_job;
    int salary;

    friend void tag_invoke(json::value_from_tag, json::value& jv,
                           const ui::detail::StaffingTableInfo& staffing_table) {
        jv = {
            {"НомерЗаписи"s, staffing_table.staffing_table_id},
            {"КодДолжности"s, std::get<std::string>(staffing_table.job_title)},
            {"КодОтдела"s, std::get<std::string>(staffing_table.department)},
            {"КоличествоСтавок"s, staffing_table.time_job},
            {"Оклад"s, staffing_table.salary}
        };
    }

    friend ui::detail::StaffingTableInfo
    tag_invoke(json::value_to_tag<ui::detail::StaffingTableInfo>&, const
               json::value& staffing_table) {
        ui::detail::StaffingTableInfo staf_t;

        staf_t.staffing_table_id = staffing_table.at("НомерЗаписи").as_int64();
        staf_t.job_title = static_cast<int>(staffing_table.at("КодДолжности").as_int64());
        staf_t.department = static_cast<int>(staffing_table.at("КодОтдела").as_int64());
        staf_t.time_job = staffing_table.at("КоличествоСтавок").as_int64();
        staf_t.salary = staffing_table.at("Оклад").as_int64();

        return staf_t;
    }
};

struct TimeSheetInfo {
    int time_sheet_id;
    int personnel_number;
    int time_worked;
    std::string month;
    std::string year;

    friend void tag_invoke(json::value_from_tag, json::value& jv,
                           const ui::detail::TimeSheetInfo& time_sheet) {
        jv = {
            {"НомерЗаписи"s, time_sheet.time_sheet_id},
            {"ТабельныйНомер"s, time_sheet.personnel_number},
            {"ОтработанноеВремя"s, time_sheet.time_worked},
            {"Месяц"s, time_sheet.month},
            {"Год"s, time_sheet.year}
        };
    }

    friend ui::detail::TimeSheetInfo
    tag_invoke(json::value_to_tag<ui::detail::TimeSheetInfo>&, const json::value&
               time_sheet) {
        ui::detail::TimeSheetInfo time_s;

        time_s.time_sheet_id = time_sheet.at("НомерЗаписи").as_int64();
        time_s.personnel_number = time_sheet.at("ТабельныйНомер").as_int64();
        time_s.time_worked = time_sheet.at("ОтработанноеВремя").as_int64();
        time_s.month = time_sheet.at("Месяц").as_string();
        time_s.year = time_sheet.at("Год").as_string();

        return time_s;
    }
};

struct VacationInfo {
    int vacation_id;
    int personnel_number;
    std::string type;
    std::string from_date;
    std::string to_date;
    int days;
    std::string leave_basis;
    std::string status;

    friend void tag_invoke(json::value_from_tag, json::value& jv,
                           const ui::detail::VacationInfo& vacation) {
        jv = {
            {"НомерЗаписи"s, vacation.vacation_id},
            {"ТабельныйНомер"s, vacation.personnel_number},
            {"ВидОтпуска"s, vacation.type},
            {"ДатаОтпуска"s, vacation.from_date},
            {"ДатаОкончания"s, vacation.to_date},
            {"КоличествоДней"s, vacation.days},
            {"Основание"s, vacation.leave_basis},
            {"Статус", vacation.status}
        };
    }

    friend ui::detail::VacationInfo
    tag_invoke(json::value_to_tag<ui::detail::VacationInfo>&, const json::value&
               vacation) {
        ui::detail::VacationInfo vac;

        vac.vacation_id = vacation.at("НомерЗаписи").as_int64();
        vac.personnel_number = vacation.at("ТабельныйНомер").as_int64();
        vac.from_date = vacation.at("ДатаОтпуска").as_string();
        vac.to_date = vacation.at("ДатаОкончания").as_string();
        vac.type = vacation.at("ВидОтпуска").as_string();
        vac.days = vacation.at("КоличествоДней").as_int64();
        vac.leave_basis = vacation.at("Основание").as_string();
        vac.status = vacation.at("Статус").as_string();

        return vac;
    }
};

} // namespace detail

} // namespace ui
