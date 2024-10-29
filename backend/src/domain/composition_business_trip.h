#pragma once

#include "../ui/view.h"

#include <memory>
#include <string>
#include <vector>

namespace domain {

class Worker;

class CompositionBusinessTrip {
  public:
    CompositionBusinessTrip(int personnel_number, int trip_id) : personnel_number_(personnel_number)
                                                               , trip_id_(trip_id) {}

    int GetPersonnelNumber() const noexcept {
        return personnel_number_;
    }

    int GetTripId() const noexcept {
        return trip_id_;
    }

  private:
    int personnel_number_;
    int trip_id_;
};

class CompositionBusinessTripRepository {
  public:
    virtual std::vector<ui::detail::CompositionBusinessTripInfo> Get() const = 0;

    virtual std::shared_ptr<domain::Worker> GetWorker() const = 0;

  protected:
    ~CompositionBusinessTripRepository() = default;
};

} // namespace domain
