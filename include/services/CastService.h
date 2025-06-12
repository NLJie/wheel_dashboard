#ifndef CAST_SERVICE_H
#define CAST_SERVICE_H

#include "core/ServiceBase.h"

class CastService : public ServiceBase {
public:
    CastService();

    void init() override;
    void deinit() override;
    void start() override;
    void stop() override;
    void update() override;

    std::string getName() const override;
    ServiceStatus getStatus() const override;

    void setEnabled(bool en) override;
    bool isEnabled() const override;

private:
    ServiceStatus status;
    bool enabled;

    // 可扩展的状态标志
    bool isCasting;
};

#endif // CAST_SERVICE_H
