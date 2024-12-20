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

std::string ApiHandler::GetIdFromTarget(const std::string& target) {
    size_t last_slash_pos = target.find_last_of('/');
    if (last_slash_pos == std::string::npos) {
        return ""s;
    }
    return target.substr(last_slash_pos + 1);
}

void ApiHandler::HandleApiResponse() {
    std::string path_part = FindAndCutTarget(req_info_);

    if (path_part == "/add"s) {
        HandleAdd();
    }
    else if (path_part == "/get"s) {
        HandleGet();
    }
    else if (path_part == "/update"s) {
        HandleUpdate();
    }
    else if (path_part == "/delete") {
        HandleDelete();
    }
    else if (path_part == "/register"s) {
        HandleRegister();
    }
    else if (path_part == "/login"s) {
        HandleLogin();
    }
    else if (path_part == "/logout"s) {
        HandleLogout();
    }
    else if (path_part == "/token"s) {
        HandleToken();
    }
    else if (path_part == "/user"s) {
        HandleUser();
    }
    else {
        SendBadRequestResponseDefault();
    }
}

void ApiHandler::HandleOptions() {
    ResponseInfo result = MakeResponse(http::status::ok, true);
    SendOkResponse({});
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

    int personnel_num = jv.at("ТабельныйНомер"s).as_int64();
    std::optional<std::string> date_of_dismissal = application_.GetUseCases().GetDateOfDismissal(personnel_num);

    if (date_of_dismissal.has_value()) {
        return SendBadRequestResponse("Сотрудник уволен"s);
    }

    std::string organization;
    organization = jv.at("НомерЗаписи").as_string();
    jv.as_object()["НомерЗаписи"] = application_.GetUseCases().GetTripId(organization);
    if (jv.at("НомерЗаписи").as_int64() == -1) {
        return SendBadRequestResponse("Ошибка Командировка не существует"s);
    }

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

    int personnel_num = jv.at("ТабельныйНомерРуководителя"s).as_int64();
    std::optional<std::string> date_of_dismissal = application_.GetUseCases().GetDateOfDismissal(personnel_num);

    if (date_of_dismissal.has_value()) {
        return SendBadRequestResponse("Сотрудник уволен"s);
    }

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

    int personnel_num = jv.at("ТабельныйНомер"s).as_int64();
    std::optional<std::string> date_of_dismissal = application_.GetUseCases().GetDateOfDismissal(personnel_num);

    if (date_of_dismissal.has_value()) {
        return SendBadRequestResponse("Сотрудник уволен"s);
    }

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

    int personnel_num = jv.at("ТабельныйНомер"s).as_int64();
    std::optional<std::string> date_of_dismissal = application_.GetUseCases().GetDateOfDismissal(personnel_num);

    if (date_of_dismissal.has_value()) {
        return SendBadRequestResponse("Сотрудник уволен"s);
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

    std::string status;
    status = jv.at("Статус").as_string();

    if (!(status == "принято"s || status == "не принято"s)) {
        return SendBadRequestResponse("Ошибка Статус не корректный"s);
    }

    std::string from_date;
    std::string to_date;
    from_date = jv.at("ДатаОтпуска").as_string();
    to_date = jv.at("ДатаОкончания").as_string();
    if (from_date >= to_date) {
        return SendBadRequestResponse("Ошибка ДатаОтпуска >= ДатаОкончания"s);
    }

    int personnel_num = jv.at("ТабельныйНомер"s).as_int64();
    std::optional<std::string> date_of_dismissal = application_.GetUseCases().GetDateOfDismissal(personnel_num);

    if (date_of_dismissal.has_value()) {
        return SendBadRequestResponse("Сотрудник уволен"s);
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
    else if (path_part == "/free-job-title"s) {
        HandleGetFreeJobTitles();
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
        if (last_role_ == "admin"s) {
            json::value jv = json::value_from(application_.GetUseCases().GetBusinessTrips());
            return SendOkResponse(json::serialize(jv));
        }
        json::value jv = json::value_from(application_.GetUseCases().GetBusinessTripsForPerson(personnel_number_));
        return SendOkResponse(json::serialize(jv));
    }
    SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetCompositionBusinessTrips() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        return SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
    }
    if (CheckEndPath()) {
        if (last_role_ == "admin"s) {
            json::value jv = json::value_from(application_.GetUseCases().GetCompositionBusinessTrips());
            return SendOkResponse(json::serialize(jv));
        }
        json::value jv = json::value_from(application_.GetUseCases().GetCompositionBusinessTripsForPerson(personnel_number_));
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
        if (last_role_ == "admin"s) {
            json::value jv = json::value_from(application_.GetUseCases().GetEmployees());
            return SendOkResponse(json::serialize(jv));
        }
        json::value jv = json::value_from(application_.GetUseCases().GetEmployeeForPerson(personnel_number_));
        return SendOkResponse(json::serialize(jv));
    }
    SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetFreeJobTitles() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        return SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
    }
    if (CheckEndPath()) {
        json::value jv = json::value_from(application_.GetUseCases().GetFreeJobTitles());
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
        if (last_role_ == "admin"s) {
            json::value jv = json::value_from(application_.GetUseCases().GetOrders());
            return SendOkResponse(json::serialize(jv));
        }
        json::value jv = json::value_from(application_.GetUseCases().GetOrdersForPerson(personnel_number_));
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
        if (last_role_ == "admin"s) {
            json::value jv = json::value_from(application_.GetUseCases().GetTimeSheet());
            return SendOkResponse(json::serialize(jv));
        }
        json::value jv = json::value_from(application_.GetUseCases().GetTimeSheetForPerson(personnel_number_));
        return SendOkResponse(json::serialize(jv));
    }
    SendBadRequestResponseDefault();
}

