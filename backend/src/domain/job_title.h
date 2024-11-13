#pragma once

#include "../ui/view.h"

#include <memory>

namespace domain {

class Worker;

class JobTitle {
  public:
    JobTitle(int job_title_id, std::string job_title) : job_title_id_(job_title_id)
                                                      , job_title_(std::move(job_title)) {}

    int GetJobTitleId() const noexcept {
        return job_title_id_;
    }

    const std::string& GetJobTitle() const noexcept {
        return job_title_;
    }

  private:
    int job_title_id_;
    std::string job_title_;
};

class JobTitleRepository {
  public:
    virtual std::vector<ui::detail::JobTitleInfo> Get() const = 0;

    virtual std::shared_ptr<domain::Worker> GetWorker() const = 0;

    virtual int GetCount() const = 0;

    virtual std::string GetJobTitle(int id) const = 0;
    virtual int GetJobTitleId(const std::string& job_title) const = 0;

  protected:
    ~JobTitleRepository() = default;
};

} // namespace domain
