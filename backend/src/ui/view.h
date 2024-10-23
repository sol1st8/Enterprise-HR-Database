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
    int id;
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
    int id;
    int manager_personal_num;
    std::string dep_name;
    int office_num;

    bool operator==(const DepartmentInfo&) const = default;
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
} // namespace detail

} // namespace ui
