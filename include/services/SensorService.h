#ifndef SENSOR_SERVICE_H
#define SENSOR_SERVICE_H

#include "SensorData.h"
#include "core/ServiceBase.h"
#include <mutex>

class SensorService : public ServiceBase {
public:
    SensorService();

    void init() override;
    void deinit() override;
    void start() override;
    void stop() override;
    void update() override;

    std::string getName() const override;
    ServiceStatus getStatus() const override;

    void setEnabled(bool en) override;
    bool isEnabled() const override;

    // 获取传感器数据的线程安全接口（拷贝当前数据）
    SensorData getSensorData();

    // 模拟更新数据（真实环境中此函数应由硬件采集线程调用）
    void simulateSensorUpdate();

private:
    ServiceStatus status;
    bool enabled;
    SensorData data;
    std::mutex data_mutex;  // 保护 data 线程安全
};

#endif // SENSOR_SERVICE_H
