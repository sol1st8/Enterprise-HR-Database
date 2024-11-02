#include "api_handler.h"
#include <algorithm>
#include <string>

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
    /*
    else if (path_part == "/update") {
        HandleUpdate();
    }
    else if (path_part == "/delete") {
        HandleDelete();
    }
    */
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
        SendWrongMethodResponseAllowedPost("Wrong method"s, true);
        return;
    }

    json::value jv = json::parse(req_info_.body);

    int days = jv.at("КоличествоДней").as_int64();
    if (days <= 0) {
        SendBadRequestResponse("Ошибка КоличествоДней <= 0"s);
        return;
    }
    std::string from_date;
    std::string to_date;
    from_date = jv.at("СДата").as_string();
    to_date = jv.at("ПоДату").as_string();
    if (from_date >= to_date) {
        SendBadRequestResponse("Ошибка СДата >= ПоДату"s);
        return;
    }

    ui::detail::BusinessTripInfo trip = json::value_to<ui::detail::BusinessTripInfo>(jv);
    if (application_.GetUseCases().GetCountBusinessTrips() + 1 !=
trip.trip_id) { SendBadRequestResponse("Ошибка НомерЗаписи = НомерЗаписи + 1"s);
        return;
    }

    try {
        application_.GetUseCases().AddBusinessTrip(trip);
    }
    catch (const std::exception& e) {
        SendBadRequestResponse(CleanErrorMessage(e.what()));
        return;
    }

    SendOkResponse({});
}

void ApiHandler::HandleAddCompositionBusinessTrip() {
    if (req_info_.method != http::verb::post) {
        SendWrongMethodResponseAllowedPost("Wrong method"s, true);
        return;
    }

    json::value jv = json::parse(req_info_.body);
    ui::detail::CompositionBusinessTripInfo trip = json::value_to<ui::detail::CompositionBusinessTripInfo>(jv);

    try {
        application_.GetUseCases().AddCompositionBusinessTrip(trip);
    }
    catch (const std::exception& e) {
        SendBadRequestResponse(CleanErrorMessage(e.what()));
        return;
    }

    SendOkResponse({});
}

void ApiHandler::HandleAddDepartment() {
    if (req_info_.method != http::verb::post) {
        SendWrongMethodResponseAllowedPost("Wrong method"s, true);
        return;
    }

    json::value jv = json::parse(req_info_.body);

    ui::detail::DepartmentInfo dep = json::value_to<ui::detail::DepartmentInfo>(jv);
    if (application_.GetUseCases().GetCountDepartments() + 1 != dep.department_id) {
        SendBadRequestResponse("Ошибка КодОтдела != КодОтдела + 1"s);
        return;
    }

    try {
        application_.GetUseCases().AddDepartment(dep);
    }
    catch (const std::exception& e) {
        SendBadRequestResponse(CleanErrorMessage(e.what()));
        return;
    }

    SendOkResponse({});
}

void ApiHandler::HandleAddEmployee() {
    if (req_info_.method != http::verb::post) {
        SendWrongMethodResponseAllowedPost("Wrong method"s, true);
        return;
    }

    json::value jv = json::parse(req_info_.body);

    std::string gender;
    gender = jv.at("Пол").as_string();
    if (!(gender == "м" || gender == "ж")) {
        SendBadRequestResponse("Ошибка Пол = м или ж"s);
        return;
    }

    ui::detail::EmployeeInfo employee = json::value_to<ui::detail::EmployeeInfo>(jv);
    if (application_.GetUseCases().GetCountEmployees() + 1 != employee.personnel_number) {
        SendBadRequestResponse("Ошибка ТабельныйНомер != ТабельныйНомер + 1"s);
        return;
    }

    try {
        application_.GetUseCases().AddEmployee(employee);
    }
    catch (const std::exception& e) {
        SendBadRequestResponse(CleanErrorMessage(e.what()));
        return;
    }

    SendOkResponse({});
}

void ApiHandler::HandleAddJobTitle() {
    if (req_info_.method != http::verb::post) {
        SendWrongMethodResponseAllowedPost("Wrong method"s, true);
        return;
    }

    json::value jv = json::parse(req_info_.body);

    ui::detail::JobTitleInfo job_title = json::value_to<ui::detail::JobTitleInfo>(jv);
    if (application_.GetUseCases().GetCountJobTitles() + 1 != job_title.job_title_id) {
        SendBadRequestResponse("Ошибка КодДолжности != КодДолжности + 1"s);
        return;
    }

    try {
        application_.GetUseCases().AddJobTitle(job_title);
    }
    catch (const std::exception& e) {
        SendBadRequestResponse(CleanErrorMessage(e.what()));
        return;
    }

    SendOkResponse({});
}

void ApiHandler::HandleAddOrder() {
    if (req_info_.method != http::verb::post) {
        SendWrongMethodResponseAllowedPost("Wrong method"s, true);
        return;
    }

    json::value jv = json::parse(req_info_.body);

    ui::detail::OrderInfo order = json::value_to<ui::detail::OrderInfo>(jv);
    if (application_.GetUseCases().GetCountOrders() + 1 != order.order_id) {
        SendBadRequestResponse("Ошибка НомерПриказа != НомерПриказа + 1"s);
        return;
    }

    try {
        application_.GetUseCases().AddOrder(order);
    }
    catch (const std::exception& e) {
        SendBadRequestResponse(CleanErrorMessage(e.what()));
        return;
    }

    SendOkResponse({});
}

