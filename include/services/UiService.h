#ifndef UI_SERVICE_H
#define UI_SERVICE_H

#include "core/ServiceBase.h"
#include "SensorData.h"
#include <memory>

class ServiceManager; // 前向声明，避免循环依赖

class UiService : public ServiceBase {
public:
    explicit UiService(ServiceManager& mgr);

    void init() override;
    void deinit() override;
    void start() override;
    void stop() override;
    void update() override;
    void restart() override;

    std::string getName() const override;
    ServiceStatus getStatus() const override;

    void setEnabled(bool en) override;
    bool isEnabled() const override;

private:
    ServiceManager& manager;
    ServiceStatus status;
    bool enabled;

    // UI显示函数示例
    void renderSpeed(float speed);
    void renderTrip(float trip);
    void renderBattery(float percent);
    void renderFuel(float percent);
    void renderTemperature(float temp);
    void renderLightLevel(int level);
    void renderGear(GearPosition gear);
};
#endif