void ApiHandler::HandleGetVacations() {
    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head) {
        return SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
    }
    if (CheckEndPath()) {
        if (last_role_ == "admin"s) {
            json::value jv = json::value_from(application_.GetUseCases().GetVacations());
            return SendOkResponse(json::serialize(jv));
        }
        json::value jv = json::value_from(application_.GetUseCases().GetVacationForPerson(personnel_number_));
        return SendOkResponse(json::serialize(jv));
    }
    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdate() {
    std::string path_part = FindAndCutTarget(req_info_);

    std::string target = req_info_.target;
    if (GetIdFromTarget(target).empty()) {
        return SendBadRequestResponseDefault();
    }

    int id = std::stoi(GetIdFromTarget(target).c_str());

    if (path_part == "/business-trip"s) {
        HandleUpdateBusinessTrip(id);
    }
    else if (path_part == "/composition-business-trip"s) {
        HandleUpdateCompositionBusinessTrip(id);
    }
    else if (path_part == "/department"s) {
        HandleUpdateDepartment(id);
    }
    else if (path_part == "/employee"s) {
        HandleUpdateEmployee(id);
    }
    else if (path_part == "/job-title"s) {
        HandleUpdateJobTitle(id);
    }
    else if (path_part == "/order"s) {
        HandleUpdateOrder(id);
    }
    else if (path_part == "/staffing-table"s) {
        HandleUpdateStaffingTable(id);
    }
    else if (path_part == "/time-sheet"s) {
        HandleUpdateTimeSheet(id);
    }
    else if (path_part == "/vacation"s) {
        HandleUpdateVacation(id);
    }
    else {
        SendNotFoundResponse();
    }
}

