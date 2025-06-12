#ifndef OTA_SERVICE_H
#define OTA_SERVICE_H

#include "core/ServiceBase.h"

class OtaService : public ServiceBase {
public:
    OtaService();

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

    // OTA相关状态标志（可扩展）
    bool updateInProgress;
};

#endif // OTA_SERVICE_H
