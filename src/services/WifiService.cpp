#define TAG "WiFi"
#include "services/WifiService.h"
#include "core/Log.h"

WifiService::WifiService()
    : status(ServiceStatus::UNINITIALIZED), enabled(true) {}

void WifiService::init() {
    OS_LOGI("Init");
    // 初始化 Wi-Fi 模块，配置连接参数等
    status = ServiceStatus::INITIALIZED;
}

void WifiService::start() {
    OS_LOGI("Start");
    // 尝试连接或开启AP模式
    status = ServiceStatus::RUNNING;
}

void WifiService::update() {
    if (!enabled || status != ServiceStatus::RUNNING) return;

    // 每周期检查连接状态、信号强度、重新连接等逻辑
    OS_LOGD("Update...");
}

void WifiService::stop() {
    OS_LOGI("Stop");
    // 断开连接或关闭模块
    status = ServiceStatus::STOPPED;
}

void WifiService::deinit() {
    OS_LOGI("Deinit");
    // 清理资源
    status = ServiceStatus::UNINITIALIZED;
}

std::string WifiService::getName() const {
    return "WifiService";
}

ServiceStatus WifiService::getStatus() const {
    return status;
}

void WifiService::setEnabled(bool en) {
    enabled = en;
}

bool WifiService::isEnabled() const {
    return enabled;
}
