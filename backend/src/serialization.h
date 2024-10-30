#pragma once

#include "ui/view.h"

#include <boost/json.hpp>

namespace {
using namespace ui::detail;
namespace json = boost::json;

void tag_invoke(json::value_from_tag, json::value& jv,
                const BusinessTripInfo& trip);

void tag_invoke(json::value_from_tag, json::value& jv,
                const CompositionBusinessTripInfo& trip);

void tag_invoke(json::value_from_tag, json::value& jv,
                const DepartmentInfo& department);

void tag_invoke(json::value_from_tag, json::value& jv,
                const EmployeeInfo& employee);

void tag_invoke(json::value_from_tag, json::value& jv,
                const JobTitleInfo& job_title);

void tag_invoke(json::value_from_tag, json::value& jv, const OrderInfo& order);

void tag_invoke(json::value_from_tag, json::value& jv,
                const StaffingTableInfo& staffing_table);

void tag_invoke(json::value_from_tag, json::value& jv,
                const TimeSheetInfo& time_sheet);

void tag_invoke(json::value_from_tag, json::value& jv,
                const VacationInfo& vacation);


BusinessTripInfo tag_invoke(json::value_to_tag<BusinessTripInfo>&,
                            const json::value& trip);

CompositionBusinessTripInfo tag_invoke(json::value_to_tag<CompositionBusinessTripInfo>&,
                                       const json::value& trip);

DepartmentInfo tag_invoke(json::value_to_tag<DepartmentInfo>&,
                          const json::value& department);

EmployeeInfo tag_invoke(json::value_to_tag<EmployeeInfo>&,
                        const json::value& employee);

JobTitleInfo tag_invoke(json::value_to_tag<JobTitleInfo>&,
                        const json::value& job_title);

OrderInfo tag_invoke(json::value_to_tag<OrderInfo>&,
                     const json::value& order);

StaffingTableInfo tag_invoke(json::value_to_tag<StaffingTableInfo>&,
                             const json::value& staffing_table);

TimeSheetInfo tag_invoke(json::value_to_tag<TimeSheetInfo>&,
                         const json::value& time_sheet);

VacationInfo tag_invoke(json::value_to_tag<VacationInfo>&,
                        const json::value& vacation);

} // namespace
