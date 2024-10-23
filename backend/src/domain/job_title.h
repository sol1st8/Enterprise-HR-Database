#pragma once

#include "../ui/view.h"

#include <optional>
#include <memory>
#include <string>
#include <vector>

namespace domain {

class Worker;

class JobTitle {
  public:
    JobTitle(int id, std::string job_title) : id_(id)
                                            , job_title_(std::move(job_title)) {}

    int GetId() const noexcept {
        return id_;
    }

    const std::string& GetJobTitle() const noexcept {
        return job_title_;
    }

  private:
    int id_;
    std::string job_title_;
};

class JobTitleRepository {
  public:
    virtual std::vector<ui::detail::JobTitleInfo> Get() const = 0;

    virtual std::shared_ptr<domain::Worker> GetWorker() const = 0;

  protected:
    ~JobTitleRepository() = default;
};

} // namespace domain
