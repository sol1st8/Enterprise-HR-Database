#pragma once

#include "../ui/view.h"

#include <memory>
#include <string>
#include <vector>

namespace domain {

class Worker;

class BusinessTrip {
  public:
    BusinessTrip(int trip_id, std::string country, std::string city,
                 std::string organization, std::string from_date,
                 std::string to_date, int days, std::string target) : trip_id_(trip_id)
                                                                    , country_(std::move(country))
                                                                    , city_(std::move(city))
                                                                    , organization_(std::move(organization))
                                                                    , from_date_(std::move(from_date))
                                                                    , to_date_(std::move(to_date))
                                                                    , days_(days)
                                                                    , target_(std::move(target)) {}

    int GetTripId() const noexcept {
        return trip_id_;
    }

    const std::string& GetCountry() const noexcept {
        return country_;
    }

    const std::string& GetCity() const noexcept {
        return city_;
    }

    const std::string& GetOrganization() const noexcept {
        return organization_;
    }

    const std::string& GetFromDate() const noexcept {
        return from_date_;
    }

    const std::string& GetToDate() const noexcept {
        return to_date_;
    }

    int GetDays() const noexcept {
        return days_;
    }

    const std::string& GetTarget() const noexcept {
        return target_;
    }

  private:
    int trip_id_;
    std::string country_;
    std::string city_;
    std::string organization_;
    std::string from_date_;
    std::string to_date_;
    int days_;
    std::string target_;
};

class BusinessTripRepository {
  public:
    virtual std::vector<ui::detail::BusinessTripInfo> Get() const = 0;

    virtual std::shared_ptr<domain::Worker> GetWorker() const = 0;

    virtual int GetCount() const = 0;

  protected:
    ~BusinessTripRepository() = default;
};

} // namespace domain
