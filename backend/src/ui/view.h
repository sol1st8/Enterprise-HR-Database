#pragma once

#include <iosfwd>
#include <optional>
#include <string>
#include <vector>

namespace app {
class UseCases;
} // namespace app

namespace ui {

namespace detail {

struct JobTitleInfo {
    int job_title_id;
    std::string job_title;

    bool operator==(const JobTitleInfo&) const = default;
};
/*
struct BusinessTrip {
    std::string id;
    std::string country;
    std::string city;
    std::string organization;
    std::string from_date;
    std::string to_date;
    int days;
    std::string target;

    bool operator==(const BusinessTrip&) const = default;
};
*/
struct DepartmentInfo {
    int department_id;
    int manager_personnel_number;
    std::string dep_name;
    int office_num;

    bool operator==(const DepartmentInfo&) const = default;
};
struct TimeSheetInfo {
    int time_sheet_id;
    int personnel_number;
    int time_worked;
    std::string month;

    bool operator==(const TimeSheetInfo&) const = default;
};
/*
struct Vacation {
    std::string id;
    int personal_num;
    std::string type;
    std::string organization;
    std::string from_date;
    std::string to_date;
    int days;
    std::string leave_basis;

    bool operator==(const Vacation&) const = default;
};
*/
struct StaffingTableInfo {
    int staffing_table_id;
    int job_title_id;
    int department_id;
    int salary;
    int time_job = 1;
};
} // namespace detail

} // namespace ui