void ApiHandler::HandleUpdateBusinessTrip(int id) {
    if (req_info_.method != http::verb::put && req_info_.method != http::verb::options) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    if (req_info_.method == http::verb::options) {
        return HandleOptions();
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["НомерЗаписи"] = id;

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
    if (application_.GetUseCases().GetCountBusinessTrips() < id) {
        return SendBadRequestResponse("Ошибка НомерЗаписи нет"s);
    }

    try {
        application_.GetUseCases().UpdateBusinessTrip(trip, id);
        return SendOkResponse({});
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateCompositionBusinessTrip(int id) {
    if (req_info_.method != http::verb::put && req_info_.method != http::verb::options) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    if (req_info_.method == http::verb::options) {
        return HandleOptions();
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["ТабельныйНомер"] = id;

    std::string organization;
    organization = jv.at("НомерЗаписи").as_string();
    jv.as_object()["НомерЗаписи"] = application_.GetUseCases().GetTripId(organization);
    if (jv.at("НомерЗаписи").as_int64() == -1) {
        return SendBadRequestResponse("Ошибка Командировка не существует"s);
    }

    ui::detail::CompositionBusinessTripInfo trip = json::value_to<ui::detail::CompositionBusinessTripInfo>(jv);

    if (application_.GetUseCases().GetCountBusinessTrips() < get<int>(trip.trip)) {
        return SendBadRequestResponse("Ошибка НомерЗаписи не найден"s);
    }
    if (application_.GetUseCases().GetCountEmployees() < id) {
        return SendBadRequestResponse("Ошибка ТабельныцНомер не найден"s);
    }

    int trip_id = jv.at("НомерЗаписи"s).as_int64();
    int personnel_num = jv.at("ТабельныйНомер"s).as_int64();
    std::string start_date_of_business_trip = application_.GetUseCases().GetStartDateOfBusinessTrip(trip_id);
    std::optional<std::string> date_of_dismissal = application_.GetUseCases().GetDateOfDismissal(personnel_num);

    if (date_of_dismissal >= start_date_of_business_trip) {
        return SendBadRequestResponse("Сотрудник уволен"s);
    }

    try {
        application_.GetUseCases().UpdateCompositionBusinessTrip(trip, id);
        return SendOkResponse({});
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateDepartment(int id) {
    if (req_info_.method != http::verb::put && req_info_.method != http::verb::options) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    if (req_info_.method == http::verb::options) {
        return HandleOptions();
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["КодОтдела"] = id;

    ui::detail::DepartmentInfo dep = json::value_to<ui::detail::DepartmentInfo>(jv);
    if (application_.GetUseCases().GetCountDepartments() < id) {
        return SendBadRequestResponse("Ошибка КодОтдела не найден"s);
    }

    try {
        application_.GetUseCases().UpdateDepartment(dep, id);
        return SendOkResponse({});
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateEmployee(int id) {
    if (req_info_.method != http::verb::put && req_info_.method != http::verb::options) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    if (req_info_.method == http::verb::options) {
        return HandleOptions();
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["ТабельныйНомер"] = id;

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
    if (application_.GetUseCases().GetCountEmployees() < id) {
        return SendBadRequestResponse("Ошибка ТабельныйНомер не найден"s);
    }

    try {
        application_.GetUseCases().UpdateEmployee(employee, id);
        return SendOkResponse({});
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateJobTitle(int id) {
    if (req_info_.method != http::verb::put && req_info_.method != http::verb::options) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    if (req_info_.method == http::verb::options) {
        return HandleOptions();
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["КодДолжности"] = id;

    ui::detail::JobTitleInfo job_title = json::value_to<ui::detail::JobTitleInfo>(jv);
    if (application_.GetUseCases().GetCountJobTitles() < id) {
        return SendBadRequestResponse("Ошибка КодДолжности не найден"s);
    }

    try {
        application_.GetUseCases().UpdateJobTitle(job_title, id);
        return SendOkResponse({});
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateOrder(int id) {
    if (req_info_.method != http::verb::put && req_info_.method != http::verb::options) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    if (req_info_.method == http::verb::options) {
        return HandleOptions();
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["НомерПриказа"] = id;

    int personnel_num = jv.at("ТабельныйНомер"s).as_int64();
    std::optional<std::string> date_of_dismissal = application_.GetUseCases().GetDateOfDismissal(personnel_num);

    if (date_of_dismissal.has_value()) {
        return SendBadRequestResponse("Сотрудник уволен"s);
    }

    ui::detail::OrderInfo order = json::value_to<ui::detail::OrderInfo>(jv);
    if (application_.GetUseCases().GetCountOrders() < id) {
        return SendBadRequestResponse("Ошибка НомерПриказа не найден"s);
    }

    try {
        application_.GetUseCases().UpdateOrder(order, id);
        return SendOkResponse({});
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateStaffingTable(int id) {
    if (req_info_.method != http::verb::put && req_info_.method != http::verb::options) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    if (req_info_.method == http::verb::options) {
        return HandleOptions();
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["НомерЗаписи"] = id;

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
    if (application_.GetUseCases().GetCountStaffingTable() < id) {
        return SendBadRequestResponse("Ошибка НомерЗаписи не найден"s);
    }

    try {
        application_.GetUseCases().UpdateStaffingTable(staffing_table, id);
        return SendOkResponse({});
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateTimeSheet(int id) {
    if (req_info_.method != http::verb::put && req_info_.method != http::verb::options) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    if (req_info_.method == http::verb::options) {
        return HandleOptions();
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["НомерЗаписи"] = id;

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

    int personnel_num = jv.at("ТабельныйНомер"s).as_int64();
    std::optional<std::string> date_of_dismissal = application_.GetUseCases().GetDateOfDismissal(personnel_num);

    if (date_of_dismissal.has_value()) {
        return SendBadRequestResponse("Сотрудник уволен"s);
    }

    ui::detail::TimeSheetInfo time_sheet = json::value_to<ui::detail::TimeSheetInfo>(jv);
    if (application_.GetUseCases().GetCountTimeSheet() < id) {
        return SendBadRequestResponse("Ошибка НомерЗаписи не найден"s);
    }

    try {
        application_.GetUseCases().UpdateTimeSheet(time_sheet, id);
        return SendOkResponse({});
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUpdateVacation(int id) {
    if (req_info_.method != http::verb::put && req_info_.method != http::verb::options) {
        return SendWrongMethodResponseAllowedPut("Wrong method"s, true);
    }

    if (req_info_.method == http::verb::options) {
        return HandleOptions();
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["НомерЗаписи"] = id;

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

    std::string status;
    status = jv.at("Статус").as_string();

    if (!(status == "принято"s || status == "не принято"s)) {
        return SendBadRequestResponse("Ошибка Статус не корректный"s);
    }

    ui::detail::VacationInfo vacation = json::value_to<ui::detail::VacationInfo>(jv);
    if (application_.GetUseCases().GetCountVacations() < id) {
        return SendBadRequestResponse("Ошибка НомерЗаписи не найден"s);
    }

    try {
        application_.GetUseCases().UpdateVacation(vacation, id);
        return SendOkResponse({});
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleDelete() {
    std::string path_part = FindAndCutTarget(req_info_);

    std::string target = req_info_.target;
    if (GetIdFromTarget(target).empty()) {
        return SendBadRequestResponseDefault();
    }

    int id = std::stoi(GetIdFromTarget(target).c_str());

    if (path_part == "/composition-business-trip"s) {
        HandleDeleteCompositionBusinessTrip(id);
    }
    else if (path_part == "/vacation"s) {
        HandleDeleteVacation(id);
    }
    else {
        SendNotFoundResponse();
    }
}

void ApiHandler::HandleDeleteCompositionBusinessTrip(int id) {
    if (req_info_.method != http::verb::delete_ && req_info_.method != http::verb::options) {
        return SendWrongMethodResponseAllowedDelete("Wrong method"s, true);
    }

    if (req_info_.method == http::verb::options) {
        return HandleOptions();
    }

    json::value jv = json::parse(req_info_.body);

    std::string organization;
    organization = jv.at("НомерЗаписи").as_string();
    jv.as_object()["НомерЗаписи"] = application_.GetUseCases().GetTripId(organization);
    jv.as_object()["ТабельныйНомер"] = id;

    ui::detail::CompositionBusinessTripInfo trip = json::value_to<ui::detail::CompositionBusinessTripInfo>(jv);

    if (application_.GetUseCases().GetCountEmployees() < id) {
        return SendBadRequestResponse("Ошибка ТабельныйНомер не найден"s);
    }

    try {
        application_.GetUseCases().DeleteCompositionBusinessTrip(trip, id);
        return SendOkResponse({});
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleDeleteVacation(int id) {
    if (req_info_.method != http::verb::delete_ && req_info_.method != http::verb::options) {
        return SendWrongMethodResponseAllowedDelete("Wrong method"s, true);
    }

    if (req_info_.method == http::verb::options) {
        return HandleOptions();
    }

    json::value jv = json::parse(req_info_.body);
    jv.as_object()["НомерЗаписи"] = id;

    std::string status;
    status = jv.at("Статус").as_string();

    if (status != "не принято"s) {
        return SendBadRequestResponse("Ошибка Статус не корректный"s);
    }

    ui::detail::VacationInfo vacation = json::value_to<ui::detail::VacationInfo>(jv);

    if (application_.GetUseCases().GetCountVacations() < id) {
        return SendBadRequestResponse("Ошибка НомерЗаписи не найден"s);
    }

    try {
        application_.GetUseCases().DeleteVacation(vacation, id);
        return SendOkResponse({});
    }
    catch (const std::exception& e) {
        return SendBadRequestResponse(CleanErrorMessage(e.what()));
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleRegister() {
    if (req_info_.method != http::verb::post) {
        return SendWrongMethodResponseAllowedPost("Wrong method"s, true);
    }

    json::value person = json::parse(req_info_.body);

    if (!person.as_object().contains("email"s) || !person.as_object().contains("password"s) || !person.as_object().contains("name"s)) {
        return SendBadRequestResponse("Invalid register format"s, "invalidRegister"s);
    }

    std::string email;
    std::string password;
    std::string name;
    std::string role = "employee"s;

    email = person.at("email").as_string();
    password = person.at("password").as_string();
    name = person.at("name").as_string();
    last_role_ = role;

    Person p{email, password, role};
    PersonInfo p_info{email, password, name, role};
    Login login{email, password};

    std::unordered_set<std::string> emails = application_.GetUseCases().GetEmails();

    if (!emails.contains(email)) {
        return SendBadRequestResponse("Сотрудник не найден"s);
    }

    personnel_number_ = application_.GetUseCases().GetPersonnelNumberForEmail(email);
    std::optional<std::string> date_of_dismissal = application_.GetUseCases().GetDateOfDismissal(personnel_number_);

    if (date_of_dismissal.has_value()) {
        return SendBadRequestResponse("Сотрудник уволен"s);
    }

    if (emails_.contains(email)) {
        return SendBadRequestResponse("Сотрудник уже зарегистрирован"s);
    }
    else {
        emails_.insert(email);
    }

    std::string access_token = GetUniqueToken();
    std::string refresh_token = GetUniqueToken();

    login_to_role_[{email, password}] = role;
    persons_.insert({p, name});
    tokens_[p_info] = {access_token, refresh_token, TimeTracker{}};
    auth_to_person_[access_token] = p_info;

    json::value jv {
        {"success"s, true},
        {"user"s, {
                {"email"s, email},
                {"name"s, name},
                {"role"s, role}
            }},
        {"accessToken"s, "Bearer "s + access_token},
        {"refreshToken"s, refresh_token}
    };

    refresh_tokens_.push_back(refresh_token);
    refresh_token_to_person_[refresh_token] = p_info;

    SendOkResponse(json::serialize(jv));
}

PersonInfo ApiHandler::CreateAdmin() {
    Person admin{"admin@work.com"s, "Admin1Admin"s, "admin"s};
    persons_.insert({admin, "Admin"s});

    PersonInfo p_info{admin.email, admin.password, persons_[admin], admin.role};

    std::string access_token = GetUniqueToken();
    std::string refresh_token = GetUniqueToken();

    tokens_[p_info] = {access_token, refresh_token, TimeTracker{}};
    auth_to_person_[access_token] = p_info;
    refresh_tokens_.push_back(refresh_token);
    refresh_token_to_person_[refresh_token] = p_info;
    last_role_ = admin.role;

    return p_info;
}

void ApiHandler::HandleLogin() {
    if (req_info_.method != http::verb::post) {
        return SendWrongMethodResponseAllowedPost("Wrong method"s, true);
    }

    json::value person = json::parse(req_info_.body);

    if (!person.as_object().contains("email"s) || !person.as_object().contains("password"s)) {
        return SendNoAuthResponse("Invalid login format"s, "invalidLogin"s);
    }

    if (person.at("email").as_string() == "admin@work.com"s && person.at("password").as_string() == "Admin1Admin"s) {
        PersonInfo p_info = CreateAdmin();
        json::value jv {
            {"success"s, true},
            {"accessToken"s, "Bearer "s + tokens_[p_info].access_token},
            {"refreshToken"s, tokens_[p_info].refresh_token},
            {"user"s, {
                    {"email"s, p_info.email},
                    {"name"s, p_info.name},
                    {"role"s, p_info.role}
                }}
        };
        return SendOkResponse(json::serialize(jv));
    }

    std::string email;
    std::string password;
    std::string role;

    email = person.at("email").as_string();
    password = person.at("password").as_string();

    try {
        role = login_to_role_.at({email, password});
    }
    catch (...) {
        return SendNoAuthResponse("Invalid login format"s, "invalidLogin"s);
    }

    personnel_number_ = application_.GetUseCases().GetPersonnelNumberForEmail(email);

    Person p{email, password, role};
    last_role_ = role;

    if (persons_.contains(p)) {
        PersonInfo p_info{email, password, persons_[p], role};
        if (tokens_.contains(p_info)) {
            refresh_tokens_.push_back(tokens_[p_info].refresh_token);
            json::value jv {
                {"success"s, true},
                {"accessToken"s, "Bearer "s + tokens_[p_info].access_token},
                {"refreshToken"s, tokens_[p_info].refresh_token},
                {"user"s, {
                        {"email"s, p_info.email},
                        {"name"s, p_info.name},
                        {"role"s, p_info.role}
                    }}
            };
            return SendOkResponse(json::serialize(jv));
        }
    }

    SendNoAuthResponse("Invalid login format"s, "invalidLogin"s);
}

void ApiHandler::HandleLogout() {
    if (req_info_.method != http::verb::post) {
        return SendWrongMethodResponseAllowedPost("Wrong method"s, true);
    }

    json::value token = json::parse(req_info_.body);

    if (!token.as_object().contains("token")) {
        return SendBadRequestResponse("Invalid token"s, "invalidToken"s);
    }

    std::string tok;
    tok = token.at("token").as_string();

    if (refresh_tokens_.empty()) {
        return SendBadRequestResponse("Invalid token"s, "invalidToken"s);
    }

    if (refresh_tokens_.back() == tok) {
        json::value jv {
            {"success"s, true},
            {"message"s, "Successful logout"s}
        };
        return SendOkResponse(json::serialize(jv));
    }
    else {
        return SendBadRequestResponse("Invalid logout"s, "invalidLogout"s);
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleToken() {
    if (req_info_.method != http::verb::post && req_info_.method != http::verb::options) {
        return SendWrongMethodResponseAllowedPost("Wrong method"s, true);
    }

    if (req_info_.method == http::verb::options) {
        return HandleOptions();
    }

    json::value token = json::parse(req_info_.body);

    if (!token.as_object().contains("token")) {
        return SendBadRequestResponse("Invalid token"s, "invalidToken"s);
    }

    std::string tok;
    tok = token.at("token").as_string();

    try {
        PersonInfo p_info = refresh_token_to_person_.at(tok);
        std::string access_token = GetUniqueToken();
        std::string refresh_token = GetUniqueToken();
        json::value jv {
            {"success"s, true},
            {"accessToken"s, "Bearer "s + access_token},
            {"refreshToken"s, refresh_token}
        };

        tokens_[p_info].access_token = access_token;
        tokens_[p_info].refresh_token = refresh_token;
        tokens_[p_info].tracker.reset_timer();
        auth_to_person_[access_token] = p_info;
        refresh_token_to_person_[refresh_token] = p_info;
        refresh_tokens_.push_back(refresh_token);

        return SendOkResponse(json::serialize(jv));
    }
    catch (...) {
        return SendBadRequestResponse("Invalid token"s, "invalidToken"s);
    }

    SendBadRequestResponseDefault();
}

void ApiHandler::HandleUser() {
    static size_t token_size = 32;

    if (req_info_.method != http::verb::get && req_info_.method != http::verb::head && req_info_.method != http::verb::options) {
        return SendWrongMethodResponseAllowedGetHead("Wrong method"s, true);
    }

    if (req_info_.method == http::verb::options) {
        return HandleOptions();
    }

    if (req_info_.auth.empty()) {
        return SendNoAuthResponse("Invalid token"s, "invalidToken"s);
    }

    std::string token_str{req_info_.auth};

    try {
        std::string email = auth_to_person_.at(token_str.substr(7)).email;
        std::string password = auth_to_person_.at(token_str.substr(7)).password;
        std::string name = auth_to_person_.at(token_str.substr(7)).name;
        std::string role = auth_to_person_.at(token_str.substr(7)).role;
        Person p{email, password, role};
        PersonInfo p_info{email, password, persons_[p], role};
        if (!tokens_[p_info].tracker.Has20MinutesPassed()) {
            json::value jv = {
                {"success"s, true},
                {"user"s, {
                        {"email"s, email},
                        {"name"s, name},
                        {"role"s, role}
                    }}
            };
            return SendOkResponse(json::serialize(jv));
        }
        else {
            return SendBadRequestResponse("Token is expired"s, "tokenIsExpired"s);
        }
    }
    catch (...) {
        return SendBadRequestResponse("Invalid token"s, "invalidToken"s);
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

void ApiHandler::SendNoAuthResponse(const std::string& message, const std::string& key, bool no_cache) {
    ResponseInfo result = MakeResponse(http::status::unauthorized, no_cache);

    json::value body = {
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
