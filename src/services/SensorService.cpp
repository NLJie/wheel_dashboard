#define TAG "Sensor"
#include "core/Log.h"

#include "services/SensorService.h"
#include <cstdlib> // rand()
#include <ctime>
#include <algorithm> // std::clamp

SensorService::SensorService()
    : status(ServiceStatus::UNINITIALIZED), enabled(true)
{
    std::srand(std::time(nullptr)); // 初始化随机数种子
}

void SensorService::init()
{
    OS_LOGI("Init");
    status = ServiceStatus::INITIALIZED;
}

void SensorService::start()
{
    OS_LOGI("Start");
    status = ServiceStatus::RUNNING;
}

void SensorService::update()
{
    if (!enabled || status != ServiceStatus::RUNNING)
        return;

    // 模拟传感器数据更新
    simulateSensorUpdate();
}

void SensorService::stop()
{
    OS_LOGW("Stop called");
    status = ServiceStatus::STOPPED;
}

void SensorService::deinit()
{
    OS_LOGI("Deinit");
    status = ServiceStatus::UNINITIALIZED;
}

std::string SensorService::getName() const
{
    return "SensorService";
}

ServiceStatus SensorService::getStatus() const
{
    return status;
}

void SensorService::setEnabled(bool en)
{
    enabled = en;
}

bool SensorService::isEnabled() const
{
    return enabled;
}

SensorData SensorService::getSensorData()
{
    std::lock_guard<std::mutex> lock(data_mutex);
    return data; // 返回数据副本
}

// 模拟线性生成数据
float simulateLinearFloat(float current, float minVal, float maxVal, float stepSize = 1.0f) {
    float delta = ((std::rand() % 2001 - 1000) / 1000.0f) * stepSize; // [-stepSize, +stepSize]
    float next = current + delta;
    return std::clamp(next, minVal, maxVal);
}

// 工具函数：模拟整数值的缓慢变化
int simulateLinearInt(int current, int minVal, int maxVal, int step = 1) {
    int delta = (std::rand() % 3) - 1; // -1, 0, +1
    int next = current + delta * step;
    return std::clamp(next, minVal, maxVal);
}

void SensorService::simulateSensorUpdate()
{
    std::lock_guard<std::mutex> lock(data_mutex);

    // 随机生成模拟数据（你可以用真实采集代码替代）线性变化模拟
    data.speed_kmh = simulateLinearInt(data.light_level, 0, 180, 2);
    data.trip_km += data.speed_kmh * 0.01f;
    if (data.trip_km > 9999.0f)
        data.trip_km = 0;

    data.battery_percent = simulateLinearFloat(data.battery_percent, 30.0f, 100.0f, 0.2f);
    data.fuel_percent    = simulateLinearFloat(data.fuel_percent, 5.0f, 100.0f, 0.3f);
    data.temperature_c   = simulateLinearFloat(data.temperature_c, -20.0f, 50.0f, 0.5f);
    data.light_level     = simulateLinearInt(data.light_level, 0, 100, 2);

    // 档位：定时变更 or 模拟驾驶行为（可拓展为状态机）
    static int frame = 0;
    if (++frame % 5 == 0) {
        data.gear = static_cast<GearPosition>(std::rand() % 5); // P R N D L
    }

    // 其他信号状态：可模拟灯光变化
    data.left_turn_signal  = std::rand() % 100 < 2;
    data.right_turn_signal = std::rand() % 100 < 2;
    data.high_beam         = std::rand() % 100 < 1;
    data.low_beam          = !data.high_beam;
    data.position_lamp     = std::rand() % 100 < 3;

    data.engine_fault      = std::rand() % 1000 < 1;
    data.fuel_warning      = (data.fuel_percent < 10);
    data.abs_warning       = std::rand() % 1000 < 1;

    data.neutral           = (data.gear == GearPosition::NEUTRAL);
    data.engine_rpm        = simulateLinearInt(data.engine_rpm, 0, 8000, 100);

    OS_LOGD("Updating...");
}
