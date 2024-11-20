#pragma once

#include "business_trip.h"
#include "composition_business_trip.h"
#include "department.h"
#include "employee.h"
#include "job_title.h"
#include "order.h"
#include "staffing_table.h"
#include "time_sheet.h"
#include "vacation.h"
#include "../ui/view.h"

namespace domain {

class Worker {
  public:
    virtual void AddBusinessTrip(const domain::BusinessTrip& trip) = 0;
    virtual void UpdateBusinessTrip(const domain::BusinessTrip& trip) = 0;

    virtual void AddCompositionBusinessTrip(const domain::CompositionBusinessTrip& trip) = 0;
    virtual void DeleteCompositionBusinessTrip(const domain::CompositionBusinessTrip& trip) = 0;
    virtual void UpdateCompositionBusinessTrip(const domain::CompositionBusinessTrip& trip) = 0;

    virtual void AddDepartment(const domain::Department& dep) = 0;
    virtual void UpdateDepartment(const domain::Department& dep) = 0;

    virtual void AddEmployee(const domain::Employee& employee) = 0;
    virtual void UpdateEmployee(const domain::Employee& employee) = 0;

    virtual void AddJobTitle(const domain::JobTitle& job_title) = 0;
    virtual void UpdateJobTitle(const domain::JobTitle& job_title) = 0;

    virtual void AddOrder(const domain::Order& order) = 0;
    virtual void UpdateOrder(const domain::Order& order) = 0;

    virtual void AddStaffingTable(const domain::StaffingTable& staffing_table) = 0;
    virtual void UpdateStaffingTable(const domain::StaffingTable& staffing_table) = 0;

    virtual void AddTimeSheet(const domain::TimeSheet& time_sheet) = 0;
    virtual void UpdateTimeSheet(const domain::TimeSheet& time_sheet) = 0;

    virtual void AddVacation(const domain::Vacation& vacation) = 0;
    virtual void UpdateVacation(const domain::Vacation& vacation) = 0;

  protected:
    virtual ~Worker() = default;
};

} // namespace domain
