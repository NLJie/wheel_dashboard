#include "services/UiService.h"
#include "services/SensorService.h"

#include "core/ServiceManager.h"
#include "core/Log.h"

#include "lvgl.h"
#include "demos/lv_demos.h"

#include "driver_backends.h"
#include "simulator_util.h"
#include "simulator_settings.h"

#include <iostream>

#define TAG "UI"

UiService::UiService(ServiceManager& mgr)
    : manager(mgr), status(ServiceStatus::UNINITIALIZED), enabled(true) {}

void UiService::init() {
    OS_LOGI("Init LVLG");

    /* Initialize LVGL. */
    lv_init();

    /* Initialize the configured backend */
    driver_backends_register();
    driver_backends_print_supported();
    if (driver_backends_init_backend("FBDEV") == -1) {
        die("Failed to initialize display backend");
    }else{
        OS_LOGI("显示后端初始化成功");
    }
    // if (driver_backends_init_backend("AIC_FBDEV") == -1) {
    //     die("Failed to initialize display backend");
    // }else{
    //     OS_LOGI("显示后端初始化成功");
    // }
    /* Enable for EVDEV support */
#if LV_USE_EVDEV
    if (driver_backends_init_backend("EVDEV") == -1) {
        die("Failed to initialize evdev");
    }
#endif
    
    lv_demo_benchmark();

    /* Enter the run loop of the selected backend */
    driver_backends_run_loop();

    status = ServiceStatus::INITIALIZED;
}

void UiService::start() {
    OS_LOGI("Start");
    status = ServiceStatus::RUNNING;
}

// void UiService::update() {
//     if (!enabled || status == ServiceStatus::RUNNING)
//         return;

//     OS_LOGD("Updating...");
// }

void UiService::update() {
    if (!enabled || status != ServiceStatus::RUNNING) return;

    OS_LOGD("Updating...");
    // 从ServiceManager获取SensorService实例
    auto sensorService = manager.getService<SensorService>();
    if (!sensorService || !sensorService->isEnabled()) {
        OS_LOGW("SensorService unavailable or disabled");
        return;
    }

    // 获取传感器数据
    SensorData data = sensorService->getSensorData();

    // 用数据更新UI显示
    renderSpeed(data.speed_kmh);
    renderTrip(data.trip_km);
    renderBattery(data.battery_percent);
    renderFuel(data.fuel_percent);
    renderTemperature(data.temperature_c);
    renderLightLevel(data.light_level);
    renderGear(data.gear);
}

void UiService::stop() {
    OS_LOGD("Stop");
    status = ServiceStatus::STOPPED;
}

void UiService::restart() {
    std::cout << "UI Restarting..." << std::endl;
    stop();
    start();
}

void UiService::deinit() {
    OS_LOGD("Deinit");
    status = ServiceStatus::UNINITIALIZED;
}

std::string UiService::getName() const {
    return "UiService";
}

ServiceStatus UiService::getStatus() const {
    return status;
}

void UiService::setEnabled(bool en) {
    enabled = en;
}

bool UiService::isEnabled() const {
    return enabled;
}

// 以下是UI显示的伪代码函数，实际应该调用你的GUI库（如LVGL）接口
void UiService::renderSpeed(float speed) {
    std::cout << "[UI] Speed: " << speed << " km/h" << std::endl;
}

void UiService::renderTrip(float trip) {
    std::cout << "[UI] Trip: " << trip << " km" << std::endl;
}

void UiService::renderBattery(float percent) {
    std::cout << "[UI] Battery: " << percent << " %" << std::endl;
}

void UiService::renderFuel(float percent) {
    std::cout << "[UI] Fuel: " << percent << " %" << std::endl;
}

void UiService::renderTemperature(float temp) {
    std::cout << "[UI] Temperature: " << temp << " °C" << std::endl;
}

void UiService::renderLightLevel(int level) {
    std::cout << "[UI] Light Level: " << level << std::endl;
}

std::string gearToString(GearPosition gear) {
    switch (gear) {
        case GearPosition::PARK:    return "P";
        case GearPosition::REVERSE: return "R";
        case GearPosition::NEUTRAL: return "N";
        case GearPosition::DRIVE:   return "D";
        case GearPosition::LOW:     return "L";
        case GearPosition::UNKNOWN: return "Unknown";
        default:                    return "Invalid";
    }
}

void UiService::renderGear(GearPosition gear) {
    std::cout << "[UI] gear: " << gearToString(gear) << std::endl;
}