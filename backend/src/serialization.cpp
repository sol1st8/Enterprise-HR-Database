#include "serialization.h"
#include "ui/view.h"

namespace {

void tag_invoke(json::value_from_tag, json::value& jv,
                const BusinessTripInfo& trip) {
    jv = {
        {"НомерЗаписи", trip.trip_id},
        {"Страна", trip.country},
        {"Город", trip.city},
        {"Организация", trip.organization},
        {"СДата", trip.from_date},
        {"ПоДату", trip.to_date},
        {"КоличествоДней", trip.days},
        {"Цель", trip.target}
    };
}

void tag_invoke(json::value_from_tag, json::value& jv,
                const CompositionBusinessTripInfo& trip) {
    jv = {
        {"ТабельныйНомер", trip.personnel_number},
        {"НомерЗаписи", trip.trip_id}
    };
}

void tag_invoke(json::value_from_tag, json::value& jv,
                const DepartmentInfo& department) {
    jv = {
        {"КодОтдела", department.department_id},
        {"ТабельныйНомерРуководителя", department.manager_personnel_number},
        {"Название", department.dep_name},
        {"НомерКабинета", department.office_num}
    };
}

void tag_invoke(json::value_from_tag, json::value& jv,
                const EmployeeInfo& employee) {
    jv = {
        {"ТабельныйНомер", employee.personnel_number},
        {"ФИО", employee.full_name},
        {"Пол", employee.gender},
        {"КодДолжности", employee.job_title_id},
        {"Стаж", employee.stage},
        {"Телефон", employee.number},
        {"Прописка", employee.registration},
        {"Образование", employee.education},
        {"ДатаПриема", employee.date},
        {"Почта", employee.mail},
        {"СемейноеПоложение", employee.marital_status}
    };
}

void tag_invoke(json::value_from_tag, json::value& jv,
                const JobTitleInfo& job_title) {
    jv = {
        {"КодДолжности", job_title.job_title_id},
        {"Название", job_title.job_title}
    };
}

void tag_invoke(json::value_from_tag, json::value& jv, const OrderInfo& order) {
    jv = {
        {"НомерПриказа", order.order_id},
        {"ТабельныйНомер", order.personnel_number},
        {"ДатаОформления", order.date},
        {"Содержание", order.content}
    };
}

void tag_invoke(json::value_from_tag, json::value& jv,
                const StaffingTableInfo& staffing_table) {
    jv = {
        {"НомерЗаписи", staffing_table.staffing_table_id},
        {"КодДолжности", staffing_table.job_title_id},
        {"КодОтдела", staffing_table.department_id},
        {"КоличествоСтавок", staffing_table.time_job},
        {"Оклад", staffing_table.salary}
    };
}

void tag_invoke(json::value_from_tag, json::value& jv,
                const TimeSheetInfo& time_sheet) {
    jv = {
        {"НомерЗаписи", time_sheet.time_sheet_id},
        {"ТабельныйНомер", time_sheet.personnel_number},
        {"ОтработанноеВремя", time_sheet.time_worked},
        {"Месяц", time_sheet.month}
    };
}

void tag_invoke(json::value_from_tag, json::value& jv,
                const VacationInfo& vacation) {
    jv = {
        {"НомерЗаписи", vacation.vacation_id},
        {"ТабельныйНомер", vacation.personnel_number},
        {"ВидОтпуска", vacation.type},
        {"ДатаОтпуска", vacation.from_date},
        {"ДатаОкончания", vacation.to_date},
        {"КоличествоДней", vacation.days},
        {"Основание", vacation.leave_basis}
    };
}


BusinessTripInfo tag_invoke(json::value_to_tag<BusinessTripInfo>&,
                            const json::value& trip) {
    BusinessTripInfo tr;

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

CompositionBusinessTripInfo tag_invoke(json::value_to_tag<CompositionBusinessTripInfo>&,
                                       const json::value& trip) {
    CompositionBusinessTripInfo tr;

    tr.personnel_number = trip.at("ТабельныйНомер").as_int64();
    tr.trip_id = trip.at("НомерЗаписи").as_int64();

    return tr;
}

DepartmentInfo tag_invoke(json::value_to_tag<DepartmentInfo>&,
                          const json::value& department) {
    DepartmentInfo dep;

    dep.department_id = department.at("КодОтдела").as_int64();
    dep.manager_personnel_number = department.at("ТабельныйНомерРуководителя").as_int64();
    dep.dep_name = department.at("Название").as_string();
    dep.office_num = department.at("НомерКабинета").as_int64();

    return dep;
}

EmployeeInfo tag_invoke(json::value_to_tag<EmployeeInfo>&,
                        const json::value& employee) {
    EmployeeInfo emp;

    emp.personnel_number = employee.at("ТабельныйНомер").as_int64();
    emp.full_name = employee.at("ФИО").as_string();
    emp.gender = employee.at("Пол").as_string();
    emp.job_title_id = employee.at("КодДолжности").as_int64();
    emp.stage = employee.at("Стаж").as_int64();
    emp.number = employee.at("Телефон").as_string();
    emp.registration = employee.at("Прописка").as_string();
    emp.education = employee.at("Образование").as_string();
    emp.date = employee.at("ДатаПриема").as_string();
    emp.mail = employee.at("Почта").as_string();
    emp.marital_status = employee.at("СемейноеПоложение").as_string();

    return emp;
}

JobTitleInfo tag_invoke(json::value_to_tag<JobTitleInfo>&,
                        const json::value& job_title) {
    JobTitleInfo job_t;

    job_t.job_title_id = job_title.at("КодДолжности").as_int64();
    job_t.job_title = job_title.at("Название").as_string();

    return job_t;
}

OrderInfo tag_invoke(json::value_to_tag<OrderInfo>&,
                     const json::value& order) {
    OrderInfo ord;

    ord.order_id = order.at("НомерПриказа").as_int64();
    ord.personnel_number = order.at("ТабельныйНомер").as_int64();
    ord.date = order.at("ДатаОформления").as_string();
    ord.content = order.at("Содержание").as_string();

    return ord;
}

StaffingTableInfo tag_invoke(json::value_to_tag<StaffingTableInfo>&,
                             const json::value& staffing_table) {
    StaffingTableInfo staf_t;

    staf_t.staffing_table_id = staffing_table.at("НомерЗаписи").as_int64();
    staf_t.job_title_id = staffing_table.at("КодДолжности").as_int64();
    staf_t.department_id = staffing_table.at("КодОтдела").as_int64();
    staf_t.time_job = staffing_table.at("КоличествоСтавок").as_int64();
    staf_t.salary = staffing_table.at("Оклад").as_int64();

    return staf_t;
}

TimeSheetInfo tag_invoke(json::value_to_tag<TimeSheetInfo>&,
                         const json::value& time_sheet) {
    TimeSheetInfo time_s;

    time_s.time_sheet_id = time_sheet.as_int64();
    time_s.personnel_number = time_sheet.as_int64();
    time_s.time_worked = time_sheet.as_int64();
    time_s.month = time_sheet.as_string();

    return time_s;
}

VacationInfo tag_invoke(json::value_to_tag<VacationInfo>&,
                        const json::value& vacation) {
    VacationInfo vac;

    vac.vacation_id = vacation.at("НомерЗаписи").as_int64();
    vac.personnel_number = vacation.at("ТабельныйНомер").as_int64();
    vac.from_date = vacation.at("ДатаОтпуска").as_string();
    vac.to_date = vacation.at("ДатаОкончания").as_string();
    vac.type = vacation.at("ВидОтпуска").as_string();
    vac.days = vacation.at("КоличествоДней").as_int64();
    vac.leave_basis = vacation.at("Основание").as_string();

    return vac;
}

} // namespace
