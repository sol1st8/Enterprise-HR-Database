#pragma once

#include <chrono>
#include <iomanip>
#include <iosfwd>
#include <optional>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>

namespace app {
class UseCases;
} // namespace app

namespace ui {

namespace detail {

struct BusinessTripInfo {
    int trip_id;
    std::string city;
    std::string organization;
    std::string from_date;
    std::string to_date;
    int days;
    std::string target;
    std::string country = "Россия";

    bool operator==(const BusinessTripInfo&) const = default;
};

struct CompositionBusinessTripInfo {
    int personnel_number;
    int trip_id;

    bool operator==(const CompositionBusinessTripInfo&) const = default;
};

struct DepartmentInfo {
    int department_id;
    int manager_personnel_number;
    std::string dep_name;
    int office_num;

    bool operator==(const DepartmentInfo&) const = default;
};

struct EmployeeInfo {
    int personnel_number;
    std::string full_name;
    int job_title_id;
    std::optional<int> stage;
    std::string number;
    std::string registration;
    std::string education;
    std::string mail;
    std::string gender = "м";
    std::string marital_status = "холост";
    std::string date;

    bool operator==(const EmployeeInfo&) const = default;
};

struct JobTitleInfo {
    int job_title_id;
    std::string job_title;

    bool operator==(const JobTitleInfo&) const = default;
};

struct OrderInfo {
    int order_id;
    int personnel_number;
    std::string content;
    std::string date;

    bool operator==(const OrderInfo&) const = default;
};

struct StaffingTableInfo {
    int staffing_table_id;
    int job_title_id;
    int department_id;
    int salary;
    int time_job = 1;

    bool operator==(const StaffingTableInfo&) const = default;
};

struct TimeSheetInfo {
    int time_sheet_id;
    int personnel_number;
    int time_worked;
    std::string month;

    bool operator==(const TimeSheetInfo&) const = default;
};

struct VacationInfo {
    int vacation_id;
    int personnel_number;
    std::string type;
    std::string from_date;
    std::string to_date;
    int days;
    std::string leave_basis;

    bool operator==(const VacationInfo&) const = default;
};

} // namespace detail

} // namespace ui