void ApiHandler::HandleAddStaffingTable() {
    if (req_info_.method != http::verb::post) {
        SendWrongMethodResponseAllowedPost("Wrong method"s, true);
        return;
    }

    json::value jv = json::parse(req_info_.body);

    int time_job = jv.at("КоличествоСтавок").as_int64();
    if (time_job <= 0) {
        SendBadRequestResponse("Ошибка КоличествоСтавок <= 0"s);
        return;
    }
    int salary = jv.at("Оклад").as_int64();
    if (salary <= 0) {
        SendBadRequestResponse("Ошибка Оклад <= 0"s);
        return;
    }

    ui::detail::StaffingTableInfo staffing_table = json::value_to<ui::detail::StaffingTableInfo>(jv);
    if (application_.GetUseCases().GetCountStaffingTable() + 1 != staffing_table.staffing_table_id) {
        SendBadRequestResponse("Ошибка НомерЗаписи != НомерЗаписи + 1"s);
        return;
    }

    try {
        application_.GetUseCases().AddStaffingTable(staffing_table);
    }
    catch (const std::exception& e) {
        SendBadRequestResponse(CleanErrorMessage(e.what()));
        return;
    }

    SendOkResponse({});
}

void ApiHandler::HandleAddTimeSheet() {
    if (req_info_.method != http::verb::post) {
        SendWrongMethodResponseAllowedPost("Wrong method"s, true);
        return;
    }

    json::value jv = json::parse(req_info_.body);

    int time_worked = jv.at("ОтработанноеВремя").as_int64();
    if (time_worked <= 0) {
        SendBadRequestResponse("Ошибка ОтработанноеВремя <= 0"s);
        return;
    }
    std::string month;
    month = jv.at("Месяц").as_string();
    if (!(month == "январь" || month == "февраль" || month == "март" || month ==
"апрель" || month == "май" || month == "июнь" || month == "июль" || month ==
"август" || month == "сентябрь" || month == "октябрь" || month == "ноябрь" ||
month == "декабрь")) { SendBadRequestResponse("Ошибка Месяц не существует"s);
        return;
    }

    ui::detail::TimeSheetInfo time_sheet = json::value_to<ui::detail::TimeSheetInfo>(jv);
    if (application_.GetUseCases().GetCountTimeSheet() + 1 != time_sheet.time_sheet_id) {
        SendBadRequestResponse("Ошибка НомерЗаписи != НомерЗаписи + 1"s);
        return;
    }

    try {
        application_.GetUseCases().AddTimeSheet(time_sheet);
    }
    catch (const std::exception& e) {
        SendBadRequestResponse(CleanErrorMessage(e.what()));
        return;
    }

    SendOkResponse({});
}

void ApiHandler::HandleAddVacation() {
    if (req_info_.method != http::verb::post) {
        SendWrongMethodResponseAllowedPost("Wrong method"s, true);
        return;
    }

    json::value jv = json::parse(req_info_.body);

    int days = jv.at("КоличествоДней").as_int64();
    if (days <= 0) {
        SendBadRequestResponse("Ошибка КоличествоДней <= 0"s);
        return;
    }
    std::string from_date;
    std::string to_date;
    from_date = jv.at("ДатаОтпуска").as_string();
    to_date = jv.at("ДатаОкончания").as_string();
    if (from_date >= to_date) {
        SendBadRequestResponse("Ошибка ДатаОтпуска >= ДатаОкончания"s);
        return;
    }

    ui::detail::VacationInfo vacation = json::value_to<ui::detail::VacationInfo>(jv);
    if (application_.GetUseCases().GetCountVacations() + 1 != vacation.vacation_id) {
        SendBadRequestResponse("Ошибка НомерЗаписи != НомерЗаписи + 1"s);
        return;
    }

    try {
        application_.GetUseCases().AddVacation(vacation);
    }
    catch (const std::exception& e) {
        SendBadRequestResponse(CleanErrorMessage(e.what()));
        return;
    }

    SendOkResponse({});
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
        SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
        return;
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetBusinessTrips());
        SendOkResponse(json::serialize(jv));
        return;
    }
    return SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetCompositionBusinessTrips() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
        return;
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetCompositionBusinessTrips());
        SendOkResponse(json::serialize(jv));
        return;
    }
    return SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetDepartments() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
        return;
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetDepartments());
        SendOkResponse(json::serialize(jv));
        return;
    }
    return SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetEmployees() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
        return;
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetEmployees());
        SendOkResponse(json::serialize(jv));
        return;
    }
    return SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetJobTitles() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
        return;
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetJobTitles());
        SendOkResponse(json::serialize(jv));
        return;
    }
    return SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetOrders() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
        return;
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetOrders());
        SendOkResponse(json::serialize(jv));
        return;
    }
    return SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetStaffingTable() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
        return;
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetStaffingTable());
        SendOkResponse(json::serialize(jv));
    }
    return SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetTimeSheet() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
        return;
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetTimeSheet());
        SendOkResponse(json::serialize(jv));
    }
    return SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetVacations() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
        return;
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetVacations());
        SendOkResponse(json::serialize(jv));
    }
    return SendBadRequestResponseDefault();
}

ApiHandler::ResponseInfo ApiHandler::MakeResponse(http::status status, bool no_cache) {
    ResponseInfo result;

    result.status = status;
    result.version = req_info_.version;
    result.content_type = body_type::json;
    result.keep_alive = req_info_.keep_alive;
    result.no_cache = no_cache;

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
