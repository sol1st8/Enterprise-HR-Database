#include "api_handler.h"

#include <algorithm>

namespace {

std::string CleanErrorMessage(const std::string& message) {
    std::string cleaned_message = message;

    size_t detail_pos = message.find("DETAIL:");
    if (detail_pos != std::string::npos) {
        cleaned_message = message.substr(detail_pos + 9);
    }

    cleaned_message.erase(std::remove(cleaned_message.begin(), cleaned_message.end(), '\"'), cleaned_message.end());
    cleaned_message.erase(std::remove(cleaned_message.begin(), cleaned_message.end(), '\n'), cleaned_message.end());

    return cleaned_message;
}

} // namespace

namespace api_handler {

bool ApiHandler::CheckEndPath() {
    return req_info_.target == "/"sv || req_info_.target.empty();
}

std::string ApiHandler::FindAndCutTarget(RequestInfo& req) {
    std::string res;

    size_t q_pos = req.target.find_last_of('?');

    size_t pos = req.target.find_first_of('/', 1);

    if (pos != req.target.npos) {
        res = req.target.substr(0, pos);
        req.target = req.target.substr(res.size());
        return res;
    }

    res = req.target;
    req.target = "";
    return res;
}

void ApiHandler::HandleApiResponse() {
    std::string path_part = FindAndCutTarget(req_info_);

    if (path_part == "/add"s) {
        HandleAdd();
    }
    else if (path_part == "/get"s) {
        HandleGet();
    }
    else if (path_part == "/update") {
        HandleUpdate();
    }
    else {
        SendBadRequestResponseDefault();
    }
}

void ApiHandler::HandleAdd() {
    std::string path_part = FindAndCutTarget(req_info_);

    if (path_part == "/business-trip"s) {
        HandleAddBusinessTrip();
    }
    else if (path_part == "/composition-business-trip"s) {
        HandleAddCompositionBusinessTrip();
    }
    else if (path_part == "/department"s) {
        HandleAddDepartment();
    }
    else if (path_part == "/employee"s) {
        HandleAddEmployee();
    }
    else if (path_part == "/job-title"s) {
        HandleAddJobTitle();
    }
    else if (path_part == "/order"s) {
        HandleAddOrder();
    }
    else if (path_part == "/staffing-table"s) {
        HandleAddStaffingTable();
    }
    else if (path_part == "/time-sheet"s) {
        HandleAddTimeSheet();
    }
    else if (path_part == "/vacation"s) {
        HandleAddVacation();
    }
    else {
        SendNotFoundResponse();
    }
}

void ApiHandler::HandleAddBusinessTrip() {
    if (req_info_.method != http::verb::post) {
        return SendWrongMethodResponseAllowedPost("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["НомерЗаписи"] = json::value(application_.GetUseCases().GetCountBusinessTrips() + 1);

    int days = jv.at("КоличествоДней").as_int64();
    if (days <= 0) {
        return SendBadRequestResponse("Ошибка КоличествоДней <= 0"s);
    }

    std::string from_date;
    std::string to_date;
    from_date = jv.at("СДата").as_string();
    to_date = jv.at("ПоДату").as_string();
    if (from_date >= to_date) {
        return SendBadRequestResponse("Ошибка СДата >= ПоДату"s);
    }

    ui::detail::BusinessTripInfo trip = json::value_to<ui::detail::BusinessTripInfo>(jv);

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().AddBusinessTrip(trip);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleAddCompositionBusinessTrip() {
    if (req_info_.method != http::verb::post) {
        return SendWrongMethodResponseAllowedPost("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);
    ui::detail::CompositionBusinessTripInfo trip = json::value_to<ui::detail::CompositionBusinessTripInfo>(jv);

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().AddCompositionBusinessTrip(trip);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleAddDepartment() {
    if (req_info_.method != http::verb::post) {
        return SendWrongMethodResponseAllowedPost("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["КодОтдела"] = json::value(application_.GetUseCases().GetCountDepartments() + 1);

    ui::detail::DepartmentInfo dep = json::value_to<ui::detail::DepartmentInfo>(jv);

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().AddDepartment(dep);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleAddEmployee() {
    if (req_info_.method != http::verb::post) {
        return SendWrongMethodResponseAllowedPost("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["ТабельныйНомер"] = json::value(application_.GetUseCases().GetCountEmployees() + 1);

    std::string job_title;
    job_title = jv.at("КодДолжности").as_string();
    jv.as_object()["КодДолжности"] = application_.GetUseCases().GetJobTitleId(job_title);
    if (jv.at("КодДолжности").as_int64() == -1) {
        return SendBadRequestResponse("Ошибка Должность не существует"s);
    }

    std::string gender;
    gender = jv.at("Пол").as_string();
    if (!(gender == "м" || gender == "ж")) {
        return SendBadRequestResponse("Ошибка Пол != м или ж"s);
    }

    ui::detail::EmployeeInfo employee = json::value_to<ui::detail::EmployeeInfo>(jv);

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().AddEmployee(employee);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleAddJobTitle() {
    if (req_info_.method != http::verb::post) {
        return SendWrongMethodResponseAllowedPost("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["КодДолжности"] = json::value(application_.GetUseCases().GetCountJobTitles() + 1);

    ui::detail::JobTitleInfo job_title = json::value_to<ui::detail::JobTitleInfo>(jv);

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().AddJobTitle(job_title);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleAddOrder() {
    if (req_info_.method != http::verb::post) {
        return SendWrongMethodResponseAllowedPost("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["НомерПриказа"] = json::value(application_.GetUseCases().GetCountOrders() + 1);

    ui::detail::OrderInfo order = json::value_to<ui::detail::OrderInfo>(jv);

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().AddOrder(order);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleAddStaffingTable() {
    if (req_info_.method != http::verb::post) {
        return SendWrongMethodResponseAllowedPost("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["НомерЗаписи"] = json::value(application_.GetUseCases().GetCountStaffingTable() + 1);

    std::string job_title;
    job_title = jv.at("КодДолжности").as_string();
    jv.as_object()["КодДолжности"] = application_.GetUseCases().GetJobTitleId(job_title);
    if (jv.at("КодДолжности").as_int64() == -1) {
        return SendBadRequestResponse("Ошибка Должность не существует"s);
    }

    std::string dep_name;
    dep_name = jv.at("КодОтдела").as_string();
    jv.as_object()["КодОтдела"] = application_.GetUseCases().GetDepartmentId(dep_name);
    if (jv.at("КодОтдела").as_int64() == -1) {
        return SendBadRequestResponse("Ошибка Отдел не существует"s);
    }

    int time_job = jv.at("КоличествоСтавок").as_int64();
    if (time_job <= 0) {
        return SendBadRequestResponse("Ошибка КоличествоСтавок <= 0"s);
    }

    int salary = jv.at("Оклад").as_int64();
    if (salary <= 0) {
        return SendBadRequestResponse("Ошибка Оклад <= 0"s);
    }

    ui::detail::StaffingTableInfo staffing_table = json::value_to<ui::detail::StaffingTableInfo>(jv);

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().AddStaffingTable(staffing_table);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleAddTimeSheet() {
    if (req_info_.method != http::verb::post) {
        return SendWrongMethodResponseAllowedPost("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["НомерЗаписи"] = json::value(application_.GetUseCases().GetCountTimeSheet() + 1);

    int time_worked = jv.at("ОтработанноеВремя").as_int64();
    if (time_worked <= 0) {
        return SendBadRequestResponse("Ошибка ОтработанноеВремя <= 0"s);
    }
    std::string month;
    month = jv.at("Месяц").as_string();
    if (!(month == "январь" || month == "февраль" || month == "март" || month ==
"апрель" || month == "май" || month == "июнь" || month == "июль" || month ==
"август" || month == "сентябрь" || month == "октябрь" || month == "ноябрь" ||
month == "декабрь")) {
        return SendBadRequestResponse("Ошибка Месяц не существует"s);
    }

    ui::detail::TimeSheetInfo time_sheet = json::value_to<ui::detail::TimeSheetInfo>(jv);

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().AddTimeSheet(time_sheet);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleAddVacation() {
    if (req_info_.method != http::verb::post) {
        return SendWrongMethodResponseAllowedPost("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["НомерЗаписи"] = json::value(application_.GetUseCases().GetCountVacations() + 1);

    int days = jv.at("КоличествоДней").as_int64();
    if (days <= 0) {
        return SendBadRequestResponse("Ошибка КоличествоДней <= 0"s);
    }

    std::string from_date;
    std::string to_date;
    from_date = jv.at("ДатаОтпуска").as_string();
    to_date = jv.at("ДатаОкончания").as_string();
    if (from_date >= to_date) {
        return SendBadRequestResponse("Ошибка ДатаОтпуска >= ДатаОкончания"s);
    }

    ui::detail::VacationInfo vacation = json::value_to<ui::detail::VacationInfo>(jv);

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().AddVacation(vacation);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleGet() {
    std::string path_part = FindAndCutTarget(req_info_);

    if (path_part == "/business-trip"s) {
        HandleGetBusinessTrips();
    }
    else if (path_part == "/composition-business-trip"s) {
        HandleGetCompositionBusinessTrips();
    }
    else if (path_part == "/department"s) {
        HandleGetDepartments();
    }
    else if (path_part == "/employee"s) {
        HandleGetEmployees();
    }
    else if (path_part == "/job-title"s) {
        HandleGetJobTitles();
    }
    else if (path_part == "/order"s) {
        HandleGetOrders();
    }
    else if (path_part == "/staffing-table"s) {
        HandleGetStaffingTable();
    }
    else if (path_part == "/time-sheet"s) {
        HandleGetTimeSheet();
    }
    else if (path_part == "/vacation"s) {
        HandleGetVacations();
    }
    else {
        SendNotFoundResponse();
    }
}

void ApiHandler::HandleGetBusinessTrips() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        return SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetBusinessTrips());
        return SendOkResponse(json::serialize(jv));
    }
    SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetCompositionBusinessTrips() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        return SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetCompositionBusinessTrips());
        return SendOkResponse(json::serialize(jv));
    }
    SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetDepartments() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        return SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetDepartments());
        return SendOkResponse(json::serialize(jv));
    }
    SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetEmployees() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        return SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetEmployees());
        return SendOkResponse(json::serialize(jv));
    }
    SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetJobTitles() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        return SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetJobTitles());
        return SendOkResponse(json::serialize(jv));
    }
    SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetOrders() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        return SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetOrders());
        return SendOkResponse(json::serialize(jv));
    }
    SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetStaffingTable() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        return SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetStaffingTable());
        return SendOkResponse(json::serialize(jv));
    }
    SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetTimeSheet() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        return SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetTimeSheet());
        return SendOkResponse(json::serialize(jv));
    }
    SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetVacations() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        return SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetVacations());
        return SendOkResponse(json::serialize(jv));
    }
    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdate() {
    std::string path_part = FindAndCutTarget(req_info_);

    if (path_part == "/business-trip"s) {
        HandleUpdateBusinessTrip();
    }
    else if (path_part == "/composition-business-trip"s) {
        HandleUpdateCompositionBusinessTrip();
    }
    else if (path_part == "/department"s) {
        HandleUpdateDepartment();
    }
    else if (path_part == "/employee"s) {
        HandleUpdateEmployee();
    }
    else if (path_part == "/job-title"s) {
        HandleUpdateJobTitle();
    }
    else if (path_part == "/order"s) {
        HandleUpdateOrder();
    }
    else if (path_part == "/staffing-table"s) {
        HandleUpdateStaffingTable();
    }
    else if (path_part == "/time-sheet"s) {
        HandleUpdateTimeSheet();
    }
    else if (path_part == "/vacation"s) {
        HandleUpdateVacation();
    }
    else {
        SendNotFoundResponse();
    }
}

void ApiHandler::HandleUpdateBusinessTrip() {
    if (req_info_.method != http::verb::put) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);

    int days = jv.at("КоличествоДней").as_int64();
    if (days <= 0) {
        return SendBadRequestResponse("Ошибка КоличествоДней <= 0"s);
    }

    std::string from_date;
    std::string to_date;
    from_date = jv.at("СДата").as_string();
    to_date = jv.at("ПоДату").as_string();
    if (from_date >= to_date) {
        return SendBadRequestResponse("Ошибка СДата >= ПоДату"s);
    }

    ui::detail::BusinessTripInfo trip = json::value_to<ui::detail::BusinessTripInfo>(jv);
    if (application_.GetUseCases().GetCountBusinessTrips() < trip.trip_id) {
        return SendBadRequestResponse("Ошибка НомерЗаписи нет"s);
    }

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().UpdateBusinessTrip(trip);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateCompositionBusinessTrip() {
    if (req_info_.method != http::verb::put) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);
    ui::detail::CompositionBusinessTripInfo trip = json::value_to<ui::detail::CompositionBusinessTripInfo>(jv);

    if (application_.GetUseCases().GetCountBusinessTrips() < trip.trip_id) {
        return SendBadRequestResponse("Ошибка НомерЗаписи не найден"s);
    }
    if (application_.GetUseCases().GetCountEmployees() < trip.personnel_number) {
        return SendBadRequestResponse("Ошибка ТабельныцНомер не найден"s);
    }

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().UpdateCompositionBusinessTrip(trip);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateDepartment() {
    if (req_info_.method != http::verb::put) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);

    ui::detail::DepartmentInfo dep = json::value_to<ui::detail::DepartmentInfo>(jv);
    if (application_.GetUseCases().GetCountDepartments() < dep.department_id) {
        return SendBadRequestResponse("Ошибка КодОтдела не найден"s);
    }

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().UpdateDepartment(dep);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateEmployee() {
    if (req_info_.method != http::verb::put) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);
    std::string job_title;
    job_title = jv.at("КодДолжности").as_string();
    jv.as_object()["КодДолжности"] = application_.GetUseCases().GetJobTitleId(job_title);
    if (jv.at("КодДолжности").as_int64() == -1) {
        return SendBadRequestResponse("Ошибка Должность не существует"s);
    }

    std::string gender;
    gender = jv.at("Пол").as_string();
    if (!(gender == "м" || gender == "ж")) {
        return SendBadRequestResponse("Ошибка Пол != м или ж"s);
    }

    ui::detail::EmployeeInfo employee = json::value_to<ui::detail::EmployeeInfo>(jv);
    if (application_.GetUseCases().GetCountEmployees() < employee.personnel_number) {
        return SendBadRequestResponse("Ошибка ТабельныйНомер не найден"s);
    }

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().UpdateEmployee(employee);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateJobTitle() {
    if (req_info_.method != http::verb::put) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);

    ui::detail::JobTitleInfo job_title = json::value_to<ui::detail::JobTitleInfo>(jv);
    if (application_.GetUseCases().GetCountJobTitles() < job_title.job_title_id) {
        return SendBadRequestResponse("Ошибка КодДолжности не найден"s);
    }

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().UpdateJobTitle(job_title);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateOrder() {
    if (req_info_.method != http::verb::put) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);

    ui::detail::OrderInfo order = json::value_to<ui::detail::OrderInfo>(jv);
    if (application_.GetUseCases().GetCountOrders() < order.order_id) {
        return SendBadRequestResponse("Ошибка НомерПриказа не найден"s);
    }

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().UpdateOrder(order);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateStaffingTable() {
    if (req_info_.method != http::verb::put) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);
    std::string job_title;
    job_title = jv.at("КодДолжности").as_string();
    jv.as_object()["КодДолжности"] = application_.GetUseCases().GetJobTitleId(job_title);
    if (jv.at("КодДолжности").as_int64() == -1) {
        return SendBadRequestResponse("Ошибка Должность не существует"s);
    }

    std::string dep_name;
    dep_name = jv.at("КодОтдела").as_string();
    jv.as_object()["КодОтдела"] = application_.GetUseCases().GetDepartmentId(dep_name);
    if (jv.at("КодОтдела").as_int64() == -1) {
        return SendBadRequestResponse("Ошибка Отдел не существует"s);
    }

    int time_job = jv.at("КоличествоСтавок").as_int64();
    if (time_job <= 0) {
        return SendBadRequestResponse("Ошибка КоличествоСтавок <= 0"s);
    }

    int salary = jv.at("Оклад").as_int64();
    if (salary <= 0) {
        return SendBadRequestResponse("Ошибка Оклад <= 0"s);
    }

    ui::detail::StaffingTableInfo staffing_table = json::value_to<ui::detail::StaffingTableInfo>(jv);
    if (application_.GetUseCases().GetCountStaffingTable() < staffing_table.staffing_table_id) {
        return SendBadRequestResponse("Ошибка НомерЗаписи не найден"s);
    }

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().UpdateStaffingTable(staffing_table);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateTimeSheet() {
    if (req_info_.method != http::verb::put) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);

    int time_worked = jv.at("ОтработанноеВремя").as_int64();
    if (time_worked <= 0) {
        return SendBadRequestResponse("Ошибка ОтработанноеВремя <= 0"s);
    }
    std::string month;
    month = jv.at("Месяц").as_string();
    if (!(month == "январь" || month == "февраль" || month == "март" || month ==
"апрель" || month == "май" || month == "июнь" || month == "июль" || month ==
"август" || month == "сентябрь" || month == "октябрь" || month == "ноябрь" ||
month == "декабрь")) {
        return SendBadRequestResponse("Ошибка Месяц не существует"s);
    }

    ui::detail::TimeSheetInfo time_sheet = json::value_to<ui::detail::TimeSheetInfo>(jv);
    if (application_.GetUseCases().GetCountTimeSheet() < time_sheet.time_sheet_id) {
        return SendBadRequestResponse("Ошибка НомерЗаписи не найден"s);
    }

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().UpdateTimeSheet(time_sheet);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateVacation() {
    if (req_info_.method != http::verb::put) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    json::value jv = json::parse(req_info_.body);

    int days = jv.at("КоличествоДней").as_int64();
    if (days <= 0) {
        return SendBadRequestResponse("Ошибка КоличествоДней <= 0"s);
    }

    std::string from_date;
    std::string to_date;
    from_date = jv.at("ДатаОтпуска").as_string();
    to_date = jv.at("ДатаОкончания").as_string();
    if (from_date >= to_date) {
        return SendBadRequestResponse("Ошибка ДатаОтпуска >= ДатаОкончания"s);
    }

    ui::detail::VacationInfo vacation = json::value_to<ui::detail::VacationInfo>(jv);
    if (application_.GetUseCases().GetCountVacations() < vacation.vacation_id) {
        return SendBadRequestResponse("Ошибка НомерЗаписи не найден"s);
    }

    try {
        if (CheckEndPath()) {
            application_.GetUseCases().UpdateVacation(vacation);
            return SendOkResponse({});
        }
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

ApiHandler::ResponseInfo ApiHandler::MakeResponse(http::status status, bool no_cache) {
    ResponseInfo result;

    result.status = status;
    result.version = req_info_.version;
    result.content_type = body_type::json;
    result.keep_alive = req_info_.keep_alive;
    result.no_cache = no_cache;
    result.additional_fields.emplace_back(http::field::access_control_allow_origin, "*"s);
    result.additional_fields.emplace_back(http::field::access_control_allow_methods, "GET, POST, PUT, DELETE, OPTIONS"s);
    result.additional_fields.emplace_back(http::field::access_control_allow_headers, "Content-Type, Authorization"s);

    return result;
}

void ApiHandler::SendOkResponse(const std::string& body, bool no_cache) {
    ResponseInfo result = MakeResponse(http::status::ok, no_cache);

    result.body = body;

    send_(result);
}

void ApiHandler::SendBadRequestResponse(std::string message, std::string code, bool no_cache) {
    ResponseInfo result = MakeResponse(http::status::bad_request, no_cache);

    json::value body = {
        {"code"s, code},
        {"message"s, message}
    };

    result.body = json::serialize(body);

    send_(result);
}

void ApiHandler::SendNotFoundResponse(const std::string& message, const std::string& key, bool no_cache) {
    ResponseInfo result = MakeResponse(http::status::not_found, no_cache);

    json::value body {
        {"code"s, key},
        {"message"s, message}
    };

    result.body = json::serialize(body);

    send_(result);
}

void ApiHandler::SendWrongMethodResponseAllowedDelete(const std::string& message, bool no_cache) {
    ResponseInfo result = MakeResponse(http::status::method_not_allowed, no_cache);

    json::value body = {
        {"code"s, "invalidMethod"s},
        {"message"s, message}
    };

    result.body = json::serialize(body);

    result.additional_fields.emplace_back(http::field::allow, "DELETE"s);

    send_(result);
}

void ApiHandler::SendWrongMethodResponseAllowedGetHead(const std::string& message, bool no_cache) {
    ResponseInfo result = MakeResponse(http::status::method_not_allowed, no_cache);

    json::value body = {
        {"code"s, "invalidMethod"s},
        {"message"s, message}
    };

    result.body = json::serialize(body);

    result.additional_fields.emplace_back(http::field::allow, "GET, HEAD"s);

    send_(result);
}

void ApiHandler::SendWrongMethodResponseAllowedPost(const std::string& message, bool no_cache) {
    ResponseInfo result = MakeResponse(http::status::method_not_allowed, no_cache);

    json::value body = {
        {"code"s, "invalidMethod"s},
        {"message"s, message}
    };

    result.body = json::serialize(body);

    result.additional_fields.emplace_back(http::field::allow, "POST"s);

    send_(result);
}

void ApiHandler::SendWrongMethodResponseAllowedPut(const std::string& message, bool no_cache) {
    ResponseInfo result = MakeResponse(http::status::method_not_allowed, no_cache);

    json::value body = {
        {"code"s, "invalidMethod"s},
        {"message"s, message}
    };

    result.body = json::serialize(body);

    result.additional_fields.emplace_back(http::field::allow, "PUT"s);

    send_(result);
}

} // namespace api_handler
