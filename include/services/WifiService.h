#ifndef WIFI_SERVICE_H
#define WIFI_SERVICE_H

#include "core/ServiceBase.h"

class WifiService : public ServiceBase {
public:
    WifiService();

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
};

#endif // WIFI_SERVICE_H
