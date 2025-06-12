#ifndef BLUETOOTH_SERVICE_H
#define BLUETOOTH_SERVICE_H

#include "core/ServiceBase.h"

class BluetoothService : public ServiceBase {
public:
    BluetoothService();

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

#endif // BLUETOOTH_SERVICE_H
